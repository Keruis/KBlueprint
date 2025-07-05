#include "CameraController.h"

CameraController::CameraController(Camera *camera)
    : m_camera(camera)
{

}

void CameraController::Update(Input &input, float deltaTime) noexcept {
    auto pos = m_camera->GetPosition();
    float speed = m_moveSpeed * deltaTime;

    if (input.IsKeyDown(XK_w) || input.IsKeyDown(XK_W)) pos.y -= speed;
    if (input.IsKeyDown(XK_s) || input.IsKeyDown(XK_S)) pos.y += speed;
    if (input.IsKeyDown(XK_a) || input.IsKeyDown(XK_A)) pos.x -= speed;
    if (input.IsKeyDown(XK_d) || input.IsKeyDown(XK_D)) pos.x += speed;
    if (input.IsKeyDown(XK_Shift_L) || input.IsKeyDown(XK_Shift_R)) pos.z += speed;
    if (input.IsKeyDown(XK_space)) pos.z -= speed;

    m_camera->SetPosition(pos.x, pos.y, pos.z);
}