from PIL import Image
import os
import cv2

def resizesize_image(input_path, output_path, size):
    """
    从指定路径获取图片,将图片修改成对应大小并保存到给定路径,以JPG格式。

    参数：
    input_path: str - 输入图片的路径
    output_path: str - 保存修改后图片的路径
    size: tuple - 新图片的大小，例如(800, 600)
    """
    try:
        # 打开输入图片
        img = Image.open(input_path)
        
        # 调整图片大小
        img = img.resize(size, Image.Resampling.LANCZOS)
        
        # 确保输出路径的文件夹存在
        os.makedirs(os.path.dirname(output_path), exist_ok=True)
        
        # 保存图片为JPG格式
        img.save(output_path, 'JPEG')
        print(f"Image saved to {output_path}")
        
    except Exception as e:
        print(f"Error: {e}")

def resizeDrawRectangle_image(input_path,output_path):
    # 加载人脸检测器
    face_cascade = cv2.CascadeClassifier('C:/Users/86180/AppData/Local/Packages/PythonSoftwareFoundation.Python.3.12_qbz5n2kfra8p0/LocalCache/local-packages/Python312/site-packages/cv2/data/haarcascade_frontalface_alt2.xml')
    # 读取图片
    image = cv2.imread(input_path)

    # 将图片转换为灰度图像
    gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # 在灰度图像中检测人脸
    faces = face_cascade.detectMultiScale(gray_image, scaleFactor=1.01, minNeighbors=5, minSize=(100, 100))

    # 遍历检测到的人脸，画出红色矩形
    for (x, y, w, h) in faces:
        cv2.rectangle(image, (x, y), (x+w, y+h), (0, 0, 255), 4)

    # 保存结果图片
    cv2.imwrite(output_path, image)

    

# 示例使用
'''
input_path = 'static\current_frame.jpg'  # 替换为实际输入图片路径
output_path = 'static\current_frame_revised.jpg'  # 替换为实际输出图片路径
size = (600, 300)  # 替换为你需要的大小

resizesize_image(input_path, output_path, size)
'''
#resizeDrawRectangle_image('static\current_frame.jpg','static\current_frame_draw.jpg')