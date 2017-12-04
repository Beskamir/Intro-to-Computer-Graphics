//
// This will store camera data within the scene
//

#include "Camera.h"

Camera::Camera(vec3 pos, vec3 target, vec3 upguide, float fov, float aspectRatio) {
    cameraOrigin=pos;

    cameraForward=normalize(target-cameraOrigin);
    cameraRight=normalize(cross(cameraForward,upguide));
    cameraUp=cross(cameraRight,cameraForward);

    cameraSize.x = tan(fov);
    cameraSize.y = cameraSize.x * aspectRatio;

}

Ray Camera::generateRay(vec2 point) {
    vec3 direction = cameraForward + (point.x*cameraSize.x*cameraRight)+(point.y*cameraSize.y*cameraUp);
    return Ray(cameraOrigin,normalize(direction));
}
