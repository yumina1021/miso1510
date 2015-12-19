//=============================================================================
//
// MS_BuildFight [CModel.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#include "Model.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "../etc/Camera.h"
//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************
const char *CModel::m_apModelName[]=
{
	"data/MODELNIGHT/body.x",		// [0]��
	"data/MODELNIGHT/head.x",		// [1]��
	"data/MODELNIGHT/arm_r.x",		// [2]�E�r
	"data/MODELNIGHT/hand_r.x",		// [3]�E��
	"data/MODELNIGHT/finger_r.x",	// [3]�E�w
	"data/MODELNIGHT/arm_l.x",		// [4]���r
	"data/MODELNIGHT/hand_l.x",		// [5]����
	"data/MODELNIGHT/finger_l.x",	// [5]���w
	"data/MODELNIGHT/leg_r.x",		// [6]�E��
	"data/MODELNIGHT/foot_r.x",		// [7]�E��
	"data/MODELNIGHT/leg_l.x",		// [8]����
	"data/MODELNIGHT/foot_l.x",		// [9]����

	"data/MODELGUN/body.x",	// [0]��
	"data/MODELGUN/head.x",	// [1]��
	"data/MODELGUN/arm_r.x",	// [2]�E�r
	"data/MODELGUN/hand_r.x",	// [3]�E��
	"data/MODELGUN/finger_r.x",	// [3]�E�w
	"data/MODELGUN/arm_l.x",	// [4]���r
	"data/MODELGUN/hand_l.x",	// [5]����
	"data/MODELGUN/finger_l.x",	// [5]���w
	"data/MODELGUN/leg_r.x",	// [6]�E��
	"data/MODELGUN/foot_r.x",	// [7]�E��
	"data/MODELGUN/leg_l.x",	// [8]����
	"data/MODELGUN/foot_l.x",	// [9]����

	"data/MODELGUN2/body.x",	// [0]��
	"data/MODELGUN2/head.x",	// [1]��
	"data/MODELGUN2/arm_r.x",	// [2]�E�r
	"data/MODELGUN2/hand_r.x",	// [3]�E��
	"data/MODELGUN2/finger_r.x",	// [3]�E�w
	"data/MODELGUN2/arm_l.x",	// [4]���r
	"data/MODELGUN2/hand_l.x",	// [5]����
	"data/MODELGUN2/finger_l.x",	// [5]���w
	"data/MODELGUN2/leg_r.x",	// [6]�E��
	"data/MODELGUN2/foot_r.x",	// [7]�E��
	"data/MODELGUN2/leg_l.x",	// [8]����
	"data/MODELGUN2/foot_l.x",	// [9]����

	"data/MODELGUN3/body.x",	// [0]��
	"data/MODELGUN3/head.x",	// [1]��
	"data/MODELGUN3/arm_r.x",	// [2]�E�r
	"data/MODELGUN3/hand_r.x",	// [3]�E��
	"data/MODELGUN3/finger_r.x",	// [3]�E�w
	"data/MODELGUN3/arm_l.x",	// [4]���r
	"data/MODELGUN3/hand_l.x",	// [5]����
	"data/MODELGUN3/finger_l.x",	// [5]���w
	"data/MODELGUN3/leg_r.x",	// [6]�E��
	"data/MODELGUN3/foot_r.x",	// [7]�E��
	"data/MODELGUN3/leg_l.x",	// [8]����
	"data/MODELGUN3/foot_l.x",	// [9]����

	"data/MODELGUN0/body.x",	// [0]��
	"data/MODELGUN0/head.x",	// [1]��
	"data/MODELGUN0/arm_r.x",	// [2]�E�r
	"data/MODELGUN0/hand_r.x",	// [3]�E��
	"data/MODELGUN0/finger_r.x",	// [3]�E�w
	"data/MODELGUN0/arm_l.x",	// [4]���r
	"data/MODELGUN0/hand_l.x",	// [5]����
	"data/MODELGUN0/finger_l.x",	// [5]���w
	"data/MODELGUN0/leg_r.x",	// [6]�E��
	"data/MODELGUN0/foot_r.x",	// [7]�E��
	"data/MODELGUN0/leg_l.x",	// [8]����
	"data/MODELGUN0/foot_l.x",	// [9]����
};
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CModel :: CModel(void)
{

	m_pD3DXMeshModel = NULL;
	m_pD3DXBuffMatModel = NULL;
	m_nNumMatModel = 0;


	m_bTransParent = false;

	m_pParent = NULL;
	m_pChild = NULL;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CModel :: ~CModel(void)
{
}
//=============================================================================
// CModel����
//=============================================================================
CModel *CModel::Create(LPDIRECT3DDEVICE9 pDevice,int nType,int nModelNum,D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CModel *pModel;

	pModel = new CModel();
	pModel->Init(pDevice,nType,nModelNum);
	pModel->SetPos(pos);
	pModel->SetRot(rot);

	return pModel;
}
//=============================================================================
// ������
//=============================================================================
HRESULT CModel :: Init(LPDIRECT3DDEVICE9 pDevice,int nType,int nModelNum)
{
	//�f�o�C�X�̎擾
	m_pDevice=pDevice;

	//�t�B�[���h�̏�����
	m_Pos = D3DXVECTOR3(0.0f,0.00001f,0.0f);
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl = D3DXVECTOR3(1.0f,1.0f,1.0f);
	m_PosOrg = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_RotOrg = D3DXVECTOR3(0.0f,0.0f,0.0f);

	SetModel(m_apModelName[nType+nModelNum]);

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

	D3DXMatrixIdentity(&m_mtxview);
	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CModel :: Uninit(void)
{
	//�l�X�ȃI�u�W�F�N�g�̏I���i�J���j����
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

}
//=============================================================================
// �X�V
//=============================================================================
void CModel :: Update(void)
{
}
//=============================================================================
// �`��
//=============================================================================
void CModel::Draw(LPDIRECT3DTEXTURE9 pD3DTex, SHADER_SET* shader, CCamera* camera)
{
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	D3DXMATRIX world, view, proj, rot, pos, mtxParent;
	D3DXMATRIX invWorld;

	//�r���[�s��
	D3DXVECTOR3 eye(0.0f, 50.0f, -100.0f);
	D3DXVECTOR3 at(0.0f, 20.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	D3DXVECTOR3 lightVec(0.20f, 0.0f, 0.80f);
	D3DXCOLOR   lightDiffuse(0.8f, 0.8f, 0.8f, 1.0f);
	D3DXCOLOR   lightDiffuse2(0.8f, 0.4f, 0.4f, 1.0f);
	D3DXCOLOR   lightAmbient(0.5f, 0.5f, 0.5f, 1.0f);

	eye = camera->GetPosP();
	at = camera->GetPosR();
	up = camera->GetVecUp();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	if (m_pParent)
	{// �e���f��������ꍇ
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{// �e���f�����Ȃ��ꍇ
		m_pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rot.y + m_RotOrg.y, m_Rot.x + m_RotOrg.x, m_Rot.z + m_RotOrg.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &rot);

	//�ړ��𔽉f
	D3DXMatrixTranslation(&pos, m_Pos.x + m_PosOrg.x, m_Pos.y + m_PosOrg.y, m_Pos.z + m_PosOrg.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &pos);

	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxview);
	// �e�̃}�g���b�N�X�ƎZ�o�����}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	D3DXMatrixInverse(&invWorld, NULL, &m_mtxWorld);
	D3DXVec3TransformCoord(&lightVec, &lightVec, &invWorld);

	D3DXMatrixLookAtLH(&view, &eye, &at, &up);

	D3DXMatrixPerspectiveFovLH(&proj, D3DXToRadian(45), 960.0f / 540.0f, 10.0f, 100000.0f);

	D3DXMATRIX wvp = m_mtxWorld*view*proj;
	D3DXVECTOR3 cameraVec = at - eye;

	D3DXVec3Normalize(&cameraVec, &cameraVec);
	D3DXVec3Normalize(&lightVec, &lightVec);

	//�f�t�H���g�̃}�e���A�����擾
	m_pDevice->GetMaterial(&matDef);
	pD3DXMat = (D3DXMATERIAL*)m_pD3DXBuffMatModel->GetBufferPointer();

	shader->vsc->SetMatrix(m_pDevice, "world", &m_mtxWorld);
	shader->vsc->SetMatrix(m_pDevice, "gWvp", &wvp);

	shader->vsc->SetFloatArray(m_pDevice, "LightDir", (float*)&lightVec, 3);
	shader->vsc->SetVector(m_pDevice, "LightDiffuse", (D3DXVECTOR4*)&lightDiffuse);
	shader->vsc->SetVector(m_pDevice, "LightDiffuse2", (D3DXVECTOR4*)&lightDiffuse2);
	shader->vsc->SetVector(m_pDevice, "LightAmbient", (D3DXVECTOR4*)&lightAmbient);
	shader->vsc->SetFloatArray(m_pDevice, "CameraVec", (float*)&cameraVec, 3);
	shader->vsc->SetFloatArray(m_pDevice, "Pos", (float*)&eye, 3);

	if (pD3DTex != NULL)
	{
		unsigned int s0 = shader->psc->GetSamplerIndex("texSampler");
		m_pDevice->SetTexture(s0, pD3DTex);
	}
	else
	{
		m_pDevice->SetTexture(0, NULL);		//�e�N�X�`���͎g��Ȃ�
	}

	m_pDevice->SetVertexShader(shader->vs);
	m_pDevice->SetPixelShader(shader->ps);
	//�}�e���A���̌������[�v
	for (int nCntMat = 0; nCntMat<(int)m_nNumMatModel; nCntMat++)
	{
		shader->vsc->SetVector(m_pDevice, "MatDiffuse", (D3DXVECTOR4*)&pD3DXMat[nCntMat].MatD3D.Diffuse);
		shader->vsc->SetVector(m_pDevice, "MatAmbient", (D3DXVECTOR4*)&pD3DXMat[nCntMat].MatD3D.Ambient);

		m_pD3DXMeshModel->DrawSubset(nCntMat);			//���f���̃p�[�c��`��
	}

	//�}�e���A�������Ƃɖ߂��I
	m_pDevice->SetMaterial(&matDef);
	m_pDevice->SetVertexShader(NULL);
	m_pDevice->SetPixelShader(NULL);
}
//=============================================================================
// ���f���ݒ�
//=============================================================================
HRESULT CModel::SetModel(const char *pFilename)
{
	char filename[256];

	LPD3DXBUFFER m_pD3DXAdjancyBuff = NULL;	// ���b�V���̗אڃ}�e���A�������i�[

	strcpy_s(filename, pFilename);

	// �w�t�@�C���̓ǂݍ���
	if(FAILED(D3DXLoadMeshFromX(filename,
								D3DXMESH_SYSTEMMEM,
								m_pDevice,
								&m_pD3DXAdjancyBuff,
								&m_pD3DXBuffMatModel,
								NULL,
								&m_nNumMatModel,
								&m_pD3DXMeshModel)))
	{
		return E_FAIL;
	}

	//�I�v�e�B�}�C�Y
	m_pD3DXMeshModel->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
		(DWORD *)m_pD3DXAdjancyBuff->GetBufferPointer(),
		NULL, NULL, NULL);//�œK�����ꂽ�אڏ��@�C���f�b�N�X�i�ʁj�@�C���f�b�N�X�i���_�j

	//�אڏ����
	m_pD3DXAdjancyBuff->Release();

	{// ���f���̒��_���W�̍ő�l�E�ŏ��l�̐ݒ�
		int nNumVertices;
		DWORD fvf,vtxSize;
		BYTE *pVertexBuffer;

		nNumVertices = m_pD3DXMeshModel->GetNumVertices();
		fvf = m_pD3DXMeshModel->GetFVF();
		vtxSize = D3DXGetFVFVertexSize( fvf );

		m_vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		m_vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);
		m_pD3DXMeshModel->LockVertexBuffer( D3DLOCK_READONLY, (void**)&pVertexBuffer );
		for(int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVertexBuffer;

			if(m_vtxMin.x > vtx.x)
			{
				m_vtxMin.x = vtx.x;
			}
			if(m_vtxMax.x < vtx.x)
			{
				m_vtxMax.x = vtx.x;
			}

			if(m_vtxMin.y > vtx.y)
			{
				m_vtxMin.y = vtx.y;
			}
			if(m_vtxMax.y < vtx.y)
			{
				m_vtxMax.y = vtx.y;
				if((int)(m_vtxMax.y + 0.01f) == (int)(m_vtxMax.y + 1.0f))
				{// �ɏ��̌덷�z��
					m_vtxMax.y = (float)((int)(m_vtxMax.y + 1.0f));
				}
			}

			if(m_vtxMin.z > vtx.z)
			{
				m_vtxMin.z = vtx.z;
			}
			if(m_vtxMax.z < vtx.z)
			{
				m_vtxMax.z = vtx.z;
			}

			pVertexBuffer += vtxSize;
		}
		m_pD3DXMeshModel->UnlockVertexBuffer();
	}

	return S_OK;
}
/////////////EOF////////////