# OpenStewartPlatform

This project is an implementation of Stewart platform with the open design, schematics, PCB and software. Feel free to iterate upon or fix our mistakes.

Project is including a following solutions:
* [ ] 6-DOF using servo stepper motors

# GOAL
I wanted to learn embedded development using something challenging. This project demonstrates usage of Inverse Kinematic math, Mechanic design, Electronic design, Firmware development and Software development with 3rd parties implementation.

# Design

For a complete design from basic theory to functional prototype follow **'/design'** directory.

* /mechanical
    * **C4D** - 3D interactive model (Cinema 4D project)
    * **GCodes** - Printable parts on 3d printer (Prusa MK2 gcode's)

* /pcb 
    * **cad** - final PCB design for an Atmel ATmega 16 version! (see. /schematics/atmega16/pcb)

* /schematics
   * **atmega** - follows a two designs a 'breadboard' and 'pcb'
   * **arduino** - contains schematics only for an UNO version!
   * **rpi** - contains schematics for raspberry pi


# Applications

For a working applications in as it is condition follow **'/app'** directory.

* Testing purposes
    * **Qt3DApp** - Presenting our Stewart-platform in 3D space.
    * **QtControlTest** - Quick 'slider' application for playing around with servos. Credits [Jiri 'Akres' Kantor](https://github.com/akres)
    * **QtWiiTest** - Qt3DApp Including support for a Wii Mote. Credits [Ivo 'Ajvo' Hlavnicka](https://github.com/rompucha) 
    
* Implementation
    * LFS [Life For Speed](https://www.lfs.net/)
        * **lfs-servos:** - To be able control our platform via Socket based WIN32 - Windows client from Life For Speed game
        * **lfs-rpi:** - To be able control our platform connected to Raspberry Pi via Socket based client from Life For Speed game
    * [Maxon Cinema 4D](https://www.maxon.net/)
        * **c4dpy-servos:** - To be able control platform directly from Cinema 4D's 3D Scene
            * **Note** - Plugin works even with a Demo version of Cinema 4D. Just follow instructions listed in folder.

# Firmware

Firmware or software for supported MCU's follow **'/firmware'** directory.

* Atmel AtMega 16 on breadboard + PCB design (see schematics)
    * Schematic: see /design/scheamtics/atmega
    * MCU firmware: see /firmware/atmega16
    * **Requirements**: **A fully working JTAG programmer.**

* Arduino UNO
    * Schematic: see /design/schematics/arduino
    * MCU firmware: see /firmware/arduino

* Raspberry Pi
    * Schematic: see /design/schematics/rpi
    * Software: see /firmware/rpi
    
# References

Well we didn't invent a wheel from scratch as might look. So I would like to list reference material what might to be good to read!

