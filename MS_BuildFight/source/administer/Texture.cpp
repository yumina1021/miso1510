//=============================================================================
//
// MS_BuildFight [CTexture.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "Texture.h"

LPDIRECT3DTEXTURE9  CTexture::m_pD3DTex[TEXTURE_LABEL_MAX];
// 各音素材のパラメータ
char* g_aParam[TEXTURE_LABEL_MAX] =
{
	{ "data/TEXTURE/Arrow.png" },
	{ "data/TEXTURE/Blue.png" },
	{ "data/TEXTURE/chara.png" },
	{ "data/TEXTURE/CharcterName1.png" },
	{ "data/TEXTURE/CharcterName2.png" },
	{ "data/TEXTURE/CharcterName3.png" },
	{ "data/TEXTURE/CharcterName4.png" },
	{ "data/TEXTURE/CharFrame.png" },
	{ "data/TEXTURE/circuit.png" },
	{ "data/TEXTURE/circuit2.png" },
	{ "data/TEXTURE/circuit_circle.png" },
	{ "data/TEXTURE/cracker.png" },
	{ "data/TEXTURE/Draw.png" },
	{ "data/TEXTURE/explosion003.png" },
	{ "data/TEXTURE/gage5.png" },
	{ "data/TEXTURE/game_rosa.png" },
	{ "data/TEXTURE/game_lila.png" },
	{ "data/TEXTURE/game_licht.png" },
	{ "data/TEXTURE/game_jiji.png" },
	{ "data/TEXTURE/golfball.png" },
	{ "data/TEXTURE/LevelStar.png" },
	{ "data/TEXTURE/Light.png" },
	{ "data/TEXTURE/loading1.jpg" },
	{ "data/TEXTURE/loading2.jpg" },
	{ "data/TEXTURE/loading3.jpg" },
	{ "data/TEXTURE/Loser.png" },
	{ "data/TEXTURE/number001.png" },
	{ "data/TEXTURE/Pause.jpg" },
	{ "data/TEXTURE/please_jiji.png" },
	{ "data/TEXTURE/please_licht.png" },
	{ "data/TEXTURE/please_lila.png" },
	{ "data/TEXTURE/please_rosa.png" },
	{ "data/TEXTURE/Rainbow.png" },
	{ "data/TEXTURE/ready1.png" },
	{ "data/TEXTURE/ready2.png" },
	{ "data/TEXTURE/Red.png" },
	{ "data/TEXTURE/s_0.png" },
	{ "data/TEXTURE/s_1.png" },
	{ "data/TEXTURE/s_2.png" },
	{ "data/TEXTURE/s_3.png" },
	{ "data/TEXTURE/s_4.png" },
	{ "data/TEXTURE/s_5.png" },
	{ "data/TEXTURE/s_6.png" },
	{ "data/TEXTURE/s_7.png" },
	{ "data/TEXTURE/s_8.png" },
	{ "data/TEXTURE/Select.png" },
	{ "data/TEXTURE/SelectPlayer1.png" },
	{ "data/TEXTURE/SelectPlayer2.png" },
	{ "data/TEXTURE/shot_jiji.png" },
	{ "data/TEXTURE/shot_licht.png" },
	{ "data/TEXTURE/shot_lila.png" },
	{ "data/TEXTURE/shot_rosa.png" },
	{ "data/TEXTURE/sky000.jpg" },
	{ "data/TEXTURE/sky004.jpg" },
	{ "data/TEXTURE/StageName1.png" },
	{ "data/TEXTURE/StageName2.png" },
	{ "data/TEXTURE/StageName3.png" },
	{ "data/TEXTURE/StageName4.png" },
	{ "data/TEXTURE/Star.png" },
	{ "data/TEXTURE/t_end.png" },
	{ "data/TEXTURE/t_start.png" },
	{ "data/TEXTURE/tama.jpg" },
	{ "data/TEXTURE/timeout.png" },
	{ "data/TEXTURE/window.png" },
	{ "data/TEXTURE/Winer.png" },
	{ "data/TEXTURE/yard.png" },
	{ "data/TEXTURE/Yellow.png" },
	{ "data/TEXTURE/character/licht/do.png" },
	{ "data/TEXTURE/character/licht/naki.png" },
	{ "data/TEXTURE/character/licht/normal.png" },
	{ "data/TEXTURE/character/licht/wara.png" },
	{ "data/TEXTURE/character/lila/do.png" },
	{ "data/TEXTURE/character/lila/naki.png" },
	{ "data/TEXTURE/character/lila/normal.png" },
	{ "data/TEXTURE/character/lila/wara.png" },
	{ "data/TEXTURE/character/navi/do.png" },
	{ "data/TEXTURE/character/navi/naki.png" },
	{ "data/TEXTURE/character/navi/normal.png" },
	{ "data/TEXTURE/character/navi/wara.png" },
	{ "data/TEXTURE/character/rosa/do.png" },
	{ "data/TEXTURE/character/rosa/naki.png" },
	{ "data/TEXTURE/character/rosa/normal.png" },
	{ "data/TEXTURE/character/rosa/wara.png" },
	{ "data/TEXTURE/result/licht_win.jpg" },
	{ "data/TEXTURE/result/licht_lose.jpg" },
	{ "data/TEXTURE/result/rosa_win.jpg" },
	{ "data/TEXTURE/result/rosa_lose.jpg" },
	{ "data/TEXTURE/result/lila_win.jpg" },
	{ "data/TEXTURE/result/lila_lose.jpg" },
	{ "data/TEXTURE/result/jiji_win.jpg" },
	{ "data/TEXTURE/result/jiji_lose.jpg" },
	{ "data/TEXTURE/background.jpg" },
};
//=============================================================================
// コンストラクタ
//=============================================================================
CTexture :: CTexture(void)
{
	for (int i = 0; i<TEXTURE_LABEL_MAX; i++)
	{
		m_pD3DTex[i] = NULL;
	}
}
//=============================================================================
// デストラクタ
//=============================================================================
CTexture :: ~CTexture(void)
{
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CTexture::Init(LPDIRECT3DDEVICE9 pdevice)
{

	for (int i = 0; i<TEXTURE_LABEL_MAX; i++)
	{
		if (D3DXCreateTextureFromFile(pdevice, g_aParam[i], &m_pD3DTex[i]) != D3D_OK)
		{
			MessageBox(NULL, g_aParam[i], TEXT("読み込みミス"), MB_OK);
		}
	}

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CTexture :: Uninit(void)
{
	for (int i = 0; i<TEXTURE_LABEL_MAX; i++)
	{
		m_pD3DTex[i]->Release();
		m_pD3DTex[i] = NULL;
	}
}
/////////////EOF////////////