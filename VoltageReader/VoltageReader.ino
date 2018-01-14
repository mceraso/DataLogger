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

// number of analog samples to take per reading
#define NUM_SAMPLES 10

int sumA2 = 0;                    // sum of samples taken
int sumA4 = 0;
unsigned char sample_count = 0; // current sample number
float voltage = 0.00;            // calculated voltage

void setup()
{
    Serial.begin(9600);
}

void loop() {
  
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
    // send voltage for display on Serial Monitor
    // voltage multiplied by 11 when using voltage divider that
    // divides by 11. 11.132 is the calibrated voltage divide
    // value
    Serial.print(voltage /* 2.1917*/);
    Serial.println (" V");
    sample_count = 0;
    sumA2 = 0;
    sumA4 = 0;
}
