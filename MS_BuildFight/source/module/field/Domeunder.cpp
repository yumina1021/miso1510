//=============================================================================
//
// MS_BuildFight [CDomeU.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "Domeunder.h"
#include "../etc/Camera.h"
#include "../../administer/Maneger.h"
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CDomeU :: CDomeU(int nPriority) : Cform3D(nPriority)
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CDomeU :: ~CDomeU(void)
{
}
//=============================================================================
// CDomeU����
//=============================================================================
CDomeU *CDomeU::Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CDomeU *pformDomeU;

	pformDomeU = new CDomeU();
	pformDomeU->Init(pDevice);
	pformDomeU->SetPos(pos);
	pformDomeU->SetRot(rot);

	return pformDomeU;
}
//=============================================================================
// ������
//=============================================================================
HRESULT CDomeU::Init(LPDIRECT3DDEVICE9 pDevice)
{
	m_pDevice = pDevice;

	int nNumBlockX = 50;
	int nNumBlockZ = 50;
	float nSizeBlockX = 6000;
	float nSizeBlockZ = 3000;

	m_nNumVertexIndex = SUM_INDEX(nNumBlockX, nNumBlockZ);
	m_nNumVertex = (nNumBlockX + 1)*(nNumBlockZ + 1);

	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/sky004.jpg", &m_pD3DTex);

	//�t�B�[���h�̏�����

	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//���_���̐ݒ�
	if (FAILED(m_pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*m_nNumVertex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pD3DVtxBuff,
		NULL)))
	{
		return E_FAIL;
	}
	if (FAILED(m_pDevice->CreateIndexBuffer(sizeof(WORD)*m_nNumVertexIndex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pD3DIndexBuff,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;

	float fBaseAngle = -(360.0f / nNumBlockX)*(D3DX_PI / 180);
	float fBaseAngleSp = -(90.0f / nNumBlockZ)*(D3DX_PI / 180);

	//���b�N
	m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//����̒��_���珇�ɍ��W��ۑ�
	for (int z = 0, num = 0; z < nNumBlockZ + 1; z++)
	{
		for (int x = 0; x < nNumBlockX + 1; x++)
		{
			pVtx[num].vtx = D3DXVECTOR3(cosf(fBaseAngle*x)*nSizeBlockX* cosf(fBaseAngleSp*z),
				sinf(fBaseAngleSp*z)*nSizeBlockZ,
				sinf(fBaseAngle*x)*nSizeBlockX* cosf(fBaseAngleSp*z));
			pVtx[num].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[num].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[num].tex = D3DXVECTOR2((float)x / nNumBlockX, (float)z / nNumBlockZ);
			num++;
		}
	}

	//�A�����b�N
	m_pD3DVtxBuff->Unlock();

	WORD *pIndex;

	m_pD3DIndexBuff->Lock(0, 0, (void**)&pIndex, 0);

	int loopx = 0;
	int VtxNo = 0;
	int check = 0;

	for (int z = 0; z < nNumBlockZ; z++)
	{
		//�E���܂�Ԃ��n�_�ł̃C���f�b�N�X�ۑ�
		if (z != 0)
		{
			loopx = 0;
			check = (z*(nNumBlockX + 1)) + (((loopx + 3) % 2)*(nNumBlockX + 1) + (loopx / 2));
			pIndex[VtxNo] = (z*(nNumBlockX + 1)) + (((loopx + 1) % 2)*(nNumBlockX + 1) + (loopx / 2));
			VtxNo++;
		}
		//���_�C���f�b�N�X�ۑ����[�v
		for (loopx = 0; loopx < (nNumBlockX + 1) * 2; loopx++)
		{
			check = (z*(nNumBlockX + 1)) + (((loopx + 3) % 2)*(nNumBlockX + 1) + (loopx / 2));
			pIndex[VtxNo] = (z*(nNumBlockX + 1)) + (((loopx + 1) % 2)*(nNumBlockX + 1) + (loopx / 2));
			VtxNo++;
		}
		if (z == nNumBlockX - 1)
		{
			break;
		}
		//����܂�Ԃ��n�_�C���f�b�N�X�ۑ�
		pIndex[VtxNo] = pIndex[VtxNo - 1];
		VtxNo++;
	}

	m_pD3DIndexBuff->Unlock();

	HRESULT hr;
	LPD3DXBUFFER err;
	LPD3DXBUFFER code;

	//�s�N�Z���V�F�[�_�[�p�ɕϊ�
	hr = D3DXCompileShaderFromFile("source/shader/basicPS.hlsl", NULL, NULL, "PS", "ps_2_0", 0, &code, &err, &_psc);

	if (FAILED(hr))
	{
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		err->Release();
		return false;
	}
	//�V�F�[�_�[�̓o�^
	hr = pDevice->CreatePixelShader((DWORD*)code->GetBufferPointer(), &_ps);

	if (FAILED(hr))
	{
		MessageBox(NULL, "FAILED", "CreatePixelShader", MB_OK);
		return false;
	}

	//�o�[�e�b�N�X�V�F�[�_�[�p�ɕϊ�1
	hr = D3DXCompileShaderFromFile("source/shader/basicVS.hlsl", NULL, NULL, "VS", "vs_2_0", 0, &code, &err, &_vsc);
	if (FAILED(hr))
	{
		MessageBox(NULL, (LPCSTR)err->GetBufferPointer(), "D3DXCompileShaderFromFile", MB_OK);
		err->Release();
		return false;
	}
	//�V�F�[�_�[�̓o�^
	hr = pDevice->CreateVertexShader((DWORD*)code->GetBufferPointer(), &_vs);
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
void CDomeU :: Uninit(void)
{
	//�l�X�ȃI�u�W�F�N�g�̏I���i�J���j����

	if(m_pD3DTex!=NULL)
	{
		m_pD3DTex->Release();
		m_pD3DTex=NULL;
	}
	if(m_pD3DVtxBuff!=NULL)
	{
		m_pD3DVtxBuff->Release();
		m_pD3DVtxBuff=NULL;
	}
	if(m_pD3DIndexBuff!=NULL)
	{
		m_pD3DIndexBuff->Release();
		m_pD3DIndexBuff = NULL;
	}


	if (_ps != NULL)	_ps->Release();
	if (_psc != NULL)	_psc->Release();
	if (_vs != NULL)	_vs->Release();
	if (_vsc != NULL)	_vsc->Release();
	Cform::Release();
}
//=============================================================================
// �X�V
//=============================================================================
void CDomeU :: Update(void)
{

}
//=============================================================================
// �`��
//=============================================================================
void CDomeU :: Draw(void)
{

	LPDIRECT3DDEVICE9 pDevice = CManager::GetDevice();

	D3DXMATRIX  mtxWorld;
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
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

	CCamera *pCamera;
	// �J�������擾
	pCamera = CManager::GetCamera();

	eye = pCamera->GetPosP();
	at = pCamera->GetPosR();
	up = pCamera->GetVecUp();

	pDevice->GetTransform(D3DTS_WORLD, &mtxParent);

	//���[���h�s��
	D3DXMatrixIdentity(&m_mtxWorld);

	D3DXMatrixRotationYawPitchRoll(&rot, m_Rot.y, m_Rot.x, m_Rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &rot);

	D3DXMatrixTranslation(&pos, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &pos);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	D3DXMatrixInverse(&invWorld, NULL, &m_mtxWorld);
	D3DXVec3TransformCoord(&lightVec, &lightVec, &invWorld);

	D3DXMatrixLookAtLH(&view, &eye, &at, &up);

	D3DXMatrixPerspectiveFovLH(&proj, D3DXToRadian(45), 960.0f / 540.0f, 10.0f, 100000.0f);

	D3DXMATRIX wvp = m_mtxWorld*view*proj;
	D3DXVECTOR3 cameraVec = at - eye;

	D3DXVec3Normalize(&cameraVec, &cameraVec);
	D3DXVec3Normalize(&lightVec, &lightVec);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetStreamSource(0, m_pD3DVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetIndices(m_pD3DIndexBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	m_pDevice->SetFVF(FVF_VERTEX_3D);

	_vsc->SetMatrix(pDevice, "world", &m_mtxWorld);
	_vsc->SetMatrix(pDevice, "gWvp", &wvp);

	_vsc->SetFloatArray(pDevice, "LightDir", (float*)&lightVec, 3);
	_vsc->SetVector(pDevice, "LightDiffuse", (D3DXVECTOR4*)&lightDiffuse);
	_vsc->SetVector(pDevice, "LightDiffuse2", (D3DXVECTOR4*)&lightDiffuse2);
	_vsc->SetVector(pDevice, "LightAmbient", (D3DXVECTOR4*)&lightAmbient);
	_vsc->SetFloatArray(pDevice, "CameraVec", (float*)&cameraVec, 3);
	_vsc->SetFloatArray(pDevice, "Pos", (float*)&eye, 3);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pD3DTex);

	unsigned int s0 = _psc->GetSamplerIndex("texSampler");
	pDevice->SetTexture(s0, m_pD3DTex);
	pDevice->SetVertexShader(_vs);

	pDevice->SetPixelShader(_ps);

	//�|���S���̕`��
	m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,m_nNumVertex,0,m_nNumVertexIndex-2);


}
/////////////EOF////////////