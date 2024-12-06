#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
const char kWindowTitle[] = "TD3";
// Windowsアプリでのエントリーポイント(main関数)
// 構造体
// 座標とスピード
typedef struct Vector2 {
	int x;
	int y;
} Vector2;

typedef struct Vector2f {
	float x;
	float y;
} Vector2f;

typedef struct Ball {
	Vector2f velocity = { 4.0f, 4.0f };
	Vector2f acceleration = { 0.0f, 1.0f };
} Ball;

Ball ball;

// player座標
Vector2 playerPos = { 0, 832 };
Vector2 enemyPos = { 0, 0 };
// playerのスクロール座標

// 背景のスクロール
Vector2 scroll;

// 当たり判定
typedef struct horn {
	// 左上
	int leftTopX;
	int leftTopY;
	// 左下
	int leftBottomX;
	int leftBottomY;
	// 右上
	int rightTopX;
	int rightTopY;
	// 右下
	int rightBottomX;
	int rightBottomY;

} horn;

// 敵の当たり判定
typedef struct EnemyHit {
	// 左上
	int leftTopX;
	int leftTopY;
	// 左下
	int leftBottomX;
	int leftBottomY;
	// 右上
	int rightTopX;
	int rightTopY;
	// 右下
	int rightBottomX;
	int rightBottomY;
} EnemyHit;

enum BLOCK {
	// ブロックなし
	NOBLOCK, // 0
	// ただのブロック
	NOMALBLOCK, // 1
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	// ライブラリの初期化
	const int screenWidth = 2560;
	const int screenHeight = 1536;
	Novice::Initialize(kWindowTitle, screenWidth, screenHeight);
	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };



	//=================================宣言====================================

	//int hideFlag = 0;
	//マップチップ
	//int grhp = Novice::LoadTexture("./block.png");

	//int map[25][25] = {};



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
	int ti = Novice::LoadTexture("./title.png");
	int back = Novice::LoadTexture("./back.png");
	/*
	int back2 = Novice::LoadTexture("./BACK2.png");
	int back3 = Novice::LoadTexture("./BACK3.png");
	int back4 = Novice::LoadTexture("./GOAL.png");*/
	//int STYN = Novice::LoadTexture("./koke_up2-2.png");
	//int graph = Novice::LoadTexture("./cell1.png");
	//int left = Novice::LoadTexture("./mushi_left2-1.png");
	//  ただのブロック
	int nomalBlock = Novice::LoadTexture("./block.png");
	int upGraph[2]{
		Novice::LoadTexture("./koke_up1-1.png"),
		Novice::LoadTexture("./koke_up2-2.png"),
	};
	//////////////////////////////////////////////////////////////

	// マップサイズ
	const int mapX = 40;
	const int mapY = 25;
	// タイルサイズ
	int mapTileSize = 64;
	int playerTileSize = 64;
	//int enemyTileSize = 64;

	int map[mapY][mapX] =//書き換えないmap
	{ {0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0},
		{0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0},
		{0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0},
		{0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0},
		{0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0},
		{0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 0, 0, 0,  0, 0, 0},
		{0, 0,  0, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1, 1, 0, 0,  0, 0, 0},
		{0, 0,  1, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 1, 0, 0,  0, 0, 0},
		{0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 1, 0, 0,  0, 0, 0},
		{0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 1, 0, 0,  0, 0, 0},
		{1, 26, 1, 1, 29, 1, 1, 33, 1, 1, 38, 1, 0, 0, 1, 0, 0,  0, 0, 0},
		{0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 1, 0, 0,  0, 0, 0},
		{0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 1, 0, 42, 0, 0, 0},
		{0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 1, 0, 0,  0, 0, 0},
		{1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 1}
	};



	//int map[40][25] = {}; 
	int animeTimer1 = 0;
	int animeCount1 = 0;

	int animeTimer = 0;
	int animeCount = 0;
	//int seen[2]{
	
	//};

	int ResTimer = 80;
	int MOutTimer = 30;
	int MFlag = 0;

	int mamPosX = 815;
	int mamPosY = 150;

	//敵
	/*int playerX3 = 1400;
	int playerY3 = 40;*/


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

	// スクロール最大・最小値
	// X
	int scrollMinY = 0;
	int scrollMaxY = 848;
	// Y
	int scrollMinX = 0;
	int scrollMaxX = 3072;
	// 移動する前にいる座標の変数
	int oldScrollX = scroll.x;
	int oldScrollY = scroll.y;

	int nowMapX = mapX;
	int nowMapY = mapY;

	horn player = {
		// 左上
		(playerPos.x / playerTileSize),
		(playerPos.y / playerTileSize),
		// 左下
		(playerPos.x - playerTileSize) / mapTileSize,
		(playerPos.y + playerTileSize - 1) / mapTileSize,
		// 右上
		(playerPos.x + playerTileSize - 1) / mapTileSize,
		(playerPos.y - playerTileSize) / mapTileSize,
		// 右下
		(playerPos.x + playerTileSize - 1) / mapTileSize,
		(playerPos.y + playerTileSize - 1) / mapTileSize,
	};
	// ジャンプするかしないか
	bool isJump = false;

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
			if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == 0) {
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
				animeTimer1 = 0;
				animeCount1 = 0;
				ResTimer = 80;
				MOutTimer = 30;
				MFlag = 0;
				mamPosX = 815;
				mamPosY = 150;
				warCount = 0;
				warTimer = 0;
				isWalk = 0;
				isStop = 0;
				 playerPos = { 0, 832 };
				//for (int y = 0; y < 40; y++)//マップチップの初期化
				//{
				//	for (int x = 0; x < 25; x++)
				//	{
				//		//map[y][x] = defaultMap[y][x];
				//	}
				//}
			}
			break;


		case STAND:

			if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == 0) {
				scene = GAME;

			}


			break;


		case GAME:
			// playerの処理
#pragma region player
			// 自由落下中のスクロール
			// スクロールする
			scroll.y = playerPos.y - screenHeight / 2;

			if (scroll.y < scrollMinY) {
				scroll.y = scrollMinY;
			}
			if (scroll.y > scrollMaxY) {
				scroll.y = scrollMaxY;
			}
			// マップ座標更新
			nowMapX = mapX;
			nowMapY = mapY;
			// スクロール止める
			oldScrollX = scroll.x;
			oldScrollY = scroll.y;
			// 角の判定
			player.leftTopX = (playerPos.x) / mapTileSize;
			player.leftTopY = (playerPos.y) / mapTileSize;
			player.leftBottomX = (playerPos.x) / mapTileSize;
			player.leftBottomY = (playerPos.y + playerTileSize - 1) / mapTileSize;
			player.rightTopX = (playerPos.x + playerTileSize - 1) / mapTileSize;
			player.rightTopY = (playerPos.y) / mapTileSize;
			player.rightBottomX = (playerPos.x + playerTileSize - 1) / mapTileSize;
			player.rightBottomY = (playerPos.y + playerTileSize - 1) / mapTileSize;
			// スペースでジャンプ
			if ((keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) && isJump == false) {
				isJump = true;
				ball.velocity.y = -25.0f;
				//sound = JAMP;

			}
			// 速度に加速度加算v
			ball.velocity.y += ball.acceleration.y;

			// 角の当たり判定
			player.leftTopX = (playerPos.x) / mapTileSize;
			player.leftTopY = (playerPos.y + int(ball.velocity.y)) / mapTileSize;
			player.leftBottomX = (playerPos.x) / mapTileSize;
			player.leftBottomY =
				(playerPos.y + playerTileSize - 1 + int(ball.velocity.y)) / mapTileSize;
			player.rightTopX = (playerPos.x + playerTileSize - 1) / mapTileSize;
			player.rightTopY = (playerPos.y + int(ball.velocity.y)) / mapTileSize;
			player.rightBottomX = (playerPos.x + playerTileSize - 1) / mapTileSize;
			player.rightBottomY =
				(playerPos.y + playerTileSize - 1 + int(ball.velocity.y)) / mapTileSize;
			// ジャンプしたときに地面にのめりこむかのめりこまないか
			if (map[player.leftTopY][player.leftTopX] == NOMALBLOCK ||
				map[player.rightTopY][player.rightTopX] == NOMALBLOCK) {
				ball.velocity.y = 0;
				playerPos.y = (player.leftTopY + 1) * mapTileSize;
				//sound = BLOCK;
			}

			// 自由落下したときに地面にのめりこむかのめりこまないか
			if (map[player.leftBottomY][player.leftBottomX] == NOMALBLOCK ||
				map[player.rightBottomY][player.rightBottomX] == NOMALBLOCK
				) {
				isJump = false;
				ball.velocity.y = 0;
				playerPos.y = (player.leftBottomY - 1) * mapTileSize;
			}


			// 自由落下中のスクロール
				// スクロールする
			scroll.y = playerPos.y - screenHeight / 2;

			if (scroll.y < scrollMinY) {
				scroll.y = scrollMinY;
			}
			if (scroll.y > scrollMaxY) {
				scroll.y = scrollMaxY;
			}

			// Yに速度加算
			playerPos.y += int(ball.velocity.y);

			// マップ座標更新
			nowMapX = mapX;
			nowMapY = mapY;
			// スクロール止める
			oldScrollX = scroll.x;
			oldScrollY = scroll.y;

			// 角の当たり判定
			player.leftTopX = (playerPos.x) / mapTileSize;
			player.leftTopY = (playerPos.y + int(ball.velocity.y)) / mapTileSize;
			player.leftBottomX = (playerPos.x) / mapTileSize;
			player.leftBottomY =
				(playerPos.y + playerTileSize - 1 + int(ball.velocity.y)) / mapTileSize;
			player.rightTopX = (playerPos.x + playerTileSize - 1) / mapTileSize;
			player.rightTopY = (playerPos.y + int(ball.velocity.y)) / mapTileSize;
			player.rightBottomX = (playerPos.x + playerTileSize - 1) / mapTileSize;
			player.rightBottomY =
				(playerPos.y + playerTileSize - 1 + int(ball.velocity.y)) / mapTileSize;


			//  左
			if ((keys[DIK_LEFT] || keys[DIK_A])) {
				// 左角の判定
				player.leftTopX = (playerPos.x - int(ball.velocity.x)) / mapTileSize;
				player.leftTopY = (playerPos.y) / mapTileSize;
				player.leftBottomX = (playerPos.x - int(ball.velocity.x)) / mapTileSize;
				player.leftBottomY = (playerPos.y + playerTileSize - 1) / mapTileSize;

				

				// 進む先がブロックじゃなかったら左にスピード分進む
				if (map[player.leftTopY][player.leftTopX] == NOBLOCK &&
					map[player.leftBottomY][player.leftBottomX] == NOBLOCK) {
					playerPos.x -= int(ball.velocity.x);
					if (playerPos.x < 0) {
						playerPos.x = 0;
					}
					// 左上か左下がブロックだったらスクロールが止まる
					if (map[player.leftTopY][player.leftTopX] == NOMALBLOCK ||
						map[player.leftBottomY][player.leftBottomX] == NOMALBLOCK) {
						scroll.x = oldScrollX;
					}
				}
			}

			// 右
			if ((keys[DIK_RIGHT] || keys[DIK_D])) {
				// 右角の判定
				player.rightTopX =
					(playerPos.x + playerTileSize - 1 + int(ball.velocity.x)) / mapTileSize;
				player.rightTopY = (playerPos.y) / mapTileSize;
				player.rightBottomX =
					(playerPos.x + playerTileSize - 1 + int(ball.velocity.x)) / mapTileSize;
				player.rightBottomY = (playerPos.y + playerTileSize - 1) / mapTileSize;
				
				// 進む先がブロックじゃなかったら右にスピード分進む
				if (map[player.rightTopY][player.rightTopX] == NOBLOCK &&
					map[player.rightBottomY][player.rightBottomX] == NOBLOCK) {
					playerPos.x += int(ball.velocity.x);
					// スクロールする
					if (scrollMinX < playerPos.x || playerPos.x > scrollMaxX) {
						scroll.x = playerPos.x + screenWidth / 2;
					}
					// 右上か右下がブロックだったらスクロールが止まる
					if (map[player.rightTopY][player.rightTopX] == NOMALBLOCK ||
						map[player.rightBottomY][player.rightBottomX] == NOMALBLOCK) {
						scroll.x = oldScrollX;
					}
				}
			}

			
		
			// スクロールする
			scroll.x = playerPos.x - screenWidth / 2;
			// スクロール止まる
			if (scroll.x < scrollMinX) {
				scroll.x = scrollMinX;
			}
			// スクロール止まる
			if (scroll.x > scrollMaxX) {
				scroll.x = scrollMaxX;
			}
#pragma endregion

			animeTimer += 1;
			if (animeTimer == 30) {//60f進むとカウントが1進む
				animeCount += 1;
				animeTimer = 0;
			}
			if (animeCount > 1) {//カウントが1になると0に戻る
				animeCount = 0;
			}

			animeTimer1 += 1;

			if (animeTimer1 == 20) {//60f進むとカウントが1進む
				animeCount1 += 1;
				animeTimer1 = 0;
			}
			if (animeCount1 > 1) {//カウントが3になると0に戻る
				animeCount1 = 0;
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
			//scr += speed;
			worldPosX += speed;


			if (worldPosX > 21960 - posXr) {//プレイヤーの座標が8960-rを超えそうになったら
				//worldPosX -= speed;//worldposXからspeed引く
				scene = CLEAR;
			}
			if (worldPosX < 0 + posXr) {//プレイヤーの座標が0+rを超えそうになったら
				worldPosX += speed;//worldposXにspeedを足す
			}

			//monitorX = worldPosX - scr;//monitorXにworldposX引くscrした値を代入
			//posY = (posYY - 500) * -1;




			/*if (keys[DIK_A]) {
				playerPos.x -= 5;
			}
			if (keys[DIK_D]) {
				playerPos.x += 5;
			}*/


			if (stopFlag == 1) {
				speed = 0;
			}
			
			if (playerPos.y > 1500) {
				scene = TITLE;
			}

			////////////////////////////////////////////////////////////////

			break;

		case GAMEOVER:
			if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == 0) {
				scene = TITLE;


			}
			break;

		case CLEAR:
			if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == 0) {
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
			Novice::DrawSprite(0, 0, ti, 1, 1, 0.0f, 0xFFFFFFFF);

			break;

		case STAND:

			Novice::DrawBox(0, 0, 2560, 1536, 0.0f, GREEN, kFillModeSolid);

			break;


		case GAME:
			Novice::DrawSprite(0, 0, back, 1, 1, 0.0f, 0xFFFFFFFF);
			/*
			Novice::DrawSprite(1280 - scr, 0, back, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite(2560 - scr, 0, back2, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite(3840 - scr, 0, back3, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite(5120 - scr, 0, back2, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite(6400 - scr, 0, back, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite(7680 - scr, 0, back3, 1, 1, 0.0f, 0xFFFFFFFF);
			Novice::DrawSprite(8960 - scr, 0, back4, 1, 1, 0.0f, 0xFFFFFFFF);*/
			Novice::ScreenPrintf(0, 100, "worldPosX:%d", worldPosX);
			//Novice::DrawSprite(monitorX - posXr, posY - posYr, STYN, 1, 1, 0.0f, 0xFFFFFFFF);
			
			// player表記
			Novice::DrawSprite(
				(playerPos.x) - scroll.x, (int)(playerPos.y) - scroll.y, upGraph[animeCount],
			1.2f,1.2f, 0.0f, 0xFFFFFFFF);

			//Novice::DrawSprite(playerX3, playerY3, left, 1.5f, 1.5f, 0.0f, 0xFFFFFFFF);
			for (int y = 0; y < mapY; y++) {
				for (int x = 0; x < mapX; x++) {
					if (playerPos.x + screenWidth > screenWidth ||
						playerPos.y + screenHeight > screenHeight) {
						switch (map[y][x]) {
							///////////////// ブロックなし
						case NOBLOCK:
							break;
							//////////////// ただのブロック
						case NOMALBLOCK:
							Novice::DrawSprite(
								(x * mapTileSize) - scroll.x, (y * mapTileSize) - scroll.y,
								nomalBlock, 1, 1, 0.0f, WHITE);
							break;
						}
					}
				}
			}
						

		case GAMEOVER:
			//Novice::DrawBox(0, 0, 1280, 720, 0.0f, BLACK, kFillModeSolid);
			break;

		case CLEAR:
			Novice::DrawBox(0, 0, 2560,1536, 0.0f, WHITE, kFillModeSolid);
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