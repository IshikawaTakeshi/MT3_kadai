#include <Novice.h>
#include "MyMath/MatrixMath.h"
#include "MyMath/MyMath.h"
#include "Grid/Grid.h"
#include "Camera/Camera.h"
#include "Sphere.h"

#include <imgui.h>

const char kWindowTitle[] = "LE2C_03_イシカワタケシ_MT3_03_01";

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

	float radius = 0.05f;

	// カメラの初期化
	Camera* camera = new Camera();
	// グリッドの初期化
	Grid* grid = new Grid();

	//スフィア(肩)の初期化
	Sphere* sphereShoulder = new Sphere(translates[0],radius);
	sphereShoulder->SetRotation(rotates[0]);
	sphereShoulder->SetScale(scales[0]);
	sphereShoulder->SetColor(0xff0000ff);
	//スフィア(肘)の初期化
	Sphere* sphereElbow = new Sphere(translates[1], radius);
	sphereElbow->SetRotation(rotates[1]);
	sphereElbow->SetScale(scales[1]);
	sphereElbow->SetColor(0x00ff00ff);
	//スフィア(手首)の初期化
	Sphere* sphereWrist = new Sphere(translates[2], radius);
	sphereWrist->SetRotation(rotates[2]);
	sphereWrist->SetScale(scales[2]);
	sphereWrist->SetColor(0x0000ffff);

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
		

		grid->Update();
		camera->Update();
		sphereShoulder->Update();
		sphereElbow->Update();
		sphereWrist->Update();
		
		
		sphereElbow->SetWorldMatrix(sphereElbow->GetWorldMatrix() * sphereShoulder->GetWorldMatrix());
		sphereWrist->SetWorldMatrix(sphereWrist->GetWorldMatrix() * sphereElbow->GetWorldMatrix());


		ImGui::Begin("Debug");
#pragma region 肩の更新
		ImGui::Text("Sphere.Shoulder");
		Vector3 shoulderTransform = sphereShoulder->GetTransform();
		ImGui::DragFloat3("Translate", &shoulderTransform.x, 0.01f);
		sphereShoulder->SetTransform(shoulderTransform);

		Vector3 shoulderRotation = sphereShoulder->GetRotation();
		ImGui::DragFloat3("Rotation", &shoulderRotation.x, 0.01f);
		sphereShoulder->SetRotation(shoulderRotation);

		float shoulderRadius = sphereShoulder->GetRadius();
		ImGui::DragFloat("Scale", &shoulderRadius, 0.01f);
		sphereShoulder->SetRadius(shoulderRadius);
#pragma endregion

#pragma region 肘の更新
		ImGui::Text("Sphere.Elbow");
		Vector3 elbowTransform = sphereElbow->GetTransform();
		ImGui::DragFloat3("Translate##2", &elbowTransform.x, 0.01f);
		sphereElbow->SetTransform(elbowTransform);

		Vector3 elbowRotation = sphereElbow->GetRotation();
		ImGui::DragFloat3("Rotation##2", &elbowRotation.x, 0.01f);
		sphereElbow->SetRotation(elbowRotation);

		float elbowRadius = sphereElbow->GetRadius();
		ImGui::DragFloat("Scale##2", &elbowRadius, 0.01f);
		sphereElbow->SetRadius(elbowRadius);

#pragma endregion

#pragma region 手首の更新
		ImGui::Text("Sphere.Wrist");
		Vector3 wristTransform = sphereWrist->GetTransform();
		ImGui::DragFloat3("Translate##3", &wristTransform.x, 0.01f);
		sphereWrist->SetTransform(wristTransform);

		Vector3 wristRotation = sphereWrist->GetRotation();
		ImGui::DragFloat3("Rotation##3", &wristRotation.x, 0.01f);
		sphereWrist->SetRotation(wristRotation);

		float wristRadius = sphereWrist->GetRadius();
		ImGui::DragFloat("Scale##3", &wristRadius, 0.01f);
		sphereWrist->SetRadius(wristRadius);
#pragma endregion

		ImGui::End();

		///
		/// ↑更新処理ここまで
		///
		
		
		///
		/// ↓描画処理ここから
		///
	
		grid->Draw(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());
		sphereShoulder->Draw(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());
		sphereElbow->Draw(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());
		sphereWrist->Draw(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());
		
		Vector3 screenShoulder = MatrixMath::Transform(MatrixMath::Transform(shoulderTransform, camera->GetViewProjectionMatrix()),camera->GetViewportMatrix());
		Vector3 screenElbow = MatrixMath::Transform(MatrixMath::Transform(shoulderTransform, camera->GetViewProjectionMatrix()), camera->GetViewportMatrix());
		Vector3 screenWrist = MatrixMath::Transform(MatrixMath::Transform(wristTransform, camera->GetViewProjectionMatrix()),camera->GetViewportMatrix());

		Novice::DrawLine(
			static_cast<int>(screenShoulder.x),
			static_cast<int>(screenShoulder.y),
			static_cast<int>(screenElbow.x),
			static_cast<int>(screenElbow.y),
			0xffffffff
		);
		Novice::DrawLine(
			static_cast<int>(screenElbow.x),
			static_cast<int>(screenElbow.y),
			static_cast<int>(screenWrist.x),
			static_cast<int>(screenWrist.y),
			0xffffffff
		);

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
