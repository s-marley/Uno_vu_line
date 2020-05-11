# UnoVULine
Code written to run on the Arduino Nano or Uno to drive LED strips such as WS2812B as a stereo VU meter.

## Features
- 10 VU patterns that move in time to the music.
- 7 standby patterns that move without audio input.
- Press the button to change pattern, long press to automatically cycle through patterns.
- Remembers the last pattern that you used when you power it off and returns to it on power on.
- Supports 75 LEDs per channel (150 total) on Uno and Nano. Much more on Mega etc.
- Completely open source and hackable. Create your own patterns or use it in whatever you like!

## Demo
Click the image below 

[![Youtube video of VU meter in action](http://img.youtube.com/vi/jhyUqx6inwI/0.jpg)](https://www.youtube.com/watch?v=jhyUqx6inwI)

## Installation and code usage
If you want to make this on your own, the schematic that I have used is:

![Wiring schematic](Uno_vu_line_schem.png?)

1. Download this repository and unzip it somewhere. You **must** rename the unzipped folder `Uno_vu_line`.
2. Open the [Arduino IDE](https://www.arduino.cc/en/Main/Software) then open `Uno_vu_line.ino`
3. You will need the FastLED and JC_Button libraries installed. In the IDE, go to `Tools` -> `Manage Libraries`. Search for `FastLED` and install the latest version and do the same with `JC_Button`.
4. On the `Uno_vu_line.ino` tab, find the line that says `# define N_PIXELS` and change the number after it to the number of LEDs you have in each string.
6. Plug in the Arduino and upload the code in the usual way, ensuring that the correct board type and com port are selected in the `Tools` menu.

## Extra info
- The more LEDs you have, the more power you will need to provide. Make sure your power source is able to cope.
- If the controller seems to go weird, I've found a quick reflash of the code usually clears it up quickly.
- This project is for entertainment purposes only and the output is not calibrated in any way.
- Code is written to run on the Nano / Uno or equivalent. Using an AVR with more SRAM will result in being able to use more LEDs.

Code is based on demos from the [FastLED](http://fastled.io/) library and code from [Cinelights](https://www.youtube.com/channel/UCOG6Bi2kvpDa1c8gHWZI5CQ) YouTube channel.
