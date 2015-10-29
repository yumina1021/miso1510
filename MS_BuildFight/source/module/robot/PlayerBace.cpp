//=============================================================================
//
// MS_BuildFight [CPlayerBace.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#include "PlayerBace.h"
#include "../../administer/Input.h"
//=============================================================================
// Player移動処理
//=============================================================================
void PlayerMove(int type,bool jump,bool over,CInputKeyboard *pkey,D3DXVECTOR3* move,D3DXVECTOR3* rot,D3DXVECTOR3* cam)
{
	if(!jump)
	{
		if(pkey->GetKeyPress(DIK_T)||over)
		{
			//移動
			if(pkey->GetKeyPress(DIK_A))
			{
				move->x-=sinf(cam->y+90*(D3DX_PI/180))*VALUE_TURBO_PLAYER;
				move->z-=cosf(cam->y+90*(D3DX_PI/180))*VALUE_TURBO_PLAYER;
				rot->y= cam->y-270*(D3DX_PI/180);
			}
			if(pkey->GetKeyPress(DIK_D))
			{
				move->x+=sinf(cam->y+90*(D3DX_PI/180))*VALUE_TURBO_PLAYER;
				move->z+=cosf(cam->y+90*(D3DX_PI/180))*VALUE_TURBO_PLAYER;
				rot->y= cam->y+-90*(D3DX_PI/180);
			}
			if(pkey->GetKeyPress(DIK_W))
			{
				move->x+=sinf(cam->y)*VALUE_TURBO_PLAYER;
				move->z+=cosf(cam->y)*VALUE_TURBO_PLAYER;
				rot->y= cam->y-180*(D3DX_PI/180);
			}
			if(pkey->GetKeyPress(DIK_S))
			{
				move->x-=sinf(cam->y)*VALUE_TURBO_PLAYER;
				move->z-=cosf(cam->y)*VALUE_TURBO_PLAYER;
				rot->y= cam->y-0*(D3DX_PI/180);
			}
		}else
		{
			//移動
			if(pkey->GetKeyPress(DIK_A))
			{
				move->x-=sinf(cam->y+90*(D3DX_PI/180))*VALUE_MOVE_PLAYER;
				move->z-=cosf(cam->y+90*(D3DX_PI/180))*VALUE_MOVE_PLAYER;
				rot->y= cam->y-270*(D3DX_PI/180);
			}
			if(pkey->GetKeyPress(DIK_D))
			{
				move->x+=sinf(cam->y+90*(D3DX_PI/180))*VALUE_MOVE_PLAYER;
				move->z+=cosf(cam->y+90*(D3DX_PI/180))*VALUE_MOVE_PLAYER;
				rot->y= cam->y+-90*(D3DX_PI/180);
			}
			if(pkey->GetKeyPress(DIK_W))
			{
				move->x+=sinf(cam->y)*VALUE_MOVE_PLAYER;
				move->z+=cosf(cam->y)*VALUE_MOVE_PLAYER;
				rot->y= cam->y-180*(D3DX_PI/180);
			}
			if(pkey->GetKeyPress(DIK_S))
			{
				move->x-=sinf(cam->y)*VALUE_MOVE_PLAYER;
				move->z-=cosf(cam->y)*VALUE_MOVE_PLAYER;
				rot->y= cam->y-0*(D3DX_PI/180);
			}
		}
		

		//斜めの場合向きの変更
		if(pkey->GetKeyPress(DIK_A)&&(pkey->GetKeyPress(DIK_S)))
		{
			rot->y = cam->y-315*(D3DX_PI/180);
		}
		else if(pkey->GetKeyPress(DIK_D)&&(pkey->GetKeyPress(DIK_S)))
		{
			rot->y = cam->y-45*(D3DX_PI/180);
		}
		if(pkey->GetKeyPress(DIK_A)&&(pkey->GetKeyPress(DIK_W)))
		{
			rot->y = cam->y-225*(D3DX_PI/180);
		}
		else if(pkey->GetKeyPress(DIK_D)&&(pkey->GetKeyPress(DIK_W)))
		{
			rot->y = cam->y-135*(D3DX_PI/180);
		}
	}else
	{
		if(pkey->GetKeyPress(DIK_T))
		{
			//移動
			if(pkey->GetKeyPress(DIK_A))
			{
				move->x-=sinf(cam->y+90*(D3DX_PI/180))*VALUE_TURBO_PLAYER;
				move->z-=cosf(cam->y+90*(D3DX_PI/180))*VALUE_TURBO_PLAYER;
				rot->y= cam->y-270*(D3DX_PI/180);
			}
			if(pkey->GetKeyPress(DIK_D))
			{
				move->x+=sinf(cam->y+90*(D3DX_PI/180))*VALUE_TURBO_PLAYER;
				move->z+=cosf(cam->y+90*(D3DX_PI/180))*VALUE_TURBO_PLAYER;
				rot->y= cam->y+-90*(D3DX_PI/180);
			}
			if(pkey->GetKeyPress(DIK_W))
			{
				move->x+=sinf(cam->y)*VALUE_TURBO_PLAYER;
				move->z+=cosf(cam->y)*VALUE_TURBO_PLAYER;
				rot->y= cam->y-180*(D3DX_PI/180);
			}
			if(pkey->GetKeyPress(DIK_S))
			{
				move->x-=sinf(cam->y)*VALUE_TURBO_PLAYER;
				move->z-=cosf(cam->y)*VALUE_TURBO_PLAYER;
				rot->y= cam->y-0*(D3DX_PI/180);
			}
		}else
		{
			//移動
			if(pkey->GetKeyPress(DIK_A))
			{
				move->x-=sinf(cam->y+90*(D3DX_PI/180))*VALUE_MOVE_PLAYER_AIR;
				move->z-=cosf(cam->y+90*(D3DX_PI/180))*VALUE_MOVE_PLAYER_AIR;
				rot->y= cam->y-270*(D3DX_PI/180);
			}
			if(pkey->GetKeyPress(DIK_D))
			{
				move->x+=sinf(cam->y+90*(D3DX_PI/180))*VALUE_MOVE_PLAYER_AIR;
				move->z+=cosf(cam->y+90*(D3DX_PI/180))*VALUE_MOVE_PLAYER_AIR;
				rot->y= cam->y+-90*(D3DX_PI/180);
			}
			if(pkey->GetKeyPress(DIK_W))
			{
				move->x+=sinf(cam->y)*VALUE_MOVE_PLAYER_AIR;
				move->z+=cosf(cam->y)*VALUE_MOVE_PLAYER_AIR;
				rot->y= cam->y-180*(D3DX_PI/180);
			}
			if(pkey->GetKeyPress(DIK_S))
			{
				move->x-=sinf(cam->y)*VALUE_MOVE_PLAYER_AIR;
				move->z-=cosf(cam->y)*VALUE_MOVE_PLAYER_AIR;
				rot->y= cam->y-0*(D3DX_PI/180);
			}
		}

		//斜めの場合向きの変更
		if(pkey->GetKeyPress(DIK_A)&&(pkey->GetKeyPress(DIK_S)))
		{
			rot->y = cam->y-315*(D3DX_PI/180);
		}
		else if(pkey->GetKeyPress(DIK_D)&&(pkey->GetKeyPress(DIK_S)))
		{
			rot->y = cam->y-45*(D3DX_PI/180);
		}
		if(pkey->GetKeyPress(DIK_A)&&(pkey->GetKeyPress(DIK_W)))
		{
			rot->y = cam->y-225*(D3DX_PI/180);
		}
		else if(pkey->GetKeyPress(DIK_D)&&(pkey->GetKeyPress(DIK_W)))
		{
			rot->y = cam->y-135*(D3DX_PI/180);
		}
	}

	//回転
	if(pkey->GetKeyPress(DIK_LSHIFT))
	{
		rot->y -= VALUE_ROTATE_PLAYER;
		if(rot->y < -D3DX_PI)
		{
			rot->y += D3DX_PI * 2.0f;
		}
	}
	if(pkey->GetKeyPress(DIK_RSHIFT))
	{
		rot->y += VALUE_ROTATE_PLAYER;
		if(rot->y > D3DX_PI)
		{
			rot->y -= D3DX_PI * 2.0f;
		}
	}
}

//=============================================================================
// Player移動処理リプレイ
//=============================================================================
void PlayerMoveReplay(int type,bool jump,bool over,CInputKeyboard *pkey,D3DXVECTOR3* move,D3DXVECTOR3* rot,D3DXVECTOR3* cam)
{
	if(!jump)
	{
		if(pkey->GetReplayKey(DIK_T)||over)
		{
			//移動
			if(pkey->GetReplayKey(DIK_A))
			{
				move->x-=sinf(cam->y+90*(D3DX_PI/180))*VALUE_TURBO_PLAYER;
				move->z-=cosf(cam->y+90*(D3DX_PI/180))*VALUE_TURBO_PLAYER;
				rot->y= cam->y-270*(D3DX_PI/180);
			}
			if(pkey->GetReplayKey(DIK_D))
			{
				move->x+=sinf(cam->y+90*(D3DX_PI/180))*VALUE_TURBO_PLAYER;
				move->z+=cosf(cam->y+90*(D3DX_PI/180))*VALUE_TURBO_PLAYER;
				rot->y= cam->y+-90*(D3DX_PI/180);
			}
			if(pkey->GetReplayKey(DIK_W))
			{
				move->x+=sinf(cam->y)*VALUE_TURBO_PLAYER;
				move->z+=cosf(cam->y)*VALUE_TURBO_PLAYER;
				rot->y= cam->y-180*(D3DX_PI/180);
			}
			if(pkey->GetReplayKey(DIK_S))
			{
				move->x-=sinf(cam->y)*VALUE_TURBO_PLAYER;
				move->z-=cosf(cam->y)*VALUE_TURBO_PLAYER;
				rot->y= cam->y-0*(D3DX_PI/180);
			}
		}else
		{
			//移動
			if(pkey->GetReplayKey(DIK_A))
			{
				move->x-=sinf(cam->y+90*(D3DX_PI/180))*VALUE_MOVE_PLAYER;
				move->z-=cosf(cam->y+90*(D3DX_PI/180))*VALUE_MOVE_PLAYER;
				rot->y= cam->y-270*(D3DX_PI/180);
			}
			if(pkey->GetReplayKey(DIK_D))
			{
				move->x+=sinf(cam->y+90*(D3DX_PI/180))*VALUE_MOVE_PLAYER;
				move->z+=cosf(cam->y+90*(D3DX_PI/180))*VALUE_MOVE_PLAYER;
				rot->y= cam->y+-90*(D3DX_PI/180);
			}
			if(pkey->GetReplayKey(DIK_W))
			{
				move->x+=sinf(cam->y)*VALUE_MOVE_PLAYER;
				move->z+=cosf(cam->y)*VALUE_MOVE_PLAYER;
				rot->y= cam->y-180*(D3DX_PI/180);
			}
			if(pkey->GetReplayKey(DIK_S))
			{
				move->x-=sinf(cam->y)*VALUE_MOVE_PLAYER;
				move->z-=cosf(cam->y)*VALUE_MOVE_PLAYER;
				rot->y= cam->y-0*(D3DX_PI/180);
			}
		}
		

		//斜めの場合向きの変更
		if(pkey->GetReplayKey(DIK_A)&&(pkey->GetReplayKey(DIK_S)))
		{
			rot->y = cam->y-315*(D3DX_PI/180);
		}
		else if(pkey->GetReplayKey(DIK_D)&&(pkey->GetReplayKey(DIK_S)))
		{
			rot->y = cam->y-45*(D3DX_PI/180);
		}
		if(pkey->GetReplayKey(DIK_A)&&(pkey->GetReplayKey(DIK_W)))
		{
			rot->y = cam->y-225*(D3DX_PI/180);
		}
		else if(pkey->GetReplayKey(DIK_D)&&(pkey->GetReplayKey(DIK_W)))
		{
			rot->y = cam->y-135*(D3DX_PI/180);
		}
	}else
	{
		if(pkey->GetReplayKey(DIK_T))
		{
			//移動
			if(pkey->GetReplayKey(DIK_A))
			{
				move->x-=sinf(cam->y+90*(D3DX_PI/180))*VALUE_TURBO_PLAYER;
				move->z-=cosf(cam->y+90*(D3DX_PI/180))*VALUE_TURBO_PLAYER;
				rot->y= cam->y-270*(D3DX_PI/180);
			}
			if(pkey->GetReplayKey(DIK_D))
			{
				move->x+=sinf(cam->y+90*(D3DX_PI/180))*VALUE_TURBO_PLAYER;
				move->z+=cosf(cam->y+90*(D3DX_PI/180))*VALUE_TURBO_PLAYER;
				rot->y= cam->y+-90*(D3DX_PI/180);
			}
			if(pkey->GetReplayKey(DIK_W))
			{
				move->x+=sinf(cam->y)*VALUE_TURBO_PLAYER;
				move->z+=cosf(cam->y)*VALUE_TURBO_PLAYER;
				rot->y= cam->y-180*(D3DX_PI/180);
			}
			if(pkey->GetReplayKey(DIK_S))
			{
				move->x-=sinf(cam->y)*VALUE_TURBO_PLAYER;
				move->z-=cosf(cam->y)*VALUE_TURBO_PLAYER;
				rot->y= cam->y-0*(D3DX_PI/180);
			}
		}else
		{
			//移動
			if(pkey->GetReplayKey(DIK_A))
			{
				move->x-=sinf(cam->y+90*(D3DX_PI/180))*VALUE_MOVE_PLAYER_AIR;
				move->z-=cosf(cam->y+90*(D3DX_PI/180))*VALUE_MOVE_PLAYER_AIR;
				rot->y= cam->y-270*(D3DX_PI/180);
			}
			if(pkey->GetReplayKey(DIK_D))
			{
				move->x+=sinf(cam->y+90*(D3DX_PI/180))*VALUE_MOVE_PLAYER_AIR;
				move->z+=cosf(cam->y+90*(D3DX_PI/180))*VALUE_MOVE_PLAYER_AIR;
				rot->y= cam->y+-90*(D3DX_PI/180);
			}
			if(pkey->GetReplayKey(DIK_W))
			{
				move->x+=sinf(cam->y)*VALUE_MOVE_PLAYER_AIR;
				move->z+=cosf(cam->y)*VALUE_MOVE_PLAYER_AIR;
				rot->y= cam->y-180*(D3DX_PI/180);
			}
			if(pkey->GetReplayKey(DIK_S))
			{
				move->x-=sinf(cam->y)*VALUE_MOVE_PLAYER_AIR;
				move->z-=cosf(cam->y)*VALUE_MOVE_PLAYER_AIR;
				rot->y= cam->y-0*(D3DX_PI/180);
			}
		}

		//斜めの場合向きの変更
		if(pkey->GetReplayKey(DIK_A)&&(pkey->GetReplayKey(DIK_S)))
		{
			rot->y = cam->y-315*(D3DX_PI/180);
		}
		else if(pkey->GetReplayKey(DIK_D)&&(pkey->GetReplayKey(DIK_S)))
		{
			rot->y = cam->y-45*(D3DX_PI/180);
		}
		if(pkey->GetReplayKey(DIK_A)&&(pkey->GetReplayKey(DIK_W)))
		{
			rot->y = cam->y-225*(D3DX_PI/180);
		}
		else if(pkey->GetReplayKey(DIK_D)&&(pkey->GetReplayKey(DIK_W)))
		{
			rot->y = cam->y-135*(D3DX_PI/180);
		}
	}
}