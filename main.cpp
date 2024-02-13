#include <Novice.h>
#include <Struct.h>
#include <Matrix.h>

const char kWindowTitle[] = "GC1C_02_アリマ_ナオト";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize("Title", 480, 960);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	//Ball構造体の初期化(空気抵抗あり)
	Ball ball = {
		{160.0f,960.0f},
		{0.0f,0.0f},
		{0.0f,0.0f},
		1.0f,
		10.0f,
		WHITE
	};

	//Ball構造体の初期化(空気抵抗なし)
	Ball ball2 = {
		{320.0f,960.0f},
		{0.0f,0.0f},
		{0.0f,0.0f},
		0.0f,
		10.0f,
		WHITE
	};

	float k = 0.6f;

	float gravity = -9.8f;

	bool isfall = false;

	Vector2 Scale = { 1.0f,1.0f };
	Vector2 Scale2 = { 1.0f,1.0f };

	float theta = 0.0f;
	float theta2 = 0.0f;

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

		if (keys[DIK_SPACE] && preKeys[DIK_SPACE]) 
		{
			isfall = true;
		}

		if (isfall == true) {

			//==========================================================<空気抵抗あり>=========================================================================

			Vector2 airResistance = { k * -ball.Velocity.x,k * -ball.Velocity.y };

			Vector2 airResistanceAcceleration = { airResistance.y / ball.mass };

			ball.acceleration.y = gravity + airResistanceAcceleration.y;

			//================================================================================================================================================

			ball2.acceleration.y = gravity;

		}

		ball.Velocity.y += (ball.acceleration.y / 60.0f);

		ball.position.y += (ball.Velocity.y / 60.0f);


		//空気抵抗なし
		ball2.Velocity.x += ball2.acceleration.x / 60.0f;
		ball2.Velocity.y += ball2.acceleration.y / 60.0f;

		ball2.position.x += ball2.Velocity.x/ 60.0f;
		ball2.position.y += ball2.Velocity.y/ 60.0f;

		///レンダリングパイプラインの処理
		Matrix3x3 cameraWorldMatrix = MakeAffineMatrix({ 1.0f,1.0f }, 0.0f,{ 240.0f,480.0f });

		Matrix3x3 worldMatrix = MakeAffineMatrix(Scale, theta, ball.position);
		Matrix3x3 worldMatrix2 = MakeAffineMatrix(Scale2, theta2, ball2.position);

		Matrix3x3 viewMatrix = InverseMatrix(cameraWorldMatrix);

		Matrix3x3 OrthoMatrix = MakeOrthographicMatrix(-240.0f, 480.0f, 240.0f, -480.0f);

		Matrix3x3 ViewportMatrix = MakeViewportMatrix(0, 0, 480.0f, 960.0f);

		Matrix3x3 vpVpMatirx = Multiply(viewMatrix, OrthoMatrix);
		vpVpMatirx = Multiply(vpVpMatirx, ViewportMatrix);
		Matrix3x3 wvpVpMatrix = Multiply(worldMatrix, vpVpMatirx);
		Matrix3x3 wvpVpMatrix2 = Multiply(worldMatrix2, vpVpMatirx);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Vector2 screenBallPosition = Transform({ 0,0 }, wvpVpMatrix);
		Vector2 screenBallPosition2 = Transform({ 0,0 }, wvpVpMatrix2);

		//描画(空気抵抗あり)
		Novice::DrawEllipse(int(screenBallPosition.x), int(screenBallPosition.y), int(ball.radius), int(ball.radius), 0.0f, ball.color, kFillModeSolid);

		//描画(空気抵抗なし)
		Novice::DrawEllipse(int(screenBallPosition2.x), int(screenBallPosition2.y), int(ball2.radius), int(ball2.radius), 0.0f, ball2.color, kFillModeSolid);

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
