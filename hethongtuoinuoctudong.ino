#include <ESP8266WiFi.h>
 
String apiKey = "IBCI6C27UPBELVKK";
const char* ssid = "SICT";
const char* password = "";
const char* server = "api.thingspeak.com";
 
int rainPin = A0;
int relay = 3;
int led1 = 4;
int led2 = 5;
WiFiClient client;
 
void setup() 
{
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
pinMode(relay, OUTPUT);
Serial.begin(9600);
 
WiFi.begin(ssid, password);
 
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
 
WiFi.begin(ssid, password);
 
while (WiFi.status() != WL_CONNECTED) 
{
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
 
}
 
void loop() 
{
 
int t = analogRead(rainPin);
  t = map(t,0,1023,0,100);
  
Serial.print("Mositure : ");
Serial.print(t);
Serial.println("%");
digitalWrite(relay, HIGH);
digitalWrite(led1, LOW);
digitalWrite(led2, HIGH);
if (t<90) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(relay, LOW);
    Serial.println("Ðộ ẩm đạt mức cho phép");
    delay(2000);
    Serial.println("ngừng tưới nước"); 
    }else{
       delay(1000);
       Serial.println("Bắt đầu tưới nước");
    }
if (client.connect(server,80)) {
String postStr = apiKey;
postStr +="&field1=";
postStr += String(t);
postStr += "\r\n\r\n";
 
client.print("POST /update HTTP/1.1\n");
client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
client.print("Content-Type: application/x-www-form-urlencoded\n");
client.print("Content-Length: ");
client.print(postStr.length());
client.print("\n\n");
client.print(postStr);


}
client.stop();
 
}
