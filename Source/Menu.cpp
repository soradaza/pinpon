#include "Menu.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Keyboard.h"


const static int GAME_Y = 240;    //�u�Q�[���v������y�ʒu
const static int CONFIG_Y = 270;    //�u�ݒ�v������y�ʒu

typedef enum {
    eMenu_Game,        //�Q�[��
    eMenu_Config,    //�ݒ�
    eMenu_End,    //�Q�[���I�[�o�[
    eMenu_Num,        //�{���ڂ̐�
} eMenu;

static int NowSelect = eMenu_Game;    //���݂̑I�����(�����̓Q�[���I��)

//�X�V
void Menu_Update() {
    if (Keyboard_Get(KEY_INPUT_DOWN) == 1) {//���L�[��������Ă�����
        NowSelect = (NowSelect + 1) % eMenu_Num;//�I����Ԃ��������
    }
    if (Keyboard_Get(KEY_INPUT_UP) == 1) {//��L�[��������Ă�����
        NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//�I����Ԃ���グ��
    }
    if (Keyboard_Get(KEY_INPUT_RETURN) == 1) {//�G���^�[�L�[�������ꂽ��
        switch (NowSelect) {//���ݑI�𒆂̏�Ԃɂ���ď����𕪊�
        case eMenu_Game://�Q�[���I�𒆂Ȃ�
            SceneMgr_ChangeScene(eScene_Game);//�V�[�����Q�[����ʂɕύX
            break;
        case eMenu_Config://�ݒ�I�𒆂Ȃ�
            SceneMgr_ChangeScene(eScene_Config);//�V�[����ݒ��ʂɕύX
            break;

        }
    }
}

//�`��
void Menu_Draw() {
    DrawString(200, 100, "��b���K�͊�{���̊�{�I", GetColor(255, 255, 255));
    DrawString(200, 120, "��Q��������Ȃ���s���|���ʂ𗎂Ƃ��Ȃ��悤�Ɋ撣��܂��傤�B", GetColor(255, 255, 255));
    DrawString(200, 150, "���j���[��ʂł��B", GetColor(255, 255, 255));
    DrawString(200, 170, "�㉺�L�[�������A�G���^�[�������ĉ������B", GetColor(255, 255, 255));
    DrawString(280, GAME_Y, "�Q�[��", GetColor(255, 255, 255));
    DrawString(280, CONFIG_Y, "�ݒ�", GetColor(255, 255, 255));
    int y = 0;
    switch (NowSelect) {//���݂̑I����Ԃɏ]���ď����𕪊�
    case eMenu_Game://�Q�[���I�𒆂Ȃ�
        y = GAME_Y;    //�Q�[���̍��W���i�[
        break;
    case eMenu_Config://�ݒ�I�𒆂Ȃ�
        y = CONFIG_Y;    //�ݒ�̍��W���i�[
        break;
    }
    DrawString(250, y, "��", GetColor(255, 255, 255));
}