#include <SoftwareSerial.h>

// Define SoftwareSerial pins for 3F Mini LiDAR communication
SoftwareSerial mySerial(2, 3); // RX, TX

// LiDAR reading variables
uint8_t data[9];
int distance;
int strength;
int check;

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);
  // Start software serial communication with the LiDAR
  mySerial.begin(115200);
  Serial.println("TF Mini LiDAR Test");
}

void loop() {
  if (mySerial.available()) {
    if (mySerial.read() == 0x59) {  // First byte of the frame
      if (mySerial.read() == 0x59) {  // Second byte of the frame
        for (int i = 0; i < 9; i++) { // Read the next 9 bytes
          data[i] = mySerial.read();
        }

        check = data[0] + data[1] + data[2] + data[3] + data[4] + data[5] + data[6] + data[7];

        if (data[8] == (check & 0xff)) { // Checksum
          distance = data[0] + data[1] * 256; // Distance in cm
          strength = data[2] + data[3] * 256; // Signal strength

          // Send distance and strength in a structured format
          Serial.print("Strength: ");
          Serial.print(distance);
          Serial.print(" , Distance: ");
          Serial.println(strength);
        }
      }
    }
  }
  delay(50);  // 50ms delay between reads
}