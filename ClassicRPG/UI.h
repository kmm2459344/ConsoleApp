//======================================
//	コマンドUI
//======================================
#ifndef __UI_H
#define __UI_H
#include "Command.h"
#include "TurnBattle.h"

// プレーヤのコマンド取得
Command GetPlayerCommand(TurnBattle* btl);
// 敵のコマンド取得
Command GetEnemyCommand();

#endif __UI_H#pragma once
