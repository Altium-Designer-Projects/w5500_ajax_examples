#include "index.h"
#include <SPI.h>
#include <Ethernet.h>
/*
 Hello 
 I design developer tools for embedded electronic systems. You can buy my projects design files.
 https://www.altiumdesignerprojects.com
*/
#define ethernetCS    10

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

EthernetServer server(80);
String HTTP_req;            // stores the HTTP request
String convert_char = index_page; 
word counter = 0;

void setup(){
  Serial.begin(9600);
  Serial.println("Ethernet WebServer Example");
  Ethernet.init(ethernetCS); 
  Ethernet.begin(mac);

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
 // listen for incoming clients
 EthernetClient client = server.available();
  if(client){
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while(client.connected()){
      if(client.available()){
        char c = client.read();
        HTTP_req += c;
        //Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
            // AJAX request....
            if(HTTP_req.indexOf("request") > -1) {  // 192.168.2.50/request
               // send rest of HTTP header
               client.println("HTTP/1.1 200 OK");                        
               client.println("Content-Type: text/xml");
               client.println("Connection: keep-alive");
               client.println();
               // send XML file containing input states              
               XML_response(client);             
            }else{  // HTTP request for web page
               client.println(convert_char); 
            }            
            
            Serial.print(HTTP_req);
            HTTP_req = "";            // finished with request, empty string                    
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}

// send the XML file with switch statuses and analog value
void XML_response(EthernetClient cl){
  counter++;
  cl.println("<?xml version = \"1.0\" ?>");
  cl.println("<counter>");
  cl.println(String(counter));
  cl.println("</counter>");
}
