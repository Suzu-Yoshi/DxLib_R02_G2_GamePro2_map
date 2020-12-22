/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//キャラチップで使用するモノをまとめています
//例として、勇者にしています。イロイロとカスタマイズしてくださいね。
#pragma once

//ヘッダーファイル読み込み
#include "DxLib.h"
#include "game.h"

//勇者系
#define YUSHA_CHIP1_PATH	TEXT(".\\IMAGE\\CHARA\\charaF01_1a1.png")			//勇者の画像１（上下左右）
#define YUSHA_CHIP2_PATH	TEXT(".\\IMAGE\\CHARA\\charaF01_1a1-X.png")			//勇者の画像２（斜め）

#define YUSHA_DIV_WIDTH		48	//勇者のキャラチップの１つ分の幅サイズ
#define YUSHA_DIV_HEIGHT	48	//勇者のキャラチップの１つ分の高さサイズ

#define YUSHA_DIV_TATE		3	//勇者のキャラチップを縦に分割する数
#define YUSHA_DIV_YOKO		4	//勇者のキャラチップを横に分割する数
#define YUSHA_DIV_NUM	YUSHA_DIV_TATE * YUSHA_DIV_YOKO	//勇者のキャラチップを分割する総数

#define YUSHA_IMG_CHANGE_MAX	10	//画像を変更するカウンタMAX値
#define YUSHA_MOVE_SPEED		2	//移動速度

//グリフィン系
#define GRIF_CHIP1_PATH	TEXT(".\\IMAGE\\CHARA\\grif02a.png")		//グリフィンの画像
#define GRIF_CHIP2_PATH	TEXT(".\\IMAGE\\CHARA\\grif02b.png")		//グリフィンの画像

#define GRIF_DIV_WIDTH		45	//グリフィンのキャラチップの１つ分の幅サイズ
#define GRIF_DIV_HEIGHT		50	//グリフィンのキャラチップの１つ分の高さサイズ

#define GRIF_DIV_TATE		3	//グリフィンのキャラチップを縦に分割する数
#define GRIF_DIV_YOKO		4	//グリフィンのキャラチップを横に分割する数
#define GRIF_DIV_NUM	GRIF_DIV_TATE * GRIF_DIV_YOKO	//グリフィンのキャラチップを分割する総数

#define GRIF_IMG_CHANGE_MAX	10	//画像を変更するカウンタMAX値
#define GRIF_MOVE_SPEED		2	//移動速度

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

enum GRIF_KIND_1 {
	GF_1, GF_2, GF_3,
	GL_1, GL_2, GL_3,
	GR_1, GR_2, GR_3,
	GB_1, GB_2, GB_3
};//グリフィンの画像の種類１(GF前/GB後/GR右/GL左)

enum GRIF_KIND_2 {
	GFF_1, GFF_2, GFF_3,
	GFL_1, GFL_2, GFL_3,
	GFR_1, GFR_2, GFR_3,
	GFB_1, GFB_2, GFB_3
};//グリフィンの画像の種類２(GFU飛上/GFL飛左/GFR飛右/GFD飛下)

//構造体定義
typedef struct STRUCT_YUSHACHIP
{
	char path[PATH_MAX];				//パス
	int handle[YUSHA_DIV_NUM];			//分割した画像ハンドルを取得
	int width;							//幅
	int height;							//高さ
}YUSHACHIP;	//YUSHACHIP構造体（勇者のキャラチップのデータが入っている）

//構造体定義
typedef struct STRUCT_GRIFCHIP
{
	char path[PATH_MAX];				//パス
	int handle[GRIF_DIV_NUM];			//分割した画像ハンドルを取得
	int width;							//幅
	int height;							//高さ
}GRIFCHIP;	//GRIFCHIP構造体（勇者のキャラチップのデータが入っている）

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

typedef struct STRUCT_GRIF
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

	BOOL IsJump;		//ジャンプしているか
	BOOL IsMoveLeft;	//左に移動しているか
	BOOL IsMoveRight;	//右に移動しているか

	int imgChangeCnt;	//画像更新カウンタ
	int imgChangeCntMAX;//画像更新カウンタMAX値

	RECT coll;			//当たり判定

}GRIF;	//グリフィン構造体

//外部のプロトタイプ宣言
extern BOOL MY_LOAD_CHARA_YUSHA(const char* path, YUSHACHIP* yusha);	//勇者の画像を読み込む
extern VOID MY_INIT_YUSHA(VOID);										//勇者の位置を初期化
extern VOID MY_DRAW_YUSHA(VOID);										//勇者を描画する関数
extern VOID MY_MOVE_YUSHA(VOID);										//勇者を移動させる関数

extern BOOL MY_LOAD_CHARA_GRIF(const char* path, GRIFCHIP* grif);	//グリフィンの画像を読み込む
extern VOID MY_INIT_GRIF(VOID);										//グリフィンの位置を初期化
extern VOID MY_DRAW_GRIF(VOID);										//グリフィンを描画する関数
extern VOID MY_MOVE_GRIF(VOID);										//グリフィンを移動させる関数
extern VOID MY_CALC_GRIF_COLL(VOID);								//プレイヤーの当たり判定を再計算する関数

//外部のグローバル変数
extern YUSHACHIP yushaChip1;	//勇者の画像１（上下左右）
extern YUSHACHIP yushaChip2;	//勇者の画像２（斜め）
extern YUSHA yusha;				//勇者の情報を管理

extern GRIFCHIP grifChip1;		//グリフィンの画像１（上下左右）
extern GRIFCHIP grifChip2;		//グリフィンの画像２（斜め）
extern GRIF grif;				//グリフィンの情報を管理