
#include "Map.h"
#include "../../administer/scene/Game.h"
#include "../etc/Ball.h"
#include "../etc/Goal.h"
#include "../../administer/Texture.h"

#define SIZE_CONVERT	(0.09f)
void CreateMapModel(int no, D3DXVECTOR3 pos, LPDIRECT3DDEVICE9 device);
//=============================================================================
// CMap初期化
//=============================================================================
HRESULT CMap::Init(LPDIRECT3DDEVICE9 device, CBall* ball[2], CGoal* goal)
{
	m_pDevice = device;
	m_pBall[0] = ball[0];
	m_pBall[1] = ball[1];
	m_pGoal = goal;
	m_mappos = D3DXVECTOR3(SCREEN_WIDTH - 150.0f, SCREEN_HEIGHT / 2.0f - 80.0f, 0.0f);

	m_player[0] =	Cform2D::Create(m_pDevice,	TEXTURE_CUPIN_P, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH / 64, SCREEN_HEIGHT / 64);
	m_player[1] =	Cform2D::Create(m_pDevice,	TEXTURE_CUPIN_U, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH / 64, SCREEN_HEIGHT / 64);
	m_goal =		Cform2D::Create(m_pDevice,	TEXTURE_CUPIN_C, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH / 64, SCREEN_HEIGHT / 64);
	m_flame =		Cform2D::Create(m_pDevice,	TEXTURE_CHARAFRAME, m_mappos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 300, 300);
	vecfactor = 0;
	return TRUE;
}
//=============================================================================
// CMap解放
//=============================================================================
void CMap :: Uninit()
{
}
//=============================================================================
// CMap更新
//=============================================================================
void CMap :: Update()
{
	m_goal->SetPos(D3DXVECTOR3(-m_pGoal->GetPos().x * SIZE_CONVERT + m_mappos.x, m_pGoal->GetPos().z * SIZE_CONVERT + m_mappos.y, 1.0f));
	if (vecfactor > 5)vecfactor = 0;
	if (vecfactor < 0)vecfactor = 5;
	switch (vecfactor)
	{
	case 0:
		// 上
		m_player[0]->SetPos(D3DXVECTOR3(m_pBall[0]->GetPos().x * SIZE_CONVERT + m_mappos.x, -m_pBall[0]->GetPos().z * SIZE_CONVERT + m_mappos.y, 1.0f));
		m_player[1]->SetPos(D3DXVECTOR3(m_pBall[1]->GetPos().x * SIZE_CONVERT + m_mappos.x, -m_pBall[1]->GetPos().z * SIZE_CONVERT + m_mappos.y, 1.0f));
		break;
	case 1:
		// 下
		m_player[0]->SetPos(D3DXVECTOR3(-m_pBall[0]->GetPos().x * SIZE_CONVERT + m_mappos.x, m_pBall[0]->GetPos().z * SIZE_CONVERT + m_mappos.y, 1.0f));
		m_player[1]->SetPos(D3DXVECTOR3(-m_pBall[1]->GetPos().x * SIZE_CONVERT + m_mappos.x, m_pBall[1]->GetPos().z * SIZE_CONVERT + m_mappos.y, 1.0f));
		break;
	case 2:
		// 右
		m_player[0]->SetPos(D3DXVECTOR3(m_pBall[0]->GetPos().z * SIZE_CONVERT + m_mappos.x, -m_pBall[0]->GetPos().y * SIZE_CONVERT + m_mappos.y, 1.0f));
		m_player[1]->SetPos(D3DXVECTOR3(m_pBall[1]->GetPos().z * SIZE_CONVERT + m_mappos.x, -m_pBall[1]->GetPos().y * SIZE_CONVERT + m_mappos.y, 1.0f));
		break;
	case 3:
		// 左
		m_player[0]->SetPos(D3DXVECTOR3(-m_pBall[0]->GetPos().z * SIZE_CONVERT + m_mappos.x,-m_pBall[0]->GetPos().y * SIZE_CONVERT + m_mappos.y, 1.0f));
		m_player[1]->SetPos(D3DXVECTOR3(-m_pBall[1]->GetPos().z * SIZE_CONVERT + m_mappos.x,-m_pBall[1]->GetPos().y * SIZE_CONVERT + m_mappos.y, 1.0f));
		break;
	case 4:
		// 手前
		m_player[0]->SetPos(D3DXVECTOR3(m_pBall[0]->GetPos().x * SIZE_CONVERT + m_mappos.x, -m_pBall[0]->GetPos().y * SIZE_CONVERT + m_mappos.y, 1.0f));
		m_player[1]->SetPos(D3DXVECTOR3(m_pBall[1]->GetPos().x * SIZE_CONVERT + m_mappos.x, -m_pBall[1]->GetPos().y * SIZE_CONVERT + m_mappos.y, 1.0f));
		break;
	case 5:
		// 奥
		m_player[0]->SetPos(D3DXVECTOR3(-m_pBall[0]->GetPos().x * SIZE_CONVERT + m_mappos.x, -m_pBall[0]->GetPos().z * SIZE_CONVERT + m_mappos.y, 1.0f));
		m_player[1]->SetPos(D3DXVECTOR3(-m_pBall[1]->GetPos().x * SIZE_CONVERT + m_mappos.x, -m_pBall[1]->GetPos().z * SIZE_CONVERT + m_mappos.y, 1.0f));
		break;
	}
}
//=============================================================================
// CMap描画
//=============================================================================
void CMap :: Draw()
{
	m_flame->Draw();
	m_player[0]->Draw();
	m_player[1]->Draw();
	m_goal->Draw();
}
//=============================================================================
// CMap座標設定
//=============================================================================
void CMap :: SetVertexPolygon()
{
}
//=============================================================================
// CMapコンストラクト
//=============================================================================
CMap :: CMap()
{

}
//=============================================================================
// CMapデストラクト
//=============================================================================
CMap :: ~CMap()
{
}


CMap* CMap::Create(LPDIRECT3DDEVICE9 device, CBall* ball[2], CGoal* goal)
{
	CMap* pObject;
	pObject = new CMap();
	
	pObject->Init(device, ball, goal);

	return pObject;
}


void CreateMapModel(int no, D3DXVECTOR3 pos, LPDIRECT3DDEVICE9 device)
{

}