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

	//���_�v�f�z������
	D3DVERTEXELEMENT9 vElement[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },		//���W
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },		//�@��
		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },	//UV
		{ 0, 32, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0 },	//tangent
		{ 0, 44, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0 },//�o�C�m�[�}��
		D3DDECL_END(),	//�Ō�ɕK�������
	};

	//�R���o�[�g����
	LPD3DXMESH pTempMesh = m_pD3DXMeshModel;
	pTempMesh->CloneMesh(D3DXMESH_SYSTEMMEM, &vElement[0], m_pDevice, &m_pD3DXMeshModel);

	//�]�@�����쐬
	D3DXComputeTangentFrame(m_pD3DXMeshModel, 0);

	if (pTempMesh)
	{
		pTempMesh->Release();
		pTempMesh = NULL;
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

	HRESULT hr;
	LPD3DXBUFFER err;
	LPD3DXBUFFER code;

	//�s�N�Z���V�F�[�_�[�p�ɕϊ�
	hr = D3DXCompileShaderFromFile("source/shader/basicPS.hlsl", NULL, NULL, "PS_DIFFUSE", "ps_2_0", 0, &code, &err, &m_shader.psc);

	if (FAILED(hr))
	{
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		err->Release();
		return false;
	}
	//�V�F�[�_�[�̓o�^
	hr = pDevice->CreatePixelShader((DWORD*)code->GetBufferPointer(), &m_shader.ps);

	if (FAILED(hr))
	{
		MessageBox(NULL, "FAILED", "CreatePixelShader", MB_OK);
		return false;
	}

	//�o�[�e�b�N�X�V�F�[�_�[�p�ɕϊ�1
	hr = D3DXCompileShaderFromFile("source/shader/basicVS.hlsl", NULL, NULL, "VS", "vs_2_0", 0, &code, &err, &m_shader.vsc);
	if (FAILED(hr))
	{
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		err->Release();
		return false;
	}
	//�V�F�[�_�[�̓o�^
	hr = pDevice->CreateVertexShader((DWORD*)code->GetBufferPointer(), &m_shader.vs);
	if (FAILED(hr))
	{
		MessageBox(NULL, "FAILED", "CreateVertexShader", MB_OK);
		return false;
	}

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
void CformX::Draw(void)
{
	CCamera* pCamera = CManager::GetCamera();

	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	D3DXMATRIX world, view, proj, rot, pos;
	D3DXMATRIX invWorld;

	//�r���[�s��
	D3DXVECTOR3 eye(0.0f, 50.0f, -100.0f);
	D3DXVECTOR3 at(0.0f, 20.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	D3DXVECTOR3 lightVec(0.20f, 0.0f, 0.80f);
	D3DXCOLOR   lightDiffuse(0.8f, 0.8f, 0.8f, 1.0f);
	D3DXCOLOR   lightDiffuse2(0.8f, 0.4f, 0.4f, 1.0f);
	D3DXCOLOR   lightAmbient(0.5f, 0.5f, 0.5f, 1.0f);

	eye = pCamera->GetPosP();
	at = pCamera->GetPosR();
	up = pCamera->GetVecUp();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rot.y, m_Rot.x, m_Rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &rot);

	//�ړ��𔽉f
	D3DXMatrixTranslation(&pos, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &pos);

	D3DXMatrixInverse(&invWorld, NULL, &m_mtxWorld);
	D3DXVec3TransformCoord(&lightVec, &lightVec, &invWorld);

	D3DXMatrixLookAtLH(&view, &eye, &at, &up);

	D3DXMatrixPerspectiveFovLH(&proj, D3DXToRadian(45), 960.0f / 540.0f, 10.0f, 100000.0f);

	D3DXMATRIX wvp = m_mtxWorld*view*proj;
	D3DXVECTOR3 cameraVec = at - eye;

	D3DXVec3Normalize(&cameraVec, &cameraVec);
	D3DXVec3Normalize(&lightVec, &lightVec);

	// ���[���h�}�g���b�N�X�̐ݒ�
	m_pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//�f�t�H���g�̃}�e���A�����擾
	m_pDevice->GetMaterial(&matDef);
	pD3DXMat = (D3DXMATERIAL*)m_pD3DXBuffMatModel->GetBufferPointer();

	m_shader.vsc->SetMatrix(m_pDevice, "world", &m_mtxWorld);
	m_shader.vsc->SetMatrix(m_pDevice, "gWvp", &wvp);

	m_shader.vsc->SetFloatArray(m_pDevice, "LightDir", (float*)&lightVec, 3);
	m_shader.vsc->SetVector(m_pDevice, "LightDiffuse", (D3DXVECTOR4*)&lightDiffuse);
	m_shader.vsc->SetVector(m_pDevice, "LightDiffuse2", (D3DXVECTOR4*)&lightDiffuse2);
	m_shader.vsc->SetVector(m_pDevice, "LightAmbient", (D3DXVECTOR4*)&lightAmbient);
	m_shader.vsc->SetFloatArray(m_pDevice, "CameraVec", (float*)&cameraVec, 3);
	m_shader.vsc->SetFloatArray(m_pDevice, "Pos", (float*)&eye, 3);

	if (m_pD3DTex[0] != NULL)
	{
		unsigned int s0 = m_shader.psc->GetSamplerIndex("texSampler");
		m_pDevice->SetTexture(s0, m_pD3DTex[0]);
	}
	else
	{
		m_pDevice->SetTexture(0, NULL);		//�e�N�X�`���͎g��Ȃ�
	}

	//�}�e���A���̌������[�v
	for (int nCntMat = 0; nCntMat<(int)m_nNumMatModel; nCntMat++)
	{
		m_shader.vsc->SetVector(m_pDevice, "MatDiffuse", (D3DXVECTOR4*)&pD3DXMat[nCntMat].MatD3D.Diffuse);
		m_shader.vsc->SetVector(m_pDevice, "MatAmbient", (D3DXVECTOR4*)&pD3DXMat[nCntMat].MatD3D.Ambient);
		m_pDevice->SetVertexShader(m_shader.vs);
		m_pDevice->SetPixelShader(m_shader.ps);

		m_pD3DXMeshModel->DrawSubset(nCntMat);			//���f���̃p�[�c��`��
	}

	//�}�e���A�������Ƃɖ߂��I
	m_pDevice->SetMaterial(&matDef);
	m_pDevice->SetPixelShader(NULL);

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