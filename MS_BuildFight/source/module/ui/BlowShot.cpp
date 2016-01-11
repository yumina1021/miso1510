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
#include "BlowShot.h"
#include "../etc/Camera.h"
#include "../../exten_common.h"
#include "../../administer/Maneger.h"
#include "../../administer/Texture.h"
const int g_blow_bg_tex[] =
{
	TEXTURE_YELLOW,
	TEXTURE_YELLOW,
	TEXTURE_YELLOW,
	TEXTURE_YELLOW
};
const int g_blow_char_tex[] =
{
	TEXTURE_C_ROSA_WARA,
	TEXTURE_C_LILA_WARA,
	TEXTURE_C_LICHT_WARA,
	TEXTURE_C_NAVI_WARA
};
const int g_blow_name_tex[] =
{
	TEXTURE_CHARANAME1,
	TEXTURE_CHARANAME2,
	TEXTURE_CHARANAME3,
	TEXTURE_CHARANAME4
};
#define BAIRITU_TEX_CHAR	(0.9f)
//=============================================================================
// コンストラクタ
//=============================================================================
CBlowShot :: CBlowShot()
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CBlowShot :: ~CBlowShot(void)
{
}
//=============================================================================
// CBlowShot生成
//=============================================================================
CBlowShot *CBlowShot::Create(LPDIRECT3DDEVICE9 pDevice, int pTexPlayer1, int pTexPlayer2)
{
	CBlowShot *pLocusEffect;

	pLocusEffect = new CBlowShot();
	pLocusEffect->Init(pDevice, pTexPlayer1, pTexPlayer2);

	return pLocusEffect;
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CBlowShot::Init(LPDIRECT3DDEVICE9 pDevice, int pTexName1, int pTexName2)
{
	m_pDevice = pDevice;
	m_bgpos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	m_charpos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 300.0f, SCREEN_HEIGHT / 2, 0.0f);
	m_namepos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 300.f, SCREEN_HEIGHT / 2 + 200.f, 0.0f);

	m_s_bgpos = D3DXVECTOR3(-SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	m_s_charpos = D3DXVECTOR3(-SCREEN_WIDTH / 2 - 300.0f, SCREEN_HEIGHT / 2, 0.0f);
	m_s_namepos = D3DXVECTOR3(-SCREEN_WIDTH / 2 + 300.f, SCREEN_HEIGHT / 2 + 200.f, 0.0f);

	m_pbgtex[0] = Cform2D::Create(m_pDevice, g_blow_bg_tex[pTexName1], m_bgpos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
	m_pbgtex[1] = Cform2D::Create(m_pDevice, g_blow_bg_tex[pTexName2], m_bgpos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);

	m_pchar[0] = Cform2D::Create(m_pDevice, g_blow_char_tex[pTexName1], m_charpos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 744 * BAIRITU_TEX_CHAR, 877 * BAIRITU_TEX_CHAR);
	m_pchar[1] = Cform2D::Create(m_pDevice, g_blow_char_tex[pTexName2], m_charpos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 744 * BAIRITU_TEX_CHAR, 877 * BAIRITU_TEX_CHAR);

	m_pname[0] = Cform2D::Create(m_pDevice, g_blow_name_tex[pTexName1], m_namepos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 544, 186);
	m_pname[1] = Cform2D::Create(m_pDevice, g_blow_name_tex[pTexName2], m_namepos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 544, 186);

	m_bFlag[0] = false;
	m_bFlag[1] = false;

	m_timer = 0.0f;
	m_bgtimer = 0.0f;
	m_chartimer = 0.0f;
	m_nametimer = 0.0f;
	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CBlowShot :: Uninit(void)
{
	for (int i = 0; i < 2; i++)
	{
		//m_pbgtex[i]->Uninit();
		//m_pchar[i]->Uninit();
		//m_pname[i]->Uninit();
	}
}
//=============================================================================
// 更新
//=============================================================================
void CBlowShot :: Update(void)
{
	for (int i = 0; i < 2; i++)
	{
		if (m_bFlag[i])
		{
			m_timer += 0.005f;
			if (m_timer > 0.001f){ m_bgtimer += 0.01f; }

			if (m_timer > 0.01f){m_chartimer += 0.04f;}

			if (m_timer > 0.05f){ m_nametimer += 0.05f; }

			if (m_bgtimer > 1.0f){ m_bgtimer = 1.0f; }
			if (m_chartimer > 1.0f){m_chartimer = 1.0f;}
			if (m_nametimer > 1.0f){m_nametimer = 1.0f;}

			if (m_timer > 1.0f)m_bFlag[i] = false;
			D3DXVECTOR3 pos;
			pos.x = EsasingNone(m_s_bgpos.x, m_bgpos.x, m_bgtimer);
			pos.y = EsasingNone(m_s_bgpos.y, m_bgpos.y, m_bgtimer);
			pos.z = EsasingNone(m_s_bgpos.z, m_bgpos.z, m_bgtimer);
			m_pbgtex[i]->SetPos(pos);
			pos.x = EsasingNone(m_s_charpos.x, m_charpos.x, m_chartimer);
			pos.y = EsasingNone(m_s_charpos.y, m_charpos.y, m_chartimer);
			pos.z = EsasingNone(m_s_charpos.z, m_charpos.z, m_chartimer);
			m_pchar[i]->SetPos(pos);
			pos.x = EsasingNone(m_s_namepos.x, m_namepos.x, m_nametimer);
			pos.y = EsasingNone(m_s_namepos.y, m_namepos.y, m_nametimer);
			pos.z = EsasingNone(m_s_namepos.z, m_namepos.z, m_nametimer);
			m_pname[i]->SetPos(pos);
		}
		m_pbgtex[i]->Update();
		m_pchar[i]->Update();
		m_pname[i]->Update();
	}
	if (!m_bFlag[0] && !m_bFlag[0])
	{
		m_timer = 0.0f;
		m_bgtimer = 0.0f;
		m_chartimer = 0.0f;
		m_nametimer = 0.0f;
	}
}
//=============================================================================
// 描画
//=============================================================================
void CBlowShot::Draw(void)
{
	for (int i = 0; i < 2; i++)
	{
		if (m_bFlag[i])
		{
			m_pbgtex[i]->Draw();
			m_pchar[i]->Draw();
			m_pname[i]->Draw();
		}
	}
}
//=============================================================================
// Easing処理
//=============================================================================
float CBlowShot::EsasingNone(float paramMin, float paramMax, float paramTime)
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