/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//ゲーム全体で使用するモノをまとめています

//重複インクルード禁止
#pragma once

//エラー抑制
#define _CRT_SECURE_NO_WARNINGS

//ヘッダーファイル読み込み
#include "DxLib.h"
#include "math.h"

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


#define GAME_GR	5	//重力

//列挙型
enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
};	//ゲームのシーン

enum GAME_STAGE {
	GAME_STAGE_RPG,
	GAME_STAGE_ACT
};	//ゲームのステージ

//########## 外部のプロトタイプ宣言 ##########
extern VOID MY_FPS_UPDATE(VOID);			//FPS値を計測、更新する
extern VOID MY_FPS_DRAW(VOID);				//FPS値を描画する
extern VOID MY_FPS_WAIT(VOID);				//FPS値を計測し、待つ

extern VOID MY_ALL_KEYDOWN_UPDATE(VOID);				//キーの入力状態を更新する
extern BOOL MY_KEY_DOWN(int KEY_INPUT_);				//キーを押しているか、キーコードで判断する
extern BOOL MY_KEY_UP(int KEY_INPUT_);					//キーを押し上げたか、キーコードで判断する
extern BOOL MY_KEYDOWN_KEEP(int KEY_INPUT_, int msec);	//キーを押し続けているか、キーコードで判断する
extern BOOL MY_KEY_PUSH(int KEY_INPUT_);				//キーをプッシュしたか、キーコードで判断する

extern BOOL MY_CHECK_RECT_COLL(RECT a, RECT b);	//領域の当たり判定をする関数

//########## 外部のグローバル変数 ##########

//FPS関連
extern int StartTimeFps;				//測定開始時刻
extern int CountFps;					//カウンタ
extern float CalcFps;					//計算結果
extern int SampleNumFps;				//平均を取るサンプル数

//キーボードの入力を取得
extern char AllKeyState[256];			//すべてのキーの状態が入る
extern char OldAllKeyState[256];		//すべてのキーの状態(直前)が入る

//ゲーム関連
extern GAME_SCENE GameScene;			//ゲームのシーンを管理
extern GAME_STAGE GameStage;			//ゲームのステージを管理
