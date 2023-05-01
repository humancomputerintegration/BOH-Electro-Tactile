# Full-Hand Electro Tactile Feedback without Obstructing Palmar Side of Hand

This is the repository for PCB schematics and Arduino codes used for the "Full-Hand Electro Tactile Feedback without Obstructing Palmar Side of Hand" paper (ACM CHI2023).

For more information, please refer to our paper: http://lab.plopes.org/#boh-electro-tactile

## notes:
1.	For PCB, the design originally assumes the use of the Bluetooth Module + Lipo battery but also works with normal Serial + power via Seeeduino XIAO's USB-C. If you go for this tethered option, ensure the battery is not connected, the power switch on the PCB is toggled ON, and the Bluetooth module is removed.
2.	The Kicad project for the PCB has not been tested for library compatibility, so let us know if it does not appear properly on your end, but just uploading the Gerber file should suffice for ordering the PCB.
3.	The Arduino code is a generic program to drive the circuit in response to Serial messages from other program instances such as Unity, Python, Processing, etc.

# citing
When using or building upon this device in an academic publication, please consider citing as follows:

Yudai Tanaka, Alan Shen, Andy Kong, and Pedro Lopes. 2023. Full-Hand Electro-Tactile Feedback without Obstructing Palmar Side of Hand. In Proceedings of the 2023 CHI Conference on Human Factors in Computing Systems (CHI'23), April 23-28, 2023, Hamburg, Germany. ACM, NewYork, NY, USA, 15 pages. https://dl.acm.org/doi/abs/10.1145/3544548.3581382

# contact
For any questions about this repository, please contact yudaitanaka@uchicago.edu
