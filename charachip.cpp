/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//�L�����`�b�v�Ŏg�p���郂�m���܂Ƃ߂Ă��܂�

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "game.h"
#include "charachip.h"
#include "mapchip.h"

//########## �O���[�o���ϐ� ##########

//�E�҂̃L�����`�b�v�̉摜���Ǘ�
YUSHACHIP yushaChip1;	//�E�҂̉摜�P�i�㉺���E�j
YUSHACHIP yushaChip2;	//�E�҂̉摜�Q�i�΂߁j

//�E�҂̏����Ǘ�
YUSHA yusha;

//########## �E�҃`�b�v��ǂݍ��ފ֐� ##########
//�����P�F�摜�̃p�X
//�����Q�F�}�b�v�z��̐擪�A�h���X
BOOL MY_LOAD_CHARA_YUSHA(const char* path, YUSHACHIP* yusha)
{
	//�}�b�v�̉摜�𕪊�����
	int mapRes = LoadDivGraph(
		path,												//�p�X
		YUSHA_DIV_NUM, YUSHA_DIV_TATE, YUSHA_DIV_YOKO,		//�������鐔
		YUSHA_DIV_WIDTH, YUSHA_DIV_HEIGHT,					//��������̕��ƍ���
		&yusha->handle[0]);								//�摜������n���h��

	if (mapRes == -1)	//�G���[���b�Z�[�W�\��
	{
		MessageBox(GetMainWindowHandle(), path, IMAGE_LOAD_ERR_TITLE, MB_OK); return FALSE;
	}

	//���ƍ������擾
	GetGraphSize(yusha->handle[0], &yusha->width, &yusha->height);

	return TRUE;
}
//########## �E�҂̈ʒu�������� ##########
VOID MY_INIT_YUSHA(VOID)
{
	yusha.x = MAP_DIV_WIDTH * 0;	//�}�b�v�̃T�C�Y����Ɍ��߂�
	yusha.y = MAP_DIV_HEIGHT * 5;	//�}�b�v�̃T�C�Y����Ɍ��߂�;
	yusha.IsMoveNaname = FALSE;
	yusha.kind1 = D_1;
	yusha.kind2 = LD_1;
	yusha.speed = YUSHA_MOVE_SPEED;	//�ړ����x

	//���ƍ�����ݒ�
	yusha.width = yushaChip1.width;
	yusha.height = yushaChip1.height;
	
	yusha.imgChangeCnt = 0;
	yusha.imgChangeCntMAX = YUSHA_IMG_CHANGE_MAX;	//�摜��ύX����J�E���^MAX

	return;
}

//########## �E�҂��ړ�������֐� ##########
VOID MY_MOVE_YUSHA(VOID)
{
	//���͂ɉ����ĉ摜��ς���

	//��Ɉړ�����Ƃ�
	if (MY_KEY_DOWN(KEY_INPUT_W) == TRUE
		&& MY_KEY_DOWN(KEY_INPUT_D) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_S) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_A) == FALSE)
	{
		yusha.IsMoveNaname = FALSE;	//�΂߈ړ����Ă��Ȃ�

		if (yusha.kind1 >= U_1 && yusha.kind1 < U_3)
		{
			//�摜�ύX�J�E���^
			if (yusha.imgChangeCnt < yusha.imgChangeCntMAX)
			{
				yusha.imgChangeCnt++;
			}
			else //�摜��ς���^�C�~���O�ɂȂ�����
			{
				yusha.kind1++;			//���̉摜�ɂ���
				yusha.imgChangeCnt = 0;	//�ύX�J�E���^������
			}
		}
		else
		{
			yusha.kind1 = U_1;	//�ŏ��̉摜�ɂ���
		}

		yusha.y -= yusha.speed;	//�ړ�
	}

	//�E�Ɉړ�����Ƃ�
	if (MY_KEY_DOWN(KEY_INPUT_W) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_D) == TRUE
		&& MY_KEY_DOWN(KEY_INPUT_S) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_A) == FALSE)
	{
		yusha.IsMoveNaname = FALSE;	//�΂߈ړ����Ă��Ȃ�

		if (yusha.kind1 >= R_1 && yusha.kind1 < R_3)
		{
			//�摜�ύX�J�E���^
			if (yusha.imgChangeCnt < yusha.imgChangeCntMAX)
			{
				yusha.imgChangeCnt++;
			}
			else //�摜��ς���^�C�~���O�ɂȂ�����
			{
				yusha.kind1++;			//���̉摜�ɂ���
				yusha.imgChangeCnt = 0;	//�ύX�J�E���^������
			}
		}
		else
		{
			yusha.kind1 = R_1;	//�ŏ��̉摜�ɂ���
		}
		yusha.x += yusha.speed;	//�ړ�
	}

	//���Ɉړ�����Ƃ�
	if (MY_KEY_DOWN(KEY_INPUT_W) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_D) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_S) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_A) == TRUE)
	{
		yusha.IsMoveNaname = FALSE;	//�΂߈ړ����Ă��Ȃ�

		if (yusha.kind1 >= L_1 && yusha.kind1 < L_3)
		{
			//�摜�ύX�J�E���^
			if (yusha.imgChangeCnt < yusha.imgChangeCntMAX)
			{
				yusha.imgChangeCnt++;
			}
			else //�摜��ς���^�C�~���O�ɂȂ�����
			{
				yusha.kind1++;			//���̉摜�ɂ���
				yusha.imgChangeCnt = 0;	//�ύX�J�E���^������
			}
		}
		else
		{
			yusha.kind1 = L_1;	//�ŏ��̉摜�ɂ���
		}
		yusha.x -= yusha.speed;	//�ړ�
	}

	//���Ɉړ�����Ƃ�
	if (MY_KEY_DOWN(KEY_INPUT_W) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_D) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_S) == TRUE
		&& MY_KEY_DOWN(KEY_INPUT_A) == FALSE)
	{
		yusha.IsMoveNaname = FALSE;	//�΂߈ړ����Ă��Ȃ�

		if (yusha.kind1 >= D_1 && yusha.kind1 < D_3)
		{
			//�摜�ύX�J�E���^
			if (yusha.imgChangeCnt < yusha.imgChangeCntMAX)
			{
				yusha.imgChangeCnt++;
			}
			else //�摜��ς���^�C�~���O�ɂȂ�����
			{
				yusha.kind1++;			//���̉摜�ɂ���
				yusha.imgChangeCnt = 0;	//�ύX�J�E���^������
			}
		}
		else
		{
			yusha.kind1 = D_1;	//�ŏ��̉摜�ɂ���
		}
		yusha.y += yusha.speed;	//�ړ�
	}

	//�����Ɉړ�����Ƃ�
	if (MY_KEY_DOWN(KEY_INPUT_W) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_D) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_S) == TRUE
		&& MY_KEY_DOWN(KEY_INPUT_A) == TRUE)
	{
		yusha.IsMoveNaname = TRUE;	//�΂߈ړ����Ă���

		if (yusha.kind2 >= LD_1 && yusha.kind2 < LD_3)
		{
			//�摜�ύX�J�E���^
			if (yusha.imgChangeCnt < yusha.imgChangeCntMAX)
			{
				yusha.imgChangeCnt++;
			}
			else //�摜��ς���^�C�~���O�ɂȂ�����
			{
				yusha.kind2++;			//���̉摜�ɂ���
				yusha.imgChangeCnt = 0;	//�ύX�J�E���^������
			}
		}
		else
		{
			yusha.kind2 = LD_1;	//�ŏ��̉摜�ɂ���
		}
		yusha.x -= yusha.speed;	//�ړ�
		yusha.y += yusha.speed;	//�ړ�
	}

	//�㍶�Ɉړ�����Ƃ�
	if (MY_KEY_DOWN(KEY_INPUT_W) == TRUE
		&& MY_KEY_DOWN(KEY_INPUT_D) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_S) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_A) == TRUE)
	{
		yusha.IsMoveNaname = TRUE;	//�΂߈ړ����Ă���

		if (yusha.kind2 >= LU_1 && yusha.kind2 < LU_3)
		{
			//�摜�ύX�J�E���^
			if (yusha.imgChangeCnt < yusha.imgChangeCntMAX)
			{
				yusha.imgChangeCnt++;
			}
			else //�摜��ς���^�C�~���O�ɂȂ�����
			{
				yusha.kind2++;			//���̉摜�ɂ���
				yusha.imgChangeCnt = 0;	//�ύX�J�E���^������
			}
		}
		else
		{
			yusha.kind2 = LU_1;	//�ŏ��̉摜�ɂ���
		}
		yusha.x -= yusha.speed;	//�ړ�
		yusha.y -= yusha.speed;	//�ړ�
	}

	//���E�Ɉړ�����Ƃ�
	if (MY_KEY_DOWN(KEY_INPUT_W) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_D) == TRUE
		&& MY_KEY_DOWN(KEY_INPUT_S) == TRUE
		&& MY_KEY_DOWN(KEY_INPUT_A) == FALSE)
	{
		yusha.IsMoveNaname = TRUE;	//�΂߈ړ����Ă���

		if (yusha.kind2 >= RD_1 && yusha.kind2 < RD_3)
		{
			//�摜�ύX�J�E���^
			if (yusha.imgChangeCnt < yusha.imgChangeCntMAX)
			{
				yusha.imgChangeCnt++;
			}
			else //�摜��ς���^�C�~���O�ɂȂ�����
			{
				yusha.kind2++;			//���̉摜�ɂ���
				yusha.imgChangeCnt = 0;	//�ύX�J�E���^������
			}
		}
		else
		{
			yusha.kind2 = RD_1;	//�ŏ��̉摜�ɂ���
		}
		yusha.x += yusha.speed;	//�ړ�
		yusha.y += yusha.speed;	//�ړ�
	}

	//��E�Ɉړ�����Ƃ�
	if (MY_KEY_DOWN(KEY_INPUT_W) == TRUE
		&& MY_KEY_DOWN(KEY_INPUT_D) == TRUE
		&& MY_KEY_DOWN(KEY_INPUT_S) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_A) == FALSE)
	{
		yusha.IsMoveNaname = TRUE;	//�΂߈ړ����Ă���

		if (yusha.kind2 >= RU_1 && yusha.kind2 < RU_3)
		{
			//�摜�ύX�J�E���^
			if (yusha.imgChangeCnt < yusha.imgChangeCntMAX)
			{
				yusha.imgChangeCnt++;
			}
			else //�摜��ς���^�C�~���O�ɂȂ�����
			{
				yusha.kind2++;			//���̉摜�ɂ���
				yusha.imgChangeCnt = 0;	//�ύX�J�E���^������
			}
		}
		else
		{
			yusha.kind2 = RU_1;	//�ŏ��̉摜�ɂ���
		}
		yusha.x += yusha.speed;	//�ړ�
		yusha.y -= yusha.speed;	//�ړ�
	}

	//���������Ă��Ȃ��Ƃ�
	if (MY_KEY_DOWN(KEY_INPUT_W) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_D) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_S) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_A) == FALSE)
	{
		yusha.imgChangeCnt = 0;		//�ύX�J�E���^������

		//�摜���~�܂��Ă���摜�ɂ���
		if (yusha.kind1 >= U_1 && yusha.kind1 <= U_3) { yusha.kind1 = U_2; }
		else if (yusha.kind1 >= R_1 && yusha.kind1 <= R_3) { yusha.kind1 = R_2; }
		else if (yusha.kind1 >= L_1 && yusha.kind1 <= L_3) { yusha.kind1 = L_2; }
		else if (yusha.kind1 >= D_1 && yusha.kind1 <= D_3) { yusha.kind1 = D_2; }

		if (yusha.kind2 >= LD_1 && yusha.kind2 <= LD_3) { yusha.kind2 = LD_2; }
		else if (yusha.kind2 >= LU_1 && yusha.kind2 <= LU_3) { yusha.kind2 = LU_2; }
		else if (yusha.kind2 >= RD_1 && yusha.kind2 <= RD_3) { yusha.kind2 = RD_2; }
		else if (yusha.kind2 >= RU_1 && yusha.kind2 <= RU_3) { yusha.kind2 = RU_2; }
	}
	return;
}

//########## �E�҂�`�悷��֐� ##########
VOID MY_DRAW_YUSHA(VOID)
{
	//�㉺���E�̈ړ��̂Ƃ�
	if (yusha.IsMoveNaname == FALSE)	//�㉺���E�̈ړ��̂Ƃ�
	{
		DrawGraph(yusha.x, yusha.y, yushaChip1.handle[yusha.kind1], TRUE);
	}
	else //�΂߂̈ړ��̂Ƃ�
	{
		DrawGraph(yusha.x, yusha.y, yushaChip2.handle[yusha.kind2], TRUE);
	}


	return;
}