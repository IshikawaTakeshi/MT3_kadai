#include "Segment.h"
#include "MyMath/MatrixMath.h"
#include "MyMath/MyMath.h"

#include "Novice.h"

#include <imgui.h>

void Segment::Initialize() {
	origin_ = { -2.0f, -1.0f, 0.0f };
	diff_ = { 3.0f,2.0f,2.0f };
	worldMatrix_ = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate_, origin_);
	color_ = 0xffffffff;
}

void Segment::Update() {

	//終点
	//Vector3 endPoint;
	//endPoint = origin_ + diff_;
	//行列の更新
	worldMatrix_ = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate_, origin_);

	//衝突した時の処理(plane)
	//if (plane) {
	//	if (IsCollision(plane) == true) {
	//		color_ = 0xff0000ff;
	//	} else {
	//		color_ = 0xffffffff;
	//	}
	//}

	ImGui::Begin("Segment");
	ImGui::DragFloat3("SegmentTransform", &origin_.x, 0.01f);
	ImGui::DragFloat3("Segment:Diff", &diff_.x, 0.01f);
	ImGui::End();
}

void Segment::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {

	//終点
	Vector3 endPoint;
	endPoint = origin_ + diff_;
	Vector3 ndcOrigin = MatrixMath::Transform(origin_, viewProjectionMatrix);
	Vector3 ndcEndPoint = MatrixMath::Transform(endPoint, viewProjectionMatrix);

	Vector3 screenOrigin = MatrixMath::Transform(ndcOrigin, viewportMatrix);
	Vector3 screenEndPoint = MatrixMath::Transform(ndcEndPoint, viewportMatrix);
	Novice::DrawLine(
		static_cast<int>(screenOrigin.x),
		static_cast<int>(screenOrigin.y),
		static_cast<int>(screenEndPoint.x),
		static_cast<int>(screenEndPoint.y),
		color_
	);
}

