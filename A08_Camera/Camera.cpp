#include "Camera.h"

Camera::Camera()
{
	cameraPosition = vector3(0.0f, 0.0f, -10.0f);
	cameraTarget = vector3(0.0f, 0.0f, 0.0f);
	cameraUp = vector3(0.0f, 1.0f, 0.0f);
	viewMatrix = glm::lookAt(cameraPosition, cameraTarget, cameraUp);
	projectionMatrix = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
	viewVector = cameraPosition - cameraTarget;
}

Camera::~Camera()
{
}

// Methods
matrix4 Camera::GetView(void) {
	return viewMatrix;
} //Should get the View Matrix from your class

matrix4 Camera::GetProjection(bool bOrtographic) {
	//m_m4Projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
	//m_m4Projection = glm::ortho(-10.80f, 10.80f, -7.68f, 7.68f, 0.01f, 15.0f);
	if (bOrtographic)
	{
		projectionMatrix = glm::ortho(-10.80f, 10.80f, -7.68f, 7.68f, 0.01f, 15.0f);
	}
	else {
		projectionMatrix = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
	}

	return projectionMatrix;
} //Should get the Projection Matrix from your class, this function should let me choose between a Perspective or an Orthographic projection depending on the bool argument.

void Camera::SetPosition(vector3 v3Position) {
	cameraPosition = v3Position;
	//m_m4View = glm::lookAt(glm::vec3(0.0f, 0.0f, 15.0f), glm::vec3(0.0f, 0.0f, 14.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}//Sets the position of the camera

void Camera::SetTarget(vector3 v3Target) {
	cameraTarget = v3Target;
}//Sets the target of the camera

void Camera::SetUp(vector3 v3Up) {
	cameraUp = v3Up;
}//Sets the up vector of the camera

void Camera::MoveForward(float fIncrement) {

	vector3 newPos = glm::normalize(viewVector);
	newPos *= fIncrement;
	cameraPosition += newPos;
	vector3 increment = vector3(0.0f, 0.0f, fIncrement);

	//viewVector = cameraPosition - cameraTarget;
	viewMatrix = glm::translate(viewMatrix, increment);
}//Move the camera forward (or backwards) depending on the “view vector”

void Camera::MoveSideways(float fIncrement) {

	vector3 viewNorm = glm::normalize(viewVector);
	vector3 upNorm = glm::normalize(cameraUp);
	vector3 rightVec = glm::cross(viewNorm, upNorm);
	rightVec *= fIncrement;
	cameraPosition += rightVec;
	//viewVector = cameraPosition - cameraTarget;
	vector3 increment = vector3(fIncrement, 0.0f, 0.0f);

	viewMatrix = glm::translate(viewMatrix, increment);
}//Move the camera based on the “right” vectordepending on the “view vector”

void Camera::MoveVertical(float fIncrement) {
	vector3 newPos = glm::normalize(cameraUp);
	//newPos = glm::rotate(newPos, vector3(0.0f, 0.0f, 1.0f));
	newPos *= fIncrement;
	cameraPosition += newPos;
	//viewVector = cameraPosition - cameraTarget;
	vector3 increment = vector3(0.0f, fIncrement, 0.0f);

	viewMatrix = glm::translate(viewMatrix, increment);
}//Move the camera up or down depending on the “up vector”

void Camera::ChangePitch(float fIncrement) {
	glm::quat pitchQuat1 = glm::angleAxis(0.0f, vector3(1.0f, 0.0f, 0.0f));
	glm::quat pitchQuat2 = glm::angleAxis(180.0f, vector3(1.0f, 0.0f, 0.0f));

	glm::quat pitchQuat3 = glm::mix(pitchQuat1, pitchQuat2, fIncrement);

	viewMatrix *= ToMatrix4(pitchQuat3);
}//Orient your camera (meaning the forward and up vectors) changing its angle in x

void Camera::ChangeRoll(float fIncrement) {
	glm::quat rollQuat1 = glm::angleAxis(0.0f, vector3(0.0f, 0.0f, 1.0f));
	glm::quat rollQuat2 = glm::angleAxis(180.0f, vector3(0.0f, 0.0f, 1.0f));

	glm::quat rollQuat3 = glm::mix(rollQuat1, rollQuat2, fIncrement);

	viewMatrix *= ToMatrix4(rollQuat3);
}//Orient your camera (meaning the forward and up vectors) changing its angle in z

void Camera::ChangeYaw(float fIncrement) {
	glm::quat yawQuat1 = glm::angleAxis(0.0f, vector3(0.0f, 1.0f, 0.0f));
	glm::quat yawQuat2 = glm::angleAxis(180.0f, vector3(0.0f, 1.0f, 0.0f));

	glm::quat yawQuat3 = glm::mix(yawQuat1, yawQuat2, fIncrement);

	viewMatrix *= ToMatrix4(yawQuat3);
}//Orient your camera (meaning the forward and up vectors) changing its angle in y