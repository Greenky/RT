# RT
***RT by PowerRangers team***
<hr> 
Final Project of Computer Graphic branch in UNIT Factory.
The goal was to create Ray Tracing program with lot of functions, such as Graphic User Interface, texture mapping, reflective and tranctarent surfaces, using just pure C and SDL Framework for visualization.

<b> How to use </b>

In MAC OS, open the folder in terminal, type `make` then execute the binary `RT` with scene by first parameter. 
Executable binary also included in repo.</br>
All scenes are based in "scenes\" folder.</br>
Execution without parameters shows `usage`.</br>
FLag [-s] after the scene turn on the server mode (works only in UNIT Factory) 

<b> Сontrols </b>
```
W-A-S-D             :	for move the camera
Left mouse button   :	highlight the object, interact with user interface
Arrow keys          :	rotate the camera, or in highlight mode rotate the object
```
***GUI capability***
>> In highlight the object mode - appears window with name, position controls and radius (for sphere and cylinder) or angle (for cone) adjustment.</p>
>> Filters button </p>
>> <li> Black and white
>> <li> Sepia
>> <li> Pixel
>> <li> Inversion </li>
>> Save button saves image of current camera position in project folder </p>
>> Antialiasing switch turns on antialiasing
