/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//�}�b�v�`�b�v�Ŏg�p���郂�m���܂Ƃ߂Ă��܂�
#pragma once

//�w�b�_�[�t�@�C���ǂݍ���
#include "DxLib.h"
#include "game.h"
#include "charachip.h"

//�}�N����`
#define MAP1_PATH			TEXT(".\\IMAGE\\MAP\\mapchip1.png")			//�}�b�v�̉摜
#define MAP1_PATH_SITA_CSV	TEXT(".\\IMAGE\\MAP\\map1_sita.csv")	//�}�b�vCSV(��)
#define MAP1_PATH_NAKA_CSV	TEXT(".\\IMAGE\\MAP\\map1_naka.csv")	//�}�b�vCSV(��)
#define MAP1_PATH_UE_CSV	TEXT(".\\IMAGE\\MAP\\map1_ue.csv")		//�}�b�vCSV(��)

#define MAP1_TATE_MAX	10	//�}�b�v�̏c�̍L��
#define MAP1_YOKO_MAX	20	//�}�b�v�̉��̍L��

#define MAP1_KABE_KIND	8	//�}�b�v�̕ǂ̎��

#define MAP1_DIV_WIDTH		32	//�}�b�v�`�b�v�̂P���̕��T�C�Y
#define MAP1_DIV_HEIGHT		32	//�}�b�v�`�b�v�̂P���̍����T�C�Y

#define MAP1_DIV_TATE		32	//�}�b�v�`�b�v���c�ɕ������鐔
#define MAP1_DIV_YOKO		41	//�}�b�v�`�b�v�����ɕ������鐔
#define MAP1_DIV_NUM	MAP1_DIV_TATE * MAP1_DIV_YOKO	//�}�b�v�`�b�v�𕪊����鑍��

#define MAP2_PATH			TEXT(".\\IMAGE\\MAP\\mapchip2.png")			//�}�b�v�̉摜
#define MAP2_PATH_SITA_CSV	TEXT(".\\IMAGE\\MAP\\map2_sita.csv")	//�}�b�vCSV(��)
#define MAP2_PATH_NAKA_CSV	TEXT(".\\IMAGE\\MAP\\map2_naka.csv")	//�}�b�vCSV(��)
#define MAP2_PATH_UE_CSV	TEXT(".\\IMAGE\\MAP\\map2_ue.csv")		//�}�b�vCSV(��)

#define MAP2_TATE_MAX	15	//�}�b�v�̏c�̍L��
#define MAP2_YOKO_MAX	20	//�}�b�v�̉��̍L��

#define MAP2_KABE_KIND	8	//�}�b�v�̕ǂ̎��

#define MAP2_DIV_WIDTH		32	//�}�b�v�`�b�v�̂P���̕��T�C�Y
#define MAP2_DIV_HEIGHT		32	//�}�b�v�`�b�v�̂P���̍����T�C�Y

#define MAP2_DIV_TATE		58	//�}�b�v�`�b�v���c�ɕ������鐔
#define MAP2_DIV_YOKO		35	//�}�b�v�`�b�v�����ɕ������鐔
#define MAP2_DIV_NUM	MAP2_DIV_TATE * MAP2_DIV_YOKO	//�}�b�v�`�b�v�𕪊����鑍��

#define MAP2_DOOR_MAX	8		//�h�A�̔ԍ��̎��

//�񋓌^
enum MAP1_KIND {
	MAP1_KIND_KABE,	//��
	MAP1_KIND_TURO,	//�ʘH
};

enum MAP2_KIND {
	MAP2_KIND_KABE,	//�u���b�N
	MAP2_KIND_TURO,	//�ʘH
	MAP2_KIND_NONE,	//�����Ȃ�
	MAP2_KIND_COIN,	//�J�M
	MAP2_KIND_DOOR	//�h�A
};

//�\���̒�`
typedef struct STRUCT_MAPCHIP1
{
	char path[PATH_MAX];				//�p�X
	int handle[MAP1_DIV_NUM];			//���������摜�n���h�����擾
	int width;							//��
	int height;							//����
}MAPCHIP1;	//MAP1CHIP�\���́i�}�b�v�`�b�v�̃f�[�^�������Ă���j

typedef struct STRUCT_MAP1
{
	int value;			//�}�b�v�̒l
	MAP1_KIND kind;		//�}�b�v�̎��
	int x;				//X�ʒu
	int y;				//Y�ʒu
	int width;			//��
	int height;			//����
	RECT coll;			//�}�b�v�̓����蔻��
}MAP1;					//MAP1�\���́i�Q�[���Ŏg�p����f�[�^�������Ă���j

typedef struct STRUCT_MAPCHIP2
{
	char path[PATH_MAX];				//�p�X
	int handle[MAP2_DIV_NUM];			//���������摜�n���h�����擾
	int width;							//��
	int height;							//����
}MAPCHIP2;	//MAP1CHIP�\���́i�}�b�v�`�b�v�̃f�[�^�������Ă���j

typedef struct STRUCT_MAP2
{
	int value;			//�}�b�v�̒l
	MAP2_KIND kind;		//�}�b�v�̎��
	int x;				//X�ʒu
	int y;				//Y�ʒu
	int width;			//��
	int height;			//����
	RECT coll;			//�}�b�v�̓����蔻��
}MAP2;					//MAP2�\���́i�Q�[���Ŏg�p����f�[�^�������Ă���j

typedef struct STRUCT_DOOR_KIND
{
	int x;			//�h�A�̏ꏊX�ʒu
	int y;			//�h�A�̏ꏊY�ʒu
}DOOR_NUMBER;		//�h�A�̔ԍ�

//########## �O���̃v���g�^�C�v�錾 ##########
extern BOOL MY_LOAD_MAPCHIP1(VOID);										//�}�b�v�`�b�v��ǂݍ��ފ֐�
extern BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT rect);						//�}�b�v�ƃv���C���[�̓����蔻�������֐�
extern BOOL MY_LOAD_CSV_MAP1(const char* path, MAP1* m, MAP1* mInit);	//�Q�[���}�b�v��CSV��ǂݍ��ފ֐�

extern BOOL MY_LOAD_MAPCHIP2(VOID);										//�}�b�v�`�b�v��ǂݍ��ފ֐�
extern BOOL MY_LOAD_CSV_MAP2(const char* path, MAP2* m, MAP2* mInit);	//�Q�[���}�b�v��CSV��ǂݍ��ފ֐�
extern VOID MY_CHECK_MAP2_DOWN(GRIF* g);								//�}�b�v�ƃv���C���[�̓����蔻�������֐�(��)
extern VOID MY_CHECK_MAP2_JUMP(GRIF* g);								//�}�b�v�ƃv���C���[�̓����蔻��(�W�����v)������֐�
extern VOID MY_CHECK_MAP2_LEFT(GRIF* g);								//�}�b�v�ƃv���C���[�̓����蔻��(��)������֐�
extern VOID MY_CHECK_MAP2_RIGHT(GRIF* g);								//�}�b�v�ƃv���C���[�̓����蔻��(�E)������֐�
extern BOOL MY_CHECK_GRIF_GROUND(GRIF g);								//�v���C���[���n�ʂƐڂ��Ă��邩�����蔻�������֐�

extern BOOL MY_CHECK_MAP2_DOOR(GRIF g);	//�}�b�v�ƃv���C���[�̓����蔻��(�h�A)������֐�
extern VOID MY_GET_MAP2_COIN(GRIF g);	//�}�b�v�ƃv���C���[�̓����蔻��(�R�C��)������֐�

//########## �O���̃O���[�o���ϐ� ##########
extern MAPCHIP1 mapChip1;

extern MAP1 map1_sita[MAP1_TATE_MAX][MAP1_YOKO_MAX];
extern MAP1 mapInit1_sita[MAP1_TATE_MAX][MAP1_YOKO_MAX];

extern MAP1 map1_naka[MAP1_TATE_MAX][MAP1_YOKO_MAX];
extern MAP1 mapInit1_naka[MAP1_TATE_MAX][MAP1_YOKO_MAX];

extern MAP1 map1_ue[MAP1_TATE_MAX][MAP1_YOKO_MAX];
extern MAP1 mapInit1_ue[MAP1_TATE_MAX][MAP1_YOKO_MAX];

extern int Map1KabeID[MAP1_KABE_KIND];

extern MAPCHIP2 mapChip2;

extern MAP2 map2_sita[MAP1_TATE_MAX][MAP1_YOKO_MAX];		//�}�b�v�f�[�^�Q�i���j
extern MAP2 mapInit2_sita[MAP1_TATE_MAX][MAP1_YOKO_MAX];	//�ŏ��̃}�b�v�f�[�^�Q�i���j

extern MAP2 map2_naka[MAP1_TATE_MAX][MAP1_YOKO_MAX];		//�}�b�v�f�[�^�Q�i���j
extern MAP2 mapInit2_naka[MAP1_TATE_MAX][MAP1_YOKO_MAX];	//�ŏ��̃}�b�v�f�[�^�Q�i���j

extern MAP2 map2_ue[MAP1_TATE_MAX][MAP1_YOKO_MAX];			//�}�b�v�f�[�^�Q�i��j
extern MAP2 mapInit2_ue[MAP1_TATE_MAX][MAP1_YOKO_MAX];		//�ŏ��̃}�b�v�f�[�^�Q�i��j

extern int Map2KabeID[MAP2_KABE_KIND];	//�ǂ�ID

extern int Map2KeyID;	//����ID
extern int Map2DoorID;	//�h�A��ID
