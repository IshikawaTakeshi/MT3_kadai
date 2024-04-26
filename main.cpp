#include <Novice.h>
#include "MyMath/MatrixMath.h"
#include "MyMath/MyMath.h"
#include "Grid/Grid.h"
#include "Camera/Camera.h"
#include "Sphere.h"

#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG

const char kWindowTitle[] = "LC1B_02_イシカワタケシ_MT3";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	//グリッド線生成
	Grid* grid = new Grid();
	//カメラ生成
	Camera* camera = new Camera();

	//線分生成
	Segment segment{ {-2.0f,-1.0f,0.0f},{3.0f,2.0f,2.0f} };
	
	//点の座標
	Vector3 point{ -1.5f,0.6f,0.6f };
	//正射影ベクトル
	Vector3 project = MyMath::Project(MyMath::Subtract(point, segment.origin), segment.diff);
	//最近接点
	Vector3 closestPoint = MyMath::ClosestPoint(project, segment);
	//点の生成
	Sphere* pointSphere = new Sphere(point, 0.01f);
	Sphere* ClosestPointSphere = new Sphere(closestPoint, 0.01f);
	//射影行列
	Matrix4x4 projectionMatrix = MatrixMath::MakePerspectiveFovMatrix(0.45f, 1280.0f / 720.0f, 0.1f, 100.0f);
	Matrix4x4 viewProjectionMatrix = MatrixMath::Multiply(camera->GetViewMatrix(), projectionMatrix);
	//ビューポート変換行列
	Matrix4x4 viewportMatrix = MatrixMath::MakeViewportMatrix(0, 0, 1280.0f, 720.0f, 0.0f, 1.0f);

	//線分の両端
	Vector3 start = MatrixMath::Transform(MatrixMath::Transform(segment.origin, viewProjectionMatrix), viewportMatrix);
	Vector3 end = MatrixMath::Transform(MatrixMath::Transform(segment.origin + segment.diff, viewProjectionMatrix), viewportMatrix);


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

		//カメラの更新
		camera->Update();
		pointSphere->Update();
		ClosestPointSphere->Update();
		viewProjectionMatrix = MatrixMath::Multiply(camera->GetViewMatrix(), projectionMatrix);

		//点の更新
		start = MatrixMath::Transform(MatrixMath::Transform(segment.origin, viewProjectionMatrix), viewportMatrix);
		end = MatrixMath::Transform(MatrixMath::Transform(MyMath::Add(segment.origin, segment.diff), viewProjectionMatrix), viewportMatrix);

		//ImGui
		ImGui::InputFloat3("point", &point.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat3("segment.origin", &segment.origin.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat3("segment.diff", &segment.diff.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat3("Project", &project.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		///
		/// ↑更新処理ここまで
		///

		
		///
		/// ↓描画処理ここから
		///

		grid->Draw(viewProjectionMatrix, viewportMatrix);
		Novice::DrawLine(
			static_cast<int>(start.x),
			static_cast<int>(start.y),
			static_cast<int>(end.x),
			static_cast<int>(end.y),
			WHITE
			);
		pointSphere->Draw(viewProjectionMatrix, viewportMatrix, RED);
		ClosestPointSphere->Draw(viewProjectionMatrix, viewportMatrix, BLACK);


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
