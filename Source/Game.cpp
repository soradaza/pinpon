#include "Game.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Keyboard.h"
#include "math.h"


#define WINDOW_WIDTH (1600)
#define WINDOW_HEIGHT (900)

//�����`�̍\���̒�`
struct Ract
{
	int x;
	int y;
	int w;
	int h;
	bool flag;
};

//�u���b�N�̌�
#define BLOCK_NUM_X (16)
#define BLOCK_NUM_Y (3)


//�񋓌^�{�^��
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

//�p�b�h����擾�������
int Pad_Inp;

//�p�b�h���������J�E���g
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



//�u���b�N��`
Ract Block[BLOCK_NUM_X][BLOCK_NUM_Y];

Ract Bar;

Ract Block2;






//�~�̍\���̒�`
struct Cir
{
	int x;
	int y;
	int r;
	bool Flag;
};
//���x�̍\���̒�`
struct Speed
{
	int x;
	int y;
};

//�{�[����`
Cir Ball[5];

// �{�[���̑��x��`
Speed Ball_Speed[5];


////�o�[��`
//Ract Bar1;

//�X�V
void Game_Update() {
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) { //Esc�L�[��������Ă�����
		SceneMgr_ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
	}


}



//�Q�[���̕ϐ�������������֐�
void Game_Ini()
{
	//�u���b�N �Ɋւ���ϐ�������
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

	//�o�[�Ɋւ���ϐ�������
	Bar = { 700, 700, 200, 30 };
	

	//�{�[���Ɋւ���ϐ�������
	Ball[0] = { 800, 690, 10 };
	Ball[1] = { 300, 10, 10 };
	Ball[2] = { 800, 10, 10 };
	Ball[3] = { 1100, 10, 10 };
	Ball[4] = { 1400, 10, 10 };

	//�{�[���̑��x�Ɋւ���ϐ�������
	Ball_Speed[0] = { 0, -5 };
	Ball_Speed[1] = { 0, -5 };
	Ball_Speed[2] = { 0, -10 };
	Ball_Speed[3] = { 0, -10 };
	Ball_Speed[4] = { 0, -15 };

}

//�u���b�N�ƃ{�[���̐ڐG����
bool HitJudg(Ract block, Cir ball)
{
	//�~���̍��W�����[�v�v�Z
	const double pi = 3.141592;
	double rad;
	double x;
	double y;
	int circum_x;
	int circum_y;
	/*bool end = TRUE;*/
	for (int i = 0; i < 360; i = i + 1)
	{
		//�~���̍��W���v�Z
		rad = pi * i / 180;
		x = cos(rad);
		y = sin(rad);
		circum_x = ball.x + ball.r * x;
		circum_y = ball.y + ball.r * y;

		//�{�[���ƃu���b�N���ڐG�����ꍇ
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

//�s���|���ƓG�̐ڐG����
bool BollJudg(Cir enemy, Cir ball)
{
	//�~���̍��W�����[�v�v�Z
	const double pi = 3.141592;
	double rad;
	double x;
	double y;
	int circum_x;
	int circum_y;
	/*bool end = TRUE;*/
	for (int i = 0; i < 360; i = i + 1)
	{
		//�~���̍��W���v�Z
		rad = pi * i / 180;
		x = cos(rad);
		y = sin(rad);
		circum_x = ball.x + ball.r * x;
		circum_y = ball.y + ball.r * y;

		//�{�[���ƃu���b�N���ڐG�����ꍇ
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

//�Q�[����`�悷��֐�
void Game_Draw()
{



	//�u���b�N�Ɋւ���ϐ�������
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

				//�Ԗ�
				/*DrawBox(
					Block[x][y].x,
					Block[x][y].y,
					Block[x][y].x + Block[x][y].w,
					Block[x][y].y + Block[x][y].h,
					GetColor(0, 0, 0),
					FALSE);*/
					//���W
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
	//�o�[1
	DrawBox(
		Bar.x,
		Bar.y,
		Bar.x + Bar.w,
		Bar.y + Bar.h,
		GetColor(255, 0, 255),
		TRUE);

	//�o�[���W1
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

	

	//�X�s�[�h
	//DrawFormatString(
	//	Ball[0].x,
	//	Ball[0].y - 10,
	//	GetColor(255, 255, 255),
	//	"(%d, %d)",
	//	Ball_Speed[0].x,
	//	Ball_Speed[0].y);


}


//�Q�[�����v�Z����֐�
void Game_Cal()
{


	////�o�[�̍��W�v�Z(�R���g���[���̃{�^�����͂ɂ����)
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


	//////�{�[���̂̍��W�v�Z(�R���g���[���̃{�^�����͂ɂ����)
	//if (Pad_Cou[e_But::But_Rig] != 0)
	//{
	//	Ball[0].x = Ball[0].x + 10;
	//}
	//if (Pad_Cou[e_But::But_Lef] != 0)
	//{
	//	Ball[0].x = Ball[0].x - 10;
	//}

	int i = 0;
	////bar��ball�̐ڐG����
	for (int y = 0; y < BLOCK_NUM_Y; y = y + 1)
	{
		for (int x = 0; x < BLOCK_NUM_X; x = x + 1)
		{
			//�u���b�N�ƃ{�[�����ڐG�����ꍇ
			if (Block[x][y].flag == TRUE &&
				HitJudg(Block[x][y], Ball[0]) == TRUE)
			{
				//�{�[���̍��W�v�Z
				Ball_Speed[0].y = Ball_Speed[0].y * (-1);

				//�u���b�N�폜
				Block[x][y].flag = FALSE;

				//���[�v�𔲂���
				break;
			}
			//�u���b�N�ƃ{�[�����ڐG�����ꍇ
			if (Block[x][y].flag == TRUE &&
				HitJudg(Block[x][y], Ball[1]) == TRUE)
			{
				//�{�[���̍��W�v�Z
				//Ball_Speed[1].y = Ball_Speed[1].y * (-1);

						//�{�[���̑��x�v�Z
				int z = ((Ball[1].x / 2) - Ball[1].x) / 10;
				Ball_Speed[1].x = z;
				Ball_Speed[1].y = Ball_Speed[1].y * (-1);

				//�u���b�N�폜
				Block[x][y].flag = FALSE;

				//���[�v�𔲂���
				break;
			}
			if (Block[x][y].flag == TRUE &&
				HitJudg(Block[x][y], Ball[2]) == TRUE)
			{
				//�{�[���̍��W�v�Z
				int z = ((Ball[2].x / 2) - Ball[2].x) / 10;
				Ball_Speed[2].x = z;
				Ball_Speed[2].y = Ball_Speed[2].y * (-1);

				//�u���b�N�폜
				Block[x][y].flag = FALSE;

				//���[�v�𔲂���
				break;
			}
			if (Block[x][y].flag == TRUE &&
				HitJudg(Block[x][y], Ball[3]) == TRUE)
			{
				//�{�[���̍��W�v�Z
				Ball_Speed[3].y = Ball_Speed[3].y * (-1);

				//�u���b�N�폜
				Block[x][y].flag = FALSE;

				//���[�v�𔲂���
				break;
			}
			if (Block[x][y].flag == TRUE &&
				HitJudg(Block[x][y], Ball[4]) == TRUE)
			{
				//�{�[���̍��W�v�Z
				Ball_Speed[4].y = Ball_Speed[4].y * (-1);

				//�u���b�N�폜
				Block[x][y].flag = FALSE;

				//���[�v�𔲂���
				break;
			}
		}
	}

	//�{�[�����o�[�ɐڐG�����ꍇ
	if (HitJudg(Bar, Ball[0]) == TRUE)
	{
		//�{�[���̑��x�v�Z
		int x = (Ball[0].x - (Bar.x + Bar.w / 2)) / 10;
		Ball_Speed[0].x = x;
		Ball_Speed[0].y = Ball_Speed[0].y * (-1);
	}

	if (HitJudg(Bar, Ball[1]) == TRUE)
	{
		//�{�[���̑��x�v�Z
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

	////�{�[�����V��ɐڐG����
	if (Ball[1].y < 0)
	{
		//�{�[���̑��x�v�Z
		/*int x = ((Ball[1].x / 2) - Ball[1].x ) / 10;
		Ball_Speed[1].x = x;*/
		Ball_Speed[1].y = Ball_Speed[1].y * (-1);

		//�{�[���̑��x�v�Z
		/*Ball_Speed[1].x = Random;
		Ball_Speed[1].y = Ball_Speed[1].y * (-1);*/


	}
	if (Ball[2].y < 0)
	{
		//�{�[���̑��x�v�Z
		int x = (Ball[2].x - (Ball[2].x / 2)) / 10;
		Ball_Speed[2].x = x;
		Ball_Speed[2].y = Ball_Speed[2].y * (-1);


	}
	if (Ball[3].y < 0)
	{

		//�{�[���̑��x�v�Z
		int x = (Ball[3].x - (Ball[3].x / 2)) / 10;
		Ball_Speed[3].x = x;
		Ball_Speed[3].y = Ball_Speed[3].y * (-1);


	}
	if (Ball[4].y < 0)
	{

		//�{�[���̑��x�v�Z
		int x = (Ball[4].x - (Ball[4].x / 2)) / 10;
		Ball_Speed[4].x = x;
		Ball_Speed[4].y = Ball_Speed[4].y * (-1);


	}


	//�{�[�����ǂɐڐG����
	if (Ball[1].x < 0 || Ball[1].x > 1600 - 2 * Ball[1].r)
	{
		//�{�[���̑��x�v�Z
		Ball_Speed[1].x = Ball_Speed[1].x * (-1);
	}
	//�{�[�����ǂɐڐG����
	if (Ball[2].x < 0 || Ball[2].x > 1600 - 2 * Ball[2].r)
	{
		//�{�[���̑��x�v�Z
		Ball_Speed[2].x = Ball_Speed[2].x * (-1);
	}
	//�{�[�����ǂɐڐG����
	if (Ball[3].x < 0 || Ball[3].x > 1600 - 2 * Ball[3].r)
	{
		//�{�[���̑��x�v�Z
		Ball_Speed[3].x = Ball_Speed[3].x * (-1);
	}
	//�{�[�����ǂɐڐG����
	if (Ball[4].x < 0 || Ball[4].x > 1600 - 2 * Ball[4].r)
	{
		//�{�[���̑��x�v�Z
		Ball_Speed[4].x = Ball_Speed[4].x * (-1);
	}
	/*if (Ball[1].x < 0 || Ball[1].x > 1600 - 2 * Ball[1].r)
	{
		Ball_Speed[1].y = Ball_Speed[1].y * (-1);
	}*/

	//�{�[������������
	if (Ball[1].y > 900)
	{
		//�{�[���̑��x�v�Z
		Ball_Speed[1].y = Ball_Speed[1].y * (-1);
	}

	//�{�[������������
	if (Ball[2].y > 900)
	{
		//�{�[���̑��x�v�Z
		Ball_Speed[2].y = Ball_Speed[2].y * (-1);
	}

	//�{�[������������
	if (Ball[3].y > 900)
	{
		//�{�[���̑��x�v�Z
		Ball_Speed[3].y = Ball_Speed[3].y * (-1);
	}

	//�{�[������������
	if (Ball[4].y > 900)
	{
		//�{�[���̑��x�v�Z
		Ball_Speed[4].y = Ball_Speed[4].y * (-1);
	}

	//�{�[���̍��W�v�Z
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


//�Q�[���I�[�o�[���̏���
bool Game_End()
{
	bool end = FALSE;

	for (int y = 0; y < BLOCK_NUM_Y; y = y + 1)
	{
		for (int x = 0; x < BLOCK_NUM_X; x = x + 1)
		{
			//1�ł��u���b�N������΃Q�[�����s
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
			//�u���b�N�ƃ{�[�����ڐG�����ꍇ
			if (Block[x][y].flag == TRUE &&
				HitJudg(Block[x][y], Ball[1]) == TRUE)
			{
				end = FALSE;
			}
		}
	}
	//�s���|���ʂ���ʊO�ɏo�Ă��A�E�g
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
		DrawString(750, 450, "Esc�L�[�������ƃ��j���[�ɖ߂�܂��B", GetColor(255, 255, 255));
	}

	//�{�[������������
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
		DrawString(750, 450, "Esc�L�[�������ƃ��j���[�ɖ߂�܂��B", GetColor(255, 255, 255));
		//End_Draw();
		//end = TRUE;
	}

	//�s���|���ʂƋʂ�����������A�E�g
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
		DrawString(750, 450, "Esc�L�[�������ƃ��j���[�ɖ߂�܂��B", GetColor(255, 255, 255));
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
		DrawString(750, 450, "Esc�L�[�������ƃ��j���[�ɖ߂�܂��B", GetColor(255, 255, 255));
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
		DrawString(750, 450, "Esc�L�[�������ƃ��j���[�ɖ߂�܂��B", GetColor(255, 255, 255));
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
		DrawString(750, 450, "Esc�L�[�������ƃ��j���[�ɖ߂�܂��B", GetColor(255, 255, 255));
	}

	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) { //Esc�L�[��������Ă�����
		end = TRUE;//�V�[�������j���[�ɕύX
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

	PlaySound("No14.wav", DX_PLAYTYPE_BACK); //test.wav�̃o�b�N�O���E���h���t
	SetWindowInitPosition(0, 0);
	SetWindowText("�s���|���Q�[��");
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);
	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);

	Game_Ini();
	Game_Cal();
	Game_Draw();

	/*Pic.Read();
	Col.Read();
	Fon.Read();*/

	//1�b�Ԃ�60��FPS
	while (ScreenFlip() == 0 &&
		ClearDrawScreen() == 0 &&
		ProcessMessage() == 0 &&
		Pad_Read() == FALSE)
	{

		
		Keyboard_Update();    //�L�[�{�[�h�̍X�V
		SceneMgr_Update();  //�X�V
		SceneMgr_Draw();    //�`��
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

