# Smart City IoT System using Arduino Nano

## Overview

This project is an IoT-based Smart City prototype developed using two Arduino Nano microcontrollers. The system demonstrates automation of various urban infrastructure components through sensor-based control, embedded programming, and real-time monitoring.

The project integrates multiple smart city modules, including railway crossing automation, smart parking management, traffic signal control, automatic dustbin operation, and street light automation.


## Features

### 1. Smart Railway Crossing

* Detects approaching trains using an IR sensor.
* Automatically closes the railway gate.
* Activates warning buzzer and blinking red LED.
* Reopens the gate after a safety delay once the train passes.

### 2. Smart Parking System

* Monitors three parking slots using sensors.
* Displays available parking spaces on an LCD screen.
* Automatically opens the entry gate when slots are available.
* Prevents entry when parking is full.

### 3. Smart Dustbin

* Uses an ultrasonic sensor to detect nearby users.
* Automatically opens the lid when a hand is detected.
* Closes the lid automatically after a few seconds.

### 4. Smart Traffic Signal

* Implements a four-state traffic control system.
* Controls North-South and East-West traffic flow.
* Uses non-blocking timing logic for smooth operation.

### 5. Smart Street Light

* Uses an LDR (Light Dependent Resistor).
* Automatically turns lights ON during low-light conditions.
* Automatically turns lights OFF during daytime.


## Hardware Components

* Arduino Nano × 2
* Servo Motors
* IR Sensors
* Ultrasonic Sensor (HC-SR04)
* LDR (Light Dependent Resistor)
* LCD I2C Display
* LEDs
* Buzzer
* Breadboards
* Jumper Wires
* Power Supply


## Software

* Arduino IDE
* Embedded C/C++


## Project Architecture

### Arduino Nano 1

* Smart Railway Crossing
* Smart Parking System

### Arduino Nano 2

* Smart Dustbin
* Smart Traffic Signal

### Independent Circuit

* Smart Street Light using LDR


## Technical Concepts Used

* Embedded Systems
* Sensor Integration
* Servo Motor Control
* LCD Communication (I2C)
* Event-Driven Programming
* State Machine Design
* Non-Blocking Timing using `millis()`
* Automation and Control Systems


## My Contribution

This project was developed as part of a six-member team.

My primary contributions included:

* Arduino programming and firmware development
* Circuit wiring and hardware integration
* Sensor interfacing
* Servo motor control
* LCD integration
* Testing and debugging
* Implementation of Smart Railway Crossing
* Implementation of Smart Parking System
* Implementation of Smart Traffic Signal
* Implementation of Smart Dustbin

The Smart Street Light module was implemented using an LDR-based automatic lighting circuit.


## Future Improvements

* IoT cloud connectivity
* Mobile application monitoring
* Smart traffic optimization
* AI-based parking prediction
* Air quality monitoring
* Energy usage analytics
* Computer vision-based traffic management
