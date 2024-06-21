#include "Segment.h"
#include "MyMath/MatrixMath.h"
#include "MyMath/MyMath.h"
#include "Plane.h"
#include "Novice.h"

#include <imgui.h>

void Segment::Initialize() {

	origin_ = { 1.0f,1.0f,1.0f };
	diff_ = {2.0f,2.0f,2.0f};
	worldMatrix_ = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate_, origin_);
	color_ = 0xffffffff;
}

void Segment::Update(Plane* plane) {

	//終点
	Vector3 endPoint;
	endPoint = origin_ + diff_;
	//行列の更新
	worldMatrix_ = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate_,(origin_ + endPoint) / 2.0f);
	
	//衝突した時の処理
	if (IsCollision(*plane) == true) {
		color_ = 0xff0000ff;
	} else {
		color_ = 0xffffffff;
	}

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

bool Segment::IsCollision(Plane& plane) {

	// 線分の始点から平面の距離
	float distance = plane.GetPlaneData().distance;

	float dot = MyMath::Dot(plane.GetPlaneData().normal, diff_);

	// ドット積が0の場合、線分は平面と平行なので交差しない
	if (dot == 0.0f) { 
		return false; 
	}

	// 交点のパラメータtを計算
	float t = (distance - MyMath::Dot(origin_, plane.GetPlaneData().normal)) / dot;

	// 交点が線分上にあるかを確認
	if (t >= 0.0f && t <= 1.0f) {
		return true; 
	} else {
		return false;
	}
}
