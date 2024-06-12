#控制小车的相关网站
from flask import Flask,request,Response,render_template,send_from_directory
import cv2
import numpy as np
import os
import requests
#调用修改图片的函数
from photo_revise import resizesize_image,resizeDrawRectangle_image

app = Flask(__name__)

ESP8266_IP = 'http://192.168.114.142'

#网站首页
@app.route('/')
def index():
    return render_template('index.html')

#上传图像数据a
@app.route('/upload', methods=['POST'])
def upload():
    file = request.files['image']
    if file:
        file.save(os.path.join('static', 'current_frame.jpg'))
        print("get it!")
    '''
    data = request.data
    nparr = np.frombuffer(data, np.uint8)
    img = cv2.imdecode(nparr, cv2.IMREAD_GRAYSCALE)
    if img is not None:
        cv2.imwrite('static/current_frame', img)
    '''
    return '', 204

#视频流，将有gen_frames()生成的视频帧发送给客户端
@app.route('/video_feed')
def video_feed():
    resizeDrawRectangle_image('static/current_frame.jpg','static/current_frame_draw.jpg')
    #将图片修改大小保存到static/current_frame_revised.jpg
    resizesize_image('static/current_frame_draw.jpg','static/current_frame_revised.jpg',(600,300))
    return Response(gen_frames(), mimetype='multipart/x-mixed-replace; boundary=frame')

def gen_frames():
    #不断读取视频帧
    while True:
        frame = open(os.path.join('static', 'current_frame_revised.jpg'), 'rb').read()
        #将读取到的数据转化为http协议接收的格式
        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n\r\n')


#控制接收返回
@app.route('/control')
def control():
    key = request.args.get('key')
    if key:
        #将信息发送到终端
        print(f"Key pressed: {key}")
        #将信息发送到esp8266设备，发送URL为：http://<ESP8266_IP>/control?key=<key>
        requests.get(f'{ESP8266_IP}/control?key={key}')
    return '', 204

if __name__ == '__main__':
    app.run(host='0.0.0.0',port=5050,debug=True)




'''        
@app.route('/background.jpg')
def background_image():
    return send_from_directory(os.path.join(app.root_path, 'static'), 'background.jpg')

@app.route('/girl.jpg')
def girl_image():
    return send_from_directory(os.path.join(app.root_path, 'static'), 'girl.jpg')
'''