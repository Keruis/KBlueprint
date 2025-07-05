#ifndef DEMO_CAMERACONTROLLER_H
#define DEMO_CAMERACONTROLLER_H

#include "Camera.h"
#include "Input.h"
#include "../Math/MMat.h"

class CameraController {
public:
    CameraController(Camera* camera);
    void Update(Input& input, float deltaTime) noexcept;

private:
    Camera* m_camera;
    float m_moveSpeed = 2.5f;
};


#endif //DEMO_CAMERACONTROLLER_H
