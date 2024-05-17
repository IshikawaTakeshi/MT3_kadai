#include "Camera.h"
#include "MyMath/MatrixMath.h"
#include "MyMath/MyMath.h"
#include "Novice.h"

#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG

Camera::Camera() {
	cameraTranslate_ = { 0.0f,1.9f,-6.49f };
	cameraRotate_ = { 0.26f,0.0f,0.0f };
	cameraScale_ = { 1.0f,1.0f,1.0f };
	worldMatrix_ = MatrixMath::MakeAffineMatrix(cameraScale_, cameraRotate_, cameraTranslate_);
	viewMatrix_ = MatrixMath::Inverse(worldMatrix_);
}

Camera::~Camera() {
}

void Camera::Update() {
	//int mousePosX;
	//int mousePosY;
	////原点との距離
	////float length = MyMath::Length(cameraTranslate_);
	////cameraRotate_.x = length * std::cos()
	//Novice::GetMousePosition(&mousePosX - 640, &mousePosY -360);

	//if (Novice::IsPressMouse(1)) {
	//	cameraRotate_ = { 0.26f, 0.0f, 0.0f };
	//}
	//cameraTranslate_.z += float(Novice::GetWheel() / 10 * float(M_PI) / 180);
	//worldMatrix_ = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate_, cameraTranslate_);
	//viewMatrix_ = MatrixMath::Inverse(worldMatrix_);
	//

	
#ifdef _DEBUG
	ImGui::Begin("Window::Camera");
	ImGui::DragFloat3("CameraTranslate",&cameraTranslate_.x, 0.01f);
	ImGui::DragFloat3("CameraRotate",&cameraRotate_.x, 0.001f);
	ImGui::End();
#endif
}

void Camera::Draw() {
}
