﻿#include "Sphere.h"
#include "MyMath/MatrixMath.h"
#include "MyMath/MyMath.h"
#include "Novice.h"
#include <string>

#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG

Sphere::Sphere(Vector3 centerPos, float radius) {
	centerPos_ = centerPos;
	radius_ = radius;
	color_ = 0xffffffff;
	worldMatrix_ = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f },centerPos_);
}

Sphere::~Sphere() {
}

void Sphere::Update(int id) {
	worldMatrix_ = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, centerPos_);

#ifdef _DEBUG
	std::string label = "Window::Sphere";
	label += "##" + std::to_string(id);
	ImGui::Begin(label.c_str());
	ImGui::DragFloat3("SphereTranslate", &centerPos_.x, 0.01f);
	ImGui::DragFloat("SphereRadius", &radius_, 0.01f);
	
	ImGui::End();
#endif // _DEBUG
}

void Sphere::Draw(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const uint32_t kSubdivision = 16;
	const float kLonEvery = static_cast<float>(M_PI) / static_cast<float>(kSubdivision); // 経度分割1つ分の角度
	const float kLatEvery = 2.0f * static_cast<float>(M_PI) / static_cast<float>(kSubdivision); // 緯度分割1つ分の角度
	
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex){
		float lat = static_cast<float>(-M_PI) / 2.0f + kLatEvery * latIndex; //現在の緯度

		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex){
			float lon = lonIndex * kLonEvery; //現在の経度
			//world座標系でのa,b,cを求める
			Vector3 a, b, c;
			Vector3 ndcA, ndcB, ndcC;
			Vector3 screenA, screenB, screenC;
			
			//スクリーン座標に変換
			a = MyMath::Multiply( radius_,{ std::cosf(lat) * std::cosf(lon),std::sinf(lat),std::cosf(lat) * std::sinf(lon) });
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

bool Sphere::IsCollision(const Sphere& s1, const Sphere& s2) {
	//	2つの弾の中心点間を求める
	float distance = MyMath::Length(MyMath::Subtract(s2.centerPos_, s1.centerPos_));
	//半径の合計よりも短ければ衝突
	if (distance <= s1.radius_ + s2.radius_) {
		return true;
	}
	return false;
}
