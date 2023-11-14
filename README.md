# IntroductionToRobotics (2023-2024)

Made for my 3rd year Robotics course at University of Bucharest. This repository contains weekly uploads of homework and labwork to track my personal growth and (maybe) some personal projects as well. Along with the code, requirements and implementation details, it also contains pictures as proof of the physical work from behind the curtains. Working in Arduino IDE with Kuongshun's learning kit.

End goal: building a real life BMO :)

# Contents: <br/>
[Homework 1](#homework-1) <br/>
[Homework 2](#homework-2) <br/>
[Homework 3](#homework-3) <br/>
[Homework 4](#homework-4) <br/>
[Homework 5](#homework-5) <br/>
 
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
