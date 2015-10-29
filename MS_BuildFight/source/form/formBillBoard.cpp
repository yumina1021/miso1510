//=============================================================================
//
// MS_BuildFight [CformBillBoard.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "formBillBoard.h"
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CformBillBoard :: CformBillBoard(int nPriority) : Cform(OBJTYPE_BILLBOARD,nPriority)
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CformBillBoard :: ~CformBillBoard(void)
{
}
//=============================================================================
// Cform2D����
//=============================================================================
CformBillBoard *CformBillBoard::Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CformBillBoard *pformBillBoard;

	pformBillBoard = new CformBillBoard();
	pformBillBoard->Init(pDevice,"data/TEXTURE/bullet000.png",10,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
	pformBillBoard->SetPos(pos);

	return pformBillBoard;
}
//=============================================================================
// ������
//=============================================================================
HRESULT CformBillBoard :: Init(LPDIRECT3DDEVICE9 pDevice,LPSTR pTexName,float fLength,D3DXCOLOR changeColor)
{

	m_pDevice=pDevice;

	//�t�B�[���h�̏�����
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//���_���̐ݒ�
	if(FAILED(m_pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&m_pD3DVtxBuff,NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;

	//���b�N
	m_pD3DVtxBuff->Lock(0,0,(void**)&pVtx,0);

	pVtx[0].vtx = D3DXVECTOR3(-fLength,fLength,0.0f);//x,y�̏�
	pVtx[1].vtx = D3DXVECTOR3(fLength,fLength,0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-fLength,-fLength,0.0f);
	pVtx[3].vtx = D3DXVECTOR3(fLength,-fLength,0.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);

	pVtx[0].diffuse = D3DXCOLOR(changeColor.r,changeColor.g,changeColor.b,changeColor.a);//�F�͔�
	pVtx[1].diffuse = D3DXCOLOR(changeColor.r,changeColor.g,changeColor.b,changeColor.a);
	pVtx[2].diffuse = D3DXCOLOR(changeColor.r,changeColor.g,changeColor.b,changeColor.a);
	pVtx[3].diffuse = D3DXCOLOR(changeColor.r,changeColor.g,changeColor.b,changeColor.a);

	pVtx[0].tex = D3DXVECTOR2(0,0);//�摜��UV�l�@U,V�̏�
	pVtx[1].tex = D3DXVECTOR2(1,0);
	pVtx[2].tex = D3DXVECTOR2(0,1);
	pVtx[3].tex = D3DXVECTOR2(1,1);	
	
	//�A�����b�N
	m_pD3DVtxBuff->Unlock();

	//�e�N�X�`���̐ݒ�
	if(pTexName!=NULL)
	{
		D3DXCreateTextureFromFile(m_pDevice,pTexName,&m_pD3DTex);
	}else
	{
		m_pD3DTex=NULL;
	}

	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CformBillBoard :: Uninit(void)
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

	Cform::Release();
}
//=============================================================================
// �X�V
//=============================================================================
void CformBillBoard :: Update(void)
{

}
//=============================================================================
// �`��
//=============================================================================
void CformBillBoard :: Draw(void)
{
	D3DXMATRIX  mtxWorld;
	//�}�g���b�N�X�̐ݒ�
	D3DXMATRIX mtxTranslate;

	//m_pDevice->SetRenderState(D3DRS_LIGHTING,FALSE);
	//m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);

	//���[���h�}�g���b�N�X�̐ݒ�
	D3DXMatrixIdentity(&mtxWorld);
	D3DXMatrixInverse(&mtxWorld,NULL,&m_MtxView);

	mtxWorld._41=0.0f;
	mtxWorld._42=0.0f;
	mtxWorld._43=0.0f;

	D3DXMatrixTranslation(&mtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);
	D3DXMatrixMultiply(&mtxWorld,&mtxWorld,&mtxTranslate);

	m_pDevice->SetTransform(D3DTS_WORLD,&mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	m_pDevice->SetStreamSource(0,m_pD3DVtxBuff,0,sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	m_pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	if(m_pD3DTex!=NULL)
	{
		m_pDevice->SetTexture(0,m_pD3DTex);
	}else
	{
		m_pDevice->SetTexture(0,NULL);
	}

	//�|���S���̕`��
	m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

	//m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);
	//m_pDevice->SetRenderState(D3DRS_LIGHTING,TRUE);


}
//=============================================================================
// UV�l�ݒ�
//=============================================================================
void CformBillBoard :: SetUV(float ful,float fur,float fvt,float fvu)
{
	VERTEX_3D *pVtx;

	//���b�N
	m_pD3DVtxBuff->Lock(0,0,(void**)&pVtx,0);

	pVtx[0].tex = D3DXVECTOR2(ful,fvt);//�摜��UV�l�@U,V�̏�
	pVtx[1].tex = D3DXVECTOR2(fur,fvt);
	pVtx[2].tex = D3DXVECTOR2(ful,fvu);
	pVtx[3].tex = D3DXVECTOR2(fur,fvu);

	//�A�����b�N
	m_pD3DVtxBuff->Unlock();
}

void CformBillBoard :: SetDiffuse(float r,float g,float b,float a)
{
	VERTEX_3D *pVtx;

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
//=============================================================================
// ���W�ݒ�
//=============================================================================
void CformBillBoard::SetVtx(float fLength)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx.x = -fLength;
		pVtx[0].vtx.y = fLength;
		pVtx[0].vtx.z = 0.0f;

		pVtx[1].vtx.x = fLength;
		pVtx[1].vtx.y = fLength;
		pVtx[1].vtx.z = 0.0f;

		pVtx[2].vtx.x = -fLength;
		pVtx[2].vtx.y = -fLength;
		pVtx[2].vtx.z = 0.0f;

		pVtx[3].vtx.x = fLength;
		pVtx[3].vtx.y = -fLength;
		pVtx[3].vtx.z = 0.0f;

		// ���_�f�[�^���A�����b�N����
		m_pD3DVtxBuff->Unlock();
	}	
}
/////////////EOF////////////