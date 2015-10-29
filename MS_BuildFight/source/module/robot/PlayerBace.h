//=============================================================================
//
// MS_BuildFight [CPlayerBace.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CPLAYERBACE_H_
#define _CPLAYERBACE_H_
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "PlayerM.h"
//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	VALUE_MOVE_PLAYER		(2.0f)				// �v���C���[�̈ړ���
#define	VALUE_TURBO_PLAYER		(4.0f)				// �v���C���[�̈ړ���
#define	VALUE_MOVE_PLAYER_AIR	(2.0f)				// �v���C���[�̈ړ���(�W�����v��)
#define	RATE_MOVE_PLAYER		(0.20f)				// �ړ������W��
#define	VALUE_ROTATE_PLAYER		(D3DX_PI * 0.05f)	// ��]���x
#define	RATE_ROTATE_PLAYER		(0.20f)				// ��]�����W��
#define VALUE_JUMP				(6.65f)				// �W�����v�l

class CInputKeyboard;

void PlayerMove(int type,bool jump,bool over,CInputKeyboard *pkey,D3DXVECTOR3* move,D3DXVECTOR3* rot,D3DXVECTOR3* cam);
void PlayerMoveReplay(int type,bool jump,bool over,CInputKeyboard *pkey,D3DXVECTOR3* move,D3DXVECTOR3* rot,D3DXVECTOR3* cam);

#endif