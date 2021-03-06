/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//キャラチップで使用するモノをまとめています
//例として、勇者にしています。イロイロとカスタマイズしてくださいね。
#pragma once

//ヘッダーファイル読み込み
#include "DxLib.h"
#include "game.h"

//勇者系
#define YUSHA_CHIP1_PATH	TEXT(".\\IMAGE\\CHARA\\charaF01_1a5.png")			//勇者の画像１（上下左右）
#define YUSHA_CHIP2_PATH	TEXT(".\\IMAGE\\CHARA\\charaF01_1a5-X.png")			//勇者の画像２（斜め）

#define YUSHA_DIV_WIDTH		48	//勇者のキャラチップの１つ分の幅サイズ
#define YUSHA_DIV_HEIGHT	48	//勇者のキャラチップの１つ分の高さサイズ

#define YUSHA_DIV_TATE		3	//勇者のキャラチップを縦に分割する数
#define YUSHA_DIV_YOKO		4	//勇者のキャラチップを横に分割する数
#define YUSHA_DIV_NUM	YUSHA_DIV_TATE * YUSHA_DIV_YOKO	//勇者のキャラチップを分割する総数

#define YUSHA_IMG_CHANGE_MAX	10	//画像を変更するカウンタMAX値
#define YUSHA_MOVE_SPEED		2	//移動速度

//グリフィン系
#define GRIF_CHIP1_PATH	TEXT(".\\IMAGE\\CHARA\\grif02a.png")		//グリフィンの画像（歩き）
#define GRIF_CHIP2_PATH	TEXT(".\\IMAGE\\CHARA\\grif02b_fix.png")	//グリフィンの画像（飛行）(元画像の位置を修正済)

#define GRIF_DIV_WIDTH		45	//グリフィンのキャラチップの１つ分の幅サイズ
#define GRIF_DIV_HEIGHT		50	//グリフィンのキャラチップの１つ分の高さサイズ

#define GRIF_DIV_TATE		3	//グリフィンのキャラチップを縦に分割する数
#define GRIF_DIV_YOKO		4	//グリフィンのキャラチップを横に分割する数
#define GRIF_DIV_NUM	GRIF_DIV_TATE * GRIF_DIV_YOKO	//グリフィンのキャラチップを分割する総数

#define GRIF_IMG_CHANGE_MAX	5	//画像を変更するカウンタMAX値
#define GRIF_MOVE_SPEED		1	//移動速度

#define GRIF_JUMP_FRAME		60	//ジャンプするフレーム数
#define GRIF_JUMP_POWER		8	//１回のジャンプ力

//列挙型
//注意）勇者のキャラチップを見て決めています。
//注１）左上が0、右に向かって＋１されます
//注２）一番右まで行ったら、左に折り返して＋１されます
enum YUSHA_KIND_1 {
	YD_1, YD_2, YD_3,
	YL_1, YL_2, YL_3,
	YR_1, YR_2, YR_3,
	YU_1, YU_2, YU_3
};//勇者の画像の種類１(U上/D下/R右/L左)

enum YUSHA_KIND_2 {
	YLD_1, YLD_2, YLD_3,
	YLU_1, YLU_2, YLU_3,
	YRD_1, YRD_2, YRD_3,
	YRU_1, YRU_2, YRU_3
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

	int choseiX;		//当たり判定調整X
	int choseiY;		//当たり判定調整Y
	int choseiWidth;	//当たり判定調整幅
	int choseiHeight;	//当たり判定調整高さ

	BOOL IsDirRight;		//右を向いているか
	BOOL IsDirLeft;			//左を向いているか

	BOOL IsJump;		//ジャンプしているか
	int JumpPower;	//ジャンプ最大量

	int JumpTimeCnt;		//ジャンプしている時間
	int BeforeJumpY;		//ジャンプする直前のY位置

	int imgChangeCnt;	//画像更新カウンタ
	int imgChangeCntMAX;//画像更新カウンタMAX値

	int mapX;		//マップ左上を0としたとき、マップ上でどのぐらいのX位置にいるのか
	int mapY;		//マップ左上を0としたとき、マップ上でどのぐらいのY位置にいるのか

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

extern VOID MY_PLAY_ANIM_YUSHA_ARUKI(YUSHA_KIND_1 Y_MIN, YUSHA_KIND_1 Y_MAX);		//勇者の歩くアニメーション関数
extern VOID MY_PLAY_ANIM_YUSHA_NANAME(YUSHA_KIND_2 GF_MIN, YUSHA_KIND_2 GF_MAX);	//勇者の斜めアニメーション関数

extern VOID MY_PLAY_MOVE_LEFT(int start,int end);		//左に行く処理
extern VOID MY_PLAY_MOVE_RIGHT(int start, int end);		//右に行く処理
extern VOID MY_PLAY_MOVE_JUMP(VOID);		//ジャンプの処理

extern VOID MY_PLAY_ANIM_ARUKI(GRIF_KIND_1 G_MIN, GRIF_KIND_1 G_MAX);		//歩くアニメーション関数
extern VOID MY_PLAY_ANIM_HABATAKI(GRIF_KIND_2 G_MIN, GRIF_KIND_2 G_MAX);	//羽ばたきのアニメーション関数

extern VOID MY_TOUCH_MAP2_DOOR(GRIF grif);	//ドアに触れたときの処理

//外部のグローバル変数
extern YUSHACHIP yushaChip1;	//勇者の画像１（上下左右）
extern YUSHACHIP yushaChip2;	//勇者の画像２（斜め）
extern YUSHA yusha;				//勇者の情報を管理

extern GRIFCHIP grifChip1;		//グリフィンの画像１（上下左右）
extern GRIFCHIP grifChip2;		//グリフィンの画像２（斜め）
extern GRIF grif;				//グリフィンの情報を管理