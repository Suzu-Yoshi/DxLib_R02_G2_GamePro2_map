/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//�}�b�v�`�b�v�Ŏg�p���郂�m���܂Ƃ߂Ă��܂�
#pragma once

//�w�b�_�[�t�@�C���ǂݍ���
#include "DxLib.h"
#include "game.h"

//�}�N����`
#define GAME_MAP_PATH			TEXT(".\\IMAGE\\MAP\\mapchip1.png")			//�}�b�v�̉摜
#define GAME_CSV_PATH_MAP1_SITA	TEXT(".\\IMAGE\\MAP\\map_map1_sita.csv")	//�}�b�vCSV(��)
#define GAME_CSV_PATH_MAP1_NAKA	TEXT(".\\IMAGE\\MAP\\map_map1_naka.csv")	//�}�b�vCSV(��)
#define GAME_CSV_PATH_MAP1_UE	TEXT(".\\IMAGE\\MAP\\map_map1_ue.csv")		//�}�b�vCSV(��)

#define GAME_MAP_TATE_MAX	10	//�}�b�v�̏c�̍L��
#define GAME_MAP_YOKO_MAX	20	//�}�b�v�̉��̍L��

#define GAME_MAP_KABE_KIND	8	//�}�b�v�̕ǂ̎��

#define MAP_DIV_WIDTH		32	//�}�b�v�`�b�v�̂P���̕��T�C�Y
#define MAP_DIV_HEIGHT		32	//�}�b�v�`�b�v�̂P���̍����T�C�Y

#define MAP_DIV_TATE		32	//�}�b�v�`�b�v���c�ɕ������鐔
#define MAP_DIV_YOKO		41	//�}�b�v�`�b�v�����ɕ������鐔
#define MAP_DIV_NUM	MAP_DIV_TATE * MAP_DIV_YOKO	//�}�b�v�`�b�v�𕪊����鑍��

//�񋓌^
enum MAP_KIND {
	MAP_KIND_KABE,	//��
	MAP_KIND_TURO,	//�ʘH
};

//�\���̒�`
typedef struct STRUCT_MAPCHIP
{
	char path[PATH_MAX];				//�p�X
	int handle[MAP_DIV_NUM];			//���������摜�n���h�����擾
	int width;							//��
	int height;							//����
}MAPCHIP;	//MAPCHIP�\���́i�}�b�v�`�b�v�̃f�[�^�������Ă���j

typedef struct STRUCT_MAP
{
	int value;			//�}�b�v�̒l
	MAP_KIND kind;		//�}�b�v�̎��
	int x;				//X�ʒu
	int y;				//Y�ʒu
	int width;			//��
	int height;			//����
	RECT Coll;			//�}�b�v�̓����蔻��
}MAP;	//MAP�\���́i�Q�[���Ŏg�p����f�[�^�������Ă���j