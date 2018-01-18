/*--------------------------------------------------------------
  Program:      volt_measure

  Description:  Reads value on analog input A2 and calculates
                the voltage assuming that a voltage divider
                network on the pin divides by 11.
  
  Hardware:     Arduino Uno with voltage divider on A2.
                
  Software:     Developed using Arduino 1.0.5 software
                Should be compatible with Arduino 1.0 +

  Date:         22 May 2013
 
  Author:       W.A. Smith, http://startingelectronics.org
--------------------------------------------------------------*/

#include <SPI.h> //SPI communication for SD card reader
#include <SD.h> //SD card functions

File myFile; //variable name for File
char fileName[] = "cap.txt"; //name SD card file here

// number of analog samples to take per reading
#define NUM_SAMPLES 10

int sumA2 = 0;                    // sum of samples taken
int sumA4 = 0;
unsigned char sample_count = 0; // current sample number
float voltage = 0.00;            // calculated voltage
int n = 1; // keep measurement count
long timeNow;

void setup() {

    //pinMode(10, OUTPUT);
    //digitalWrite(10, HIGH);
  
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
      myFile.print("Voltage (V), ");
      myFile.println("Milliseconds");
      // close the file:
      myFile.close();
      Serial.println("done.");
    } else {
      // if the file didn't open, print an error:
      Serial.println("error opening file");
    }
    
    Serial.println("initialization done.");
    
}

void loop(){    
    // take a number of analog samples and add them up
    while (sample_count < NUM_SAMPLES) {
        sumA2 += analogRead(A2);
        sumA4 += analogRead(A4);
        sample_count++;
        delay(10);
    }
    
    // calculate the voltage
    // use 5.0 for a 5.0V ADC reference voltage
    // 5.015V is the calibrated reference voltage
    voltage = (((float)sumA4 - (float)sumA2) / (float)NUM_SAMPLES * 5.21 * 25.7 / 5.7) / 1024.0;

    Serial.print(voltage);
    Serial.println(" V");
    
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    myFile = SD.open(fileName, FILE_WRITE);

    // if the file opened okay, write to it:
    if (myFile) {
      Serial.print("Writing to file...");
      myFile.print(n);
      myFile.print(", ");
      myFile.print(voltage);
      myFile.print(", ");

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
    sample_count = 0;
    sumA2 = 0;
    sumA4 = 0;
}
