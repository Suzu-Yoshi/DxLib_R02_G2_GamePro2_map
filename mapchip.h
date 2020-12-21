/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//マップチップで使用するモノをまとめています
#pragma once

//ヘッダーファイル読み込み
#include "DxLib.h"
#include "game.h"

//マクロ定義
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

//列挙型
enum MAP_KIND {
	MAP_KIND_KABE,	//壁
	MAP_KIND_TURO,	//通路
};

//構造体定義
typedef struct STRUCT_MAPCHIP
{
	char path[PATH_MAX];				//パス
	int handle[MAP_DIV_NUM];			//分割した画像ハンドルを取得
	int width;							//幅
	int height;							//高さ
}MAPCHIP;	//MAPCHIP構造体（マップチップのデータが入っている）

typedef struct STRUCT_MAP
{
	int value;			//マップの値
	MAP_KIND kind;		//マップの種類
	int x;				//X位置
	int y;				//Y位置
	int width;			//幅
	int height;			//高さ
	RECT Coll;			//マップの当たり判定
}MAP;	//MAP構造体（ゲームで使用するデータが入っている）