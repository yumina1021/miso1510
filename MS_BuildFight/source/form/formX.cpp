//=============================================================================
//
// MS_BuildFight [CformX.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "formX.h"
#include "../module/robot/PlayerM.h"
#include "../module/robot/EnemyM.h"
#include "../administer/scene/Game.h"
#include "../module/etc/Camera.h"
#include "../administer/Maneger.h"
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CformX :: CformX(OBJTYPE objType,int nPriority) : Cform(objType,nPriority)
{
	nTextureNum=0;

	for(int i=0;i<TEXTURE_MAX;i++)
	{
		m_pD3DTex[i]=NULL;
	}

	m_bDeathFlag=false;
	m_nDeathCount=0;

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CformX :: ~CformX(void)
{
}
//=============================================================================
// CformX����
//=============================================================================
CformX *CformX::Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot,bool set,bool enemy)
{
	CformX *pformX;

	pformX = new CformX();
	if(enemy==true)
	{
		pformX->Init(pDevice,"data/MODEL/ring.x","data/TEXTURE/toumei6.png");
	}else
	{
		pformX->Init(pDevice,"data/MODEL/ring.x",NULL);
	}
	pformX->SetPos(pos);
	pformX->SetRot(rot);
	pformX->SetViewFlag(set);
	pformX->m_bEnemyFlag=enemy;

	return pformX;
}
//=============================================================================
// ������
//=============================================================================
HRESULT CformX :: Init(LPDIRECT3DDEVICE9 pDevice,LPSTR pFileName,LPSTR pTexName)
{
	//�f�o�C�X�̎擾
	m_pDevice=pDevice;

	//�t�B�[���h�̏�����
	m_Pos = D3DXVECTOR3(0.0f,0.00001f,0.0f);
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//x�t�@�C���̐ݒ�
	if(FAILED(D3DXLoadMeshFromX(pFileName,
								D3DXMESH_SYSTEMMEM,
								m_pDevice,
								NULL,
								&m_pD3DXBuffMatModel,
								NULL,
								&m_nNumMatModel,
								&m_pD3DXMeshModel)))
	{
		return E_FAIL;
	}
	//�e�N�X�`���̐ݒ�
	if(pTexName!=NULL)
	{
		D3DXCreateTextureFromFile(m_pDevice,pTexName,&m_pD3DTex[0]);
	}
	else
	{
		m_pD3DTex[0]=NULL;
	}

	m_bEnemyFlag=false;

	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CformX :: Uninit(void)
{
	//�l�X�ȃI�u�W�F�N�g�̏I���i�J���j����
	for(int i=0;i<TEXTURE_MAX;i++)
	{
		if(m_pD3DTex[i]!=NULL)
		{
			m_pD3DTex[i]->Release();
			m_pD3DTex[i]=NULL;
		}
	}
	if(m_pD3DXMeshModel!=NULL)
	{
		m_pD3DXMeshModel->Release();
		m_pD3DXMeshModel=NULL;
	}
	if(m_pD3DXBuffMatModel!=NULL)
	{
		m_pD3DXBuffMatModel->Release();
		m_pD3DXBuffMatModel=NULL;
	}

	Cform::Release();
}
//=============================================================================
// �X�V
//=============================================================================
void CformX :: Update(void)
{
	if(m_bDeathFlag)
	{
		D3DXVECTOR3 pos;

		if(m_bEnemyFlag==false)
		{
			CPlayerM *pPlayer;
			pPlayer=CGame::GetPlayer();
			pos=pPlayer->GetPos();
		}else
		{
			CEnemyM *pEnemy;
			pEnemy=CGame::GetEnemy(0);
			pos=pEnemy->GetPos();
		}
		m_Pos.x=pos.x;
		m_Pos.y=pos.y+100;
		m_Pos.z=pos.z;

		if(m_nDeathCount>1240)
		{
			m_nDeathCount=0;
			this->Uninit();
		}else
		{
			m_nDeathCount++;
		}
	}
	//���K��
	if(m_rotDestModel.y<-(D3DX_PI))
	{
		m_rotDestModel.y =(D3DX_PI);
	}
	if(m_rotDestModel.y>(D3DX_PI))
	{
		m_rotDestModel.y =-(D3DX_PI);
	}

	float fDiffRotY;

	//�ړI�̌����ւ̍�
	fDiffRotY = m_rotDestModel.y - m_Rot.y;

	//��̉�]���p
	if((fDiffRotY<-(D3DX_PI))||(fDiffRotY>(D3DX_PI)))
	{
		fDiffRotY *= -1;
	}

	//�ύX�l���
	m_Rot.y += fDiffRotY*0.15f;

	//���K��
	if(m_Rot.y<-(D3DX_PI))
	{
		m_Rot.y =(D3DX_PI);
	}
	if(m_Rot.y>(D3DX_PI))
	{
		m_Rot.y =-(D3DX_PI);
	}

	//����
	if(m_Pos.y<0)
	{
		m_Pos.y=0.00001f;
	}
}
//=============================================================================
// �`��
//=============================================================================
void CformX :: Draw(void)
{
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	D3DXMATRIX  mtxWorld;
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

	SetRotCamera(CManager::GetCamera()->GetRotCamera());
	SetMtxView(CManager::GetCamera()->GetMtxView());

	D3DXMatrixIdentity(&mtxWorld);
	D3DXMatrixScaling(&mtxScl,m_Scl.x,m_Scl.y,m_Scl.z);
	D3DXMatrixMultiply(&mtxWorld,&mtxWorld,&mtxScl);
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_Rot.y,m_Rot.x,m_Rot.z);
	D3DXMatrixMultiply(&mtxWorld,&mtxWorld,&mtxRot);
	D3DXMatrixTranslation(&mtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);
	D3DXMatrixMultiply(&mtxWorld,&mtxWorld,&mtxTranslate);

	m_pDevice->SetTransform(D3DTS_WORLD,&mtxWorld);

	//�f�t�H���g�̃}�e���A�����擾
	m_pDevice->GetMaterial(&matDef);

	pD3DXMat=(D3DXMATERIAL*)m_pD3DXBuffMatModel->GetBufferPointer();
	
	if(m_pD3DTex!=NULL)
	{
		m_pDevice->SetTexture(0,m_pD3DTex[nTextureNum]);					//�e�N�X�`���͎g��Ȃ�

	}else
	{
		m_pDevice->SetTexture(0,NULL);						//�e�N�X�`���͎g��Ȃ�

	}

	//�}�e���A���̌������[�v
	for (int nCntMat = 0; nCntMat<(int)m_nNumMatModel; nCntMat++)
	{
		m_pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
		m_pD3DXMeshModel->DrawSubset(nCntMat);			//���f���̃p�[�c��`��
	}

	//�}�e���A�������Ƃɖ߂��I
	m_pDevice->SetMaterial(&matDef);

}

void CformX ::SetTexture(LPSTR pTexName,int num)
{
	if(pTexName!=NULL)
	{
		D3DXCreateTextureFromFile(m_pDevice,pTexName,&m_pD3DTex[num]);
	}else
	{
		m_pD3DTex[num]=NULL;
	}
}
/////////////EOF////////////