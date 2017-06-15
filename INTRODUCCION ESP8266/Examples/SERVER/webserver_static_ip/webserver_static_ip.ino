#include <ESP8266WiFi.h>            
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

//http://192.168.1.1/?t=a&b=c

IPAddress ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

const char* ssid     = "AMyAP";
const char* password = "workshop";

MDNSResponder mdns;

ESP8266WebServer server(80);   //Web server object. Will be listening in port 80 (default for HTTP)

void handleGenericArgs() ;
void handleNotFound();

void setup() {

Serial.begin(115200);
delay(10);

WiFi.mode(WIFI_AP);
WiFi.softAPConfig(ip, gateway, subnet);
WiFi.softAP(ssid,password);

Serial.print("IP address: ");
Serial.println(WiFi.softAPIP());  //Print the local IP to access the server


  if (mdns.begin("esp8266",ip)) {
    Serial.println("MDNS responder started");
  } 

server.on("/", [](){server.send ( 200, "text/plain", "this works as well" );});
server.on("/test", handleGenericArgs); //Associate the handler function to the path
server.onNotFound(handleNotFound);


server.begin();                                       //Start the server
Serial.println("Server listening");   

MDNS.addService("http","tcp",80);

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

void handleNotFound(){
  /*String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }*/
  server.send(404, "text/plain", message);
}

