//=============================================================================
//
// MS_BuildFight [CGimmick.cpp]
// 15/08/20
// Author : TOSIKAZU INAZAWA
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "Gimmick.h" 
#include "../../../source/exten_common.h"
//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************
const LPSTR CGimmick::m_ModelName[] =
{
	"data/MODEL/cube.x",
	"data/MODEL/cube.x",
	"data/MODEL/cube.x",
	"data/MODEL/ufo.x",
	"data/MODEL/cube.x",
	"data/MODEL/tornado.x",
};
//=============================================================================
// �R���X�g���N�^
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
// �f�X�g���N�^
//=============================================================================
CGimmick :: ~CGimmick(void)
{

}
//=============================================================================
// CBall����
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
// ������
//=============================================================================
HRESULT CGimmick::Init(LPDIRECT3DDEVICE9 pDevice, int nType,MOVETYPE MoveType)
{
	//�f�o�C�X�̎擾
	m_pDevice = pDevice;

	//�����̏�����
	CformX::Init(m_pDevice, m_ModelName[nType], NULL);

	m_bViewFlag = true;

	m_nsMagnet = N;

	SetGimmickType((GIMMICKTYPE)nType);
	SetMoveType((MOVETYPE)MoveType);

	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CGimmick::Uninit(void)
{
	//�l�X�ȃI�u�W�F�N�g�̏I���i�J���j����

	CformX::Uninit();

}
//=============================================================================
// �X�V
//=============================================================================
void CGimmick::Update(void)
{
	_UpdateObject();
	//�X�V�Ăяo��
	CformX::Update();
}
//=============================================================================
// �`��
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
			UpdateCubeMoveStop();		//��~
			break;
		case MOVETYPE_UPDOWN:
			UpdateCubeMoveUpDown();		//�㉺
			break;
		case MOVETYPE_SLIDE:
			UpdateCubeMoveSlide();	//���ړ�
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
			UpdateCloudMoveStop();		//��~
			break;
		case MOVETYPE_UPDOWN:
			UpdateCloudMoveUpDown();		//�㉺
			break;
		case MOVETYPE_SLIDE:
			UpdateCloudMoveSlide();	//���ړ�
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
		UpdateCrowMoveStop();		//��~
		break;
	case MOVETYPE_UPDOWN:
		UpdateCrowMoveUpDown();		//�㉺
		break;
	case MOVETYPE_SLIDE:
		UpdateCrowMoveSlide();		//���ړ�
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
		UpdateUFOMoveStop();		//��~
		break;
	case MOVETYPE_UPDOWN:
		UpdateUFOMoveUpDown();		//�㉺
		break;
	case MOVETYPE_SLIDE:
		UpdateUFOMoveSlide();	//���ړ�
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
		UpdateWindMoveStop();		//��~
		break;
	case MOVETYPE_UPDOWN:
		UpdateWindMoveUpDown();		//�㉺
		break;
	case MOVETYPE_SLIDE:
		UpdateWindMoveSlide();	//���ړ�
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
		UpdateTornadoMoveStop();		//��~
		break;
	case MOVETYPE_UPDOWN:
		UpdateTornadoMoveUpDown();		//�㉺
		break;
	case MOVETYPE_SLIDE:
		UpdateTornadoMoveSlide();	//���ړ�
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