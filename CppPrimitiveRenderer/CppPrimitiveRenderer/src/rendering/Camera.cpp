#include "Camera.h"
Camera::Camera(glm::vec3 pos, glm::vec3 lookAt) : position(pos), prevTickPosition(pos)
{
	this->lookAt(lookAt);
	makeProjectionMatrix();
}

Camera::Camera(glm::vec3 pos, float pitch, float yaw) : position(pos), prevTickPosition(pos), pitch(pitch), yaw(yaw)
{
	updateVectors();
	makeProjectionMatrix();
}

Camera::Camera(glm::vec3 pos) : position(pos), prevTickPosition(pos), pitch(0), yaw(-90)
{
	updateVectors();
	makeProjectionMatrix();
}

Camera::~Camera()
{

}

void Camera::onFixedUpdate(float timeStep)
{
	prevTickPosition = position;
}

void Camera::onUpdate(float ptnt)
{
	updateVectors(ptnt);
}

void Camera::lookAt(glm::vec3 pos, float ptnt /*= 1.0F*/)
{
	frontVec = glm::normalize(pos - getLerpPosition(ptnt));
	pitch = asin(frontVec.y);
	yaw = atan2(frontVec.x, frontVec.z);
	updateVectors(ptnt);
}

void Camera::updateVectors(float ptnt /*= 1.0F*/)
{
	glm::vec3 camDirectionVector;
	camDirectionVector.x = cos(glm::radians(yaw));
	camDirectionVector.y = 0;
	camDirectionVector.z = sin(glm::radians(yaw));
	flatFrontVec = glm::normalize(camDirectionVector);
	camDirectionVector.x *= cos(glm::radians(pitch));
	camDirectionVector.y = sin(glm::radians(pitch));
	camDirectionVector.z *= cos(glm::radians(pitch));
	frontVec = glm::normalize(camDirectionVector);
	rightVec = glm::normalize(glm::cross(frontVec, upVec));
	viewMatrix = glm::lookAt(getLerpPosition(ptnt), getLerpPosition(ptnt) + frontVec, upVec);
}

void Camera::setFov(float fov)
{
	this->fov = fov;
	makeProjectionMatrix();
}

void Camera::setNearPlane(float np)
{
	nearPlane = np;
	makeProjectionMatrix();
}

void Camera::setFarPlane(float fp)
{
	farPlane = fp;
	makeProjectionMatrix();
}

void Camera::setPos(glm::vec3 newPos)
{
	position = newPos;
}

void Camera::addPos(glm::vec3 p)
{
	position += p;
}

void Camera::moveFowards(float distance)
{
	position += distance * flatFrontVec;
}

void Camera::moveUp(float distance)
{
	position.y += distance;
}

void Camera::strafeRight(float distance)
{
	position += glm::normalize(glm::cross(frontVec, upVec)) * distance;
}

void Camera::rotatePitch(float degrees)
{
	pitch += degrees;
	if (pitch >= 90) { pitch = 89.9F; return; }
	if (pitch <= -90)pitch = -89.9F;
}

void Camera::makeProjectionMatrix()
{
	projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}
