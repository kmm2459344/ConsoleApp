//======================================
//	マインスィーパー ステージ
//======================================
#include "Stage.h"
#include "Cell.h"
#include "Utility.h"
#include <stdio.h>  // printf()
#include <assert.h>

// 関数プロトタイプ
static void SetupField(Stage* stage);
static bool IsCursorPosition(Stage* stage, int x, int y);
static void UpdateField(Stage* stage);
static void OpenFieldAll(Stage* stage);
static Cell* GetCursorCell(Stage* stage);
static bool IsInField(int x, int y);
static bool IsClear(Stage* stage);
static void Beep();

// ステージ初期化
void InitializeStage(Stage* stage)
{
	SetupField(stage);
	UpdateField(stage);
	stage->cursorX = 0;
	stage->cursorY = 0;
	stage->isExplosion = false;
	stage->isClear = false;
}
// フィールドのセットアップ
static void SetupField(Stage* stage)
{
	// 全部リセット
	for (int y = 0; y < FIELD_HEIGHT; y++) {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			// ★ここをコーディングしてください
			// (x,y) のセルを取得して SetupCell()を呼びます
			Cell* cell = GetFieldCell(stage, x, y);
			SetupCell(cell);
		}
	}
	// ランダムにBOMB配置
	int count = BOMB_COUNT;
	while (count > 0) {
		// ここをコーディングしてください。
		// 0～FIELD_WIDTH-1 の乱数を x
		// 0～FIELD_HEIGHT-1 の乱数を y　として
		// (x,y)のセルを取得して、ボム未設定なら
		// SetBomb()を呼びます。countも-1します。
		int x = GetRand(FIELD_WIDTH);
		int y = GetRand(FIELD_HEIGHT);
		Cell* cell = GetFieldCell(stage, x, y);
		if (IsBomb(cell) == false) {
			SetBomb(cell, true);
			count--;
		}

	}
}
// 隣接ボムの数を更新
static void UpdateField(Stage* stage)
{
	for (int y = 0; y < FIELD_HEIGHT; y++) {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			// ★ここをコーディングしてください
			// (x,y)のセルを取得して、
			// (x,y)のGetAdacentBomsCount()の値を
			// SetAdjacentBomc()で設定します
			Cell* cell = GetFieldCell(stage, x, y);
			int n = GetAdjacentBombsCount(stage, x, y);
			SetAdjacentBombs(cell, n);
		}
	}
}
// フィールドを開示する
static void OpenFieldAll(Stage* stage)
{
	for (int y = 0; y < FIELD_HEIGHT; y++) {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			// ★ここをコーディングしてください
			// (x,y)のセルを取得して
			// OpemCell()を呼びます
			Cell* cell = GetFieldCell(stage, x, y);
			OpenCell(cell);
		}
	}
}
// 隣接ボムの数を取得
int GetAdjacentBombsCount(Stage* stage, int x, int y)
{
	int count = 0;
	for (int dy = -1; dy <= 1; dy++) {
		for (int dx = -1; dx <= 1; dx++) {
			if (dx == 0 && dy == 0) {
				continue;
			}
			// ★ここをコーディングしてください
			// (x+dx,y+dy)のセルを取得し
			// nullptrでないことを確認して、IsBomb()だったらカウントします
			Cell* cell = GetFieldCell(stage, x + dx, y + dy);
			if (cell != nullptr && IsBomb(cell)) {
				count++;
			}
		}
	}
	return count;
}
// 自動開示
void AutoEraseMines(Stage* stage, int x, int y)
{
	// ★ここをコーディングしてください。
	// (x,y)のセルを取得して、
	// nullptrか、IsBomb()か、IsHide()==false なら
	// 何もしないでreturnします
	// 
	Cell* cell = GetFieldCell(stage, x, y);
	if (cell == nullptr || IsBomb(cell) || IsHide(cell) == false) {
		return;
	}
	SetHide(cell, false);
	// ★ここをコーディングしてください。
	// セルのGetAdjacentBombs()が0 のとき、
	// (x,y)周辺をAutoEraseMines()します(再帰呼び出し)
	// 
	if (GetAdjacentBombs(cell) == 0) {
		for (int dy = -1; dy <= 1; dy++) {
			for (int dx = -1; dx <= 1; dx++) {
				if (dx == 0 && dy == 0)
				{
					continue;
				}
				AutoEraseMines(stage, x + dx, y + dy);
			}
			
		}
	}
}

const char* AA_CURSOR = "＠";  // カーソル
const char* AA_EXPLOSION = "※"; // 爆発
const char* AA_FLAG = "▲";  // フラグ
const char* AA_BOMB = "●";  // 爆弾
const char* AA_MINE = "■";  // 未開放
const char* AA_NUMBERS[] = {   // 開放済
	"・",
	"１",
	"２",
	"３",
	"４",
	"５",
	"６",
	"７",
	"８",
	"９",
};
// スクリーン描画
void DrawScreen(Stage* stage)
{
	int hideCount = 0;
	int bombCount = 0;
	int flagCount = 0;

	ClearScreen();
	for (int y = 0; y < FIELD_HEIGHT; y++) {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			Cell* cell = GetFieldCell(stage, x, y);
			if (IsCursorPosition(stage, x, y) && stage->isClear == false) {
				// ★ここをコーディングしてください
				// 爆発時にAA_EXPLOSION をそれ以外は AA_CURSORを表示します
			}
			else {
				if (IsFlag(cell)) {
					// ★ここをコーディングしてください
					// AA_FLAGを表示します
					printf(AA_FLAG);
				}
				else if (IsHide(cell)) {
					// ★ここをコーディングしてください
					// AA_MINEを表示します
					printf(AA_MINE);
				}
				else if (IsBomb(cell)) {
					// ★ここをコーディングしてください
					// AA_BOMBを表示します
					printf(AA_BOMB);
				}
				else {
					int n = GetAdjacentBombs(cell);
					assert(0 <= n && n <= 8);
					// ★ここをコーディングしてください
					// AA_NUMBERS[n]を表示します
					printf(AA_NUMBERS[n]);
				}
			}
			if (IsBomb(cell)) bombCount++;
			if (IsHide(cell)) hideCount++;
			if (IsFlag(cell)) flagCount++;
		}
		putchar('\n');
	}
	putchar('\n');
	// ★ここをコーディングしてください
	// "フラグ／ボム　xxx/xxx"(フラグの数とボムの数) を表示します
	// "解放          xxx/xxx"(解放済の数と開放すべき数)を表示します
	printf("フラグ/ボム:%3d/3d\n", flagCount, bombCount);
	int open1 = FIELD_WIDTH * FIELD_HEIGHT - hideCount;
	int open2 = FIELD_WIDTH * FIELD_HEIGHT - bombCount;
	printf("解放　　　:%3d/%3d\n", open1, open2);
}
// カーソル位置か?
static bool IsCursorPosition(Stage* stage, int x, int y)
{
	// ★ここをコーディングしてください
	// (x,y)がカーソル位置か調べて、真偽を返します
	return x == stage->cursorX && y == stage->cursorY;
}

// カーソル移動
void MoveCursor(Stage* stage, int addX, int addY)
{
	// ★ここをコーディングしてください
	// カーソル位置に addX,addY を加算して
	// その座標がField内にあれば、カーソル位置を更新します
	int x = stage->cursorX + addX;
	int y = stage->cursorY + addY;
	if (IsInField(x, y)) {
		stage->cursorX = x;
		stage->cursorY = y;
	}
}
// カーソルのflag反転
void FlipCursorFlag(Stage* stage)
{
	// ★ここをコーディングしてください
	// GetCursoirCell()でカーソル位置のセルを取得して
	// FlipCell()を呼びます
	Cell* cell = GetCursorCell(stage);
	FlipFlag(cell);
}
// カーソルのセルを開放(終了フラグを返す)
bool OpenCursorCell(Stage* stage)
{
	Cell* cell = GetCursorCell(stage);
	SetHide(cell, false);
	if (IsBomb(cell)) {
		Beep();
		stage->isExplosion = true;
		OpenFieldAll(stage);
	}
	else if (IsClear(stage)) {
		Beep();
		stage->isClear = true;
	}
	// 自動開示
	for (int dy = -1; dy <= 1; dy++) {
		for (int dx = -1; dx <= 1; dx++) {
			if (dx == 0 && dy == 0) {
				continue;
			}
			int x = stage->cursorX + dx;
			int y = stage->cursorY + dy;
			AutoEraseMines(stage, x, y);
		}
	}
	return stage->isExplosion || stage->isClear;
}
// クリアか?
static bool IsClear(Stage* stage)
{
	for (int y = 0; y < FIELD_HEIGHT; y++) {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			// ★ここをコーディングしてください
			// (x,y)のセルを取得して
			// IsBomb()==false かつ IsHide()なら、falseを返します
			// 
			// ボムでないところが開いてないなら、非クリア
			Cell* cell = GetFieldCell(stage, x, y);
			if (IsBomb(cell) == false && IsHide(cell)) {
				return false;
			}
		}
	}
	return true;
}
// カーソル位置のセルを取得
static Cell* GetCursorCell(Stage* stage)
{
	// ★ここをコーディングしてください
	// カーソル位置のcellを取得して返します
	return GetFieldCell(stage, stage->cursorY, stage->cursorX);
}
// フィールドのセル取得
Cell* GetFieldCell(Stage* stage, int x, int y)
{
	// ★ここをコーディングしてください
	// (x,y)がField内を確認して field[y][x]のアドレスを返します
	// field外なら nullptr を返します
	if (IsInField(x, y)) {
		return &stage->field[y][x];
	}
}
// フィールド内か?
bool IsInField(int x, int y)
{
	return 0 <= x && x < FIELD_WIDTH
		&& 0 <= y && y < FIELD_HEIGHT;
}
// 勝った?
bool IsWin(Stage* stage)
{
	// ★ここをコーディングしてください。
	// stageのisClearを返します
	return stage->isClear;
}
// 負けた?
bool IsLose(Stage* stage)
{
	// ★ここをコーディングしてください。
	// stageのisExplosionを返します
	return stage->isExplosion;
}
// ビープ音を鳴らす
static void Beep()
{
	// ★ここをコーディングしてください。
	// '\a' を表示します
	putchar('\a');
}