#include <ArduinoHttpClient.h>
#include <WiFi.h>

#include "DHT.h"
#define DHTPIN 22    // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

char ssid[] = "zozo";
char password[] = "1234567890";

char serverAddress[] = "10.42.0.1";  // server address
int port = 8000;

WiFiClient wifi;
HttpClient client = HttpClient(wifi, serverAddress, port);
int status = WL_IDLE_STATUS;

String tempKey = "temperature_table2";
String humKey = "humidity_table2";
String secret = "IT2021";

void setup()
{
    Serial.begin(115200);
    dht.begin();
    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

int value = 0;

void loop()
{
  int t = dht.readTemperature();
  int h = dht.readHumidity();
  String tempVal =  String(t,DEC);
  String humVal =  String(h,DEC); 
  Post(tempKey, tempVal);
  Post(humKey, humVal);
  
  delay(5000); 
}

void Post(String key, String val){
  Serial.println("making POST request");
  String contentType = "application/x-www-form-urlencoded";
  String postData = "key="+key+"&val="+val+"&secret="+secret;
  client.post("/api/v1/", contentType, postData);

  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);

  Serial.println("Wait five seconds");  
}
