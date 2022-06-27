# ArduinoJimStim
Arduino implementation of the JimStim used for megasquirt

JimStim for Arduino
A pattern based ignition emulator with 44 common ignition and cam patterns . The patterns are in wheels_default.h 
Each pattern is a sequence where the first digit is the ignition and cam pulse and the sequence is terminated with 0xff,0, where it loops Back to the beginning.
As it is writing directly to PORTB you could potentially have up to 6 outputs in the pattern.

- 00 is all off
- 01 is ignition on cam off
- 02 is cam on ignition off
- 03 is both can and ignition on
The second digit is the number of degrees this pattern applies for. 
These patterns can either be for 360 degrees or 720 degrees.
