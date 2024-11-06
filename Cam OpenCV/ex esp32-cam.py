import cv2
import urllib.request
import numpy as np

# Load cascade files for face and eye detection
f_cas = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
eye_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_eye.xml')

# URL của ESP32-CAM với độ phân giải 240x176 và định dạng MJPEG
url = 'http://192.168.1.33/240x176.mjpeg'

cv2.namedWindow("Live Transmission", cv2.WINDOW_AUTOSIZE)

# Mở luồng video MJPEG từ URL
stream = urllib.request.urlopen(url)
byte_data = b''

while True:
    try:
        # Đọc dữ liệu từ luồng video
        byte_data += stream.read(1024)
        a = byte_data.find(b'\xff\xd8')
        b = byte_data.find(b'\xff\xd9')
        
        if a != -1 and b != -1:
            jpg = byte_data[a:b+2]
            byte_data = byte_data[b+2:]

            # Giải mã hình ảnh
            img = cv2.imdecode(np.frombuffer(jpg, dtype=np.uint8), cv2.IMREAD_COLOR)

            # Chuyển ảnh sang grayscale
            gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
            faces = f_cas.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5)

            # Vẽ khung quanh khuôn mặt
            for x, y, w, h in faces:
                cv2.rectangle(img, (x, y), (x + w, y + h), (0, 0, 255), 3)
                roi_gray = gray[y:y + h, x:x + w]
                roi_color = img[y:y + h, x:x + w]
                eyes = eye_cascade.detectMultiScale(roi_gray)

                # Vẽ khung quanh mắt
                for (ex, ey, ew, eh) in eyes:
                    cv2.rectangle(roi_color, (ex, ey), (ex + ew, ey + eh), (0, 255, 0), 2)

            # Hiển thị luồng video
            cv2.imshow("Live Transmission", img)

            # Nhấn 'q' để thoát
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

    except Exception as e:
        print(f"Lỗi: {e}")
        break

cv2.destroyAllWindows()
