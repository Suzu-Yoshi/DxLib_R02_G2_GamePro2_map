/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//�}�b�v�`�b�v�Ŏg�p���郂�m���܂Ƃ߂Ă��܂�
#pragma once

//�w�b�_�[�t�@�C���ǂݍ���
#include "DxLib.h"
#include "game.h"

//�}�N����`
#define MAP1_PATH			TEXT(".\\IMAGE\\MAP\\mapchip1.png")			//�}�b�v�̉摜
#define MAP1_PATH_SITA_CSV	TEXT(".\\IMAGE\\MAP\\map_map1_sita.csv")	//�}�b�vCSV(��)
#define MAP1_PATH_NAKA_CSV	TEXT(".\\IMAGE\\MAP\\map_map1_naka.csv")	//�}�b�vCSV(��)
#define MAP1_PATH_UE_CSV	TEXT(".\\IMAGE\\MAP\\map_map1_ue.csv")		//�}�b�vCSV(��)

#define MAP1_TATE_MAX	10	//�}�b�v�̏c�̍L��
#define MAP1_YOKO_MAX	20	//�}�b�v�̉��̍L��

#define MAP1_KABE_KIND	8	//�}�b�v�̕ǂ̎��

#define MAP1_DIV_WIDTH		32	//�}�b�v�`�b�v�̂P���̕��T�C�Y
#define MAP1_DIV_HEIGHT		32	//�}�b�v�`�b�v�̂P���̍����T�C�Y

#define MAP1_DIV_TATE		32	//�}�b�v�`�b�v���c�ɕ������鐔
#define MAP1_DIV_YOKO		41	//�}�b�v�`�b�v�����ɕ������鐔
#define MAP1_DIV_NUM	MAP1_DIV_TATE * MAP1_DIV_YOKO	//�}�b�v�`�b�v�𕪊����鑍��

//�񋓌^
enum MAP1_KIND {
	MAP1_KIND_KABE,	//��
	MAP1_KIND_TURO,	//�ʘH
};

//�\���̒�`
typedef struct STRUCT_MAPCHIP
{
	char path[PATH_MAX];				//�p�X
	int handle[MAP1_DIV_NUM];			//���������摜�n���h�����擾
	int width;							//��
	int height;							//����
}MAP1CHIP;	//MAP1CHIP�\���́i�}�b�v�`�b�v�̃f�[�^�������Ă���j

typedef struct STRUCT_MAP
{
	int value;			//�}�b�v�̒l
	MAP1_KIND kind;		//�}�b�v�̎��
	int x;				//X�ʒu
	int y;				//Y�ʒu
	int width;			//��
	int height;			//����
	RECT coll;			//�}�b�v�̓����蔻��
}MAP1;					//MAP1�\���́i�Q�[���Ŏg�p����f�[�^�������Ă���j

//########## �O���̃v���g�^�C�v�錾 ##########
extern BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT rect);					//�}�b�v�ƃv���C���[�̓����蔻�������֐�
extern BOOL MY_LOAD_CSV_MAP1(const char* path, MAP1* m, MAP1* mInit);	//�Q�[���}�b�v��CSV��ǂݍ��ފ֐�

//########## �O���̃O���[�o���ϐ� ##########
extern MAP1CHIP mapChip1;

extern MAP1 map1_sita[MAP1_TATE_MAX][MAP1_YOKO_MAX];
extern MAP1 mapInit1_sita[MAP1_TATE_MAX][MAP1_YOKO_MAX];

extern MAP1 map1_naka[MAP1_TATE_MAX][MAP1_YOKO_MAX];
extern MAP1 mapInit1_naka[MAP1_TATE_MAX][MAP1_YOKO_MAX];

extern MAP1 map1_ue[MAP1_TATE_MAX][MAP1_YOKO_MAX];
extern MAP1 mapInit1_ue[MAP1_TATE_MAX][MAP1_YOKO_MAX];

extern int Map1KabeID[MAP1_KABE_KIND];