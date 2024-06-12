#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>


//#include <SPI.h>
//#include "FS.h"


//局域网信息
const char* SSID = "ztl";
const char* PASSWORD = "meiyoumima";

const char* server = "http://192.168.114.248:5000/post_data";  // Flask服务器IP地址
ESP8266WebServer servertoesp(80);

WiFiClient client;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);


  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected");
  Serial.print("IP ADDRESS:");
  Serial.println(WiFi.localIP());  // get ip address

  servertoesp.on("/control", handleControl);
  servertoesp.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // put your main code here, to run repeatedly:
  //servertoesp.handleClient();
  /*
  if (WiFi.status() == WL_CONNECTED) { // 检查是否连接到WiFi
    HTTPClient http;
    http.begin(client,server); // 指定服务器地址
    http.addHeader("Content-Type", "application/json"); // 添加HTTP头

    // 创建要发送的JSON数据
    String jsonData = "{\"sensor_value\": 12345}";

    // 发送HTTP POST请求
    int httpResponseCode = http.POST(jsonData);

    // 打印HTTP响应码
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    // 关闭连接
    http.end();
  } else {
    Serial.println("WiFi Disconnected");
  }
  delay(1000); // 每10秒发送一次数据
  */
  
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();  //去除可能存在的空格 要不要加command =?
    Serial.println(command);
  }


}




void handleControl() {
  if (servertoesp.hasArg("key")) {
    String key = servertoesp.arg("key");
    Serial.println(key);
  }
  servertoesp.send(204, "text/plain", "");
}
