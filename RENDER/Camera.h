#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_

#include "../Math/MMat.h"
#include "../Math/MVec.h"

class Camera {
public:
	Camera();
	Camera(const Camera&);
	~Camera();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	Math::Vec::VecF3 GetPosition();
	Math::Vec::VecF3 GetRotation();

	void Render();
	void GetViewMatrix(Math::Mat::MatF44&);

	void RenderBaseViewMatrix();
	void GetBaseViewMatrix(Math::Mat::MatF44&);

	void RenderReflection(float);
	void GetReflectionViewMatrix(Math::Mat::MatF44&);

	void Move(float, float, float) noexcept;
	void RotateByMouse(float, float) noexcept;

private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	Math::Mat::MatF44 m_viewMatrix;
	Math::Mat::MatF44 m_baseViewMatrix;
	Math::Mat::MatF44 m_reflectionViewMatrix;
};

#endif