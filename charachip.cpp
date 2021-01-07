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
	yusha.kind1 = YD_1;
	yusha.kind2 = YLD_1;
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
	grif.choseiX = +16;
	grif.choseiY = +12;
	grif.choseiWidth = -16;
	grif.choseiHeight = +6;

	//最初は右向き
	grif.IsDirRight = TRUE;

	grif.imgChangeCnt = 0;
	grif.imgChangeCntMAX = GRIF_IMG_CHANGE_MAX;	//画像を変更するカウンタMAX

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

		//歩きのアニメーション
		MY_PLAY_ANIM_YUSHA_ARUKI(YU_1, YU_3);

		yusha.y -= yusha.speed;	//移動
	}

	//右に移動するとき
	if (MY_KEY_DOWN(KEY_INPUT_W) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_D) == TRUE
		&& MY_KEY_DOWN(KEY_INPUT_S) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_A) == FALSE)
	{
		yusha.IsMoveNaname = FALSE;	//斜め移動していない

		//歩きのアニメーション
		MY_PLAY_ANIM_YUSHA_ARUKI(YR_1, YR_3);

		yusha.x += yusha.speed;	//移動
	}

	//左に移動するとき
	if (MY_KEY_DOWN(KEY_INPUT_W) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_D) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_S) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_A) == TRUE)
	{
		yusha.IsMoveNaname = FALSE;	//斜め移動していない

		//歩きのアニメーション
		MY_PLAY_ANIM_YUSHA_ARUKI(YL_1, YL_3);

		yusha.x -= yusha.speed;	//移動
	}

	//下に移動するとき
	if (MY_KEY_DOWN(KEY_INPUT_W) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_D) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_S) == TRUE
		&& MY_KEY_DOWN(KEY_INPUT_A) == FALSE)
	{
		yusha.IsMoveNaname = FALSE;	//斜め移動していない

		//歩きのアニメーション
		MY_PLAY_ANIM_YUSHA_ARUKI(YD_1, YD_3);

		yusha.y += yusha.speed;	//移動
	}

	//下左に移動するとき
	if (MY_KEY_DOWN(KEY_INPUT_W) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_D) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_S) == TRUE
		&& MY_KEY_DOWN(KEY_INPUT_A) == TRUE)
	{
		yusha.IsMoveNaname = TRUE;	//斜め移動している

		//斜めのアニメーション
		MY_PLAY_ANIM_YUSHA_NANAME(YLD_1, YLD_3);

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

		//斜めのアニメーション
		MY_PLAY_ANIM_YUSHA_NANAME(YLU_1, YLU_3);

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

		//斜めのアニメーション
		MY_PLAY_ANIM_YUSHA_NANAME(YRD_1, YRD_3);

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

		//斜めのアニメーション
		MY_PLAY_ANIM_YUSHA_NANAME(YRU_1, YRU_3);

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
		if (yusha.kind1 >= YU_1 && yusha.kind1 <= YU_3) { yusha.kind1 = YU_2; }
		else if (yusha.kind1 >= YR_1 && yusha.kind1 <= YR_3) { yusha.kind1 = YR_2; }
		else if (yusha.kind1 >= YL_1 && yusha.kind1 <= YL_3) { yusha.kind1 = YL_2; }
		else if (yusha.kind1 >= YD_1 && yusha.kind1 <= YD_3) { yusha.kind1 = YD_2; }

		if (yusha.kind2 >= YLD_1 && yusha.kind2 <= YLD_3) { yusha.kind2 = YLD_2; }
		else if (yusha.kind2 >= YLU_1 && yusha.kind2 <= YLU_3) { yusha.kind2 = YLU_2; }
		else if (yusha.kind2 >= YRD_1 && yusha.kind2 <= YRD_3) { yusha.kind2 = YRD_2; }
		else if (yusha.kind2 >= YRU_1 && yusha.kind2 <= YRU_3) { yusha.kind2 = YRU_2; }
	}
	return;
}

//########## 勇者の歩くアニメーション関数 ##########
//引数：MIN：アニメーションの開始番号
//引数：MAX：アニメーションの終了番号
VOID MY_PLAY_ANIM_YUSHA_ARUKI(YUSHA_KIND_1 Y_MIN, YUSHA_KIND_1 Y_MAX)
{
	if (yusha.kind1 >= Y_MIN && yusha.kind1 <= Y_MAX)
	{
		if (yusha.imgChangeCnt == 0)	//すぐに画像を変更
		{
			if (yusha.kind1 < Y_MAX) { yusha.kind1++; }		//次の画像にする
			else { yusha.kind1 = Y_MIN; }					//最初の画像にする
			yusha.imgChangeCnt++;
		}
		else if (yusha.imgChangeCnt < yusha.imgChangeCntMAX)	//カウンタアップ
		{
			yusha.imgChangeCnt++;
		}
		else if (yusha.imgChangeCnt >= yusha.imgChangeCntMAX)	//カウンタ初期化
		{
			yusha.imgChangeCnt = 0;	//変更カウンタ初期化
		}
	}
	else
	{
		yusha.kind1 = Y_MIN;	//最初の画像にする
	}
}

//########## 勇者の斜めのアニメーション関数 ##########
//引数：MIN：アニメーションの開始番号
//引数：MAX：アニメーションの終了番号
VOID MY_PLAY_ANIM_YUSHA_NANAME(YUSHA_KIND_2 Y_MIN, YUSHA_KIND_2 Y_MAX)
{
	if (yusha.kind2 >= Y_MIN && yusha.kind2 <= Y_MAX)
	{
		if (yusha.imgChangeCnt == 0)	//すぐに画像を変更
		{
			if (yusha.kind2 < Y_MAX) { yusha.kind2++; }		//次の画像にする
			else { yusha.kind2 = Y_MIN; }					//最初の画像にする
			yusha.imgChangeCnt++;
		}
		else if (yusha.imgChangeCnt < yusha.imgChangeCntMAX)	//カウンタアップ
		{
			yusha.imgChangeCnt++;
		}
		else if (yusha.imgChangeCnt >= yusha.imgChangeCntMAX)	//カウンタ初期化
		{
			yusha.imgChangeCnt = 0;	//変更カウンタ初期化
		}
	}
	else
	{
		yusha.kind2 = Y_MIN;	//最初の画像にする
	}
}

//########## グリフィンを移動させる関数 ##########
VOID MY_MOVE_GRIF(VOID)
{
	//直前の位置を取得
	grif.oldx = grif.x;
	grif.oldy = grif.y;

	//強制的に下に重力を発生させる
	grif.y += GAME_GR;

	//マップ上も移動
	grif.mapY += GAME_GR;

	//マップ２と当たり判定（ジャンプ）
	MY_CHECK_MAP2_JUMP(&grif);

	//左に行く処理
	MY_PLAY_MOVE_LEFT();

	//マップとプレイヤーの当たり判定(左)をする関数
	MY_CHECK_MAP2_LEFT(&grif);

	//右に行く処理
	MY_PLAY_MOVE_RIGHT();

	//マップとプレイヤーの当たり判定(右)をする関数
	MY_CHECK_MAP2_RIGHT(&grif);

	//ジャンプの処理
	MY_PLAY_MOVE_JUMP();

	//マップ２との当たり判定（下）
	MY_CHECK_MAP2_DOWN(&grif);

	//何も押していないとき
	if (MY_KEY_DOWN(KEY_INPUT_W) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_D) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_S) == FALSE
		&& MY_KEY_DOWN(KEY_INPUT_A) == FALSE)
	{
		//ジャンプしていないときは
		if (grif.IsJump == FALSE)
		{
			grif.imgChangeCnt = 0;	//アニメーションを止める

			//画像を止まっている画像にする
			if (grif.kind1 >= GF_1 && grif.kind1 <= GF_3) { grif.kind1 = GF_2; }
			else if (grif.kind1 >= GL_1 && grif.kind1 <= GL_3) { grif.kind1 = GL_2; }
			else if (grif.kind1 >= GR_1 && grif.kind1 <= GR_3) { grif.kind1 = GR_2; }
			else if (grif.kind1 >= GB_1 && grif.kind1 <= GB_3) { grif.kind1 = GB_2; }
		}
	}

	//当たり判定再計算
	MY_CALC_GRIF_COLL();

	//コインゲット処理
	MY_GET_MAP2_COIN(grif);

	//ドアに触れたときの処理
	MY_TOUCH_MAP2_DOOR(grif);

	return;
}

//ドアに触れたときの処理
VOID MY_TOUCH_MAP2_DOOR(GRIF grif)
{
	switch (MY_CHECK_MAP2_DOOR(grif))
	{
	case -1:
		//何もしない

		break;
	case 0:
		//ステージを選択
		GameStage = GAME_STAGE_RPG;

		break;
	case 1:
		//エンド画面へ
		GameScene = GAME_SCENE_END;

		break;
	}

	return;
}

//左に行く処理
VOID MY_PLAY_MOVE_LEFT(VOID)
{
	//左に移動するとき
	if (MY_KEY_DOWN(KEY_INPUT_A) == TRUE)
	{
		//左を向いている
		grif.IsDirRight = FALSE;
		grif.IsDirLeft = TRUE;

		//左へ移動
		grif.x -= grif.speed;
		
		//マップ上も移動
		grif.mapX -= grif.speed;
	}

	//左を向いているとき
	if (grif.IsDirLeft == TRUE)
	{
		//ジャンプしていないときは
		if (grif.IsJump == FALSE)
		{
			//歩くアニメーションで動かす
			MY_PLAY_ANIM_ARUKI(GL_1, GL_3);
		}
		else if (grif.IsJump == TRUE)	//ジャンプしているとき
		{
			//羽ばたきのアニメーションで動かす
			MY_PLAY_ANIM_HABATAKI(GFL_1, GFL_3);
		}
	}

	return;
}

//右に行く処理
VOID MY_PLAY_MOVE_RIGHT(VOID)
{
	//右に移動するとき
	if (MY_KEY_DOWN(KEY_INPUT_D) == TRUE)
	{
		//右を向いている
		grif.IsDirRight = TRUE;
		grif.IsDirLeft = FALSE;

		//右へ移動
		grif.x += grif.speed;

		//マップ上も移動
		grif.mapX += grif.speed;
	}

	//右を向いているとき
	if (grif.IsDirRight == TRUE)
	{
		//ジャンプしていないときは
		if (grif.IsJump == FALSE)
		{
			//歩くアニメーションで動かす
			MY_PLAY_ANIM_ARUKI(GR_1, GR_3);
		}
		else if (grif.IsJump == TRUE)	//ジャンプしているとき
		{
			//羽ばたきのアニメーションで動かす
			MY_PLAY_ANIM_HABATAKI(GFR_1, GFR_3);
		}
	}

	return;
}

//ジャンプの処理
VOID MY_PLAY_MOVE_JUMP(VOID)
{
	//上にジャンプするとき
	if (MY_KEY_DOWN(KEY_INPUT_W) == TRUE)
	{
		//地面にあたっているとき
		if (MY_CHECK_GRIF_GROUND(grif) == TRUE)
		{
			//ジャンプしていなければ
			if (grif.IsJump == FALSE)
			{
				grif.IsJump = TRUE;					//ジャンプする
				grif.BeforeJumpY = grif.y;			//ジャンプする前のY位置
				grif.JumpPowerMax = GRIF_JUMP_POWER;//ジャンプ力設定
				grif.JumpTimeCnt = 0;				//ジャンプできる時間
			}
		}
	}

	//ジャンプしているとき
	if (grif.IsJump == TRUE)
	{
		//ジャンプできる力が残っていれば
		if (grif.JumpPowerMax > 0)
		{
			//画面内にいれば、
			if (grif.y - GAME_GR + grif.JumpPowerMax >= 0)
			{
				//重力に抵抗しないと、飛べない・・・
				grif.y -= GAME_GR + grif.JumpPowerMax;

				//マップ上も移動
				grif.mapY -= GAME_GR + grif.JumpPowerMax;
			}
			else
			{
				//画面外なら重力に従う
				grif.y -= GAME_GR;

				//マップ上も移動
				grif.mapY -= GAME_GR;
			}

			//10フレームごとに・・・
			if (grif.JumpTimeCnt % 10 == 0)
			{
				//ジャンプ力を失っていく・・・
				grif.JumpPowerMax -= 2;
			}

			//ジャンプしている時間カウントアップ
			grif.JumpTimeCnt++;
		}
		else
		{
			grif.IsJump = FALSE;
		}
	}

	return;
}

//########## 歩くアニメーション関数 ##########
//引数：MIN：アニメーションの開始番号
//引数：MAX：アニメーションの終了番号
VOID MY_PLAY_ANIM_ARUKI(GRIF_KIND_1 G_MIN, GRIF_KIND_1 G_MAX)
{
	if (grif.kind1 >= G_MIN && grif.kind1 <= G_MAX)
	{
		if (grif.imgChangeCnt == 0)	//すぐに画像を変更
		{
			if (grif.kind1 < G_MAX) { grif.kind1++; }		//次の画像にする
			else { grif.kind1 = G_MIN; }					//最初の画像にする
			grif.imgChangeCnt++;
		}
		else if (grif.imgChangeCnt < grif.imgChangeCntMAX)	//カウンタアップ
		{
			grif.imgChangeCnt++;
		}
		else if (grif.imgChangeCnt >= grif.imgChangeCntMAX)	//カウンタ初期化
		{
			grif.imgChangeCnt = 0;	//変更カウンタ初期化
		}
	}
	else
	{
		grif.kind1 = G_MIN;	//最初の画像にする
	}
}

//########## 羽ばたきのアニメーション関数 ##########
//引数：MIN：アニメーションの開始番号
//引数：MAX：アニメーションの終了番号
VOID MY_PLAY_ANIM_HABATAKI(GRIF_KIND_2 GF_MIN, GRIF_KIND_2 GF_MAX)
{
	if (grif.kind2 >= GF_MIN && grif.kind2 <= GF_MAX)
	{
		if (grif.imgChangeCnt == 0)	//すぐに画像を変更
		{
			if (grif.kind2 < GF_MAX) { grif.kind2++; }		//次の画像にする
			else { grif.kind2 = GF_MIN; }					//最初の画像にする
			grif.imgChangeCnt++;
		}
		else if (grif.imgChangeCnt < grif.imgChangeCntMAX)	//カウンタアップ
		{
			grif.imgChangeCnt++;
		}
		else if (grif.imgChangeCnt >= grif.imgChangeCntMAX)	//カウンタ初期化
		{
			grif.imgChangeCnt = 0;	//変更カウンタ初期化
		}
	}
	else
	{
		grif.kind2 = GF_MIN;	//最初の画像にする
	}
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