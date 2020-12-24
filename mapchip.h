/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//マップチップで使用するモノをまとめています
#pragma once

//ヘッダーファイル読み込み
#include "DxLib.h"
#include "game.h"
#include "charachip.h"

//マクロ定義
#define MAP1_PATH			TEXT(".\\IMAGE\\MAP\\mapchip1.png")			//マップの画像
#define MAP1_PATH_SITA_CSV	TEXT(".\\IMAGE\\MAP\\map1_sita.csv")	//マップCSV(下)
#define MAP1_PATH_NAKA_CSV	TEXT(".\\IMAGE\\MAP\\map1_naka.csv")	//マップCSV(中)
#define MAP1_PATH_UE_CSV	TEXT(".\\IMAGE\\MAP\\map1_ue.csv")		//マップCSV(上)

#define MAP1_TATE_MAX	10	//マップの縦の広さ
#define MAP1_YOKO_MAX	20	//マップの横の広さ

#define MAP1_KABE_KIND	8	//マップの壁の種類

#define MAP1_DIV_WIDTH		32	//マップチップの１つ分の幅サイズ
#define MAP1_DIV_HEIGHT		32	//マップチップの１つ分の高さサイズ

#define MAP1_DIV_TATE		32	//マップチップを縦に分割する数
#define MAP1_DIV_YOKO		41	//マップチップを横に分割する数
#define MAP1_DIV_NUM	MAP1_DIV_TATE * MAP1_DIV_YOKO	//マップチップを分割する総数

#define MAP2_PATH			TEXT(".\\IMAGE\\MAP\\mapchip2.png")			//マップの画像
#define MAP2_PATH_SITA_CSV	TEXT(".\\IMAGE\\MAP\\map2_sita.csv")	//マップCSV(下)
#define MAP2_PATH_NAKA_CSV	TEXT(".\\IMAGE\\MAP\\map2_naka.csv")	//マップCSV(中)
#define MAP2_PATH_UE_CSV	TEXT(".\\IMAGE\\MAP\\map2_ue.csv")		//マップCSV(上)

#define MAP2_TATE_MAX	15	//マップの縦の広さ
#define MAP2_YOKO_MAX	20	//マップの横の広さ

#define MAP2_KABE_KIND	8	//マップの壁の種類

#define MAP2_DIV_WIDTH		32	//マップチップの１つ分の幅サイズ
#define MAP2_DIV_HEIGHT		32	//マップチップの１つ分の高さサイズ

#define MAP2_DIV_TATE		58	//マップチップを縦に分割する数
#define MAP2_DIV_YOKO		35	//マップチップを横に分割する数
#define MAP2_DIV_NUM	MAP2_DIV_TATE * MAP2_DIV_YOKO	//マップチップを分割する総数

#define MAP2_DOOR_MAX	8		//ドアの番号の種類

//列挙型
enum MAP1_KIND {
	MAP1_KIND_KABE,	//壁
	MAP1_KIND_TURO,	//通路
};

enum MAP2_KIND {
	MAP2_KIND_KABE,	//ブロック
	MAP2_KIND_TURO,	//通路
	MAP2_KIND_NONE,	//何もない
	MAP2_KIND_COIN,	//カギ
	MAP2_KIND_DOOR	//ドア
};

//構造体定義
typedef struct STRUCT_MAPCHIP1
{
	char path[PATH_MAX];				//パス
	int handle[MAP1_DIV_NUM];			//分割した画像ハンドルを取得
	int width;							//幅
	int height;							//高さ
}MAPCHIP1;	//MAP1CHIP構造体（マップチップのデータが入っている）

typedef struct STRUCT_MAP1
{
	int value;			//マップの値
	MAP1_KIND kind;		//マップの種類
	int x;				//X位置
	int y;				//Y位置
	int width;			//幅
	int height;			//高さ
	RECT coll;			//マップの当たり判定
}MAP1;					//MAP1構造体（ゲームで使用するデータが入っている）

typedef struct STRUCT_MAPCHIP2
{
	char path[PATH_MAX];				//パス
	int handle[MAP2_DIV_NUM];			//分割した画像ハンドルを取得
	int width;							//幅
	int height;							//高さ
}MAPCHIP2;	//MAP1CHIP構造体（マップチップのデータが入っている）

typedef struct STRUCT_MAP2
{
	int value;			//マップの値
	MAP2_KIND kind;		//マップの種類
	int x;				//X位置
	int y;				//Y位置
	int width;			//幅
	int height;			//高さ
	RECT coll;			//マップの当たり判定
}MAP2;					//MAP2構造体（ゲームで使用するデータが入っている）

typedef struct STRUCT_DOOR_KIND
{
	int x;			//ドアの場所X位置
	int y;			//ドアの場所Y位置
}DOOR_NUMBER;		//ドアの番号

//########## 外部のプロトタイプ宣言 ##########
extern BOOL MY_LOAD_MAPCHIP1(VOID);										//マップチップを読み込む関数
extern BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT rect);						//マップとプレイヤーの当たり判定をする関数
extern BOOL MY_LOAD_CSV_MAP1(const char* path, MAP1* m, MAP1* mInit);	//ゲームマップのCSVを読み込む関数

extern BOOL MY_LOAD_MAPCHIP2(VOID);										//マップチップを読み込む関数
extern BOOL MY_LOAD_CSV_MAP2(const char* path, MAP2* m, MAP2* mInit);	//ゲームマップのCSVを読み込む関数
extern VOID MY_CHECK_MAP2_DOWN(GRIF* g);								//マップとプレイヤーの当たり判定をする関数(下)
extern VOID MY_CHECK_MAP2_JUMP(GRIF* g);								//マップとプレイヤーの当たり判定(ジャンプ)をする関数
extern VOID MY_CHECK_MAP2_LEFT(GRIF* g);								//マップとプレイヤーの当たり判定(左)をする関数
extern VOID MY_CHECK_MAP2_RIGHT(GRIF* g);								//マップとプレイヤーの当たり判定(右)をする関数
extern BOOL MY_CHECK_GRIF_GROUND(GRIF g);								//プレイヤーが地面と接しているか当たり判定をする関数

extern BOOL MY_CHECK_MAP2_DOOR(GRIF g);	//マップとプレイヤーの当たり判定(ドア)をする関数
extern VOID MY_GET_MAP2_COIN(GRIF g);	//マップとプレイヤーの当たり判定(コイン)をする関数

//########## 外部のグローバル変数 ##########
extern MAPCHIP1 mapChip1;

extern MAP1 map1_sita[MAP1_TATE_MAX][MAP1_YOKO_MAX];
extern MAP1 mapInit1_sita[MAP1_TATE_MAX][MAP1_YOKO_MAX];

extern MAP1 map1_naka[MAP1_TATE_MAX][MAP1_YOKO_MAX];
extern MAP1 mapInit1_naka[MAP1_TATE_MAX][MAP1_YOKO_MAX];

extern MAP1 map1_ue[MAP1_TATE_MAX][MAP1_YOKO_MAX];
extern MAP1 mapInit1_ue[MAP1_TATE_MAX][MAP1_YOKO_MAX];

extern int Map1KabeID[MAP1_KABE_KIND];

extern MAPCHIP2 mapChip2;

extern MAP2 map2_sita[MAP1_TATE_MAX][MAP1_YOKO_MAX];		//マップデータ２（下）
extern MAP2 mapInit2_sita[MAP1_TATE_MAX][MAP1_YOKO_MAX];	//最初のマップデータ２（下）

extern MAP2 map2_naka[MAP1_TATE_MAX][MAP1_YOKO_MAX];		//マップデータ２（中）
extern MAP2 mapInit2_naka[MAP1_TATE_MAX][MAP1_YOKO_MAX];	//最初のマップデータ２（中）

extern MAP2 map2_ue[MAP1_TATE_MAX][MAP1_YOKO_MAX];			//マップデータ２（上）
extern MAP2 mapInit2_ue[MAP1_TATE_MAX][MAP1_YOKO_MAX];		//最初のマップデータ２（上）

extern int Map2KabeID[MAP2_KABE_KIND];	//壁のID

extern int Map2KeyID;	//鍵のID
extern int Map2DoorID;	//ドアのID
