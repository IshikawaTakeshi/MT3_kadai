#include "Grid.h"
#include "MyMath/MatrixMath.h"
#include "Novice.h"

Grid::Grid() {
	pos_ = { 0.0f,0.0f,0.0f };
	rotate_ = { 0.0f,0.0f,0.0f };
	worldMatrix_ = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate_, pos_);
}

void Grid::Update() {
	worldMatrix_ = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate_, pos_);
}

void Grid::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {

	//gridの半分の幅
	const float kGridHarfWidth_ = 2.0f;

	//分割数
	const uint32_t kSubDivision_ = 10;

	//1つ分の長さ
	const float kGridEvery_ = (kGridHarfWidth_ * 2.0f) / float(kSubDivision_);

	//X線
	for (uint32_t xIndex = 0; xIndex <= kSubDivision_; ++xIndex){
		Vector3 startPos = {-kGridHarfWidth_ + kGridEvery_ * xIndex, 0.0f,-kGridHarfWidth_};
		Vector3 endPos = {-kGridHarfWidth_ + kGridEvery_ * xIndex,0.0f,kGridHarfWidth_ };
		Vector3 ndcStartPos = MatrixMath::Transform(startPos, viewProjectionMatrix);
		Vector3 ndcEndPos = MatrixMath::Transform(endPos, viewProjectionMatrix);
		Vector3 screenStartPos = MatrixMath::Transform(ndcStartPos, viewportMatrix);
		Vector3 screenEndPos = MatrixMath::Transform(ndcEndPos, viewportMatrix);
		Novice::DrawLine(
			static_cast<int>(screenStartPos.x),
			static_cast<int>(screenStartPos.y),
			static_cast<int>(screenEndPos.x),
			static_cast<int>(screenEndPos.y),
			0xaaaaaaff
		);
	}

	//Z線
	for (uint32_t zIndex = 0; zIndex <= kSubDivision_; ++zIndex) {
		Vector3 startPos = { kGridHarfWidth_,0.0f, - kGridHarfWidth_ + kGridEvery_ * zIndex };
		Vector3 endPos = { -kGridHarfWidth_,0.0f, - kGridHarfWidth_ + kGridEvery_ * zIndex };
		Vector3 ndcStartPos = MatrixMath::Transform(startPos, viewProjectionMatrix);
		Vector3 ndcEndPos = MatrixMath::Transform(endPos, viewProjectionMatrix);
		Vector3 screenStartPos = MatrixMath::Transform(ndcStartPos, viewportMatrix);
		Vector3 screenEndPos = MatrixMath::Transform(ndcEndPos, viewportMatrix);
		Novice::DrawLine(
			static_cast<int>(screenStartPos.x),
			static_cast<int>(screenStartPos.y),
			static_cast<int>(screenEndPos.x),
			static_cast<int>(screenEndPos.y),
			0xaaaaaaff
		);
	}
}
