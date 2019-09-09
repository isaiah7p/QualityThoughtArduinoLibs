#include <SPI.h>
#include <Ethernet.h>
 
// MAC address from Ethernet shield sticker under board
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 200); // IP address, may need to change depending on network
EthernetServer server(80);  // create a server at port 80
 
String HTTP_req;          // stores the HTTP request
boolean LED_status = 0;   // state of LED, off by default
 
void setup()
{
    Ethernet.begin(mac, ip);  // initialize Ethernet device
    server.begin();           // start to listen for clients
    Serial.begin(9600);       // for diagnostics
    pinMode(2, OUTPUT);       // LED on pin 2
    pinMode(3, OUTPUT);       // LED on pin 3
    pinMode(4, OUTPUT);       // LED on pin 4
}
 
void loop()
{
    EthernetClient client = server.available();  // try to get client
 
    if (client) {  // got client?
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {   // client data available to read
                char c = client.read(); // read 1 byte (character) from client
                HTTP_req += c;  // save the HTTP request 1 char at a time
                // last line of client request is blank and ends with \n
                // respond to client only after last line received
                
                if (c == '\n' && currentLineIsBlank) {
                    // send a standard http response header
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connection: close");
                    client.println();
                    
                    // send web page
                    client.println("<!DOCTYPE html>");
                    client.println("<html>");
                    client.println("<head>");
                    client.println("<title>Arduino LED Control</title>");
                    client.println("<meta charset=\"utf-8\" />");
                    client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, minimum-scale=1\" />");
                    client.println("<link rel=\"stylesheet\" href=\"http://파일업로드경로/style.css\" />");
                    client.println("<script src=\"http://ajax.googleapis.com/ajax/libs/jquery/1.9.1/jquery.min.js\"></script>");
                    client.println("<script src=\"http://파일업로드경로/script.js\"></script>");                    
                    client.println("</head>");
                    client.println("<body></body></html>");
 
                    if (HTTP_req.indexOf("r=1") > -1) {
                      digitalWrite(2, HIGH);
                    }
                    if (HTTP_req.indexOf("r=0") > -1) {
                        digitalWrite(2, LOW);
                    }
                    if (HTTP_req.indexOf("g=1") > -1) {
                        digitalWrite(3, HIGH);
                    }
                    if (HTTP_req.indexOf("g=0") > -1) {
                        digitalWrite(3, LOW);
                    }
                    if (HTTP_req.indexOf("b=1") > -1) {
                        digitalWrite(4, HIGH);
                    }
                    if (HTTP_req.indexOf("b=0") > -1) {
                        digitalWrite(4, LOW);
                    }
                    Serial.print(HTTP_req);
                    HTTP_req = "";    // finished with request, empty string  
 
                    break;
                }
                
                // every line of text received from the client ends with \r\n
                if (c == '\n') {
                    // last character on line of received text
                    // starting new line with next character read
                    currentLineIsBlank = true;
                } 
                else if (c != '\r') {
                    // a text character was received from client
                    currentLineIsBlank = false;
                }
            } // end if (client.available())
        } // end while (client.connected())
        delay(1);      // give the web browser time to receive the data
        client.stop(); // close the connection
    } // end if (client)
}



