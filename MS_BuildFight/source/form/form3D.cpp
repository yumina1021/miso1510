//=============================================================================
//
// MS_BuildFight [Cform3D.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "form3D.h"
#include "../module/field/meshfielddata.h"
#include "../module/etc/Camera.h"
#include "../administer/Maneger.h"
#include "../exten_common.h"
//=============================================================================
// �R���X�g���N�^
//=============================================================================
Cform3D :: Cform3D(int nPriority) : Cform(OBJTYPE_3D,nPriority)
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
Cform3D :: ~Cform3D(void)
{
}
//=============================================================================
// Cform3D����
//=============================================================================
Cform3D *Cform3D::Create(LPDIRECT3DDEVICE9 pDevice,LPSTR pTexName,D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	Cform3D *pform3D;

	pform3D = new Cform3D();
	pform3D->Init(pDevice,pTexName);
	pform3D->SetPos(pos);

	return pform3D;
}
//=============================================================================
// Cform3D����
//=============================================================================
Cform3D *Cform3D::Create(LPDIRECT3DDEVICE9 pDevice, LPSTR pTexName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float width, float height)
{
	Cform3D *pform3D;

	pform3D = new Cform3D();
	pform3D->Init(pDevice, pTexName, width, height);
	pform3D->SetPos(pos);
	pform3D->SetRot(rot);

	return pform3D;
}
//=============================================================================
// ������
//=============================================================================
HRESULT Cform3D :: Init(LPDIRECT3DDEVICE9 pDevice,LPSTR pTexName)
{
	m_pDevice=pDevice;

	int nNumBlockX=1;
	int nNumBlockZ=1;


	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(m_pDevice,pTexName,&m_pD3DTex);

	//�t�B�[���h�̏�����
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl = D3DXVECTOR3(1.0f,1.0f,1.0f);

	m_fLength = sqrtf((float)(((TEXTURE_SIZE_X / 2) * (TEXTURE_SIZE_X / 2)) + ((TEXTURE_SIZE_Y / 2) * (TEXTURE_SIZE_Y / 2))));
	m_fAngle = atan2f((TEXTURE_SIZE_X / 2), (TEXTURE_SIZE_Y / 2));

	//���_���̐ݒ�
	if(FAILED(m_pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)* NUM_VERTEX,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_3D,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuff,
											NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].vtx.x = -sinf(m_fAngle) * m_fLength;
	pVtx[0].vtx.y = 0.0f;
	pVtx[0].vtx.z = -cosf(m_fAngle) * m_fLength;

	pVtx[1].vtx.x = -sinf(m_fAngle) * m_fLength;
	pVtx[1].vtx.y = 0.0f;
	pVtx[1].vtx.z = cosf(m_fAngle) * m_fLength;

	pVtx[2].vtx.x = sinf(m_fAngle) * m_fLength;
	pVtx[2].vtx.y = 0.0f;
	pVtx[2].vtx.z = -cosf(m_fAngle) * m_fLength;

	pVtx[3].vtx.x = sinf(m_fAngle) * m_fLength;
	pVtx[3].vtx.y = 0.0f;
	pVtx[3].vtx.z = cosf(m_fAngle) * m_fLength;

	// ���_���W�̐ݒ�
	D3DXVECTOR3 vec0, vec1;
	D3DXVECTOR3 nor0, nor1;

	vec0 = pVtx[1].vtx - pVtx[0].vtx;
	vec1 = pVtx[2].vtx - pVtx[1].vtx;

	D3DXVec3Cross(&nor0, &vec0, &vec1);

	D3DXVec3Normalize(&nor0, &nor0);

	vec0 = pVtx[2].vtx - pVtx[1].vtx;
	vec1 = pVtx[2].vtx - pVtx[3].vtx;

	D3DXVec3Cross(&nor1, &vec0, &vec1);

	D3DXVec3Normalize(&nor1, &nor1);

	pVtx[0].nor = nor0;
	pVtx[1].nor.x = (nor0.x + nor1.x) / 2;
	pVtx[1].nor.y = (nor0.y + nor1.y) / 2;
	pVtx[1].nor.z = (nor0.z + nor1.z) / 2;
	pVtx[2].nor.x = (nor0.x + nor1.x) / 2;
	pVtx[2].nor.y = (nor0.y + nor1.y) / 2;
	pVtx[2].nor.z = (nor0.z + nor1.z) / 2;
	pVtx[3].nor = nor1;

	// ���ˌ��̐ݒ�
	pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// ���_�f�[�^���A�����b�N����
	m_pD3DVtxBuff->Unlock();

	//�s�N�Z���V�F�[�_�[�p�ɕϊ�1
	Create_PS("source/shader/basicPS.hlsl", "PS_TEXDIFFUSE", &m_shader.ps, &m_shader.psc, m_pDevice);

	//�o�[�e�b�N�X�V�F�[�_�[�p�ɕϊ�1
	Create_VS("source/shader/basicVS.hlsl", "VS", &m_shader.vs, &m_shader.vsc, m_pDevice);

	return S_OK;
}


//=============================================================================
// ������
//=============================================================================
HRESULT Cform3D::Init(LPDIRECT3DDEVICE9 pDevice, LPSTR pTexName, float fTexSizeX, float fTexSizeY)
{
	m_pDevice = pDevice;

	int nNumBlockX = 1;
	int nNumBlockZ = 1;


	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(m_pDevice, pTexName, &m_pD3DTex);

	//�t�B�[���h�̏�����
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_fLength = sqrtf((float)(((fTexSizeX / 2) * (fTexSizeX / 2)) + ((fTexSizeY / 2) * (fTexSizeY / 2))));
	m_fAngle = atan2f((fTexSizeX / 2), (fTexSizeY / 2));

	//���_���̐ݒ�
	if (FAILED(m_pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)* NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pD3DVtxBuff,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].vtx.x = -sinf(m_fAngle) * m_fLength;
	pVtx[0].vtx.y = 0.0f;
	pVtx[0].vtx.z = cosf(m_fAngle) * m_fLength;

	pVtx[1].vtx.x = sinf(m_fAngle) * m_fLength;
	pVtx[1].vtx.y = 0.0f;
	pVtx[1].vtx.z = cosf(m_fAngle) * m_fLength;

	pVtx[2].vtx.x = -sinf(m_fAngle) * m_fLength;
	pVtx[2].vtx.y = 0.0f;
	pVtx[2].vtx.z = -cosf(m_fAngle) * m_fLength;

	pVtx[3].vtx.x = sinf(m_fAngle) * m_fLength;
	pVtx[3].vtx.y = 0.0f;
	pVtx[3].vtx.z = -cosf(m_fAngle) * m_fLength;

	pVtx[0].nor.x = 0.0f;
	pVtx[0].nor.y = 1.0f;
	pVtx[0].nor.z = 0.0f;
	pVtx[1].nor.x = 0.0f;
	pVtx[1].nor.y = 1.0f;
	pVtx[1].nor.z = 0.0f;
	pVtx[2].nor.x = 0.0f;
	pVtx[2].nor.y = 1.0f;
	pVtx[2].nor.z = 0.0f;
	pVtx[3].nor.x = 0.0f;
	pVtx[3].nor.y = 1.0f;
	pVtx[3].nor.z = 0.0f;

	// ���ˌ��̐ݒ�
	pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// ���_�f�[�^���A�����b�N����
	m_pD3DVtxBuff->Unlock();

	//�s�N�Z���V�F�[�_�[�p�ɕϊ�1
	Create_PS("source/shader/basicPS.hlsl", "PS_TEXDIFFUSE", &m_shader.ps, &m_shader.psc, m_pDevice);

	//�o�[�e�b�N�X�V�F�[�_�[�p�ɕϊ�1
	Create_VS("source/shader/basicVS.hlsl", "VS", &m_shader.vs, &m_shader.vsc, m_pDevice);

	m_pColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	CCamera* pCamera = CManager::GetCamera();

	//�r���[�s��
	eye = pCamera->GetPosP();
	at = pCamera->GetPosR();
	up = pCamera->GetVecUp();

	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void Cform3D :: Uninit(void)
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

	if (m_shader.ps != NULL)m_shader.ps->Release();
	if (m_shader.psc != NULL)m_shader.psc->Release();
	if (m_shader.vs != NULL)m_shader.vs->Release();
	if (m_shader.vsc != NULL)m_shader.vsc->Release();

	Cform::Release();
}
//=============================================================================
// �X�V
//=============================================================================
void Cform3D :: Update(void)
{
}
//=============================================================================
// �`��
//=============================================================================
void Cform3D :: Draw(void)
{
	D3DXMATRIX  mtxWorld;
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, view, proj;

	//�}�g���b�N�X�̐ݒ�
	D3DXMatrixIdentity(&mtxWorld);

	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_Rot.y,m_Rot.x,m_Rot.z);
	D3DXMatrixMultiply(&mtxWorld,&mtxWorld,&mtxRot);

	D3DXMatrixTranslation(&mtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);
	D3DXMatrixMultiply(&mtxWorld,&mtxWorld,&mtxTranslate);

	D3DXMatrixLookAtLH(&view, &eye, &at, &up);

	D3DXMatrixPerspectiveFovLH(&proj, D3DXToRadian(45), 960.0f / 540.0f, 10.0f, 100000.0f);

	D3DXMATRIX wvp = mtxWorld*view*proj;

	m_shader.vsc->SetMatrix(m_pDevice, "world", &mtxWorld);
	m_shader.vsc->SetMatrix(m_pDevice, "gWvp", &wvp);

	unsigned int s0 = m_shader.psc->GetSamplerIndex("texSampler");
	m_pDevice->SetTexture(s0, m_pD3DTex);

	m_shader.vsc->SetVector(m_pDevice, "MatDiffuse", (D3DXVECTOR4*)&m_pColor);

	m_pDevice->SetVertexShader(m_shader.vs);
	m_pDevice->SetPixelShader(m_shader.ps);

	//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	m_pDevice->SetStreamSource(0,m_pD3DVtxBuff,0,sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	m_pDevice->SetFVF(FVF_VERTEX_3D);

	//�|���S���̕`��
	m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	m_pDevice->SetVertexShader(nullptr);

	m_pDevice->SetPixelShader(nullptr);
}
//=============================================================================
// �J���[�ݒ�
//=============================================================================
void Cform3D::SetDiffuse(float r, float g, float b, float a)
{
	VERTEX_3D *pVtx;

	//���b�N
	m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���̐ݒ�
	pVtx[0].diffuse = D3DXCOLOR(r, g, b, a);
	pVtx[1].diffuse = D3DXCOLOR(r, g, b, a);
	pVtx[2].diffuse = D3DXCOLOR(r, g, b, a);
	pVtx[3].diffuse = D3DXCOLOR(r, g, b, a);

	//�A�����b�N
	m_pD3DVtxBuff->Unlock();
}
//=============================================================================
// �n�ʂ̍������擾
//=============================================================================
float Cform3D::GetHeight(D3DXVECTOR3 pos, D3DXVECTOR3 *pNormal)
{
	float fHeight = 0.0f;
	VERTEX_3D *pVtx;
	bool bFinish = false;
	VERTEX_3D *pVtx0, *pVtx1, *pVtx2;
	D3DXVECTOR3 vec0, vec1;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���E���ɐݒ�
	pVtx0 = &pVtx[0];
	pVtx1 = &pVtx[1];
	pVtx2 = &pVtx[2];

	vec0 = pVtx1->vtx - pVtx0->vtx;
	vec1 = pos - pVtx0->vtx;
	if(((vec0.z * vec1.x) - (vec0.x * vec1.z)) >= 0.0f)
	{
		vec0 = pVtx2->vtx - pVtx1->vtx;
		vec1 = pos - pVtx1->vtx;
		if(((vec0.z * vec1.x) - (vec0.x * vec1.z)) >= 0.0f)
		{
			vec0 = pVtx0->vtx - pVtx2->vtx;
			vec1 = pos - pVtx2->vtx;
			if(((vec0.z * vec1.x) - (vec0.x * vec1.z)) >= 0.0f)
			{
				// �|���S����̍������擾
				fHeight = GetHeightPolygon(pVtx0->vtx, pVtx1->vtx, pVtx2->vtx, pos, pNormal);
				//��������Ă�
				bFinish = true;
			}
		}
	}
	//��������ĂȂ��ꍇ
	if(bFinish == false)
	{
		// ���_���E���ɐݒ�
		pVtx0 = &pVtx[1];
		pVtx1 = &pVtx[3];
		pVtx2 = &pVtx[2];

		vec0 = pVtx1->vtx - pVtx0->vtx;
		vec1 = pos - pVtx0->vtx;
		if(((vec0.z * vec1.x) - (vec0.x * vec1.z)) >= 0.0f)
		{
			vec0 = pVtx2->vtx - pVtx1->vtx;
			vec1 = pos - pVtx1->vtx;
			if(((vec0.z * vec1.x) - (vec0.x * vec1.z)) >= 0.0f)
			{
				vec0 = pVtx0->vtx - pVtx2->vtx;
				vec1 = pos - pVtx2->vtx;
				if(((vec0.z * vec1.x) - (vec0.x * vec1.z)) >= 0.0f)
				{
					// �|���S����̍������擾
					fHeight = GetHeightPolygon(pVtx0->vtx, pVtx1->vtx, pVtx2->vtx, pos, pNormal);

					bFinish = true;
				}
			}
		}
	}

	// ���_�f�[�^���A�����b�N����
	m_pD3DVtxBuff->Unlock();

	if(bFinish == true)
	{
		//CDebugProc::Print("�n�ʂ̍���:%f\n", fHeight);
	}

	return fHeight;
}
//=============================================================================
// �Y������|���S����ł̍������Z�o
//=============================================================================
float Cform3D::GetHeightPolygon(const D3DXVECTOR3& P0, const D3DXVECTOR3& P1, const D3DXVECTOR3& P2,
										D3DXVECTOR3 pos, D3DXVECTOR3 *pNormal)
{
	D3DXVECTOR3 vec0,vec1;
	D3DXVECTOR3 normal;
	float fHeight;

	vec0 = P1 - P0;
	vec1 = P2 - P0;

	// �Q�̐����̊O�ς���@�������߂�
	D3DXVec3Cross(&normal, &vec1, &vec0);

	// ���K��
	D3DXVec3Normalize(&normal, &normal);

	if(normal.y == 0.0f)
	{// �@���������Ȃ疳��
		return 0.0f;
	}

	// �������Z�o [("�C�ӂ̒��_"����"�ړI�̈ʒu"�ւ̃x�N�g��)�E�@���x�N�g�� �� �O]
	fHeight = P0.y - ((normal.x * (pos.x - P0.x) + normal.z * (pos.z - P0.z)) / normal.y);

	if(pNormal)
	{
		*pNormal = normal;
	}

	return fHeight;
}
/////////////EOF////////////