/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//マップチップで使用するモノをまとめています

//########## ヘッダーファイル読み込み ##########
#include "game.h"
#include "mapchip.h"

//########## グローバル変数 ##########

//マップチップの画像を管理
MAPCHIP1 mapChip1;

MAP1 map1_sita[MAP1_TATE_MAX][MAP1_YOKO_MAX];		//マップデータ１（下）
MAP1 mapInit1_sita[MAP1_TATE_MAX][MAP1_YOKO_MAX];	//最初のマップデータ１（下）

MAP1 map1_naka[MAP1_TATE_MAX][MAP1_YOKO_MAX];		//マップデータ１（中）
MAP1 mapInit1_naka[MAP1_TATE_MAX][MAP1_YOKO_MAX];	//最初のマップデータ１（中）

MAP1 map1_ue[MAP1_TATE_MAX][MAP1_YOKO_MAX];		//マップデータ１（上）
MAP1 mapInit1_ue[MAP1_TATE_MAX][MAP1_YOKO_MAX];	//最初のマップデータ１（上）

int Map1KabeID[MAP1_KABE_KIND] = { 34,35,66,67,257,258,350,409 };	//壁のID

//マップチップの画像を管理
MAPCHIP2 mapChip2;

MAP2 map2_sita[MAP1_TATE_MAX][MAP1_YOKO_MAX];		//マップデータ２（下）
MAP2 mapInit2_sita[MAP1_TATE_MAX][MAP1_YOKO_MAX];	//最初のマップデータ２（下）

MAP2 map2_naka[MAP1_TATE_MAX][MAP1_YOKO_MAX];		//マップデータ２（中）
MAP2 mapInit2_naka[MAP1_TATE_MAX][MAP1_YOKO_MAX];	//最初のマップデータ２（中）

MAP2 map2_ue[MAP1_TATE_MAX][MAP1_YOKO_MAX];			//マップデータ２（上）
MAP2 mapInit2_ue[MAP1_TATE_MAX][MAP1_YOKO_MAX];		//最初のマップデータ２（上）

int Map2KabeID[MAP2_KABE_KIND] = { 986,987,988,989,1044,1045,1046 };	//壁のID

//########## マップチップを読み込む関数 ##########
BOOL MY_LOAD_MAPCHIP1(VOID)
{
	//マップの画像を分割する
	int mapRes = LoadDivGraph(
		MAP1_PATH,										//パス
		MAP1_DIV_NUM, MAP1_DIV_TATE, MAP1_DIV_YOKO,		//分割する数
		MAP1_DIV_WIDTH, MAP1_DIV_HEIGHT,				//画像を分割するの幅と高さ
		&mapChip1.handle[0]);							//分割した画像が入るハンドル

	if (mapRes == -1)	//エラーメッセージ表示
	{
		MessageBox(GetMainWindowHandle(), MAP1_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK); return FALSE;
	}

	//幅と高さを取得
	GetGraphSize(mapChip1.handle[0], &mapChip1.width, &mapChip1.height);

	return TRUE;
}

//########## マップチップを読み込む関数 ##########
BOOL MY_LOAD_MAPCHIP2(VOID)
{
	//マップの画像を分割する
	int mapRes = LoadDivGraph(
		MAP2_PATH,										//パス
		MAP2_DIV_NUM, MAP2_DIV_TATE, MAP2_DIV_YOKO,		//分割する数
		MAP2_DIV_WIDTH, MAP2_DIV_HEIGHT,				//画像を分割するの幅と高さ
		&mapChip2.handle[0]);							//分割した画像が入るハンドル

	if (mapRes == -1)	//エラーメッセージ表示
	{
		MessageBox(GetMainWindowHandle(), MAP2_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK); return FALSE;
	}

	//幅と高さを取得
	GetGraphSize(mapChip2.handle[0], &mapChip2.width, &mapChip2.height);

	return TRUE;
}

//########## ゲームマップのCSVを読み込む関数 ##########
//引数１：CSVのパス
//引数２：マップ配列の先頭アドレス
//引数２：マップ配列の先頭アドレス(初期化用)
BOOL MY_LOAD_CSV_MAP1(const char* path, MAP1* m, MAP1* mInit)
{
	FILE* fp;

	if ((fp = fopen(path, "r")) == NULL)	//ファイルを読み込みモード(r)で開く
	{
		return FALSE;	//異常終了
	}

	//ここから正常に読み込めたときの処理****************************************

	int result = 0;			//ファイルの最後かチェック
	for (int tate = 0; tate < MAP1_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < MAP1_YOKO_MAX; yoko++)
		{
			//ポインタを配列の場所に変換する
			//先頭アドレスから、（横の数の分、縦の移動量を足し）、横の移動量を足す
			MAP1* p = m + tate * MAP1_YOKO_MAX + yoko;

			//ファイルから数値を一つ読み込み(%d,)、配列に格納する
			result = fscanf(fp, "%d,", &p->value);

			if (result == EOF) { break; }	//最終行まで読み込めた
		}
		if (result == EOF) { break; }		//最終行まで読み込めた
	}

	fclose(fp);	//ファイルを閉じる

	//ここからマップの種類の判別処理****************************************

	for (int tate = 0; tate < MAP1_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < MAP1_YOKO_MAX; yoko++)
		{
			//ポインタを配列の場所に変換する
			//先頭アドレスから、（横の数の分、縦の移動量を足し）、横の移動量を足す
			MAP1* p = m + tate * MAP1_YOKO_MAX + yoko;
			MAP1* pInit = mInit + tate * MAP1_YOKO_MAX + yoko;

			p->kind = MAP1_KIND_TURO;	//一旦、全ての種類を通路にする
			//マップの種類を判別する
			for (int cnt = 0; cnt < MAP1_KABE_KIND; cnt++)
			{
				if (p->value == Map1KabeID[cnt])
				{
					p->kind = MAP1_KIND_KABE;	//種類を壁にする
					break;
				}
			}

			//マップの位置の処理
			p->x = yoko * MAP1_DIV_WIDTH;
			p->y = tate * MAP1_DIV_HEIGHT;
			p->width = MAP1_DIV_WIDTH;
			p->height = MAP1_DIV_HEIGHT;

			//マップの当たり判定の処理
			p->coll.left = p->x;
			p->coll.top = p->y;
			p->coll.right = p->coll.left + p->width;
			p->coll.bottom = p->coll.top + p->height;

			//初期マップにも保存する
			pInit = p;
		}
	}

	return TRUE;
}

//########## ゲームマップのCSVを読み込む関数 ##########
//引数１：CSVのパス
//引数２：マップ配列の先頭アドレス
//引数２：マップ配列の先頭アドレス(初期化用)
BOOL MY_LOAD_CSV_MAP2(const char* path, MAP2* m, MAP2* mInit)
{
	FILE* fp;

	if ((fp = fopen(path, "r")) == NULL)	//ファイルを読み込みモード(r)で開く
	{
		return FALSE;	//異常終了
	}

	//ここから正常に読み込めたときの処理****************************************

	int result = 0;			//ファイルの最後かチェック
	for (int tate = 0; tate < MAP2_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < MAP2_YOKO_MAX; yoko++)
		{
			//ポインタを配列の場所に変換する
			//先頭アドレスから、（横の数の分、縦の移動量を足し）、横の移動量を足す
			MAP2* p = m + tate * MAP2_YOKO_MAX + yoko;

			//ファイルから数値を一つ読み込み(%d,)、配列に格納する
			result = fscanf(fp, "%d,", &p->value);

			if (result == EOF) { break; }	//最終行まで読み込めた
		}
		if (result == EOF) { break; }		//最終行まで読み込めた
	}

	fclose(fp);	//ファイルを閉じる

	//ここからマップの種類の判別処理****************************************

	for (int tate = 0; tate < MAP2_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < MAP2_YOKO_MAX; yoko++)
		{
			//ポインタを配列の場所に変換する
			//先頭アドレスから、（横の数の分、縦の移動量を足し）、横の移動量を足す
			MAP2* p = m + tate * MAP2_YOKO_MAX + yoko;
			MAP2* pInit = mInit + tate * MAP2_YOKO_MAX + yoko;

			p->kind = MAP2_KIND_TURO;	//一旦、全ての種類を通路にする
			//マップの種類を判別する
			for (int cnt = 0; cnt < MAP2_KABE_KIND; cnt++)
			{
				if (p->value == Map2KabeID[cnt])
				{
					p->kind = MAP2_KIND_KABE;	//種類を壁にする
					break;
				}
			}

			//マップの位置の処理
			p->x = yoko * MAP1_DIV_WIDTH;
			p->y = tate * MAP1_DIV_HEIGHT;
			p->width = MAP1_DIV_WIDTH;
			p->height = MAP1_DIV_HEIGHT;

			//マップの当たり判定の処理
			p->coll.left = p->x + 1;
			p->coll.top = p->y + 1;
			p->coll.right = p->coll.left + p->width - 1;
			p->coll.bottom = p->coll.top + p->height - 1;

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
	for (int tate = 0; tate < MAP1_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < MAP1_YOKO_MAX; yoko++)
		{
			//プレイヤーとマップが当たっているとき
			if (MY_CHECK_RECT_COLL(player, map1_naka[tate][yoko].coll) == TRUE)
			{
				//壁のときは、プレイヤーとマップが当たっている
				if (map1_naka[tate][yoko].kind == MAP1_KIND_KABE) { return TRUE; }
			}
		}
	}

	return FALSE;
}

//マップとプレイヤーの当たり判定(地面)をする関数
VOID MY_CHECK_MAP2_DOWN(GRIF* g)
{
	//グリフィンがいる位置を配列的に計算する
	int ArrX_L = (g->x + grif.choseiX) / MAP2_DIV_WIDTH;				//X位置（左）
	int ArrX_R = (g->x + g->width + grif.choseiWidth) / MAP2_DIV_WIDTH;	//X位置（右）
	int ArrY = (g->y + g->height + grif.choseiHeight) / MAP2_DIV_HEIGHT;//Y位置(下の埋まっている位置)

	if (ArrX_L < 0) { ArrX_L = 0; }
	if (ArrX_R >= MAP2_YOKO_MAX) { ArrX_R = MAP2_YOKO_MAX - 1; }

	//プレイヤーとマップが当たっているとき
	//壁のときは、プレイヤーとマップが当たっている
	if (map2_naka[ArrY][ArrX_L].kind == MAP2_KIND_KABE
		|| map2_naka[ArrY][ArrX_R].kind == MAP2_KIND_KABE)
	{
		//通路のところまで押し上げる
		while (map2_naka[ArrY][ArrX_L].kind != MAP2_KIND_TURO
			|| map2_naka[ArrY][ArrX_R].kind != MAP2_KIND_TURO)
		{
			g->y--;	//少しずつ上へ
			ArrY = (g->y + g->height) / MAP2_DIV_HEIGHT;	//Y位置再計算（下の位置）
		}
	}

	/*
	この方法の既知のバグ

　　　　■
	□☆

	このようなステージのとき、☆の位置から右へ移動すると、■の上に乗ってしまう
	理由として
	☆から右へ移動
	↓
	キャラ右は床がないが、キャラ左は床がある
	↓
	キャラ左が床のため、押し上げる
	↓
	キャラ右が床にぶつかるため、押し上げる
	↓
	キャラが上に乗ってしまう
	という動作をする。なんとか解消したい。。。
	*/

	return;
}
