#pragma once
#include "../glm/vec3.hpp"
#include "../glm/ext.hpp"

/*Class for a 3D camera with projection and view matrices*/
class Camera
{
public:
	Camera(glm::vec3 pos, glm::vec3 lookAt);
	Camera(glm::vec3 pos, float pitch, float yaw);
	Camera(glm::vec3 pos);
	~Camera();
	virtual void onFixedUpdate(float timeStep);
	virtual void onUpdate(float ptnt);
	glm::vec3 getPosition() { return position; }
	glm::vec3 getLerpPosition(float ptnt) { return prevTickPosition + (position - prevTickPosition) * ptnt; }
	float getYaw() { return yaw; }
	float getPitch() { return pitch; }
	void lookAt(glm::vec3 pos, float ptnt = 1.0F);

	/*Update the directional vectors of the camera based on position rotations. ptnt = percentage to next tick, for interpolating*/
	void updateVectors(float ptnt = 1.0F);

	glm::mat4 getViewMatrix() { return viewMatrix; }
	glm::mat4 getProjectionMatrix() { return projectionMatrix; }
	void setFov(float fov);
	void setNearPlane(float np);
	void setFarPlane(float fp);
	void setPos(glm::vec3 newPos);
	void addPos(glm::vec3 p);
	void moveFowards(float distance);
	void moveUp(float distance);
	void strafeRight(float distance);
	void rotatePitch(float degrees);
	glm::vec3 getCamPos() const { return position; }
	glm::vec3 getCamFrontVec() const { return frontVec; }
	void rotateYaw(float degrees) { yaw += degrees; }
	/*Calcultes projection matrix. Should be called each time the aspect ratio, fov or draw distance changes.*/
	void makeProjectionMatrix();
	void setAspectRatio(float ar) { aspectRatio = ar; makeProjectionMatrix(); }
protected:
	float farPlane = 1000.0F;
	float nearPlane = 0.1F;
	float fov = 60.0F;
	float yaw = -90.0F;
	float pitch = 0;
	glm::vec3 prevTickPosition;
	glm::vec3 position;
	glm::vec3 flatFrontVec;
	glm::vec3 frontVec;
	glm::vec3 rightVec;
	const glm::vec3 upVec = {0,1,0};
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	float aspectRatio = 1.0F;
};