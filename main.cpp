/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//Ex.CSVファイルのデータを読み込んで、マップと当たり判定を作るサンプル
//サンプルなので、丸パクリせず、参考にしてください。
//サンプルなので、必要最低限のことしか、していません。

//エラー抑制
#define _CRT_SECURE_NO_WARNINGS

//########## ヘッダーファイル読み込み ##########
#include "DxLib.h"

//########## マクロ定義 ##########
#define GAME_WIDTH			800	//画面の横の大きさ
#define GAME_HEIGHT			600	//画面の縦の大きさ
#define GAME_COLOR			32	//画面のカラービット

#define GAME_WINDOW_BAR		0				//タイトルバーはデフォルトにする
#define GAME_WINDOW_NAME	"GAME TITLE"	//ウィンドウのタイトル
#define GAME_FPS			60				//FPSの数値	

//パスの長さ
#define PATH_MAX			255	//255文字まで
#define NAME_MAX			255	//255文字まで

//エラーメッセージ
#define IMAGE_LOAD_ERR_TITLE	TEXT("画像読み込みエラー")

//画像のパス
#define GAME_MAP_PATH			TEXT(".\\IMAGE\\MAP\\mapchip1.png")			//マップの画像
#define GAME_CSV_PATH_MAP1_SITA	TEXT(".\\IMAGE\\MAP\\map_map1_sita.csv")	//マップCSV(下)
#define GAME_CSV_PATH_MAP1_NAKA	TEXT(".\\IMAGE\\MAP\\map_map1_naka.csv")	//マップCSV(中)
#define GAME_CSV_PATH_MAP1_UE	TEXT(".\\IMAGE\\MAP\\map_map1_ue.csv")		//マップCSV(上)

#define GAME_MAP_TATE_MAX	10	//マップの縦の広さ
#define GAME_MAP_YOKO_MAX	20	//マップの横の広さ

#define GAME_MAP_KABE_KIND	8	//マップの壁の種類

#define MAP_DIV_WIDTH		32	//マップチップの１つ分の幅サイズ
#define MAP_DIV_HEIGHT		32	//マップチップの１つ分の高さサイズ

#define MAP_DIV_TATE		32	//マップチップを縦に分割する数
#define MAP_DIV_YOKO		41	//マップチップを横に分割する数
#define MAP_DIV_NUM	MAP_DIV_TATE * MAP_DIV_YOKO	//マップチップを分割する総数

//終了ダイアログ用
#define MOUSE_R_CLICK_TITLE		TEXT("ゲーム中断")
#define MOUSE_R_CLICK_CAPTION	TEXT("ゲームを中断し、タイトル画面に戻りますか？")

enum MAP_KIND {
	MAP_KIND_KABE,	//壁
	MAP_KIND_TURO,	//通路
};

enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
};	//ゲームのシーン

typedef struct STRUCT_IMAGE
{
	char path[PATH_MAX];		//パス
	int handle;					//ハンドル
	int x;						//X位置
	int y;						//Y位置
	int width;					//幅
	int height;					//高さ
}IMAGE;	//画像構造体

typedef struct STRUCT_MAPCHIP
{
	char path[PATH_MAX];				//パス
	int handle[MAP_DIV_NUM];			//分割したの弾の画像ハンドルを取得
	int width;							//幅
	int height;							//高さ
}MAPCHIP;	//MAPCHIP構造体

typedef struct STRUCT_MAP
{
	int value;			//マップの値
	MAP_KIND kind;		//マップの種類
	int x;				//X位置
	int y;				//Y位置
	int width;			//幅
	int height;			//高さ
	RECT Coll;			//マップの当たり判定
}MAP;	//MAP構造体

//########## グローバル変数 ##########
//FPS関連
int StartTimeFps;				//測定開始時刻
int CountFps;					//カウンタ
float CalcFps;					//計算結果
int SampleNumFps = GAME_FPS;	//平均を取るサンプル数

//キーボードの入力を取得
char AllKeyState[256] = { '\0' };			//すべてのキーの状態が入る
char OldAllKeyState[256] = { '\0' };		//すべてのキーの状態(直前)が入る

int GameScene;		//ゲームシーンを管理

//マップチップの画像を管理
MAPCHIP mapChip;

MAP map1_sita[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];		//マップデータ１（下）
MAP mapInit1_sita[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];	//最初のマップデータ１（下）

MAP map1_naka[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];		//マップデータ１（中）
MAP mapInit1_naka[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];	//最初のマップデータ１（中）

MAP map1_ue[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];			//マップデータ１（上）
MAP mapInit1_ue[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];		//最初のマップデータ１（上）

int KabeID[GAME_MAP_KABE_KIND] = { 34,35,66,67,257,258,350,409 };	//壁のID

//########## プロトタイプ宣言 ##########
VOID MY_FPS_UPDATE(VOID);			//FPS値を計測、更新する
VOID MY_FPS_DRAW(VOID);				//FPS値を描画する
VOID MY_FPS_WAIT(VOID);				//FPS値を計測し、待つ

VOID MY_ALL_KEYDOWN_UPDATE(VOID);	//キーの入力状態を更新する
BOOL MY_KEY_DOWN(int);				//キーを押しているか、キーコードで判断する
BOOL MY_KEY_UP(int);				//キーを押し上げたか、キーコードで判断する
BOOL MY_KEYDOWN_KEEP(int, int);		//キーを押し続けているか、キーコードで判断する
BOOL MY_KEY_PUSH(int KEY_INPUT_);	//キーをプッシュしたか、キーコードで判断する

VOID MY_START(VOID);		//スタート画面
VOID MY_START_PROC(VOID);	//スタート画面の処理
VOID MY_START_DRAW(VOID);	//スタート画面の描画

VOID MY_PLAY(VOID);			//プレイ画面
VOID MY_PLAY_PROC(VOID);	//プレイ画面の処理
VOID MY_PLAY_DRAW(VOID);	//プレイ画面の描画

VOID MY_END(VOID);			//エンド画面
VOID MY_END_PROC(VOID);		//エンド画面の処理
VOID MY_END_DRAW(VOID);		//エンド画面の描画

BOOL MY_LOAD_IMAGE(VOID);		//画像をまとめて読み込む関数
VOID MY_DELETE_IMAGE(VOID);		//画像をまとめて削除する関数

BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT);	//マップとプレイヤーの当たり判定をする関数
BOOL MY_CHECK_RECT_COLL(RECT, RECT);	//領域の当たり判定をする関数

BOOL MY_LOAD_CSV_MAP1(const char* path, MAP* m, MAP* mInit);	//ゲームマップのCSVを読み込む関数
void DrawBoxRect(RECT r, unsigned int color, bool b);			//RECTを利用して四角を描画

//########## プログラムで最初に実行される関数 ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);								//ウィンドウモードに設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//指定の数値でウィンドウを表示する
	SetWindowStyleMode(GAME_WINDOW_BAR);				//タイトルバーはデフォルトにする
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));			//ウィンドウのタイトルの文字
	SetAlwaysRunFlag(TRUE);								//非アクティブでも実行する
	SetWindowIconID(333);								//アイコンファイルを読込

	if (DxLib_Init() == -1) { return -1; }	//ＤＸライブラリ初期化処理

	//画像を読み込む
	if (MY_LOAD_IMAGE() == FALSE) { return -1; }

	//CSVを読み込む
	if (MY_LOAD_CSV_MAP1(GAME_CSV_PATH_MAP1_NAKA, &map1_naka[0][0], &mapInit1_naka[0][0]) == FALSE) { return -1; }
	if (MY_LOAD_CSV_MAP1(GAME_CSV_PATH_MAP1_UE, &map1_ue[0][0], &mapInit1_ue[0][0]) == FALSE) { return -1; }
	if (MY_LOAD_CSV_MAP1(GAME_CSV_PATH_MAP1_SITA, &map1_sita[0][0], &mapInit1_sita[0][0]) == FALSE) { return -1; }
	
	//Draw系関数は裏画面に描画
	SetDrawScreen(DX_SCREEN_BACK);

	//ゲームシーンはスタート画面から
	GameScene = GAME_SCENE_START;

	//無限ループ
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	//メッセージ処理の結果がエラーのとき、強制終了
		if (ClearDrawScreen() != 0) { break; }	//画面を消去できなかったとき、強制終了

		MY_ALL_KEYDOWN_UPDATE();				//押しているキー状態を取得

		MY_FPS_UPDATE();	//FPSの処理[更新]

		//シーンごとに処理を行う
		switch (GameScene)
		{
		case GAME_SCENE_START:
			MY_START();	//スタート画面
			break;
		case GAME_SCENE_PLAY:
			MY_PLAY();	//プレイ画面
			break;
		case GAME_SCENE_END:
			MY_END();	//エンド画面
			break;
		}

		MY_FPS_DRAW();		//FPSの処理[描画]

		ScreenFlip();		//モニタのリフレッシュレートの速さで裏画面を再描画

		MY_FPS_WAIT();		//FPSの処理[待つ]
	}

	//画像ハンドルを破棄
	MY_DELETE_IMAGE();

	DxLib_End();	//ＤＸライブラリ使用の終了処理

	return 0;
}

//########## FPS値を計測、更新する関数 ##########
VOID MY_FPS_UPDATE(VOID)
{
	if (CountFps == 0) //1フレーム目なら時刻を記憶
	{
		StartTimeFps = GetNowCount();
	}

	if (CountFps == SampleNumFps) //60フレーム目なら平均を計算
	{
		int now = GetNowCount();
		//現在の時間から、0フレーム目の時間を引き、FPSの数値で割る＝1FPS辺りの平均時間が計算される
		CalcFps = 1000.f / ((now - StartTimeFps) / (float)SampleNumFps);
		CountFps = 0;
		StartTimeFps = now;
	}
	CountFps++;
	return;
}

//########## FPS値を描画する関数 ##########
VOID MY_FPS_DRAW(VOID)
{
	//文字列を描画
	DrawFormatString(0, GAME_HEIGHT - 20, GetColor(255, 255, 255), "FPS:%.1f", CalcFps);
	return;
}

//########## FPS値を計測し、待つ関数 ##########
VOID MY_FPS_WAIT(VOID)
{
	int resultTime = GetNowCount() - StartTimeFps;					//かかった時間
	int waitTime = CountFps * 1000 / GAME_FPS - resultTime;	//待つべき時間

	if (waitTime > 0)		//指定のFPS値よりも早い場合
	{
		WaitTimer(waitTime);	//待つ
	}
	return;
}

//########## キーの入力状態を更新する関数 ##########
VOID MY_ALL_KEYDOWN_UPDATE(VOID)
{
	//参考：https://dxlib.xsrv.jp/function/dxfunc_input.html

	char TempKey[256];	//一時的に、現在のキーの入力状態を格納する

	//直前のキー入力をとっておく
	for (int i = 0; i < 256; i++)
	{
		OldAllKeyState[i] = AllKeyState[i];
	}

	GetHitKeyStateAll(TempKey); // 全てのキーの入力状態を得る

	for (int i = 0; i < 256; i++)
	{
		if (TempKey[i] != 0)	//押されているキーのキーコードを押しているとき
		{
			AllKeyState[i]++;	//押されている
		}
		else
		{
			AllKeyState[i] = 0;	//押されていない
		}
	}
	return;
}

//キーを押しているか、キーコードで判断する
//引　数：int：キーコード：KEY_INPUT_???
BOOL MY_KEY_DOWN(int KEY_INPUT_)
{
	//キーコードのキーを押している時
	if (AllKeyState[KEY_INPUT_] != 0)
	{
		return TRUE;	//キーを押している
	}
	else
	{
		return FALSE;	//キーを押していない
	}
}

//キーを押し上げたか、キーコードで判断する
//引　数：int：キーコード：KEY_INPUT_???
BOOL MY_KEY_UP(int KEY_INPUT_)
{
	if (OldAllKeyState[KEY_INPUT_] >= 1	//直前は押していて
		&& AllKeyState[KEY_INPUT_] == 0)	//今は押していないとき
	{
		return TRUE;	//キーを押し上げている
	}
	else
	{
		return FALSE;	//キーを押し上げていない
	}
}

//キーをプッシュしたか、キーコードで判断する
//引　数：int：キーコード：KEY_INPUT_???
BOOL MY_KEY_PUSH(int KEY_INPUT_)
{
	if (OldAllKeyState[KEY_INPUT_] == 0		//直前は押していなくて
		&& AllKeyState[KEY_INPUT_] >= 1)	//今は押しているとき
	{
		return TRUE;	//キーをプッシュした（押し続けても、１回のみ発生）
	}
	else
	{
		return FALSE;	//キーをプッシュしていないか、押し続けている
	}
}

//キーを押し続けているか、キーコードで判断する
//引　数：int：キーコード：KEY_INPUT_???
//引　数：int：キーを押し続ける時間
BOOL MY_KEYDOWN_KEEP(int KEY_INPUT_, int DownTime)
{
	//押し続ける時間=秒数×FPS値
	//例）60FPSのゲームで、1秒間押し続けるなら、1秒×60FPS
	int UpdateTime = DownTime * GAME_FPS;

	if (AllKeyState[KEY_INPUT_] > UpdateTime)
	{
		return TRUE;	//押し続けている
	}
	else
	{
		return FALSE;	//押し続けていない
	}
}

//スタート画面
VOID MY_START(VOID)
{
	MY_START_PROC();	//スタート画面の処理
	MY_START_DRAW();	//スタート画面の描画

	return;
}

//スタート画面の処理
VOID MY_START_PROC(VOID)
{
	//エンターキーを押したら、プレイシーンへ移動する
	if (MY_KEY_PUSH(KEY_INPUT_RETURN) == TRUE)
	{
		GameScene = GAME_SCENE_PLAY;
	}

	return;
}

//スタート画面の描画
VOID MY_START_DRAW(VOID)
{

	DrawString(0, 0, "スタート画面(エンターキーを押して下さい)", GetColor(255, 255, 255));
	return;
}

//プレイ画面
VOID MY_PLAY(VOID)
{
	MY_PLAY_PROC();	//プレイ画面の処理
	MY_PLAY_DRAW();	//プレイ画面の描画

	return;
}

//プレイ画面の処理
VOID MY_PLAY_PROC(VOID)
{
	if (MY_KEY_PUSH(KEY_INPUT_RETURN) == TRUE)
	{
		GameScene = GAME_SCENE_START;
		return;
	}

	return;
}

//プレイ画面の描画
VOID MY_PLAY_DRAW(VOID)
{
	//マップを描画
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			DrawGraph(
				map1_sita[tate][yoko].x,
				map1_sita[tate][yoko].y,
				mapChip.handle[map1_sita[tate][yoko].value],
				TRUE);
			
			DrawGraph(
				map1_naka[tate][yoko].x,
				map1_naka[tate][yoko].y,
				mapChip.handle[map1_naka[tate][yoko].value],
				TRUE);

			DrawGraph(
				map1_ue[tate][yoko].x,
				map1_ue[tate][yoko].y,
				mapChip.handle[map1_ue[tate][yoko].value],
				TRUE);

			//当たり判定の描画（デバッグ用）(中だけ)
			switch (map1_naka[tate][yoko].kind)
			{
			case MAP_KIND_KABE:	//壁のとき
				DrawBoxRect(map1_naka[tate][yoko].Coll, GetColor(255, 0, 0), FALSE);
				break;
			case MAP_KIND_TURO:	//通路のとき
				DrawBoxRect(map1_naka[tate][yoko].Coll, GetColor(0, 255, 0), FALSE);
				break;
			}


		}
	}

	return;
}

//エンド画面
VOID MY_END(VOID)
{
	MY_END_PROC();	//エンド画面の処理
	MY_END_DRAW();	//エンド画面の描画
	return;
}

//エンド画面の処理
VOID MY_END_PROC(VOID)
{
	//エスケープキーを押したら、スタートシーンへ移動する
	if (MY_KEY_DOWN(KEY_INPUT_ESCAPE) == TRUE)
	{
		GameScene = GAME_SCENE_START;
		return;
	}

	return;
}

//エンド画面の描画
VOID MY_END_DRAW(VOID)
{

	DrawString(0, 0, "エンド画面(エスケープキーを押して下さい)", GetColor(255, 255, 255));
	return;
}

//画像をまとめて読み込む関数
BOOL MY_LOAD_IMAGE(VOID)
{
	//マップの画像を分割する
	int mapRes = LoadDivGraph(
		GAME_MAP_PATH,										//赤弾のパス
		MAP_DIV_NUM, MAP_DIV_TATE, MAP_DIV_YOKO,			//赤弾を分割する数
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,						//画像を分割するの幅と高さ
		&mapChip.handle[0]);								//分割した画像が入るハンドル

	if (mapRes == -1)	//エラーメッセージ表示
	{
		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK); return FALSE;
	}

	//幅と高さを取得
	GetGraphSize(mapChip.handle[0], &mapChip.width, &mapChip.height);

	//マップデータを読み込む


	return TRUE;
}

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

//画像をまとめて削除する関数
VOID MY_DELETE_IMAGE(VOID)
{
	for (int i_num = 0; i_num < MAP_DIV_NUM; i_num++) { DeleteGraph(mapChip.handle[i_num]); }

	return;
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

//領域の当たり判定をする関数
BOOL MY_CHECK_RECT_COLL(RECT a, RECT b)
{
	if (a.left < b.right &&
		a.top < b.bottom &&
		a.right > b.left &&
		a.bottom > b.top
		)
	{
		return TRUE;	//当たっている
	}

	return FALSE;		//当たっていない
}

//RECTを利用して四角を描画
void DrawBoxRect(RECT r, unsigned int color, bool b)
{
	//引数を基に描画
	DrawBox(r.left, r.top, r.right, r.bottom, color, b);
	return;
}