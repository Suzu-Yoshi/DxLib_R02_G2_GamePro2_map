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

VOID MY_PLAY(VOID);				//�v���C���(RPG)

VOID MY_PLAY_PROC_RPG(VOID);	//�v���C��ʂ̏���(RPG)
VOID MY_PLAY_DRAW_RPG(VOID);	//�v���C��ʂ̕`��(RPG)

VOID MY_PLAY_PROC_ACT(VOID);	//�v���C��ʂ̏���(ACT)
VOID MY_PLAY_DRAW_ACT(VOID);	//�v���C��ʂ̕`��(ACT)

VOID MY_END(VOID);			//�G���h���
VOID MY_END_PROC(VOID);		//�G���h��ʂ̏���
VOID MY_END_DRAW(VOID);		//�G���h��ʂ̕`��

BOOL MY_LOAD_MAPCHIP1(VOID);		//�摜���܂Ƃ߂ēǂݍ��ފ֐�
VOID MY_DELETE_IMAGE(VOID);		//�摜���܂Ƃ߂č폜����֐�

void DrawBoxRect(RECT r, unsigned int color, bool b);			//RECT�𗘗p���Ďl�p��`��

//########## �v���O�����ōŏ��Ɏ��s�����֐� ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);				//Log.txt���o�͂��Ȃ�
	ChangeWindowMode(TRUE);								//�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//�w��̐��l�ŃE�B���h�E��\������
	SetWindowStyleMode(GAME_WINDOW_BAR);				//�^�C�g���o�[�̓f�t�H���g�ɂ���
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));			//�E�B���h�E�̃^�C�g���̕���
	SetAlwaysRunFlag(TRUE);								//��A�N�e�B�u�ł����s����
	SetWindowIconID(333);								//�A�C�R���t�@�C����Ǎ�

	if (DxLib_Init() == -1) { return -1; }	//�c�w���C�u��������������

	//�}�b�v�`�b�v��ǂݍ���
	if (MY_LOAD_MAPCHIP1() == FALSE) { return -1; }
	if (MY_LOAD_MAPCHIP2() == FALSE) { return -1; }

	//CSV��ǂݍ���
	if (MY_LOAD_CSV_MAP1(MAP1_PATH_NAKA_CSV, &map1_naka[0][0], &mapInit1_naka[0][0]) == FALSE) { return -1; }
	if (MY_LOAD_CSV_MAP1(MAP1_PATH_UE_CSV, &map1_ue[0][0], &mapInit1_ue[0][0]) == FALSE) { return -1; }
	if (MY_LOAD_CSV_MAP1(MAP1_PATH_SITA_CSV, &map1_sita[0][0], &mapInit1_sita[0][0]) == FALSE) { return -1; }

	if (MY_LOAD_CSV_MAP2(MAP2_PATH_NAKA_CSV, &map2_naka[0][0], &mapInit2_naka[0][0]) == FALSE) { return -1; }
	if (MY_LOAD_CSV_MAP2(MAP2_PATH_UE_CSV, &map2_ue[0][0], &mapInit2_ue[0][0]) == FALSE) { return -1; }
	if (MY_LOAD_CSV_MAP2(MAP2_PATH_SITA_CSV, &map2_sita[0][0], &mapInit2_sita[0][0]) == FALSE) { return -1; }

	//�L�����`�b�v��ǂݍ���(�E��)
	if (MY_LOAD_CHARA_YUSHA(YUSHA_CHIP1_PATH, &yushaChip1) == FALSE) { return -1; }
	if (MY_LOAD_CHARA_YUSHA(YUSHA_CHIP2_PATH, &yushaChip2) == FALSE) { return -1; }

	//�L�����`�b�v��ǂݍ���(�O���t�B��)
	if (MY_LOAD_CHARA_GRIF(GRIF_CHIP1_PATH, &grifChip1) == FALSE) { return -1; }
	if (MY_LOAD_CHARA_GRIF(GRIF_CHIP2_PATH, &grifChip2) == FALSE) { return -1; }

	//Draw�n�֐��͗���ʂɕ`��
	SetDrawScreen(DX_SCREEN_BACK);

	//�Q�[���V�[���̓X�^�[�g��ʂ���
	GameScene = GAME_SCENE_START;

	//�Q�[���̃X�e�[�W�͂P����
	GameStage = GAME_STAGE_RPG;

	//�����ɃA���`�G�C���A�X��������
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_8X8);

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
		MY_INIT_GRIF();		//�O���t�B���̈ʒu��������

		//�X�e�[�W��I��
		GameStage = GAME_STAGE_ACT;

		//�v���C��ʂ�
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
	switch (GameStage)
	{
	case GAME_STAGE_RPG:
		MY_PLAY_PROC_RPG();	//�v���C��ʂ̏���(RPG)
		MY_PLAY_DRAW_RPG();	//�v���C��ʂ̕`��(RPG)
		break;
	case GAME_STAGE_ACT:
		MY_PLAY_PROC_ACT();	//�v���C��ʂ̏���(ACT)
		MY_PLAY_DRAW_ACT();	//�v���C��ʂ̕`��(ACT)
		break;
	}

	return;
}

//�v���C��ʂ̏���(RPG)
VOID MY_PLAY_PROC_RPG(VOID)
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

//�v���C��ʂ̕`��(RPG)
VOID MY_PLAY_DRAW_RPG(VOID)
{
	//�}�b�v����`��
	for (int tate = 0; tate < MAP1_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < MAP1_YOKO_MAX; yoko++)
		{
			DrawGraph(
				map1_sita[tate][yoko].x,
				map1_sita[tate][yoko].y,
				mapChip1.handle[map1_sita[tate][yoko].value],
				TRUE);
		}
	}

	//�}�b�v����`��
	for (int tate = 0; tate < MAP1_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < MAP1_YOKO_MAX; yoko++)
		{

			DrawGraph(
				map1_naka[tate][yoko].x,
				map1_naka[tate][yoko].y,
				mapChip1.handle[map1_naka[tate][yoko].value],
				TRUE);
		}
	}

	MY_DRAW_YUSHA();	//�E�҂�`��

	//�}�b�v���`��
	for (int tate = 0; tate < MAP1_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < MAP1_YOKO_MAX; yoko++)
		{
			DrawGraph(
				map1_ue[tate][yoko].x,
				map1_ue[tate][yoko].y,
				mapChip1.handle[map1_ue[tate][yoko].value],
				TRUE);
		}
	}

	//�f�o�b�O�`��
	for (int tate = 0; tate < MAP1_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < MAP1_YOKO_MAX; yoko++)
		{
			//�����蔻��̕`��i�f�o�b�O�p�j(������)
			switch (map1_naka[tate][yoko].kind)
			{
			case MAP1_KIND_KABE:	//�ǂ̂Ƃ�
				DrawBoxRect(map1_naka[tate][yoko].coll, GetColor(255, 0, 0), FALSE);
				break;
			case MAP1_KIND_TURO:	//�ʘH�̂Ƃ�
				DrawBoxRect(map1_naka[tate][yoko].coll, GetColor(0, 255, 0), FALSE);
				break;
			}
		}
	}

	//�E�҂̓����蔻��f�o�b�O�`��
	DrawBoxRect(yusha.coll, GetColor(0, 0, 255), FALSE);

	return;
}

//�v���C��ʂ̏���(ACT)
VOID MY_PLAY_PROC_ACT(VOID)
{
	if (MY_KEY_PUSH(KEY_INPUT_RETURN) == TRUE)
	{
		GameScene = GAME_SCENE_START;
		return;
	}

	MY_MOVE_GRIF();			//�O���t�B���̈ړ�����

	return;
}

//�v���C��ʂ̕`��(ACT)
VOID MY_PLAY_DRAW_ACT(VOID)
{
	//�}�b�v����`��
	for (int tate = 0; tate < MAP2_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < MAP2_YOKO_MAX; yoko++)
		{
			DrawGraph(
				map2_sita[tate][yoko].x,
				map2_sita[tate][yoko].y,
				mapChip2.handle[map2_sita[tate][yoko].value],
				TRUE);
		}
	}

	//�}�b�v����`��
	for (int tate = 0; tate < MAP2_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < MAP2_YOKO_MAX; yoko++)
		{

			DrawGraph(
				map2_naka[tate][yoko].x,
				map2_naka[tate][yoko].y,
				mapChip2.handle[map2_naka[tate][yoko].value],
				TRUE);
		}
	}

	MY_DRAW_GRIF();		//�O���t�H����`��

	//�}�b�v���`��
	for (int tate = 0; tate < MAP2_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < MAP2_YOKO_MAX; yoko++)
		{
			DrawGraph(
				map2_ue[tate][yoko].x,
				map2_ue[tate][yoko].y,
				mapChip2.handle[map2_ue[tate][yoko].value],
				TRUE);
		}
	}

	//�f�o�b�O�`��
	for (int tate = 0; tate < MAP2_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < MAP2_YOKO_MAX; yoko++)
		{
			//�����蔻��̕`��i�f�o�b�O�p�j(������)
			switch (map2_naka[tate][yoko].kind)
			{
			case MAP2_KIND_KABE:	//�ǂ̂Ƃ�
				DrawBoxRect(map2_naka[tate][yoko].coll, GetColor(255, 0, 0), FALSE);
				break;
			case MAP2_KIND_TURO:	//�ʘH�̂Ƃ�
				DrawBoxRect(map2_naka[tate][yoko].coll, GetColor(0, 255, 0), FALSE);
				break;
			}
		}
	}

	DrawFormatString(0, 20, GetColor(255, 255, 255), "��@���̈ʒu/X:%d,Y:%d", grif.x, grif.y);
	DrawFormatString(0, 40, GetColor(255, 255, 255), "�}�b�v�̈ʒu/X:%d,Y:%d", grif.mapX, grif.mapY);
	DrawFormatString(0, 60, GetColor(255, 255, 255), "�}�b�v�z��@/[%d][%d]", grif.mapY / MAP2_DIV_HEIGHT, grif.mapX / MAP2_DIV_WIDTH);

	//�O���t�H���̓����蔻��f�o�b�O�`��
	DrawBoxRect(grif.coll, GetColor(0, 0, 255), FALSE);

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

//�摜���܂Ƃ߂č폜����֐�
VOID MY_DELETE_IMAGE(VOID)
{
	for (int i_num = 0; i_num < MAP1_DIV_NUM; i_num++) { DeleteGraph(mapChip1.handle[i_num]); }
	for (int i_num = 0; i_num < MAP2_DIV_NUM; i_num++) { DeleteGraph(mapChip2.handle[i_num]); }

	return;
}

//RECT�𗘗p���Ďl�p��`��
void DrawBoxRect(RECT r, unsigned int color, bool b)
{
	//��������ɕ`��
	DrawBox(r.left, r.top, r.right, r.bottom, color, b);
	return;
}