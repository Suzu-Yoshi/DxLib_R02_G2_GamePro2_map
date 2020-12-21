/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//キャラチップで使用するモノをまとめています
#pragma once

//ヘッダーファイル読み込み
#include "DxLib.h"
#include "game.h"

//画像のパス
#define GAME_CHARA_1_PATH	TEXT(".\\IMAGE\\CHARA\\charaF01_1a1.png.png")		//勇者の画像１（上下左右）
#define GAME_CHARA_2_PATH	TEXT(".\\IMAGE\\CHARA\\charaF01_1a1-X.png")			//勇者の画像２（斜め）

#define CHARA_DIV_WIDTH		48	//キャラチップの１つ分の幅サイズ
#define CHARA_DIV_HEIGHT	48	//キャラチップの１つ分の高さサイズ

#define CHARA_DIV_TATE		4	//キャラチップを縦に分割する数
#define CHARA_DIV_YOKO		3	//キャラチップを横に分割する数
#define CHARA_DIV_NUM	CHARA_DIV_TATE * CHARA_DIV_YOKO	//マップチップを分割する総数

//構造体定義
typedef struct STRUCT_CHARACHIP
{
	char path[PATH_MAX];				//パス
	int handle[CHARA_DIV_NUM];			//分割した画像ハンドルを取得
	int width;							//幅
	int height;							//高さ
}CHARACHIP;	//CHARACHIP構造体（キャラチップのデータが入っている）
