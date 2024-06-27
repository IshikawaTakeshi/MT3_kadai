#include "Segment.h"
#include "MyMath/MatrixMath.h"
#include "MyMath/MyMath.h"
#include "Plane.h"
#include "Triangle.h"
#include "Collision.h"
#include "Novice.h"

#include <imgui.h>

void Segment::Initialize() {

	origin_ = { 0.0f,1.0f,0.0f };
	diff_ = { 0.0f,0.0f,2.0f };
	worldMatrix_ = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate_, origin_);
	color_ = 0xffffffff;
}

void Segment::Update(Triangle* triangle) {

	//終点
	Vector3 endPoint;
	endPoint = origin_ + diff_;
	//行列の更新
	worldMatrix_ = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate_, (origin_ + endPoint) / 2.0f);

	//衝突した時の処理(plane)
	//if (plane) {
	//	if (IsCollision(plane) == true) {
	//		color_ = 0xff0000ff;
	//	} else {
	//		color_ = 0xffffffff;
	//	}
	//}

	//衝突した時の処理(triangle)
	if (triangle) {
		if (IsCollision(triangle) == true) {
			color_ = 0xff0000ff;
		} else {
			color_ = 0xffffffff;
		}
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

bool Segment::IsCollision(Plane* plane) {

	// 線分の始点から平面の距離
	float distance = plane->GetPlaneData().distance;

	float dot = MyMath::Dot(plane->GetPlaneData().normal, diff_);

	// ドット積が0の場合、線分は平面と平行なので交差しない
	if (dot == 0.0f) {
		return false;
	}

	// 交点のパラメータtを計算
	float t = (distance - MyMath::Dot(origin_, plane->GetPlaneData().normal)) / dot;

	// 交点が線分上にあるかを確認
	if (t >= 0.0f && t <= 1.0f) {
		return true;
	}

	return false;
}

bool Segment::IsCollision(Triangle* triangle) {

	//各辺を結んだベクトルと、頂点と衝突点pを結んだベクトルのクロス積を取る
	Vector3 v01 = triangle->GetVertices(1) - triangle->GetVertices(0);
	Vector3 v12 = triangle->GetVertices(2) - triangle->GetVertices(1);
	Vector3 v20 = triangle->GetVertices(0) - triangle->GetVertices(2);

	Vector3 v0p = origin_ - triangle->GetVertices(0);
	Vector3 v1p = origin_ - triangle->GetVertices(1);
	Vector3 v2p = origin_ - triangle->GetVertices(2);

	Vector3 cross01 = MyMath::Cross(v01, v1p);
	Vector3 cross12 = MyMath::Cross(v12, v2p);
	Vector3 cross20 = MyMath::Cross(v20, v0p);

	//すべての小三角形のクロス積と法線が同じ方向を向いていたら衝突
	if (MyMath::Dot(cross01, triangle->GetNormal()) >= 0.0f &&
		MyMath::Dot(cross12, triangle->GetNormal()) >= 0.0f &&
		MyMath::Dot(cross20, triangle->GetNormal()) >= 0.0f) {

		//衝突
		return true;
	}

	return false;
}
