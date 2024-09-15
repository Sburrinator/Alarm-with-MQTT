#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Keypad.h>

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns

char key_layout[ROW_NUM][COLUMN_NUM] = {
  {'1','4','7', '*'},
  {'2','5','8', '0'},
  {'3','6','9', '#'},
  {'A','B','C', 'D'}
};

byte pin_rows[ROW_NUM] = {D1, D2, D3, D4};      // The ESP8266 pins connect to the row pins
byte pin_column[COLUMN_NUM] = {D5, D6, D7, D8}; // The ESP8266 pins connect to the column pins

Keypad tastiera = Keypad( makeKeymap(key_layout), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

const char *ssid = "Your SSID";   // SSID WIFI
const char *password = "Your Password"; // PSW WIFI

const char *ID = "tastierino";  // device name
const char *TOPIC = "allarme/output";  // Topic subscribe
const char *TOPIC_PUB="allarme/tastierino"; // topic publish

IPAddress broker(192,168,1,219); // IP broker raspberry
WiFiClient wclient;

PubSubClient client(wclient); // Setup MQTT client

// Legge i messaggi dal broker, Subscribe nel topic room/light, Publish nel topic room/light/state per lo stato
void callback(char* topic, byte* payload, unsigned int length) {
  
  
}

// Connessione con la rete WiFi
void setup_wifi() {
  Serial.print("\nConnecting to ");
  Serial.println(ssid);
  WiFi.persistent(false);
  WiFi.begin(ssid, password); // Connect to network

  while (WiFi.status() != WL_CONNECTED) { // Loop fino a che non si connette
    delay(200);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// Reconnect to client
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if(client.connect(ID)) {
      Serial.println("connected");
      Serial.print("Publishing into: ");
      Serial.println(TOPIC_PUB);
      Serial.println('\n');
    } else {
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200); // Start serial communication at 115200 baud
  setup_wifi(); // Connect to network
  client.setServer(broker, 1883);
  client.setCallback(callback);// Initialize the callback routine


}
String codice="";

bool primaVolta=true;
bool stato=false;
void loop() {
  
  if (!client.connected())  // Reconnect if connection is lost
  {
    reconnect();
  }
  client.loop();            // loops the function
  String response;
  if(primaVolta){           //if it's the first time using the keypad it publishes "connesso" (to organize better the outputs on the raspberry console)
    client.publish(TOPIC_PUB, "connesso");
    primaVolta=!primaVolta;
  }
    
  char tasto = (char)tastiera.getKey();  //gets the key pressed
  if (tasto) {
    if (tasto == '#') {                  //"#" works like a send button
      if (codice == "1234") {            //1234 is the code that is set, if it's correct, it publishes on the topic the new state of the alarm
        Serial.println("Corretto");      //otherwise, if it's wrong, it doesnt do anything (you can set a buzzer or smth that make noise)
        codice = "";
        stato=!stato;
      } else {
        Serial.println("Sbagliato");
        codice = "";
      }
      if(stato){
        client.publish(TOPIC_PUB, "on");
        Serial.println("Pubblicato 'on'");
      }else{
        client.publish(TOPIC_PUB, "off");
        Serial.println("Pubblicato 'off'");
      }
    } else {                            //adds every input letter to the "codice" string 
      codice += tasto; 
      Serial.println(tasto);
    }
  }
}
