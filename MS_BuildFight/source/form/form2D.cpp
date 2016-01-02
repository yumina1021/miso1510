//=============================================================================
//
// MS_BuildFight [Cform2D.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "form2D.h"
#include "../administer/Texture.h"
//=============================================================================
// �R���X�g���N�^
//=============================================================================
Cform2D :: Cform2D(OBJTYPE objtype,int nPriority) : Cform(objtype,nPriority)
{
	//�|���S���̉�]�l������
	m_Rot.z=0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
Cform2D :: ~Cform2D(void)
{
}
//=============================================================================
// Cform2D����
//=============================================================================
Cform2D *Cform2D::Create(LPDIRECT3DDEVICE9 pDevice, int pFileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float width, float height)
{
	Cform2D *pform2D;

	pform2D = new Cform2D();
	pform2D->Init(pDevice, pFileName, pos, rot, width, height);

	return pform2D;
}
//=============================================================================
// ������
//=============================================================================
HRESULT Cform2D :: Init(LPDIRECT3DDEVICE9 pDevice,int pFileName,D3DXVECTOR3 pos,D3DXVECTOR3 rot,float width,float height)
{
	m_pDevice=pDevice;
	m_texid = pFileName;
	//if(pFileName!=NULL)
	//{
	//	//�e�N�X�`���̓ǂݍ���
	//	D3DXCreateTextureFromFile(m_pDevice,pFileName,&m_pD3DTex);
	//}else
	//{
	//	m_pD3DTex=NULL;
	//}

	//���_�o�b�t�@�̐���(�������̊m�F)
	if(FAILED(m_pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*POINT_MAX,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_2D,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuff,
											NULL)))
	{
		return E_FAIL;
	}

	m_Pos=pos;
	m_Rot=rot;

	m_fWidth = width;
	m_fHeight = height;

	//�|���S���Ίp���̒���������
	m_fLength = sqrtf(((m_fWidth / 2)*(m_fWidth / 2)) + ((m_fHeight / 2)*(m_fHeight / 2)));

	//�|���S���Ίp���̊p�x������
	m_fAngle = atan2f((m_fWidth / 2), (m_fHeight / 2));

	D3DXVECTOR3 Setpos[POINT_MAX];					//�|���S���̈ʒu
	
	//��]
	Setpos[0].x = m_Pos.x + (sin(-m_Rot.z - m_fAngle)*m_fLength);
	Setpos[0].y = m_Pos.y - (cos(-m_Rot.z - m_fAngle)*m_fLength);
	Setpos[1].x = m_Pos.x + (sin(-m_Rot.z + m_fAngle)*m_fLength);
	Setpos[1].y = m_Pos.y - (cos(-m_Rot.z + m_fAngle)*m_fLength);
	Setpos[2].x = m_Pos.x + (sin(m_Rot.z - m_fAngle)*m_fLength);
	Setpos[2].y = m_Pos.y + (cos(m_Rot.z - m_fAngle)*m_fLength);
	Setpos[3].x = m_Pos.x + (sin(m_Rot.z + m_fAngle)*m_fLength);
	Setpos[3].y = m_Pos.y + (cos(m_Rot.z + m_fAngle)*m_fLength);

	VERTEX_2D *pVtx;

	//���b�N
	m_pD3DVtxBuff->Lock(0,0,(void**)&pVtx,0);

	//�|���S���̐ݒ�

	pVtx[0].vtx=D3DXVECTOR3(Setpos[0].x,Setpos[0].y,0.0f);//x,y�̏�
	pVtx[1].vtx=D3DXVECTOR3(Setpos[1].x,Setpos[1].y,0.0f);
	pVtx[2].vtx=D3DXVECTOR3(Setpos[2].x,Setpos[2].y,0.0f);
	pVtx[3].vtx=D3DXVECTOR3(Setpos[3].x,Setpos[3].y,0.0f);

	pVtx[0].hrw=1.0f;//1.0f�Œ�
	pVtx[1].hrw=1.0f;
	pVtx[2].hrw=1.0f;
	pVtx[3].hrw=1.0f;

	pVtx[0].diffuse = D3DCOLOR_RGBA(255,255,255,255);//�F�͔�
	pVtx[1].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[2].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[3].diffuse = D3DCOLOR_RGBA(255,255,255,255);

	pVtx[0].tex = D3DXVECTOR2(0,0);//�摜��UV�l�@U,V�̏�
	pVtx[1].tex = D3DXVECTOR2(1,0);
	pVtx[2].tex = D3DXVECTOR2(0,1);
	pVtx[3].tex = D3DXVECTOR2(1,1);

	//�A�����b�N
	m_pD3DVtxBuff->Unlock();

	return S_OK;
}
//=============================================================================
// ������
//=============================================================================
//=============================================================================
// �I��
//=============================================================================
void Cform2D :: Uninit(void)
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
	Cform::Release();
}
//=============================================================================
// �I��
//=============================================================================
void Cform2D::Uninit2(void)
{
	//�l�X�ȃI�u�W�F�N�g�̏I���i�J���j����
	if (m_pD3DVtxBuff != NULL)
	{
		m_pD3DVtxBuff->Release();
		m_pD3DVtxBuff = NULL;
	}
	Cform::Release();
}
//=============================================================================
// �X�V
//=============================================================================
void Cform2D :: Update(void)
{
	D3DXVECTOR3 Setpos[POINT_MAX];					//�|���S���̈ʒu
	
	//��]
	Setpos[0].x = m_Pos.x + (sin(-m_Rot.z - m_fAngle)*m_fLength);
	Setpos[0].y = m_Pos.y - (cos(-m_Rot.z - m_fAngle)*m_fLength);
	Setpos[1].x = m_Pos.x + (sin(-m_Rot.z + m_fAngle)*m_fLength);
	Setpos[1].y = m_Pos.y - (cos(-m_Rot.z + m_fAngle)*m_fLength);
	Setpos[2].x = m_Pos.x + (sin(m_Rot.z - m_fAngle)*m_fLength);
	Setpos[2].y = m_Pos.y + (cos(m_Rot.z - m_fAngle)*m_fLength);
	Setpos[3].x = m_Pos.x + (sin(m_Rot.z + m_fAngle)*m_fLength);
	Setpos[3].y = m_Pos.y + (cos(m_Rot.z + m_fAngle)*m_fLength);

	VERTEX_2D *pVtx;

	//���b�N
	m_pD3DVtxBuff->Lock(0,0,(void**)&pVtx,0);
	//�|���S���̐ݒ�

	pVtx[0].vtx=D3DXVECTOR3(Setpos[0].x,Setpos[0].y,0.0f);//x,y�̏�
	pVtx[1].vtx=D3DXVECTOR3(Setpos[1].x,Setpos[1].y,0.0f);
	pVtx[2].vtx=D3DXVECTOR3(Setpos[2].x,Setpos[2].y,0.0f);
	pVtx[3].vtx=D3DXVECTOR3(Setpos[3].x,Setpos[3].y,0.0f);

	//�A�����b�N
	m_pD3DVtxBuff->Unlock();
}
//=============================================================================
// �`��
//=============================================================================
void Cform2D :: Draw(void)
{
	//m_pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	//m_pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);

	//�l�X�ȃI�u�W�F�N�g�̕`�揈��
	m_pDevice->SetStreamSource(0,m_pD3DVtxBuff,0,sizeof(VERTEX_2D));

	if (m_texid != -1)
	{
		//�e�N�X�`���̐ݒ�
		m_pDevice->SetTexture(0, CTexture::GetTex(m_texid));
	}else
	{
		//�e�N�X�`���̐ݒ�
		m_pDevice->SetTexture(0,NULL);
	}

	//���_�t�H�[�}�b�g�̕`��
	m_pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

	//m_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	//m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
}

void Cform2D :: SetDiffuse(float r,float g,float b,float a)
{
	VERTEX_2D *pVtx;

	//���b�N
	m_pD3DVtxBuff->Lock(0,0,(void**)&pVtx,0);

	//�|���S���̐ݒ�
	pVtx[0].diffuse = D3DXCOLOR(r,g,b,a);
	pVtx[1].diffuse = D3DXCOLOR(r,g,b,a);
	pVtx[2].diffuse = D3DXCOLOR(r,g,b,a);
	pVtx[3].diffuse = D3DXCOLOR(r,g,b,a);

	//�A�����b�N
	m_pD3DVtxBuff->Unlock();
}

void Cform2D::SetTexture(int pFileName)
{
	m_texid = pFileName;
	//if (m_pD3DTex != NULL)m_pD3DTex->Release();
	//D3DXCreateTextureFromFile(m_pDevice, pFileName, &m_pD3DTex);
}

//�傫���ݒ�
void Cform2D::SetLength(float width, float height)
{
	m_fWidth = width;

	m_fHeight = height;

	//�|���S���Ίp���̒���������
	m_fLength = sqrtf(((m_fWidth / 2)*(m_fWidth / 2)) + ((m_fHeight / 2)*(m_fHeight / 2)));

	//�|���S���Ίp���̊p�x������
	m_fAngle = atan2f((m_fWidth / 2), (m_fHeight / 2));
}
/////////////EOF////////////