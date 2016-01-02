//=============================================================================
//
// MS_BuildFight [CIcon.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "Icon.h"
#include "../../administer/Texture.h"
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CIcon :: CIcon(int nPriority) : Cform(OBJTYPE_2D,nPriority)
{

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CIcon :: ~CIcon(void)
{
}
//=============================================================================
// CIcon����
//=============================================================================
CIcon *CIcon::Create(LPDIRECT3DDEVICE9 pDevice,int pTexName,D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CIcon *pIcon;

	pIcon = new CIcon();
	pIcon->Init(pDevice,pTexName,pos);
	pIcon->SetPos(pos);

	return pIcon;
}
//=============================================================================
// ������
//=============================================================================
HRESULT CIcon :: Init(LPDIRECT3DDEVICE9 pDevice,int pTexName,D3DXVECTOR3 pos)
{
	m_pDevice=pDevice;

	int nNumBlockX=1;
	int nNumBlockZ=1;

	m_texid = pTexName;
	//�e�N�X�`���̐ݒ�
	//D3DXCreateTextureFromFile(m_pDevice,NULL,&m_pD3DTex);

	//�t�B�[���h�̏�����
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Posplus = pos;
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl = D3DXVECTOR3(1.0f,1.0f,1.0f);

	m_fLength = sqrtf((float)(((ICON_SIZE_X / 2) * (ICON_SIZE_X / 2)) + ((ICON_SIZE_Y / 2) * (ICON_SIZE_Y / 2))));
	m_fAngle = atan2f((ICON_SIZE_X / 2), (ICON_SIZE_Y / 2));

	//���_���̐ݒ�
	if(FAILED(m_pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)* NUM_VERTEX,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_2D,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuff,
											NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].vtx = D3DXVECTOR3(-m_fLength,m_fLength,0.0f);//x,y�̏�
	pVtx[1].vtx = D3DXVECTOR3(m_fLength,m_fLength,0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-m_fLength,-m_fLength,0.0f);
	pVtx[3].vtx = D3DXVECTOR3(m_fLength,-m_fLength,0.0f);

	pVtx[0].hrw=1.0f;//1.0f�Œ�
	pVtx[1].hrw=1.0f;
	pVtx[2].hrw=1.0f;
	pVtx[3].hrw=1.0f;

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

	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CIcon :: Uninit(void)
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
// �X�V
//=============================================================================
void CIcon :: Update(void)
{
	D3DXVECTOR3 Setpos[4];					//�|���S���̈ʒu

	m_Pos+=m_Posplus;

	//��]
	Setpos[0].x = m_Pos.x + (sin(m_Rot.y - m_fAngle)*m_fLength);
	Setpos[0].y = m_Pos.y - (cos(m_Rot.y - m_fAngle)*m_fLength);
	Setpos[1].x = m_Pos.x + (sin(m_Rot.y + m_fAngle)*m_fLength);
	Setpos[1].y = m_Pos.y - (cos(m_Rot.y + m_fAngle)*m_fLength);
	Setpos[2].x = m_Pos.x + (sin(-m_Rot.y - m_fAngle)*m_fLength);
	Setpos[2].y = m_Pos.y + (cos(-m_Rot.y - m_fAngle)*m_fLength);
	Setpos[3].x = m_Pos.x + (sin(-m_Rot.y + m_fAngle)*m_fLength);
	Setpos[3].y = m_Pos.y + (cos(-m_Rot.y + m_fAngle)*m_fLength);
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
void CIcon :: Draw(void)
{
	D3DXMATRIX  mtxWorld;
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	//�}�g���b�N�X�̐ݒ�
	//D3DXMatrixIdentity(&mtxWorld);

	//D3DXMatrixScaling(&mtxScl,m_Scl.x,m_Scl.y,m_Scl.z);
	//D3DXMatrixMultiply(&mtxWorld,&mtxWorld,&mtxScl);

	// ���[�e�[�V����(�J�����̋t�s��)
	//D3DXMatrixInverse(&mtxWorld,NULL,&m_MtxView);

	//mtxWorld._41 = 0.0f;
	//mtxWorld._42 = 0.0f;
	//mtxWorld._43 = 0.0f;

	//D3DXMatrixTranslation(&mtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);
	//D3DXMatrixMultiply(&mtxWorld,&mtxWorld,&mtxTranslate);

	//m_pDevice->SetTransform(D3DTS_WORLD,&mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	m_pDevice->SetStreamSource(0,m_pD3DVtxBuff,0,sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	m_pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	m_pDevice->SetTexture(0, CTexture::GetTex(m_texid));

	//�|���S���̕`��
	m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	m_pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}
/////////////EOF////////////