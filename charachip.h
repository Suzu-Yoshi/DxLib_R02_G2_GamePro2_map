/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//�L�����`�b�v�Ŏg�p���郂�m���܂Ƃ߂Ă��܂�
//��Ƃ��āA�E�҂ɂ��Ă��܂��B�C���C���ƃJ�X�^�}�C�Y���Ă��������ˁB
#pragma once

//�w�b�_�[�t�@�C���ǂݍ���
#include "DxLib.h"
#include "game.h"

//�摜�̃p�X
#define YUSHA_CHIP1_PATH	TEXT(".\\IMAGE\\CHARA\\charaF01_1a1.png")			//�E�҂̉摜�P�i�㉺���E�j
#define YUSHA_CHIP2_PATH	TEXT(".\\IMAGE\\CHARA\\charaF01_1a1-X.png")			//�E�҂̉摜�Q�i�΂߁j

#define YUSHA_DIV_WIDTH		48	//�E�҂̃L�����`�b�v�̂P���̕��T�C�Y
#define YUSHA_DIV_HEIGHT	48	//�E�҂̃L�����`�b�v�̂P���̍����T�C�Y

#define YUSHA_DIV_TATE		3	//�E�҂̃L�����`�b�v���c�ɕ������鐔
#define YUSHA_DIV_YOKO		4	//�E�҂̃L�����`�b�v�����ɕ������鐔
#define YUSHA_DIV_NUM	YUSHA_DIV_TATE * YUSHA_DIV_YOKO	//�E�҂̃L�����`�b�v�𕪊����鑍��

#define YUSHA_IMG_CHANGE_MAX	10	//�摜��ύX����J�E���^MAX�l
#define YUSHA_MOVE_SPEED		2	//�ړ����x

//�񋓌^
//���Ӂj�E�҂̃L�����`�b�v�����Č��߂Ă��܂��B
//���P�j���オ0�A�E�Ɍ������ā{�P����܂�
//���Q�j��ԉE�܂ōs������A���ɐ܂�Ԃ��ā{�P����܂�
enum YUSHA_KIND_1 {
	D_1, D_2, D_3,
	L_1, L_2, L_3,
	R_1, R_2, R_3,
	U_1, U_2, U_3
};//�E�҂̉摜�̎�ނP(U��/D��/R�E/L��)

enum YUSHA_KIND_2 {
	LD_1, LD_2, LD_3,
	LU_1, LU_2, LU_3,
	RD_1, RD_2, RD_3,
	RU_1, RU_2, RU_3
};//�E�҂̉摜�̎�ނQ(LD����/LU�E��/RD�E��/RU�E��)

//�\���̒�`
typedef struct STRUCT_YUSHACHIP
{
	char path[PATH_MAX];				//�p�X
	int handle[YUSHA_DIV_NUM];			//���������摜�n���h�����擾
	int width;							//��
	int height;							//����
}YUSHACHIP;	//YUSHACHIP�\���́i�E�҂̃L�����`�b�v�̃f�[�^�������Ă���j

typedef struct STRUCT_YUSHA
{
	int kind1;			//�摜�̎�ނP
	int kind2;			//�摜�̎�ނQ
	int x;				//X�ʒu
	int y;				//Y�ʒu
	int oldx;			//X�ʒu(���O)
	int oldy;			//Y�ʒu(���O)
	int width;			//��
	int height;			//����
	int speed;			//�ړ����x
	
	BOOL IsMoveNaname;	//�΂߈ړ������Ă��邩

	int imgChangeCnt;	//�摜�X�V�J�E���^
	int imgChangeCntMAX;//�摜�X�V�J�E���^MAX�l

	RECT coll;			//�����蔻��

}YUSHA;	//�E�ҍ\����

//�O���̃v���g�^�C�v�錾
extern BOOL MY_LOAD_CHARA_YUSHA(const char* path, YUSHACHIP* yusha);	//�E�҂̉摜��ǂݍ���
extern VOID MY_DRAW_YUSHA(VOID);										//�E�҂�`�悷��֐�
extern VOID MY_INIT_YUSHA(VOID);										//�E�҂̈ʒu��������
extern VOID MY_MOVE_YUSHA(VOID);										//�E�҂��ړ�������֐�

//�O���̃O���[�o���ϐ�
extern YUSHACHIP yushaChip1;	//�E�҂̉摜�P�i�㉺���E�j
extern YUSHACHIP yushaChip2;	//�E�҂̉摜�Q�i�΂߁j
extern YUSHA yusha;				//�E�҂̏����Ǘ�