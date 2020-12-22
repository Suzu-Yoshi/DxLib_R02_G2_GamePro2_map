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

//�O���t�B���̃L�����`�b�v�̉摜���Ǘ�
GRIFCHIP grifChip1;		//�O���t�B���̉摜�P�i�㉺���E�j
GRIFCHIP grifChip2;		//�O���t�B���̉摜�Q�i�΂߁j

//�O���t�B���̏����Ǘ�
GRIF grif;

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

//########## �O���t�B���`�b�v��ǂݍ��ފ֐� ##########
//�����P�F�摜�̃p�X
//�����Q�F�}�b�v�z��̐擪�A�h���X
BOOL MY_LOAD_CHARA_GRIF(const char* path, GRIFCHIP* grif)
{
	//�}�b�v�̉摜�𕪊�����
	int mapRes = LoadDivGraph(
		path,												//�p�X
		GRIF_DIV_NUM, GRIF_DIV_TATE, GRIF_DIV_YOKO,			//�������鐔
		GRIF_DIV_WIDTH, GRIF_DIV_HEIGHT,					//��������̕��ƍ���
		&grif->handle[0]);									//�摜������n���h��

	if (mapRes == -1)	//�G���[���b�Z�[�W�\��
	{
		MessageBox(GetMainWindowHandle(), path, IMAGE_LOAD_ERR_TITLE, MB_OK); return FALSE;
	}

	//���ƍ������擾
	GetGraphSize(grif->handle[0], &grif->width, &grif->height);

	return TRUE;
}

//########## �E�҂̈ʒu�������� ##########
VOID MY_INIT_YUSHA(VOID)
{
	yusha.x = MAP1_DIV_WIDTH * 0;	//�}�b�v�̃T�C�Y����Ɍ��߂�
	yusha.y = MAP1_DIV_HEIGHT * 5;	//�}�b�v�̃T�C�Y����Ɍ��߂�;
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

//########## �O���t�B���̈ʒu�������� ##########
VOID MY_INIT_GRIF(VOID)
{
	grif.x = MAP1_DIV_WIDTH * 0;		//�}�b�v�̃T�C�Y����Ɍ��߂�
	grif.y = MAP1_DIV_HEIGHT * 0;		//�}�b�v�̃T�C�Y����Ɍ��߂�;
	grif.kind1 = GL_1;
	grif.kind2 = GFR_1;
	grif.speed = GRIF_MOVE_SPEED;	//�ړ����x

	//���ƍ�����ݒ�
	grif.width = grifChip1.width;
	grif.height = grifChip1.height;

	grif.imgChangeCnt = 0;
	grif.imgChangeCntMAX = YUSHA_IMG_CHANGE_MAX;	//�摜��ύX����J�E���^MAX

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

//########## �O���t�B�����ړ�������֐� ##########
VOID MY_MOVE_GRIF(VOID)
{
	//���͂ɉ����ĉ摜��ς���

	//��Ɉړ�����Ƃ�
	if (MY_KEY_DOWN(KEY_INPUT_W) == TRUE)
	{
		grif.IsJump = TRUE;	//�W�����v

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
			grif.kind1 = U_1;	//�ŏ��̉摜�ɂ���
		}
		grif.y -= GAME_GR + grif.speed;	//�d�͂ɏ���
	}


	//���Ɉړ�����Ƃ�
	if (MY_KEY_DOWN(KEY_INPUT_A) == TRUE)
	{
		grif.IsJump = FALSE;
		if (grif.kind1 >= L_1 && grif.kind1 < L_3)
		{
			//�摜�ύX�J�E���^
			if (grif.imgChangeCnt < grif.imgChangeCntMAX)
			{
				grif.imgChangeCnt++;
			}
			else //�摜��ς���^�C�~���O�ɂȂ�����
			{
				grif.kind1++;			//���̉摜�ɂ���
				grif.imgChangeCnt = 0;	//�ύX�J�E���^������
			}
		}
		else
		{
			grif.kind1 = L_1;	//�ŏ��̉摜�ɂ���
		}
		grif.x -= grif.speed;
		grif.IsMoveLeft = TRUE;
	}
	else
	{
		grif.IsMoveLeft = FALSE;
	}

	//�E�Ɉړ�����Ƃ�
	if (MY_KEY_DOWN(KEY_INPUT_D) == TRUE)
	{
		grif.IsJump = FALSE;
		if (grif.kind1 >= R_1 && grif.kind1 < R_3)
		{
			//�摜�ύX�J�E���^
			if (grif.imgChangeCnt < grif.imgChangeCntMAX)
			{
				grif.imgChangeCnt++;
			}
			else //�摜��ς���^�C�~���O�ɂȂ�����
			{
				grif.kind1++;			//���̉摜�ɂ���
				grif.imgChangeCnt = 0;	//�ύX�J�E���^������
			}
		}
		else
		{
			grif.kind1 = R_1;	//�ŏ��̉摜�ɂ���
		}
		grif.x += grif.speed;
		grif.IsMoveRight = TRUE;
	}
	else
	{
		grif.IsMoveRight = FALSE;
	}

	//���������Ă��Ȃ��Ƃ�
	if (MY_KEY_DOWN(KEY_INPUT_W) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_D) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_S) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_A) == FALSE)
	{
		grif.imgChangeCnt = 0;		//�ύX�J�E���^������

		//�摜���~�܂��Ă���摜�ɂ���
		if (grif.kind1 >= GF_1 && grif.kind1 <= GF_3) { grif.kind1 = GF_2; }
		else if (grif.kind1 >= GL_1 && grif.kind1 <= GL_3) { grif.kind1 = GL_2; }
		else if (grif.kind1 >= GR_1 && grif.kind1 <= GR_3) { grif.kind1 = GR_2; }
		else if (grif.kind1 >= GB_1 && grif.kind1 <= GB_3) { grif.kind1 = GB_2; }

		if (grif.kind2 >= GFF_1 && grif.kind2 <= GFF_3) { grif.kind2 = GFF_2; }
		else if (grif.kind2 >= GFL_1 && grif.kind2 <= GFL_3) { grif.kind2 = GFL_2; }
		else if (grif.kind2 >= GFR_1 && grif.kind2 <= GFR_3) { grif.kind2 = GFR_2; }
		else if (grif.kind2 >= GFB_1 && grif.kind2 <= GFB_3) { grif.kind2 = GFB_2; }
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

//########## �O���t�B����`�悷��֐� ##########
VOID MY_DRAW_GRIF(VOID)
{
	//�㉺���E�̈ړ��̂Ƃ�
	if (grif.IsJump == FALSE)	//�㉺���E�̈ړ��̂Ƃ�
	{
		DrawGraph(grif.x, grif.y, grifChip1.handle[grif.kind1], TRUE);
	}
	else //�W�����v�̂Ƃ�
	{
		DrawGraph(grif.x, grif.y, grifChip2.handle[grif.kind2], TRUE);
	}

	return;
}

//########## �v���C���[�̓����蔻����Čv�Z����֐� ##########
VOID MY_CALC_GRIF_COLL(VOID)
{
	//�i�����蔻��𒲐��j
	grif.coll.left = grif.x + 12;
	grif.coll.top = grif.y + 12;
	grif.coll.right = grif.x + grif.width - 12;
	grif.coll.bottom = grif.y + grif.height + 4;
	return;
}