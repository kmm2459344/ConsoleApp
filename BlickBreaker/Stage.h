//======================================
//	ブロックくずし ステージ
//======================================
#ifndef __STAGE_H
#define __STAGE_H

const int FIELD_WIDTH = 14;
const int FIELD_HEIGHT = FIELD_WIDTH * 2;
const int PADDLE_WIDTH = 4;

// フィルード内容
typedef enum {
	FIELD_NONE,   // 空間
	FIELD_BLOCK,  // ブロック
	FIELD_OUT,    // (外側)
} Field;

// ステージ構造体
typedef struct {
	int ballX;        // ボールの位置
	int ballY;
	int ballVelocityX; // ボールの速度
	int ballVelocityY;
	int paddleX;       // パトル(左端)の位置
	int paddleY;
	Field field[FIELD_HEIGHT][FIELD_WIDTH];
} Stage;

// 描画モード
typedef enum {
	DM_READY,
	DM_GAME,
	DM_PAUSE,
	DM_CLEAR,
} DrawMode;

// 初期化
void InitializeStage(Stage* stage);
// ボール位置をリセット
void ResetBall(Stage* stage);
// スクリーン描画
void DrawScreen(Stage* stage, DrawMode mode);
// ボールを失ったか?
bool IsBallMiss(Stage* stage);
// 面クリアしたか?
bool IsClear(Stage* stage);
// ボール移動
void MoveBall(Stage* stage);
// パドル移動
void MovePaddle(Stage* stage, int addX);
// フィールドのセッター
void SetField(Stage* stage, int x, int y, Field value);
// フィールドのゲッター
Field GetField(Stage* stage, int x, int y);

#endif // __STAGE_H
#pragma once
