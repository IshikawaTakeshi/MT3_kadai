#include <Novice.h>
#include "MyMath/MatrixMath.h"
#include "MyMath/MyMath.h"
#include "Grid/Grid.h"
#include "Camera/Camera.h"
#include "Segment.h"
#include "Sphere.h"
#include "Grid/Grid.h"
#include "Pendulum.h"
#include <imgui.h>

//フレーム間の経過時間(デルタタイム)
static inline const float kDeltaTime = 1.0f / 60.0f;


const char kWindowTitle[] = "LE2C_03_イシカワタケシ_MT3_03_00";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Pendulum pendulum{
		{0.0f,1.0f,0.0f},
		0.8f,
		0.7f,
		0.0f,
		0.0f,
		MatrixMath::MakeIdentity4x4()
	};

	//球体の生成
	Sphere* sphere = new Sphere();
	sphere->Initialize({ 0.0f,0.0f,0.0f }, 0.05f);

	//更新処理の実行フラグ
	bool isUpdate = false;

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
		// ペンデュラムの更新
		pendulum.Update();
		if (isUpdate == true) {
			pendulum.anglerAcceleration = -(9.8f / pendulum.length) * std::sinf(pendulum.angle);
			pendulum.anglerVelocity += pendulum.anglerAcceleration * kDeltaTime;
			pendulum.angle += pendulum.anglerVelocity * kDeltaTime;

			sphere->SetCenterPos({
				pendulum.anchorPos.x + std::cosf(pendulum.angle) * pendulum.length,
				pendulum.anchorPos.y - std::sinf(pendulum.angle) * pendulum.length,
				pendulum.anchorPos.z
				}
			);

			sphere->Update();
		}

#pragma region imgui
		ImGui::Begin("Debug");
		ImGui::Checkbox("Update", &isUpdate);

		ImGui::End();
#pragma endregion

		///
		/// ↑更新処理ここまで
		///



		///
		/// ↓描画処理ここから
		///

		grid->Draw(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());
		sphere->Draw(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());
		pendulum.Draw(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix(), sphere->GetCenterPos());

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
