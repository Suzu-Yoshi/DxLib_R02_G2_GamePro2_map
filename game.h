/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//�Q�[���S�̂Ŏg�p���郂�m���܂Ƃ߂Ă��܂�

//�d���C���N���[�h�֎~
#pragma once

//�w�b�_�[�t�@�C���ǂݍ���
#include "DxLib.h"

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

//�񋓌^
enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
};	//�Q�[���̃V�[��