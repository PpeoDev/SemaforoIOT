#include <WiFi.h>
#include <PubSubClient.h>

int buzzer = 19;
int green = 21;
int yellow = 22;
int red = 23;

const char* ssid     = "Desktop_F4823364";
const char* password = "93889610";
const char* mqtt_server = "broken.hivemq.com";

WiFiServer server(80);

void setup()
{
    pinMode(buzzer, OUTPUT);
    pinMode(green, OUTPUT);
    pinMode(yellow, OUTPUT);
    pinMode(red, OUTPUT);
    
    Serial.begin(115200);
    pinMode(23, OUTPUT);      // set the LED pin mode

    delay(10);

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
 WiFiClient client = server.available();   

  if (client) {                             
    Serial.println("New Client.");           
    String currentLine = "";                
    while (client.connected()) {            
      if (client.available()) {             
        char c = client.read();             
        Serial.write(c);                   
        if (c == '\n') {                    

          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            
            client.print("Clica <a href=\"/H\">aqui</a>.<br>");
            client.print("Clica <a href=\"/L\">aqui</a>.<br>");       
            client.println();
            
            break;
          } else {    
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;      
        }

        if (currentLine.endsWith("GET /L")) {
          digitalWrite(23, HIGH);                
        }
        
        if (currentLine.endsWith("GET /H")) {
          while("GET /H" == "GET /H"){
            if (currentLine.endsWith("GET /L")){
              break;
            }
              digitalWrite(green, HIGH);
              digitalWrite(red, LOW);
              delay(5000);

              digitalWrite(yellow, HIGH);
              digitalWrite(green, LOW);
              delay(2000);

              digitalWrite(red, HIGH);
              digitalWrite(yellow, LOW);
              if (red,HIGH){
                  digitalWrite(buzzer,HIGH);
                  delay(1000);
                  digitalWrite(buzzer,LOW);
                  delay(5000);
                  digitalWrite(buzzer,HIGH);
                  delay(300);       //Sinalizando que vai abrir
                  digitalWrite(buzzer,LOW);
                  digitalWrite(red,LOW);
                  delay(100);
                  digitalWrite(buzzer,HIGH);
                  digitalWrite(red,HIGH);
                  delay(300);
                  digitalWrite(buzzer,LOW);
                  digitalWrite(red,LOW);
                  delay(100);
                  digitalWrite(buzzer,HIGH);
                  digitalWrite(red,HIGH);
                  delay(300);
                  digitalWrite(buzzer,LOW);
                  digitalWrite(red,LOW);
                  delay(100);
              }
              digitalWrite(red,HIGH);
              delay(2000);  
          }             
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
