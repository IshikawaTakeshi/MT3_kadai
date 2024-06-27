#include "Triangle.h"
#include "MyMath/MatrixMath.h"
#include "MyMath/MyMath.h"
#include "Segment.h"
#include "Novice.h"

#include <imgui.h>

void Triangle::Initialize() {
	normal_ = { 0.0f,0.0f,-1.0f };
	distance_ = 1.0f;
	centerPos_ = MyMath::Multiply(distance_, normal_);
	vertices_[0] = { -1.0f,0.0f,0.0f };
	vertices_[1] = { 0.0f,1.0f,0.0f };
	vertices_[2] = { 1.0f,0.0f,0.0f };
	worldMatrix_ = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, centerPos_);
}

void Triangle::Update() {


	//ワールド行列の更新
	worldMatrix_ = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, centerPos_);

	//imgui
	ImGui::Begin("Triangle");
	ImGui::DragFloat3("vertices1", &vertices_[0].x, 0.01f);
	ImGui::DragFloat3("vertices2", &vertices_[1].x, 0.01f);
	ImGui::DragFloat3("vertices3", &vertices_[2].x, 0.01f);
	ImGui::DragFloat3("normal", &normal_.x, 0.01f);
	normal_ = MyMath::Normalize(normal_);
	ImGui::DragFloat("Distance", &distance_, 0.01f);
	ImGui::End();
}

void Triangle::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, Segment* seg) {

	Vector3 screenSegOrigin;
	screenSegOrigin = MatrixMath::Transform(MatrixMath::Transform(seg->GetOrigin(), viewProjectionMatrix), viewportMatrix);

	Vector3 screenVertices[3];
	screenVertices[0] = MatrixMath::Transform(MatrixMath::Transform(vertices_[0], viewProjectionMatrix), viewportMatrix);
	screenVertices[1] = MatrixMath::Transform(MatrixMath::Transform(vertices_[1], viewProjectionMatrix), viewportMatrix);
	screenVertices[2] = MatrixMath::Transform(MatrixMath::Transform(vertices_[2], viewProjectionMatrix), viewportMatrix);

	Novice::DrawTriangle(
		static_cast<int>(screenVertices[0].x),
		static_cast<int>(screenVertices[0].y),
		static_cast<int>(screenVertices[1].x),
		static_cast<int>(screenVertices[1].y),
		static_cast<int>(screenVertices[2].x),
		static_cast<int>(screenVertices[2].y),
		0xffffffff,
		kFillModeWireFrame
	);

	Novice::DrawTriangle(
		static_cast<int>(screenVertices[2].x),
		static_cast<int>(screenVertices[2].y),
		static_cast<int>(screenVertices[1].x),
		static_cast<int>(screenVertices[1].y),
		static_cast<int>(screenSegOrigin.x),
		static_cast<int>(screenSegOrigin.y),
		0x0000ffff,
		kFillModeWireFrame
	);
}

