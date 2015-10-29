//=============================================================================
//
// MS_BuildFight [Number.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CNUMBER_H_
#define _CNUMBER_H_
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
#define POINT_MAX			(4)
#define NUMBER_WIDTH		(30)
#define NUMBER_HEIGHT		(60)
#define NUMBER_FIRST_X		(0)
#define NUMBER_FIRST_Y		(0)
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CNumber
{
	public:
		CNumber(void);//�R���X�g���N�^
		~CNumber(void);//�f�X�g���N�^

		static CNumber *Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXCOLOR color,float width,float height);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXCOLOR color,float width,float height);//������
		void Uninit(void);//�I��
		void Update(void);//�X�V
		void Draw(void);//�`��

		void SetNumber(float nNumber);
		void SetColor(D3DXCOLOR color);

		void SetPos(D3DXVECTOR3 pos){m_Pos=pos;};
		void SetPos(float fx,float fy,float fz){m_Pos.x=fx;m_Pos.y=fy;m_Pos.z=fz;};
		D3DXVECTOR3 GetPos(void){return m_Pos;};
	private:
		LPDIRECT3DTEXTURE9  	m_pD3DTex;		//�e�N�X�`���\���p
		LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuff;	//���_���i�[���[�N(���I)
		LPDIRECT3DDEVICE9		m_pDevice;		// pDevice�I�u�W�F�N�g(�`��ɕK�v)	

		D3DXVECTOR3				m_Pos;			//�ʒu
		D3DXVECTOR3				m_Rot;			//����

		float					m_fLength;		//�|���S���Ίp���̒���
		float					m_fAngle;		//�|���S���Ίp���̊p�x

		int m_nNumber;
};

#endif

/////////////EOF////////////