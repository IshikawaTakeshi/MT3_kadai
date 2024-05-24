#include <Novice.h>
#include "MyMath/MatrixMath.h"
#include "MyMath/MyMath.h"
#include "Grid/Grid.h"
#include "Camera/Camera.h"
#include "Sphere.h"
#include "Plane.h"

#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG

const char kWindowTitle[] = "LE2C_03_イシカワタケシ_MT3_02_02";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Sphere* sphere = new Sphere({ 0,0,0 }, 0.5f);
	Grid* grid = new Grid();
	Camera* camera = new Camera();
	Plane* plane = new Plane();

	//射影行列
	Matrix4x4 projectionMatrix = MatrixMath::MakePerspectiveFovMatrix(0.45f, 1280.0f / 720.0f, 0.1f, 100.0f);
	Matrix4x4 viewProjectionMatrix = MatrixMath::Multiply(camera->GetViewMatrix(), projectionMatrix);
	//ビューポート変換行列
	Matrix4x4 viewportMatrix = MatrixMath::MakeViewportMatrix(0, 0, 1280.0f, 720.0f, 0.0f, 1.0f);


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
		plane->Update();
		sphere->Update(plane->GetPlaneData());
		
		
		viewProjectionMatrix = MatrixMath::Multiply(camera->GetViewMatrix(), projectionMatrix);

		///
		/// ↑更新処理ここまで
		///
		


		///
		/// ↓描画処理ここから
		///

		sphere->Draw(viewProjectionMatrix, viewportMatrix);
		grid->Draw(viewProjectionMatrix, viewportMatrix);
		plane->Draw(viewProjectionMatrix, viewportMatrix);


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
