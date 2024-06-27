#include "Collision.h"
#include "Plane.h"
#include "Segment.h"
#include "Triangle.h"
#include "MyMath/MyMath.h"

bool Collision::Segment2PlaneIsCollision(Segment* segment, Plane* plane) {

	// 線分の始点から平面の距離
	float distance = plane->GetPlaneData().distance;

	float dot = MyMath::Dot(plane->GetPlaneData().normal, segment->GetDiff());

	// ドット積が0の場合、線分は平面と平行なので交差しない
	if (dot == 0.0f) {
		return false;
	}

	// 交点のパラメータtを計算
	float t = (distance - MyMath::Dot(segment->GetOrigin(), plane->GetPlaneData().normal)) / dot;

	// 交点が線分上にあるかを確認
	if (t >= 0.0f && t <= 1.0f) {
		return true;
	}

	return false;
}

bool Collision::Segment2TriangleIsCollision(Segment* segment, Triangle* triangle) {

	//各辺を結んだベクトルと、頂点と衝突点pを結んだベクトルのクロス積を取る
	Vector3 v01 = triangle->GetVertices(1) - triangle->GetVertices(0);
	Vector3 v12 = triangle->GetVertices(2) - triangle->GetVertices(1);
	Vector3 v20 = triangle->GetVertices(0) - triangle->GetVertices(2);

	Vector3 v0p = segment->GetOrigin() - triangle->GetVertices(0);
	Vector3 v1p = segment->GetOrigin() - triangle->GetVertices(1);
	Vector3 v2p = segment->GetOrigin() - triangle->GetVertices(2);

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
