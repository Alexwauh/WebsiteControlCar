# WebsiteControlCar

使用Flask架构，上位机通过ESP8266，在同一IP下，局域网无线控制小车

##系统框架

采用Flask架构，在本地局域网上传 index.html 使用者可以通过键盘上的 方向键，以及AWSD，发送GET请求给ESP8266，控制小车的运动，以及水平、垂直舵机的运动。

##配件介绍
1.无线控制麦克纳姆轮智能小车电机驱动板驱动器
![OLED](https://github.com/Alexwauh/WebsiteControlCar/assets/170586618/8f043f24-3569-4449-82e8-49e47d3364dc)

2.UNO R3开发板
![OLED](https://github.com/Alexwauh/WebsiteControlCar/assets/170586618/6d06cc60-0c65-45d4-9540-7aff1a760c83)

3.ESP8266NodeMCU CH340 
![OLED](https://github.com/Alexwauh/WebsiteControlCar/assets/170586618/476cc0aa-5125-4fb8-82a3-47eb08b60867)

4.OLED SSD1306
![OLED](https://github.com/Alexwauh/WebsiteControlCar/assets/170586618/e7e919e1-0286-4287-892c-94abb4616664)

5.HC-SR04超声波模块CS100A
![wheel](https://github.com/Alexwauh/WebsiteControlCar/assets/170586618/9d9eccde-2a5c-48a9-b8cd-f59ef6e50a11)

6.1:90蓝双轴减速电机
![wheel](https://github.com/Alexwauh/WebsiteControlCar/assets/170586618/4b2ecdf3-fec6-475b-85c0-188fa09e0eb3)

7.麦克纳姆轮
![wheel](https://github.com/Alexwauh/WebsiteControlCar/assets/170586618/15a06521-81a5-45ea-9e6e-053817d09470)

8.舵机 MG996 180度/270度
![servo](https://github.com/Alexwauh/WebsiteControlCar/assets/170586618/a44f846d-07a3-465a-a81f-5f43f12e61db)

9.锂电池12V
![battery](https://github.com/Alexwauh/WebsiteControlCar/assets/170586618/e2f67776-4124-4b16-8080-16b505a7d566)

##项目说明
1.Arduino文件在使用时需要将ElChge中的 DFRobot_ASCllfont/DFRobot_SSD1306/DFRobot_URM10 文件放入下面路径：你的Arduino软件路径/libraries****（如果 QGPMakerMotorShield_V5.2 也放入，需要修改对应调用的工程文件的引用）****

