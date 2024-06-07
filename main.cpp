#include <Novice.h>
#include "MyMath/MatrixMath.h"
#include "MyMath/MyMath.h"
#include "Grid/Grid.h"
#include "Camera/Camera.h"
#include "Lines.h"
#include "Plane.h"

#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG

//線分と平面の当たり判定
bool IsCollision(const Segment& segment, Plane& plane) {

	float dot = MyMath::Dot(plane.GetPlaneData().normal, segment.diff);

	// ドット積が0の場合、線分は平面と平行なので交差しない
	if (dot == 0.0f) {
		return false;
	}

	// 交点のパラメータtを計算
	float t = (plane.GetPlaneData().distance - MyMath::Dot(segment.origin, plane.GetPlaneData().normal)) / dot;

	if (t >= 0.0f && t <= 1.0f) {
		return true;
	} else {
		return false;
	}
}

Vector3 GetSegmentMidpoint(const Vector3& P1, const Vector3& P2) {
	float midX = (P1.x + P2.x) / 2.0f;
	float midY = (P1.y + P2.y) / 2.0f;
	float midZ = (P1.z + P2.z) / 2.0f;

	return Vector3(midX, midY, midZ);
}

const char kWindowTitle[] = "LE2C_03_イシカワタケシ_MT3_02_03";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Segment segment = { {-2.0f,-1.0f,0.0f}, {3.0f,2.0f,2.0f} };
	Segment screenSegment;
	Vector3 segmentMidPoint = GetSegmentMidpoint(segment.origin, segment.diff);
	Matrix4x4 segmentMatrix = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, segmentMidPoint);
	unsigned int segmentColor = 0xffffffff;

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
		
		
		if (IsCollision(segment, *plane) == true) {
			segmentColor = 0xff0000ff;
		} else {
			segmentColor = 0xffffffff;
		}
		
		viewProjectionMatrix = MatrixMath::Multiply(camera->GetViewMatrix(), projectionMatrix);

		screenSegment.origin = MatrixMath::Transform(MatrixMath::Transform(segment.origin, viewProjectionMatrix), viewportMatrix);
		screenSegment.diff = MatrixMath::Transform(MatrixMath::Transform(segment.diff, viewProjectionMatrix), viewportMatrix);

		segmentMidPoint = GetSegmentMidpoint(screenSegment.origin, screenSegment.diff);
		segmentMatrix = MatrixMath::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, segmentMidPoint);

		ImGui::Begin("Segment");
		ImGui::DragFloat3("SegmentTransform", &segmentMidPoint.x,0.1f);
		ImGui::End();
		///
		/// ↑更新処理ここまで
		///
		


		///
		/// ↓描画処理ここから
		///

		
		grid->Draw(viewProjectionMatrix, viewportMatrix);
		plane->Draw(viewProjectionMatrix, viewportMatrix);

		Novice::DrawLine(
			static_cast<int>(screenSegment.origin.x),
			static_cast<int>(screenSegment.origin.y),
			static_cast<int>(screenSegment.diff.x),
			static_cast<int>(screenSegment.diff.y),
			segmentColor
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
