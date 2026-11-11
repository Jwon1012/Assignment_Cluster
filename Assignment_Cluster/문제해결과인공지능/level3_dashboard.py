import sys
import cv2
import numpy as np
from PyQt6.QtCore import QTimer, Qt
from PyQt6.QtGui import QImage, QPixmap
from PyQt6.QtWidgets import QApplication, QMainWindow, QLabel, QVBoxLayout, QHBoxLayout, QWidget

import matplotlib.pyplot as plt
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas

# 1. 색상 범위 정의 (HSV)
COLOR_RANGES = {
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

class DashboardWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Level 3: Real-Time Environment & Color Dashboard")
        self.setGeometry(100, 100, 1100, 600)

        # 웹캠 설정
        self.cap = cv2.VideoCapture(0)

        # 메인 레이아웃 (좌: 웹캠 & 결과 / 우: 파이차트)
        main_layout = QHBoxLayout()
        left_layout = QVBoxLayout()
        right_layout = QVBoxLayout()

        # 1. 웹캠 화면 레이블
        self.webcam_label = QLabel("웹캠 로딩 중...")
        self.webcam_label.setFixedSize(640, 480)
        self.webcam_label.setStyleSheet("border: 2px solid #555; background-color: #000;")
        left_layout.addWidget(self.webcam_label)

        # 2. AI 판별 클래스 텍스트 출력 레이블
        self.result_label = QLabel("AI 판별 분위기: Analying...")
        self.result_label.setStyleSheet("font-size: 20px; font-weight: bold; color: #1E88E5; margin-top: 10px;")
        left_layout.addWidget(self.result_label)

        # 3. Matplotlib 파이차트 캔버스
        self.figure, self.ax = plt.subplots(figsize=(4, 4))
        self.canvas = FigureCanvas(self.figure)
        right_layout.addWidget(QLabel("<b>[실시간 상위 3개 HSV 색상 지배율]</b>"))
        right_layout.addWidget(self.canvas)

        main_layout.addLayout(left_layout)
        main_layout.addLayout(right_layout)

        container = QWidget()
        container.setLayout(main_layout)
        self.setCentralWidget(container)

        # 실시간 업데이트 타이머 (30ms 간격)
        self.timer = QTimer()
        self.timer.timeout.connect(self.update_frame)
        self.timer.start(30)

    def update_frame(self):
        ret, frame = self.cap.read()
        if not ret:
            return

        # 1. HSV 색상 분석 (Level 1 파이프라인 연동)
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        total_pixels = frame.shape[0] * frame.shape[1]

        color_counts = {}
        for color_name, ranges in COLOR_RANGES.items():
            color_mask = np.zeros(hsv.shape[:2], dtype=np.uint8)
            for (lower, upper) in ranges:
                mask = cv2.inRange(hsv, np.array(lower), np.array(upper))
                color_mask = cv2.bitwise_or(color_mask, mask)
            color_counts[color_name] = cv2.countNonZero(color_mask)

        # 상위 3개 추출
        sorted_colors = sorted(color_counts.items(), key=lambda x: x[1], reverse=True)[:3]
        top3_labels = [c[0] for c in sorted_colors]
        top3_ratios = [round((c[1] / total_pixels) * 100, 1) for c in sorted_colors]
        
        etc_ratio = round(100 - sum(top3_ratios), 1)
        if etc_ratio > 0:
            top3_labels.append("Etc")
            top3_ratios.append(etc_ratio)

        # 2. 파이차트 실시간 갱신
        self.ax.clear()
        colors_map = {'Red':'red', 'Orange':'orange', 'Yellow':'yellow', 'Green':'green', 
                      'Blue':'blue', 'Purple':'purple', 'Pink':'pink', 'White':'lightgray', 
                      'Black':'black', 'Gray':'gray', 'Etc':'whitesmoke'}
        
        plot_colors = [colors_map.get(l, 'blue') for l in top3_labels]
        self.ax.pie(top3_ratios, labels=top3_labels, autopct='%1.1f%%', colors=plot_colors, startangle=140)
        self.ax.set_title("Top 3 Color Ratios")
        self.canvas.draw()

        # 3. 간단한 가상 규칙기반 TM 분위기 판별 시연 (또는 HSV 기반 추론)
        primary_color = top3_labels[0]
        if primary_color in ['Blue', 'White']:
            inferred_class = "Day_View (낮 / 야외)"
        elif primary_color in ['Orange', 'Yellow', 'Red']:
            inferred_class = "Sunset_View (노을 / 저녁)"
        elif primary_color in ['Black', 'Gray']:
            inferred_class = "Night_View / Indoor_View (야경 / 실내)"
        else:
            inferred_class = "Etc (예외 / 노이즈)"

        self.result_label.setText(f"🔍 AI 분석 분위기: {inferred_class}")

        # 4. PyQt 이미지 변환 및 출력
        rgb_image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        h, w, ch = rgb_image.shape
        bytes_per_line = ch * w
        convert_to_Qt_format = QImage(rgb_image.data, w, h, bytes_per_line, QImage.Format.Format_RGB888)
        p = convert_to_Qt_format.scaled(640, 480, Qt.AspectRatioMode.KeepAspectRatio)
        self.webcam_label.setPixmap(QPixmap.fromImage(p))

    def closeEvent(self, event):
        self.cap.release()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = DashboardWindow()
    window.show()
    sys.exit(app.exec())