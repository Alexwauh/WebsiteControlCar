# WebsiteControlCar

使用Flask架构，上位机通过ESP8266，在同一IP下，局域网无线控制小车

## 系统框架

采用Flask架构，在本地局域网上传 index.html 使用者可以通过键盘上的 方向键，以及AWSD，发送GET请求给ESP8266，控制小车的运动，以及水平、垂直舵机的运动。

## 配件介绍
**1.无线控制麦克纳姆轮智能小车电机驱动板驱动器**

![expandBoard](https://github.com/Alexwauh/WebsiteControlCar/assets/170586618/bd43f2bc-6deb-4c52-8e0b-cf4c6d63e3a2)


**2.UNO R3开发板**

![UNOR3](https://github.com/Alexwauh/WebsiteControlCar/assets/170586618/7d2c55f3-9a4c-4f1a-acaf-f6a13dda2fb7)


**3.ESP8266NodeMCU CH340** 

![UNOR3](https://github.com/Alexwauh/WebsiteControlCar/assets/170586618/16796b91-a999-47c9-9fe8-05ecf5dbeafc)


**4.OLED SSD1306**

![OLED](https://github.com/Alexwauh/WebsiteControlCar/assets/170586618/e7e919e1-0286-4287-892c-94abb4616664)

**5.HC-SR04超声波模块CS100A**

![UNOR3](https://github.com/Alexwauh/WebsiteControlCar/assets/170586618/3f99a930-b14d-4f64-808f-311d68e27118)


**6.1:90蓝双轴减速电机**

![motor](https://github.com/Alexwauh/WebsiteControlCar/assets/170586618/49bcf916-c366-469f-9c2f-a936e663d7e0)



**7.麦克纳姆轮**

![wheel](https://github.com/Alexwauh/WebsiteControlCar/assets/170586618/15a06521-81a5-45ea-9e6e-053817d09470)

**8.舵机 MG996 180度/270度**

![servo](https://github.com/Alexwauh/WebsiteControlCar/assets/170586618/a44f846d-07a3-465a-a81f-5f43f12e61db)

**9.锂电池12V**

![battery](https://github.com/Alexwauh/WebsiteControlCar/assets/170586618/e2f67776-4124-4b16-8080-16b505a7d566)

## 项目说明
1.Arduino文件在使用时需要将ElChge中的 DFRobot_ASCllfont/DFRobot_SSD1306/DFRobot_URM10 文件放入下面路径：你的Arduino软件路径/libraries
**如果 QGPMakerMotorShield_V5.2 也放入，需要修改对应调用的工程文件的引用）**  
2.嘉立创文件和最后的连线图略有区别，正在更新  
3.本来打算做openmv的图传人脸识别，但是由于资金紧张，能力有限，目前只能做到通过JSON格式，ESP8266和openmv串口连接，通过Socket发送，速度太慢，`一张图要3-4秒`考试将至希望下次能完成

