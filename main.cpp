#include <Novice.h>
#include "MyMath/MatrixMath.h"
#include "MyMath/MyMath.h"
#include "Grid/Grid.h"
#include "Camera/Camera.h"
#include "Segment.h"
#include "Sphere.h"
#include "Grid/Grid.h"
#include "MyMath/Easing.h"
#include <imgui.h>

const char kWindowTitle[] = "LE2C_03_イシカワタケシ_MT3_03_00";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Vector3 controlPoint[4] = {
		{-0.8f,0.58f,1.0f},
		{1.76f,1.0f,-0.3f},
		{0.94f,-0.7f,2.3f},
		{-0.53f,-0.26f,-0.15f}
	};

	float radius = 0.05f;

	// カメラの生成
	Camera* camera = new Camera();
	// グリッドの生成
	Grid* grid = new Grid();
	//制御点を描画するための球体の生成
	Sphere* sphereP0 = new Sphere(controlPoint[0], radius);
	Sphere* sphereP1 = new Sphere(controlPoint[1], radius);
	Sphere* sphereP2 = new Sphere(controlPoint[2], radius);
	Sphere* sphereP3 = new Sphere(controlPoint[3], radius);
	

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		
		camera->Update();
		grid->Update();
		sphereP0->Update();
		sphereP1->Update();
		sphereP2->Update();
		sphereP3->Update();

#pragma region imgui
		ImGui::Begin("Debug");
		//========== sphereP0の数値を表示 ==========//
		ImGui::Text("Sphere.P0");
		Vector3 p0Transform = sphereP0->GetTransform();
		ImGui::DragFloat3("Translate", &p0Transform.x, 0.01f);
		sphereP0->SetTransform(p0Transform);

		float p0Radius = sphereP0->GetRadius();
		ImGui::DragFloat("Scale", &p0Radius, 0.01f);
		sphereP0->SetRadius(p0Radius);

		//========== sphereP1の数値を表示 ==========//
		ImGui::Text("Sphere.P1");
		Vector3 p1Transform = sphereP1->GetTransform();
		ImGui::DragFloat3("Translate##2", &p1Transform.x, 0.01f);
		sphereP1->SetTransform(p1Transform);

		float p1Radius = sphereP1->GetRadius();
		ImGui::DragFloat("Scale", &p1Radius, 0.01f);
		sphereP1->SetRadius(p1Radius);

		//=========== sphereP2の数値を表示 ==========//
		ImGui::Text("Sphere.P2");
		Vector3 p2Transform = sphereP2->GetTransform();
		ImGui::DragFloat3("Translate##3", &p2Transform.x, 0.01f);
		sphereP2->SetTransform(p2Transform);

		float p2Radius = sphereP2->GetRadius();
		ImGui::DragFloat("Scale", &p2Radius, 0.01f);
		sphereP2->SetRadius(p2Radius);

		//========== sphereP3の数値を表示 ==========//
		ImGui::Text("Sphere.P3");
		Vector3 p3Transform = sphereP3->GetTransform();
		ImGui::DragFloat3("Translate##4", &p3Transform.x, 0.01f);
		sphereP3->SetTransform(p3Transform);

		float p3Radius = sphereP3->GetRadius();
		ImGui::DragFloat("Scale", &p3Radius, 0.01f);
		sphereP3->SetRadius(p3Radius);

		ImGui::End();
#pragma endregion

		///
		/// ↑更新処理ここまで
		///
		


		///
		/// ↓描画処理ここから
		///
	
		grid->Draw(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());
		sphereP0->Draw(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());
		sphereP1->Draw(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());
		sphereP2->Draw(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());
		sphereP3->Draw(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());

		//Catmull-rom曲線描画
		Easing::DrawCatmullRom(
			sphereP0->GetTransform(), sphereP0->GetTransform(), sphereP1->GetTransform(), sphereP2->GetTransform(),
			camera->GetViewProjectionMatrix(), camera->GetViewportMatrix(), 0x00ff00ff);

		Easing::DrawCatmullRom(
			sphereP0->GetTransform(), sphereP1->GetTransform(), sphereP2->GetTransform(), sphereP3->GetTransform(),
			 camera->GetViewProjectionMatrix(), camera->GetViewportMatrix(), 0x00ff00ff);
		
		Easing::DrawCatmullRom(
			sphereP1->GetTransform(), sphereP2->GetTransform(), sphereP3->GetTransform(), sphereP3->GetTransform(),
			camera->GetViewProjectionMatrix(), camera->GetViewportMatrix(), 0x00ff00ff);
		
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
