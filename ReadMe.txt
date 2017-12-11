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
    - Gamma correction on the final image. (used to brighten up the final render)

Known issues:
    refractions don't work great under some circumstances...
    rendering takes a while since lights slow things down.

    - The final version hasn't actually been tested on Linux... which is why I'm reluctant to put in multithreading or compute shader support right now since those are stuff that are very likely to break on another OS.

desired features:
    - use a compute shader
    - multithreading
    - pbr (again, just like during the last assignment)
    - better user input
    - I really wanted to make it real time and merge it with the previous project)

Comments on the rendered images:
    Defualt render:
        - rendered at 1024*1024
        - 3*3 samples per pixel,
        - 55 FOV
        - 4 depth
        - right wall reflective
        - other walls diffuse
        - cube diffuse (I admit, refractions were a bit wonky on it)
        - sphere transparent
        - background is black

    My render:
        - rendered at 1024*1024
        - 3*3 samples per pixel,
        - 55 FOV
        - 4 depth
        - everything but the sphere's made in blender and transformed into the correct coordinate system that the ray tracer was using (this was painful af)
        - ground has a texture
        - center pyramid has a light (middle piece) and refractive (very top) component.
        - other pyramids both diffuse along with the bottom of the middle one
        - sphere above "pond/lake" transparent
        - lake reflective... (guess that makes it ice then :P refractions weren't looking good since light had trouble getting past it)
        - sky (background) is blue
        - lights located at the star (directional), above the pyramid (point), and above the pond (directional)
            - directional lights are based on their relation to the pond.
            - lights have color to them.

Citations and credit:

	Enormous thanks to https://www.scratchapixel.com almost everything is based on that tutorial series.

    Additionally this series was also really helpful: https://www.youtube.com/watch?v=RIgc5J_ZGu8

    Also even though I basically rewrote everything from scratch the code provided with the assignment was really helpful which, incombination with blender, was instrumental to figuring out the wacky coordinate system that the default scene required.

    Other sources I found useful or at the very least interesting:
        https://www.ics.uci.edu/~gopi/CS211B/RayTracing%20tutorial.pdf
        https://courses.cs.washington.edu/courses/cse557/08wi/projects/trace/
        really wish I had a bit more time to implement some of the features described in the first one.