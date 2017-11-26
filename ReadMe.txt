Author: Sebastian Kopacz
		30002779
Purpose: cpsc 453 assignment 4. Ray-tracer

To compile run: 
	cmake CMakeLists.txt
	make all

To run:
	./Assignment4

To use:
    specify model and its textures on the commandline:
        ie: data/models/provided/chess_king/king.obj d data/textures/testTexture.jpg
            <filepath to the model (relative should work)> <model type, (d,a,s,n)> <filepath to the texture>
    specify everything in a config file and pass it in as a commandline argument:
        ie:
            #### plate
            >M: data/models/provided/plate/plate.obj
             D: data/models/provided/plate/plate.colour.png
             A: data/models/provided/plate/plate.ao.png

            #### chair
            >M: data/models/provided/oak_chair/oak_chair.obj
             D: data/models/provided/oak_chair/oak_table.colour.jpg
             A: data/models/provided/oak_chair/oak_chair.ao.png

            #### donut
            >M: data/models/provided/coffee_cup/coffee_cup.obj
             D: data/models/provided/coffee_cup/coffee_cup.colour.png
             A: data/models/provided/coffee_cup/coffee_cup.ao.png

        #### = indicates a new model is beginning
        >M: is the filepath to the model
         D: filepath to a diffuse texture
         A: filepath to an ao texture
         S: filepath to a specular texture
         N: filepath to a normal texture

        new lines and any text right after #### are optional, otherwise everything else is mandatory to the very last space

Keyboard inputs of note:
    fps mode:
        f = enables fps mode
        mouse movement moves the camera
        wasd moves the camera as expected in a typical fps
        q and e move the camera up and down
        scroll wheel changes the speed at which the camera moves.

    transformations: (completely based on blender's shortcuts)
        s = enables scaling
        r = enables rotate
        g = enables movement
        once a tranformation is active:
        x = locks the transformation to the x axis
        y = locks the transformation to the y axis
        y = locks the transformation to the z axis

        shift+x = locks the transformation to y and z but not the x axis
        shift+y = locks the transformation to x and z but not the y axis
        shift+z = locks the transformation to x and y but not the z axis

        a = enables all axis (scaling is now uniform, rotations and transformations are harder to use)

        for scaling and rotations just move the mouse and hopefully it's pretty intuitive. Although there's a slight bug when scaling/rotating in that the center of the window or the mouse's last position is used as a reference point rather than the center of the object that is being modified. All this means is that it's a bit weird to move the mouse toward the center of the screen rather than toward the object that you want to scale down.

        For translations, there were multiple plans for getting them to work but ultimately they all failed so I had to resort to a basic solution. Basically U, I, O, J, K, L control all the directions that an object can travel in. At least when considering 3D space.

        Also for translations if you scroll your mouse wheel while you have them active you can decrease or increase the speed at which those transformations are done.

        To apply a transformation click the left mouse button
        to cancel a transformation either switch to a different transformation (ie if scaling switch to rotate or move) or more practically just hit escape.

    lighting:
        ctrl + d = toggles the diffuse texture
        ctrl + s = toggles the specular texture
        ctrl + a = toggles the AO texture

    other:
        c = center on the object.... I think it only sort of works though :(
        shift + d = duplicate the selected model

        to select a model just left click on it.

Features:
    camera movement (fps mode),
    scaling, rotating, and moving a model
    support for diffuse, specular, and ambient occlusion texture maps
    window scaling does not negatively affect the render (scene remains visible and without stretching)
    duplication of a model using shift+d
    mouse loops around the screen when scaling, and rotating blender style. Would also include translations if I had figured out how to make them work when using a mouse. ##Although this also leads to a potential bug where if you move too quickly you can escape the window and then you're no longer looping as intended.##
    toggling the textures on and off (works for diffuse, ao and specular textures)
    can parse a config.txt file or take input directly from the commandline. Although commandline input is limited to a single model with a bunch of textures. So if you want to load multiple objects you need to set them up in a config file. ##Config file might need to be named config.txt ##
    obviously the camera is perspective (I kind of wanted to implement a toggle between orthonormal and perspective but ran out of time)

    chessboard was assembled in my primitive modeling/render engine by hand and screenshots are included.
    
    As usual anything the assignment specified should be done and had a grade value associated has been completed.

failed features:
    normal texture mapping, didn't have time to properly learn and implement it although the beginnings for it are kind of there
    using my own models for the final render with all the textures I could think of (specular, diffuse, AO, normal, etc)
    pbr lighting, (I know how to construct it with nodes in blender so it'd just require me to figure out how to do it in opengl and then the lighting's really really pretty. I'll probably end up implementing it after i submit the assignment)
    really fancy mouse based translations and rotations. Currently only scaling works "okayish" with a mouse while rotations are meh and translations were so bad I had to disable them and switch to using keys.
    I also wanted to figure out how to enable AA within OpenGL for this assignment
    Multithreading for parsing reading files would be nice
    better keyboard and mouse inputs
    would have been neat to include some kind of visual guide to help indicate where the light source is and potentially included another light source or two.
    would have been neat to figure out how cubemaps work and have a proper skybox with reflections.
    keyboard specified values for how far a model should move along a given axis like in blender would have been a nice feature but for various reasons it was breaking more things than fixing... probably cause I was half awake when I was writing it :(
    essentially the commented out code are features that were at various stages of development and I didn't feel the need to completely delete them since many of them I really wanted to get working.

Known issues:
    may crash after it's been running for a while... it crashed after (...thankfully) I finished taking screenshots of my chess board


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

	Resources for getting stuff to work on Windows:
	https://gist.github.com/romanlarionov/2a22e77be3f2b574a2bd
	https://www.opengl.org/discussion_boards/showthread.php/198730-How-do-I-build-GLEW-for-mingw-w64-using-cmake-on-Windows?s=2621b22461d8dfb26cbeb7e2a558bee1&p=1283379&viewfull=1#post1283379
	http://www.glfw.org/download.html
	http://glew.sourceforge.net/
	The #ifdef's to include GLEW only on windows are thanks to Scott Saunders and Blake Mealey.

    Resources for figuring out phony lighting, diffuse maps, specular, and ambient lighting:
    https://learnopengl.com/code_viewer.php?code=lighting/basic_lighting&type=fragment
    https://learnopengl.com/code_viewer.php?code=lighting/lighting_maps&type=fragment

    Resource for figuring out how to select models in a scene:
    https://en.wikibooks.org/wiki/OpenGL_Programming/Object_selection

    Models used in chessboard render were provided to us by the TA although I was very close to using my own models and procedurally generated textures.
