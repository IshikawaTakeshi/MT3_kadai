#include <Novice.h>
#include "MyMath/MatrixMath.h"
#include "MyMath/MyMath.h"
#include "Grid/Grid.h"
#include "Camera/Camera.h"
#include "Segment.h"
#include "Sphere.h"
#include "Grid/Grid.h"
#include "MyMath/Easing.h"
#include "Spring.h"
#include "Ball.h"
#include <imgui.h>

const char kWindowTitle[] = "LE2C_03_イシカワタケシ_MT3_03_00";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	//バネの生成
	Spring spring = {
		{0.0f,1.0f,0.0f},
		0.7f,
		100.0f,
		2.0f,
		MatrixMath::MakeIdentity4x4()
	};

	//ボールの生成
	Ball* ball = new Ball();
	ball->Initialize({ 0.8f,0.2f,0.0f },0.05f);
	//更新処理の実行フラグ
	bool isUpdate = false;

	// カメラの生成
	Camera* camera = new Camera();
	// グリッドの生成
	Grid* grid = new Grid();

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
		spring.Update();
		if (isUpdate == true) {
			ball->Update(spring);
		
		}
	
#pragma region imgui
		ImGui::Begin("Debug");
		ImGui::Checkbox("BallUpdate", &isUpdate);

		ImGui::Text("Ball");
		ImGui::Text("CenterPos: %f,%f,%f", ball->GetCenterPos().x, ball->GetCenterPos().y, ball->GetCenterPos().z);
		ImGui::End();
#pragma endregion

		///
		/// ↑更新処理ここまで
		///
		


		///
		/// ↓描画処理ここから
		///
	
		grid->Draw(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());
		ball->Draw(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());
		spring.Draw(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix(),ball->GetCenterPos());
		
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
