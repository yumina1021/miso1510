//=============================================================================
//
// MS_BuildFight [LocusEffect.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "Cupin.h"
#include "../etc/Camera.h"
#include "../../exten_common.h"
#include "../../administer/Maneger.h"
#include "../../administer/Texture.h"

#define BAIRITU_TEX_CHAR	(0.9f)
D3DXVECTOR3 g_pos_start[5] =
{
	{SCREEN_WIDTH / 2 - 500.0f , SCREEN_HEIGHT / 2 - 40.0f, 0.0f},
	{SCREEN_WIDTH / 2 - 300.0f , SCREEN_HEIGHT / 2 - 60.0f, 0.0f},
	{SCREEN_WIDTH / 2 - 100.0f , SCREEN_HEIGHT / 2 - 80.0f, 0.0f},
	{SCREEN_WIDTH / 2 + 300.0f , SCREEN_HEIGHT / 2 - 60.0f, 0.0f},
	{SCREEN_WIDTH / 2 + 500.0f , SCREEN_HEIGHT / 2 - 40.0f, 0.0f}
};
const int g_cupin_tex[] =
{
	TEXTURE_CUPIN_C,
	TEXTURE_CUPIN_U,
	TEXTURE_CUPIN_P,
	TEXTURE_CUPIN_I,
	TEXTURE_CUPIN_N
};
//=============================================================================
// コンストラクタ
//=============================================================================
CCupin :: CCupin()
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CCupin :: ~CCupin(void)
{
}
//=============================================================================
// CCupin生成
//=============================================================================
CCupin *CCupin::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CCupin *pLocusEffect;

	pLocusEffect = new CCupin();
	pLocusEffect->Init(pDevice);

	return pLocusEffect;
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CCupin::Init(LPDIRECT3DDEVICE9 pDevice)
{
	m_pDevice = pDevice;
	for (int i = 0; i < 5; i++)
	{
		m_pos[i] = g_pos_start[i];
		m_s_timer[i] = 0.0f;
		m_pcupin[i] = Cform2D::Create(m_pDevice, g_cupin_tex[i], m_pos[i], D3DXVECTOR3(0.0f, 0.0f, 0.0f), 200.0f, 200.0f);
	}
	m_s_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT , 0.0f);

	m_timer = 0.0f;

	m_bDrawFlag = false;
	m_bFlag = false;
	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CCupin :: Uninit(void)
{
}
//=============================================================================
// 更新
//=============================================================================
void CCupin :: Update(void)
{
	if (m_bFlag)
	{
		m_timer += 0.005f;
		if (m_timer > 0.02f){ m_s_timer[0] += 0.05f; }

		if (m_timer > 0.04f){ m_s_timer[1] += 0.05f; }

		if (m_timer > 0.08f){ m_s_timer[2] += 0.05f; }

		if (m_timer > 0.16f){ m_s_timer[3] += 0.05f; }

		if (m_timer > 0.24f){ m_s_timer[4] += 0.05f; }

		if (m_s_timer[4] > 3.0f)
		{
			m_s_timer[4] = 3.0f; m_bFlag = false;
		}
		D3DXVECTOR3 pos;
		for (int i = 0; i < 5; i++)
		{
			pos.x = EsasingNone(m_s_pos.x, m_pos[i].x, m_s_timer[i]);
			pos.y = EsasingNone(m_s_pos.y, m_pos[i].y, m_s_timer[i]);
			pos.z = EsasingNone(m_s_pos.z, m_pos[i].z, m_s_timer[i]);
			m_pcupin[i]->SetPos(pos);
			m_pcupin[i]->Update();
		}
	}
	if (!m_bFlag)
	{
		m_timer = 0.0f;
	}
	if (!m_bDrawFlag)
	{
		for (int i = 0; i < 5; i++)
		{
			m_s_timer[i] = 0.0f;
			m_pcupin[i]->SetPos(m_s_pos);
		}
	}
}
//=============================================================================
// 描画
//=============================================================================
void CCupin::Draw(void)
{
	if (m_bDrawFlag)
	{
		for (int i = 0; i < 5; i++)
		{
			m_pcupin[i]->Draw();
		}
	}
}
//=============================================================================
// Easing処理
//=============================================================================
float CCupin::EsasingNone(float paramMin, float paramMax, float paramTime)
{

	// 線形
	//return (paramMaxPos - paramMinPos)* paramTime + paramMinPos;

	float tmpRet(0.0f);

	if (paramTime < 0.5f)
	{

		// 二次曲線
		tmpRet = (2.0 * paramTime) * (2.0 * paramTime) * 0.5f;

	}
	else
	{
		tmpRet = -((2.0 * paramTime - 2.0f) * (2.0 * paramTime - 2.0f)) * 0.5f + 1.0f;

	}
	if (paramTime > 1.0f)
	{
		return paramMax;
	}
	return (paramMax - paramMin) * tmpRet + paramMin;

}
/////////////EOF////////////