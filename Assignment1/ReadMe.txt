Author: Sebastian Kopacz
		30002779
Purpose: cpsc 453 assignment 1. Draw Hilbert Curves using triangles and lines

To compile run: 
	cmake CMakeLists.txt
	make all

To run:
	./Assignment1

Keyboard inputs of note:
	i = increase the hilbert curve's detail 
	k = decrease the hilbert curve's detail
	o = draw the hilbert curve using triangles
	l = draw the hilbert curve using lines

Known issues:
	May crash on windows if you spam it with input while it's trying to compute stuff, 
	as far as I can tell that's not an issue on Linux.


Citations and credit:

	Resources for figuring out the syntax of GLFW and OpenGL:	
	https://learnopengl.com
	http://www.glfw.org/docs/latest/input_guide.html
	http://www.glfw.org/docs/latest/window_guide.html

	Resources for getting shit to work on Windows:
	https://gist.github.com/romanlarionov/2a22e77be3f2b574a2bd
	https://www.opengl.org/discussion_boards/showthread.php/198730-How-do-I-build-GLEW-for-mingw-w64-using-cmake-on-Windows?s=2621b22461d8dfb26cbeb7e2a558bee1&p=1283379&viewfull=1#post1283379
	http://www.glfw.org/download.html
	http://glew.sourceforge.net/
	The #ifdef's to include GLEW only on windows are thanks to Scott Saunders and Blake Mealey.

	Main resource for figuring out how to generate Hilbert Curves:
	https://www.youtube.com/watch?v=3s7h2MHQtxc