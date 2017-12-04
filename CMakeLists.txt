cmake_minimum_required(VERSION 3.7)
project(Assignment4)

set(PROJECT_NAME Assignment4) #Macro the project name
set(CMAKE_CXX_STANDARD 11)


#Indicate that OpenCL is needed
find_package(OpenGL REQUIRED)

#The source files for the project
set(SOURCE_FILES src/Scene/Models/Sphere.cpp src/Scene/Models/Sphere.h src/Scene/Models/Plane.cpp src/Scene/Models/Plane.h src/Scene/Models/Mesh.cpp src/Scene/Models/Mesh.h src/main.cpp src/Raytracer/RayTracer.cpp src/Raytracer/RayTracer.h src/Scene/Camera.cpp src/Scene/Camera.h src/Raytracer/ImageData.cpp src/Raytracer/ImageData.h src/Scene/Scene.cpp src/Scene/Scene.h src/Raytracer/Ray.cpp src/Raytracer/Ray.h src/Raytracer/Color.cpp src/Raytracer/Color.h src/Raytracer/Intersection.cpp src/Raytracer/Intersection.h src/Scene/Model.cpp src/Scene/Model.h src/myMath.h src/Scene/Models/ModelSet.cpp src/Scene/Models/ModelSet.h)

#src/OpenGL/mainOpenGL.cpp src/OpenGL/mainOpenGL.h src/OpenGL/ShaderProgram.cpp src/OpenGL/ShaderProgram.h src/OpenGL/OpenGL_Program.cpp src/OpenGL/OpenGL_Program.h src/OpenGL/Model.cpp src/OpenGL/Model.h src/OpenGL/Camera.cpp src/OpenGL/Camera.h src/OpenGL/Transformations.cpp src/OpenGL/Transformations.h src/OpenGL/Mouse.cpp src/OpenGL/Mouse.h

#src/OpenModel.h src/OpenModel.cpp
#src/ImageTexture.cpp src/ImageTexture.h

#Gets glfw
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(deps/glfw)

#Get glm
option(GLM_TEST_ENABLE ON)
add_subdirectory(deps/glm)

#Get stb
include_directories(deps/stb)

#Include GLEW libraries only if on windows
IF (WIN32)
    set(GLEW_DIR "deps/glew")
    include_directories(${GLEW_DIR}/include)
    add_definitions(-DGLEW_STATIC)
    link_directories(${GLEW_DIR}/lib)
ENDIF()


#Create the executable using the sourcefiles
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

#Link the libraries
IF (WIN32)
    # Include glew32s if on windows
    target_link_libraries(${PROJECT_NAME} glfw glew32s glm ${OPENGL_LIBRARY})
ELSE()
    # don't include glew32s if not on windows
    target_link_libraries(${PROJECT_NAME} glfw glm ${OPENGL_LIBRARY})
ENDIF()

#SET(CMAKE_CXX_FLAGS "-std=c++1y -wall -lglfw -lGL -lOpenGL -lGLEW -pthread -lfreetype")
#SET(CMAKE_CXX_FLAGS "-wall")

set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")