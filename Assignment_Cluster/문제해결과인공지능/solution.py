import os
import cv2
import numpy as np

# 1. 파일 위치 기준 절대 경로 설정
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
image_dir = os.path.join(BASE_DIR, "images")
csv_file_path = os.path.join(BASE_DIR, "level2_dataset.csv")

# 2. 색상 범주 정의 (HSV 범위)
color_ranges = {
    'Red': [((0, 50, 50), (10, 255, 255)), ((170, 50, 50), (180, 255, 255))],
    'Orange': [((11, 50, 50), (25, 255, 255))],
    'Yellow': [((26, 50, 50), (35, 255, 255))],
    'Green': [((36, 50, 50), (85, 255, 255))],
    'Blue': [((86, 50, 50), (125, 255, 255))],
    'Purple': [((126, 50, 50), (145, 255, 255))],
    'Pink': [((146, 50, 50), (169, 255, 255))],
    'White': [((0, 0, 200), (180, 30, 255))],
    'Black': [((0, 0, 0), (180, 255, 45))],
    'Gray': [((0, 0, 46), (180, 49, 199))]
}

valid_extensions = ('.jpg', '.jpeg', '.png', '.bmp', '.webp')

# 3. CSV 무조건 초기화 생성 (헤더에 Label 필수 포함!)
with open(csv_file_path, "w", encoding="utf-8") as f:
    f.write("FileName,Color1,Ratio1,Color2,Ratio2,Color3,Ratio3,Etc_Ratio,Label\n")

print("🔍 images 하위 폴더 이미지 분석 시작...\n")

total_count = 0

# 4. os.walk를 통한 하위 폴더 5개 전체 탐색
if os.path.exists(image_dir):
    for root, dirs, files in os.walk(image_dir):
        # images 폴더 자체는 제외하고 서브폴더명(Label) 추출
        if root == image_dir:
            continue
        
        label = os.path.basename(root)  # 예: dark_outfit, Etc, Evening_view 등
        
        for file in files:
            if file.lower().endswith(valid_extensions):
                file_path = os.path.join(root, file)
                
                # cv2 imdecode를 이용한 한글 경로 및 webp 대응 읽기
                img_array = np.fromfile(file_path, np.uint8)
                img = cv2.imdecode(img_array, cv2.IMREAD_COLOR)
                
                if img is None:
                    continue

                hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
                total_pixels = img.shape[0] * img.shape[1]

                color_counts = {}
                for color_name, ranges in color_ranges.items():
                    color_mask = np.zeros(hsv.shape[:2], dtype=np.uint8)
                    for (lower, upper) in ranges:
                        mask = cv2.inRange(hsv, np.array(lower), np.array(upper))
                        color_mask = cv2.bitwise_or(color_mask, mask)
                    color_counts[color_name] = cv2.countNonZero(color_mask)

                # 상위 3개 색상 추출
                sorted_colors = sorted(color_counts.items(), key=lambda x: x[1], reverse=True)
                top3 = sorted_colors[:3]

                top3_ratios = [(c, round((count / total_pixels) * 100, 2)) for c, count in top3]
                etc_count = total_pixels - sum(count for _, count in top3)
                etc_ratio = round((etc_count / total_pixels) * 100, 2)

                # CSV에 데이터 + 라벨 기록
                row = f"{file},{top3_ratios[0][0]},{top3_ratios[0][1]},{top3_ratios[1][0]},{top3_ratios[1][1]},{top3_ratios[2][0]},{top3_ratios[2][1]},{etc_ratio},{label}\n"
                
                with open(csv_file_path, "a", encoding="utf-8") as f:
                    f.write(row)
                
                total_count += 1
                print(f"✅ 분석 완료 [{label}]: {file}")

print(f"\n🎉 총 {total_count}개의 이미지가 '{csv_file_path}'에 성공적으로 가공되어 라벨링 되었습니다!")