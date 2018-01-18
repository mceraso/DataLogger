# DataLogger

Using an Arduino Nano and MicroSD Card Adapter, we want to create a "black box" DataLogger
to analyze our robots after they complete a run. 

Both sketches were developed using https://www.arduino.cc/en/Tutorial/ReadWrite. 

# SDCardVoltageReadings.ino

This program reads the voltage across two points in a circuit, averages 5 readings, and then writes that average into a .TXT file
on an SD card. In practice we get about 7.5 readings / second. The goal of this sketch is to develop voltage profiles for our robots
and batteries to better understand their behavior over time. It's already helped us to better tune our motor driver chips and to undestand
undercharged batteries as the root cause for some problem behaviors.

We used https://startingelectronics.org/articles/arduino/measuring-voltage-with-arduino/
to develop this sketch. Pictures of our voltage divider and wiring diagram to come.

# SDCardDallasTemps.ino

This program uses a bus of five temperature sensors, collects temperature readings from each, and then writes each sensor's output to a
.TXT file on an SD card. The temperature sensors collect 1 reading / second. The goal of this sketch is to develop temperature profiles
for our robots and batteries to better understand their behavior over time. We are keenly interested in mapping battery, motor, and motor
driver chip temperatures to see if high temperatures correlate with problem behavior.

We used https://create.arduino.cc/projecthub/TheGadgetBoy/ds18b20-digital-temperature-sensor-and-arduino-9cc806
to develop this sketch. Pictures of our wiring diagram setup to come.

# Power Challenges

Using SDCardVoltageReadings.ino, we ran into an issue where an SD card failed and would get extremely hot when plugged into a computer
oor into our device. A new SD card would not work with the original set up, and we discovered that both the Arduino Nano and Micro SD
Card Adapter had failed. We do not yet know why this equipment failed, but we believe it has to do with the battery set up. In our
original design, we plugged a 5V battery into the micro USB port of the nano. This thread suggests that this is problematic:
https://electronics.stackexchange.com/questions/60199/powering-arduino-nano-12volts.

More research to come. The thread where we discovered we had fried equipment can be found here: http://forum.arduino.cc/index.php?topic=522486.msg3562711#msg3562711.
