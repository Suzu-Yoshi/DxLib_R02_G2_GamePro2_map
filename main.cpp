/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//初期：CSVファイルのデータを読み込んで、マップと当たり判定を作るサンプル
//追加：キャラチップを読み込み、移動に合わせて画像を動かすサンプル
//サンプルなので、丸パクリせず、参考にしてください。
//サンプルなので、必要最低限のことしか、していません。自由にカスタマイズしてください。

//########## ヘッダーファイル読み込み ##########
#include "game.h"
#include "mapchip.h"
#include "charachip.h"

typedef struct STRUCT_IMAGE
{
	char path[PATH_MAX];		//パス
	int handle;					//ハンドル
	int x;						//X位置
	int y;						//Y位置
	int width;					//幅
	int height;					//高さ
}IMAGE;	//画像構造体

//########## グローバル変数 ##########

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

	//キャラチップを読み込む
	if (MY_LOAD_CHARA_YUSHA(YUSHA_CHIP1_PATH, &yushaChip1) == FALSE) { return -1; }
	if (MY_LOAD_CHARA_YUSHA(YUSHA_CHIP2_PATH, &yushaChip2) == FALSE) { return -1; }

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
		MY_INIT_YUSHA();	//勇者の位置を初期化

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

	//直前の位置を取得
	yusha.oldx = yusha.x;
	yusha.oldy = yusha.y;

	MY_MOVE_YUSHA();//勇者の移動処理

	//プレイヤーの当たり判定を再計算（当たり判定を小さくしている）
	yusha.coll.left = yusha.x + 12;
	yusha.coll.top = yusha.y + 20;
	yusha.coll.right = yusha.x + yusha.width - 12;
	yusha.coll.bottom = yusha.y + yusha.height - 0;

	//マップ１との当たり判定
	if (MY_CHECK_MAP1_PLAYER_COLL(yusha.coll) == TRUE)
	{
		//何かにぶつかっていたら、移動しない
		yusha.x = yusha.oldx;
		yusha.y = yusha.oldy;
	}

	return;
}

//プレイ画面の描画
VOID MY_PLAY_DRAW(VOID)
{
	//マップ下を描画
	for (int tate = 0; tate < MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < MAP_YOKO_MAX; yoko++)
		{
			DrawGraph(
				map1_sita[tate][yoko].x,
				map1_sita[tate][yoko].y,
				mapChip.handle[map1_sita[tate][yoko].value],
				TRUE);
		}
	}

	//マップ中を描画
	for (int tate = 0; tate < MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < MAP_YOKO_MAX; yoko++)
		{

			DrawGraph(
				map1_naka[tate][yoko].x,
				map1_naka[tate][yoko].y,
				mapChip.handle[map1_naka[tate][yoko].value],
				TRUE);
		}
	}

	MY_DRAW_YUSHA();	//勇者を描画

	//マップ上を描画
	for (int tate = 0; tate < MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < MAP_YOKO_MAX; yoko++)
		{
			DrawGraph(
				map1_ue[tate][yoko].x,
				map1_ue[tate][yoko].y,
				mapChip.handle[map1_ue[tate][yoko].value],
				TRUE);
		}
	}

	//デバッグ描画
	for (int tate = 0; tate < MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < MAP_YOKO_MAX; yoko++)
		{
			//当たり判定の描画（デバッグ用）(中だけ)
			switch (map1_naka[tate][yoko].kind)
			{
			case MAP_KIND_KABE:	//壁のとき
				DrawBoxRect(map1_naka[tate][yoko].coll, GetColor(255, 0, 0), FALSE);
				break;
			case MAP_KIND_TURO:	//通路のとき
				DrawBoxRect(map1_naka[tate][yoko].coll, GetColor(0, 255, 0), FALSE);
				break;
			}
		}
	}

	//勇者の当たり判定デバッグ描画
	DrawBoxRect(yusha.coll, GetColor(0, 0, 255), FALSE);

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

	return TRUE;
}


//画像をまとめて削除する関数
VOID MY_DELETE_IMAGE(VOID)
{
	for (int i_num = 0; i_num < MAP_DIV_NUM; i_num++) { DeleteGraph(mapChip.handle[i_num]); }

	return;
}

//RECTを利用して四角を描画
void DrawBoxRect(RECT r, unsigned int color, bool b)
{
	//引数を基に描画
	DrawBox(r.left, r.top, r.right, r.bottom, color, b);
	return;
}