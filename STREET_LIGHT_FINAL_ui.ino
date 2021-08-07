
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "AndroidAP33F5";
const char* password = "princess";
WiFiServer server(80);
int LED1 = D0;
int LED2 = D2;
int LED3 = D3;

void setup(void) {
  // put your setup code here, to run once:

pinMode(A0,INPUT);
pinMode(D0,OUTPUT);
pinMode(D2,OUTPUT);
pinMode(D3,OUTPUT);
Serial.begin(115200);
  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.begin();
  Serial.println("Web server started!");
}

void loop(void) {
  // put your main code here, to run repeatedly:
// Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
int value = analogRead(A0);
//float value1 = value * (5.0 / 1023);
client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><meta http-equiv=\"refresh\" content=\"5\">");
  client.println("<link rel=\"icon\" href=\"data:,\">");
  //css
  client.println("<style>html {font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
  client.println("text-decoration: none; font-size: 20px; margin: 4px; cursor: pointer;}</style></head>");
  // Web Page Heading
  client.println("<body><h1><b>Serole Smart Street lighting system</b></h1></body>");
if(value <= 110 )
{
   client.println("<style>html { background-color: #59594F;}");
   client.println("text-decoration: none; font-size: 20px; margin: 4px; cursor: pointer;}</style></head>");
  // Web Page Heading
  client.println("<body><h1><b>Its dark, Street Lights are ON</b></h1></body>");
  client.println("");
  client.println("<h3>Lane1 Street Lights are ON</h3><BR><BR>");
  client.println("<h3>Lane2 Street Lights are ON</h3><BR><BR>");
  client.println("<h3>Lane3 Street Lights are ON</h3><BR><BR>");
  client.println("<h3>Lane4 Street Lights are ON</h3><BR><BR>");
  digitalWrite(LED1,HIGH);
  digitalWrite(LED2,HIGH);
  digitalWrite(LED3,HIGH);
  Serial.println("street light is on");
  Serial.println(value);
  //Serial.println(value1);
   
}

else 
{
   client.println("<style>html { background-color: #F9F9E9;}");
   client.println("text-decoration: none; font-size: 20px; margin: 4px; cursor: pointer;}</style></head>");
  // Web Page Heading
  client.println("<body><h1><b>Its morning!, Street Lights are OFF</b></h1></body>");
  client.println("<h3>Lane1 Street Lights are OFF</h3><BR><BR>");
  client.println("<h3>Lane2 Street Lights are OFF</h3><BR><BR>");
  client.println("<h3>Lane3 Street Lights are OFF</h3><BR><BR>");
  client.println("<h3>Lane4 Street Lights are OFF</h3><BR><BR>");
  client.println("");
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
  Serial.println("street light is off");
   Serial.println(value);
//   Serial.println(value1);
//   delay(value1);    
   client.println("</html>");
 

}


}
