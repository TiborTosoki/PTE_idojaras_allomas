#include <ESP8266WiFi.h>

String apiKey = "7BQQWGBM6PQNEGJO";
const char *ssid =  "Tosoki";
const char *pass =  "";
const char* server = "api.thingspeak.com";
WiFiClient client;

float temperature, windDirection,  windSpeed, solarIrradiance;

String weatherDatas = "";
String subString;
int div1, div2, div3;

void setup() {
  Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
    //delay(10);
    weatherDatas = Serial.readString();
    div1 = weatherDatas.indexOf(';');
    temperature = (weatherDatas.substring(0, div1)).toFloat();
    div2 = weatherDatas.indexOf(';', div1 + 1);
    windDirection = (weatherDatas.substring(div1 + 1, div2 + 1)).toFloat();
    div3 = weatherDatas.indexOf(';', div2 + 1);
    windSpeed = (weatherDatas.substring(div2 + 1, div3 + 1)).toFloat();
    solarIrradiance = (weatherDatas.substring(div3 + 1)).toFloat();
    uploadDataToWeb();
    ESP.deepSleep(0);
  }

  if ( millis() > 15000) {
    Serial.println("Timeout, going to sleep.");
    ESP.deepSleep(0);
  }


}


void uploadDataToWeb() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, pass);
  }

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");

    if (millis() > 20000) {
      ESP.deepSleep(0);
      Serial.println("Can't connect, go to sleep.");
    }
  }

  if (client.connect(server, 80)) {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(temperature);
    postStr += "&field2=";
    postStr += String(windDirection);
    postStr += "&field3=";
    postStr += String(windSpeed);
    postStr += "&field4=";
    postStr += String(solarIrradiance);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
  }
  client.stop();
}
