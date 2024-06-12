'''
from flask import Flask, request

app = Flask(__name__)

@app.route('/post_data', methods=['POST'])
def post_data():
    data = request.json
    print(f"Received data: {data}")
    return "Data received", 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
'''

import socket
import cv2
import numpy as np

def receive_image(sock):
    print("3")
    size = int.from_bytes(sock.recv(2), 'big')
    print(size)
    img_data = sock.recv(size)
    np_data = np.frombuffer(img_data, np.uint8)
    img = cv2.imdecode(np_data, cv2.IMREAD_COLOR)
    print(img)
    return img

# 连接到ESP8266
host = '192.168.114.142'
port = 80

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
try:
    sock.connect((host, port))
except socket.error as e:
    print("连接失败:", e)
else:
    print("连接成功")

while True:
    print("1")
    img = receive_image(sock)
    cv2.imshow('Image', img)
    print("2")
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

sock.close()
cv2.destroyAllWindows()

