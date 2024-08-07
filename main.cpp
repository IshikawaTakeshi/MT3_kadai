#include <Novice.h>
#include "MyMath/MatrixMath.h"
#include "MyMath/MyMath.h"
#include "Grid/Grid.h"
#include "Camera/Camera.h"
#include "Segment.h"
#include "Sphere.h"
#include "Ball.h"
#include "Grid/Grid.h"
#include "Plane.h"
#include "AABB.h"
#include "OBB.h"
#include "Collision.h"
#include <imgui.h>

//フレーム間の経過時間(デルタタイム)
static inline const float kDeltaTime = 1.0f / 60.0f;


const char kWindowTitle[] = "LE2C_03_イシカワタケシ_MT3_02_07";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Vector3 orientations[3] = { {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f} };

	//OBB
	OBB* obb = new OBB();
	obb->Initialize({ 0.0f, 0.0f, 0.0f },orientations,{ 0.5f, 0.5f, 0.5f });

	//Sphere
	Sphere* sphere = new Sphere();
	sphere->Initialize({ 0.0f, 0.0f, 0.0f }, 0.5f);

	// カメラの生成
	Camera* camera = new Camera();
	// グリッドの生成
	Grid* grid = new Grid();

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

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

		// カメラの更新
		camera->Update();
		// グリッドの更新
		grid->Update();

		//OBBの更新
		obb->Update();

		//Sphereの更新
		sphere->Update();

		if (Collision::OBB2SphereIsCollision(obb, sphere) == true) {
			sphere->SetColor(0xff0000ff);
		} else {
			sphere->SetColor(0xffffffff);
		}

		ImGui::Begin("Debug");
		obb->UpdateImGui();
		sphere->UpdateImGui();
		ImGui::End();

		///
		/// ↑更新処理ここまで
		///



		///
		/// ↓描画処理ここから
		///

		grid->Draw(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());

		//OBBの描画
		obb->Draw(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());

		//Sphereの描画
		sphere->Draw(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());
		
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
