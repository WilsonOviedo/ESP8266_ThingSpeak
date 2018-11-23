#include <ESP8266WiFi.h>

String apiKey = "xxxxxxx";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "xxxxx";     // replace with your wifi ssid and wpa2 key
const char *pass =  "xxxxxx";
const char* server = "api.thingspeak.com";

WiFiClient client;

void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println("Connecting to ");
  Serial.println(ssid);


  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");

}

void loop()
{
  if (client.connect(server, 80))  //   "184.106.153.149" or api.thingspeak.com
  {

    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(WiFi.RSSI());


    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);;
  }
  client.stop();

  Serial.println("Enviando...");

  delay(10000);
}
