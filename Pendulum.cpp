#include "Pendulum.h"
#include "MyMath/MatrixMath.h"
#include "Novice.h"

#include <cmath>

void Pendulum::Update() {

	worldMatrix = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, anchorPos);
}

void Pendulum::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, const Vector3& diff) {

	Vector3 ndcAnchorPos = MatrixMath::Transform(anchorPos, worldMatrix * viewProjectionMatrix);
	Vector3 ndcDiffPos = MatrixMath::Transform(diff, viewProjectionMatrix);

	Vector3 screenAnchorPos = MatrixMath::Transform(ndcAnchorPos, viewportMatrix);
	Vector3 screenDiffPos = MatrixMath::Transform(ndcDiffPos, viewportMatrix);

	//描画
	Novice::DrawLine(
		static_cast<int>(screenAnchorPos.x),
		static_cast<int>(screenAnchorPos.y),
		static_cast<int>(screenDiffPos.x),
		static_cast<int>(screenDiffPos.y),
		0xffffffff
	);
}
