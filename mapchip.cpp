/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//�}�b�v�`�b�v�Ŏg�p���郂�m���܂Ƃ߂Ă��܂�

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "game.h"
#include "mapchip.h"

//########## �O���[�o���ϐ� ##########

//�}�b�v�`�b�v�̉摜���Ǘ�
MAP1CHIP mapChip1;

MAP1 map1_sita[MAP1_TATE_MAX][MAP1_YOKO_MAX];		//�}�b�v�f�[�^�P�i���j
MAP1 mapInit1_sita[MAP1_TATE_MAX][MAP1_YOKO_MAX];	//�ŏ��̃}�b�v�f�[�^�P�i���j

MAP1 map1_naka[MAP1_TATE_MAX][MAP1_YOKO_MAX];		//�}�b�v�f�[�^�P�i���j
MAP1 mapInit1_naka[MAP1_TATE_MAX][MAP1_YOKO_MAX];	//�ŏ��̃}�b�v�f�[�^�P�i���j

MAP1 map1_ue[MAP1_TATE_MAX][MAP1_YOKO_MAX];		//�}�b�v�f�[�^�P�i��j
MAP1 mapInit1_ue[MAP1_TATE_MAX][MAP1_YOKO_MAX];	//�ŏ��̃}�b�v�f�[�^�P�i��j

int Map1KabeID[MAP1_KABE_KIND] = { 34,35,66,67,257,258,350,409 };	//�ǂ�ID

//�}�b�v�`�b�v�̉摜���Ǘ�
MAP1CHIP mapChip2;

MAP1 map2_sita[MAP1_TATE_MAX][MAP1_YOKO_MAX];		//�}�b�v�f�[�^�Q�i���j
MAP1 mapInit1_sita[MAP1_TATE_MAX][MAP1_YOKO_MAX];	//�ŏ��̃}�b�v�f�[�^�Q�i���j

MAP1 map2_naka[MAP1_TATE_MAX][MAP1_YOKO_MAX];		//�}�b�v�f�[�^�Q�i���j
MAP1 mapInit1_naka[MAP1_TATE_MAX][MAP1_YOKO_MAX];	//�ŏ��̃}�b�v�f�[�^�Q�i���j

MAP1 map2_ue[MAP1_TATE_MAX][MAP1_YOKO_MAX];		//�}�b�v�f�[�^�Q�i��j
MAP1 mapInit1_ue[MAP1_TATE_MAX][MAP1_YOKO_MAX];	//�ŏ��̃}�b�v�f�[�^�Q�i��j

int Map2KabeID[MAP1_KABE_KIND] = { 34,35,66,67,257,258,350,409 };	//�ǂ�ID

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