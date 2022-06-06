#include <WiFi.h>
#include <PubSubClient.h>

int buzzer = 19;
int green = 21;
int yellow = 22;
int red = 23;

const char* ssid = "Desktop_F4823364"; // variable that records the name of the wireless network
const char* password = "93889610";  // variable that records the passworld of the wireless network

WiFiServer server(80);

void setup()
{
    pinMode(buzzer, OUTPUT);  // set the Buzzer pin mode
    pinMode(green, OUTPUT);   // set the Green LED pin mode
    pinMode(yellow, OUTPUT);  // set the Yellow LED pin mode
    pinMode(red, OUTPUT);     // set the Red LED pin mode
    

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
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();

}

int value = 0;


void loop(){
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client
    Serial.println("New Client.");          // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character
          
          // if the current line is blank, you have two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Clica <a href=\"/H\">aqui</a>.<br>");
            client.print("Clica <a href=\"/L\">aqui</a>.<br>"); 
            // The HTTP response ends with another blank line:      
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you have a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you have anything else but a carriage return character
          currentLine += c;      // add it to the end of the currentLine
        }
        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(23, HIGH);                // GET /L turns the Red LED on
        }
        
        if (currentLine.endsWith("GET /H")) {
          while("GET /H" == "GET /H"){  // GET /H turns the LEDs on
            if (currentLine.endsWith("GET /L")){
              break;
            }
              digitalWrite(green, HIGH);  // turns the Green Led on
              digitalWrite(red, LOW);     // turns the Red Led off
              delay(5000);                // wait 5 seconds to execute next lines

              digitalWrite(yellow, HIGH); // turns the Yellow Led on
              digitalWrite(green, LOW);   // turns the Red Led on
              delay(2000);                // wait 2 seconds to execute next lines

              digitalWrite(red, HIGH);    // turns the Red Led on
              digitalWrite(yellow, LOW);  // turns the Yellow Led off
              if (red,HIGH){
                  //  warns that it will close
                  digitalWrite(buzzer,HIGH); // turns the buzzer on
                  delay(1000);  // wait 1 seconds to execute next lines
                  digitalWrite(buzzer,LOW); // turns the buzzer off
                  delay(5000);  // wait 5 seconds to execute next lines
                  //  warns that it will open
                  digitalWrite(buzzer,HIGH);  // turns the buzzer on
                  delay(300);       // wait 3 milliseconds to execute next lines
                  digitalWrite(buzzer,LOW); // turns the buzzer off
                  digitalWrite(red,LOW);  // turns the Red Led off
                  delay(100);    // wait 1 milliseconds to execute next lines
                  digitalWrite(buzzer,HIGH);  // turns the buzzer on
                  digitalWrite(red,HIGH); // turns the Red Led on
                  delay(300);   // wait 3 milliseconds to execute next lines
                  digitalWrite(buzzer,LOW); // turns the buzzer off
                  digitalWrite(red,LOW);  // turns the Red Led off
                  delay(100);   // wait 1 milliseconds to execute next lines
                  digitalWrite(buzzer,HIGH);  // turns the buzzer on
                  digitalWrite(red,HIGH); // turns the Red Led on
                  delay(300);   // wait 3 milliseconds to execute next lines
                  digitalWrite(buzzer,LOW); // turns the buzzer off
                  digitalWrite(red,LOW);  // turns the Red Led off
                  delay(100);   // wait 1 milliseconds to execute next lines
              }
              digitalWrite(red,HIGH); // turns the Red Led on
              delay(2000);  // wait 2 seconds to execute next lines
          }             
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
