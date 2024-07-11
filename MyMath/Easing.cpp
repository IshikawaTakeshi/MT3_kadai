#include "Easing.h"
#include "Novice.h"
#include "MyMath/MatrixMath.h"



Vector3 Easing::Bezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2, float easedT) {
	// 制御点p0o1を線形補間
	Vector3 p0p1 = Lerp(controlPoint0, controlPoint1, easedT);
	// 制御点p1o2を線形補間
	Vector3 p1p2 = Lerp(controlPoint1, controlPoint2, easedT);
	// 補間点p0p1,p1p2を線形補間
	return Lerp(p0p1, p1p2, easedT);
}
void Easing::DrawBezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2,
	const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	
	//分割数
	float division = 32;

	for (int i = 0; i < division; i++) {

		//媒介変数の初期化
		float t0 = i / static_cast<float>(division);
		float t1 = (i + 1) / static_cast<float>(division);

		//t0,t1,制御点を使ってベジエ曲線上の点を求める
		Vector3 bezier0 = Bezier(controlPoint0, controlPoint1, controlPoint2, t0);
		Vector3 bezier1 = Bezier(controlPoint0, controlPoint1, controlPoint2, t1);

		//それぞれの点をスクリーン座標に変換
		Vector3 screenPos0 = MatrixMath::Transform(MatrixMath::Transform(bezier0, viewProjectionMatrix), viewportMatrix);
		Vector3 screenPos1 = MatrixMath::Transform(MatrixMath::Transform(bezier1, viewProjectionMatrix), viewportMatrix);

		//描画
		Novice::DrawLine(
			static_cast<int>(screenPos0.x), static_cast<int>(screenPos0.y),
			static_cast<int>(screenPos1.x), static_cast<int>(screenPos1.y),
			color
		);
	}	
}

Vector3 Easing::CatmullRom(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2, const Vector3& controlPoint3, float easedT) {
	
	Vector3 result = ((-controlPoint0 + 3.0f * controlPoint1 - 3.0f * controlPoint2 + controlPoint3) * powf(easedT,3) +
		(2.0f * controlPoint0 - 5.0f * controlPoint1 + 4.0f * controlPoint2 - controlPoint3) * powf(easedT, 2) +
		(-controlPoint0 + controlPoint2) * easedT + 2.0f * controlPoint1) / 2.0f;

	return result;
}

void Easing::DrawCatmullRom(
	const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2, const Vector3& controlPoint3,
	const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	//分割数
	float division = 32;

	for (int i = 0; i < division; i++) {

		//媒介変数の初期化
		float t0 = i / static_cast<float>(division);
		float t1 = (i + 1) / static_cast<float>(division);
				
		//catmull-rom曲線上の点を求める
		Vector3 catmullRomP0p1 = CatmullRom(controlPoint0, controlPoint1, controlPoint2, controlPoint3, t0);
		Vector3 catmullRomP1p2 = CatmullRom(controlPoint0, controlPoint1, controlPoint2, controlPoint3, t1);
		
		//それぞれの点をスクリーン座標に変換
		Vector3 screenPosP0p1 = MatrixMath::Transform(MatrixMath::Transform(catmullRomP0p1, viewProjectionMatrix), viewportMatrix);
		Vector3 screenPosP1p2 = MatrixMath::Transform(MatrixMath::Transform(catmullRomP1p2, viewProjectionMatrix), viewportMatrix);
		
		//描画
		Novice::DrawLine(
			static_cast<int>(screenPosP0p1.x), static_cast<int>(screenPosP0p1.y),
			static_cast<int>(screenPosP1p2.x), static_cast<int>(screenPosP1p2.y),
			color
		);
	}
}
