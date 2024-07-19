#include "Ball.h"
#include "Spring.h"
#include "MyMath/MyMath.h"
#include "MyMath/MatrixMath.h"
#include "Novice.h"

#include <imgui.h>

Ball::Ball() {}

Ball::~Ball() {}

void Ball::Initialize(Vector3 centerPos, float radius) {
	centerPos_ = centerPos;
	radius_ = radius;
	worldMatrix_ = MatrixMath::MakeIdentity4x4();
	velocity_ = { 0.0f,0.0f,0.0f };
	acceleration_ = { 0.0f,0.0f,0.0f };
	color_ = 0x0000ffff;
	mass_ = 2.0f;
}

void Ball::Update(const Spring& spring) {

	Vector3 diff = centerPos_ - spring.anchorPos;
	float diffLength = MyMath::Length(diff);

	if (diffLength != 0.0f) {

		Vector3 direction = MyMath::Normalize(diff);
		Vector3 restPosition = spring.anchorPos + direction * spring.naturalLength;
		Vector3 displacement = diffLength * (centerPos_ - restPosition);
		Vector3 restoringForce = -spring.stiffness * displacement;
		//減衰抵抗を計算
		Vector3 dampingForce = -spring.dampingCoefficient * velocity_;
		Vector3 force = restoringForce + dampingForce;
		acceleration_ = force / mass_;
	}

	//加速度も速度もどちらも秒を基準とした値である
	//デルタタイムの適用
	velocity_ += acceleration_ * kDeltaTime_;
	centerPos_ += velocity_ * kDeltaTime_;

	worldMatrix_ = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, centerPos_);
}

void Ball::UpdateImGui() {
	ImGui::Text("Ball");
	ImGui::Text("CenterPos: %f,%f,%f", centerPos_.x, centerPos_.y, centerPos_.z);
	ImGui::Text("Acceleration: %f,%f,%f", acceleration_.x, acceleration_.y, acceleration_.z);
	ImGui::Text("Velocity: %f,%f,%f", velocity_.x, velocity_.y, velocity_.z);
}

void Ball::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const uint32_t kSubdivision = 16;
	const float kLonEvery = static_cast<float>(M_PI) / static_cast<float>(kSubdivision); // 経度分割1つ分の角度
	const float kLatEvery = 2.0f * static_cast<float>(M_PI) / static_cast<float>(kSubdivision); // 緯度分割1つ分の角度

	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = static_cast<float>(-M_PI) / 2.0f + kLatEvery * latIndex; //現在の緯度

		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery; //現在の経度
			//world座標系でのa,b,cを求める
			Vector3 a, b, c;
			Vector3 ndcA, ndcB, ndcC;
			Vector3 screenA, screenB, screenC;

			//スクリーン座標に変換
			a = MyMath::Multiply(radius_, { std::cosf(lat) * std::cosf(lon),std::sinf(lat),std::cosf(lat) * std::sinf(lon) });
			b = MyMath::Multiply(radius_, { std::cosf(lat + kLatEvery) * std::cosf(lon),std::sinf(lat + kLatEvery), std::cosf(lat + kLatEvery) * std::sinf(lon) });
			c = MyMath::Multiply(radius_, { std::cosf(lat) * std::cosf(lon + kLonEvery),std::sinf(lat),std::cosf(lat) * std::sinf(lon + kLonEvery) });
			ndcA = MatrixMath::Transform(a, MatrixMath::Multiply(worldMatrix_, viewProjectionMatrix));
			ndcB = MatrixMath::Transform(b, MatrixMath::Multiply(worldMatrix_, viewProjectionMatrix));
			ndcC = MatrixMath::Transform(c, MatrixMath::Multiply(worldMatrix_, viewProjectionMatrix));
			screenA = MatrixMath::Transform(ndcA, viewportMatrix);
			screenB = MatrixMath::Transform(ndcB, viewportMatrix);
			screenC = MatrixMath::Transform(ndcC, viewportMatrix);

			//ab,acで線を引く
			Novice::DrawLine(
				static_cast<int>(screenA.x),
				static_cast<int>(screenA.y),
				static_cast<int>(screenB.x),
				static_cast<int>(screenB.y),
				color_
			);
			Novice::DrawLine(
				static_cast<int>(screenA.x),
				static_cast<int>(screenA.y),
				static_cast<int>(screenC.x),
				static_cast<int>(screenC.y),
				color_
			);
		}
	}
}

