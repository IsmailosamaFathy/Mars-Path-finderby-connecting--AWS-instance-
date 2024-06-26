/**
 * ESP32 AWS Library
 * 
 * Functions to get the crawler coordinates from the Camera over AWS IoT
 * 
 * Authors: Vipul Deshpande, Jaime Burbano
 */


/*
  Copyright 2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.
  Permission is hereby granted, free of charge, to any person obtaining a copy of this
  software and associated documentation files (the "Software"), to deal in the Software
  without restriction, including without limitation the rights to use, copy, modify,
  merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
  permit persons to whom the Software is furnished to do so.
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "secrets.h"
#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"
#include "AWS.h"

/* The MQTT topics that this device should publish/subscribe to */
#define AWS_IOT_PUBLISH_TOPIC   "esp32/pub" 
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/target"

int roverCoords[2];
int rx, ry, ra;
int tx, ty;


WiFiClientSecure net = WiFiClientSecure();
MQTTClient client = MQTTClient(256);


myawsclass::myawsclass() {

}


void messageHandler(String &topic, String &payload) {
  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  const char* message = doc["message"];
  if (topic.equals("esp32/rover")) {
    //Serial.println("Received rover coordinates: " + payload);
    // Parse payload to extract rover coordinates
    StaticJsonDocument<200> roverDoc;
    deserializeJson(roverDoc, payload);
    const char* roverString = roverDoc["rover"];  // Extract the rover string
    int firstParenthesis = strchr(roverString, '(') - roverString;  // Find the index of the first '('
    int secondParenthesis = strchr(roverString + firstParenthesis + 1, ')') - roverString;  // Find the index of the second '('
    char coordinateString[30];
    strncpy(coordinateString, roverString + firstParenthesis + 1, secondParenthesis - firstParenthesis - 1);  // Extract the coordinates substring
    
    coordinateString[secondParenthesis - firstParenthesis - 1] = '\0';  // Null-terminate the string
    
    sscanf(coordinateString, "%d, %d", &rx, &ry);  // Extract the x and y coordinates
    sscanf(roverString + secondParenthesis + 2, "%d", &ra);

    // Serial.print("Extracted rover coordinates: [");
    // Serial.print(x);
    // Serial.print(", ");
    // Serial.print(y);
    // Serial.println("]");
  }

  else if (topic.equals("esp32/target")) {
    //Serial.println("Received rover coordinates: " + payload);
    // Parse payload to extract rover coordinates
    StaticJsonDocument<200> roverDoc;
    deserializeJson(roverDoc, payload);
    const char* roverString = roverDoc["target"];  // Extract the rover string
    int firstParenthesis = strchr(roverString, '(') - roverString;  // Find the index of the first '('
    int secondParenthesis = strchr(roverString + firstParenthesis + 1, ')') - roverString;  // Find the index of the second '('
    char coordinateString[30];
    strncpy(coordinateString, roverString + firstParenthesis + 1, secondParenthesis - firstParenthesis - 1);  // Extract the coordinates substring
    
    coordinateString[secondParenthesis - firstParenthesis - 1] = '\0';  // Null-terminate the string
    
    sscanf(coordinateString, "%d, %d", &tx, &ty);  // Extract the x and y coordinates

    // Serial.print("Extracted rover coordinates: [");
    // Serial.print(x);
    // Serial.print(", ");
    // Serial.print(y);
    // Serial.println("]");
  }
}


void myawsclass::stayConnected() {
  // client.loop();
  if (!client.connected()) {
    Serial.println("Disconnected from AWS IoT. Reconnecting...");
    connectAWS(); // Attempt to reconnect
  }
  client.loop();
}

void myawsclass::connectAWS() {

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print("Connecting...!");
  }

  Serial.print("CONNECTED...!\n");

  /* Configure WiFiClientSecure to use the AWS IoT device credentials */
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  /* Connect to the MQTT broker on the AWS endpoint we defined earlier */
  client.begin(AWS_IOT_ENDPOINT, 8883, net);

  /* Create a message handler */
  client.onMessage(messageHandler);

  Serial.print("Connecting to AWS IOT");

  while (!client.connect(THINGNAME)) {
    Serial.print(".");
    delay(100);
  }

  if(!client.connected())
  {
    Serial.println("AWS IoT Timeout!");
    return;
  }

  /* Subscribe to a topic */
  // client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
  client.subscribe("esp32/target");
  // client.subscribe("esp32/pub");
  client.subscribe("esp32/rover");

  Serial.println("AWS IoT Connected!");
}

void myawsclass::publishMessage(int16_t sensorValue) {

  StaticJsonDocument<200> doc;
  //doc["time"] = millis();
  doc["sensor"] = sensorValue;
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); /* print to client */

  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

myawsclass awsobject = myawsclass();  /* creating an object of class aws */


