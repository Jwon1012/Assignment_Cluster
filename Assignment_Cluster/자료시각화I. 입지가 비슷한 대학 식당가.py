import re
import time
import requests
import pandas as pd
import openpyxl
from pathlib import Path

# ==============================================================================
# 1. 설정 (발급받은 SK Open API appKey를 아래 따옴표 안에 붙여넣으세요)
# ==============================================================================
SK_APP_KEY = "d03nxxkTmM80q5whXzH8Q9DkDSsNe8po7iRp1T4F"

BASE_DIR = Path(__file__).resolve().parent
XLSX_PATH = BASE_DIR / "유사입지_13개대학_주변식당_전처리.xlsx"
SAVE_INTERVAL = 50  # 50행마다 자동 중간 저장 (일일 무료 한도 도달 시에도 데이터 보존)

HEADERS_GET = {
    "Accept": "application/json",
    "appKey": SK_APP_KEY,
}
HEADERS_POST = {
    "Accept": "application/json",
    "Content-Type": "application/json",
    "appKey": SK_APP_KEY,
}


# ==============================================================================
# 2. Tmap API 호출 함수 (좌표 변환 & 보행자 도보 거리 계산)
# ==============================================================================
def clean_addr_for_geocoding(addr: str) -> str:
    """층/호수 및 괄호 법정동을 제거하여 지오코딩 정확도를 높임"""
    s = re.sub(r"\s*\([^)]*\)\s*$", "", str(addr)).strip()
    m = re.match(r"^(.+?(?:대로|로|길)(?:\d+번길)?\s*\d+(?:-\d+)?)", s)
    if m:
        return m.group(1)
    m2 = re.match(r"^(.+?(?:동|리)\s*(?:산\s*)?\d+(?:-\d+)?)", s)
    if m2:
        return m2.group(1)
    return s


def search_poi_coord(keyword: str):
    """Tmap POI 통합검색으로 장소(대학 정문 등)의 출입구 좌표(lon, lat) 조회"""
    url = "https://apis.openapi.sk.com/tmap/pois"
    params = {
        "version": 1,
        "searchKeyword": keyword,
        "resCoordType": "WGS84GEO",
        "reqCoordType": "WGS84GEO",
        "count": 1,
    }
    resp = requests.get(url, headers=HEADERS_GET, params=params, timeout=10)
    if resp.status_code == 429:
        raise RuntimeError("QUOTA_EXCEEDED")
    if resp.status_code != 200:
        return None
    pois = resp.json().get("searchPoiInfo", {}).get("pois", {}).get("poi", [])
    if not pois:
        return None
    poi = pois[0]
    lon = poi.get("frontLon") if poi.get("frontLon") not in [None, "", "0"] else poi.get("noorLon")
    lat = poi.get("frontLat") if poi.get("frontLat") not in [None, "", "0"] else poi.get("noorLat")
    if lon and lat:
        return float(lon), float(lat)
    return None


def geocode_address(addr: str, fallback_keyword: str):
    """Tmap Full Text Geocoding으로 주소를 좌표(lon, lat)로 변환 (실패 시 POI 검색 보완)"""
    clean_addr = clean_addr_for_geocoding(addr)
    url = "https://apis.openapi.sk.com/tmap/geo/fullAddrGeo"
    params = {
        "version": 1,
        "format": "json",
        "coordType": "WGS84GEO",
        "fullAddr": clean_addr,
    }
    resp = requests.get(url, headers=HEADERS_GET, params=params, timeout=10)
    if resp.status_code == 429:
        raise RuntimeError("QUOTA_EXCEEDED")
    if resp.status_code == 200:
        coords = resp.json().get("coordinateInfo", {}).get("coordinate", [])
        if coords:
            c = coords[0]
            lon = c.get("newLon") if c.get("newLon") not in [None, "", "0"] else c.get("lon")
            lat = c.get("newLat") if c.get("newLat") not in [None, "", "0"] else c.get("lat")
            if lon and lat:
                return float(lon), float(lat)
    # 주소 변환 실패 시 '<시군구> <식당명>' POI 검색으로 재시도
    return search_poi_coord(fallback_keyword)


def get_tmap_walking_distance(start_coord, end_coord, straight_m):
    """Tmap 보행자 경로 안내 API로 실제 보행자 도로 기준 도보 거리(m) 산출"""
    url = "https://apis.openapi.sk.com/tmap/routes/pedestrian?version=1"
    payload = {
        "startX": start_coord[0],
        "startY": start_coord[1],
        "endX": end_coord[0],
        "endY": end_coord[1],
        "reqCoordType": "WGS84GEO",
        "resCoordType": "WGS84GEO",
        "startName": "대학정문",
        "endName": "식당",
    }
    try:
        resp = requests.post(url, headers=HEADERS_POST, json=payload, timeout=10)
        if resp.status_code == 429:
            raise RuntimeError("QUOTA_EXCEEDED")
        if resp.status_code == 200:
            # 특수 제어 문자로 인한 JSON 파싱 에러 방지를 위해 원본 텍스트 정제
            import json
            cleaned_text = re.sub(r'[\x00-\x1f\x7f-\x9f]', '', resp.text)
            data = json.loads(cleaned_text)
            
            features = data.get("features", [])
            if features:
                dist = features[0].get("properties", {}).get("totalDistance")
                if dist is not None:
                    return int(dist)
    except Exception:
        pass  # 에러 발생 시 아래 fallback 로직으로 자연스럽게 넘어감

    # 경로 안내 실패 시 근거리인 경우 직선거리 반영
    if straight_m is not None and straight_m <= 120:
        return int(straight_m)
    return None


def reclassify_catchment(univ: str, addr: str, straight_m: float, walk_m: float) -> str:
    """수집된 실제 도보 길이(600m 이내) 기준으로 식당가 생활권 구분 갱신"""
    m = re.search(r"\(([^)]+)\)", str(addr))
    dong = m.group(1) if m else ""
    is_walk_core = (walk_m <= 600) if pd.notna(walk_m) else (straight_m <= 600)

    if univ == "상명대학교 서울캠퍼스":
        if dong in ["구기동", "평창동", "부암동"]:
            return "제외_지형단절권역"
        if dong == "홍지동":
            return "1차_도보생활권"
        if dong in ["신영동", "홍은동"]:
            return "1차_도보생활권" if is_walk_core else "2차_대중교통연계생활권"
        if dong == "홍제동":
            return "2차_대중교통연계생활권"
        return "제외_외곽권역"

    if univ == "용인대학교":
        if dong in ["이동읍 서리", "남동"]:
            return "제외_지형단절권역"
        if is_walk_core:
            return "1차_도보생활권"
        elif dong in ["삼가동", "역북동"] and straight_m <= 2000:
            return "2차_대중교통연계생활권"
        return "제외_외곽권역"

    if is_walk_core:
        return "1차_도보생활권"
    elif straight_m <= 1500:
        return "2차_대중교통연계생활권"
    return "제외_외곽권역"


# ==============================================================================
# 3. 메인 실행 파이프라인 (기존 엑셀 서식·시트 유지 + 실시간 진행률 출력)
# ==============================================================================
def main():
    if "여기에_" in SK_APP_KEY or not SK_APP_KEY.strip():
        print("❌ 상단의 SK_APP_KEY 변수에 발급받은 앱키를 먼저 입력해 주세요!")
        return

    wb = openpyxl.load_workbook(XLSX_PATH)
    ws = wb["식당_데이터_전처리"]
    total_rows = ws.max_row - 1

    # 1) 13개 대학 정문 좌표 확보
    univ_names = list(dict.fromkeys(
        ws.cell(row=r, column=1).value for r in range(2, ws.max_row + 1)
    ))
    univ_coords = {}
    print("=== 1단계: 13개 대학 정문 좌표 조회 시작 ===")
    for u in univ_names:
        coord = search_poi_coord(f"{u} 정문") or search_poi_coord(u)
        univ_coords[u] = coord
        print(f"  · {u}: {coord}")
        time.sleep(0.05)

    # 2) 빈칸인 행만 Tmap 보행자 거리 조회 및 실시간 출력
    print(f"\n=== 2단계: 식당 도보 거리 수집 시작 (전체 {total_rows}행) ===")
    updated_count = 0
    addr_cache = {}  # 동일 건물/상가 주소 중복 API 호출 방지용 캐시

    try:
        for r in range(2, ws.max_row + 1):
            curr_walk = ws.cell(row=r, column=3).value
            if curr_walk is not None and str(curr_walk).strip() != "":
                continue  # 이미 채워진 행은 건너뜀 (이어하기 지원)

            univ = ws.cell(row=r, column=1).value
            name = ws.cell(row=r, column=4).value
            addr = ws.cell(row=r, column=7).value
            straight_m = ws.cell(row=r, column=8).value

            start_coord = univ_coords.get(univ)
            if not start_coord:
                continue

            clean_addr = clean_addr_for_geocoding(addr)
            if clean_addr in addr_cache:
                end_coord = addr_cache[clean_addr]
            else:
                sigungu = str(addr).split(" ")[1] if len(str(addr).split(" ")) > 1 else ""
                end_coord = geocode_address(addr, f"{sigungu} {name}")
                addr_cache[clean_addr] = end_coord

            walk_m = None
            if end_coord:
                walk_m = get_tmap_walking_distance(start_coord, end_coord, straight_m)

            if walk_m is not None:
                ws.cell(row=r, column=3, value=walk_m)
                new_cat = reclassify_catchment(univ, addr, straight_m, walk_m)
                ws.cell(row=r, column=21, value=new_cat)
                updated_count += 1
                print(f"[{r-1}/{total_rows}] {univ} | {name} -> 도보 {walk_m}m ({new_cat})")
            else:
                print(f"[{r-1}/{total_rows}] {univ} | {name} -> 조회 실패(건너뜀)")

            if updated_count > 0 and updated_count % SAVE_INTERVAL == 0:
                wb.save(XLSX_PATH)
                print(f"  💾 중간 저장 완료 ({updated_count}건 반영됨)")

            time.sleep(0.05)  # 초당 요청 제한 방지

    except RuntimeError as e:
        if "QUOTA_EXCEEDED" in str(e):
            wb.save(XLSX_PATH)
            print(f"\n⚠️ SK Open API 일일 무료 호출 한도에 도달하여 현재까지 수집된 {updated_count}건을 안전하게 저장했습니다.")
            print("내일(또는 다른 계정 appKey로 변경 후) 다시 실행하시면 빈칸부터 자동으로 이어서 수집합니다!")
            return
        raise

    wb.save(XLSX_PATH)
    print(f"\n✅ 수집 완료! 총 {updated_count}건의 도보 길이가 '{XLSX_PATH.name}'에 반영되었습니다.")


if __name__ == "__main__":
    main()