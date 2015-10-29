//=============================================================================
//
// MS_BuildFight [CBar.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CBAR_H_
#define _CBAR_H_
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "../../common.h"
//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define POINT_MAX		(4)
#define BAR_WIDTH		(30)
#define BAR_HEIGHT		(60)
#define BAR_FIRST_X		(0)
#define BAR_FIRST_Y		(0)
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBar
{
	public:
		CBar();//�R���X�g���N�^
		~CBar(void);//�f�X�g���N�^

		static CBar *Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXCOLOR color,float width,float height);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXCOLOR color,float width,float height);//������
		void Uninit(void);//�I��
		void Update(void);//�X�V
		void Draw(void);//�`��

		void SetViewFlag(bool Flag){m_bViewFlag=Flag;};
		
	private:
		LPDIRECT3DTEXTURE9  	m_pD3DTex;		//�e�N�X�`���\���p
		LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;	//���_���i�[���[�N(���I)
		LPDIRECT3DDEVICE9		m_pDevice;		// pDevice�I�u�W�F�N�g(�`��ɕK�v)	

		D3DXVECTOR3				m_Pos;			//�ʒu
		D3DXVECTOR3				m_Rot;			//����

		float					m_fLength;		//�|���S���Ίp���̒���
		float					m_fAngle;		//�|���S���Ίp���̊p�x
		bool					m_bViewFlag;	
};

#endif

/////////////EOF////////////