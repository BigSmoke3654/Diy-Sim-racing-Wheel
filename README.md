Author :- Chirag Pilania

This project turns an Arduino Leonardo into a fully functional racing wheel and pedal set, recognized as a controller in Windows.

Features :-
steering wheel : uses a basic rotary encoder with 900 degree rotation (450 both sides)
throttle , brake and clutch

hardware :-
rotary encoder
3x potentiometers
1x arduino leonardo
1x incremental rotary encoder

wiring :- 
Encoder CLK pin :- D2
Encoder DT pin  :- D3
Throttle pot    :- A2
Brake pot       :- A1
Clutch pot      :- A0

you can branch out the ground and 5v wires to power and ground everything using only 2 pins on the arduino

libraries used :-
Encoder by Paul Stoffregen
Joystick by Matthew Heironimus

the code is really easy to understand and configurable if you want to change the steering angle , pedals smoothening , steering senstivity
the pedal smoothening ensures realiable input even with loose cables to the potentiometers

Games supported :-
Beamng Drive
asseto corsa
Euro Truck Simulator 2
Mud runner
Snow Runner

Updates :-

i will soon add H shifter , Led screen for info and maybe some buttons too