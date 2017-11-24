#version 410
//Shader heavily based on: https://learnopengl.com/code_viewer.php?code=lighting/basic_lighting&type=fragment

//in vec3 vertexColor;
in vec3 Normal;
in vec3 modelPos;
in vec2 uvCoord;

out vec4 FragmentColour;

struct TextureData{
    sampler2D diffuse;
    sampler2D ambiantOcculusion;
    sampler2D specular;
};
struct UseTexture{
    bool diffuse;
    bool ambiantOcculusion;
    bool specular;
};
struct Material{
    vec3 diffuse;
    vec3 ambiantOcculusion;
    vec3 specular;
};

// Texture samplers
//uniform sampler2D texture1;
//uniform int imageStyle=0;
//uniform int useTexture=1;
uniform vec3 diffuseDefault = vec3(0.75f,0.25f,0.0f);
uniform vec3 lighting = vec3(1.0f,1.0f,1.0f);
uniform vec3 lightPos = vec3(5.0f,5.0f,5.0f);
uniform vec3 viewPos;
uniform TextureData textureData;
uniform UseTexture useTexture;
uniform Material material = {vec3(0.75f,0.25f,0.0f),vec3(0.75f,0.25f,0.0f),vec3(0.75f,0.25f,0.0f)};
//material.diffuse=vec3(0.75f,0.25f,0.0f);

//declare functions
vec3 getAmbientLighting(vec3 diffuseColor);
vec3 getDiffuseLighting();
vec3 getSpecularLighting();

//Globals
vec3 norm = normalize(Normal);
vec3 lightDirection = normalize(lightPos-modelPos);


void main() {
    vec3 textureColor = vec3(texture(textureData.diffuse,uvCoord));
    vec3 diffuseColor;
    if(useTexture.diffuse){
        diffuseColor = textureColor;
    }
    else{
        diffuseColor = material.diffuse;
//        diffuseColor = material.diffuse;
    }

    vec3 finalColor = (getAmbientLighting(diffuseColor)+getDiffuseLighting()+getSpecularLighting()) * diffuseColor;

    FragmentColour=vec4(finalColor,1.0f);

//    FragmentColour=diffuseData;
}

//Get the ambient lighting of the object
vec3 getAmbientLighting(vec3 diffuseColor){
    vec3 ambientValue;
    if(false){
        ambientValue = vec3(texture(textureData.ambiantOcculusion,uvCoord));
    }
    else{
        ambientValue = vec3(0.25f);
    }
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