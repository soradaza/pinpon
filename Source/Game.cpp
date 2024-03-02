#include "Game.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Keyboard.h"
#include "math.h"


#define WINDOW_WIDTH (1600)
#define WINDOW_HEIGHT (900)

//長方形の構造体定義
struct Ract
{
	int x;
	int y;
	int w;
	int h;
	bool flag;
};

//ブロックの個数
#define BLOCK_NUM_X (16)
#define BLOCK_NUM_Y (3)


//列挙型ボタン
enum e_But
{
	But_Dow,
	But_Lef,
	But_Rig,
	But_Up,
	But_A,
	But_B,
	But_X,
	But_Y,
	But_L,
	But_R,
	But_Sel,
	But_Sta,
	But_L3,
	But_R3,
	But_Total,
};

//パッドから取得した情報
int Pad_Inp;

//パッドを押したカウント
int Pad_Cou[e_But::But_Total];

bool Pad_Read()
{
	Pad_Inp = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	for (int b = 0; b < e_But::But_Total; b = b + 1)
	{
		if (Pad_Inp & (1 << b))
		{
			Pad_Cou[b] = Pad_Cou[b] + 1;
		}
		else Pad_Cou[b] = 0;
	}

	return FALSE;
}



//ブロック定義
Ract Block[BLOCK_NUM_X][BLOCK_NUM_Y];

Ract Bar;

Ract Block2;






//円の構造体定義
struct Cir
{
	int x;
	int y;
	int r;
	bool Flag;
};
//速度の構造体定義
struct Speed
{
	int x;
	int y;
};

//ボール定義
Cir Ball[5];

// ボールの速度定義
Speed Ball_Speed[5];


////バー定義
//Ract Bar1;

//更新
void Game_Update() {
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) { //Escキーが押されていたら
		SceneMgr_ChangeScene(eScene_Menu);//シーンをメニューに変更
	}


}



//ゲームの変数を初期化する関数
void Game_Ini()
{
	//ブロック に関する変数初期化
	for (int y = 0; y < BLOCK_NUM_Y; y = y + 1)
	{
		for (int x = 0; x < BLOCK_NUM_X; x = x + 1)
		{
			Block[x][y] = {
				x * 100,
				100 + y * 50,
				100,
				50,
				TRUE
			};
		}
	}

	//バーに関する変数初期化
	Bar = { 700, 700, 200, 30 };
	

	//ボールに関する変数初期化
	Ball[0] = { 800, 690, 10 };
	Ball[1] = { 300, 10, 10 };
	Ball[2] = { 800, 10, 10 };
	Ball[3] = { 1100, 10, 10 };
	Ball[4] = { 1400, 10, 10 };

	//ボールの速度に関する変数初期化
	Ball_Speed[0] = { 0, -5 };
	Ball_Speed[1] = { 0, -5 };
	Ball_Speed[2] = { 0, -10 };
	Ball_Speed[3] = { 0, -10 };
	Ball_Speed[4] = { 0, -15 };

}

//ブロックとボールの接触判定
bool HitJudg(Ract block, Cir ball)
{
	//円周の座標をループ計算
	const double pi = 3.141592;
	double rad;
	double x;
	double y;
	int circum_x;
	int circum_y;
	/*bool end = TRUE;*/
	for (int i = 0; i < 360; i = i + 1)
	{
		//円周の座標を計算
		rad = pi * i / 180;
		x = cos(rad);
		y = sin(rad);
		circum_x = ball.x + ball.r * x;
		circum_y = ball.y + ball.r * y;

		//ボールとブロックが接触した場合
		if (block.y <= circum_y &&
			circum_y <= block.y + block.h &&
			block.x <= circum_x &&
			circum_x <= block.x + block.w)
		{
			//Ball_Speed[0].y = Ball_Speed[0].y * (-1);
			return TRUE;
		}
		//else {
		//	Ball_Speed[0].y = Ball_Speed[0].y * (-1);//540y
			
		//}

	}
	return FALSE;

}

//ピンポンと敵の接触判定
bool BollJudg(Cir enemy, Cir ball)
{
	//円周の座標をループ計算
	const double pi = 3.141592;
	double rad;
	double x;
	double y;
	int circum_x;
	int circum_y;
	/*bool end = TRUE;*/
	for (int i = 0; i < 360; i = i + 1)
	{
		//円周の座標を計算
		rad = pi * i / 180;
		x = cos(rad);
		y = sin(rad);
		circum_x = ball.x + ball.r * x;
		circum_y = ball.y + ball.r * y;

		//ボールとブロックが接触した場合
		if (enemy.y <= circum_y &&
			circum_y <= enemy.y + enemy.r &&
			enemy.x <= circum_x &&
			circum_x <= enemy.x + enemy.r)
		{
			return TRUE;
		}
		//else {
		//	Ball_Speed[0].y = Ball_Speed[0].y * (-1);//540y

		//}

	}
	return FALSE;

}

//ゲームを描画する関数
void Game_Draw()
{



	//ブロックに関する変数初期化
	for (int y = 0; y < BLOCK_NUM_Y; y = y + 1)
	{
		for (int x = 0; x < BLOCK_NUM_X; x = x + 1)
		{

			if (Block[x][y].flag == TRUE)
			{
				switch (y)
				{
				case 0:
					DrawBox(
						Block[x][y].x,
						Block[x][y].y,
						Block[x][y].x + Block[x][y].w,
						Block[x][y].y + Block[x][y].h,
						GetColor(255, 0, 0),
						TRUE);
					break;
				case 1:

					DrawBox(
						Block[x][y].x,
						Block[x][y].y,
						Block[x][y].x + Block[x][y].w,
						Block[x][y].y + Block[x][y].h,
						GetColor(0, 255, 0),
						TRUE);
					break;
				case 2:
					DrawBox(
						Block[x][y].x,
						Block[x][y].y,
						Block[x][y].x + Block[x][y].w,
						Block[x][y].y + Block[x][y].h,
						GetColor(0, 0, 255),
						TRUE);
					break;
				}

				//網目
				/*DrawBox(
					Block[x][y].x,
					Block[x][y].y,
					Block[x][y].x + Block[x][y].w,
					Block[x][y].y + Block[x][y].h,
					GetColor(0, 0, 0),
					FALSE);*/
					//座標
				DrawFormatString(
					Block[x][y].x,
					Block[x][y].y,
					GetColor(255, 255, 255),
					"(%d, %d)",
					Block[x][y].x,
					Block[x][y].y);

			}
		}
	}
	//バー1
	DrawBox(
		Bar.x,
		Bar.y,
		Bar.x + Bar.w,
		Bar.y + Bar.h,
		GetColor(255, 0, 255),
		TRUE);

	//バー座標1
	DrawFormatString(
		Bar.x,
		Bar.y,
		GetColor(0, 0, 0),
		"(%d, %d)",
		Bar.x,
		Bar.y);

	

	//Ball
	DrawCircle(
		Ball[0].x,
		Ball[0].y,
		Ball[0].r,
		GetColor(255, 124, 0),
		TRUE);

	//Ball
	DrawFormatString(
		Ball[0].x,
		Ball[0].y,
		GetColor(255, 255, 255),
		"(%d, %d)",
		Ball[0].x,
		Ball[0].y);

	//Ball
	DrawCircle(
		Ball[1].x,
		Ball[1].y,
		Ball[1].r = 30,
		GetColor(0, 0, 255),
		TRUE);



	//Ball
	DrawCircle(
		Ball[2].x,
		Ball[2].y,
		Ball[2].r = 30,
		GetColor(0, 255, 255),
		TRUE);

	//Ball
	DrawCircle(
		Ball[3].x,
		Ball[3].y,
		Ball[3].r = 30,
		GetColor(255, 0, 255),
		TRUE);

	//Ball
	DrawCircle(
		Ball[4].x,
		Ball[4].y,
		Ball[4].r = 30,
		GetColor(0, 255, 0),
		TRUE);

	

	//スピード
	//DrawFormatString(
	//	Ball[0].x,
	//	Ball[0].y - 10,
	//	GetColor(255, 255, 255),
	//	"(%d, %d)",
	//	Ball_Speed[0].x,
	//	Ball_Speed[0].y);


}


//ゲームを計算する関数
void Game_Cal()
{


	////バーの座標計算(コントローラのボタン入力によって)
	if (Pad_Cou[e_But::But_Rig] != 0)
	{
		Bar.x = Bar.x + 10;
	}
	if (Pad_Cou[e_But::But_Lef] != 0)
	{
		Bar.x = Bar.x - 10;
	}
	if (Pad_Cou[e_But::But_Dow] != 0)
	{
		Bar.y = Bar.y + 10;
	}
	if (Pad_Cou[e_But::But_Up] != 0)
	{
		Bar.y = Bar.y - 10;
	}


	//////ボールのの座標計算(コントローラのボタン入力によって)
	//if (Pad_Cou[e_But::But_Rig] != 0)
	//{
	//	Ball[0].x = Ball[0].x + 10;
	//}
	//if (Pad_Cou[e_But::But_Lef] != 0)
	//{
	//	Ball[0].x = Ball[0].x - 10;
	//}

	int i = 0;
	////barとballの接触判定
	for (int y = 0; y < BLOCK_NUM_Y; y = y + 1)
	{
		for (int x = 0; x < BLOCK_NUM_X; x = x + 1)
		{
			//ブロックとボールが接触した場合
			if (Block[x][y].flag == TRUE &&
				HitJudg(Block[x][y], Ball[0]) == TRUE)
			{
				//ボールの座標計算
				Ball_Speed[0].y = Ball_Speed[0].y * (-1);

				//ブロック削除
				Block[x][y].flag = FALSE;

				//ループを抜ける
				break;
			}
			//ブロックとボールが接触した場合
			if (Block[x][y].flag == TRUE &&
				HitJudg(Block[x][y], Ball[1]) == TRUE)
			{
				//ボールの座標計算
				//Ball_Speed[1].y = Ball_Speed[1].y * (-1);

						//ボールの速度計算
				int z = ((Ball[1].x / 2) - Ball[1].x) / 10;
				Ball_Speed[1].x = z;
				Ball_Speed[1].y = Ball_Speed[1].y * (-1);

				//ブロック削除
				Block[x][y].flag = FALSE;

				//ループを抜ける
				break;
			}
			if (Block[x][y].flag == TRUE &&
				HitJudg(Block[x][y], Ball[2]) == TRUE)
			{
				//ボールの座標計算
				int z = ((Ball[2].x / 2) - Ball[2].x) / 10;
				Ball_Speed[2].x = z;
				Ball_Speed[2].y = Ball_Speed[2].y * (-1);

				//ブロック削除
				Block[x][y].flag = FALSE;

				//ループを抜ける
				break;
			}
			if (Block[x][y].flag == TRUE &&
				HitJudg(Block[x][y], Ball[3]) == TRUE)
			{
				//ボールの座標計算
				Ball_Speed[3].y = Ball_Speed[3].y * (-1);

				//ブロック削除
				Block[x][y].flag = FALSE;

				//ループを抜ける
				break;
			}
			if (Block[x][y].flag == TRUE &&
				HitJudg(Block[x][y], Ball[4]) == TRUE)
			{
				//ボールの座標計算
				Ball_Speed[4].y = Ball_Speed[4].y * (-1);

				//ブロック削除
				Block[x][y].flag = FALSE;

				//ループを抜ける
				break;
			}
		}
	}

	//ボールがバーに接触した場合
	if (HitJudg(Bar, Ball[0]) == TRUE)
	{
		//ボールの速度計算
		int x = (Ball[0].x - (Bar.x + Bar.w / 2)) / 10;
		Ball_Speed[0].x = x;
		Ball_Speed[0].y = Ball_Speed[0].y * (-1);
	}

	if (HitJudg(Bar, Ball[1]) == TRUE)
	{
		//ボールの速度計算
		int x = (Ball[1].x - (Bar.x + Bar.w / 2)) / 10;
		Ball_Speed[1].x = x;
		Ball_Speed[1].y = Ball_Speed[1].y * (-1);
	}


	if (Ball[0].y < 550)
	{
		Ball_Speed[0].y = Ball_Speed[0].y * (-1);
	}

	int Random = GetRand(3);

	SRand(12);

	////ボールが天井に接触した
	if (Ball[1].y < 0)
	{
		//ボールの速度計算
		/*int x = ((Ball[1].x / 2) - Ball[1].x ) / 10;
		Ball_Speed[1].x = x;*/
		Ball_Speed[1].y = Ball_Speed[1].y * (-1);

		//ボールの速度計算
		/*Ball_Speed[1].x = Random;
		Ball_Speed[1].y = Ball_Speed[1].y * (-1);*/


	}
	if (Ball[2].y < 0)
	{
		//ボールの速度計算
		int x = (Ball[2].x - (Ball[2].x / 2)) / 10;
		Ball_Speed[2].x = x;
		Ball_Speed[2].y = Ball_Speed[2].y * (-1);


	}
	if (Ball[3].y < 0)
	{

		//ボールの速度計算
		int x = (Ball[3].x - (Ball[3].x / 2)) / 10;
		Ball_Speed[3].x = x;
		Ball_Speed[3].y = Ball_Speed[3].y * (-1);


	}
	if (Ball[4].y < 0)
	{

		//ボールの速度計算
		int x = (Ball[4].x - (Ball[4].x / 2)) / 10;
		Ball_Speed[4].x = x;
		Ball_Speed[4].y = Ball_Speed[4].y * (-1);


	}


	//ボールが壁に接触した
	if (Ball[1].x < 0 || Ball[1].x > 1600 - 2 * Ball[1].r)
	{
		//ボールの速度計算
		Ball_Speed[1].x = Ball_Speed[1].x * (-1);
	}
	//ボールが壁に接触した
	if (Ball[2].x < 0 || Ball[2].x > 1600 - 2 * Ball[2].r)
	{
		//ボールの速度計算
		Ball_Speed[2].x = Ball_Speed[2].x * (-1);
	}
	//ボールが壁に接触した
	if (Ball[3].x < 0 || Ball[3].x > 1600 - 2 * Ball[3].r)
	{
		//ボールの速度計算
		Ball_Speed[3].x = Ball_Speed[3].x * (-1);
	}
	//ボールが壁に接触した
	if (Ball[4].x < 0 || Ball[4].x > 1600 - 2 * Ball[4].r)
	{
		//ボールの速度計算
		Ball_Speed[4].x = Ball_Speed[4].x * (-1);
	}
	/*if (Ball[1].x < 0 || Ball[1].x > 1600 - 2 * Ball[1].r)
	{
		Ball_Speed[1].y = Ball_Speed[1].y * (-1);
	}*/

	//ボールが落ちたら
	if (Ball[1].y > 900)
	{
		//ボールの速度計算
		Ball_Speed[1].y = Ball_Speed[1].y * (-1);
	}

	//ボールが落ちたら
	if (Ball[2].y > 900)
	{
		//ボールの速度計算
		Ball_Speed[2].y = Ball_Speed[2].y * (-1);
	}

	//ボールが落ちたら
	if (Ball[3].y > 900)
	{
		//ボールの速度計算
		Ball_Speed[3].y = Ball_Speed[3].y * (-1);
	}

	//ボールが落ちたら
	if (Ball[4].y > 900)
	{
		//ボールの速度計算
		Ball_Speed[4].y = Ball_Speed[4].y * (-1);
	}

	//ボールの座標計算
	Ball[0].y = Ball[0].y + Ball_Speed[0].y;
	Ball[0].x = Ball[0].x + Ball_Speed[0].x;

	Ball[1].y += Ball_Speed[1].y;
	Ball[1].x += Ball_Speed[1].x;
	Ball[2].y += Ball_Speed[2].y;
	Ball[2].x += Ball_Speed[2].x;
	Ball[3].y += Ball_Speed[3].y;
	Ball[3].x += Ball_Speed[3].x;
	Ball[4].y += Ball_Speed[4].y;
	Ball[4].x += Ball_Speed[4].x;



}


//ゲームオーバー時の処理
bool Game_End()
{
	bool end = FALSE;

	for (int y = 0; y < BLOCK_NUM_Y; y = y + 1)
	{
		for (int x = 0; x < BLOCK_NUM_X; x = x + 1)
		{
			//1個でもブロックがあればゲーム続行
			if (Block[x][y].flag == TRUE)
			{
				end = FALSE;
			}
		}
	}
	for (int y = 0; y < BLOCK_NUM_Y; y = y + 1)
	{
		for (int x = 0; x < BLOCK_NUM_X; x = x + 1)
		{
			//ブロックとボールが接触した場合
			if (Block[x][y].flag == TRUE &&
				HitJudg(Block[x][y], Ball[1]) == TRUE)
			{
				end = FALSE;
			}
		}
	}
	//ピンポン玉が画面外に出てもアウト
	if (Ball[0].x < 0 || Ball[0].x > 1600 - 2 * Ball[0].r)
	{
		Ball[0].y = Ball[0].y - Ball_Speed[0].y;
		Ball[0].x = Ball[0].x - Ball_Speed[0].x;
		Ball[1].y = Ball[1].y - Ball_Speed[1].y;
		Ball[1].x = Ball[1].x - Ball_Speed[1].x;
		Ball[2].y = Ball[2].y - Ball_Speed[2].y;
		Ball[2].x = Ball[2].x - Ball_Speed[2].x;
		Ball[3].y = Ball[3].y - Ball_Speed[3].y;
		Ball[3].x = Ball[3].x - Ball_Speed[3].x;
		Ball[4].y = Ball[4].y - Ball_Speed[4].y;
		Ball[4].x = Ball[4].x - Ball_Speed[4].x;
		DrawString(750, 400, "Game Over", GetColor(255, 255, 255));
		DrawString(750, 450, "Escキーを押すとメニューに戻ります。", GetColor(255, 255, 255));
	}

	//ボールが落ちたら
	if (Ball[0].y > 900)
	{
		Ball[0].y = Ball[0].y - Ball_Speed[0].y;
		Ball[0].x = Ball[0].x - Ball_Speed[0].x;
		Ball[1].y = Ball[1].y - Ball_Speed[1].y;
		Ball[1].x = Ball[1].x - Ball_Speed[1].x;
		Ball[2].y = Ball[2].y - Ball_Speed[2].y;
		Ball[2].x = Ball[2].x - Ball_Speed[2].x;
		Ball[3].y = Ball[3].y - Ball_Speed[3].y;
		Ball[3].x = Ball[3].x - Ball_Speed[3].x;
		Ball[4].y = Ball[4].y - Ball_Speed[4].y;
		Ball[4].x = Ball[4].x - Ball_Speed[4].x;
		DrawString(750, 400, "Game Over", GetColor(255, 255, 255));
		DrawString(750, 450, "Escキーを押すとメニューに戻ります。", GetColor(255, 255, 255));
		//End_Draw();
		//end = TRUE;
	}

	//ピンポン玉と玉が当たったらアウト
	if (BollJudg(Ball[1], Ball[0]) == TRUE)
	{
		Ball[0].y = Ball[0].y - Ball_Speed[0].y;
		Ball[0].x = Ball[0].x - Ball_Speed[0].x;
		Ball[1].y = Ball[1].y - Ball_Speed[1].y;
		Ball[1].x = Ball[1].x - Ball_Speed[1].x;
		Ball[2].y = Ball[2].y - Ball_Speed[2].y;
		Ball[2].x = Ball[2].x - Ball_Speed[2].x;
		Ball[3].y = Ball[3].y - Ball_Speed[3].y;
		Ball[3].x = Ball[3].x - Ball_Speed[3].x;
		Ball[4].y = Ball[4].y - Ball_Speed[4].y;
		Ball[4].x = Ball[4].x - Ball_Speed[4].x;
		DrawString(750, 400, "Game Over", GetColor(255, 255, 255));
		DrawString(750, 450, "Escキーを押すとメニューに戻ります。", GetColor(255, 255, 255));
	}
	if (BollJudg(Ball[2], Ball[0]) == TRUE)
	{
		Ball[0].y = Ball[0].y - Ball_Speed[0].y;
		Ball[0].x = Ball[0].x - Ball_Speed[0].x;
		Ball[1].y = Ball[1].y - Ball_Speed[1].y;
		Ball[1].x = Ball[1].x - Ball_Speed[1].x;
		Ball[2].y = Ball[2].y - Ball_Speed[2].y;
		Ball[2].x = Ball[2].x - Ball_Speed[2].x;
		Ball[3].y = Ball[3].y - Ball_Speed[3].y;
		Ball[3].x = Ball[3].x - Ball_Speed[3].x;
		Ball[4].y = Ball[4].y - Ball_Speed[4].y;
		Ball[4].x = Ball[4].x - Ball_Speed[4].x;
		DrawString(750, 400, "Game Over", GetColor(255, 255, 255));
		DrawString(750, 450, "Escキーを押すとメニューに戻ります。", GetColor(255, 255, 255));
	}
	if (BollJudg(Ball[3], Ball[0]) == TRUE)
	{
		Ball[0].y = Ball[0].y - Ball_Speed[0].y;
		Ball[0].x = Ball[0].x - Ball_Speed[0].x;
		Ball[1].y = Ball[1].y - Ball_Speed[1].y;
		Ball[1].x = Ball[1].x - Ball_Speed[1].x;
		Ball[2].y = Ball[2].y - Ball_Speed[2].y;
		Ball[2].x = Ball[2].x - Ball_Speed[2].x;
		Ball[3].y = Ball[3].y - Ball_Speed[3].y;
		Ball[3].x = Ball[3].x - Ball_Speed[3].x;
		Ball[4].y = Ball[4].y - Ball_Speed[4].y;
		Ball[4].x = Ball[4].x - Ball_Speed[4].x;
		DrawString(750, 400, "Game Over", GetColor(255, 255, 255));
		DrawString(750, 450, "Escキーを押すとメニューに戻ります。", GetColor(255, 255, 255));
	}
	if (BollJudg(Ball[4], Ball[0]) == TRUE)
	{
		Ball[0].y = Ball[0].y - Ball_Speed[0].y;
		Ball[0].x = Ball[0].x - Ball_Speed[0].x;
		Ball[1].y = Ball[1].y - Ball_Speed[1].y;
		Ball[1].x = Ball[1].x - Ball_Speed[1].x;
		Ball[2].y = Ball[2].y - Ball_Speed[2].y;
		Ball[2].x = Ball[2].x - Ball_Speed[2].x;
		Ball[3].y = Ball[3].y - Ball_Speed[3].y;
		Ball[3].x = Ball[3].x - Ball_Speed[3].x;
		Ball[4].y = Ball[4].y - Ball_Speed[4].y;
		Ball[4].x = Ball[4].x - Ball_Speed[4].x;
		DrawString(750, 400, "Game Over", GetColor(255, 255, 255));
		DrawString(750, 450, "Escキーを押すとメニューに戻ります。", GetColor(255, 255, 255));
	}

	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) { //Escキーが押されていたら
		end = TRUE;//シーンをメニューに変更
	}
	return end;
}






int WINAPI WinMain(

	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstnce,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)

{
	ChangeWindowMode(TRUE);
	DxLib_Init();

	PlaySound("No14.wav", DX_PLAYTYPE_BACK); //test.wavのバックグラウンド演奏
	SetWindowInitPosition(0, 0);
	SetWindowText("ピンポンゲーム");
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);
	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);

	Game_Ini();
	Game_Cal();
	Game_Draw();

	/*Pic.Read();
	Col.Read();
	Fon.Read();*/

	//1秒間に60回FPS
	while (ScreenFlip() == 0 &&
		ClearDrawScreen() == 0 &&
		ProcessMessage() == 0 &&
		Pad_Read() == FALSE)
	{

		
		Keyboard_Update();    //キーボードの更新
		SceneMgr_Update();  //更新
		SceneMgr_Draw();    //描画
		/*Game_Cal();
		Game_Draw();*/
		if (Game_End() == TRUE)
		{
			Game_Ini();
		}
	}

	DxLib_End();
	return 0;
}

