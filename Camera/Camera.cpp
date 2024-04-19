#include "Camera.h"
#include "MyMath/MatrixMath.h"

#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG

Camera::Camera() {
	cameraTranslate_ = { 0.0f,1.9f,-6.49f };
	cameraRotate_ = { 0.26f,0.0f,0.0f };
	worldMatrix_ = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate_, cameraTranslate_);
	viewMatrix_ = MatrixMath::Inverse(worldMatrix_);
}

Camera::~Camera() {
}

void Camera::Update() {
	worldMatrix_ = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate_, cameraTranslate_);
	viewMatrix_ = MatrixMath::Inverse(worldMatrix_);

#ifdef _DEBUG
	ImGui::Begin("Window::Camera");
	ImGui::DragFloat3("CameraTranslate",&cameraTranslate_.x, 0.01f);
	ImGui::DragFloat3("CameraRotate",&cameraRotate_.x, 0.001f);
	ImGui::End();
#endif
}

void Camera::Draw() {
}
