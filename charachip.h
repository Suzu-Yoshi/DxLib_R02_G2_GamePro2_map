/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//�L�����`�b�v�Ŏg�p���郂�m���܂Ƃ߂Ă��܂�
#pragma once

//�w�b�_�[�t�@�C���ǂݍ���
#include "DxLib.h"
#include "game.h"

//�摜�̃p�X
#define GAME_CHARA_1_PATH	TEXT(".\\IMAGE\\CHARA\\charaF01_1a1.png.png")		//�E�҂̉摜�P�i�㉺���E�j
#define GAME_CHARA_2_PATH	TEXT(".\\IMAGE\\CHARA\\charaF01_1a1-X.png")			//�E�҂̉摜�Q�i�΂߁j

#define CHARA_DIV_WIDTH		48	//�L�����`�b�v�̂P���̕��T�C�Y
#define CHARA_DIV_HEIGHT	48	//�L�����`�b�v�̂P���̍����T�C�Y

#define CHARA_DIV_TATE		4	//�L�����`�b�v���c�ɕ������鐔
#define CHARA_DIV_YOKO		3	//�L�����`�b�v�����ɕ������鐔
#define CHARA_DIV_NUM	CHARA_DIV_TATE * CHARA_DIV_YOKO	//�}�b�v�`�b�v�𕪊����鑍��

//�\���̒�`
typedef struct STRUCT_CHARACHIP
{
	char path[PATH_MAX];				//�p�X
	int handle[CHARA_DIV_NUM];			//���������摜�n���h�����擾
	int width;							//��
	int height;							//����
}CHARACHIP;	//CHARACHIP�\���́i�L�����`�b�v�̃f�[�^�������Ă���j
