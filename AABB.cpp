#include "AABB.h"
#include "MyMath/MatrixMath.h"
#include "Novice.h"
#include <algorithm>
#include <imgui.h>


void AABB::Initialize(Vector3 min, Vector3 max) {
	min_ = min;
	max_ = max;
	color_ = 0xffffffff;
}

void AABB::Update() {

	min_.x = (std::min)(min_.x, max_.x);
	max_.x = (std::max)(min_.x, max_.x);
	min_.y = (std::min)(min_.y, max_.y);
	max_.y = (std::max)(min_.y, max_.y);
	min_.z = (std::min)(min_.z, max_.z);
	max_.z = (std::max)(min_.z, max_.z);
}

void AABB::UpdateImGui(std::string name) {
	ImGui::Text(name.c_str());
	ImGui::DragFloat3("aabb.min", &min_.x, 0.01f);
	ImGui::DragFloat3("aabb.max", &max_.x, 0.01f);
}

void AABB::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {

	Vector3 vertices[8];
	vertices[0] = Vector3(min_.x, min_.y, min_.z);
	vertices[1] = Vector3(max_.x, min_.y, min_.z);
	vertices[2] = Vector3(min_.x, max_.y, min_.z);
	vertices[3] = Vector3(max_.x, max_.y, min_.z);
	vertices[4] = Vector3(min_.x, min_.y, max_.z);
	vertices[5] = Vector3(max_.x, min_.y, max_.z);
	vertices[6] = Vector3(min_.x, max_.y, max_.z);
	vertices[7] = Vector3(max_.x, max_.y, max_.z);

	Vector3 screenVertices[8];
	for (int i = 0; i < 8; i++) {
		screenVertices[i] =
			MatrixMath::Transform(MatrixMath::Transform(vertices[i], viewProjectionMatrix), viewportMatrix);
	}

	//=========================== 底面 ===========================//

	Novice::DrawLine(
		static_cast<int>(screenVertices[0].x),
		static_cast<int>(screenVertices[0].y),
		static_cast<int>(screenVertices[1].x),
		static_cast<int>(screenVertices[1].y),
		color_
	);

	Novice::DrawLine(
		static_cast<int>(screenVertices[1].x),
		static_cast<int>(screenVertices[1].y),
		static_cast<int>(screenVertices[3].x),
		static_cast<int>(screenVertices[3].y),
		color_
	);

	Novice::DrawLine(
		static_cast<int>(screenVertices[3].x),
		static_cast<int>(screenVertices[3].y),
		static_cast<int>(screenVertices[2].x),
		static_cast<int>(screenVertices[2].y),
		color_
	);

	Novice::DrawLine(
		static_cast<int>(screenVertices[2].x),
		static_cast<int>(screenVertices[2].y),
		static_cast<int>(screenVertices[0].x),
		static_cast<int>(screenVertices[0].y),
		color_
	);

	//=========================== 上面 ===========================//

	Novice::DrawLine(
		static_cast<int>(screenVertices[4].x),
		static_cast<int>(screenVertices[4].y),
		static_cast<int>(screenVertices[5].x),
		static_cast<int>(screenVertices[5].y),
		color_
	);

	Novice::DrawLine(
		static_cast<int>(screenVertices[5].x),
		static_cast<int>(screenVertices[5].y),
		static_cast<int>(screenVertices[7].x),
		static_cast<int>(screenVertices[7].y),
		color_
	);

	Novice::DrawLine(
		static_cast<int>(screenVertices[7].x),
		static_cast<int>(screenVertices[7].y),
		static_cast<int>(screenVertices[6].x),
		static_cast<int>(screenVertices[6].y),
		color_
	);

	Novice::DrawLine(
		static_cast<int>(screenVertices[6].x),
		static_cast<int>(screenVertices[6].y),
		static_cast<int>(screenVertices[4].x),
		static_cast<int>(screenVertices[4].y),
		color_
	);

	//=========================== 側面 ===========================//

	Novice::DrawLine(
		static_cast<int>(screenVertices[0].x),
		static_cast<int>(screenVertices[0].y),
		static_cast<int>(screenVertices[4].x),
		static_cast<int>(screenVertices[4].y),
		color_
	);

	Novice::DrawLine(
		static_cast<int>(screenVertices[1].x),
		static_cast<int>(screenVertices[1].y),
		static_cast<int>(screenVertices[5].x),
		static_cast<int>(screenVertices[5].y),
		color_
	);

	Novice::DrawLine(
		static_cast<int>(screenVertices[2].x),
		static_cast<int>(screenVertices[2].y),
		static_cast<int>(screenVertices[6].x),
		static_cast<int>(screenVertices[6].y),
		color_
	);

	Novice::DrawLine(
		static_cast<int>(screenVertices[3].x),
		static_cast<int>(screenVertices[3].y),
		static_cast<int>(screenVertices[7].x),
		static_cast<int>(screenVertices[7].y),
		color_
	);

}

bool AABB::IsCollision(const AABB& aabb2) {
	if ((min_.x <= aabb2.max_.x && max_.x >= aabb2.min_.x) &&
		(min_.y <= aabb2.max_.y && max_.y >= aabb2.min_.y) &&
		(min_.z <= aabb2.max_.z && max_.z >= aabb2.min_.z)) {

		return true;
	}
	return false;
}
