# OpenStewartPlatform
This project is implementation of Stewart platform with the open design, schematics, PCB and software. Feel free to iterate upon or fix our mistakes.

Project is including a following solutions:
* [ ] 6-DOF
* [ ] 3-DOF

# GOAL
Teach embedded development using something challenging.

# Applications

We have created a few apps:

* Testing purposes
    * Qt3DApp - Presenting our Stewart-platform in 3D space.
    * QtControlTest - Quick 'slider' controled application for playing around with servos
    * QtWiiTest - Including support for a Wii Mote
    
* Implementation
    * LFS (Life For Speed)
        * lfs-servos: To be able control our platform via Socket based client from Life For Speed game
        * lfs-rpi: To be able control our platform connected to Raspberry Pi via Socket based client from Life For Speed game
    * Cinema 4D
        * c4dpy-servos: To be able control platform directly from Cinema 4D's 3D Scene

# Hardware

* Atmel AtMega 16 on breadboard (see schematics)
    * Schematic: (see /design/scheamtics/)
    * MCU firmware: (see /firmware/atmega16/)
    
* Arduino UNO
    * Schematic: (see /design/schematics/)
    * MCU firmware: (see /firmware/arduino/)

* Raspberry Pi
    * Schematic: (see /design/schematics/)
    * Software: (see /firmware/rpi/)
