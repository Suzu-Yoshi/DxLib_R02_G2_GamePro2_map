/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//キャラチップで使用するモノをまとめています

//########## ヘッダーファイル読み込み ##########
#include "game.h"
#include "charachip.h"
#include "mapchip.h"

//########## グローバル変数 ##########

//勇者のキャラチップの画像を管理
YUSHACHIP yushaChip1;	//勇者の画像１（上下左右）
YUSHACHIP yushaChip2;	//勇者の画像２（斜め）

//勇者の情報を管理
YUSHA yusha;

//########## 勇者チップを読み込む関数 ##########
//引数１：画像のパス
//引数２：マップ配列の先頭アドレス
BOOL MY_LOAD_CHARA_YUSHA(const char* path, YUSHACHIP* yusha)
{
	//マップの画像を分割する
	int mapRes = LoadDivGraph(
		path,												//パス
		YUSHA_DIV_NUM, YUSHA_DIV_TATE, YUSHA_DIV_YOKO,		//分割する数
		YUSHA_DIV_WIDTH, YUSHA_DIV_HEIGHT,					//分割するの幅と高さ
		&yusha->handle[0]);								//画像が入るハンドル

	if (mapRes == -1)	//エラーメッセージ表示
	{
		MessageBox(GetMainWindowHandle(), path, IMAGE_LOAD_ERR_TITLE, MB_OK); return FALSE;
	}

	//幅と高さを取得
	GetGraphSize(yusha->handle[0], &yusha->width, &yusha->height);

	return TRUE;
}
//########## 勇者の位置を初期化 ##########
VOID MY_INIT_YUSHA(VOID)
{
	yusha.x = MAP_DIV_WIDTH * 0;	//マップのサイズを基準に決める
	yusha.y = MAP_DIV_HEIGHT * 5;	//マップのサイズを基準に決める;
	yusha.IsMoveNaname = FALSE;
	yusha.kind1 = D_1;
	yusha.kind2 = LD_1;
	yusha.speed = YUSHA_MOVE_SPEED;	//移動速度

	//幅と高さを設定
	yusha.width = yushaChip1.width;
	yusha.height = yushaChip1.height;
	
	yusha.imgChangeCnt = 0;
	yusha.imgChangeCntMAX = YUSHA_IMG_CHANGE_MAX;	//画像を変更するカウンタMAX

	return;
}

//########## 勇者を移動させる関数 ##########
VOID MY_MOVE_YUSHA(VOID)
{
	//入力に応じて画像を変える

	//上に移動するとき
	if (MY_KEY_DOWN(KEY_INPUT_W) == TRUE
		&& MY_KEY_DOWN(KEY_INPUT_D) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_S) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_A) == FALSE)
	{
		yusha.IsMoveNaname = FALSE;	//斜め移動していない

		if (yusha.kind1 >= U_1 && yusha.kind1 < U_3)
		{
			//画像変更カウンタ
			if (yusha.imgChangeCnt < yusha.imgChangeCntMAX)
			{
				yusha.imgChangeCnt++;
			}
			else //画像を変えるタイミングになったら
			{
				yusha.kind1++;			//次の画像にする
				yusha.imgChangeCnt = 0;	//変更カウンタ初期化
			}
		}
		else
		{
			yusha.kind1 = U_1;	//最初の画像にする
		}

		yusha.y -= yusha.speed;	//移動
	}

	//右に移動するとき
	if (MY_KEY_DOWN(KEY_INPUT_W) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_D) == TRUE
		&& MY_KEY_DOWN(KEY_INPUT_S) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_A) == FALSE)
	{
		yusha.IsMoveNaname = FALSE;	//斜め移動していない

		if (yusha.kind1 >= R_1 && yusha.kind1 < R_3)
		{
			//画像変更カウンタ
			if (yusha.imgChangeCnt < yusha.imgChangeCntMAX)
			{
				yusha.imgChangeCnt++;
			}
			else //画像を変えるタイミングになったら
			{
				yusha.kind1++;			//次の画像にする
				yusha.imgChangeCnt = 0;	//変更カウンタ初期化
			}
		}
		else
		{
			yusha.kind1 = R_1;	//最初の画像にする
		}
		yusha.x += yusha.speed;	//移動
	}

	//左に移動するとき
	if (MY_KEY_DOWN(KEY_INPUT_W) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_D) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_S) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_A) == TRUE)
	{
		yusha.IsMoveNaname = FALSE;	//斜め移動していない

		if (yusha.kind1 >= L_1 && yusha.kind1 < L_3)
		{
			//画像変更カウンタ
			if (yusha.imgChangeCnt < yusha.imgChangeCntMAX)
			{
				yusha.imgChangeCnt++;
			}
			else //画像を変えるタイミングになったら
			{
				yusha.kind1++;			//次の画像にする
				yusha.imgChangeCnt = 0;	//変更カウンタ初期化
			}
		}
		else
		{
			yusha.kind1 = L_1;	//最初の画像にする
		}
		yusha.x -= yusha.speed;	//移動
	}

	//下に移動するとき
	if (MY_KEY_DOWN(KEY_INPUT_W) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_D) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_S) == TRUE
		&& MY_KEY_DOWN(KEY_INPUT_A) == FALSE)
	{
		yusha.IsMoveNaname = FALSE;	//斜め移動していない

		if (yusha.kind1 >= D_1 && yusha.kind1 < D_3)
		{
			//画像変更カウンタ
			if (yusha.imgChangeCnt < yusha.imgChangeCntMAX)
			{
				yusha.imgChangeCnt++;
			}
			else //画像を変えるタイミングになったら
			{
				yusha.kind1++;			//次の画像にする
				yusha.imgChangeCnt = 0;	//変更カウンタ初期化
			}
		}
		else
		{
			yusha.kind1 = D_1;	//最初の画像にする
		}
		yusha.y += yusha.speed;	//移動
	}

	//下左に移動するとき
	if (MY_KEY_DOWN(KEY_INPUT_W) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_D) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_S) == TRUE
		&& MY_KEY_DOWN(KEY_INPUT_A) == TRUE)
	{
		yusha.IsMoveNaname = TRUE;	//斜め移動している

		if (yusha.kind2 >= LD_1 && yusha.kind2 < LD_3)
		{
			//画像変更カウンタ
			if (yusha.imgChangeCnt < yusha.imgChangeCntMAX)
			{
				yusha.imgChangeCnt++;
			}
			else //画像を変えるタイミングになったら
			{
				yusha.kind2++;			//次の画像にする
				yusha.imgChangeCnt = 0;	//変更カウンタ初期化
			}
		}
		else
		{
			yusha.kind2 = LD_1;	//最初の画像にする
		}
		yusha.x -= yusha.speed;	//移動
		yusha.y += yusha.speed;	//移動
	}

	//上左に移動するとき
	if (MY_KEY_DOWN(KEY_INPUT_W) == TRUE
		&& MY_KEY_DOWN(KEY_INPUT_D) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_S) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_A) == TRUE)
	{
		yusha.IsMoveNaname = TRUE;	//斜め移動している

		if (yusha.kind2 >= LU_1 && yusha.kind2 < LU_3)
		{
			//画像変更カウンタ
			if (yusha.imgChangeCnt < yusha.imgChangeCntMAX)
			{
				yusha.imgChangeCnt++;
			}
			else //画像を変えるタイミングになったら
			{
				yusha.kind2++;			//次の画像にする
				yusha.imgChangeCnt = 0;	//変更カウンタ初期化
			}
		}
		else
		{
			yusha.kind2 = LU_1;	//最初の画像にする
		}
		yusha.x -= yusha.speed;	//移動
		yusha.y -= yusha.speed;	//移動
	}

	//下右に移動するとき
	if (MY_KEY_DOWN(KEY_INPUT_W) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_D) == TRUE
		&& MY_KEY_DOWN(KEY_INPUT_S) == TRUE
		&& MY_KEY_DOWN(KEY_INPUT_A) == FALSE)
	{
		yusha.IsMoveNaname = TRUE;	//斜め移動している

		if (yusha.kind2 >= RD_1 && yusha.kind2 < RD_3)
		{
			//画像変更カウンタ
			if (yusha.imgChangeCnt < yusha.imgChangeCntMAX)
			{
				yusha.imgChangeCnt++;
			}
			else //画像を変えるタイミングになったら
			{
				yusha.kind2++;			//次の画像にする
				yusha.imgChangeCnt = 0;	//変更カウンタ初期化
			}
		}
		else
		{
			yusha.kind2 = RD_1;	//最初の画像にする
		}
		yusha.x += yusha.speed;	//移動
		yusha.y += yusha.speed;	//移動
	}

	//上右に移動するとき
	if (MY_KEY_DOWN(KEY_INPUT_W) == TRUE
		&& MY_KEY_DOWN(KEY_INPUT_D) == TRUE
		&& MY_KEY_DOWN(KEY_INPUT_S) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_A) == FALSE)
	{
		yusha.IsMoveNaname = TRUE;	//斜め移動している

		if (yusha.kind2 >= RU_1 && yusha.kind2 < RU_3)
		{
			//画像変更カウンタ
			if (yusha.imgChangeCnt < yusha.imgChangeCntMAX)
			{
				yusha.imgChangeCnt++;
			}
			else //画像を変えるタイミングになったら
			{
				yusha.kind2++;			//次の画像にする
				yusha.imgChangeCnt = 0;	//変更カウンタ初期化
			}
		}
		else
		{
			yusha.kind2 = RU_1;	//最初の画像にする
		}
		yusha.x += yusha.speed;	//移動
		yusha.y -= yusha.speed;	//移動
	}

	//何も押していないとき
	if (MY_KEY_DOWN(KEY_INPUT_W) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_D) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_S) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_A) == FALSE)
	{
		yusha.imgChangeCnt = 0;		//変更カウンタ初期化

		//画像を止まっている画像にする
		if (yusha.kind1 >= U_1 && yusha.kind1 <= U_3) { yusha.kind1 = U_2; }
		else if (yusha.kind1 >= R_1 && yusha.kind1 <= R_3) { yusha.kind1 = R_2; }
		else if (yusha.kind1 >= L_1 && yusha.kind1 <= L_3) { yusha.kind1 = L_2; }
		else if (yusha.kind1 >= D_1 && yusha.kind1 <= D_3) { yusha.kind1 = D_2; }

		if (yusha.kind2 >= LD_1 && yusha.kind2 <= LD_3) { yusha.kind2 = LD_2; }
		else if (yusha.kind2 >= LU_1 && yusha.kind2 <= LU_3) { yusha.kind2 = LU_2; }
		else if (yusha.kind2 >= RD_1 && yusha.kind2 <= RD_3) { yusha.kind2 = RD_2; }
		else if (yusha.kind2 >= RU_1 && yusha.kind2 <= RU_3) { yusha.kind2 = RU_2; }
	}
	return;
}

//########## 勇者を描画する関数 ##########
VOID MY_DRAW_YUSHA(VOID)
{
	//上下左右の移動のとき
	if (yusha.IsMoveNaname == FALSE)	//上下左右の移動のとき
	{
		DrawGraph(yusha.x, yusha.y, yushaChip1.handle[yusha.kind1], TRUE);
	}
	else //斜めの移動のとき
	{
		DrawGraph(yusha.x, yusha.y, yushaChip2.handle[yusha.kind2], TRUE);
	}


	return;
}