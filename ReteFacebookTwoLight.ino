

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid = "NagRaj"; // change to your home wifi name
const char* password = "7060196036"; //  change to your home wifi password
const char* mqtt_server = "io.reteiot.com"; // MQTT broker Name 

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi() {

  delay(10);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
   
  }

  randomSeed(micros());

  
}

void callback(char* topic, byte* payload, unsigned int length) {
  
  if ((char)payload[0] == 'A' && (char)payload[1]== '1') {
      digitalWrite(D0, LOW);
   
  } 
  if ((char)payload[0] == 'A' && (char)payload[1]== '0') {
      digitalWrite(D0, HIGH);
   
  } 
  if ((char)payload[0] == 'B' && (char)payload[1]== '1') {
      digitalWrite(D1, LOW);
   
  } 
  if ((char)payload[0] == 'B' && (char)payload[1]== '0') {
      digitalWrite(D1, HIGH);
   
  } 
  
  
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
       digitalWrite(BUILTIN_LED, LOW);
      client.subscribe("nagendrachaudhary2016@gmail.com/******"); 
    } else {
     
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // on board led for mqtt status indication.
  pinMode(D0, OUTPUT); // lED
  pinMode(D1, OUTPUT); // lED
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  digitalWrite(BUILTIN_LED, HIGH);
  
}

void loop() {

  if (!client.connected()) {
     digitalWrite(BUILTIN_LED, HIGH);
    reconnect();
  }
  client.loop();

}
