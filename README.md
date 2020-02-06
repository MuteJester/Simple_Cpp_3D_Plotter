# Simple_Cpp_3D_Plotter
An MFC application for 3d ploting and analysis of coordiante based shapes.
The core algorithms and calculation are  based on the SIPL library which can be found in its own repository.
You can either plot the shapes in real time while inside the application ,or plot the coordinate points ,the vectors or the edges in a
simple .txt file and import the plot into the application.

## Preplot shapes into .txt files:
its much faster to plot in a .txt file if you already got all your vectors and you just want to visualize it ,
in order to create a readble plot , the following pattern must be present :
first line of txt file must be;- **Vectors**

then in each line after spesify a 3d point - (x,y,z) followed by the point name ,
for example : **(15,15,15) v0**

when done adding point and ready to get into the Edge ploting (what points are connected with a line between them), write in a new line
**EEE** - this will tell the application the following lines are edges ,
there is also the format - **ECE** this will tell the application the edges that will be written are collored edges, you will need to 
add a color at the end of the connection line ,
each connection line has to be formated in the following way:
**PointName1 PointName2** and if stated **ECE** the also a number from 1 - 137 which is a seriel number of a color
from the Color_Pallete class ,more about this calss can be found in the SIPL wiki.

Examples of plots can be found in this repository under the "Plot" Folder

## Intercation with the application

after loading the plot or creating one , you can click the **Camera** Tab and increace the Z value of the camera inorder 
to get closer to the shape ,

Inorder to rotate the shape click the **R** tab in the application and increase the X,Y,Z Values;

The **Teta** tab can be used to move the camera position in realtion to the shape .

## Quick Keys

Increasing and Decresing X,Y,Z Values of tabs can be done easily by pressing the hot-keys:

**X Increase** : - press the "z" key on you keyboard.

**Y Increase** : - press the "x" key on you keyboard.

**Z Increase** : - press the "c" key on you keyboard.

**X Decrease** : - press the "a" key on you keyboard.

**Y Decrease** : - press the "s" key on you keyboard.

**Z Decrease** : - press the "d" key on you keyboard.








# Exampels Of Plots
![Alt text](https://github.com/MuteJester/Simple_Cpp_3D_Plotter/blob/master/PlotExamples/exmp1.png  )
![Alt text](https://github.com/MuteJester/Simple_Cpp_3D_Plotter/blob/master/PlotExamples/exmp2.png  )
![Alt text](https://github.com/MuteJester/Simple_Cpp_3D_Plotter/blob/master/PlotExamples/exmp3.png  )
![Alt text](https://github.com/MuteJester/Simple_Cpp_3D_Plotter/blob/master/PlotExamples/exmp4.png  )

