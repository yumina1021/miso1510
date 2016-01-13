//=============================================================================
//
// MS_BuildFight [LocusEffect.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CUPIN_H_
#define _CUPIN_H_
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************

#include "../../form/form2D.h"
//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CCupin
{
	public:
		CCupin();//�R���X�g���N�^
		~CCupin();//�f�X�g���N�^

		static CCupin* Create(LPDIRECT3DDEVICE9 pDevice);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice);//������
		void Uninit(void);//�I��
		void Update(void);//�X�V
		void Draw(void);//�`��

		void SetFlag(bool change){ m_bFlag = change; };
		bool GetFlag(){ return m_bFlag; };
		void SetDrawFlag(bool change){ m_bDrawFlag = change; };
		bool GetDrawFlag(){ return m_bDrawFlag; };
		float EsasingNone(float paramMin, float paramMax, float paramTime);

	private :
		LPDIRECT3DDEVICE9		m_pDevice;			// pDevice�I�u�W�F�N�g(�`��ɕK�v)

		int m_texid;
		float m_timer;
		float m_s_timer[5];
		bool m_bFlag;
		bool m_bDrawFlag;
		Cform2D* m_pcupin[5];
		D3DXVECTOR3 m_pos[5];
		D3DXVECTOR3 m_s_pos;
};

#endif

/////////////EOF////////////