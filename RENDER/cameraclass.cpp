#include "cameraclass.h"

Camera::Camera() {
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;
}


Camera::Camera(const Camera& other)
{

}


Camera::~Camera()
{

}


void Camera::SetPosition(float x, float y, float z) {
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	return;
}


void Camera::SetRotation(float x, float y, float z) {
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	return;
}


Math::Vec::VecF3 Camera::GetPosition() {
	return Math::Vec::VecF3(m_positionX, m_positionY, m_positionZ);
}


Math::Vec::VecF3 Camera::GetRotation() {
	return Math::Vec::VecF3(m_rotationX, m_rotationY, m_rotationZ);
}

void Camera::Render() {
    Math::Vec::VecF3 up(0.0f, 1.0f, 0.0f);
    Math::Vec::VecF3 position(m_positionX, m_positionY, m_positionZ);
    Math::Vec::VecF3 lookAt(0.0f, 0.0f, 1.0f);

    float pitch = m_rotationX * 0.0174532925f;
    float yaw   = m_rotationY * 0.0174532925f;
    float roll  = m_rotationZ * 0.0174532925f;

    Math::Mat::MatF44 rotationMatrix = Math::Mat::RotationRollPitchYaw(pitch, yaw, roll);

    Math::Vec::VecF4 lookAt4 = rotationMatrix * Math::Vec::VecF4(lookAt, 0.0f);
    Math::Vec::VecF4 up4     = rotationMatrix * Math::Vec::VecF4(up, 0.0f);

    Math::Vec::VecF3 transformedLookAt = Math::Vec::VecF3(lookAt4.x, lookAt4.y, lookAt4.z);
    Math::Vec::VecF3 transformedUp     = Math::Vec::VecF3(up4.x, up4.y, up4.z);

    transformedLookAt = position + transformedLookAt;

    m_viewMatrix = Math::Mat::LookAtLH(position, transformedLookAt, transformedUp);
}


void Camera::GetViewMatrix(Math::Mat::MatF44& viewMatrix) {
	viewMatrix = m_viewMatrix;
}

void Camera::RenderBaseViewMatrix() {
    // 向上向量
    Math::Vec::VecF3 up(0.0f, 1.0f, 0.0f);

    // 相机位置
    Math::Vec::VecF3 position(m_positionX, m_positionY, m_positionZ);

    // 初始朝向（本地空间中向前）
    Math::Vec::VecF3 lookAt(0.0f, 0.0f, 1.0f);

    // 欧拉角转换为弧度
    float pitch = m_rotationX * 0.0174532925f;  // X轴
    float yaw   = m_rotationY * 0.0174532925f;  // Y轴
    float roll  = m_rotationZ * 0.0174532925f;  // Z轴

    // 创建旋转矩阵
    Math::Mat::MatF44 rotationMatrix = Math::Mat::RotationRollPitchYaw(pitch, yaw, roll);

    // 旋转方向向量（w = 0 表示不平移）
    Math::Vec::VecF4 lookAt4 = rotationMatrix * Math::Vec::VecF4(lookAt, 0.0f);
    Math::Vec::VecF4 up4     = rotationMatrix * Math::Vec::VecF4(up,     0.0f);

    Math::Vec::VecF3 transformedLookAt(lookAt4.x, lookAt4.y, lookAt4.z);
    Math::Vec::VecF3 transformedUp(up4.x, up4.y, up4.z);

    // 变换后的视线目标点 = 相机位置 + 方向向量
    transformedLookAt = position + transformedLookAt;

    // 构建视图矩阵（左手坐标系）
    m_baseViewMatrix = Math::Mat::LookAtLH(position, transformedLookAt, transformedUp);
}


void Camera::GetBaseViewMatrix(Math::Mat::MatF44 & viewMatrix) {
	viewMatrix = m_baseViewMatrix;
	return;
}


void Camera::RenderReflection(float height) {
    // Up 向量始终为世界上方向
    Math::Vec::VecF3 up(0.0f, 1.0f, 0.0f);

    // 计算反射后的相机位置（以某个高度为反射面）
    Math::Vec::VecF3 position(m_positionX, -m_positionY + (height * 2.0f), m_positionZ);

    // 默认观察方向为向前 (Z+)
    Math::Vec::VecF3 lookAt(0.0f, 0.0f, 1.0f);

    // 将旋转角从角度转换为弧度（注意 pitch 是反转的）
    float pitch = (-m_rotationX) * 0.0174532925f;
    float yaw   =  (m_rotationY) * 0.0174532925f;
    float roll  =  (m_rotationZ) * 0.0174532925f;

    // 构建旋转矩阵
    Math::Mat::MatF44 rotationMatrix = Math::Mat::RotationRollPitchYaw(pitch, yaw, roll);

    // 旋转方向向量（w=0）
    Math::Vec::VecF4 lookAt4 = rotationMatrix * Math::Vec::VecF4(lookAt, 0.0f);
    Math::Vec::VecF4 up4     = rotationMatrix * Math::Vec::VecF4(up,     0.0f);

    // 提取 vec3f 分量
    Math::Vec::VecF3 transformedLookAt(lookAt4.x, lookAt4.y, lookAt4.z);
    Math::Vec::VecF3 transformedUp(up4.x, up4.y, up4.z);

    // lookAt 是从位置向外看的方向
    transformedLookAt = position + transformedLookAt;

    // 构建视图矩阵
    m_reflectionViewMatrix = Math::Mat::LookAtLH(position, transformedLookAt, transformedUp);
}


void Camera::GetReflectionViewMatrix(Math::Mat::MatF44& reflectionViewMatrix) {
	reflectionViewMatrix = m_reflectionViewMatrix;
	return;
}

void Camera::Move(float forward, float right, float vertical) noexcept {
    float yaw = m_rotationY * 3.1415926535f / 180.0f; // XM_PI

    // 基于 yaw 计算前方向和右方向（单位向量）
    Math::Vec::VecF3 forwardVec(std::sinf(yaw), 0.0f, std::cosf(yaw));
    Math::Vec::VecF3 rightVec  (std::cosf(yaw), 0.0f, -std::sinf(yaw));
    Math::Vec::VecF3 upVec     (0.0f, 1.0f, 0.0f); // 垂直方向

    // 组合三向移动
    Math::Vec::VecF3 moveVec = forwardVec * forward + rightVec * right + upVec * vertical;

    // 更新相机位置
    m_positionX += moveVec.x;
    m_positionY += moveVec.y;
    m_positionZ += moveVec.z;
}

void Camera::RotateByMouse(float dx, float dy) noexcept {
	constexpr float sensitivity = 0.12f;

	m_rotationY += dx * sensitivity;
	m_rotationX += dy * sensitivity;

	// 限制俯仰角
	if (m_rotationX > 89.0f)  m_rotationX = 89.0f;
	if (m_rotationX < -89.0f) m_rotationX = -89.0f;
}