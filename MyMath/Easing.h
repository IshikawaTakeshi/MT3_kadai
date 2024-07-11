#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"
#include "MyMath/MyMath.h"
#include <cmath>
#include <numbers>

class Easing {
public:

	//===============線形補間====================//

	static float Lerp(float startPos, float endPos, float easedT) {
		return (1.0f - easedT) * startPos + easedT * endPos;
	}

	static Vector3 Lerp(Vector3 startPos, Vector3 endPos, float easedT) {
		return (1.0f - easedT) * startPos + easedT * endPos;
	}

	static float EaseOut(float x) {
		return sinf((x * std::numbers::pi_v<float>) / 2.0f);
	}

	static float EaseIn(float x) {
		return 1.0f - cosf((x * std::numbers::pi_v<float>) / 2.0f);
	}

	static float EaseInOut(float x) {
		return -(cosf(std::numbers::pi_v<float> * x) - 1.0f) / 2.0f;
	}

	static Vector3 Bezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2, float easedT);

	/// <summary>
	/// ベジエ曲線の描画
	/// </summary>
	/// <param name="controlPoint0"></param>
	/// <param name="controlPoint1"></param>
	/// <param name="controlPoint2"></param>
	/// <param name="viewProjectionMatrix"></param>
	/// <param name="viewportMatrix"></param>
	/// <param name="color"></param>
	static void DrawBezier(
		const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2,
		const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
};






