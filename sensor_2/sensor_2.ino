#include "secret.h"
#include <WiFiClientSecure.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

const char* ssid = "zik";
const char* password = "12345678";
float t;
float h;

#define dht_pin 22      //to get dht data
#define dht_type DHT22
DHT dht(dht_pin, dht_type);
char msgdht[150];
long lastMsg = 0;

WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);

void connectAWS()
{
  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  client.setServer(AWS_IOT_ENDPOINT, 8883);
  client.setCallback(messageHandler);

  while (!client.connected()) {
    Serial.println("Connecting to AWS IoT… ");
    if (client.connect(THINGNAME)) {
      Serial.println("Connected");
      client.subscribe("esp32/test");
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}


void setup() {
  Serial.begin(9600);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  dht.begin();
}

void loop() {
  if (!client.connected()) {
  connectAWS();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 5000){
    lastMsg = now;

    h = dht.readHumidity();
    t = dht.readTemperature();

    String dht_data = "{\"device_id\":\"sensor_2\", \"temperature\":"+String(t)+", \"humidity\":"+String(h) +" }";
    Serial.println(dht_data);
    dht_data.toCharArray(msgdht, (dht_data.length() + 1 ));
    client.publish("esp32/data", msgdht);
  }
}

void messageHandler(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Incoming Msg: ");
  Serial.println(topic);
  String message;
  for (int i=0; i<length; i++){
    message = message + (char)payload[i];
  }
  Serial.println(message);
}



