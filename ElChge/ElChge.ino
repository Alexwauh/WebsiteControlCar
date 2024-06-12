#include <Wire.h>
#include <SoftwareSerial.h>
#include "QGPMakerMotorShield_V5.2\QGPMakerMotorShield_Lib_V5.2\QGPMaker_MotorShield.cpp"
#include "QGPMakerMotorShield_V5.2\QGPMakerMotorShield_Lib_V5.2\Adafruit_MS_PWMServoDriver.cpp"
#include "DFRobot_URM10\DFRobot_URM10.cpp"
#include <DFRobot_SSD1306_I2C.h>
// 创建对象
DFRobot_URM10 urm10;
DFRobot_SSD1306_I2C oled12864;

QGPMaker_MotorShield  ElChgecar = QGPMaker_MotorShield();   //创建一个ElChgecar名的类，控制电机
// 电机驱动
QGPMaker_DCMotor      *DCMotor_rightback = ElChgecar.getMotor(2);    //右后轮
QGPMaker_DCMotor      *DCMotor_leftback = ElChgecar.getMotor(1);   //左后轮
QGPMaker_DCMotor      *DCMotor_rightfront = ElChgecar.getMotor(3); //右前轮
QGPMaker_DCMotor      *DCMotor_leftfront = ElChgecar.getMotor(4);  //左前轮

// 舵机驱动
QGPMaker_Servo  *Servo_vertical = ElChgecar.getServo(7);   //控制垂直倾角
QGPMaker_Servo  *Servo_horizon = ElChgecar.getServo(6);    //控制水平倾角

//int t = 10;
SoftwareSerial openmv_serial(10,11); // RX,TX

void motor(int how){
  switch(how){
    case 1:{ //前进
      DCMotor_leftback->setSpeed(100);
	    DCMotor_leftback->run(FORWARD);

      DCMotor_rightback->setSpeed(100);
	    DCMotor_rightback->run(FORWARD);

      DCMotor_leftfront->setSpeed(100);
	    DCMotor_leftfront->run(FORWARD);

      DCMotor_rightfront->setSpeed(100);
	    DCMotor_rightfront->run(FORWARD);
      break;
    }
    case 2:{ //后退
      DCMotor_leftback->setSpeed(100);
	    DCMotor_leftback->run(BACKWARD);

      DCMotor_rightback->setSpeed(100);
	    DCMotor_rightback->run(BACKWARD);

      DCMotor_leftfront->setSpeed(100);
	    DCMotor_leftfront->run(BACKWARD);

      DCMotor_rightfront->setSpeed(100);
	    DCMotor_rightfront->run(BACKWARD);
      
      break;
    }
    case 3:{ //左转
      DCMotor_leftback->setSpeed(100);
	    DCMotor_leftback->run(FORWARD);

      DCMotor_rightback->setSpeed(100);
	    DCMotor_rightback->run(BACKWARD);

      DCMotor_leftfront->setSpeed(100);
	    DCMotor_leftfront->run(BACKWARD);

      DCMotor_rightfront->setSpeed(100);
	    DCMotor_rightfront->run(FORWARD);
      break;
    }
    case 4:{ //右转
      DCMotor_leftback->setSpeed(100);
	    DCMotor_leftback->run(BACKWARD);

      DCMotor_rightback->setSpeed(100);
	    DCMotor_rightback->run(FORWARD);

      DCMotor_leftfront->setSpeed(100);
	    DCMotor_leftfront->run(FORWARD);

      DCMotor_rightfront->setSpeed(100);
	    DCMotor_rightfront->run(BACKWARD);
      break;
    }
    case 5:{ //停止
      DCMotor_leftback->setSpeed(0);
	    DCMotor_leftback->run(RELEASE);

      DCMotor_rightback->setSpeed(0);
	    DCMotor_rightback->run(RELEASE);

      DCMotor_leftfront->setSpeed(0);
	    DCMotor_leftfront->run(RELEASE);

      DCMotor_rightfront->setSpeed(0);
	    DCMotor_rightfront->run(RELEASE);
      break;
    }

  }
}//小车 1前进 2后退 3左转 4右转 5停止
void CheckArrow_motor(String command){
  if (command.startsWith("Arrow")){ //判断命令是否以Arrow 开头，如果是说明是控制小车的运动
    if(command == "ArrowUp"){
      motor(1);
    }//前进
    else if(command == "ArrowDown"){
      motor(2);
    }//后退
    else if(command == "ArrowLeft"){
      motor(3);
    }//左转
    else if(command == "ArrowRight"){
      motor(4);
    }//右转
    else if(command == "ArrowZero"){
      motor(5);
    }//停止
  }
}//判断小车是否运动，驱动小车
void UpdateServo(String input){
  //字符串传递格式 vertical: verticalValue horizon: horizonValue(传递到uno板上的字符串)
  int SERVO;
  if(input.startsWith("Horizon")){
    SERVO = Servo_horizon->readDegrees();
    if(input == "HorizonA"){//向右
      if(SERVO<10){
        SERVO = 0;
      }
      else{
        SERVO = SERVO - 10;
      }
      Servo_horizon->writeServo(SERVO);
    }
    else{//向左
      if(SERVO>170){
        SERVO = 180;
      }
      else{
        SERVO = SERVO + 10;
      }
      Servo_horizon->writeServo(SERVO);
    }
    Serial.println(SERVO);
  }
  else if(input.startsWith("Vertical")){
    SERVO = Servo_vertical->readDegrees();
    if(input == "VerticalL"){//向下
      if(SERVO<10){
        SERVO = 0;
      }
      else{
        SERVO = SERVO - 10;
      }
      Servo_vertical->writeServo(SERVO);
    }
    else{//向上
      if(SERVO>170){
        SERVO = 180;
      }
      else{
        SERVO = SERVO + 10;
      }
      Servo_vertical->writeServo(SERVO);
    }
    
  }
  
}//更新舵机值

void getOpenmv_coordinate(String input){
  // openmv的摄像头图片为240*320，将舵机控制到+-10即可
  if(input.startsWith("Openmv")){
    //Serial.println(input);
    int width_turn = input.indexOf("Openmv") + 6;
    int height_turn = input.indexOf(",") + 1;
    int width = input.substring(width_turn,input.indexOf(",")-1).toInt();
    int height = input.substring(height_turn).toInt();

    // 判断并计算舵机和中心点差值
    if(width>10){
      Serial.print("left ");
    }
    else if(width<-10){
      Serial.print("right ");
    }

    if(height>10){
      Serial.println("down");
    }
    else if(height<-10){
      Serial.println("up");
    }

  }
}

void setup() {
  // put your setup code here, to run once:
  ElChgecar.begin(50); //电机初始化
	Serial.begin(115200);
  Servo_vertical->writeServo(90);
  oled12864.begin(0x3c);
	oled12864.fillScreen(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    String command = Serial.readStringUntil('\n');
    command.trim(); //去除可能存在的空格 要不要加command =?
    
    CheckArrow_motor(command);
    UpdateServo(command);

    }//如果有信号
      //和ESP8266通信
  oled12864.setCursorLine(1);
	oled12864.printLine((urm10.getDistanceCM(A0, A1)));
  
}
