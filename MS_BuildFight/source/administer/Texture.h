//=============================================================================
//
// MS_BuildFight [Sound.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CTEXTURE_H_
#define _CTEXTURE_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "../common.h"
//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	TEXTURE_ARROW = 0,
	TEXTURE_BLUE,
	TEXTURE_CHARA,
	TEXTURE_CHARANAME1,
	TEXTURE_CHARANAME2,
	TEXTURE_CHARANAME3,
	TEXTURE_CHARANAME4,
	TEXTURE_CHARAFRAME,
	TEXTURE_CIRCUIT,
	TEXTURE_CIRCUIT2,
	TEXTURE_CIRCUIT_CIRCLE,
	TEXTURE_CRACKER,
	TEXTURE_DRAW,
	TEXTURE_EXPLOSION003,
	TEXTURE_GAGE,
	TEXTURE_GAME_ROSA,
	TEXTURE_GAME_LILA,
	TEXTURE_GAME_LICHT,
	TEXTURE_GAME_JIJI,
	TEXTURE_GOLFBALL,
	TEXTURE_LEVELSTAR,
	TEXTURE_LIGHT,
	TEXTURE_LOADING1,
	TEXTURE_LOADING2,
	TEXTURE_LOADING3,
	TEXTURE_LOSER,
	TEXTURE_NUMBER001,
	TEXTURE_PAUSE,
	TEXTURE_PLEASE_JIJI,
	TEXTURE_PLEASE_LICHT,
	TEXTURE_PLEASE_LILA,
	TEXTURE_PLEASE_ROSA,
	TEXTURE_RAINBOW,
	TEXTURE_READY1,
	TEXTURE_READY2,
	TEXTURE_RED,
	TEXTURE_S_0,
	TEXTURE_S_1,
	TEXTURE_S_2,
	TEXTURE_S_3,
	TEXTURE_S_4,
	TEXTURE_S_5,
	TEXTURE_S_6,
	TEXTURE_S_7,
	TEXTURE_S_8,
	TEXTURE_SELECT,
	TEXTURE_SELECTPLAYER1,
	TEXTURE_SELECTPLAYER2,
	TEXTURE_SHOT_JIJI,
	TEXTURE_SHOT_LICHT,
	TEXTURE_SHOT_LILA,
	TEXTURE_SHOT_ROSA,
	TEXTURE_SKY000,
	TEXTURE_SKY004,
	TEXTURE_STAGENAME1,
	TEXTURE_STAGENAME2,
	TEXTURE_STAGENAME3,
	TEXTURE_STAGENAME4,
	TEXTURE_STAR,
	TEXTURE_T_END,
	TEXTURE_T_START,
	TEXTURE_TAMA,
	TEXTURE_TIMEOUT,
	TEXTURE_WINDOW,
	TEXTURE_WINER,
	TEXTURE_YARD,
	TEXTURE_YELLOW,
	TEXTURE_C_LICHT_DO,
	TEXTURE_C_LICHT_NAKI,
	TEXTURE_C_LICHT_NORMAL,
	TEXTURE_C_LICHT_WARA,
	TEXTURE_C_LILA_DO,
	TEXTURE_C_LILA_NAKI,
	TEXTURE_C_LILA_NORMAL,
	TEXTURE_C_LILA_WARA,
	TEXTURE_C_NAVI_DO,
	TEXTURE_C_NAVI_NAKI,
	TEXTURE_C_NAVI_NORMAL,
	TEXTURE_C_NAVI_WARA,
	TEXTURE_C_ROSA_DO,
	TEXTURE_C_ROSA_NAKI,
	TEXTURE_C_ROSA_NORMAL,
	TEXTURE_C_ROSA_WARA,
	TEXTURE_R_LICHT_WIN,
	TEXTURE_R_LICHT_LOSE,
	TEXTURE_R_ROSA_WIN,
	TEXTURE_R_ROSA_LOSE,
	TEXTURE_R_LILA_WIN,
	TEXTURE_R_LILA_LOSE,
	TEXTURE_R_JIJI_WIN,
	TEXTURE_R_JIJI_LOSE,
	TEXTURE_BACKGTROUND,
	TEXTURE_GOAL_NAVI,
	TEXTURE_CUPIN_C,
	TEXTURE_CUPIN_U,
	TEXTURE_CUPIN_P,
	TEXTURE_CUPIN_I,
	TEXTURE_CUPIN_N,
	TEXTURE_MAP_FIELD,
	TEXTURE_ICON_ROSA,
	TEXTURE_ICON_LILA,
	TEXTURE_ICON_LICHT,
	TEXTURE_ICON_JIJI,
	TEXTURE_ICON_FLAG,
	TEXTURE_ICON_BALL,
	TEXTURE_LABEL_MAX
} TEXTURE_LABEL;

//*****************************************************************************
// パラメータ構造体定義
//*****************************************************************************


//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTexture
{
	public:
		CTexture(void);				//コンストラクタ
		~CTexture(void);				//デストラクタ

		HRESULT Init(LPDIRECT3DDEVICE9 pdevice);				//初期化
		void Uninit(void);						//終了

		static LPDIRECT3DTEXTURE9 GetTex(int id)
		{
			if (id < TEXTURE_ARROW || TEXTURE_LABEL_MAX <= id)
			{
				return NULL;
			}
			return m_pD3DTex[id]; 
		}

	private:
		static LPDIRECT3DTEXTURE9  	m_pD3DTex[TEXTURE_LABEL_MAX];			//テクスチャ表示用
};

#endif

/////////////EOF////////////