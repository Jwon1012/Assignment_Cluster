import cv2
import numpy as np
import csv
import os

# 1. HSV 색상 범위 정의 (유채색 6종 + 무채색 3종)
# 국제 표준 색상 공간(Color Space) 정률 및 색상환(Color Wheel)에서 기원한 수치
COLOR_RANGES = {
    # [무채색] 명도(V)와 채도(S) 기준
    'Black':      {'lower': np.array([0, 0, 0]),       'upper': np.array([180, 255, 45])},
    'White':      {'lower': np.array([0, 0, 200]),     'upper': np.array([180, 30, 255])},
    'Gray':       {'lower': np.array([0, 0, 46]),      'upper': np.array([180, 40, 199])},
    # 유채색: 색상(H: 0~180) 기준
    'Red':        [
                    {'lower': np.array([0, 50, 50]),   'upper': np.array([10, 255, 255])},
                    {'lower': np.array([170, 50, 50]), 'upper': np.array([180, 255, 255])}
                  ],
    'Skin/Orange':{'lower': np.array([11, 40, 50]),    'upper': np.array([25, 255, 255])},
    'Yellow':     {'lower': np.array([26, 50, 50]),    'upper': np.array([35, 255, 255])},
    'Green':      {'lower': np.array([36, 50, 50]),    'upper': np.array([85, 255, 255])},
    'Blue':       {'lower': np.array([86, 50, 50]),    'upper': np.array([135, 255, 255])},
    'Purple':     {'lower': np.array([136, 50, 50]),   'upper': np.array([169, 255, 255])}
}

# 2. 이미지 1장 추출 함수
def extract_top3_colors(frame):
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV) 
    total_pixels = frame.shape[0] * frame.shape[1]
    color_counts = {}

    # 각 색상 마스크별 픽셀 수 계산
    for color_name, bounds in COLOR_RANGES.items():
        if isinstance(bounds, list): # Red처럼 범위가 2개인 경우
            #inRange함수는 영상내의 픽셀을 조사하여 맞으면 흰색, 안맞으면 검정색 마스크 생성
            # 1. 0~10 범위에 해당하는 픽셀들만 흰색(255)으로 표시한 마스크 1 생성
            mask1 = cv2.inRange(hsv, bounds[0]['lower'], bounds[0]['upper']) 
            # 2. 170~180 범위에 해당하는 픽셀들만 흰색(255)으로 표시한 마스크 2 생성
            mask2 = cv2.inRange(hsv, bounds[1]['lower'], bounds[1]['upper'])
            # 3. or연산으로 합치
            mask = cv2.bitwise_or(mask1, mask2)
        else:
            mask = cv2.inRange(hsv, bounds['lower'], bounds['upper'])
        
        color_counts[color_name] = cv2.countNonZero(mask) #해당되는 색상의 픽셀 개수 카운팅 

    # 내림차순 정렬 후 비율 계산
    sorted_colors = sorted(color_counts.items(), key=lambda x: x[1], reverse=True)
    
    top3 = sorted_colors[:3] #내림차순으로 정리한 후 0번째 인덱스(1위)부터 2번째(3위)까지 슬라이싱
    top3_sum = sum([count for _, count in top3]) #상위 3개의 색상이 차지하는 총 픽셀의 개수를 제고, 색상 이름을 쓰지 말고 픽셀수만 카운트
    etc_ratio = round(((total_pixels - top3_sum) / total_pixels) * 100, 2)
    
    results = []
    for name, count in top3:
        ratio = round((count / total_pixels) * 100, 2)
        results.append((name, ratio))
        
    return results, etc_ratio

# 3. 폴더 내 이미지 일괄 처리 및 CSV 생성
image_folder = "./images"  # 분석할 이미지들이 들어있는 폴더 경로

# 폴더가 없으면 자동 생성
if not os.path.exists(image_folder):
    os.makedirs(image_folder)
    print(f"'{image_folder}' 폴더를 생성했습니다. 여기에 테스트용 이미지(.jpg, .png)를 넣어주세요!")

# CSV 파일 생성
with open("level2_dataset.csv", mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['FileName', 'Color1', 'Ratio1', 'Color2', 'Ratio2', 'Color3', 'Ratio3', 'Etc_Ratio'])

    valid_extensions = ('.jpg', '.jpeg', '.png', '.bmp')
    image_files = [f for f in os.listdir(image_folder) if f.lower().endswith(valid_extensions)]

    if not image_files:
        print(f"'{image_folder}' 폴더 안에 분석할 이미지 파일이 없습니다.")
    else:
        print(f"총 {len(image_files)}장의 이미지 분석을 시작합니다...\n")
        
        for idx, file_name in enumerate(image_files, 1):
            img_path = os.path.join(image_folder, file_name)
            frame = cv2.imread(img_path)

            if frame is None:
                continue

            top3, etc = extract_top3_colors(frame)
            
            row = [
                file_name,
                top3[0][0], top3[0][1],
                top3[1][0], top3[1][1],
                top3[2][0], top3[2][1],
                etc
            ]
            writer.writerow(row)
            print(f"[{idx}/{len(image_files)}] {file_name} -> 1위: {top3[0][0]}({top3[0][1]}%), 2위: {top3[1][0]}({top3[1][1]}%), 3위: {top3[2][0]}({top3[2][1]}%), Etc: {etc}%")

print("\n분석 완료! 결과가 level2_dataset.csv 파일로 저장되었습니다.")