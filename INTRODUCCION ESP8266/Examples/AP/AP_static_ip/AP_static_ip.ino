#include <ESP8266WiFi.h>            
#include <ESP8266WebServer.h>

IPAddress ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);


/*
  Serial.begin(115200);
  Serial1.begin(19200);
  WiFi.mode(WIFI_AP_STA);  //need both to serve the webpage and take commands via tcp
  IPAddress ip(1,2,3,4);
  IPAddress gateway(1,2,3,1); 
  IPAddress subnet(255,255,255,0); 
  WiFi.softAPConfig(ip, gateway, subnet);
  WiFi.softAP("ESPname1"); //Access point is open

  delay(1000);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP); - See more at: http://www.esp8266.com/viewtopic.php?f=29&t=12124#sthash.8qKZUFEx.dpuf
 */

ESP8266WebServer server(80);   //Web server object. Will be listening in port 80 (default for HTTP)

void handleGenericArgs() ;

void setup() {

Serial.begin(115200);

WiFi.mode(WIFI_AP);
WiFi.softAPConfig(ip, gateway, subnet);
WiFi.softAP("ESP8266AP","todobi77");

Serial.print("IP address: ");
Serial.println(WiFi.softAPIP());  //Print the local IP to access the server

server.on("/", handleGenericArgs); //Associate the handler function to the path
//server.on("/query", handleSpecificArg);   //Associate the handler function to the path

server.begin();                                       //Start the server
Serial.println("Server listening");   

}

void loop() {

server.handleClient();    //Handling of incoming requests

}


void handleGenericArgs() { //Handler

String message = "Number of args received:";
message += server.args();            //Get number of parameters
message += "\n";                            //Add a new line

for (int i = 0; i < server.args(); i++) {

  message += "Arg " + (String)i + " -> ";   //Include the current iteration value
  message += server.argName(i) + ": ";     //Get the name of the parameter
  message += server.arg(i) + "\n";              //Get the value of the parameter

} 

server.send(200, "text/plain", message);       //Response to the HTTP request

}

