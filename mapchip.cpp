/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//マップチップで使用するモノをまとめています

//########## ヘッダーファイル読み込み ##########
#include "game.h"
#include "mapchip.h"

//########## グローバル変数 ##########

//マップチップの画像を管理
MAPCHIP mapChip;

MAP map1_sita[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];		//マップデータ１（下）
MAP mapInit1_sita[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];	//最初のマップデータ１（下）

MAP map1_naka[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];		//マップデータ１（中）
MAP mapInit1_naka[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];	//最初のマップデータ１（中）

MAP map1_ue[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];			//マップデータ１（上）
MAP mapInit1_ue[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];		//最初のマップデータ１（上）

int KabeID[GAME_MAP_KABE_KIND] = { 34,35,66,67,257,258,350,409 };	//壁のID

//########## ゲームマップのCSVを読み込む関数 ##########
//引数１：CSVのパス
//引数２：マップ配列の先頭アドレス
//引数２：マップ配列の先頭アドレス(初期化用)
BOOL MY_LOAD_CSV_MAP1(const char* path, MAP* m, MAP* mInit)
{
	FILE* fp;

	if ((fp = fopen(path, "r")) == NULL)	//ファイルを読み込みモード(r)で開く
	{
		return FALSE;	//異常終了
	}

	//ここから正常に読み込めたときの処理****************************************

	int result = 0;			//ファイルの最後かチェック
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//ポインタを配列の場所に変換する
			//先頭アドレスから、（横の数の分、縦の移動量を足し）、横の移動量を足す
			MAP* p = m + tate * GAME_MAP_YOKO_MAX + yoko;

			//ファイルから数値を一つ読み込み(%d,)、配列に格納する
			result = fscanf(fp, "%d,", &p->value);

			if (result == EOF) { break; }	//最終行まで読み込めた
		}
		if (result == EOF) { break; }		//最終行まで読み込めた
	}

	fclose(fp);	//ファイルを閉じる

	//ここからマップの種類の判別処理****************************************

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//ポインタを配列の場所に変換する
			//先頭アドレスから、（横の数の分、縦の移動量を足し）、横の移動量を足す
			MAP* p = m + tate * GAME_MAP_YOKO_MAX + yoko;
			MAP* pInit = mInit + tate * GAME_MAP_YOKO_MAX + yoko;

			p->kind = MAP_KIND_TURO;	//一旦、全ての種類を通路にする
			//マップの種類を判別する
			for (int cnt = 0; cnt < GAME_MAP_KABE_KIND; cnt++)
			{
				if (p->value == KabeID[cnt])
				{
					p->kind = MAP_KIND_KABE;	//種類を壁にする
					break;
				}
			}

			//マップの位置の処理
			p->x = yoko * MAP_DIV_WIDTH;
			p->y = tate * MAP_DIV_HEIGHT;
			p->width = MAP_DIV_WIDTH;
			p->height = MAP_DIV_HEIGHT;

			//マップの当たり判定の処理
			p->Coll.left = p->x;
			p->Coll.top = p->y;
			p->Coll.right = p->Coll.left + p->width;
			p->Coll.bottom = p->Coll.top + p->height;

			//初期マップにも保存する
			pInit = p;
		}
	}

	return TRUE;
}


//マップとプレイヤーの当たり判定をする関数
BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT player)
{
	//マップの当たり判定を設定する
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//プレイヤーとマップが当たっているとき
			if (MY_CHECK_RECT_COLL(player, map1_sita[tate][yoko].Coll) == TRUE)
			{
				//壁のときは、プレイヤーとマップが当たっている
				if (map1_sita[tate][yoko].kind == MAP_KIND_KABE) { return TRUE; }
			}
		}
	}

	return FALSE;
}