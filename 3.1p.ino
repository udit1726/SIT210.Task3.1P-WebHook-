#include <WiFiNINA.h>
#include <ThingSpeak.h> 
const int IRPin = 12;
char ssid[] = "Airtel_9811351651";     // WiFi SSID
char pass[] = "rangoarku1726";

unsigned long channelID = 2249485;         // My ThingSpeak Channel ID
const char *apiKey = "3VVLE2U0AVHYAA5B"; 
WiFiClient client;

void setup()
{
  Serial.begin(9600);
  connectWiFi();
  ThingSpeak.begin(client);
}

void loop()
{
  delay(1000);
  int Value = analogRead(IRPin);
  Serial.print("Analog Value: ");
  Serial.println(Value);

  if (!isnan(Value))
  {
    sendDataToThingSpeak(Value);
  }
  else
  {
    Serial.println("Failed to read from IR sensor ");
  }
  Serial.println("Delaying before next iteration...");
  delay(30000); 
}

 void connectWiFi() 
  {
    while (WiFi.status() != WL_CONNECTED) 
    {
      Serial.print("Connecting to WiFi...");
      WiFi.begin(ssid, pass);
      delay(1000);
    }
    Serial.println("Connected to WiFi");
  }

void sendDataToThingSpeak(int value) 
{
  ThingSpeak.setField(1, value);
  int httpCode = ThingSpeak.writeFields(channelID, apiKey);

  if (httpCode == 200) 
  {
    Serial.println("Data sent to ThingSpeak");
  } 
  else
  {
    Serial.println("Error sending data to ThingSpeak");
  }
}   
  
 