//=============================================================================
//
// MS_BuildFight [CLight.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "Light.h"
//=============================================================================
// コンストラクタ
//=============================================================================
CLight :: CLight(void)
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CLight :: ~CLight(void)
{
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CLight :: Init(LPDIRECT3DDEVICE9 pDevice)
{
	D3DXVECTOR3 vecDir;
	
	ZeroMemory(&m_Light[0],sizeof(D3DLIGHT9));
	m_Light[0].Type = D3DLIGHT_DIRECTIONAL;
	m_Light[0].Diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	//m_Light[0].Diffuse = D3DXCOLOR(1.0f,0.3f,0.0f,1.0f);
	m_Light[0].Ambient = D3DXCOLOR(0.50f,0.50f,0.50f,1.0f);
	vecDir = D3DXVECTOR3(10.0f,-10.0f,-10.0f);
	//vecDir = D3DXVECTOR3(0.20f, -0.60f, 0.80f);
	D3DXVec3Normalize((D3DXVECTOR3*)&m_Light[0].Direction,&vecDir);
	pDevice->SetLight(0,&m_Light[0]);	//設定
	pDevice->LightEnable(0,TRUE);		//ON,OFF

	ZeroMemory(&m_Light[1],sizeof(D3DLIGHT9));
	m_Light[1].Type = D3DLIGHT_DIRECTIONAL;
	m_Light[1].Diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	//m_Light[1].Diffuse = D3DXCOLOR(1.0f,0.3f,0.0f,0.5f);
	m_Light[1].Ambient = D3DXCOLOR(0.20f,0.20f,0.20f,1.0f);
	vecDir = D3DXVECTOR3(-10.0f,9.0f,10.0f);
	//vecDir = D3DXVECTOR3(-0.20f, 1.00f, -0.50f);
	D3DXVec3Normalize((D3DXVECTOR3*)&m_Light[1].Direction,&vecDir);
	pDevice->SetLight(1,&m_Light[1]);	//設定
	pDevice->LightEnable(1,TRUE);		//ON,OFF

	ZeroMemory(&m_Light[2],sizeof(D3DLIGHT9));
	m_Light[2].Type = D3DLIGHT_DIRECTIONAL;
	m_Light[2].Diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	//m_Light[2].Diffuse = D3DXCOLOR(1.0f,0.3f,0.0f,0.3f);
	m_Light[2].Ambient = D3DXCOLOR(0.10f,0.10f,0.10f,1.0f);
	//vecDir = D3DXVECTOR3(0.0f,-50.0f,100.0f);
	vecDir = D3DXVECTOR3(0.80f, 0.10f, 0.50f);
	D3DXVec3Normalize((D3DXVECTOR3*)&m_Light[2].Direction,&vecDir);
	pDevice->SetLight(2,&m_Light[2]);	//設定
	pDevice->LightEnable(2,TRUE);		//ON,OFF

	pDevice->SetRenderState(D3DRS_LIGHTING,TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENT, TRUE);
	
	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CLight :: Uninit(void)
{

}
//=============================================================================
// 更新
//=============================================================================
void CLight :: Update(void)
{

}
//=============================================================================
// 描画
//=============================================================================
void CLight :: Draw(void)
{

}
/////////////EOF////////////