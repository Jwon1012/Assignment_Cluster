import os
from PIL import Image

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
image_dir = os.path.join(BASE_DIR, "images")

valid_extensions = ('.jpg', '.jpeg', '.png', '.bmp', '.webp')

print("🚀 TM 업로드용 이미지 포맷(JPG) 일괄 표준화 시작...\n")

converted_count = 0
removed_count = 0

for root, dirs, files in os.walk(image_dir):
    for file in files:
        file_path = os.path.join(root, file)
        ext = os.path.splitext(file)[1].lower()
        
        # 이미지 외 쓸데없는 파일이거나 webp/png 등 변환 대상인 경우
        if ext in valid_extensions:
            try:
                # 이미지 열어서 RGB 변환 후 .jpg로 재저장
                with Image.open(file_path) as img:
                    rgb_img = img.convert('RGB')
                    new_file_path = os.path.splitext(file_path)[0] + ".jpg"
                    rgb_img.save(new_file_path, 'JPEG')
                    
                    # 기존 .webp 등 호환성 떨어지는 파일은 삭제
                    if ext != '.jpg':
                        os.remove(file_path)
                        converted_count += 1
            except Exception as e:
                # 깨진 파일 삭제
                print(f"⚠️ 깨진 파일 삭제: {file}")
                os.remove(file_path)
                removed_count += 1

print(f"\n🎉 변환 완료! {converted_count}개 파일 JPG 변환 완료, {removed_count}개 깨진 파일 정리됨.")
print("이제 images 폴더의 사진들을 TM에 다시 드래그 앤 드롭해 보세요!")