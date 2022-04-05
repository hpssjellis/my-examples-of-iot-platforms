/*
// This example uses an Arduino/Genuino Zero together with
// a WiFi101 Shield or a MKR1000 to connect to shiftr.io.
//
// IMPORTANT: This example uses the new WiFi101 library.
//
// IMPORTANT: You need to install/update the SSL certificates first:
// https://github.com/arduino-libraries/WiFi101-FirmwareUpdater#to-update-ssl-certificates
//
// You can check on your device after a successful
// connection here: https://www.shiftr.io/try.
//
// by Gilberto Conti
// https://github.com/256dpi/arduino-mqtt
*/

#include <Arduino.h> // Only needed by https://platformio.org/
#include "WiFi.h"
#include "WiFiSSLClient.h"

#include <MQTT.h>


//#include "arduino_secrets.h"   // more safe
#define SECRET_SSID "yourSSID"
#define SECRET_PASS "yourPASS"

int status = WL_IDLE_STATUS;


char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;        // your network password (use for WPA, or use as key for WEP)

WiFiSSLClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void connect() {
  Serial.print("checking wifi...");
  while (status != WL_CONNECTED) {
    Serial.println(".");
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(3000);
  }

  Serial.print("\nconnecting...");
                         // clientID (a random unique number), username, activeKey
  while (!client.connect("arduino89245897", "yourUser", "aio_yourActiveKeydfghddfghdfgfgth")) {
    Serial.print(".");
    delay(3000);
  }

  Serial.println("\nconnected!");

  client.subscribe("/jerteach/feeds/led1");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);

  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.
}

void setup() {
  
  Serial.begin(115200);
  //while (!Serial) {} // wait for serial port to connect. I DON'T LIKE WAITING
 
   pinMode(LED_BUILTIN, OUTPUT);      
  pinMode(LEDB, OUTPUT);   
  digitalWrite(LEDB, LOW);  
  delay(5000);
  Serial.println("Wait a bit to connect serial monitor");
  digitalWrite(LEDB, HIGH);  
  delay(5000);
  Serial.println("Wait a bit");
  digitalWrite(LEDB, LOW);  
  delay(5000);
  Serial.println("Wait a bit");
  
  
  digitalWrite(LEDB, LOW);          // blue on while connecting
  digitalWrite(LED_BUILTIN, HIGH);          

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }
  //
  // MQTT brokers usually use port 8883 for secure connections.
  client.begin("io.adafruit.com", 8883, net);
  client.onMessage(messageReceived);

  connect();
}

void loop() {
  client.loop();

  if (!client.connected()) {
    connect();
  }

  // publish a message roughly every 12 seconds.
  if (millis() - lastMillis > 12000) {
    lastMillis = millis();
    client.publish("/jerteach/feeds/led1", "333");
  }
}
