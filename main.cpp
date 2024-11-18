#include <Novice.h>
const char kWindowTitle[] = "TD3";
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);
	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//=================================宣言====================================

	//int hideFlag = 0;

	//プレイヤー
	int worldPosX = 640;
	int scr = 0;
	int monitorX = worldPosX - scr;
	int speed = 10;
	int posXr = 100;
	int posYr = 0;
	int stopFlag = 0;
	int posX = 0;
	int posY = 0;
	int posYY = 0;

	//////背景画像集////////////////////////////////////////////

	int back = Novice::LoadTexture("./BACK1.png");
	int back2 = Novice::LoadTexture("./BACK2.png");
	int back3 = Novice::LoadTexture("./BACK3.png");
	int back4 = Novice::LoadTexture("./GOAL.png");
	int STYN = Novice::LoadTexture("./koke_up2-2.png");

	//////////////////////////////////////////////////////////////


	int animeTimer = 0;
	int animeCount = 0;

	//int seen[2]{
	
	//};

	int ResTimer = 80;
	int MOutTimer = 30;
	int MFlag = 0;

	int mamPosX = 815;
	int mamPosY = 150;


	//シーン切り替え
	enum SCENE {
		TITLE,
		STAND,
		GAME,
		CLEAR,
		GAMEOVER
	};

	int scene = TITLE;



	
	int walkCount = 0;
	int walkTimer = 0;

	
	int warCount = 0;
	int warTimer = 0;

	/////////////////////////////////////////////////


	int isWalk = 0;
	int isStop = 0;


	//=========================================================================
		// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();
		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);
		///
		/// ============================================================================↓更新処理ここから ================================================================
		///

		switch (scene)
		{
		case TITLE:
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
				scene = STAND;
				worldPosX = 0;
				worldPosX = 640;
				scr = 0;
				monitorX = worldPosX - scr;
				speed = 10;
				posXr = 100;
				posYr = 0;
				posX = 0;
				posY = 0;
				posYY = 0;
				animeTimer = 0;
				animeCount = 0;
				ResTimer = 80;
				MOutTimer = 30;
				MFlag = 0;
				mamPosX = 815;
				mamPosY = 150;
				warCount = 0;
				warTimer = 0;
				isWalk = 0;
				isStop = 0;
			}
			break;


		case STAND:

			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
				scene = GAME;

			}


			break;


		case GAME:


			animeTimer += 1;

			if (animeTimer == 20) {//60f進むとカウントが1進む
				animeCount += 1;
				animeTimer = 0;
			}
			if (animeCount > 1) {//カウントが3になると0に戻る
				animeCount = 0;
			}



			walkTimer += 1;

			if (walkTimer == 30) {//30f進むとカウントが1進む
				walkCount += 1;
				walkTimer = 0;
			}
			if (walkCount > 1) {//カウントが3になると0に戻る
				walkCount = 0;
			}


			warTimer += 1;

			if (warTimer == 30) {//300f進むとカウントが1進む
				warCount += 1;
				warTimer = 0;
			}
			if (warCount > 1) {//カウントが3になると0に戻る
				warCount = 0;
			}

			posX = worldPosX;
			scr += speed;
			worldPosX += speed;


			if (worldPosX > 8960 - posXr) {//プレイヤーの座標が8960-rを超えそうになったら
				//worldPosX -= speed;//worldposXからspeed引く
				scene = CLEAR;
			}
			if (worldPosX < 0 + posXr) {//プレイヤーの座標が0+rを超えそうになったら
				worldPosX += speed;//worldposXにspeedを足す
			}
			monitorX = worldPosX - scr;//monitorXにworldposX引くscrした値を代入
			posY = (posYY - 500) * -1;
			if (keys[DIK_A]) {
				posXr += 5;
			}
			if (keys[DIK_D]) {
				posXr -= 5;
			}

			if (stopFlag == 1) {
				speed = 0;
			}
			
			

			////////////////////////////////////////////////////////////////

			break;

		case GAMEOVER:
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
				scene = TITLE;


			}
			break;

		case CLEAR:
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
				scene = TITLE;

			}
			break;
		}

		///
		/// ================================================================↑更新処理ここまで =================================================================================
		///
		///
		/// ================================================================↓描画処理ここから ==================================================================================
		///

		switch (scene)
		{
		case TITLE:
			Novice::DrawBox(0, 0, 1280, 720, 0.0f, RED, kFillModeSolid);

			break;

		case STAND:

			Novice::DrawBox(0, 0, 1280, 720, 0.0f, GREEN, kFillModeSolid);

			break;


		case GAME:

			Novice::DrawSprite(0 - scr, 0, back, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite(1280 - scr, 0, back, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite(2560 - scr, 0, back2, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite(3840 - scr, 0, back3, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite(5120 - scr, 0, back2, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite(6400 - scr, 0, back, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite(7680 - scr, 0, back3, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite(8960 - scr, 0, back4, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::ScreenPrintf(0, 100, "worldPosX:%d", worldPosX);
			Novice::DrawSprite(monitorX - posXr, posY - posYr, STYN, 1, 1, 0.0f, 0xFFFFFFFF);
			break;
		
			
		

		case GAMEOVER:
			Novice::DrawBox(0, 0, 1280, 720, 0.0f, BLACK, kFillModeSolid);
			break;

		case CLEAR:
			Novice::DrawBox(0, 0, 1280, 720, 0.0f, WHITE, kFillModeSolid);
			break;
		}
		///
		/// ================================================================↑描画処理ここまで ===================================================================================
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