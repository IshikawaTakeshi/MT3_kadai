#include <Novice.h>
#include "MyMath/MatrixMath.h"
#include "MyMath/MyMath.h"
#include "Grid/Grid.h"
#include "Camera/Camera.h"
#include "Sphere.h"

#include <imgui.h>

const char kWindowTitle[] = "LE2C_03_イシカワタケシ_MT3_03_02";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Vector3 translates[3] = {
		{0.2f,1.0f,0.0f},
		{0.4f,0.0f,0.0f},
		{0.3f,0.0f,0.0f},
	};

	Vector3 rotates[3] = {
		{0.0f,0.0f,-6.8f},
		{0.0f,0.0f,-1.4f},
		{0.0f,0.0f,0.0f},
	};

	Vector3 scales[3] = {
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
	};

	float radius = 0.3f;

	// カメラの初期化
	Camera* camera = new Camera();
	// グリッドの初期化
	Grid* grid = new Grid();

	//スフィア(肩)の初期化
	Sphere* sphereShoulder = new Sphere(translates[0],radius);
	sphereShoulder->SetRotation(rotates[0]);
	sphereShoulder->SetScale(scales[0]);
	//スフィア(肘)の初期化
	Sphere* sphereElbow = new Sphere(translates[1], radius);
	sphereElbow->SetRotation(rotates[1]);
	sphereElbow->SetScale(scales[1]);
	//スフィア(手首)の初期化
	Sphere* sphereWrist = new Sphere(translates[2], radius);
	sphereWrist->SetRotation(rotates[2]);
	sphereWrist->SetScale(scales[2]);



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
		
		sphereShoulder->Update();
		sphereElbow->Update();
		sphereShoulder->Update();
		
		sphereElbow->SetWorldMatrix()

		ImGui::Begin("Window");

		ImGui::End();

		///
		/// ↑更新処理ここまで
		///
		


		///
		/// ↓描画処理ここから
		///
	
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
