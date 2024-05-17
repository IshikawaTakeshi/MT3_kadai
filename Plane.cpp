#include "Plane.h"
#include "Mymath/MatrixMath.h"
#include "MyMath/MyMath.h"
#include "Novice.h"

#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG

Plane::Plane() {
	plane_.normal = { 0.0f,1.0f,0.0f };
	plane_.distance = 1.0f;
	centerPos_ = MyMath::Multiply(plane_.distance, plane_.normal);
	color_ = 0xffffffff;
	worldMatrix_ = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, centerPos_);
}

Plane::~Plane() {}

void Plane::Update() {
	worldMatrix_ = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, centerPos_);

#ifdef _DEBUG
	ImGui::Begin("Window::Sphere");
	ImGui::DragFloat3("PlaneTranslate", &centerPos_.x, 0.01f);
	plane_.normal = MyMath::Normalize(plane_.normal);
	ImGui::DragFloat3("PlaneDistance", &plane_.distance, 0.01f);
	ImGui::End();
#endif // _DEBUG
}

void Plane::Draw(const PlaneData& plane, const Matrix4x4& viewPrjection,
	const Matrix4x4& viewport) {

	
	Vector3 perpendiculars[4];
	perpendiculars[0] = MyMath::Normalize(MyMath::Perpendicular(plane.normal));
	perpendiculars[1] = { -perpendiculars[0].x, -perpendiculars[0].y,-perpendiculars[0].z };
	perpendiculars[2] = MyMath::Cross(plane.normal, perpendiculars[0]);
	perpendiculars[3] = { -perpendiculars[2].x, -perpendiculars[2].y,-perpendiculars[2].z };

	Vector3 points[4];
	for (int32_t index = 0; index < 4; index++) {
		Vector3 extend = MyMath::Multiply(2.0f, perpendiculars[index]);
		Vector3 point = MyMath::Add(centerPos_, extend);
		points[index] = MatrixMath::Transform(MatrixMath::Transform(point, viewPrjection), viewport);
	}

	Novice::DrawLine(
		static_cast<int>(points[0].x),
		static_cast<int>(points[0].y),
		static_cast<int>(points[1].x),
		static_cast<int>(points[1].y),
		color_);
	Novice::DrawLine(
		static_cast<int>(points[1].x),
		static_cast<int>(points[1].y), 
		static_cast<int>(points[2].x),
		static_cast<int>(points[2].y),
		color_);
	Novice::DrawLine(
		static_cast<int>(points[2].x),
		static_cast<int>(points[2].y),
		static_cast<int>(points[3].x),
		static_cast<int>(points[3].y),
		color_);
	Novice::DrawLine(
		static_cast<int>(points[3].x),
		static_cast<int>(points[3].y),
		static_cast<int>(points[0].x),
		static_cast<int>(points[0].y),
		color_);


}

