#include <ArduinoHttpClient.h>
#include <WiFi.h>

//  client(server) ip and port
char server_address[] = "192.168.202.156";  // server address
int port = 5000;

//  wifi credintials
char ssid[] = "Myd";
char password[] = "UIUXUIUX";

WiFiClient wifi;
HttpClient client = HttpClient(wifi, server_address, port);
int status = WL_IDLE_STATUS;

void setup() {
//  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(10);
  }
//  Serial.println("IP address: ");
//  Serial.println(WiFi.localIP());
}

void loop() {
  Post();
  delay(10*1000);
}

//  HTTP POST function that sends key-value pair
void Post(){
  Serial.println("making POST request");
  String contentType = "application/x-www-form-urlencoded";
  String postData = "key=a&val=1";
  client.post("/esp", contentType, postData);

  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();
  
//
//  Serial.print("Status code: ");
//  Serial.println(statusCode);
//  Serial.print("Response: ");
//  Serial.println(response);
}
