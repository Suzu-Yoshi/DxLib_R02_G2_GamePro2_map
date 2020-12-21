/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//ゲーム全体で使用するモノをまとめています

//重複インクルード禁止
#pragma once

//ヘッダーファイル読み込み
#include "DxLib.h"

//マクロ定義
#define GAME_WIDTH			800	//画面の横の大きさ
#define GAME_HEIGHT			600	//画面の縦の大きさ
#define GAME_COLOR			32	//画面のカラービット

#define GAME_WINDOW_BAR		0				//タイトルバーはデフォルトにする
#define GAME_WINDOW_NAME	"GAME TITLE"	//ウィンドウのタイトル
#define GAME_FPS			60				//FPSの数値	

//パスの長さ
#define PATH_MAX			255	//255文字まで
#define NAME_MAX			255	//255文字まで

//エラーメッセージ
#define IMAGE_LOAD_ERR_TITLE	TEXT("画像読み込みエラー")

//終了ダイアログ用
#define MOUSE_R_CLICK_TITLE		TEXT("ゲーム中断")
#define MOUSE_R_CLICK_CAPTION	TEXT("ゲームを中断し、タイトル画面に戻りますか？")

//列挙型
enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
};	//ゲームのシーン