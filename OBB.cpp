#include "OBB.h"
#include "MyMath/MatrixMath.h"
#include "AABB.h"
#include "Novice.h"

#include <imgui.h>


void OBB::Initialize(Vector3 centerPos, Vector3 orientations[3], Vector3 size) {

	centerPos_ = centerPos;
	orientation_[0] = orientations[0];
	orientation_[1] = orientations[1];
	orientation_[2] = orientations[2];
	size_ = size;
	rotation_ = { 0.0f,0.0f,0.0f };
	worldMatrix_ = MatrixMath::MakeAffineMatrix(size_, { 0,0,0 }, centerPos_);
	rotationMatrix_ = MatrixMath::MakeIdentity4x4();

	color_ = 0xffffffff;
}

void OBB::Update() {

	rotationMatrix_ = MatrixMath::MakeRotateMatrix(rotation_);

	orientation_[0].x = rotationMatrix_.m[0][0];
	orientation_[0].y = rotationMatrix_.m[0][1];
	orientation_[0].z = rotationMatrix_.m[0][2];

	orientation_[1].x = rotationMatrix_.m[1][0];
	orientation_[1].y = rotationMatrix_.m[1][1];
	orientation_[1].z = rotationMatrix_.m[1][2];

	orientation_[2].x = rotationMatrix_.m[2][0];
	orientation_[2].y = rotationMatrix_.m[2][1];
	orientation_[2].z = rotationMatrix_.m[2][2];

	worldMatrix_ = MatrixMath::MakeAffineMatrix(size_, rotation_, centerPos_);
}

void OBB::UpdateImGui() {
	ImGui::Text("OBB");
	ImGui::DragFloat3("Pos", &centerPos_.x, 0.01f);
	ImGui::DragFloat3("Size", &size_.x, 0.01f);
	ImGui::SliderAngle("rotateX", &rotation_.x);
	ImGui::SliderAngle("rotateY", &rotation_.y);
	ImGui::SliderAngle("rotateZ", &rotation_.z);
	ImGui::DragFloat3("Orientation0", &orientation_[0].x, 0.01f);
	ImGui::DragFloat3("Orientation1", &orientation_[1].x, 0.01f);
	ImGui::DragFloat3("Orientation2", &orientation_[2].x, 0.01f);
}

void OBB::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	
	Vector3 vertices[8];

	// OBBの8つの頂点を計算
	Vector3 halfSizeX = orientation_[0] * size_.x;
	Vector3 halfSizeY = orientation_[1] * size_.y;
	Vector3 halfSizeZ = orientation_[2] * size_.z;

	vertices[0] = centerPos_ - halfSizeX - halfSizeY - halfSizeZ;
	vertices[1] = centerPos_ + halfSizeX - halfSizeY - halfSizeZ;
	vertices[2] = centerPos_ + halfSizeX + halfSizeY - halfSizeZ;
	vertices[3] = centerPos_ - halfSizeX + halfSizeY - halfSizeZ;

	vertices[4] = centerPos_ - halfSizeX - halfSizeY + halfSizeZ;
	vertices[5] = centerPos_ + halfSizeX - halfSizeY + halfSizeZ;
	vertices[6] = centerPos_ + halfSizeX + halfSizeY + halfSizeZ;
	vertices[7] = centerPos_ - halfSizeX + halfSizeY + halfSizeZ;

	// 各頂点をスクリーン座標に変換
	Vector3 screenVertices[8];
	for (int i = 0; i < 8; i++) {
		screenVertices[i] =
			MatrixMath::Transform(MatrixMath::Transform(vertices[i], viewProjectionMatrix), viewportMatrix);
	}

	// OBBのエッジを描画
	int edges[12][2] = {
		{0, 1}, {1, 2}, {2, 3}, {3, 0},
		{4, 5}, {5, 6}, {6, 7}, {7, 4},
		{0, 4}, {1, 5}, {2, 6}, {3, 7}
	};

	for (int i = 0; i < 12; ++i) {
		Novice::DrawLine(
			static_cast<int>(screenVertices[edges[i][0]].x),
			static_cast<int>(screenVertices[edges[i][0]].y),
			static_cast<int>(screenVertices[edges[i][1]].x),
			static_cast<int>(screenVertices[edges[i][1]].y),
			0xffffffff);
	}
}
