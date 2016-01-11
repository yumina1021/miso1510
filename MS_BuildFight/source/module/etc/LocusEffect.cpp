//=============================================================================
//
// MS_BuildFight [LocusEffect.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "LocusEffect.h"
#include "Camera.h"
#include "../../exten_common.h"
#include "../../administer/Maneger.h"
#include "../../administer/Texture.h"
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLocusEffect :: CLocusEffect(OBJTYPE objtype,int nPriority) : Cform(objtype,nPriority)
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLocusEffect :: ~CLocusEffect(void)
{
}
//=============================================================================
// CLocusEffect����
//=============================================================================
CLocusEffect *CLocusEffect::Create(LPDIRECT3DDEVICE9 pDevice,int pTexName,D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CLocusEffect *pLocusEffect;

	pLocusEffect = new CLocusEffect();
	pLocusEffect->Init(pDevice,pTexName);
	//pLocusEffect->SetPos(pos);

	return pLocusEffect;
}
//=============================================================================
// ������
//=============================================================================
HRESULT CLocusEffect :: Init(LPDIRECT3DDEVICE9 pDevice,int pTexName)
{
	m_pDevice=pDevice;

	int nNumBlockX=1;
	int nNumBlockZ=1;

	//�e�N�X�`���̐ݒ�
	m_texid = pTexName;
	//D3DXCreateTextureFromFile(m_pDevice,"data/TEXTURE/toumei2.png",&m_pD3DTex);

	//�t�B�[���h�̏�����
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl = D3DXVECTOR3(1.0f,1.0f,1.0f);

	m_fLength = sqrtf((float)(((TEXTURE_SIZE_X / 2) * (TEXTURE_SIZE_X / 2)) + ((TEXTURE_SIZE_Y / 2) * (TEXTURE_SIZE_Y / 2))));
	m_fAngle = atan2f((TEXTURE_SIZE_X / 2), (TEXTURE_SIZE_Y / 2));

	//���_���̐ݒ�
	if(FAILED(m_pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)* 2 * BUFFER_MAX,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_3D,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuff,
											NULL)))
	{
		return E_FAIL;
	}

	for(int i=0;i<BUFFER_MAX;i++)
	{
		PosBuff[i]=D3DXVECTOR3(0.0f,0.0f,0.0f);
		ColorBuff[i]=D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	}

	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for(int i=0;i<BUFFER_MAX;i++)
	{
		pVtx[i].vtx=PosBuff[i];
		pVtx[i].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
		pVtx[i].diffuse= ColorBuff[i];
		pVtx[i].tex = D3DXVECTOR2(0,0);
	}

	// ���_�f�[�^���A�����b�N����
	m_pD3DVtxBuff->Unlock();

	m_bFlag = false;

	//�s�N�Z���V�F�[�_�[�p�ɕϊ�1
	Create_PS("source/shader/basicPS.hlsl", "PS", &shaderSet.ps, &shaderSet.psc, m_pDevice);

	//�o�[�e�b�N�X�V�F�[�_�[�p�ɕϊ�1
	Create_VS("source/shader/basicVS.hlsl", "VS", &shaderSet.vs, &shaderSet.vsc, m_pDevice);

	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CLocusEffect :: Uninit(void)
{
	//�l�X�ȃI�u�W�F�N�g�̏I���i�J���j����

	//if(m_pD3DTex!=NULL)
	//{
	//	m_pD3DTex->Release();
	//	m_pD3DTex=NULL;
	//}
	if(m_pD3DVtxBuff!=NULL)
	{
		m_pD3DVtxBuff->Release();
		m_pD3DVtxBuff=NULL;
	}
	if (shaderSet.ps != NULL)	shaderSet.ps->Release();
	if (shaderSet.psc != NULL)	shaderSet.psc->Release();
	if (shaderSet.vs != NULL)	shaderSet.vs->Release();
	if (shaderSet.vsc != NULL)	shaderSet.vsc->Release();

	Cform::Release();
}
//=============================================================================
// �X�V
//=============================================================================
void CLocusEffect :: Update(void)
{
	VERTEX_3D *pVtx;

	if (m_bFlag)
	{
		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int i = 0; i < BUFFER_MAX / 2; i++)
		{
			pVtx[i * 2].vtx = PosBuff[i * 2];
			pVtx[i * 2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[i * 2].diffuse = ColorBuff[i * 2];
			pVtx[i * 2].tex = D3DXVECTOR2(0, 0);

			pVtx[i * 2 + 1].vtx = PosBuff[i * 2 + 1];
			pVtx[i * 2 + 1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[i * 2 + 1].diffuse = ColorBuff[i * 2 + 1];
			pVtx[i * 2 + 1].tex = D3DXVECTOR2(1, 0);
		}

		// ���_�f�[�^���A�����b�N����
		m_pD3DVtxBuff->Unlock();
	}
}
//=============================================================================
// �`��
//=============================================================================
void CLocusEffect :: Draw(void)
{
	if (m_bFlag)
	{
		CCamera* pCamera = CManager::GetCamera();

		D3DXMATRIX view, proj;
		//�r���[�s��
		D3DXVECTOR3 eye(0.0f, 50.0f, -100.0f);
		D3DXVECTOR3 at(0.0f, 20.0f, 0.0f);
		D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

		eye = pCamera->GetPosP();
		at = pCamera->GetPosR();
		up = pCamera->GetVecUp();

		m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		// SRC(���ꂩ��`�悷�鑤) + DEST(���ɕ`�悳��Ă鑤)
		m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		// SRC�𔼓������������
		m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		// DEST�����̂܂ܕ`�悷���
		m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

		//�}�g���b�N�X�̐ݒ�
		D3DXMatrixIdentity(&mtxWorld);
		D3DXMatrixScaling(&mtxScl, m_Scl.x, m_Scl.y, m_Scl.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		D3DXMatrixTranslation(&mtxTranslate, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		D3DXMatrixLookAtLH(&view, &eye, &at, &up);

		D3DXMatrixPerspectiveFovLH(&proj, D3DXToRadian(45), 960.0f / 540.0f, 10.0f, 100000.0f);

		D3DXMATRIX wvp = mtxWorld*view*proj;

		shaderSet.vsc->SetMatrix(m_pDevice, "world", &mtxWorld);
		shaderSet.vsc->SetMatrix(m_pDevice, "gWvp", &wvp);

		shaderSet.vsc->SetVector(m_pDevice, "MatDiffuse", &D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));

		m_pDevice->SetVertexShader(shaderSet.vs);
		m_pDevice->SetPixelShader(shaderSet.ps);

		//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
		m_pDevice->SetStreamSource(0, m_pD3DVtxBuff, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		m_pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		m_pDevice->SetTexture(0, NULL);

		unsigned int s0 = shaderSet.psc->GetSamplerIndex("texSampler");
		m_pDevice->SetTexture(s0, CTexture::GetTex(m_texid));

		//�|���S���̕`��
		m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 120);

		m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

		m_pDevice->SetVertexShader(NULL);
		m_pDevice->SetPixelShader(NULL);
	}
}

//=============================================================================
// �Z�b�g
//=============================================================================
//void CLocusEffect :: SetPosBuffer(D3DXVECTOR3 pos1,D3DXVECTOR3 pos2,D3DXMATRIX mtxWorld)
void CLocusEffect :: SetPosBuffer(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 posA=pos;

	//D3DXVec3TransformCoord(&posA,&pos1,&mtxWorld);
	//D3DXVec3TransformCoord(&posB,&pos2,&mtxWorld);

	for(int i=119;i>0;i--)
	{
		PosBuff[i*2+1]=PosBuff[((i-1)*2)+1];
		PosBuff[i*2]=PosBuff[(i-1)*2];

		if(ColorBuff[((i-1)*2)].a>0.0f)
		{
			//ColorBuff[(i-1)*2].a -= 0.01f;
		}else
		{
			//ColorBuff[(i-1)*2].a = 0.0f;
		}
		
		if(ColorBuff[((i-1)*2)+1].a>0.0f)
		{
			//ColorBuff[((i-1)*2)+1].a -= 0.03f;
		}else
		{
			//ColorBuff[((i-1)*2)+1].a = 0.0f;
		}

		ColorBuff[i*2+1]=ColorBuff[((i-1)*2)+1];
		ColorBuff[i*2]=ColorBuff[(i-1)*2];
	}

	PosBuff[0]=D3DXVECTOR3(posA.x-18.0f,posA.y,posA.z);
	PosBuff[1]=D3DXVECTOR3(posA.x+18.0f,posA.y,posA.z);

	ColorBuff[0]=D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	ColorBuff[1]=D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

}
/////////////EOF////////////