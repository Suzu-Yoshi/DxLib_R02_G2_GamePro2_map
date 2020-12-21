/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//マップチップで使用するモノをまとめています
#pragma once

//ヘッダーファイル読み込み
#include "DxLib.h"
#include "game.h"

//マクロ定義
#define MAP1_PATH			TEXT(".\\IMAGE\\MAP\\mapchip1.png")			//マップの画像
#define MAP1_PATH_SITA_CSV	TEXT(".\\IMAGE\\MAP\\map_map1_sita.csv")	//マップCSV(下)
#define MAP1_PATH_NAKA_CSV	TEXT(".\\IMAGE\\MAP\\map_map1_naka.csv")	//マップCSV(中)
#define MAP1_PATH_UE_CSV	TEXT(".\\IMAGE\\MAP\\map_map1_ue.csv")		//マップCSV(上)

#define MAP1_TATE_MAX	10	//マップの縦の広さ
#define MAP1_YOKO_MAX	20	//マップの横の広さ

#define MAP1_KABE_KIND	8	//マップの壁の種類

#define MAP1_DIV_WIDTH		32	//マップチップの１つ分の幅サイズ
#define MAP1_DIV_HEIGHT		32	//マップチップの１つ分の高さサイズ

#define MAP1_DIV_TATE		32	//マップチップを縦に分割する数
#define MAP1_DIV_YOKO		41	//マップチップを横に分割する数
#define MAP1_DIV_NUM	MAP1_DIV_TATE * MAP1_DIV_YOKO	//マップチップを分割する総数

//列挙型
enum MAP1_KIND {
	MAP1_KIND_KABE,	//壁
	MAP1_KIND_TURO,	//通路
};

//構造体定義
typedef struct STRUCT_MAPCHIP
{
	char path[PATH_MAX];				//パス
	int handle[MAP1_DIV_NUM];			//分割した画像ハンドルを取得
	int width;							//幅
	int height;							//高さ
}MAP1CHIP;	//MAP1CHIP構造体（マップチップのデータが入っている）

typedef struct STRUCT_MAP
{
	int value;			//マップの値
	MAP1_KIND kind;		//マップの種類
	int x;				//X位置
	int y;				//Y位置
	int width;			//幅
	int height;			//高さ
	RECT coll;			//マップの当たり判定
}MAP1;					//MAP1構造体（ゲームで使用するデータが入っている）

//########## 外部のプロトタイプ宣言 ##########
extern BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT rect);					//マップとプレイヤーの当たり判定をする関数
extern BOOL MY_LOAD_CSV_MAP1(const char* path, MAP1* m, MAP1* mInit);	//ゲームマップのCSVを読み込む関数

//########## 外部のグローバル変数 ##########
extern MAP1CHIP mapChip1;

extern MAP1 map1_sita[MAP1_TATE_MAX][MAP1_YOKO_MAX];
extern MAP1 mapInit1_sita[MAP1_TATE_MAX][MAP1_YOKO_MAX];

extern MAP1 map1_naka[MAP1_TATE_MAX][MAP1_YOKO_MAX];
extern MAP1 mapInit1_naka[MAP1_TATE_MAX][MAP1_YOKO_MAX];

extern MAP1 map1_ue[MAP1_TATE_MAX][MAP1_YOKO_MAX];
extern MAP1 mapInit1_ue[MAP1_TATE_MAX][MAP1_YOKO_MAX];

extern int Map1KabeID[MAP1_KABE_KIND];