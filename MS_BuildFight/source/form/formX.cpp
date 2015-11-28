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
#include "../exten_common.h"

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
// CformX����
//=============================================================================
CformX *CformX::Create(LPDIRECT3DDEVICE9 pDevice, LPSTR pModNameStr, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CformX *pformX;

	pformX = new CformX();
	pformX->Init(pDevice, pModNameStr, NULL);
	pformX->SetPos(pos);
	pformX->SetRot(rot);

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

	// �L���[�u�e�N�X�`���̓ǂݍ���
	D3DXCreateCubeTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		"data/TEXTURE/sky.dds",		// �t�@�C���̖��O
		&m_pD3DTextureCube);		// �ǂݍ��ރ������[

	m_bEnemyFlag=false;

	//�s�N�Z���V�F�[�_�[�p�ɕϊ�1
	Create_PS("source/shader/basicPS.hlsl", "PS_DIFFUSE", &m_shader.ps, &m_shader.psc, m_pDevice);

	//�o�[�e�b�N�X�V�F�[�_�[�p�ɕϊ�1
	Create_VS("source/shader/basicVS.hlsl", "VS", &m_shader.vs, &m_shader.vsc, m_pDevice);
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

	if (m_pD3DTextureCube != NULL)
	{// �}�e���A���̊J��
		m_pD3DTextureCube->Release();
		m_pD3DTextureCube = NULL;
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

	if(m_shader.ps != NULL	)m_shader.ps	->Release();
	if(m_shader.psc!= NULL	)m_shader.psc	->Release();
	if(m_shader.vs	!= NULL	)m_shader.vs	->Release();
	if(m_shader.vsc!= NULL	)m_shader.vsc	->Release();
	Cform::Release();
}
//=============================================================================
// �X�V
//=============================================================================
void CformX :: Update(void)
{

	//���K��
	m_rotDestModel.x = Rotation_Normalizer(m_rotDestModel.x);
	m_rotDestModel.y = Rotation_Normalizer(m_rotDestModel.y);
	m_rotDestModel.z = Rotation_Normalizer(m_rotDestModel.z);

	D3DXVECTOR3 fDiffRot;

	//�ړI�̌����ւ̍�
	fDiffRot = m_rotDestModel - m_Rot;

	//��̉�]���p
	if ((fDiffRot.x<-(D3DX_PI)) || (fDiffRot.x>(D3DX_PI)))
	{
		fDiffRot.x *= -1;
	}
	if ((fDiffRot.y<-(D3DX_PI)) || (fDiffRot.y>(D3DX_PI)))
	{
		fDiffRot.y *= -1;
	}
	if ((fDiffRot.z<-(D3DX_PI)) || (fDiffRot.z>(D3DX_PI)))
	{
		fDiffRot.z *= -1;
	}

	//�ύX�l���
	m_Rot += fDiffRot*0.015f;

	//���K��
	m_Rot.x = Rotation_Normalizer(m_Rot.x);
	m_Rot.y = Rotation_Normalizer(m_Rot.y);
	m_Rot.z = Rotation_Normalizer(m_Rot.z);

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
	D3DXMATRIX invWorld, invTransWorld;

	//�r���[�s��
	D3DXVECTOR3 eye(0.0f, 50.0f, -100.0f);
	D3DXVECTOR3 at(0.0f, 20.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	D3DXVECTOR3 lightVec(m_Pos.x - 0.20f, m_Pos.y - 0.0f, m_Pos.z- 0.80f);
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
	D3DXMatrixInverse(&invTransWorld, NULL, &m_mtxWorld);
	D3DXMatrixTranspose(&invTransWorld, &invTransWorld);

	D3DXVec3TransformCoord(&lightVec, &lightVec, &invWorld);

	D3DXMatrixLookAtLH(&view, &eye, &at, &up);

	D3DXMatrixPerspectiveFovLH(&proj, D3DXToRadian(45), 960.0f / 540.0f, 10.0f, 100000.0f);

	D3DXMATRIX wvp = m_mtxWorld*view*proj;
	D3DXVECTOR3 cameraVec = at - eye;

	D3DXVec3Normalize(&cameraVec, &cameraVec);
	D3DXVec3Normalize(&lightVec, &lightVec);

	// ���[���h�}�g���b�N�X�̐ݒ�
	//m_pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//�f�t�H���g�̃}�e���A�����擾
	m_pDevice->GetMaterial(&matDef);
	pD3DXMat = (D3DXMATERIAL*)m_pD3DXBuffMatModel->GetBufferPointer();

	m_shader.vsc->SetMatrix(m_pDevice, "world", &m_mtxWorld);
	m_shader.vsc->SetMatrix(m_pDevice, "gWvp", &wvp);
	m_shader.vsc->SetMatrix(m_pDevice, "worldInvTranspose", &invTransWorld);

	m_shader.psc->SetFloatArray(m_pDevice, "CameraVec", (float*)&cameraVec, 3);
	m_shader.psc->SetFloatArray(m_pDevice, "LightDir", (float*)&lightVec, 3);

	m_shader.vsc->SetVector(m_pDevice, "LightDiffuse", (D3DXVECTOR4*)&lightDiffuse);
	m_shader.vsc->SetVector(m_pDevice, "LightDiffuse2", (D3DXVECTOR4*)&lightDiffuse2);
	m_shader.vsc->SetVector(m_pDevice, "LightAmbient", (D3DXVECTOR4*)&lightAmbient);
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

	unsigned int s0;
	s0 = m_shader.psc->GetSamplerIndex("texSamplerCube");
	m_pDevice->SetTexture(s0, m_pD3DTextureCube);

	//�}�e���A���̌������[�v
	for (int nCntMat = 0; nCntMat<(int)m_nNumMatModel; nCntMat++)
	{
		m_shader.vsc->SetVector(m_pDevice, "MatDiffuse", (D3DXVECTOR4*)&pD3DXMat[nCntMat].MatD3D.Diffuse);
		m_shader.psc->SetVector(m_pDevice, "MatDiffuse", (D3DXVECTOR4*)&pD3DXMat[nCntMat].MatD3D.Diffuse);
		m_shader.vsc->SetVector(m_pDevice, "MatAmbient", (D3DXVECTOR4*)&pD3DXMat[nCntMat].MatD3D.Ambient);
		m_pDevice->SetVertexShader(m_shader.vs);
		m_pDevice->SetPixelShader(m_shader.ps);

		m_pD3DXMeshModel->DrawSubset(nCntMat);			//���f���̃p�[�c��`��
	}

	//�}�e���A�������Ƃɖ߂��I
	m_pDevice->SetMaterial(&matDef);

	m_pDevice->SetVertexShader(NULL);
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