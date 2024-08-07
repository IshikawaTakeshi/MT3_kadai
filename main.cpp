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
#include "Collision.h"
#include <imgui.h>

//フレーム間の経過時間(デルタタイム)
static inline const float kDeltaTime = 1.0f / 60.0f;


const char kWindowTitle[] = "LE2C_03_イシカワタケシ_MT3_02_07";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	//aabb
	AABB* aabb = new AABB();
	aabb->Initialize({ -0.5f, -0.5f, -0.5f }, { 0.5f, 0.5f, 0.5f });

	//segment
	Segment* segment = new Segment();
	segment->Initialize({ -0.7f,0.3f,0.0f }, { 2.0f,-0.5f,0.0f });

	Sphere* sphereDiff = new Sphere();
	sphereDiff->Initialize(segment->GetDiff(), 0.01f);

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

		//AAABBの更新
		aabb->Update();

		//segmentの更新
		segment->Update();

		//sphereDiffの更新
		sphereDiff->SetCenterPos(segment->GetOrigin() + segment->GetDiff());
		sphereDiff->Update();

		if (Collision::AABB2SegmentIsCollision(aabb, segment) == true) {
			aabb->SetColor(0xff0000ff);
		} else {
			aabb->SetColor(0xffffffff);
		}


		///
		/// ↑更新処理ここまで
		///



		///
		/// ↓描画処理ここから
		///

		grid->Draw(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());

		aabb->Draw(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());

		segment->Draw(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());

		sphereDiff->Draw(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());

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
