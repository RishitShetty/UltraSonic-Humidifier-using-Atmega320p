Ultrasonic Humidifier Controlled by ATmega328P and HC-05 Bluetooth 

The ultrasonic humidifier project idea was to test the effectiveness of the prototype using a 8 Bit 
microcontroller Atmega328P with the Bluetooth module and other peripherals. This project was 
done to evaluate the author’s (Me) capabilities in compact PCB designing and coding 
capabilities in embedded C programming.  
Project Motivation: The basic use of an ultrasonic humidifier is to convert the liquid 
into mist particles useful for a spray-based mechanism in small devices mainly for the 
purpose of cleaning and getting into hard-to-get access places. Integrating it with a 
Bluetooth module makes the system more robust and easier to use and integrate with 
other modules with the add of no cost at all. 
Objectives: 
o Provide ON/OFF control of an ultrasonic transducer via push button or 
smartphone. 
o Maintain safe, efficient power management. 
o Keep BOM and PCB footprint minimized (cost & size). 
o Ensure reliable wireless communication (HC-05). 
2. Design Explanation 
2.1 System Overview & Block Diagram 
 High-Level Blocks: 
1. Power Supply (12 V Battery or Adapter → AMS1117 → 5 V Rail) 
2. ATmega328P Microcontroller 
3. HC-05 Bluetooth Module 
4. Manual Push Button Input 
5. MOSFET + Flyback Diode → Ultrasonic Transducer 
6. Status LED Indicator 
2.2 Component Selection Rationale 
1. ATmega328P Microcontroller 
o The Atmega328P is a high performance yet low power consumption 8-bit micro
controller with clock execution of 131 powerful execution. It serves as a perfect 
micro-controller for this system as we don’t require a MCU more powerful than 
this and power consumption is low enough. It is a simple RISC instruction set 
with 32KB of flash memory making it optimal. 
2. HC-05 Bluetooth Module 
o The HC-05 Bluetooth module is a common and cheap 2.4 GHz BL module which 
can be used easily integrated with the Atmega328P as it uses UART protocol for 
interfacing. 
3. MOSFET (IRFZ44N) 
o The MOSFET used in the circuit design was IRFZ44N because of its moderately 
compact footprint size and cost and effectiveness. It can handle up to 55V of drain 
source voltage and drain gate voltage and around 40 amps of drain current. 
4. Ultrasonic Transducer (e.g., 20 mm, 1.7 MHz Module) 
o In the KiCAD design the ultrasonic transducer used was a general one with a 
small footprint so as to accommodate it in the overall design. As we are using 12V 
input voltage for the ultrasonic transducer we need the switching mechanism 
using the MOSFET. The Atmega320P GPIO pins can only handle 5V and current 
in the milliamperes which is not sufficient for the sensor. 
5. AMS1117-5.0 Voltage Regulator 
o The AMS1117 is a common voltage regulator used in multiple breakout boards for 
regulating either 3.3 or 5 V depending upon the use. It’s cheap and effectiveness 
made it optimal in this project. 
6. Push Button & Debounce 
o The push button included was a pull-up which means it is always high until 
pressed making it low, debouncing was needed in order to make the small 
oscillations redundant and not to be considered as a press. 
7. Status LED 
o To give us an indication of the state of the system as we have two mechanisms to 
switch it, which is the button and the Bluetooth function which may make it 
confusing to figure out the status. 
8. Passive Components (Resistors, Capacitors, Flyback Diode) 
o The reset button is designed as a pull-up with a 10K ohm resistor, a 220 ohm 
resistor added to the gate so as to not let excess current into the gate of the 
MOSFET, Flyback diode to not allow reverse current flow to the MOSFET which 
could potentially damage it, and voltage dividers are used to reduce 5 volts to 3.3 
volts into the Rx and Tx pins of the Bluetooth module.  
 
 
 
2.3 Control Logic Flow 
1. Power-On Initialization 
o Initialize GPIO: Push button (input with pull-up), MOSFET pin (output LOW), 
LED pin (output LOW). 
o Initialize UART (UBRR=103 for 9600 bps @16 MHz). 
o Set mode = MANUAL by default. 
2. Main Loop 
while (true): 
    if (mode == MANUAL): 
        if (button_pressed()): 
            toggle_humidifier() 
            blink_LED()  // optional feedback 
            delay_ms(200)  // debounce 
    if (UART data available): 
        cmd = uart_receive() 
        if (cmd == '1'): 
            humidifier_on() 
            mode = BLUETOOTH 
        else if (cmd == '0'): 
            humidifier_off() 
            mode = BLUETOOTH 
        else if (cmd == 'M'): 
            mode = MANUAL 
 
The Bluetooth mode switching and manual mode switching are completely independent of each 
other and can work simultaneously, as you can see there are separate loops for each function. 
 
2.4 PCB & Hardware Considerations 
 HC-05 Placement & Antenna Keep-Out 
o The Bluetooth modules antenna was left on a void ground plane to improve range 
and also distanced from the MOSFET so to reduce EMI which could cause noise 
and subsequently loss of data. 
 MOSFET & Power Traces 
o The MOSFET’s position was thoroughly thought about as it could produce EMI 
and disrupt signal and caries high voltage. The traces used for the power lanes 
were thicker compared to the rest, 0.254 mm trace for the power line and 0.177 
mm for the rest. 
 Decoupling Capacitors 
o The decoupling capacitors are supposed to be as close to AMS1117 as possible so 
as to minimize power loss. 
 Reset Button & Pull-Up 
o Similarly, the button and the 10 Kohm pull-up has to be close to the push button 
to account for resistance. 
 Battery Pad Footprint 
o Battery pads are a must as our circuit needs 12V external supply to operate. 
 
3. Challenges & Solutions 
Here we will discuss the issues faced in circuit designing and how I worked over it. 
3.1 Signal Interference (Bluetooth & Switching Noise) 
Since EMI is always an issue circuit designers face, it will cause constructive and destructive 
interference with the low current data lines and result in data loss. So, I decided to keep the Rx 
and Tx lines distanced from the high voltage lines and the MOSFET which could also be a 
reason for EMI due to switching. 
3.2 Mode Switching Logic (Manual vs. Bluetooth) 
There are possibilities when the button switching could collide with the Bluetooth function and 
cause a race condition. Hence, a priority logic would definitely prove to rectify this issue and 
also debouncing the push button handles it well enough. 
3.3 Moisture & Environmental Concerns 
Depending upon how the ultrasonic humidifier module would be used, the cause of corrosion 
could be a concern. This is the reason I incorporated a small footprint for the ultrasonic 
transducer which serves as pads and can be used separately from the PCB. 
4. Block Diagram 
Instructions: Create a simple block diagram (e.g., in Microsoft PowerPoint, draw.io, or hand
sketch and import) showing these interactions: 
1. 12 V Battery / Adapter → AMS1117 → 5 V Rail 
2. 12 V Battery → Ultrasonic Transducer → 12 V Rail 
3. 5 V Rail → ATmega328P, HC-05, Status LED 
4. ATmega328P ↔ HC-05 (UART TX/RX) 
5. ATmega328P → MOSFET Gate  
6. MOSFET Drain → Ultrasonic Transducer 
7. Push Button → ATmega328P (GPIO) 
8. Status LED ← ATmega328P (GPIO) 
5. Potential Production Optimizations 
[Discuss how the design could be optimized for a production run. Cover cost reduction, board 
size shrinkage, alternative components, and manufacturing considerations.] 
1. Component Consolidation 
o For future considerations a better MCU with high clock frequency and if more 
functions were required for a production and market scenario. 
2. PCB Layout Miniaturization 
o Resistors, capacitors and other components footprint size could be reduced from 
current 0805 to per se 0402 for example and MCU size also can be reduced 
considerably if changed.
<img width="812" height="751" alt="image" src="https://github.com/user-attachments/assets/6c65b273-09c3-4e34-aee1-26399d2a4b1c" />
<img width="920" height="822" alt="image" src="https://github.com/user-attachments/assets/bc57ab9b-d1f7-4eee-b2f8-7d671caa5b0c" />


4. Assembly & Testing Jigs 
o More debugging lines in code would certainly help gather information of certain 
failures and help with failure and fault handling. Along with more testing and the 
addition of functions in future, more testing points need to be added.
 6. Conclusion 
Working on this led me to gain more in-depth knowledge on the Atmega328P and although it was 
an evaluatory task for me, this task did not really push me to any limits but helped me learn a 
couple of relevant things. 
7. References 
1. ATmega328P Datasheet, Microchip Technology. 
2. HC-05 Bluetooth Module Datasheet. 
3. AMS1117-5.0 Datasheet, Advanced Monolithic Systems. 
4. IRFZ44N MOSFET Datasheet, International Rectifier. 
5. https://chatgpt.com, for some assistance in embedded C.
