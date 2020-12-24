/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//�}�b�v�`�b�v�Ŏg�p���郂�m���܂Ƃ߂Ă��܂�

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "game.h"
#include "mapchip.h"

//########## �O���[�o���ϐ� ##########

//�}�b�v�`�b�v�̉摜���Ǘ�
MAPCHIP1 mapChip1;

MAP1 map1_sita[MAP1_TATE_MAX][MAP1_YOKO_MAX];		//�}�b�v�f�[�^�P�i���j
MAP1 mapInit1_sita[MAP1_TATE_MAX][MAP1_YOKO_MAX];	//�ŏ��̃}�b�v�f�[�^�P�i���j

MAP1 map1_naka[MAP1_TATE_MAX][MAP1_YOKO_MAX];		//�}�b�v�f�[�^�P�i���j
MAP1 mapInit1_naka[MAP1_TATE_MAX][MAP1_YOKO_MAX];	//�ŏ��̃}�b�v�f�[�^�P�i���j

MAP1 map1_ue[MAP1_TATE_MAX][MAP1_YOKO_MAX];		//�}�b�v�f�[�^�P�i��j
MAP1 mapInit1_ue[MAP1_TATE_MAX][MAP1_YOKO_MAX];	//�ŏ��̃}�b�v�f�[�^�P�i��j

int Map1KabeID[MAP1_KABE_KIND] = { 34,35,66,67,257,258,350,409 };	//�ǂ�ID

//�}�b�v�`�b�v�̉摜���Ǘ�
MAPCHIP2 mapChip2;

MAP2 map2_sita[MAP1_TATE_MAX][MAP1_YOKO_MAX];		//�}�b�v�f�[�^�Q�i���j
MAP2 mapInit2_sita[MAP1_TATE_MAX][MAP1_YOKO_MAX];	//�ŏ��̃}�b�v�f�[�^�Q�i���j

MAP2 map2_naka[MAP1_TATE_MAX][MAP1_YOKO_MAX];		//�}�b�v�f�[�^�Q�i���j
MAP2 mapInit2_naka[MAP1_TATE_MAX][MAP1_YOKO_MAX];	//�ŏ��̃}�b�v�f�[�^�Q�i���j

MAP2 map2_ue[MAP1_TATE_MAX][MAP1_YOKO_MAX];			//�}�b�v�f�[�^�Q�i��j
MAP2 mapInit2_ue[MAP1_TATE_MAX][MAP1_YOKO_MAX];		//�ŏ��̃}�b�v�f�[�^�Q�i��j

int Map2KabeID[MAP2_KABE_KIND] = { 928,986,987,988,989,1044,1045,1046 };	//�ǂ�ID(Tiled�Ŋm�F�I)

int Map2NoneID = 0;		//�u�Ȃɂ��Ȃ��v��ID(Tiled�Ŋm�F�I) 
int Map2KeyID = 2006;	//����ID(Tiled�Ŋm�F�I) 
int Map2CoinID = 1990;	//�R�C����ID(Tiled�Ŋm�F�I) 
int Map2DoorID = 2000;	//�h�A��ID(Tiled�Ŋm�F�I)

//########## �}�b�v�`�b�v��ǂݍ��ފ֐� ##########
BOOL MY_LOAD_MAPCHIP1(VOID)
{
	//�}�b�v�̉摜�𕪊�����
	int mapRes = LoadDivGraph(
		MAP1_PATH,										//�p�X
		MAP1_DIV_NUM, MAP1_DIV_TATE, MAP1_DIV_YOKO,		//�������鐔
		MAP1_DIV_WIDTH, MAP1_DIV_HEIGHT,				//�摜�𕪊�����̕��ƍ���
		&mapChip1.handle[0]);							//���������摜������n���h��

	if (mapRes == -1)	//�G���[���b�Z�[�W�\��
	{
		MessageBox(GetMainWindowHandle(), MAP1_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK); return FALSE;
	}

	//���ƍ������擾
	GetGraphSize(mapChip1.handle[0], &mapChip1.width, &mapChip1.height);

	return TRUE;
}

//########## �}�b�v�`�b�v��ǂݍ��ފ֐� ##########
BOOL MY_LOAD_MAPCHIP2(VOID)
{
	//�}�b�v�̉摜�𕪊�����
	int mapRes = LoadDivGraph(
		MAP2_PATH,										//�p�X
		MAP2_DIV_NUM, MAP2_DIV_TATE, MAP2_DIV_YOKO,		//�������鐔
		MAP2_DIV_WIDTH, MAP2_DIV_HEIGHT,				//�摜�𕪊�����̕��ƍ���
		&mapChip2.handle[0]);							//���������摜������n���h��

	if (mapRes == -1)	//�G���[���b�Z�[�W�\��
	{
		MessageBox(GetMainWindowHandle(), MAP2_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK); return FALSE;
	}

	//���ƍ������擾
	GetGraphSize(mapChip2.handle[0], &mapChip2.width, &mapChip2.height);

	return TRUE;
}

//########## �Q�[���}�b�v��CSV��ǂݍ��ފ֐� ##########
//�����P�FCSV�̃p�X
//�����Q�F�}�b�v�z��̐擪�A�h���X
//�����Q�F�}�b�v�z��̐擪�A�h���X(�������p)
BOOL MY_LOAD_CSV_MAP1(const char* path, MAP1* m, MAP1* mInit)
{
	FILE* fp;

	if ((fp = fopen(path, "r")) == NULL)	//�t�@�C����ǂݍ��݃��[�h(r)�ŊJ��
	{
		return FALSE;	//�ُ�I��
	}

	//�������琳��ɓǂݍ��߂��Ƃ��̏���****************************************

	int result = 0;			//�t�@�C���̍Ōォ�`�F�b�N
	for (int tate = 0; tate < MAP1_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < MAP1_YOKO_MAX; yoko++)
		{
			//�|�C���^��z��̏ꏊ�ɕϊ�����
			//�擪�A�h���X����A�i���̐��̕��A�c�̈ړ��ʂ𑫂��j�A���̈ړ��ʂ𑫂�
			MAP1* p = m + tate * MAP1_YOKO_MAX + yoko;

			//�t�@�C�����琔�l����ǂݍ���(%d,)�A�z��Ɋi�[����
			result = fscanf(fp, "%d,", &p->value);

			if (result == EOF) { break; }	//�ŏI�s�܂œǂݍ��߂�
		}
		if (result == EOF) { break; }		//�ŏI�s�܂œǂݍ��߂�
	}

	fclose(fp);	//�t�@�C�������

	//��������}�b�v�̎�ނ̔��ʏ���****************************************

	for (int tate = 0; tate < MAP1_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < MAP1_YOKO_MAX; yoko++)
		{
			//�|�C���^��z��̏ꏊ�ɕϊ�����
			//�擪�A�h���X����A�i���̐��̕��A�c�̈ړ��ʂ𑫂��j�A���̈ړ��ʂ𑫂�
			MAP1* p = m + tate * MAP1_YOKO_MAX + yoko;
			MAP1* pInit = mInit + tate * MAP1_YOKO_MAX + yoko;

			p->kind = MAP1_KIND_TURO;	//��U�A�S�Ă̎�ނ�ʘH�ɂ���
			//�}�b�v�̎�ނ𔻕ʂ���
			for (int cnt = 0; cnt < MAP1_KABE_KIND; cnt++)
			{
				if (p->value == Map1KabeID[cnt])
				{
					p->kind = MAP1_KIND_KABE;	//��ނ�ǂɂ���
					break;
				}
			}

			//�}�b�v�̈ʒu�̏���
			p->x = yoko * MAP1_DIV_WIDTH;
			p->y = tate * MAP1_DIV_HEIGHT;
			p->width = MAP1_DIV_WIDTH;
			p->height = MAP1_DIV_HEIGHT;

			//�}�b�v�̓����蔻��̏���
			p->coll.left = p->x;
			p->coll.top = p->y;
			p->coll.right = p->coll.left + p->width;
			p->coll.bottom = p->coll.top + p->height;

			//�����}�b�v�ɂ��ۑ�����
			pInit = p;
		}
	}

	return TRUE;
}

//########## �Q�[���}�b�v��CSV��ǂݍ��ފ֐� ##########
//�����P�FCSV�̃p�X
//�����Q�F�}�b�v�z��̐擪�A�h���X
//�����Q�F�}�b�v�z��̐擪�A�h���X(�������p)
BOOL MY_LOAD_CSV_MAP2(const char* path, MAP2* m, MAP2* mInit)
{
	FILE* fp;

	if ((fp = fopen(path, "r")) == NULL)	//�t�@�C����ǂݍ��݃��[�h(r)�ŊJ��
	{
		return FALSE;	//�ُ�I��
	}

	//�������琳��ɓǂݍ��߂��Ƃ��̏���****************************************

	int result = 0;			//�t�@�C���̍Ōォ�`�F�b�N
	for (int tate = 0; tate < MAP2_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < MAP2_YOKO_MAX; yoko++)
		{
			//�|�C���^��z��̏ꏊ�ɕϊ�����
			//�擪�A�h���X����A�i���̐��̕��A�c�̈ړ��ʂ𑫂��j�A���̈ړ��ʂ𑫂�
			MAP2* p = m + tate * MAP2_YOKO_MAX + yoko;

			//�t�@�C�����琔�l����ǂݍ���(%d,)�A�z��Ɋi�[����
			result = fscanf(fp, "%d,", &p->value);

			if (result == EOF) { break; }	//�ŏI�s�܂œǂݍ��߂�
		}
		if (result == EOF) { break; }		//�ŏI�s�܂œǂݍ��߂�
	}

	fclose(fp);	//�t�@�C�������

	//��������}�b�v�̎�ނ̔��ʏ���****************************************

	for (int tate = 0; tate < MAP2_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < MAP2_YOKO_MAX; yoko++)
		{
			//�|�C���^��z��̏ꏊ�ɕϊ�����
			//�擪�A�h���X����A�i���̐��̕��A�c�̈ړ��ʂ𑫂��j�A���̈ړ��ʂ𑫂�
			MAP2* p = m + tate * MAP2_YOKO_MAX + yoko;
			MAP2* pInit = mInit + tate * MAP2_YOKO_MAX + yoko;

			p->kind = MAP2_KIND_TURO;	//��U�A�S�Ă̎�ނ�ʘH�ɂ���
			//�}�b�v�̎�ނ𔻕ʂ���
			for (int cnt = 0; cnt < MAP2_KABE_KIND; cnt++)
			{
				if (p->value == Map2KabeID[cnt])
				{
					p->kind = MAP2_KIND_KABE;	//��ނ�ǂɂ���
					break;
				}
			}

			if (p->value == Map2KeyID) { p->kind = MAP2_KIND_KEY; }		//��ނ��J�M�ɂ���
			if (p->value == Map2CoinID) { p->kind = MAP2_KIND_COIN; }	//��ނ��R�C���ɂ���
			if (p->value == Map2DoorID) { p->kind = MAP2_KIND_DOOR; }	//��ނ��h�A�ɂ���	

			//�}�b�v�̈ʒu�̏���
			p->x = yoko * MAP1_DIV_WIDTH;
			p->y = tate * MAP1_DIV_HEIGHT;
			p->width = MAP1_DIV_WIDTH;
			p->height = MAP1_DIV_HEIGHT;

			//�}�b�v�̓����蔻��̏���
			p->coll.left = p->x + 1;
			p->coll.top = p->y + 1;
			p->coll.right = p->coll.left + p->width - 1;
			p->coll.bottom = p->coll.top + p->height - 1;

			//�����}�b�v�ɂ��ۑ�����
			pInit = p;
		}
	}

	return TRUE;
}

//�}�b�v�ƃv���C���[�̓����蔻�������֐�
BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT player)
{
	//�}�b�v�̓����蔻���ݒ肷��
	for (int tate = 0; tate < MAP1_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < MAP1_YOKO_MAX; yoko++)
		{
			//�v���C���[�ƃ}�b�v���������Ă���Ƃ�
			if (MY_CHECK_RECT_COLL(player, map1_naka[tate][yoko].coll) == TRUE)
			{
				//�ǂ̂Ƃ��́A�v���C���[�ƃ}�b�v���������Ă���
				if (map1_naka[tate][yoko].kind == MAP1_KIND_KABE) { return TRUE; }
			}
		}
	}

	return FALSE;
}

//�}�b�v�ƃv���C���[�̓����蔻��(�n��)������֐�
VOID MY_CHECK_MAP2_DOWN(GRIF* g)
{
	//�O���t�B��������ʒu��z��I�Ɍv�Z����
	int ArrX_L = (g->x + grif.choseiX) / MAP2_DIV_WIDTH;				//X�ʒu�i���j
	int ArrX_R = (g->x + g->width + g->choseiWidth) / MAP2_DIV_WIDTH;	//X�ʒu�i�E�j
	int ArrY = (g->y + g->height + g->choseiHeight) / MAP2_DIV_HEIGHT;//Y�ʒu(���̖��܂��Ă���ʒu)

	//��ʊO�̒l���擾���Ȃ�
	if (ArrX_L < 0) { ArrX_L = 0; }
	if (ArrX_R >= MAP2_YOKO_MAX) { ArrX_R = MAP2_YOKO_MAX - 1; }

	//�v���C���[�ƃ}�b�v���������Ă���Ƃ�
	//�ǂ̂Ƃ��́A�v���C���[�ƃ}�b�v���������Ă���
	if (map2_naka[ArrY][ArrX_L].kind == MAP2_KIND_KABE
		|| map2_naka[ArrY][ArrX_R].kind == MAP2_KIND_KABE)
	{
		//�ʘH�̂Ƃ���܂ŉ����グ��
		while (map2_naka[ArrY][ArrX_L].kind != MAP2_KIND_TURO
			|| map2_naka[ArrY][ArrX_R].kind != MAP2_KIND_TURO)
		{
			g->y--;	//���������
			ArrY = (g->y + g->height) / MAP2_DIV_HEIGHT;	//Y�ʒu�Čv�Z�i���̈ʒu�j
		}
	}


	return;
}

//�v���C���[���n�ʂƐڂ��Ă��邩�����蔻�������֐�
BOOL MY_CHECK_GRIF_GROUND(GRIF g)
{
	//�O���t�B��������ʒu��z��I�Ɍv�Z����
	int ArrX_L = (g.x + grif.choseiX) / MAP2_DIV_WIDTH;				//X�ʒu�i���j
	int ArrX_R = (g.x + g.width + g.choseiWidth) / MAP2_DIV_WIDTH;	//X�ʒu�i�E�j
	int ArrY = (g.y + g.height + g.choseiHeight) / MAP2_DIV_HEIGHT;//Y�ʒu(���̖��܂��Ă���ʒu)

	//��ʊO�̒l���擾���Ȃ�
	if (ArrX_L < 0) { ArrX_L = 0; }
	if (ArrX_R >= MAP2_YOKO_MAX) { ArrX_R = MAP2_YOKO_MAX - 1; }

	//�v���C���[�ƃ}�b�v���������Ă���Ƃ�
	//�ǂ̂Ƃ��́A�v���C���[�ƃ}�b�v���������Ă���
	if (map2_naka[ArrY][ArrX_L].kind == MAP2_KIND_KABE
		|| map2_naka[ArrY][ArrX_R].kind == MAP2_KIND_KABE)
	{
		return TRUE;
	}

	return FALSE;
}

//�}�b�v�ƃv���C���[�̓����蔻��(�W�����v)������֐�
VOID MY_CHECK_MAP2_JUMP(GRIF* g)
{
	//�O���t�B��������ʒu��z��I�Ɍv�Z����
	int ArrX_L = (g->x + grif.choseiX) / MAP2_DIV_WIDTH;				//X�ʒu�i���j
	int ArrX_R = (g->x + g->width + g->choseiWidth) / MAP2_DIV_WIDTH;	//X�ʒu�i�E�j
	int ArrY = (g->y) / MAP2_DIV_HEIGHT;								//Y�ʒu(��)

	//��ʊO�̒l���擾���Ȃ�
	if (ArrX_L < 0) { ArrX_L = 0; }
	if (ArrX_R >= MAP2_YOKO_MAX) { ArrX_R = MAP2_YOKO_MAX - 1; }

	//�v���C���[�ƃ}�b�v���������Ă���Ƃ�
	//�ǂ̂Ƃ��́A�v���C���[�ƃ}�b�v���������Ă���
	if (map2_naka[ArrY][ArrX_L].kind == MAP2_KIND_KABE
		|| map2_naka[ArrY][ArrX_R].kind == MAP2_KIND_KABE)
	{
		//�ʘH�̂Ƃ���܂ŉ����グ��
		while (map2_naka[ArrY][ArrX_L].kind != MAP2_KIND_TURO
			|| map2_naka[ArrY][ArrX_R].kind != MAP2_KIND_TURO)
		{
			g->y++;	//����������
			ArrY = (g->y) / MAP2_DIV_HEIGHT;	//Y�ʒu�Čv�Z�i���̈ʒu�j
		}
	}

	return;
}

//�}�b�v�ƃv���C���[�̓����蔻��(��)������֐�
VOID MY_CHECK_MAP2_LEFT(GRIF* g)
{
	//�O���t�B��������ʒu��z��I�Ɍv�Z����
	int ArrX_L = (g->x + g->choseiX) / MAP2_DIV_WIDTH;	//X�ʒu�i���j
	int ArrY = (g->y + (g->height / 2)) / MAP2_DIV_HEIGHT;	//Y�ʒu(���S)

	//��ʊO�̒l���擾���Ȃ�
	if (ArrX_L < 0) { ArrX_L = 0; }

	//�v���C���[�ƃ}�b�v���������Ă���Ƃ�
	//�ǂ̂Ƃ��́A�v���C���[�ƃ}�b�v���������Ă���
	if (map2_naka[ArrY][ArrX_L].kind == MAP2_KIND_KABE)
	{
		//�ʘH�̂Ƃ���܂ŉ����߂�
		while (map2_naka[ArrY][ArrX_L].kind != MAP2_KIND_TURO)
		{
			g->x++;	//�������E��
			ArrX_L = (g->x + g->choseiX) / MAP2_DIV_WIDTH;	//X�ʒu�Čv�Z
		}
	}

	return;
}


//�}�b�v�ƃv���C���[�̓����蔻��(�E)������֐�
VOID MY_CHECK_MAP2_RIGHT(GRIF* g)
{
	//�O���t�B��������ʒu��z��I�Ɍv�Z����
	int ArrX_R = (g->x + g->width + g->choseiWidth) / MAP2_DIV_WIDTH;	//X�ʒu�i�E�j
	int ArrY = (g->y + (g->height / 2)) / MAP2_DIV_HEIGHT;				//Y�ʒu(���S)

	//��ʊO�̒l���擾���Ȃ�
	if (ArrX_R >= MAP2_YOKO_MAX) { ArrX_R = MAP2_YOKO_MAX - 1; }

	//�v���C���[�ƃ}�b�v���������Ă���Ƃ�
	//�ǂ̂Ƃ��́A�v���C���[�ƃ}�b�v���������Ă���
	if (map2_naka[ArrY][ArrX_R].kind == MAP2_KIND_KABE)
	{
		//�ʘH�̂Ƃ���܂ŉ����߂�
		while (map2_naka[ArrY][ArrX_R].kind != MAP2_KIND_TURO)
		{
			g->x--;	//����������
			ArrX_R = (g->x + g->width + g->choseiWidth) / MAP2_DIV_WIDTH;	//X�ʒu�Čv�Z
		}
	}

	return;
}

//�}�b�v�ƃv���C���[�̓����蔻��(��)������֐�
BOOL MY_CHECK_MAP2_KEY(GRIF g)
{
	//�O���t�B��������ʒu��z��I�Ɍv�Z����
	int ArrX = (g.x + (g.width / 2)) / MAP2_DIV_WIDTH;		//X�ʒu(���S)
	int ArrY = (g.y + (g.height / 2)) / MAP2_DIV_HEIGHT;	//Y�ʒu(���S)

	//��ʊO�̒l���擾���Ȃ�
	if (ArrX < 0) { ArrX = 0; }
	if (ArrX >= MAP2_YOKO_MAX) { ArrX = MAP2_YOKO_MAX - 1; }

	//�v���C���[�ƃ}�b�v���������Ă���Ƃ�
	//�J�M�̂Ƃ��́A�v���C���[�ƃ}�b�v���������Ă���
	if (map2_naka[ArrY][ArrX].kind == MAP2_KIND_KEY)
	{
		return TRUE;
	}

	return FALSE;
}

//�}�b�v�ƃv���C���[�̓����蔻��(�h�A)������֐�
BOOL MY_CHECK_MAP2_DOOR(GRIF g)
{
	//�O���t�B��������ʒu��z��I�Ɍv�Z����
	int ArrX = (g.x + (g.width / 2)) / MAP2_DIV_WIDTH;		//X�ʒu(���S)
	int ArrY = (g.y + (g.height / 2)) / MAP2_DIV_HEIGHT;	//Y�ʒu(���S)

	//��ʊO�̒l���擾���Ȃ�
	if (ArrX < 0) { ArrX = 0; }
	if (ArrX >= MAP2_YOKO_MAX) { ArrX = MAP2_YOKO_MAX - 1; }

	//�v���C���[�ƃ}�b�v���������Ă���Ƃ�
	//�J�M�̂Ƃ��́A�v���C���[�ƃ}�b�v���������Ă���
	if (map2_naka[ArrY][ArrX].kind == MAP2_KIND_DOOR)
	{
		return TRUE;
	}

	return FALSE;
}

//�}�b�v�ƃv���C���[�̓����蔻��(�R�C��)������֐�
VOID MY_GET_MAP2_COIN(GRIF g)
{
	//�O���t�B��������ʒu��z��I�Ɍv�Z����
	int ArrX = (g.x + (g.width / 2)) / MAP2_DIV_WIDTH;		//X�ʒu(���S)
	int ArrY = (g.y + (g.height / 2)) / MAP2_DIV_HEIGHT;	//Y�ʒu(���S)

	//��ʊO�̒l���擾���Ȃ�
	if (ArrX < 0) { ArrX = 0; }
	if (ArrX >= MAP2_YOKO_MAX) { ArrX = MAP2_YOKO_MAX - 1; }

	//�v���C���[�ƃ}�b�v���������Ă���Ƃ�
	//�J�M�̂Ƃ��́A�v���C���[�ƃ}�b�v���������Ă���
	if (map2_naka[ArrY][ArrX].kind == MAP2_KIND_COIN)
	{
		//�R�C���̉摜���u�Ȃɂ��Ȃ��v�ɂ���
		map2_naka[ArrY][ArrX].kind = MAP2_KIND_NONE;
		map2_naka[ArrY][ArrX].value = Map2NoneID;
	}

	return;
}