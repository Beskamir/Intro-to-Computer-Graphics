# Intro-to-Computer-Graphics
Storage repository for the 4 assignments I did for the 'Intro to Computer Graphics' course I took.

For additional images, [click here](https://www.artstation.com/beskamir/albums/1146636) to go to my ArtStation.

---
## Assignment 1: Hilbert Curve  

### Features: 
- Draws first to tenth order Hilbert Curves using OpenGL's lines as well as by using thin triangles.

#### Multi-colored 7th order Hilbert Curve using thin triangles for the lines: <img src="https://cdnb.artstation.com/p/assets/images/images/014/276/469/large/sebastian-kopacz-assignment1-2018-11-26-23-06-56.jpg?1543298910" width="400" />

### Credits:
- Regarding the software implementation the following resources were invaluable: 
   - For understanding OpenGL: https://learnopengl.com
   - For input: http://www.glfw.org/docs/latest/input_guide.html
   - For the window: http://www.glfw.org/docs/latest/window_guide.html
---
## Assignment 2: Image Manipulation  

### Features: 
- Draw multi-colored Catmull-Rom curves and loops.
- Apply image filters (grayscale and 2-bit quantization).
- Move and scale the image.


#### Multi-colored Catmull-Rom spline drawing and 2-bit image quantization: <img src="https://cdnb.artstation.com/p/assets/images/images/014/257/939/large/sebastian-kopacz-bonusimage.jpg?1543232178" width="400" />

#### Original image by nexus user realdreadstar (check credits section): <img src="https://cdnb.artstation.com/p/assets/images/images/014/258/571/large/sebastian-kopacz-tower.jpg?1543231507" width="400" />

#### Grayscale filter uses NTSC conversion weights: <img src="https://cdnb.artstation.com/p/assets/images/images/014/258/845/large/sebastian-kopacz-greyscale.jpg?1543232531" width="400" />

#### 2-bit image quantization: <img src="https://cdnb.artstation.com/p/assets/images/images/014/276/275/large/sebastian-kopacz-2bit.jpg?1543297907" width="400" />


### Credits:
- Original image is by realdreadstar/Natty Dread and he made it by setting up a custom scene in The Witcher 3 and taking a screenshot of it.
    - [Link to realdreadstar's version on the Nexus](https://www.nexusmods.com/witcher3/images/1239)
    - [Link to Natty Dread's version on Flickr](https://www.flickr.com/photos/90866390@N06/17649150394/in/dateposted-public/)
  - Regarding the software implementation the following resources were invaluable: 
   - For understanding OpenGL: https://learnopengl.com
   - For input: http://www.glfw.org/docs/latest/input_guide.html
   - For the window: http://www.glfw.org/docs/latest/window_guide.html
   - Lines drawn using: https://vicrucann.github.io/tutorials/osg-shader-3dlines/
---
## Assignment 3: Model Viewer and Basic Editor


### Features:
- Models can be selected by mouse clicking on them.
- Selected models can be modified by rotating, scaling, translating, duplicating, or turning various textures on or off.
- Supports basic OBJ features and models/textures can be imported with a config file or command-line arguments.
### Lighting model:
- Phong lighting using diffuse, specular and ambient occlusion textures.
  
#### Scene was built in engine using the model transformation tools I implemented:<img src="https://cdnb.artstation.com/p/assets/images/images/014/257/445/large/sebastian-kopacz-chessboard02.jpg?1543227840" width="400" /> <img src="https://cdna.artstation.com/p/assets/images/images/014/257/446/large/sebastian-kopacz-chessboard.jpg?1543226413" width="400" />

  
### Credits:
- All models and textures shown in the image were provided to us by the TA as part of the course.
- Regarding the software implementation the following resources were invaluable: 
   - For understanding OpenGL: https://learnopengl.com
   - For input: http://www.glfw.org/docs/latest/input_guide.html
   - For the window: http://www.glfw.org/docs/latest/window_guide.html
   - For being able to select models by clicking on them: https://en.wikibooks.org/wiki/OpenGL_Programming/Object_selection
---
## Assignment 4: Whitted Ray Tracer
  
### Features:
- Ray intersection test for spheres and triangles.
- Functional shadow, reflection, refraction, and diffuse bounces.
- Gamma correction.
- Procedural textures.
- Directional and point lights.
- Supports basic OBJ features and models can be loaded with a config file.
  
#### My custom scene: <img src="https://cdna.artstation.com/p/assets/images/images/014/259/400/large/sebastian-kopacz-custom.jpg?1543234486" width="400" />

#### Default Cornell box: <img src="https://cdnb.artstation.com/p/assets/images/images/014/259/407/large/sebastian-kopacz-default.jpg?1543234451" width="400" />

### Credits:
- All models either made by me or specified in the assignment description.
- Most of the ray tracer code was based on https://www.scratchapixel.com 
---