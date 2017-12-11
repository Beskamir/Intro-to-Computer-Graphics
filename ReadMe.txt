Author: Sebastian Kopacz
		30002779
Purpose: cpsc 453 assignment 4. Ray-tracer

To compile run: 
	cmake CMakeLists.txt
	make all

To run:
	./Assignment4 --default
	./Assignment4 --yours
	./Assignment4 <path to config.txt file> (ie ./Assignment4 data/config.txt)

To use:
    to modify values such as the resolution/fov/samples/depth/etc input values into the console after running the program. There will be prompts and instructions.

    to make a custom scene follow the formatting of the config file provided with this project.


Features:
    - perspective camera
    - sphere and triangles
    - can import obj files
    - reflections
    - refractions (mostly works)
    - shadows
    - super sampling
    - point and directional (sun) lights
    - mesh "lighting" (well not really just the mesh looks like it's a light and there are lights beside it which light up the scene)
    - low poly terrain and pyramids specifically made for the project
    -

Known issues:
    refractions don't work great under some circumstances...
    rendering takes a while since lights slow things down.

desired features:
    - use a compute shader

Citations and credit:

	Enormous thanks to:
