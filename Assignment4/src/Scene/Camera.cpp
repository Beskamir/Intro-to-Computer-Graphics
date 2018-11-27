//
// This will store camera data within the scene
//

#include "Camera.h"

Camera::Camera(vec3 pos, vec3 target, vec3 upguide, float fov, float aspectRatio) {
    cameraOrigin=pos;

    //cameraUp = up;
    //cameraForward = -direction;
    //cameraRight = normalize(cross(cameraForward,cameraUp));

    cameraForward=normalize(target-cameraOrigin);
    cameraRight=normalize(cross(cameraForward,upguide));
    cameraUp=cross(cameraRight,cameraForward);
    //cameraUp=vec3(1,0,0);

    //cout<<cameraUp.x<<","<<cameraUp.y<<","<<cameraUp.z<<endl;
    //cout<<cameraRight.x<<","<<cameraRight.y<<","<<cameraRight.z<<endl;
    //cout<<cameraForward.x<<","<<cameraForward.y<<","<<cameraForward.z<<endl;

    auto radianFOV = (float)(fov * acos(-1) / 180.0);
    cameraSize.x = (tan(radianFOV/2));
    cameraSize.y = cameraSize.x * aspectRatio;
}

Ray Camera::generateRay(vec2 point) {
    vec3 direction = cameraForward
                     + (point.x * cameraSize.x * cameraUp)
                     + (point.y * cameraSize.y * cameraRight);
    //vec3 direction = vec3(
    //        point.x * cameraAspectRatio * scalar,
    //        point.y * scalar,
    //        -1.0f
    //);
    //cout<<direction.x<<"\t"<<direction.y<<"\t"<<direction.z<<endl;

    return Ray(cameraOrigin,normalize(direction));
}
