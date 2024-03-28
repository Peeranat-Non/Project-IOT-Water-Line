#include <ESP8266WiFi.h>
#include <TridentTD_LineNotify.h>

// ################# What you need to modify #########################

// Your WiFi credentials.
const char *ssid = "Peeranat";
const char *pass = "peeranat43109";

// Your Line notify token
#define LINE_TOKEN "vKdJzJyltgOXDC68pgKmgOSw5Xo7xevGdktbxRVcc1r"

const int sensor_pin = A0;  /* Connect Soil moisture analog sensor pin to A0 of NodeMCU */
int count = 0;
int D = 0;

void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    // ทำการ Print "Connectiong..." ทุก 1000ms
    Serial.println("Connecting...  ");
    Serial.printf("Connection Status: %d\n", WiFi.status());
    delay(1000);
  }

  Serial.print("Wi-Fi connected.");
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());

  // กำหนด Line Token
  LINE.setToken(LINE_TOKEN);

  // Welcome message
  LINE.notify("เครื่องแจ้งเตือนระดับน้ำท่วมเชื่อมต่อ WiFi แล้ว");

}

void loop() {
  float moisture_percentage;
  String msg;
  
  moisture_percentage = ( 100.00 - ( (analogRead(sensor_pin)/1023.00) * 100.00 ) );

  Serial.print("Soil Moisture(in Percentage) = ");
  Serial.print(moisture_percentage);
  Serial.println("%");
  Serial.print(D);
  
  if ( moisture_percentage >= 20 && moisture_percentage <= 29 && count == 0 ){
      msg = "ระดับน้ำอยู่ในระดับ : Low " + String() + "\r\n" +
      "สูงจากพื้น 10 cm " + "ความชื้น : " + String(moisture_percentage) + " %" ;

      D == 1;
      D++;
      count == 1;
      LINE.notify(msg);
  }
  else
  {
    if ( moisture_percentage < 20 && D > 0){
      msg = "ระดับน้ำลดลงต่ำกว่า 10 cm แล้ว ";

      D = 0;
      LINE.notify(msg);
    }
  }
  if ( moisture_percentage >= 30 && moisture_percentage <= 39 && count == 0){
      msg = "ระดับน้ำอยู่ในระดับ : Mid " + String() + "\r\n" +
      "สูงจากพื้น 20 cm " + "ความชื้น : " + String(moisture_percentage) + " %" ;
      
      count == 1;
      LINE.notify(msg);
  }
  if ( moisture_percentage >= 40 && count == 0){
      msg = "ระดับน้ำอยู่ในระดับ : High! " + String() + "\r\n" +
      "สูงจากพื้น 30 cm " + "ความชื้น : " + String(moisture_percentage) + " %" ;
      
      count == 1;
      LINE.notify(msg);
  } 
  if ( count < 10 ){
      count++;
  }else{
    count = 0;
  }

  delay(1000);
  
}