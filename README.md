# IntroductionToRobotics (2023-2024)

Made for my 3rd year Robotics course at University of Bucharest. This repository contains weekly uploads of homework and labwork to track my personal growth and (maybe) some personal projects as well. Along with the code, requirements and implementation details, it also contains pictures as proof of the physical work from behind the curtains. Working in Arduino IDE with Kuongshun's learning kit.

End goal: building a real life BMO :)

# Contents: <br/>
[Homework 1](#homework-1) <br/>
[Homework 2](#homework-2) <br/>
[Homework 3](#homework-3) <br/>

<details>
<summary>## Homework 1</summary>

Had to create the github repository and give access to our teacher and TAs. 
</details>
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

![9bf9d171-9e07-4458-bed2-4e188e162558](https://github.com/slayyyyyyy/IntroductionToRobotics/assets/104028747/f81550ee-4a0b-4f3f-baf9-e2bc4450cfe1)

![982f6a10-990e-4238-9dba-8cfa2499f279](https://github.com/slayyyyyyy/IntroductionToRobotics/assets/104028747/c5d4ee81-41a1-446a-9537-e5558312e507)

Using the 3 potentiometers, one can control and adjust the brightness of each LED color. The video accessed through this Google Drive link will show a demonstration of what the circuit and the code provided in the repository do: [RGB control with 3 potentiometers](https://drive.google.com/file/d/1Dxou-CeesZ6c_ggzSLRYmoL9Te8A52zk/view?usp=share_link)

Fun and easy task! :)

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
![WhatsApp Image 2023-10-30 at 10 23 35 PM](https://github.com/slayyyyyyy/IntroductionToRobotics/assets/104028747/06a42660-d216-463a-9fb2-b63668fdec49)

![WhatsApp Image 2023-10-30 at 10 23 39 PM](https://github.com/slayyyyyyy/IntroductionToRobotics/assets/104028747/437c3110-14a5-4fc0-8455-3889b05159fb)

Pressing the buttons, one can "call" the elevator to the desired floor. The buzzer will make a short, loud sound to announce the elevator doors closing and then a continous "buzz" to signal that the elevator is moving between floors. Each LED will light up when the elevator reaches its floor, no matter if it stops there or if it keeps moving. The red LED will keep blinking as long as the elevator moves and it completely turns off when the lift is stationing. When the desired floor is reached, the buzzer will "beep" 3 times to announce it. The following video presents a demonstration of this implementation: [Elevator simulator](https://drive.google.com/file/d/1r7enTS17K0I_EYG-8yfubzbX0qP36-ov/view?usp=sharing)

Challenging task and definitely harder !
