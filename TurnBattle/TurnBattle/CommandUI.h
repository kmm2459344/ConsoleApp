//======================================
//	�R�}���hUI
//======================================
// �������ɃC���N���[�h�K�[�h(�J�n)���L�����Ă��������B
#ifndef INCLUDED_CommandUI
#define INCLUDED_CommandUI

#include "Command.h"
#include "TurnBattle.h"

// �v���[���̃R�}���h�擾
Command GetPlayerCommand(TurnBattle* btl);
// �G�̃R�}���h�擾
Command GetEnemyCommand();

// �������ɃC���N���[�h�K�[�h(�I��)���L�����Ă��������B
#endif