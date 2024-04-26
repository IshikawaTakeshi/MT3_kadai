#include <Novice.h>
#include "MyMath/MatrixMath.h"
#include "MyMath/MyMath.h"
#include "Grid/Grid.h"
#include "Camera/Camera.h"
#include "Sphere.h"

#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG




const char kWindowTitle[] = "LE2C_03_イシカワタケシ_MT3_02_01";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	//球の生成
	Sphere* sphere[2];
	sphere[0] = new Sphere({ 0.0f,0.3f,0.0f }, 0.5f);
	sphere[1] = new Sphere({ 1.0f,0.3f,1.0f }, 0.5f);
	
	//グリッド線の生成
	Grid* grid = new Grid();
	//カメラの生成
	Camera* camera = new Camera();

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
		sphere[0]->Update(0);
		sphere[1]->Update(1);

		if (Sphere::IsCollision(*sphere[0], *sphere[1]) == true) {
			sphere[0]->SetColor(0xff0000ff);
		} else {
			sphere[0]->SetColor(0xffffffff);
		}
		grid->Update();

		//射影行列の更新
		viewProjectionMatrix = MatrixMath::Multiply(camera->GetViewMatrix(), projectionMatrix);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		//グリッド線の描画
		grid->Draw(viewProjectionMatrix, viewportMatrix);
		//球体描画
		sphere[0]->Draw(viewProjectionMatrix, viewportMatrix);
		sphere[1]->Draw(viewProjectionMatrix, viewportMatrix);

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
