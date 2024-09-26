//======================================
//	マインスィーパー セル
//======================================
#include "Cell.h"
// セットフップ(初期化)状態にする
void SetupCell(Cell* cell)
{
	// ★ここをコーディングしてください
	// cellのbombを false にセットします
	// cellのhideを true にセットします
	// cellのflagを false にセットします
	// cellのadjacentBombsを 0 にセットします
	cell->bomb = false;
	cell->hide = true;
	cell->flag = false;
	cell->adjacentBombs = 0;
}
// bombか?
bool IsBomb(Cell* cell)
{
	// ★ここをコーディングしてください
	// cellのbombを返します
	return cell->bomb;
}
// bomb をセット
void SetBomb(Cell* cell, bool value)
{
	// ★ここをコーディングしてください
	// cellのbombにvalueを代入します
	cell->bomb = value;
}
// hideか?
bool IsHide(Cell* cell)
{
	// ★ここをコーディングしてください
	// cellのhideを返します
	return cell->hide;
}
// hide をセット
void SetHide(Cell* cell, bool value)
{
	// ★ここをコーディングしてください
	// cellのhideにvalueを代入します
	cell->hide = value;
}
// flagか?
bool IsFlag(Cell* cell)
{
	// ★ここをコーディングしてください
	// cellのflagを返します
	return cell->flag;
}
// flag を反転
void FlipFlag(Cell* cell)
{
	// ★ここをコーディングしてください
	// cellのflagを反転します
	cell->flag = !cell->flag;
}
// adjacentBombsを取得
int GetAdjacentBombs(Cell* cell)
{
	// ★ここをコーディングしてください
	// cellのadjacentBombsを返します
	return cell->adjacentBombs;
}
// adjacentBombsをセット
void SetAdjacentBombs(Cell* cell, int value)
{
	// ★ここをコーディングしてください
	// cellのadjacentBombsにvalueを代入します
	cell->adjacentBombs = value;
}
// 開示する
void OpenCell(Cell* cell)
{
	// ★ここをコーディングしてください
	// cellのhideにfalseを入れます
	// cellのflagにfalseを入れます
	cell->hide = false;
	cell->flag = false;
}