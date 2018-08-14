# Perpetual Sedimentation (PS) Prototype

**This page describes how to build a perpetual sedimentation prototype housing three syringe pumps. These pumps allow for a continuous delivery of particles.**

This project is a fork of the original DropletKitchen project; [Low-cost, High-performance Syringe Pumps for Microfluidics Applications](https://github.com/DropletKitchen/pumpsn17). Original source code of the project is provided under MIT License. The source may contain code under a different license, if this is the case it is stated in the LICENSE file. 

The designs and documentation in this repository is Copyright (c) 2018 Jack Harrington and made available under a [Creative Commons Attribution 4.0 International (CC BY 4.0)](https://creativecommons.org/licenses/by/4.0/) License.

![](https://github.com/jack-harrington88/pumpsn17/blob/master/ConstructionPictures/PSPumpLab.png)
> The PS Pump prototype

## Introduction

The low-cost, high-performance syringe pumps from the droplet kitchen are suitable for a wide range of microfluidic applications, rivalling commercial pumps in quality at a fraction of the cost. The rapid sedimentation of particles often used in experiments (e.g. the DNA barcoded microbeads used in Drop-Seq) requires the use of expensive magnetic stirrers to actuate magnetic bars within the syringe. However, the DropSeq beads are fabricated using Toyopearl HW-65S resin, a brittle material that is prone to fracture during magnetic stirring. The perpetual sedimentation prototype provides a contactless solution to maintain particles in a suspended state to ensure continuous delivery.

The three PS syringe pumps work the same way as the original droplet kitchen pumps. The leadscrew is driven through a nut, pushing the plunger of the syringe at a controllable rate. A fourth motor controls the rotation of the chassis, rotating 360 degrees clockwise before turning 360 degree anticlockwise. This change of direction prevents the wires and tubing from continuously twisting. By loading well mixed syringes, the continuous rotation keeps particles evenly distributed throughout the syringe.

The prototype is relatively easy to construct for less than £500. Access to a laser cutter and 3d-printer is required - check a local makerspace/University or alternatively paid laser cutting and 3d-printing services are available online. Some experience with soldering/tinkering is advised.

The laser cut parts were designed in [CoralDRAW](https://www.coreldraw.com/en/) and each 3D print component was designed using [FreeCad](https://www.freecadweb.org/).
Modifications to the structure can be made by downloading and editing the [dxf file](https://github.com/jack-harrington88/pumpsn17/blob/master/PSPump_lasercut.dxf) and [FreeCad files](https://github.com/jack-harrington88/pumpsn17/tree/master/3d%20print/FCstd%20files).

## Bill of Materials
|	Item	|	Number	|	Purpose	|	Bought from	|	Part-no.	|	Approx. Cost (£)	|
|	-----------------------------------------------------------------------------------------	|	:---------:	|	:-------------:	|	--------------:	|	:----------:	|	:---:	|
|	Stepper Motor - NEMA17 - 400 steps (0.9 degree/step)	|	4	|	Stepper Motor	|	RS (can find cheaper)	|	535-0401	|	~108	|
|	Big Easy Stepper Driver	|	4	|	Stepper board	|	Hobbytronics	|	ROB-12859	|	~68	|
|	TEENSY3.2	|	1	|	Microcontroller	|	cpc-Farnell	|	SC13539	|	~17	|
|	Fine Hex Adjuster, 1/4"-80, 4" Long 	|	3	|	Leadscrew	|	Thorlabs	|	F25SS400	|	~30	|
|	Locking Phosphor-Bronze Bushing with Nut, 1/4”-80, L=0.50”	|	3	|	Leadscrew nut	|	Thorlabs	|	N80L6P	|	~21	|
|	Silver Steel 6 mm x 333 mm	|	10	|		|	Technobots	|	4426-006	|	~20	|
|	Zinc Collets 6 mm pk/4	|	48	|	Fasteners	|	Technobots	|	4609-060	|	~12	|
|	Linear Bearing LM6UU 6 mm Bushing	|	3	|	Slides motorpart	|	Technobots	|	4604-606	|	~3	|
|	Universal Coupling Body	|	3	|	Motor to screw connector	|	Technobots	|	4604-050	|	~9	|
|	Universal Coupling Insert - 5 mm	|	3	|	Motor to coupling	|	Technobots	|	4604-059	|	~6	|
|	Universal Coupling Insert - 1/4”	|	3	|	Coupling to screw	|	Technobots	|	4604-066	|	~9	|
|	306-3M-09 Timing Belt 3 mm Pitch, 9 mm Wide, 102 Teeth	|	1	|	Timing Belt	|	WychBearings	|	306-3M-09	|	~2	|
|	Shielded ball bearings (inner diameter 8 mm, outer 22 mm, 7 mm width)	|	4	|	Bearings	|	Simply Bearings or Amazon	|	608ZZ	|	~5 for 8	|
|	Stripboard	|	1	|	Mount for electronics	|	Technobots	|		|	~2	|
|	Sugru	|	1	|	Isolate PCB-headers	|	Amazon	|		|	~7	|
|	PCB headers and footers	|	some	|	Simple connectors	|	RS	|		|	~10	|
|	Various M3 Screws	|	Many	|		|	Hardware shop	|		|	~3	|
|	M6 Screws	|	Many	|		|	Hardware shop	|		|	~3	|
|	M6 Nuts	|	Many	|		|	Hardware shop	|		|	~3	|
|	12V/>=5A power supply	|	1	|		|	CPC-Farnell	|		|	~20	|
|	Ribbon cable (15ft)	|	4 m	|		|	Technobots	|		|	~4	|
|	micro USB cable	|	1	|		|	CPC-Farnell	|		|	~3	|
|	Acrylic (410 x 280 x 5 mm)	|	Pack of 5	|		|	TechSoft	|		|	~22	|
|	PLA Filament (1.7 mm)	|	>31 m	|		|	Farnell	|		|	~26	|
|		|		|		|		|	Total	|	413	|



## Assembly

* Laser cut each of the parts found in the [.dxf file](https://github.com/jack-harrington88/pumpsn17/blob/master/PSPump_lasercut.dxf)
* 3d-print the required number of pieces at 15% infill.

### Laser Cut and 3D Printed Components

|Name|Method|Number|file location|
|----|:----------:|:-------------|-------------:|
|A|Laser Cut|2|[dxf file](https://github.com/jack-harrington88/pumpsn17/blob/master/PSPump_lasercut.dxf)|
|B|Laser Cut|1|[dxf file](https://github.com/jack-harrington88/pumpsn17/blob/master/PSPump_lasercut.dxf)|
|C|Laser Cut|1|[dxf file](https://github.com/jack-harrington88/pumpsn17/blob/master/PSPump_lasercut.dxf)|
|D|Laser Cut|1|[dxf file](https://github.com/jack-harrington88/pumpsn17/blob/master/PSPump_lasercut.dxf)|
|E|Laser Cut|1|[dxf file](https://github.com/jack-harrington88/pumpsn17/blob/master/PSPump_lasercut.dxf)|
|F|Laser Cut|12*|[dxf file](https://github.com/jack-harrington88/pumpsn17/blob/master/PSPump_lasercut.dxf)|
|G|Laser Cut|12|[dxf file](https://github.com/jack-harrington88/pumpsn17/blob/master/PSPump_lasercut.dxf)|
|ArmBearingStand|3d Print (4.10m)|1|[ArmBearingStand.stl](https://github.com/jack-harrington88/pumpsn17/blob/master/3d%20print/ArmBearingStand.stl)|
|BearingStand|3d Print (2.76m)|2|[BearingStand.stl](https://github.com/jack-harrington88/pumpsn17/blob/master/3d%20print/BearingStand.stl)|
|MotorStand|3d Print (8.83m)|1|[MotorStand.stl](https://github.com/jack-harrington88/pumpsn17/blob/master/3d%20print/MotorStand.stl)|
|StandPulley|3d Print (4.97m)|1| [StandPulley.stl](https://github.com/jack-harrington88/pumpsn17/blob/master/3d%20print/StandPulley.stl) |
|PumpPulley|3d Print (4.97m)|1| [PumpPulley.stl](https://github.com/jack-harrington88/pumpsn17/blob/master/3d%20print/PumpPulley.stl) |
|Cog|3d Print (0.99m)|2| [cog.stl](https://github.com/jack-harrington88/pumpsn17/blob/master/3d%20print/cog.stl)|

\* *or more depending on size of syringe*

![](https://github.com/jack-harrington88/pumpsn17/blob/master/ConstructionPictures/LaserCutParts.png) 
> The laser cut parts for the syringe pump chassis.

### Assembly

As with the assembly of the droplet kitchen syringe pumps:
* For 3 of the motors; attach the universal coupling inserts and bodies to each of the motor shafts.
* Screw four part Gs onto the three stepper motors. 
* Insert each lead screw.

Additionally:
* Add an M3 nut into the rectangular hole in each of the cogs and pulleys and insert an M3 screw down through the top. See figure below.

![](https://github.com/jack-harrington88/pumpsn17/blob/master/ConstructionPictures/pulley.png) 
> The pulley with a grub screw and nut.



#### The Syringe Pump Chassis

Required; all remaining laser cut components, 2x cogs, 1x pump pulley, the 3 motor parts, 3x lead screw nut, 7x steel rods, 36x collets. 

Following the figure below:

  1. Align parts D and E together, pushing 2 rods through each segment and fastening together with collets.

  2. Slide the three stepper motor mounts on to each pump segment.

  3. Fasten parts B and C together using the lead screw nut.

     Slide the joined B & C components onto the rods (approx. 190 mm from parts D & E) securing in place with collets.
   
     Thread the lead screw through the lead screw nuts.
   
  4. Slide two part A pieces onto the rods and fasten with collets approx. 80 mm from B & C.

  5. Using M6 Nuts and screws, fasten four part Fs onto the two part As (more can be used for larger syringes).

  6. Push a steel rod through the two printed cogs.

     Align the cogs with the cog-shaped holes in D&E and B&C parts and screw the grub screws tight.
   
     At the rear end of this central rod, attach the pump pulley and tighten the grub screw.

![](https://github.com/jack-harrington88/pumpsn17/blob/master/ConstructionPictures/ConstructionPics.png)
> The construction of the syringe pump chassis.

#### The PS Stand
Required; 3x steel rods, 1x arm bearing stand, 1x motor stand, 2x bearing stand, 4x ball bearings, 12x collets.


* Firmly push each ball bearing onto the two bearing stands.
* Attach one bearing stand to the motor stand and the other to the arm bearing stand.
* Thread three rods through the holes in either stand piece.
* Screw the remaining stepper motor onto the motor stand using M3 screws (see below, left).
* Adjust the distance and orientation to allow the three pumps in the overall chassis to rest evenly on top of the ball bearings, fastening in place with collets.

![](https://github.com/jack-harrington88/pumpsn17/blob/master/ConstructionPictures/ConstructionStand.png)
> Construction of the PS stand.

* Push the stand pulley onto the stepper motor, tightening the grub screw.
* Attach the belt to both pulleys. There should be a tight fit without the pumps lifting from the ball bearings (see above, right. 

![](https://github.com/jack-harrington88/pumpsn17/blob/master/ConstructionPictures/PSStand_belt.png)
> The PS stand and belt mechanism.


### Electronics

* The electronics are set up the same as the [droplet kitchen pumps](https://github.com/DropletKitchen/pumpsn17/blob/master/README.org#electronics).
* For the first three stepper motors - extend the length of wiring using the ribbon wire and PCB-connectors. The length of wire between motor and motor driver should be >0.9 m. This comfortably allows enough room for the complete rotation of the PS pumps. 
* The fourth stepper motor (pins 11  & 12 - direction and speed respectively) controls the rotation.

# Software for the Pertpetual Sedimentation Pumps

The pumps are controlled in the same way as the [droplet kitchen pumps](https://github.com/DropletKitchen/pumpsn17).
* Download all the files from [PSPumpSoftware](https://github.com/jack-harrington88/pumpsn17/tree/master/PSPumpSoftware).
* Upload the Flexible3or4Pumps.ino to the Teensy microcontroller through the [Arduino IDE](https://www.pjrc.com/teensy/td_download.html) .
* [Pure Data](https://puredata.info/) is used for the frontend and calculating flow rates and rotation speeds.
* Place the PSPump.pd, PSPumpGOP.pd and o.io.slipserial.pd into a folder together and run through Pure Data (when controlling the pumps opening the PSPump.pd and PSPumpGOP.pd together helps prevent the stepper motor from 'missing' a turn).

# Syringe Pump and Rotation Control

The syringe pumps are controlled exactly as in the droplet kitchen pumps, moving the slider to the desired rate. Syringe diameters can also be altered with the corresponding buttons.
![](https://github.com/jack-harrington88/pumpsn17/blob/master/ConstructionPictures/Frontend.png)
> The Pure Data front end to control syringe pumps and chassis rotation.


The rotation rate is controlled through the blue radio buttons labelled "Rotation_speed" (far left stopping rotation). Below these controls is a manual override on the direction and the feedback direction from the microcontroller. Pressing the all_off button stops all 3 pumps and halts rotation. The Bang! button sets the syringe pumps to flow at a specific rate which can be configured in PSPumpGOP.pd. Changes to the speeds and degree of rotation is also easily done by modifying the PSPumpGOP.pd as below. 

![](https://github.com/jack-harrington88/pumpsn17/blob/master/ConstructionPictures/rotation_calcs.png)
> The chassis rotation calculations.
