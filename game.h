/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//�Q�[���S�̂Ŏg�p���郂�m���܂Ƃ߂Ă��܂�

//�d���C���N���[�h�֎~
#pragma once

//�G���[�}��
#define _CRT_SECURE_NO_WARNINGS

//�w�b�_�[�t�@�C���ǂݍ���
#include "DxLib.h"
#include "math.h"

//�}�N����`
#define GAME_WIDTH			800	//��ʂ̉��̑傫��
#define GAME_HEIGHT			600	//��ʂ̏c�̑傫��
#define GAME_COLOR			32	//��ʂ̃J���[�r�b�g

#define GAME_WINDOW_BAR		0				//�^�C�g���o�[�̓f�t�H���g�ɂ���
#define GAME_WINDOW_NAME	"GAME TITLE"	//�E�B���h�E�̃^�C�g��
#define GAME_FPS			60				//FPS�̐��l	

//�p�X�̒���
#define PATH_MAX			255	//255�����܂�
#define NAME_MAX			255	//255�����܂�

//�G���[���b�Z�[�W
#define IMAGE_LOAD_ERR_TITLE	TEXT("�摜�ǂݍ��݃G���[")

//�I���_�C�A���O�p
#define MOUSE_R_CLICK_TITLE		TEXT("�Q�[�����f")
#define MOUSE_R_CLICK_CAPTION	TEXT("�Q�[���𒆒f���A�^�C�g����ʂɖ߂�܂����H")


#define GAME_GR	5	//�d��

//�񋓌^
enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
};	//�Q�[���̃V�[��

enum GAME_STAGE {
	GAME_STAGE_RPG,
	GAME_STAGE_ACT
};	//�Q�[���̃X�e�[�W

//########## �O���̃v���g�^�C�v�錾 ##########
extern VOID MY_FPS_UPDATE(VOID);			//FPS�l���v���A�X�V����
extern VOID MY_FPS_DRAW(VOID);				//FPS�l��`�悷��
extern VOID MY_FPS_WAIT(VOID);				//FPS�l���v�����A�҂�

extern VOID MY_ALL_KEYDOWN_UPDATE(VOID);				//�L�[�̓��͏�Ԃ��X�V����
extern BOOL MY_KEY_DOWN(int KEY_INPUT_);				//�L�[�������Ă��邩�A�L�[�R�[�h�Ŕ��f����
extern BOOL MY_KEY_UP(int KEY_INPUT_);					//�L�[�������グ�����A�L�[�R�[�h�Ŕ��f����
extern BOOL MY_KEYDOWN_KEEP(int KEY_INPUT_, int msec);	//�L�[�����������Ă��邩�A�L�[�R�[�h�Ŕ��f����
extern BOOL MY_KEY_PUSH(int KEY_INPUT_);				//�L�[���v�b�V���������A�L�[�R�[�h�Ŕ��f����

extern BOOL MY_CHECK_RECT_COLL(RECT a, RECT b);	//�̈�̓����蔻�������֐�

//########## �O���̃O���[�o���ϐ� ##########

//FPS�֘A
extern int StartTimeFps;				//����J�n����
extern int CountFps;					//�J�E���^
extern float CalcFps;					//�v�Z����
extern int SampleNumFps;				//���ς����T���v����

//�L�[�{�[�h�̓��͂��擾
extern char AllKeyState[256];			//���ׂẴL�[�̏�Ԃ�����
extern char OldAllKeyState[256];		//���ׂẴL�[�̏��(���O)������

//�Q�[���֘A
extern GAME_SCENE GameScene;			//�Q�[���̃V�[�����Ǘ�
extern GAME_STAGE GameStage;			//�Q�[���̃X�e�[�W���Ǘ�
