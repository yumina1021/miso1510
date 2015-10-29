//=============================================================================
//
// MS_BuildFight [CLock.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "Lock.h"
#include "../etc/Camera.h"
#include "../../administer/Maneger.h"
//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************
const LPSTR CLock::m_apTextureName[]=
{
	"data/TEXTURE/lock.png",
	"data/TEXTURE/lockon.png"
};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLock :: CLock():CformBillBoard(7)
{
	m_nTextureNum=0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLock :: ~CLock(void)
{
}
//=============================================================================
// CLock����
//=============================================================================
CLock *CLock::Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CLock *pformBillBoard;

	pformBillBoard = new CLock();
	pformBillBoard->Init(pDevice,pos,rot);

	return pformBillBoard;
}
//=============================================================================
// ������
//=============================================================================
HRESULT CLock :: Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	m_pDevice=pDevice;

	//������
	//CformBillBoard::Init(m_pDevice,m_apTextureName[0],pos,rot,50,50);
	CformBillBoard::Init(m_pDevice,m_apTextureName[0],20,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));


	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CLock :: Uninit(void)
{
	//�l�X�ȃI�u�W�F�N�g�̏I���i�J���j����
	CformBillBoard::Uninit();

}
//=============================================================================
// �X�V
//=============================================================================
void CLock :: Update(void)
{
	//D3DXMATRIX  mtxWorld;
	//D3DXMATRIX mtxTranslate,mtxParent;

	CCamera *pCamera;
	pCamera = CManager::GetCamera();
	//CEnemyM *pEnemy;
	//pEnemy = CManager::GetEnemy();
	D3DXVECTOR3 setPos =pCamera->GetPointView();

	//mtxParent=pEnemy->GetMtxWorld();

	//D3DXMatrixIdentity(&mtxWorld);
	//D3DXMatrixTranslation(&mtxTranslate,setPos.x,setPos.y,setPos.z);
	//D3DXMatrixMultiply(&mtxWorld,&mtxWorld,&mtxTranslate);
	//D3DXMatrixMultiply(&mtxWorld,&mtxWorld,&mtxParent);

	setPos.y+=50;
	CformBillBoard::SetPos(D3DXVECTOR3(setPos.x,setPos.y,setPos.z));

	CformBillBoard::Update();
}
//=============================================================================
// �`��
//=============================================================================
void CLock :: Draw(void)
{
	CformBillBoard::Draw();
}
/////////////EOF////////////