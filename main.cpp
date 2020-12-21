/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//�����FCSV�t�@�C���̃f�[�^��ǂݍ���ŁA�}�b�v�Ɠ����蔻������T���v��
//�ǉ��F�L�����`�b�v��ǂݍ��݁A�ړ��ɍ��킹�ĉ摜�𓮂����T���v��
//�T���v���Ȃ̂ŁA�ۃp�N�������A�Q�l�ɂ��Ă��������B
//�T���v���Ȃ̂ŁA�K�v�Œ���̂��Ƃ����A���Ă��܂���B���R�ɃJ�X�^�}�C�Y���Ă��������B

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "game.h"
#include "mapchip.h"
#include "charachip.h"

typedef struct STRUCT_IMAGE
{
	char path[PATH_MAX];		//�p�X
	int handle;					//�n���h��
	int x;						//X�ʒu
	int y;						//Y�ʒu
	int width;					//��
	int height;					//����
}IMAGE;	//�摜�\����

//########## �O���[�o���ϐ� ##########

VOID MY_START(VOID);		//�X�^�[�g���
VOID MY_START_PROC(VOID);	//�X�^�[�g��ʂ̏���
VOID MY_START_DRAW(VOID);	//�X�^�[�g��ʂ̕`��

VOID MY_PLAY(VOID);			//�v���C���
VOID MY_PLAY_PROC(VOID);	//�v���C��ʂ̏���
VOID MY_PLAY_DRAW(VOID);	//�v���C��ʂ̕`��

VOID MY_END(VOID);			//�G���h���
VOID MY_END_PROC(VOID);		//�G���h��ʂ̏���
VOID MY_END_DRAW(VOID);		//�G���h��ʂ̕`��

BOOL MY_LOAD_IMAGE(VOID);		//�摜���܂Ƃ߂ēǂݍ��ފ֐�
VOID MY_DELETE_IMAGE(VOID);		//�摜���܂Ƃ߂č폜����֐�

void DrawBoxRect(RECT r, unsigned int color, bool b);			//RECT�𗘗p���Ďl�p��`��

//########## �v���O�����ōŏ��Ɏ��s�����֐� ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);								//�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//�w��̐��l�ŃE�B���h�E��\������
	SetWindowStyleMode(GAME_WINDOW_BAR);				//�^�C�g���o�[�̓f�t�H���g�ɂ���
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));			//�E�B���h�E�̃^�C�g���̕���
	SetAlwaysRunFlag(TRUE);								//��A�N�e�B�u�ł����s����
	SetWindowIconID(333);								//�A�C�R���t�@�C����Ǎ�

	if (DxLib_Init() == -1) { return -1; }	//�c�w���C�u��������������

	//�摜��ǂݍ���
	if (MY_LOAD_IMAGE() == FALSE) { return -1; }

	//CSV��ǂݍ���
	if (MY_LOAD_CSV_MAP1(GAME_CSV_PATH_MAP1_NAKA, &map1_naka[0][0], &mapInit1_naka[0][0]) == FALSE) { return -1; }
	if (MY_LOAD_CSV_MAP1(GAME_CSV_PATH_MAP1_UE, &map1_ue[0][0], &mapInit1_ue[0][0]) == FALSE) { return -1; }
	if (MY_LOAD_CSV_MAP1(GAME_CSV_PATH_MAP1_SITA, &map1_sita[0][0], &mapInit1_sita[0][0]) == FALSE) { return -1; }

	//�L�����`�b�v��ǂݍ���
	if (MY_LOAD_CHARA_YUSHA(YUSHA_CHIP1_PATH, &yushaChip1) == FALSE) { return -1; }
	if (MY_LOAD_CHARA_YUSHA(YUSHA_CHIP2_PATH, &yushaChip2) == FALSE) { return -1; }

	//Draw�n�֐��͗���ʂɕ`��
	SetDrawScreen(DX_SCREEN_BACK);

	//�Q�[���V�[���̓X�^�[�g��ʂ���
	GameScene = GAME_SCENE_START;

	//�������[�v
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	//���b�Z�[�W�����̌��ʂ��G���[�̂Ƃ��A�����I��
		if (ClearDrawScreen() != 0) { break; }	//��ʂ������ł��Ȃ������Ƃ��A�����I��

		MY_ALL_KEYDOWN_UPDATE();				//�����Ă���L�[��Ԃ��擾

		MY_FPS_UPDATE();	//FPS�̏���[�X�V]

		//�V�[�����Ƃɏ������s��
		switch (GameScene)
		{
		case GAME_SCENE_START:
			MY_START();	//�X�^�[�g���
			break;
		case GAME_SCENE_PLAY:
			MY_PLAY();	//�v���C���
			break;
		case GAME_SCENE_END:
			MY_END();	//�G���h���
			break;
		}

		MY_FPS_DRAW();		//FPS�̏���[�`��]

		ScreenFlip();		//���j�^�̃��t���b�V�����[�g�̑����ŗ���ʂ��ĕ`��

		MY_FPS_WAIT();		//FPS�̏���[�҂�]
	}

	//�摜�n���h����j��
	MY_DELETE_IMAGE();

	DxLib_End();	//�c�w���C�u�����g�p�̏I������

	return 0;
}

//�X�^�[�g���
VOID MY_START(VOID)
{
	MY_START_PROC();	//�X�^�[�g��ʂ̏���
	MY_START_DRAW();	//�X�^�[�g��ʂ̕`��

	return;
}

//�X�^�[�g��ʂ̏���
VOID MY_START_PROC(VOID)
{
	//�G���^�[�L�[����������A�v���C�V�[���ֈړ�����
	if (MY_KEY_PUSH(KEY_INPUT_RETURN) == TRUE)
	{
		MY_INIT_YUSHA();	//�E�҂̈ʒu��������

		GameScene = GAME_SCENE_PLAY;
	}

	return;
}

//�X�^�[�g��ʂ̕`��
VOID MY_START_DRAW(VOID)
{

	DrawString(0, 0, "�X�^�[�g���(�G���^�[�L�[�������ĉ�����)", GetColor(255, 255, 255));
	return;
}

//�v���C���
VOID MY_PLAY(VOID)
{
	MY_PLAY_PROC();	//�v���C��ʂ̏���
	MY_PLAY_DRAW();	//�v���C��ʂ̕`��

	return;
}

//�v���C��ʂ̏���
VOID MY_PLAY_PROC(VOID)
{
	if (MY_KEY_PUSH(KEY_INPUT_RETURN) == TRUE)
	{
		GameScene = GAME_SCENE_START;
		return;
	}

	//���O�̈ʒu���擾
	yusha.oldx = yusha.x;
	yusha.oldy = yusha.y;

	MY_MOVE_YUSHA();//�E�҂̈ړ�����

	//�v���C���[�̓����蔻����Čv�Z�i�����蔻������������Ă���j
	yusha.coll.left = yusha.x + 12;
	yusha.coll.top = yusha.y + 20;
	yusha.coll.right = yusha.x + yusha.width - 12;
	yusha.coll.bottom = yusha.y + yusha.height - 0;

	//�}�b�v�P�Ƃ̓����蔻��
	if (MY_CHECK_MAP1_PLAYER_COLL(yusha.coll) == TRUE)
	{
		//�����ɂԂ����Ă�����A�ړ����Ȃ�
		yusha.x = yusha.oldx;
		yusha.y = yusha.oldy;
	}

	return;
}

//�v���C��ʂ̕`��
VOID MY_PLAY_DRAW(VOID)
{
	//�}�b�v����`��
	for (int tate = 0; tate < MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < MAP_YOKO_MAX; yoko++)
		{
			DrawGraph(
				map1_sita[tate][yoko].x,
				map1_sita[tate][yoko].y,
				mapChip.handle[map1_sita[tate][yoko].value],
				TRUE);
		}
	}

	//�}�b�v����`��
	for (int tate = 0; tate < MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < MAP_YOKO_MAX; yoko++)
		{

			DrawGraph(
				map1_naka[tate][yoko].x,
				map1_naka[tate][yoko].y,
				mapChip.handle[map1_naka[tate][yoko].value],
				TRUE);
		}
	}

	MY_DRAW_YUSHA();	//�E�҂�`��

	//�}�b�v���`��
	for (int tate = 0; tate < MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < MAP_YOKO_MAX; yoko++)
		{
			DrawGraph(
				map1_ue[tate][yoko].x,
				map1_ue[tate][yoko].y,
				mapChip.handle[map1_ue[tate][yoko].value],
				TRUE);
		}
	}

	//�f�o�b�O�`��
	for (int tate = 0; tate < MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < MAP_YOKO_MAX; yoko++)
		{
			//�����蔻��̕`��i�f�o�b�O�p�j(������)
			switch (map1_naka[tate][yoko].kind)
			{
			case MAP_KIND_KABE:	//�ǂ̂Ƃ�
				DrawBoxRect(map1_naka[tate][yoko].coll, GetColor(255, 0, 0), FALSE);
				break;
			case MAP_KIND_TURO:	//�ʘH�̂Ƃ�
				DrawBoxRect(map1_naka[tate][yoko].coll, GetColor(0, 255, 0), FALSE);
				break;
			}
		}
	}

	//�E�҂̓����蔻��f�o�b�O�`��
	DrawBoxRect(yusha.coll, GetColor(0, 0, 255), FALSE);

	return;
}

//�G���h���
VOID MY_END(VOID)
{
	MY_END_PROC();	//�G���h��ʂ̏���
	MY_END_DRAW();	//�G���h��ʂ̕`��
	return;
}

//�G���h��ʂ̏���
VOID MY_END_PROC(VOID)
{
	//�G�X�P�[�v�L�[����������A�X�^�[�g�V�[���ֈړ�����
	if (MY_KEY_DOWN(KEY_INPUT_ESCAPE) == TRUE)
	{
		GameScene = GAME_SCENE_START;
		return;
	}

	return;
}

//�G���h��ʂ̕`��
VOID MY_END_DRAW(VOID)
{

	DrawString(0, 0, "�G���h���(�G�X�P�[�v�L�[�������ĉ�����)", GetColor(255, 255, 255));
	return;
}

//�摜���܂Ƃ߂ēǂݍ��ފ֐�
BOOL MY_LOAD_IMAGE(VOID)
{
	//�}�b�v�̉摜�𕪊�����
	int mapRes = LoadDivGraph(
		GAME_MAP_PATH,										//�Ԓe�̃p�X
		MAP_DIV_NUM, MAP_DIV_TATE, MAP_DIV_YOKO,			//�Ԓe�𕪊����鐔
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,						//�摜�𕪊�����̕��ƍ���
		&mapChip.handle[0]);								//���������摜������n���h��

	if (mapRes == -1)	//�G���[���b�Z�[�W�\��
	{
		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK); return FALSE;
	}

	//���ƍ������擾
	GetGraphSize(mapChip.handle[0], &mapChip.width, &mapChip.height);

	return TRUE;
}


//�摜���܂Ƃ߂č폜����֐�
VOID MY_DELETE_IMAGE(VOID)
{
	for (int i_num = 0; i_num < MAP_DIV_NUM; i_num++) { DeleteGraph(mapChip.handle[i_num]); }

	return;
}

//RECT�𗘗p���Ďl�p��`��
void DrawBoxRect(RECT r, unsigned int color, bool b)
{
	//��������ɕ`��
	DrawBox(r.left, r.top, r.right, r.bottom, color, b);
	return;
}