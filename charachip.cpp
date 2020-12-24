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

	//�����蔻��̒���
	grif.choseiX = +16;
	grif.choseiY = +12;
	grif.choseiWidth = -16;
	grif.choseiHeight = +6;

	//�ŏ��͉E����
	grif.IsDirRight = TRUE;

	grif.imgChangeCnt = 0;
	grif.imgChangeCntMAX = GRIF_IMG_CHANGE_MAX;	//�摜��ύX����J�E���^MAX

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
				yusha.x += yusha.speed;	//�ړ�
				yusha.kind1++;			//���̉摜�ɂ���
				yusha.imgChangeCnt = 0;	//�ύX�J�E���^������
			}
		}
		else
		{

			yusha.kind1 = R_1;	//�ŏ��̉摜�ɂ���
		}

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
	//���O�̈ʒu���擾
	grif.oldx = grif.x;
	grif.oldy = grif.y;

	//�����I�ɉ��ɏd�͂𔭐�������
	grif.y += GAME_GR;

	//�����蔻��Čv�Z
	MY_CALC_GRIF_COLL();

	//�}�b�v�Q�Ɠ����蔻��i�W�����v�j
	MY_CHECK_MAP2_JUMP(&grif);

	//���ɍs������
	MY_PLAY_MOVE_LEFT();

	//�}�b�v�ƃv���C���[�̓����蔻��(��)������֐�
	MY_CHECK_MAP2_LEFT(&grif);

	//�E�ɍs������
	MY_PLAY_MOVE_RIGHT();

	//�}�b�v�ƃv���C���[�̓����蔻��(�E)������֐�
	MY_CHECK_MAP2_RIGHT(&grif);

	//�W�����v�̏���
	MY_PLAY_MOVE_JUMP();

	//�}�b�v�Q�Ƃ̓����蔻��i���j
	MY_CHECK_MAP2_DOWN(&grif);

	//���������Ă��Ȃ��Ƃ�
	if (MY_KEY_DOWN(KEY_INPUT_W) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_D) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_S) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_A) == FALSE)
	{
		//�W�����v���Ă��Ȃ��Ƃ���
		if (grif.IsJump == FALSE)
		{
			grif.imgChangeCnt = 0;	//�A�j���[�V�������~�߂�

			//�摜���~�܂��Ă���摜�ɂ���
			if (grif.kind1 >= GF_1 && grif.kind1 <= GF_3) { grif.kind1 = GF_2; }
			else if (grif.kind1 >= GL_1 && grif.kind1 <= GL_3) { grif.kind1 = GL_2; }
			else if (grif.kind1 >= GR_1 && grif.kind1 <= GR_3) { grif.kind1 = GR_2; }
			else if (grif.kind1 >= GB_1 && grif.kind1 <= GB_3) { grif.kind1 = GB_2; }
		}
	}

	//�R�C���Q�b�g����
	MY_GET_MAP2_COIN(grif);

	//�J�M�Q�b�g����
	if (MY_CHECK_MAP2_KEY(grif))
	{

	}

	//�h�A�ɐG�ꂽ�Ƃ��̏���
	if(MY_CHECK_MAP2_DOOR(grif))
	{

	}

	return;
}

//���ɍs������
VOID MY_PLAY_MOVE_LEFT(VOID)
{
	//���Ɉړ�����Ƃ�
	if (MY_KEY_DOWN(KEY_INPUT_A) == TRUE)
	{
		//���������Ă���
		grif.IsDirRight = FALSE;
		grif.IsDirLeft = TRUE;

		grif.x -= grif.speed;	//���ֈړ�
	}

	//���������Ă���Ƃ�
	if (grif.IsDirLeft == TRUE)
	{
		//�W�����v���Ă��Ȃ��Ƃ���
		if (grif.IsJump == FALSE)
		{
			//�����A�j���[�V�����œ�����
			MY_PLAY_ANIM_ARUKI(GL_1, GL_3);
		}
		else if (grif.IsJump == TRUE)	//�W�����v���Ă���Ƃ�
		{
			//�H�΂����̃A�j���[�V�����œ�����
			MY_PLAY_ANIM_HABATAKI(GFL_1, GFL_3);
		}
	}

	return;
}

//�E�ɍs������
VOID MY_PLAY_MOVE_RIGHT(VOID)
{
	//�E�Ɉړ�����Ƃ�
	if (MY_KEY_DOWN(KEY_INPUT_D) == TRUE)
	{
		//�E�������Ă���
		grif.IsDirRight = TRUE;
		grif.IsDirLeft = FALSE;

		//�E�ֈړ�
		grif.x += grif.speed;
	}

	//�E�������Ă���Ƃ�
	if (grif.IsDirRight == TRUE)
	{
		//�W�����v���Ă��Ȃ��Ƃ���
		if (grif.IsJump == FALSE)
		{
			//�����A�j���[�V�����œ�����
			MY_PLAY_ANIM_ARUKI(GR_1, GR_3);
		}
		else if (grif.IsJump == TRUE)	//�W�����v���Ă���Ƃ�
		{
			//�H�΂����̃A�j���[�V�����œ�����
			MY_PLAY_ANIM_HABATAKI(GFR_1, GFR_3);
		}
	}

	return;
}

//�W�����v�̏���
VOID MY_PLAY_MOVE_JUMP(VOID)
{
	//��ɃW�����v����Ƃ�
	if (MY_KEY_DOWN(KEY_INPUT_W) == TRUE)
	{
		//�n�ʂɂ������Ă���Ƃ�
		if (MY_CHECK_GRIF_GROUND(grif) == TRUE)
		{
			//�W�����v���Ă��Ȃ����
			if (grif.IsJump == FALSE)
			{
				grif.IsJump = TRUE;					//�W�����v����
				grif.BeforeJumpY = grif.y;			//�W�����v����O��Y�ʒu
				grif.JumpCnt = 0;					//�W�����v��
				grif.JumpCntMax = GRIF_JUMP_MAX;	//�W�����v��MAX
			}
		}
	}
	
	//�W�����v���Ă���Ƃ�
	if (grif.IsJump == TRUE)
	{
		//�W�����v�̏���
		if (grif.JumpCnt < grif.JumpCntMax)
		{
			if (grif.y - GAME_GR + GRIF_JUMP_POWER >= 0)	//��ʓ��ɂ���΁A
			{
				grif.y -= GAME_GR + GRIF_JUMP_POWER;	//�d�͂ɒ�R���Ȃ��ƁA��ׂȂ��E�E�E
			}
			else
			{
				grif.y -= GAME_GR;	//�d�͕��͒�R���Ȃ��ƁA�����ɗ�����E�E�E
			}

			grif.JumpCnt++;
		}
		else
		{
			grif.JumpCnt = 0;
			grif.IsJump = FALSE;
		}
	}

	return;
}

//########## �����A�j���[�V�����֐� ##########
//�����FMIN�F�A�j���[�V�����̊J�n�ԍ�
//�����FMAX�F�A�j���[�V�����̏I���ԍ�
VOID MY_PLAY_ANIM_ARUKI(GRIF_KIND_1 G_MIN, GRIF_KIND_1 G_MAX)
{
	if (grif.kind1 >= G_MIN && grif.kind1 <= G_MAX)
	{
		if (grif.imgChangeCnt == 0)	//�����ɉ摜��ύX
		{
			if (grif.kind1 < G_MAX) { grif.kind1++; }		//���̉摜�ɂ���
			else { grif.kind1 = G_MIN; }					//�ŏ��̉摜�ɂ���
			grif.imgChangeCnt++;
		}
		else if (grif.imgChangeCnt < grif.imgChangeCntMAX)	//�J�E���^�A�b�v
		{
			grif.imgChangeCnt++;
		}
		else if (grif.imgChangeCnt >= grif.imgChangeCntMAX)	//�J�E���^������
		{
			grif.imgChangeCnt = 0;	//�ύX�J�E���^������
		}
	}
	else
	{
		grif.kind1 = G_MIN;	//�ŏ��̉摜�ɂ���
	}
}

//########## �H�΂����̃A�j���[�V�����֐� ##########
//�����FMIN�F�A�j���[�V�����̊J�n�ԍ�
//�����FMAX�F�A�j���[�V�����̏I���ԍ�
VOID MY_PLAY_ANIM_HABATAKI(GRIF_KIND_2 GF_MIN, GRIF_KIND_2 GF_MAX)
{
	if (grif.kind2 >= GF_MIN && grif.kind2 <= GF_MAX)
	{
		if (grif.imgChangeCnt == 0)	//�����ɉ摜��ύX
		{
			if (grif.kind2 < GF_MAX) { grif.kind2++; }		//���̉摜�ɂ���
			else { grif.kind2 = GF_MIN; }					//�ŏ��̉摜�ɂ���
			grif.imgChangeCnt++;
		}
		else if (grif.imgChangeCnt < grif.imgChangeCntMAX)	//�J�E���^�A�b�v
		{
			grif.imgChangeCnt++;
		}
		else if (grif.imgChangeCnt >= grif.imgChangeCntMAX)	//�J�E���^������
		{
			grif.imgChangeCnt = 0;	//�ύX�J�E���^������
		}
	}
	else
	{
		grif.kind2 = GF_MIN;	//�ŏ��̉摜�ɂ���
	}
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
	grif.coll.left = grif.x + grif.choseiX;
	grif.coll.top = grif.y + grif.choseiY;
	grif.coll.right = grif.x + grif.width + grif.choseiWidth;
	grif.coll.bottom = grif.y + grif.height + grif.choseiHeight;
	return;
}