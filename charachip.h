/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//キャラチップで使用するモノをまとめています
//例として、勇者にしています。イロイロとカスタマイズしてくださいね。
#pragma once

//ヘッダーファイル読み込み
#include "DxLib.h"
#include "game.h"

//画像のパス
#define YUSHA_CHIP1_PATH	TEXT(".\\IMAGE\\CHARA\\charaF01_1a1.png")			//勇者の画像１（上下左右）
#define YUSHA_CHIP2_PATH	TEXT(".\\IMAGE\\CHARA\\charaF01_1a1-X.png")			//勇者の画像２（斜め）

#define YUSHA_DIV_WIDTH		48	//勇者のキャラチップの１つ分の幅サイズ
#define YUSHA_DIV_HEIGHT	48	//勇者のキャラチップの１つ分の高さサイズ

#define YUSHA_DIV_TATE		3	//勇者のキャラチップを縦に分割する数
#define YUSHA_DIV_YOKO		4	//勇者のキャラチップを横に分割する数
#define YUSHA_DIV_NUM	YUSHA_DIV_TATE * YUSHA_DIV_YOKO	//勇者のキャラチップを分割する総数

#define YUSHA_IMG_CHANGE_MAX	10	//画像を変更するカウンタMAX値
#define YUSHA_MOVE_SPEED		2	//移動速度

//列挙型
//注意）勇者のキャラチップを見て決めています。
//注１）左上が0、右に向かって＋１されます
//注２）一番右まで行ったら、左に折り返して＋１されます
enum YUSHA_KIND_1 {
	D_1, D_2, D_3,
	L_1, L_2, L_3,
	R_1, R_2, R_3,
	U_1, U_2, U_3
};//勇者の画像の種類１(U上/D下/R右/L左)

enum YUSHA_KIND_2 {
	LD_1, LD_2, LD_3,
	LU_1, LU_2, LU_3,
	RD_1, RD_2, RD_3,
	RU_1, RU_2, RU_3
};//勇者の画像の種類２(LD左下/LU右上/RD右下/RU右上)

//構造体定義
typedef struct STRUCT_YUSHACHIP
{
	char path[PATH_MAX];				//パス
	int handle[YUSHA_DIV_NUM];			//分割した画像ハンドルを取得
	int width;							//幅
	int height;							//高さ
}YUSHACHIP;	//YUSHACHIP構造体（勇者のキャラチップのデータが入っている）

typedef struct STRUCT_YUSHA
{
	int kind1;			//画像の種類１
	int kind2;			//画像の種類２
	int x;				//X位置
	int y;				//Y位置
	int oldx;			//X位置(直前)
	int oldy;			//Y位置(直前)
	int width;			//幅
	int height;			//高さ
	int speed;			//移動速度
	
	BOOL IsMoveNaname;	//斜め移動をしているか

	int imgChangeCnt;	//画像更新カウンタ
	int imgChangeCntMAX;//画像更新カウンタMAX値

	RECT coll;			//当たり判定

}YUSHA;	//勇者構造体

//外部のプロトタイプ宣言
extern BOOL MY_LOAD_CHARA_YUSHA(const char* path, YUSHACHIP* yusha);	//勇者の画像を読み込む
extern VOID MY_DRAW_YUSHA(VOID);										//勇者を描画する関数
extern VOID MY_INIT_YUSHA(VOID);										//勇者の位置を初期化
extern VOID MY_MOVE_YUSHA(VOID);										//勇者を移動させる関数

//外部のグローバル変数
extern YUSHACHIP yushaChip1;	//勇者の画像１（上下左右）
extern YUSHACHIP yushaChip2;	//勇者の画像２（斜め）
extern YUSHA yusha;				//勇者の情報を管理