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
// インクルードファイル
//*****************************************************************************
#include "PlayerM.h"
//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VALUE_MOVE_PLAYER		(2.0f)				// プレイヤーの移動量
#define	VALUE_TURBO_PLAYER		(4.0f)				// プレイヤーの移動量
#define	VALUE_MOVE_PLAYER_AIR	(2.0f)				// プレイヤーの移動量(ジャンプ中)
#define	RATE_MOVE_PLAYER		(0.20f)				// 移動慣性係数
#define	VALUE_ROTATE_PLAYER		(D3DX_PI * 0.05f)	// 回転速度
#define	RATE_ROTATE_PLAYER		(0.20f)				// 回転慣性係数
#define VALUE_JUMP				(6.65f)				// ジャンプ値

class CInputKeyboard;

void PlayerMove(int type,bool jump,bool over,CInputKeyboard *pkey,D3DXVECTOR3* move,D3DXVECTOR3* rot,D3DXVECTOR3* cam);
void PlayerMoveReplay(int type,bool jump,bool over,CInputKeyboard *pkey,D3DXVECTOR3* move,D3DXVECTOR3* rot,D3DXVECTOR3* cam);

#endif