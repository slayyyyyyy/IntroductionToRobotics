# IntroductionToRobotics (2023-2024)

Made for my 3rd year Robotics course at University of Bucharest. This repository contains weekly uploads of homework and labwork to track my personal growth and (maybe) some personal projects as well. Along with the code, requirements and implementation details, it also contains pictures as proof of the physical work from behind the curtains. Working in Arduino IDE with Kuongshun's learning kit.

End goal: building a real life BMO :)

# Contents: <br/>
[Homework 1](#homework-1) <br/>
[Homework 2](#homework-2) <br/>
[Homework 3](#homework-3) <br/>
[Homework 4](#homework-4) <br/>
[Homework 5](#homework-5) <br/>
[Homework 6](#homework-6) <br/>
[Homework 7](#homework-7) <br/>
 
## Homework 1

Had to create the github repository and give access to our teacher and TAs.

[Back to contents](#contents-)

## Homework 2

Component requirements: <br />
• RGB LED (At least 1) <br />
• Potentiometers (At least 3) <br />
• Resistors and wires as needed <br />

Tasks: <br />
• Technical Task : Use of separate potentiometers for controlling each color of the RGB LED: Red, Green, and Blue. This control must leverage digital electronics. Specifically, I need to read the potentiometer’s value with Arduino and then write a mapped value to the LED pins. <br />
• Publishing Task : Update github repo with the code and update README.md with the task requirements, pics of the setup and a link to a video showing its functionality. <br />
• Coding Task : Clean, well-structured code, avoidance of "magic numbers", use of constants with meaningful names. <br />

Using 3 potentiometers, a RGB LED, 3 resistors and a whole bunch of wires, I finally put together the following setup:

<img src="https://github.com/slayyyyyyy/IntroductionToRobotics/assets/104028747/f81550ee-4a0b-4f3f-baf9-e2bc4450cfe1 " width = "450" height = "400">

<img src="https://github.com/slayyyyyyy/IntroductionToRobotics/assets/104028747/c5d4ee81-41a1-446a-9537-e5558312e507" width = "450" height = "400">


Using the 3 potentiometers, one can control and adjust the brightness of each LED color. The video accessed through this Google Drive link will show a demonstration of what the circuit and the code provided in the repository do: [RGB control with 3 potentiometers](https://drive.google.com/file/d/1Dxou-CeesZ6c_ggzSLRYmoL9Te8A52zk/view?usp=share_link)

Fun and easy task! :)

[Back to contents](#contents-)

## Homework 3

This  assignment  involves  simulating  a  3-floor  elevator  control  system  using LEDs, buttons, and a buzzer with Arduino. The task is meant as an exercise to familiarize with new concepts, such as using button state change, implementing debouncing techniques and coordinating multiple components to represent real-world scenarios.

Component requirements: <br/>
•LEDs  (At  least  4:  3  for  the  floors  and  1  for  the  elevator’s  operational state) <br/>
•Buttons (At least 3 for floor calls) <br/>
•Buzzer (1) <br/>
•Resistors and wires as needed <br/>

Tasks: <br/>
• Technical Task : Each of the 3 LEDs should represent one of the 3 floors. The LED corresponding to the current floor should light up. Additionally, another LED should represent the elevator’s operational state. It should blink when the elevator is moving and remain static when stationary. The 3 buttons represent the call buttons from the 3 floors.  When pressed, the elevator should simulate movement towards the floor after a short interval (2-3 seconds). The buzzer should sound briefly during the following scenarios : elevator arriving at the desired floor (something resembling a ”cling”) and elevator doors closing and movement (pro tip: split them into 2 different sounds). If the elevator is already at the desired floor, pressing the button for that floor should have no effect. Otherwise, after a button press, the elevator should ”wait for the doors to close” and then ”move” to the corresponding floor. If the elevator is in movement, it should either do nothing or it should stack its decision (get to the first programmed floor,  open the doors, wait, close them and then go to the next desired floor). Finally, debounce implemented for the buttons to avoid unintentional repeated button presses. <br/>
• Publishing Task : Update github repo with the code and update README.md with the task requirements, pics of the setup and a link to a video showing its functionality. <br />
• Coding Task : Clean, well-structured code, avoidance of "magic numbers", use of constants with meaningful names. <br />

After figuring out how to setup the 4 LEDs, the 3 buttons and the buzzer, the following circuit came to reality. For my elevator, I choose to use green LEDs for elevator floors and a red LED to signal the movement of the elevator:

<img src="https://github.com/slayyyyyyy/IntroductionToRobotics/assets/104028747/06a42660-d216-463a-9fb2-b63668fdec49" width = "450" height = "400">

<img src="https://github.com/slayyyyyyy/IntroductionToRobotics/assets/104028747/437c3110-14a5-4fc0-8455-3889b05159fb" width = "450" height = "400">

Pressing the buttons, one can "call" the elevator to the desired floor. The buzzer will make a short, loud sound to announce the elevator doors closing and then a continous "buzz" to signal that the elevator is moving between floors. Each LED will light up when the elevator reaches its floor, no matter if it stops there or if it keeps moving. The red LED will keep blinking as long as the elevator moves and it completely turns off when the lift is stationing. When the desired floor is reached, the buzzer will "beep" 3 times to announce it. The following video presents a demonstration of this implementation: [Elevator simulator](https://drive.google.com/file/d/1r7enTS17K0I_EYG-8yfubzbX0qP36-ov/view?usp=sharing)

Challenging task and definitely harder !

[Back to contents](#contents-)

## Homework 4

This  assignment  involves  drawing on a 7 segment display with a joystick. 

Component requirements: <br/>
•7 segment display <br/>
•Joystick (1) <br/>
•Resistors and wires as needed <br/>

Tasks: <br/>
• Technical Task : The initial position should be on the DP. The current position always blinks (irrespective of the fact that the segment is on or off). Use the joystick to move from one position to neighbors (see table for corresponding movement). Short pressing the button toggles the segment state from ON to OFF or from OFF to ON. Long pressing the button resets the entire display by turning all the segments OFF and moving the current position to the decimal point. <br/>
![image](https://github.com/slayyyyyyy/IntroductionToRobotics/assets/104028747/d3e62057-6c99-4068-a507-47a7ee1248c8) <br/>
• Publishing Task : Update github repo with the code and update README.md with the task requirements, pics of the setup and a link to a video showing its functionality. <br />
• Coding Task : Clean, well-structured code, avoidance of "magic numbers", use of constants with meaningful names, use of <b>millis()</b> or <b>micros()</b>, using <b>interrupts</b> instead of delay(), avoidance of repetitive structures. <br />

The physical setup is represented in the following pictures:

<img src="https://github.com/slayyyyyyy/IntroductionToRobotics/assets/104028747/a2157dac-8258-4dd5-afc7-6989b60a7bcf" width = "500" height = "500">

<img src="https://github.com/slayyyyyyy/IntroductionToRobotics/assets/104028747/8b91ea31-9740-4b95-960c-7c8069eb9356" width = "500" height = "500">

<img src="https://github.com/slayyyyyyy/IntroductionToRobotics/assets/104028747/b735b11e-b80c-4960-b51f-75f646c04aa2" width = "500" height = "500">


A demonstration of how this works can be found here: [7 segments display drawing](https://drive.google.com/file/d/1xeKaUdoSJDZcFFWQKgC5CfdPgCAyIZon/view?usp=drive_link)

Harder task!

[Back to contents](#contents-)

## Homework 5

This  assignment  involves  implementing a stopwatch on a 4 digit 7 segment display.

Component requirements: <br/>
•4 digit 7 segment display <br/>
•Buttons (3) <br/>
•Resistors and wires as needed <br/>

Tasks: <br/>
• Technical Task : The starting value of the 4 digit 7 segment display shouldbe ”000.0”.  The buttons should have the following functionalities:<br/>
   – Button 1:  Start / pause. <br/>
   –Button  2:   Reset  (if  in  pause  mode).   Reset  saved  laps  (if  in  lap viewing mode). <br/>
   –Button 3:  Save lap (if in counting mode), cycle through last saved laps (up to 4 laps). <br/>
   
  Workflow: <br/>
  1.  Display shows ”000.0”.  When pressing the Start button, the timer should start. <br/>
  2.  During timer counter, each press of the the lap button, it should save  that  timer’s  value  in  memory  (not  persistent,  it  is  OK  to  be deleted upon reset), up to 4 laps; pressing the 5th  time  should  override  the  1st  saved  one.   If  the  reset button is pressed while the timer works, nothing happens. If the pause button is pressed, the timer stops. <br/>
  3. In Pause Mode, the lap flag button doesn’t work anymore. Pressing the reset button resets it to 000.0. <br/>
  4. After reset, the flag buttons can now be pressed to cycle through the lap times.  Each press of the the flag button, it takes the display to the next saved lap.  Pressing it continuously should cycle through it continuously.  Pressing the reset button while in this state resets all of the flags and takes the timer back to ”000.0”. <br/>

  
• Publishing Task : Update github repo with the code and update README.md with the task requirements, pics of the setup and a link to a video showing its functionality. <br />
• Coding Task : Clean, well-structured code, avoidance of "magic numbers", use of constants with meaningful names, use of <b>millis()</b> or <b>micros()</b>, using <b>interrupts</b> instead of delay(), avoidance of repetitive structures. <br />

The physical setup is represented in the following pictures:

<img src="https://github.com/slayyyyyyy/IntroductionToRobotics/assets/104028747/b7fb22d4-5c31-473b-b4b0-7d26fbeb0dc2" width = "450" height = "400">

<img src="https://github.com/slayyyyyyy/IntroductionToRobotics/assets/104028747/542ca7e8-4d1c-40cf-b284-a42ac2fe7990" width = "450" height = "400">

<img src="https://github.com/slayyyyyyy/IntroductionToRobotics/assets/104028747/ded374ff-1187-4f0e-b1a8-1ca6f1088a00" width = "450" height = "400">

A demonstration of how this works can be found here: [Stopwatch timer](https://drive.google.com/drive/folders/1nxeEOL7xyXRTufGuW4njaviQLgLu5JVY?usp=sharing)

[Back to contents](#contents-)

## Homework 6

This assignment involves creating a pseudo-smart environment with sensors which logs the data collected from external stimuli.

Component requirements: <br/>
•Ultrasonic Sensor (HC-SR04) <br/>
•LDR (Light-Dependent Resistor) <br/>
•RGB LED <br/>
•Resistors and wires as needed <br/>

The main menu structure includes 4 options and each of them opens a submenu: <br/>
  1. Sensor Settings which includes: </br>
     1.1 Sensors Sampling Interval, which prompts you for a value between 1 and 10 (seconds) and saves it in EEPROM, used as a sampling rate for the sensors. </br>
     1.2 Ultrasonic Alert Threshold, which prompts you with a threshold value for the ultrasonic sensor, which can be min or max. If the sensor readings are within the given parameter and the LED is in Automatic Mode, it will be <b>green</b> and if it exceeds the threshold, it should turn <b>red</b>. </br>
     1.3 LDR Alert Threshold, which acts the same as the ultrasonic one, but for the LDR sensor. </br>
     1.4 Back, which brings you back to the main menu. </br>
  2. Reset Logger Data which will prompt you with a confirmation message and two options, YES/NO. Depending on the user input (1 or 2), you can reset all logged (saved) data or return to the main menu. </br>
  3. System Status, which includes: </br>
     3.1 Current Sensor Readings, which continously prints sensor readings, at the set sampling rate and exits at any user input, going back to the submenu. </br>
     3.2 Current Sensor Settings, which displays the sampling rate and the sensor thresholds. </br>
     3.3 Display Logged Data, which displays the last 10 sensor readings for all sensors, previously saved in EEPROM. </br>
     3.4 Back, which brings you back to the main menu. </br>
  4.  RGB LED Control, which includes: </br>
     4.1 Manual Color Control, which allows you to input the RGB colors for the normal parameters color and the alert color for when Automatic Mode is OFF.</br>
     4.2 Toggle Automatic ON/OFF, which allows you to toggle the Automatic Mode ON or OFF. </br>
     3.4 Back, which brings you back to the main menu. </br>

The hardest task was to understand exactly what this system is supposed to do. Navigation through the menus was also tough to crack and I'm sure a lot of what I've done for this assignment could've been done way easier and it can definitely be improved, but in the end the system seems to be functional. Something important to mention is that except for the data stored in EEPROM, all data will be overwritten when selecting the option (thresholds, RGB colors). The physical setup was quite simple this time:

<img src="https://github.com/slayyyyyyy/IntroductionToRobotics/assets/104028747/a6882ab7-c892-4785-9d01-972b9c17f04a" width = "450" height = "400">

<img src="https://github.com/slayyyyyyy/IntroductionToRobotics/assets/104028747/6f2010f8-1dfc-40db-bf86-4389e1421cc5" width = "450" height = "400">

<img src="https://github.com/slayyyyyyy/IntroductionToRobotics/assets/104028747/341f3de8-5f5a-43c7-b7f8-f73768ca3558" width = "450" height = "400">

Demonstration of how the system works can be found here: [Pseudo-smart system](https://drive.google.com/drive/folders/10MRlVvZC56dq31HIOaNbjWOWX7YH696M)

[Back to contents](#contents-)

## Homework 7

This assignment involved creating a mini game on an 8x8 matrix that can be played with a joystick. The game must have at least 3 types of elements:  player (blinks slowly),  bombs/bullets (blinks fast),  wall (doesn’t blink).  The basic idea is that it generates walls on the map (50% - 75% of the map) and then you move around with the player and destroy them. You can do it Bomberman style or terminator-tanks style. I chose to have a player that shoots bullets at the walls, destroying them if they're in the given range which can be adjusted in the code. That means, for example, if the player stands in front of 2 consecutive walls and the shooting range is 3, then the player will destroy both walls with only one bullet. It should be also mentioned that the player cannot fire a bullet until they've chosen a direction (i.e. they have to move the joystick in any direction first).

Component requirements: <br/>
•Joystick <br/>
•8x8 LED Matrix <br/>
•MAX7219 <br/>
•Resistors and wires as needed <br/>

SOURCE MENTION: Part of the code used (especially the one regarding player movement) comes directly from the lab and I only adjusted it to suit my preferences. </br> 
POSSIBLE ISSUE: When navigating the map, one can find that there are no borders, meaning that when they reach the edge of the map, if moving in the same direction, they'll emerge from the opposite edge (e.g. if the player exceeds the UP 'border', they will emerge next from the DOWN 'border'). While someone can consider this a bug, I consider it a feature (I didn't try to change it) :)

The physical setup:

<img src="https://github.com/slayyyyyyy/IntroductionToRobotics/assets/104028747/94487a6f-6d5f-476c-aaab-49b146e46b06" width = "450" height = "400">

<img src="https://github.com/slayyyyyyy/IntroductionToRobotics/assets/104028747/c041280c-7066-4fb6-830e-9c45975754ac" width = "450" height = "400">

<img src="https://github.com/slayyyyyyy/IntroductionToRobotics/assets/104028747/578fa8a3-a37b-48b9-b75a-b50662d0ff87" width = "450" height = "400">

<img src="https://github.com/slayyyyyyy/IntroductionToRobotics/assets/104028747/458bd96a-12e6-487b-adbc-cfa39adbefd0" width = "450" height = "400">

See how it works here: [Tanks wannabe mini matrix game](https://drive.google.com/drive/folders/1_6NIzyuJCxbOuRSm8yvlMBXXTN7iitz-?usp=sharing)

[Back to contents](#contents-)
