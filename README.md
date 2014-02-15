# Fake ISMIC controller

This is a firmware to ISMIC chip which allows to communicate between blade chassis management unit and Cisco blade switch.
It is for Cisco CBS-3120 in HP BladeSystem c-Class, but probably supports other similar hardware.

### Description
The main reason to write it was need to control fan speed from switch CLI over ssh. Big additional fan is a must due to huge power consumption.
More info here: https://tomaszgluch.pl/wiki/en/2014-01/hp-bladesystem-onboard-supervisor-chip-reverse-engineering
This project is discontinued due to hardware failue on my only device. Probably I²C interface is broken on ASIC side.

### Implementation
It switches on power to switch logic, so there is no requirement to make any modifications on hardware.
This firmware also implements I²C communication on internal bus, so you can read/write registers from switch console.
That registers store a rack name, bay number etc. in original firmware, but can be used as buffer for external fan control or switch off command.


