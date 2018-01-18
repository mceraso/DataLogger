#include <OneWire.h>
#include <DallasTemperature.h>
 
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2

#include <SPI.h> //SPI communication for SD card reader
#include <SD.h> //SD card functions

// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

File myFile; //variable name for File
char fileName[] = "temp.txt"; //name SD card file here
int n = 1; // keep measurement count
long timeNow;

void setup(void)
{
  // start serial port
  Serial.begin(9600);
  while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");

  if (!SD.begin(10)) {
      Serial.println("initialization failed!");
      return;
  }

  myFile = SD.open(fileName, FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
      myFile.print("Measurement Count, ");
      myFile.print("T1 (F), ");
      myFile.print("T2 (F), ");
      myFile.print("T3 (F), ");
      myFile.print("T4 (F), ");
      myFile.print("T5 (F), ");
      myFile.println("Milliseconds");
      // close the file:
      myFile.close();
      Serial.println("done.");
   } else {
      // if the file didn't open, print an error:
      Serial.println("error opening file");
   }
    
   Serial.println("initialization done.");

   // Start up the library
   sensors.begin();
}
 
 
void loop(void)
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print(" Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");

  Serial.print("Temperatures are: ");
  for (int i = 0; i < 5; i++){
    Serial.print(sensors.getTempCByIndex(i) * 9 / 5 + 32);
    if (i != 4){
     Serial.print(", ");    
    }    
  }
    // Why "byIndex"? 
    // You can have more than one IC on the same bus. 
    // 0 refers to the first IC on the wire

    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
  myFile = SD.open(fileName, FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to file...");
    myFile.print(n);
    myFile.print(", ");
    for (int i = 0; i < 5; i++){
      myFile.print(sensors.getTempCByIndex(i) * 9 / 5 + 32);
      myFile.print(", ");
    }    
    
    timeNow = millis();      
    myFile.println(timeNow);
      
    // close the file:
    myFile.close();
    Serial.println("done.");
    
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening file");
  }
  
  n++;      
}

