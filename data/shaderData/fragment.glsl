#version 410
//Shader heavily based on: https://learnopengl.com/code_viewer.php?code=lighting/basic_lighting&type=fragment

//in vec3 vertexColor;
in vec3 Normal;
in vec3 modelPos;
in vec2 uvCoord;

out vec4 FragmentColour;

// Texture samplers
//uniform sampler2D texture1;
//uniform int imageStyle=0;
//uniform int useTexture=1;
uniform vec3 diffuseColor=vec3(0.75f,0.25f,0.0f);
uniform vec3 lighting = vec3(1.0f,1.0f,1.0f);
uniform vec3 lightPos = vec3(5.0f,5.0f,5.0f);
uniform vec3 viewPos;

//declare functions
vec3 getAmbientLighting();
vec3 getDiffuseLighting();
vec3 getSpecularLighting();
//Globals
vec3 norm = normalize(Normal);
vec3 lightDirection = normalize(lightPos-modelPos);


void main() {

    vec3 finalColor = (getAmbientLighting()+getDiffuseLighting()+getSpecularLighting()) * diffuseColor;

    FragmentColour=vec4(finalColor,1.0f);
}

//Get the ambient lighting of the object
vec3 getAmbientLighting(){
    float ambientValue = 0.25f;
    return ambientValue * lighting;
}

//Get diffuse lighting
vec3 getDiffuseLighting(){
    vec3 lightDirection = normalize(lightPos-modelPos);
    float difference = max(dot(norm, lightDirection),0.0);
    return difference * lighting;
}

vec3 getSpecularLighting(){
    float specStrength=0.5f;
    vec3 viewDir = normalize(viewPos - modelPos);
    vec3 reflectDir = reflect(-lightDirection,norm);
    float specular = pow(max(dot(viewDir,reflectDir),0.0),32);
    return specStrength * specular * lighting;
}