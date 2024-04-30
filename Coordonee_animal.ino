/*
  Lora Send And Receive
*/
// GROUPE : Manon, Maxim, Alexandre, Martin
#include <MKRWAN.h>
 
LoRaModem modem;
 
// Please enter your data
String appEui = "a8610a3231327d05";
String appKey = "03030303030303030303030303030303";
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial);
  // change this to your regional band (eg. US915, AS923, ...)
  if (!modem.begin(EU868)) {
    Serial.println("Failed to start module");
    while (1) {}
  };
  Serial.print("Your module version is: ");
  Serial.println(modem.version());
  Serial.print("Your device EUI is: ");
  Serial.println(modem.deviceEUI());
 
  int connected = modem.joinOTAA(appEui, appKey);
  if (!connected) {
    Serial.println("Something went wrong...");
    while (1) {}
  }
 
  // Set poll interval to 60 secs.
  modem.minPollInterval(60);
}
 
void loop() {
  // Serial.println();
  // Serial.println("Enter a message to send to network");
  // Serial.println("(make sure that end-of-line 'NL' is enabled)");
 
  //while (!Serial.available());
  //String msg = Serial.readStringUntil('\n');
  // Serial.println();
 
 
  int x = random(-200,200);//coordonnée de x entre -200 et 200
  int y = random(-200,200);//coordonnée dde y entre -200 et 200
  String msg = "Koba:"+String(x)+String(y);
  Serial.print("Sending: " + msg + " - ");
  for (unsigned int i = 0; i < msg.length(); i++) {
    Serial.print(msg[i] >> 4, HEX);
    Serial.print(msg[i] & 0xF, HEX);
    Serial.print(" ");
  }
  Serial.println();
 
  int err;
  modem.beginPacket();//moment ou on envoie le message sur le réseau
  modem.print(msg);
  err = modem.endPacket(true);
  if (err > 0) {
    Serial.println("Message sent correctly");
  } else {
    Serial.println("Error sending message :(");
    Serial.println("(you may send a limited amount of messages per minute, depending on the signal strength");
    Serial.println("it may vary from 1 message every couple of seconds to 1 message every minute)");
  }
  delay(1000);
  if (!modem.available()) {
    Serial.println("No downlink message received at this time.");
    return;
  }
  char rcv[64];
  int i = 0;
  while (modem.available()) {
    rcv[i++] = (char)modem.read();
  }
  Serial.print("Received: ");
  for (unsigned int j = 0; j < i; j++) {
    Serial.print(rcv[j] >> 4, HEX);
    Serial.print(rcv[j] & 0xF, HEX);
    Serial.print(" ");
  }
  Serial.println();
}
