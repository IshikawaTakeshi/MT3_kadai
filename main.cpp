#include <Novice.h>
#include "MyMath/MatrixMath.h"
#include "MyMath/MyMath.h"
#include "Grid/Grid.h"
#include "Camera/Camera.h"
#include "AABB.h"
#include "Sphere.h"
#include <imgui.h>

const char kWindowTitle[] = "LE2C_03_イシカワタケシ_MT3_02_03";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	//グリッド線の生成
	Grid* grid = new Grid();
	//カメラの生成
	Camera* camera = new Camera();
	//AABB
	AABB* aabb1 = new AABB();
	aabb1->Initialize({ -0.5f,-0.5f,-0.5f }, { 0.0f,0.0f,0.0f });
	//Sphere
	Sphere* sphere = new Sphere({0.0f,1.0f,-1.0f},0.5f);


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
		
		aabb1->Update();
		sphere->Update();
		grid->Update();	
		camera->Update();
	

		if (aabb1->IsCollision(sphere) == true) {
			aabb1->SetColor(0xff0000ff);
		} else {
			aabb1->SetColor(0xffffffff);
		}

		ImGui::Begin("AABB1");
		aabb1->UpdateImGui("aabb1");
		ImGui::End();
		
		///
		/// ↑更新処理ここまで
		///
		


		///
		/// ↓描画処理ここから
		///
	
		aabb1->Draw(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());
		sphere->Draw(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());
		grid->Draw(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());
		
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
