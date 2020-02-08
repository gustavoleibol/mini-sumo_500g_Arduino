# Instructions

Electric and Software project for navigation of the mini-sumo 500g (My Robot Banguela)

ArduinoIDE is required

Understanded the pinnout of Arduino is required

*Developed by Gustavo Rocha Serafim in 2018*

# Components

Arduino UNO

Driver motor L298N

3x Sensor E18-D80NK

Battery 7v

2x motors DC 6v with current stall 2A per canal

2x Sensor Line QRE

Protoboard (or shield)

Jumpers

# Electrical schematic

![](https://github.com/gustavoleibol/mini-sumo_500g_Arduino/blob/master/Image.png)

# Software

Simple logic for beginners in robot world mini-sumo

Definition the pins is equals Electrical schematic

if object find equals 0 for sensor central, Banguela will be attack

if white line find less than 630 (white line) for sensor qre, Banguela will be back off doing curve

Jumpers colors commented in code equals eletrical schematic



