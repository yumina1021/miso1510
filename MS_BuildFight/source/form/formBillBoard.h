//=============================================================================
//
// MS_BuildFight [formBillBoard.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CSCENEBILLBOARD_H_
#define _CSCENEBILLBOARD_H_
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "form.h"
//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CformBillBoard  : public Cform
{
	public:
		CformBillBoard(int nPriority = 7);//�R���X�g���N�^
		~CformBillBoard(void);//�f�X�g���N�^

		static CformBillBoard *Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,LPSTR pTexName,float fLength,D3DXCOLOR changeColor);//������
		void Uninit(void);//�I��
		void Update(void);//�X�V
		void Draw(void);//�`��

		void SetDiffuse(float r,float g,float b,float a);
		void SetVtx(float fLength);

		void SetPos(D3DXVECTOR3 pos){m_Pos=pos;};
		void SetPos(float fx,float fy,float fz){m_Pos.x=fx;m_Pos.y=fy;m_Pos.z=fz;};
		D3DXVECTOR3 GetPos(void){return m_Pos;};
		void SetRot(D3DXVECTOR3 rot){m_Rot=rot;};
		void SetRot(float fx,float fy,float fz){m_Rot.x=fx;m_Rot.y=fy;m_Rot.z=fz;};
		D3DXVECTOR3 GetRot(void){return m_Rot;};
		void SetMtxView (D3DXMATRIX changeMtx){m_MtxView=changeMtx;};
		void SetUV(float ful,float fur,float fvt,float fvu);

	protected:
		LPDIRECT3DDEVICE9		m_pDevice;		// pDevice�I�u�W�F�N�g(�`��ɕK�v)
	private:
		LPDIRECT3DTEXTURE9  	m_pD3DTex;		//�e�N�X�`���\���p
		LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;	//���_���i�[���[�N(���I)

		D3DXMATRIX				m_MtxView;		//�r���[�}�g���N�X

		D3DXVECTOR3				m_Pos;			//�ʒu
		D3DXVECTOR3				m_Rot;			//����
		D3DXVECTOR3				m_Scl;			//�傫��
};

#endif

/////////////EOF////////////