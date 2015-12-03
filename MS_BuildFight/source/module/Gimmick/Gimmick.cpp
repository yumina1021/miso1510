//=============================================================================
//
// MS_BuildFight [CGimmick.cpp]
// 15/08/20
// Author : TOSIKAZU INAZAWA
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "Gimmick.h" 
#include "../../../source/exten_common.h"
//*****************************************************************************
// 静的変数
//*****************************************************************************
const LPSTR CGimmick::m_ModelName[] =
{
	"data/MODEL/cube.x",
	"data/MODEL/cloud.x",
	"data/MODEL/crow.x",
	"data/MODEL/UFO.x",
	"data/MODEL/ball.x",
	"data/MODEL/tornado.x",
};
//=============================================================================
// コンストラクタ
//=============================================================================
CGimmick::CGimmick() :CformX()
{
	m_Size			= 
	m_Pos			= 
	m_Rot			= 
	m_Scl			= D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Speed			= 1.0f;
	m_Work			= D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_GimmickType	= GIMMICK_TORNADO;
	m_MoveType		= MOVETYPE_STOP;
}
//=============================================================================
// デストラクタ
//=============================================================================
CGimmick :: ~CGimmick(void)
{

}
//=============================================================================
// CBall生成
//=============================================================================
CGimmick *CGimmick::Create(LPDIRECT3DDEVICE9 pDevice, GIMMICKTYPE GimmickType, MOVETYPE MoveType, D3DXVECTOR3 movePos, D3DXVECTOR3 moveRot)
{

	CGimmick *pGimmick;

	pGimmick = new CGimmick();
	pGimmick->m_Work = movePos;
	pGimmick->Init(pDevice, GimmickType, MoveType);
	pGimmick->SetPos(movePos);
	pGimmick->SetRot(moveRot);

	return pGimmick;
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CGimmick::Init(LPDIRECT3DDEVICE9 pDevice, int nType,MOVETYPE MoveType)
{
	//デバイスの取得
	m_pDevice = pDevice;

	//建物の初期化
	CformX::Init(m_pDevice, m_ModelName[nType], NULL);

	m_bViewFlag = true;

	SetGimmickType((GIMMICKTYPE)nType);
	SetMoveType((MOVETYPE)MoveType);

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CGimmick::Uninit(void)
{
	//様々なオブジェクトの終了（開放）処理

	CformX::Uninit();

}
//=============================================================================
// 更新
//=============================================================================
void CGimmick::Update(void)
{
	_UpdateObject();
	//更新呼び出し
	CformX::Update();
}
//=============================================================================
// 描画
//=============================================================================
void CGimmick::Draw(void)
{
	if (m_bViewFlag)
	{
		CformX::Draw();
	}
}

void CGimmick::_UpdateObject(void)
{
	switch (GetGimmickType())
	{
		case GIMMICK_CUBE:
			_UpdateCube();
			break;
		case GIMMICK_CLOUD:
			_UpdateCloud();
			break;
		case GIMMICK_CROW:
			_UpdateCrow();
			break;
		case GIMMICK_UFO:
			_UpdateUFO();
			break;
		case GIMMICK_WIND:
			_UpdateWind();
			break;
		case GIMMICK_TORNADO:
			_UpdateTornado();
			break;
	}


	CformX::Update();
}

void CGimmick::_UpdateCube(void)
{
	switch (GetMoveType())
	{
		case MOVETYPE_STOP:
			UpdateCubeMoveStop();		//停止
			break;
		case MOVETYPE_UPDOWN:
			UpdateCubeMoveUpDown();		//上下
			break;
		case MOVETYPE_SLIDE:
			UpdateCubeMoveSlide();	//横移動
			break;
	}
	CformX::SetPos(m_Pos);
	CformX::SetRot(m_Rot);
}
void CGimmick::UpdateCubeMoveStop(void)
{
	
}
void CGimmick::UpdateCubeMoveSlide(void)
{
	m_Pos.x += m_Speed;
	
	if (m_Pos.x > m_Work.x+300)
	{ m_Speed *= -1.0f; }
	if (m_Pos.x < m_Work.x-300)
	{ m_Speed *= -1.0f; }

}
void CGimmick::UpdateCubeMoveUpDown(void)
{
	m_Pos.y += m_Speed;

	if (m_Pos.y > m_Work.y + 300) { m_Speed *= -1.0f; }
	if (m_Pos.y < m_Work.y - 300){ m_Speed *= -1.0f; }
}

void CGimmick::_UpdateCloud(void)
{
	switch (GetMoveType())
	{
		case MOVETYPE_STOP:
			UpdateCloudMoveStop();		//停止
			break;
		case MOVETYPE_UPDOWN:
			UpdateCloudMoveUpDown();		//上下
			break;
		case MOVETYPE_SLIDE:
			UpdateCloudMoveSlide();	//横移動
			break;
	}
	CformX::SetPos(m_Pos);
	CformX::SetRot(m_Rot);
}

void CGimmick::UpdateCloudMoveStop(void)
{

}
void CGimmick::UpdateCloudMoveSlide(void)
{
	m_Pos.x += m_Speed;

	if (m_Pos.x > m_Work.x + 300){m_Speed *= -1.0f;}
	if (m_Pos.x < m_Work.x - 300){m_Speed *= -1.0f;}
}
void CGimmick::UpdateCloudMoveUpDown(void)
{
	m_Pos.y += m_Speed;

	if (m_Pos.y > m_Work.y + 300) { m_Speed *= -1.0f; }
	if (m_Pos.y < m_Work.y - 300){ m_Speed *= -1.0f; }
}


void CGimmick::_UpdateCrow(void)
{
	switch (GetMoveType())
	{
	case MOVETYPE_STOP:
		UpdateCrowMoveStop();		//停止
		break;
	case MOVETYPE_UPDOWN:
		UpdateCrowMoveUpDown();		//上下
		break;
	case MOVETYPE_SLIDE:
		UpdateCrowMoveSlide();		//横移動
		break;
	}
	CformX::SetPos(m_Pos);
	CformX::SetRot(m_Rot);
}

void CGimmick::UpdateCrowMoveStop(void)
{

}
void CGimmick::UpdateCrowMoveSlide(void)
{
	m_Pos.x += m_Speed;



	if (m_Pos.x > m_Work.x + 300){ m_Speed *= -1.0f; }
	if (m_Pos.x < m_Work.x - 300){ m_Speed *= -1.0f; }
}
void CGimmick::UpdateCrowMoveUpDown(void)
{
	m_Pos.y += m_Speed;

	if (m_Pos.y > m_Work.y + 300) { m_Speed *= -1.0f; }
	if (m_Pos.y < m_Work.y - 300){ m_Speed *= -1.0f; }
}

void CGimmick::_UpdateUFO(void)
{
	switch (GetMoveType())
	{
	case MOVETYPE_STOP:
		UpdateUFOMoveStop();		//停止
		break;
	case MOVETYPE_UPDOWN:
		UpdateUFOMoveUpDown();		//上下
		break;
	case MOVETYPE_SLIDE:
		UpdateUFOMoveSlide();	//横移動
		break;
	}
	CformX::SetPos(m_Pos);
}

void CGimmick::UpdateUFOMoveStop(void)
{
	D3DXVECTOR3 Rot;
	Rot = CformX::GetRot();
	Rot.y += 0.1f;
	CformX::SetRot(Rot);
}
void CGimmick::UpdateUFOMoveSlide(void)
{
	m_Pos.x += m_Speed;

	D3DXVECTOR3 Rot;
	Rot = CformX::GetRot();
	Rot.y += 0.1f;
	CformX::SetRot(Rot);

	if (m_Pos.x > m_Work.x + 300){ m_Speed *= -1.0f; }
	if (m_Pos.x < m_Work.x - 300){ m_Speed *= -1.0f; }
}
void CGimmick::UpdateUFOMoveUpDown(void)
{
	m_Pos.y += m_Speed;

	D3DXVECTOR3 Rot;
	Rot = CformX::GetRot();
	Rot.y += 0.1f;
	CformX::SetRot(Rot);

	if (m_Pos.y > m_Work.y + 300) { m_Speed *= -1.0f; }
	if (m_Pos.y < m_Work.y - 300){ m_Speed *= -1.0f; }
}
void CGimmick::_UpdateWind(void)
{
	switch (GetMoveType())
	{
	case MOVETYPE_STOP:
		UpdateWindMoveStop();		//停止
		break;
	case MOVETYPE_UPDOWN:
		UpdateWindMoveUpDown();		//上下
		break;
	case MOVETYPE_SLIDE:
		UpdateWindMoveSlide();	//横移動
		break;
	}
	CformX::SetPos(m_Pos);
	CformX::SetRot(m_Rot);
}

void CGimmick::UpdateWindMoveStop(void)
{

}
void CGimmick::UpdateWindMoveSlide(void)
{
	m_Pos.x += m_Speed;

	if (m_Pos.x > m_Work.x + 300){ m_Speed *= -1.0f; }
	if (m_Pos.x < m_Work.x - 300){ m_Speed *= -1.0f; }
}
void CGimmick::UpdateWindMoveUpDown(void)
{
	m_Pos.y += m_Speed;

	if (m_Pos.y > m_Work.y + 300) { m_Speed *= -1.0f; }
	if (m_Pos.y < m_Work.y - 300){ m_Speed *= -1.0f; }
}
void CGimmick::_UpdateTornado(void)
{
	switch (GetMoveType())
	{
	case MOVETYPE_STOP:
		UpdateTornadoMoveStop();		//停止
		break;
	case MOVETYPE_UPDOWN:
		UpdateTornadoMoveUpDown();		//上下
		break;
	case MOVETYPE_SLIDE:
		UpdateTornadoMoveSlide();	//横移動
		break;
	}
	CformX::SetPos(m_Pos);
}

void CGimmick::UpdateTornadoMoveStop(void)
{
	D3DXVECTOR3 Rot;
	Rot = CformX::GetRot();
	Rot.y += 100.0f;
	CformX::SetRot(Rot);
}
void CGimmick::UpdateTornadoMoveSlide(void)
{
	m_Pos.x += m_Speed;

	D3DXVECTOR3 Rot;
	Rot = CformX::GetRot();
	Rot.y += 0.1f;
	CformX::SetRot(Rot);

	if (m_Pos.x > m_Work.x + 300){ m_Speed *= -1.0f; }
	if (m_Pos.x < m_Work.x - 300){ m_Speed *= -1.0f; }
}
void CGimmick::UpdateTornadoMoveUpDown(void)
{
	m_Pos.y += m_Speed;

	D3DXVECTOR3 Rot;
	Rot = CformX::GetRot();
	Rot.y += 0.1f;
	CformX::SetRot(Rot);

	if (m_Pos.y > m_Work.y + 300) { m_Speed *= -1.0f; }
	if (m_Pos.y < m_Work.y - 300){ m_Speed *= -1.0f; }
}



/////////////EOF////////////