//=============================================================================
//
// MS_BuildFight [CCursor.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "Cursor.h"
#include "../../administer/Input.h"
#include "../../administer/Maneger.h"

//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************
const float CURSOR_MOVE_COFF(10.0f);

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCursor::CCursor() :CCharPicture(),
m_fDiffuse(1.0f),
m_fVelocity(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
m_bUseWiiPad(false),
m_Time(0.0f)
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCursor :: ~CCursor(void)
{
}
//=============================================================================
// CCursor����
//=============================================================================
CCursor *CCursor::Create(LPDIRECT3DDEVICE9 pDevice,PictureNum nType,D3DXVECTOR3 pos,float fwidth,float fheight)
{
	CCursor *pform2D;

	pform2D = new CCursor();
	pform2D->Init(pDevice,nType,pos,fwidth,fheight);

	return pform2D;
}
//=============================================================================
// ������
//=============================================================================
HRESULT CCursor :: Init(LPDIRECT3DDEVICE9 pDevice,PictureNum nType,D3DXVECTOR3 pos,float fwidth,float fheight)
{
	//�t�B�[���h�̏�����
	CCharPicture::Init(pDevice, nType, pos, fwidth, fheight);

	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CCursor :: Uninit(void)
{
	//�l�X�ȃI�u�W�F�N�g�̏I���i�J���j����
	CCharPicture::Uninit();
}
//=============================================================================
// �X�V
//=============================================================================
void CCursor :: Update(void)
{

	// �ړ��ʂ̉��Z
	//AddForce();

	CCharPicture::Update();
}
//=============================================================================
// �`��
//=============================================================================
void CCursor :: Draw(void)
{
	CCharPicture::Draw();
}
//=============================================================================
// �J�[���ړ��ł̑I��
//=============================================================================
bool CCursor::HitChkRect(const D3DXVECTOR3& paramPos1,
	const D3DXVECTOR3& paramPos2,
	const D3DXVECTOR3& paramLen1,
	const D3DXVECTOR3& paramLen2){

	if (abs(paramPos1.x - paramPos2.x) < (paramLen1.x * 0.5f + paramLen2.x * 0.5f) //���̔���
		&& abs(paramPos1.y - paramPos2.y) < (paramLen1.y * 0.5f + paramLen2.y * 0.5f)) //�c�̔���
	{

		// ��������
		return true;

	}

	// �������ĂȂ�
	return false;

}
//=============================================================================
// �L�[�{�[�h���g�p���Ă̈ړ�
// Wii�����R�����g��Ȃ��J�[�\���ړ��͂�������g��
//=============================================================================
void CCursor::MoveByKeybord(void){

	POINT tmpPointPos;
	D3DXVECTOR3 tmpPos(GetPos());

	HWND tmpWnd = CManager::GetWndHandle();

	GetCursorPos(&tmpPointPos);
	ScreenToClient(tmpWnd, &tmpPointPos);

	tmpPos.x = static_cast<float>(tmpPointPos.x);
	tmpPos.y = static_cast<float>(tmpPointPos.y);

	SetPos(tmpPos);

	// ������
	m_fVelocity.x = 0.0f;
	m_fVelocity.y = 0.0f;

}
//=============================================================================
// �L�[�{�[�h���g�p���Ă̈ړ�
// Wii�����R�����g��Ȃ��J�[�\���ړ��͂�������g��
//=============================================================================
void CCursor::AddForce(void){

	D3DXVECTOR3 tmpPos(GetPos());

	// ���W�̐ݒ�
	SetPos(tmpPos + m_fVelocity);

}
//=============================================================================
// �L�[�{�[�h���g�p���Ă̈ړ�
// Wii�����R�����g��Ȃ��J�[�\���ړ��͂�������g��
//=============================================================================
void CCursor::SyncCharPos(D3DXVECTOR3 paramSyncPos){

	D3DXVECTOR3 tmpPos(GetPos());

	tmpPos.x = EsasingNone(tmpPos.x, paramSyncPos.x, m_Time);
	tmpPos.y = EsasingNone(tmpPos.y, paramSyncPos.y, m_Time);
	tmpPos.z = EsasingNone(tmpPos.z, paramSyncPos.z, m_Time);

	SetPos(tmpPos);

	if (m_Time >= 1.0f)
	{
		m_Time = 0.0f;
	}
	else
	{
		m_Time += 0.02f;
	}

}
//=============================================================================
// �L�[�{�[�h���g�p���Ă̈ړ�
//=============================================================================
void CCursor::RadianRot(float& paramRot)
{
	if (paramRot > D3DX_PI)
	{
		paramRot += -D3DX_PI * 2.0f;
	}
	else if (paramRot < -D3DX_PI)
	{
		paramRot += D3DX_PI * 2.0f;
	}
}
//=============================================================================
// Easing����
//=============================================================================
float CCursor::EsasingNone(float paramMin, float paramMax, float paramTime){

	// ���`
	//return (paramMaxPos - paramMinPos)* paramTime + paramMinPos;

	float tmpRet(0.0f);

	if (paramTime < 0.5f)
	{

		// �񎟋Ȑ�
		tmpRet = (2.0 * paramTime) * (2.0 * paramTime) * 0.5f;

	}
	else
	{
		tmpRet = -((2.0 * paramTime - 2.0f) * (2.0 * paramTime - 2.0f)) * 0.5f + 1.0f;

	}

	return (paramMax - paramMin) * tmpRet + paramMin;
	
}
/////////////EOF////////////