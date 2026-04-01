# Virtual Pilot Pro & Pro Pedals USB Adapter

This is a slight modification of [Necroware's GamePort Adapter](https://github.com/necroware/gameport-adapter)
For technical information about how it works, please visit the original project page, it is very well documented.

## Changes

1. There are two GamePort connectors instead of just one.

   Why: I wanted to use only one adapter to have both yoke and pedals.<br/>
   Drawback: The DIP switch had to be removed to reuse the inputs.<br/>
   You can still change to all other Joystick drivers by editing the code if you want, but changes will be necessary to add pedal functionality individually.

2. Sliders:

   Reading an axis as a "slider" on your driver will skip calibrating it's center based on it's position during power-on.<br/>
   The rest of the auto-calibration is still the same.<br/>
   Usefull for pedals that spring back instead of staying centered.

3. Driver for the CH Products Virtual Pilot Pro yoke:

   CHVirtualPilotPro.h file provided for use with the unmodified [Necroware's GamePort Adapter](https://github.com/necroware/gameport-adapter).

4. Driver for the CH Producst Pro Pedals:

   CHProPedals.h file provided for use with the unmodified [Necroware's GamePort Adapter](https://github.com/necroware/gameport-adapter).

## Connectors (ATENTION!)

```mermaid
 flowchart LR
    Y[(CH Products<br/>Virtual Pilot Pro)] --- c0
    c0@{ shape: bow-rect, label: "unlabeled<br/>male connector" }
    style Y stroke:#f00
    style c0 stroke:#f00

    c0 --> a0 --- A[(Adapter)] <--> USB
    a0@{ shape: bow-rect, label: "GamePort 1" }
    style a0 stroke:#0f0
    style A stroke:#0f0

    P[(CH Products<br/>Pro Pedals)] --- c1
    c1@{ shape: bow-rect, label: "#quot;GAMEPORT#quot;<br/>male connector" }
    style P stroke:#00f
    style c1 stroke:#00f

    c1 --> a1 --- A
    a1@{ shape: bow-rect, label: "GamePort 2" }
    style a1 stroke:#0f0
    
    c2 --> c3 --- c1
    c2 --- c1
    c2@{ shape: bow-rect, label: "#quot;AUX PORT#quot;<br/>male connector" }
    c3@{ shape: bow-rect, label: "#quot;JOYSTICK#quot;<br/>female connector" }
    style c2 stroke:#00f
    style c3 stroke:#00f
```

The CH Products Virtual Pilot Pro MUST be plugged to the adapter on the GamePort 1.

There is NO AUTOMATIC DETECTION of what controller is plugged to which port.

The mode switch on the pedals MUST be set to "PLANE" BEFORE powering on the adapter.

The CH Products Pro Pedals have thee 15 pin connectors, two male and one female.

This adapter expects you to plug the "AUX PORT" labeled male end on the "JOYSTICK" labeled female end, and plug the "GAMEPORT" labeled end to the adapter on the GamePort 2.

The  originl intended way of connecting the CH Products Pro Pedals as stated on it's user manual will not be recognized without modifications to the code.

## Bill of materials (BOM)

The hardware is super simple. To build an adapter you'll need the following parts:

Part    |  Qty  | [LCSC](https://lcsc.com/) #  | [Digikey](https://www.digikey.com/) #                | [Mouser Electronics](https://www.mouser.com/) # | Comment
--------|-------|---------|--------------------------|----------------------|------------------------------------------
CONN1   |   2   | C77835  | 609-5371-ND              | 523-L77SDA15SA4CH4F  | DB15 female connector
R1..R8  |   8   | C172965 | 13-MFR-25FTE52-100KCT-ND | 603-MFR-25FTE52-100K | 100 kOhm resistors
U1      |   1   | C72120  | ED3051-5-ND              | 649-DILB24P-223TLF   | DIP24 Socket (optional)
U1      |   1   |   N/A   | 1568-1060-ND             | 474-DEV-12640        | Arduino Pro Micro (ATmega32U4 16MHz, 5V), including two 12 pin header connectors, MicroUSB version (see "Known issues")

## Which controllers were tested?

* CH Products Virtual Pilot Pro
* CH Products Pro Pedals


## What is auto calibration?

Old analog joysticks have resistors inside, which are specified to be 100 kOhm.
Unfortunately, these resistors are either worn out, bad quality or were wrong from
the beginning. Therefore most of the generic analog joysticks had adjustment
screws to correct the center point of the joystick. Also many games had
calibration options in their settings to readjust the joystick. With USB and new
digital solutions the calibration was not required anymore and was completely
implemented in the joysticks and/or drivers. Many modern games have no option
to re-calibrate the joystick anymore. If we try to play such newer games with
an old analog joystick through this adapter, the joystick center point would be
totally offset. That's why the adapter implements auto calibration internally and
presents already corrected values to the operation system. 

__ATTENTION__: a hard requirement for using the analog joysticks is that during 
plugging into the USB port all axes not set up as sliders must be in their middle state, 
because all the subsequent calibration happens based on the initial state.

## Known issues

* *Ruder Axis is not working, just the Toe Brakes*

   A)First make sure all the connectors are as specified on this page, not as specified on the manual.

     -Virtual Pilot Pro connector ----→ Adapter GamePort 1 connector

     -Pro Pedals "GAMEPORT" connector ----→ Adapter GamePort 2 connector

     -connector labeled "AUX PORT" ----→ connector labeled "JOYSTICK"
  
   B)Set the mode switch on the pedal to "PLANE" instead of "CAR".
   Setting it to car passes the Left and Right Pedals to be used as Brake and Gas, intead of Left and Right Toe Brakes, through the connector labeled "GAMEPORT".
   This ignores the Rudder function completely, and we already have both Left and Right Pedals input from the connector labeled "AUX PORT".

* *Pedal axis are weird*

   Changing the mode switch on the pedal (from "CAR" to "PLANE" or otherwise) will mess up the calibration.
   Power off the adapter, make sure the switch is set to "PLANE" BEFORE the adapter is powered back on.
   (Assuming your hardware is not damaged).

* *Yoke/Joystick *

   Changing the mode switch on the pedal (from "CAR" to "PLANE" or otherwise) will mess up the calibration.
   Unplug the adapter, make sure the switch is set to "PLANE" before plugging it back again. 

* *Some axes on an analog joystick are offset*

   Auto calibration requires the axes to be in the center position during 
   initialization. Please see the paragraph about auto-calibration.

* *Joystick doesn't work*

   Make sure that you are using one of supported joysticks or a joystick which can
   work in legacy analog mode

* *MicroUSB port on the Arduino is not stable enough*

   Use the USB-C version of the Arduino instead.  
   Or always keep the MicroUSB cable attached to the Arduino MicroUSB version to avoid further wear and apply plug/unplug operations only on the remote side of the cable.

## Special thanks

Obviously, huge thanks to [Necroware](https://github.com/necroware) for developing and sharing the project.
And to those previously mentioned in the original project:
"I would like to give some special thanks to *Creopard* from the German 
dosreloaded.de community for providing me the mentioned joysticks. Without that
donation this project wouldn't be possible. Especially dealing with Sidewinder
3D Pro was a very exciting task."

## Links
* [Linux Sidewinder Driver](https://github.com/torvalds/linux/blob/master/drivers/input/joystick/sidewinder.c)
* [Sidewinder patent](https://patents.google.com/patent/US5628686A/en)
* [Creopard Retro Site](https://www.creopard.de/)

