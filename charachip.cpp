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

//グリフィンのキャラチップの画像を管理
GRIFCHIP grifChip1;		//グリフィンの画像１（上下左右）
GRIFCHIP grifChip2;		//グリフィンの画像２（斜め）

//グリフィンの情報を管理
GRIF grif;

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

//########## グリフィンチップを読み込む関数 ##########
//引数１：画像のパス
//引数２：マップ配列の先頭アドレス
BOOL MY_LOAD_CHARA_GRIF(const char* path, GRIFCHIP* grif)
{
	//マップの画像を分割する
	int mapRes = LoadDivGraph(
		path,												//パス
		GRIF_DIV_NUM, GRIF_DIV_TATE, GRIF_DIV_YOKO,			//分割する数
		GRIF_DIV_WIDTH, GRIF_DIV_HEIGHT,					//分割するの幅と高さ
		&grif->handle[0]);									//画像が入るハンドル

	if (mapRes == -1)	//エラーメッセージ表示
	{
		MessageBox(GetMainWindowHandle(), path, IMAGE_LOAD_ERR_TITLE, MB_OK); return FALSE;
	}

	//幅と高さを取得
	GetGraphSize(grif->handle[0], &grif->width, &grif->height);

	return TRUE;
}

//########## 勇者の位置を初期化 ##########
VOID MY_INIT_YUSHA(VOID)
{
	yusha.x = MAP1_DIV_WIDTH * 0;	//マップのサイズを基準に決める
	yusha.y = MAP1_DIV_HEIGHT * 5;	//マップのサイズを基準に決める;
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

//########## グリフィンの位置を初期化 ##########
VOID MY_INIT_GRIF(VOID)
{
	grif.x = MAP1_DIV_WIDTH * 0;		//マップのサイズを基準に決める
	grif.y = MAP1_DIV_HEIGHT * 0;		//マップのサイズを基準に決める;
	grif.kind1 = GL_1;
	grif.kind2 = GFR_1;
	grif.speed = GRIF_MOVE_SPEED;	//移動速度

	//幅と高さを設定
	grif.width = grifChip1.width;
	grif.height = grifChip1.height;

	//当たり判定の調整
	grif.choseiX = +12;
	grif.choseiY = +12;
	grif.choseiWidth = -12;
	grif.choseiHeight = +6;

	grif.imgChangeCnt = 0;
	grif.imgChangeCntMAX = YUSHA_IMG_CHANGE_MAX;	//画像を変更するカウンタMAX

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
				yusha.x += yusha.speed;	//移動
				yusha.kind1++;			//次の画像にする
				yusha.imgChangeCnt = 0;	//変更カウンタ初期化
			}
		}
		else
		{
			
			yusha.kind1 = R_1;	//最初の画像にする
		}
		
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

//########## グリフィンを移動させる関数 ##########
VOID MY_MOVE_GRIF(VOID)
{
	//直前の位置を取得
	grif.oldx = grif.x;
	grif.oldy = grif.y;

	//強制的に下に重力を発生させる
	grif.y += GAME_GR;

	//当たり判定再計算
	MY_CALC_GRIF_COLL();

	//マップ２との当たり判定（下）
	MY_CHECK_MAP2_DOWN(&grif);

	//左に移動するとき
	if (MY_KEY_DOWN(KEY_INPUT_A) == TRUE)
	{
		grif.IsJump = FALSE;
		if (grif.kind1 >= L_1 && grif.kind1 < L_3)
		{
			//画像変更カウンタ
			if (grif.imgChangeCnt < grif.imgChangeCntMAX)
			{
				grif.imgChangeCnt++;
			}
			else //画像を変えるタイミングになったら
			{
				grif.kind1++;			//次の画像にする
				grif.imgChangeCnt = 0;	//変更カウンタ初期化
			}
		}
		else
		{
			grif.kind1 = L_1;	//最初の画像にする
		}
		grif.x -= grif.speed;
		grif.IsMoveLeft = TRUE;
	}
	else
	{
		grif.IsMoveLeft = FALSE;
	}

	//右に移動するとき
	if (MY_KEY_DOWN(KEY_INPUT_D) == TRUE)
	{
		grif.IsJump = FALSE;
		if (grif.kind1 >= R_1 && grif.kind1 < R_3)
		{
			//画像変更カウンタ
			if (grif.imgChangeCnt < grif.imgChangeCntMAX)
			{
				grif.imgChangeCnt++;
			}
			else //画像を変えるタイミングになったら
			{
				grif.kind1++;			//次の画像にする
				grif.imgChangeCnt = 0;	//変更カウンタ初期化
			}
		}
		else
		{
			grif.kind1 = R_1;	//最初の画像にする
		}
		grif.x += grif.speed;
		grif.IsMoveRight = TRUE;
	}
	else
	{
		grif.IsMoveRight = FALSE;
	}

	//何も押していないとき
	if (MY_KEY_DOWN(KEY_INPUT_W) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_D) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_S) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_A) == FALSE)
	{
		grif.imgChangeCnt = 0;		//変更カウンタ初期化

		//画像を止まっている画像にする
		if (grif.kind1 >= GF_1 && grif.kind1 <= GF_3) { grif.kind1 = GF_2; }
		else if (grif.kind1 >= GL_1 && grif.kind1 <= GL_3) { grif.kind1 = GL_2; }
		else if (grif.kind1 >= GR_1 && grif.kind1 <= GR_3) { grif.kind1 = GR_2; }
		else if (grif.kind1 >= GB_1 && grif.kind1 <= GB_3) { grif.kind1 = GB_2; }

		if (grif.kind2 >= GFF_1 && grif.kind2 <= GFF_3) { grif.kind2 = GFF_2; }
		else if (grif.kind2 >= GFL_1 && grif.kind2 <= GFL_3) { grif.kind2 = GFL_2; }
		else if (grif.kind2 >= GFR_1 && grif.kind2 <= GFR_3) { grif.kind2 = GFR_2; }
		else if (grif.kind2 >= GFB_1 && grif.kind2 <= GFB_3) { grif.kind2 = GFB_2; }
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

//########## グリフィンを描画する関数 ##########
VOID MY_DRAW_GRIF(VOID)
{
	//上下左右の移動のとき
	if (grif.IsJump == FALSE)	//上下左右の移動のとき
	{
		DrawGraph(grif.x, grif.y, grifChip1.handle[grif.kind1], TRUE);
	}
	else //ジャンプのとき
	{
		DrawGraph(grif.x, grif.y, grifChip2.handle[grif.kind2], TRUE);
	}

	return;
}

//########## プレイヤーの当たり判定を再計算する関数 ##########
VOID MY_CALC_GRIF_COLL(VOID)
{
	//（当たり判定を調整）
	grif.coll.left = grif.x + grif.choseiX;
	grif.coll.top = grif.y + grif.choseiY;
	grif.coll.right = grif.x + grif.width + grif.choseiWidth;
	grif.coll.bottom = grif.y + grif.height + grif.choseiHeight;
	return;
}