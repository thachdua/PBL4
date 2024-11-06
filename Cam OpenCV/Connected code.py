import cv2 
import mediapipe as mp
import urllib.request
import numpy as np

face_mesh = mp.solutions.face_mesh.FaceMesh()
url = 'http://10.10.27.250/cam-hi.jpg'

while True:
    img_resp = urllib.request.urlopen(url)
    img_np = np.array(bytearray(img_resp.read()), dtype=np.uint8)
    frame = cv2.imdecode(img_np, -1)

    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    
    output = face_mesh.process(rgb_frame)
    landmark_point = output.multi_face_landmarks
    frame_h, frame_w, _ = frame.shape
    
    if landmark_point:
        landmarks = landmark_point[0].landmark
        for landmark in landmarks:
            x = int(landmark.x * frame_w)
            y = int(landmark.y * frame_h)
            cv2.circle(frame, (x, y), 3, (0, 255, 0))
    
    print(landmark_point)
    
    cv2.imshow('Face', frame)
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cv2.destroyAllWindows()
