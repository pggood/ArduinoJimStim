# ArduinoJimStim
Arduino implementation of the JimStim used for megasquirt

JimStim for Arduino

A pattern based ignition emulator with 44 common ignition and cam patterns . 

The patterns are in 

wheels_default.h 

Each pattern is a sequence where the first digit is the ignition and cam pulse and the second is the number of degrees it applies for .

The sequence is terminated with 0xff,0, where it loops Back to the beginning.

As it is writing directly to PORTB you could potentially have up to 6 outputs in the pattern.

- 00 is all off
- 01 is ignition on cam off
- 02 is cam on ignition off
- 03 is both cam and ignition on

These patterns can either be for 360 degrees or 720 degrees.

If you are constructing a patern be carefull to add up all the degrees in the second field and make sure it adds up to either 360 or 720

This can be done in a spreadsheet first.

The repository holds the Ardunio source code as well as the Kicad PCB Schematic and gerber files that can be made by people like pcbway, jlcpcb or whoever you prefered PCB maker is. The design is through hole so can be put together by a hobyist with basic soldering skills.
