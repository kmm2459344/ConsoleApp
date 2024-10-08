//======================================
//	コマンドUI
//======================================
// ★ここにインクルードガード(開始)を記入してください。
#ifndef INCLUDED_CommandUI
#define INCLUDED_CommandUI

#include "Command.h"
#include "TurnBattle.h"

// プレーヤのコマンド取得
Command GetPlayerCommand(TurnBattle* btl);
// 敵のコマンド取得
Command GetEnemyCommand();

// ★ここにインクルードガード(終了)を記入してください。
#endif