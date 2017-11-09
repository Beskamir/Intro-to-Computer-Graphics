Author: Sebastian Kopacz
		30002779
Purpose: cpsc 453 assignment 2. Read images and draw curves

To compile run: 
	cmake CMakeLists.txt
	make all

To run:
	./Assignment2

Keyboard inputs of note:

    Image scaling speed modifiers:
        1 = set scaling speed to 0.005 (min scaling speed)
        2 = decrease scaling speed by 0.005
        3 = set scaling speed to 0.025 (default scaling speed)
        4 = increase scaling speed by 0.005
        5 = set scaling speed to 0.1 (max scaling speed)

    Image panning:
        Click right mouse button and move mouse

    Image scaling:
        scroll wheel

    Image effects:
        q = 2bit quantized
        w = standard image
        e = grey scale image

    Point drawing:
        Right click

Known issues:



Citations and credit:
	
	Boilerplate based heavily on:
	https://github.com/JoeyDeVries/LearnOpenGL

	Resources for figuring out the syntax of GLFW and OpenGL:	
	https://learnopengl.com
	http://www.glfw.org/docs/latest/input_guide.html
	http://www.glfw.org/docs/latest/window_guide.html

    Resources for figuring out texture loading:
    https://stackoverflow.com/questions/23150123/loading-png-with-stb-image-for-opengl-texture-gives-wrong-colors
    https://www.reddit.com/r/opengl/comments/57d21g/displaying_an_image_with_stb/
    https://learnopengl.com

    Resources for figuring out how to convert an image to grey scale:
    https://www.gamedev.net/forums/topic/456541-glreadpixels---how-to-convert-an-image-to-grayscale/?PageSpeed=noscript

    Resources for figuring out how to draw curves:
    http://steve.hollasch.net/cgindex/curves/catmull-rom.html 
    https://www.youtube.com/watch?v=9_aJGUTePYo
    http://www.wolframalpha.com/input/?i=y%3D0.5*%7B0%5E3,0%5E2,0,1%7D*%7B%7B-1,3,-3,1%7D,%7B2,-5,4,-1%7D,%7B-1,0,1,0%7D,%7B0,2,0,0%7D%7D*%7B%7B-1,-1%7D,%7B-1,1%7D,%7B1,1%7D,%7B1,-1%7D%7D
    

	Resources for getting shit to work on Windows:
	https://gist.github.com/romanlarionov/2a22e77be3f2b574a2bd
	https://www.opengl.org/discussion_boards/showthread.php/198730-How-do-I-build-GLEW-for-mingw-w64-using-cmake-on-Windows?s=2621b22461d8dfb26cbeb7e2a558bee1&p=1283379&viewfull=1#post1283379
	http://www.glfw.org/download.html
	http://glew.sourceforge.net/
	The #ifdef's to include GLEW only on windows are thanks to Scott Saunders and Blake Mealey.

    Images from:
    CaliforniaCondor.jpg - My friend Rukiya Hassan painted it as I was working on graphics
    Other images, idk I had them on my desktop for ages.