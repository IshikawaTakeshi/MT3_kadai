#include "Collision.h"
#include "Plane.h"
#include "Segment.h"
#include "Triangle.h"
#include "Ball.h"
#include "AABB.h"
#include "MyMath/MyMath.h"

#include <algorithm>

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

void Collision::Ball2PlaneIsCollision(Ball* ball, Plane* plane, float deltaTime) {

	//反発係数
	float e = 0.8f;

	ball->SetAcceleration({ 0.0f,-9.8f,0.0f });
	ball->SetVelocity(ball->GetVelocity() + ball->GetAcceleration() * deltaTime);
	ball->SetCenterPos(ball->GetCenterPos() + ball->GetVelocity() * deltaTime);

	if (ball->IsCollision(plane->GetPlaneData()) == true) {
		Vector3 reflected = MyMath::Reflect(ball->GetVelocity(), plane->GetPlaneData().normal);
		Vector3 projectNormal = MyMath::Project(reflected, plane->GetPlaneData().normal);
		Vector3 movingDirection = reflected - projectNormal;

		ball->SetVelocity(projectNormal * e + movingDirection);
	}
}

bool Collision::AABB2SegmentIsCollision(AABB* aabb, Segment* segment) {

	//AABBを構成する平面との衝突点の媒介変数
	Vector3 tPlaneMax;
	Vector3 tPlaneMin;

	//衝突点のうち近い方
	Vector3 tNear;
	//衝突点のうち遠い方
	Vector3 tFar;
	if(segment->GetDiff().x != 0.0f) {
		tPlaneMax.x = (aabb->GetMax().x - segment->GetOrigin().x) / segment->GetDiff().x;
		tPlaneMin.x = (aabb->GetMin().x - segment->GetOrigin().x) / segment->GetDiff().x;
	} else {
		tPlaneMax.x = std::numeric_limits<float>::infinity();
		tPlaneMin.x = -std::numeric_limits<float>::infinity();
	}

	if (segment->GetDiff().y != 0.0f) {
		tPlaneMax.y = (aabb->GetMax().y - segment->GetOrigin().y) / segment->GetDiff().y;
		tPlaneMin.y = (aabb->GetMin().y - segment->GetOrigin().y) / segment->GetDiff().y;
	} else {
		tPlaneMax.y = std::numeric_limits<float>::infinity();
		tPlaneMin.y = -std::numeric_limits<float>::infinity();
	}

	if (segment->GetDiff().z != 0.0f) {
		tPlaneMax.z = (aabb->GetMax().z - segment->GetOrigin().z) / segment->GetDiff().z;
		tPlaneMin.z = (aabb->GetMin().z - segment->GetOrigin().z) / segment->GetDiff().z;
	} else {
		tPlaneMax.z = std::numeric_limits<float>::infinity();
		tPlaneMin.z = -std::numeric_limits<float>::infinity();
	}


	tNear.x = std::min(tPlaneMax.x, tPlaneMin.x);
	tNear.y = std::min(tPlaneMax.y, tPlaneMin.y);
	tNear.z = std::min(tPlaneMax.z, tPlaneMin.z);
	tFar.x = std::max(tPlaneMax.x, tPlaneMin.x);
	tFar.y = std::max(tPlaneMax.y, tPlaneMin.y);
	tFar.z = std::max(tPlaneMax.z, tPlaneMin.z);

	//AABBとの衝突点(貫通点)のt値が小さいほう
	float tMin = std::max(std::max(tNear.x, tNear.y), tNear.z);
	//AABBとの衝突点(貫通点)のt値が大きいほう
	float tMax = std::min(std::min(tFar.x, tFar.y), tFar.z);

	if (tMin > tMax) {
		return false;
	}

	if (tMax < 0) {
		return false;
	}


	if (tMin <= 1 && tMax >= 0) {
		//衝突
		return true;
	}

	return false;
}
