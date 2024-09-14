#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define pinPIR D1       // Pin PIR
int statePIR  = LOW;     // Stato PIR

const char *ssid = "CasaDeiDuri24";   // SSID WIFI
const char *password = "Samuelduro"; // PSW WIFI
//#define BUZZER D7            // Pin buzzer

const char *ID = "sensoremovimento2";  // Nome device
const char *TOPIC = "allarme/output";  // Topic subscribe
const char *TOPIC_PUB="allarme/movimento1";
//const char *STATE_TOPIC = "hamza/culo/ciao";  // Topic publish

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
  pinMode(pinPIR, INPUT);
}


void loop() {
  
  if (!client.connected())  // Reconnect if connection is lost
  {
    reconnect();
  }
  client.loop();
  String response;

  int valPIR = digitalRead(pinPIR);
  if(valPIR==HIGH){
    if (statePIR == LOW) {
      Serial.println("Movimento rilevato!");
      client.publish(TOPIC_PUB, "rilevato");
      statePIR = HIGH;
    }
  }
  else{
    if (statePIR == HIGH) {
      Serial.println("Movimento terminato!"); 
      client.publish(TOPIC_PUB, "no");
      statePIR = LOW;
    }
  }
}