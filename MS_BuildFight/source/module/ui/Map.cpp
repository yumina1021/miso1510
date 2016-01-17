
#include "Map.h"
#include "../../administer/scene/Game.h"
#include "../etc/Ball.h"
#include "../etc/Goal.h"
#include "../../administer/Texture.h"
#include "../../form/formX.h"

#define SIZE_CONVERT	(0.05f)
void CreateMapModel(int no, D3DXVECTOR3 pos, LPDIRECT3DDEVICE9 device);
int g_icon_char[] =
{
	TEXTURE_ICON_ROSA,
	TEXTURE_ICON_LILA,
	TEXTURE_ICON_LICHT,
	TEXTURE_ICON_JIJI
};
//=============================================================================
// CMap初期化
//=============================================================================
HRESULT CMap::Init(LPDIRECT3DDEVICE9 device, CBall* ball[2], CGoal* goal, CformX* cursol, int player1, int player2)
{
	m_pDevice = device;
	m_pBall[0] = ball[0];
	m_pBall[1] = ball[1];
	m_pCursol = cursol;
	m_pGoal = goal;
	m_mappos = D3DXVECTOR3(SCREEN_WIDTH - 150.0f, SCREEN_HEIGHT / 2.0f - 80.0f, 0.0f);

	m_player[0] = Cform2D::Create(m_pDevice, g_icon_char[player1], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH / 32, SCREEN_HEIGHT / 32);
	m_player[1] = Cform2D::Create(m_pDevice, g_icon_char[player2], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH / 32, SCREEN_HEIGHT / 32);
	m_goal = Cform2D::Create(m_pDevice, TEXTURE_ICON_FLAG, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH / 32, SCREEN_HEIGHT / 32);
	m_flame =		Cform2D::Create(m_pDevice,	TEXTURE_CHARAFRAME, m_mappos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 300, 300);
	m_cursol = Cform2D::Create(m_pDevice, TEXTURE_ICON_BALL, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH / 64, SCREEN_HEIGHT / 64);
	//m_cursol->SetDiffuse(0.1f,0.f,0.1f,0.1f);
	vecfactor = 0;
	m_bDrawFlag = false;
	return TRUE;
}
//=============================================================================
// CMap解放
//=============================================================================
void CMap :: Uninit()
{
	delete m_fieldpos;
	delete[] m_Field;
}
//=============================================================================
// CMap更新
//=============================================================================
void CMap :: Update()
{
	if (vecfactor > 5)vecfactor = 0;
	if (vecfactor < 0)vecfactor = 5;
	switch (vecfactor)
	{
	case 0:
		// 上
		m_player[0]->SetPos(D3DXVECTOR3(m_pBall[0]->GetPos().x * SIZE_CONVERT + m_mappos.x, -m_pBall[0]->GetPos().z * SIZE_CONVERT + m_mappos.y, 1.0f));
		m_player[1]->SetPos(D3DXVECTOR3(m_pBall[1]->GetPos().x * SIZE_CONVERT + m_mappos.x, -m_pBall[1]->GetPos().z * SIZE_CONVERT + m_mappos.y, 1.0f));
		for (int i = 0; i < m_fieldnum; i++)
		{
			m_Field[i]->SetPos(D3DXVECTOR3(m_fieldpos[i].x * SIZE_CONVERT + m_mappos.x, -m_fieldpos[i].z * SIZE_CONVERT + m_mappos.y, 1.0f));
		}
		m_cursol->SetPos(D3DXVECTOR3(m_pCursol->GetPos().x * SIZE_CONVERT + m_mappos.x, -m_pCursol->GetPos().z * SIZE_CONVERT + m_mappos.y, 1.0f));
		m_goal->SetPos(D3DXVECTOR3(m_pGoal->GetPos().x * SIZE_CONVERT + m_mappos.x, -m_pGoal->GetPos().z * SIZE_CONVERT + m_mappos.y, 1.0f));
		break;
	case 1:
		// 下
		m_player[0]->SetPos(D3DXVECTOR3(-m_pBall[0]->GetPos().x * SIZE_CONVERT + m_mappos.x, m_pBall[0]->GetPos().z * SIZE_CONVERT + m_mappos.y, 1.0f));
		m_player[1]->SetPos(D3DXVECTOR3(-m_pBall[1]->GetPos().x * SIZE_CONVERT + m_mappos.x, m_pBall[1]->GetPos().z * SIZE_CONVERT + m_mappos.y, 1.0f));
		for (int i = 0; i < m_fieldnum; i++)
		{
			m_Field[i]->SetPos(D3DXVECTOR3(-m_fieldpos[i].x * SIZE_CONVERT + m_mappos.x, m_fieldpos[i].z * SIZE_CONVERT + m_mappos.y, 1.0f));
		}
		m_cursol->SetPos(D3DXVECTOR3(-m_pCursol->GetPos().x * SIZE_CONVERT + m_mappos.x, m_pCursol->GetPos().z * SIZE_CONVERT + m_mappos.y, 1.0f));
		m_goal->SetPos(D3DXVECTOR3(-m_pGoal->GetPos().x * SIZE_CONVERT + m_mappos.x, m_pGoal->GetPos().z * SIZE_CONVERT + m_mappos.y, 1.0f));
		break;
	case 2:
		// 右
		m_player[0]->SetPos(D3DXVECTOR3(m_pBall[0]->GetPos().z * SIZE_CONVERT + m_mappos.x, -m_pBall[0]->GetPos().y * SIZE_CONVERT + m_mappos.y, 1.0f));
		m_player[1]->SetPos(D3DXVECTOR3(m_pBall[1]->GetPos().z * SIZE_CONVERT + m_mappos.x, -m_pBall[1]->GetPos().y * SIZE_CONVERT + m_mappos.y, 1.0f));
		for (int i = 0; i < m_fieldnum; i++)
		{
			m_Field[i]->SetPos(D3DXVECTOR3(m_fieldpos[i].z * SIZE_CONVERT + m_mappos.x, -m_fieldpos[i].y * SIZE_CONVERT + m_mappos.y, 1.0f));
		}
		m_cursol->SetPos(D3DXVECTOR3(m_pCursol->GetPos().z * SIZE_CONVERT + m_mappos.x, -m_pCursol->GetPos().y * SIZE_CONVERT + m_mappos.y, 1.0f));
		m_goal->SetPos(D3DXVECTOR3(m_pGoal->GetPos().z * SIZE_CONVERT + m_mappos.x, -m_pGoal->GetPos().y * SIZE_CONVERT + m_mappos.y, 1.0f));
		break;
	case 3:
		// 左
		m_player[0]->SetPos(D3DXVECTOR3(-m_pBall[0]->GetPos().z * SIZE_CONVERT + m_mappos.x,-m_pBall[0]->GetPos().y * SIZE_CONVERT + m_mappos.y, 1.0f));
		m_player[1]->SetPos(D3DXVECTOR3(-m_pBall[1]->GetPos().z * SIZE_CONVERT + m_mappos.x, -m_pBall[1]->GetPos().y * SIZE_CONVERT + m_mappos.y, 1.0f));
		for (int i = 0; i < m_fieldnum; i++)
		{
			m_Field[i]->SetPos(D3DXVECTOR3(-m_fieldpos[i].z * SIZE_CONVERT + m_mappos.x, -m_fieldpos[i].y * SIZE_CONVERT + m_mappos.y, 1.0f));
		}
		m_cursol->SetPos(D3DXVECTOR3(-m_pCursol->GetPos().z * SIZE_CONVERT + m_mappos.x, -m_pCursol->GetPos().y * SIZE_CONVERT + m_mappos.y, 1.0f));
		m_goal->SetPos(D3DXVECTOR3(-m_pGoal->GetPos().z * SIZE_CONVERT + m_mappos.x, -m_pGoal->GetPos().y * SIZE_CONVERT + m_mappos.y, 1.0f));
		break;
	case 4:
		// 手前
		m_player[0]->SetPos(D3DXVECTOR3(m_pBall[0]->GetPos().x * SIZE_CONVERT + m_mappos.x, -m_pBall[0]->GetPos().y * SIZE_CONVERT + m_mappos.y, 1.0f));
		m_player[1]->SetPos(D3DXVECTOR3(m_pBall[1]->GetPos().x * SIZE_CONVERT + m_mappos.x, -m_pBall[1]->GetPos().y * SIZE_CONVERT + m_mappos.y, 1.0f));
		for (int i = 0; i < m_fieldnum; i++)
		{
			m_Field[i]->SetPos(D3DXVECTOR3(m_fieldpos[i].x * SIZE_CONVERT + m_mappos.x, -m_fieldpos[i].y * SIZE_CONVERT + m_mappos.y, 1.0f));
		}
		m_cursol->SetPos(D3DXVECTOR3(m_pCursol->GetPos().x * SIZE_CONVERT + m_mappos.x, -m_pCursol->GetPos().y * SIZE_CONVERT + m_mappos.y, 1.0f));
		m_goal->SetPos(D3DXVECTOR3(m_pGoal->GetPos().x * SIZE_CONVERT + m_mappos.x, -m_pGoal->GetPos().y * SIZE_CONVERT + m_mappos.y, 1.0f));
		break;
	case 5:
		// 奥
		m_player[0]->SetPos(D3DXVECTOR3(-m_pBall[0]->GetPos().x * SIZE_CONVERT + m_mappos.x, -m_pBall[0]->GetPos().y * SIZE_CONVERT + m_mappos.y, 1.0f));
		m_player[1]->SetPos(D3DXVECTOR3(-m_pBall[1]->GetPos().x * SIZE_CONVERT + m_mappos.x, -m_pBall[1]->GetPos().y * SIZE_CONVERT + m_mappos.y, 1.0f));
		for (int i = 0; i < m_fieldnum; i++)
		{
			m_Field[i]->SetPos(D3DXVECTOR3(-m_fieldpos[i].x * SIZE_CONVERT + m_mappos.x, -m_fieldpos[i].y * SIZE_CONVERT + m_mappos.y, 1.0f));
		}
		m_cursol->SetPos(D3DXVECTOR3(-m_pCursol->GetPos().x * SIZE_CONVERT + m_mappos.x, -m_pCursol->GetPos().y * SIZE_CONVERT + m_mappos.y, 1.0f));
		m_goal->SetPos(D3DXVECTOR3(-m_pGoal->GetPos().x * SIZE_CONVERT + m_mappos.x, -m_pGoal->GetPos().y * SIZE_CONVERT + m_mappos.y, 1.0f));
		break;
	}
}
//=============================================================================
// CMap描画
//=============================================================================
void CMap :: Draw()
{
	if (m_bDrawFlag)
	{
		m_flame->Draw();
		for (int i = 0; i < m_fieldnum; i++)
		{
			m_Field[i]->Draw();
		}
		m_cursol->Draw();
		if (CGame::GetBallFlag(0)) m_player[0]->Draw();
		if (CGame::GetBallFlag(1)) m_player[1]->Draw();
		m_goal->Draw();
	}
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


CMap* CMap::Create(LPDIRECT3DDEVICE9 device, CBall* ball[2], CGoal* goal, CformX* cursol, int player1, int player2)
{
	CMap* pObject;
	pObject = new CMap();
	
	pObject->Init(device, ball, goal, cursol, player1, player2);

	return pObject;
}


void CreateMapModel(int no, D3DXVECTOR3 pos, LPDIRECT3DDEVICE9 device)
{

}
void CMap::SetMapFieldNum(int num)
{
	m_fieldnum = num;
	m_fieldpos = new D3DXVECTOR3[num];
	m_Field = new Cform2D*[num];
}
void CMap::SetMapFieldPos(int id,D3DXVECTOR3 pos,float map_size)
{
	D3DXVECTOR3 work;
	m_Field[id] = Cform2D::Create(m_pDevice, TEXTURE_MAP_FIELD, pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), map_size * SIZE_CONVERT * 2.0f, map_size * SIZE_CONVERT * 2.0f);
	m_fieldpos[id] = pos;
}
