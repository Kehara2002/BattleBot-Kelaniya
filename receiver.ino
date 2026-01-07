#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

#define RF_RX_PIN 22   // Connect DATA pin of RX module here

void setup() {
  Serial.begin(115200);
  
  mySwitch.enableReceive(RF_RX_PIN);  // Enable receiver on GPIO22
  
  // Optional: adjust protocol & pulse length if default doesn't work
  mySwitch.setProtocol(1);     // Try 1, 2, or 3 if needed
  mySwitch.setPulseLength(350); // Try 300-350 range for cheap 315 MHz modules
  
  Serial.println("Receiver Ready!");
}

void loop() {
  if (mySwitch.available()) {
    int value = mySwitch.getReceivedValue();
    
    if (value == 0) {
      Serial.println("Unknown data");
    } else {
      Serial.print("Received: ");
      Serial.println(value);

      // Map values if needed: e.g., 1=Forward, 2=Backward, 3=Left, 4=Right, 0=Stop
    }

    mySwitch.resetAvailable();
  }
}
