#include "Camera.h"
#include "MyMath/MatrixMath.h"

#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG

Camera::Camera() {
	cameraTranslate_ = { 3.0f,1.9f,-4.49f };
	cameraRotate_ = { 0.26f,-0.6f,0.0f };
	worldMatrix_ = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate_, cameraTranslate_);
	viewMatrix_ = MatrixMath::Inverse(worldMatrix_);
	projectionMatrix_ = MatrixMath::MakePerspectiveFovMatrix(0.45f, 1280.0f / 720.0f, 0.1f, 100.0f);
	viewProjectionMatrix_ = MatrixMath::Multiply(viewMatrix_, projectionMatrix_);
	viewportMatrix_ = MatrixMath::MakeViewportMatrix(0, 0, 1280.0f, 720.0f, 0.0f, 1.0f);
}

Camera::~Camera() {
}

void Camera::Update() {

	//アフィン行列の更新
	worldMatrix_ = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate_, cameraTranslate_);

	viewMatrix_ = MatrixMath::Inverse(worldMatrix_);
	//ビュープロジェクションの更新
	viewProjectionMatrix_ = MatrixMath::Multiply(viewMatrix_, projectionMatrix_);

#ifdef _DEBUG
	ImGui::Begin("Window::Camera");
	ImGui::DragFloat3("CameraTranslate",&cameraTranslate_.x, 0.01f);
	ImGui::DragFloat3("CameraRotate",&cameraRotate_.x, 0.001f);
	ImGui::End();
#endif
}

void Camera::Draw() {
}
