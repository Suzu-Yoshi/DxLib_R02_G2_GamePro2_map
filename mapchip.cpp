/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//�}�b�v�`�b�v�Ŏg�p���郂�m���܂Ƃ߂Ă��܂�

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "game.h"
#include "mapchip.h"

//########## �O���[�o���ϐ� ##########

//�}�b�v�`�b�v�̉摜���Ǘ�
MAPCHIP mapChip;

MAP map1_sita[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];		//�}�b�v�f�[�^�P�i���j
MAP mapInit1_sita[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];	//�ŏ��̃}�b�v�f�[�^�P�i���j

MAP map1_naka[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];		//�}�b�v�f�[�^�P�i���j
MAP mapInit1_naka[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];	//�ŏ��̃}�b�v�f�[�^�P�i���j

MAP map1_ue[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];			//�}�b�v�f�[�^�P�i��j
MAP mapInit1_ue[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];		//�ŏ��̃}�b�v�f�[�^�P�i��j

int KabeID[GAME_MAP_KABE_KIND] = { 34,35,66,67,257,258,350,409 };	//�ǂ�ID

//########## �Q�[���}�b�v��CSV��ǂݍ��ފ֐� ##########
//�����P�FCSV�̃p�X
//�����Q�F�}�b�v�z��̐擪�A�h���X
//�����Q�F�}�b�v�z��̐擪�A�h���X(�������p)
BOOL MY_LOAD_CSV_MAP1(const char* path, MAP* m, MAP* mInit)
{
	FILE* fp;

	if ((fp = fopen(path, "r")) == NULL)	//�t�@�C����ǂݍ��݃��[�h(r)�ŊJ��
	{
		return FALSE;	//�ُ�I��
	}

	//�������琳��ɓǂݍ��߂��Ƃ��̏���****************************************

	int result = 0;			//�t�@�C���̍Ōォ�`�F�b�N
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�|�C���^��z��̏ꏊ�ɕϊ�����
			//�擪�A�h���X����A�i���̐��̕��A�c�̈ړ��ʂ𑫂��j�A���̈ړ��ʂ𑫂�
			MAP* p = m + tate * GAME_MAP_YOKO_MAX + yoko;

			//�t�@�C�����琔�l����ǂݍ���(%d,)�A�z��Ɋi�[����
			result = fscanf(fp, "%d,", &p->value);

			if (result == EOF) { break; }	//�ŏI�s�܂œǂݍ��߂�
		}
		if (result == EOF) { break; }		//�ŏI�s�܂œǂݍ��߂�
	}

	fclose(fp);	//�t�@�C�������

	//��������}�b�v�̎�ނ̔��ʏ���****************************************

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�|�C���^��z��̏ꏊ�ɕϊ�����
			//�擪�A�h���X����A�i���̐��̕��A�c�̈ړ��ʂ𑫂��j�A���̈ړ��ʂ𑫂�
			MAP* p = m + tate * GAME_MAP_YOKO_MAX + yoko;
			MAP* pInit = mInit + tate * GAME_MAP_YOKO_MAX + yoko;

			p->kind = MAP_KIND_TURO;	//��U�A�S�Ă̎�ނ�ʘH�ɂ���
			//�}�b�v�̎�ނ𔻕ʂ���
			for (int cnt = 0; cnt < GAME_MAP_KABE_KIND; cnt++)
			{
				if (p->value == KabeID[cnt])
				{
					p->kind = MAP_KIND_KABE;	//��ނ�ǂɂ���
					break;
				}
			}

			//�}�b�v�̈ʒu�̏���
			p->x = yoko * MAP_DIV_WIDTH;
			p->y = tate * MAP_DIV_HEIGHT;
			p->width = MAP_DIV_WIDTH;
			p->height = MAP_DIV_HEIGHT;

			//�}�b�v�̓����蔻��̏���
			p->Coll.left = p->x;
			p->Coll.top = p->y;
			p->Coll.right = p->Coll.left + p->width;
			p->Coll.bottom = p->Coll.top + p->height;

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
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�v���C���[�ƃ}�b�v���������Ă���Ƃ�
			if (MY_CHECK_RECT_COLL(player, map1_sita[tate][yoko].Coll) == TRUE)
			{
				//�ǂ̂Ƃ��́A�v���C���[�ƃ}�b�v���������Ă���
				if (map1_sita[tate][yoko].kind == MAP_KIND_KABE) { return TRUE; }
			}
		}
	}

	return FALSE;
}