//=============================================================================
//
// MS_BuildFight [LocusEffect.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CBLOWSHOT_H_
#define _CBLOWSHOT_H_
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
class CBlowShot
{
	public:
		CBlowShot();//�R���X�g���N�^
		~CBlowShot();//�f�X�g���N�^

		static CBlowShot* Create(LPDIRECT3DDEVICE9 pDevice, int pTexPlayer1, int pTexPlayer2);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice, int pTexName1, int pTexName2);//������
		void Uninit(void);//�I��
		void Update(void);//�X�V
		void Draw(void);//�`��

		void SetFlag(bool change, int id){ m_bFlag[id] = change; };
		bool GetFlag(int id){ return m_bFlag[id]; };
		float EsasingNone(float paramMin, float paramMax, float paramTime);

	private :
		LPDIRECT3DDEVICE9		m_pDevice;			// pDevice�I�u�W�F�N�g(�`��ɕK�v)

		int m_texid;
		float m_timer;
		float m_bgtimer;
		float m_chartimer;
		float m_nametimer;
		bool m_bFlag[2];
		Cform2D* m_pbgtex[2];
		Cform2D* m_pchar[2];
		Cform2D* m_pname[2];
		D3DXVECTOR3 m_bgpos;
		D3DXVECTOR3 m_charpos;
		D3DXVECTOR3 m_namepos;
		D3DXVECTOR3 m_s_bgpos;
		D3DXVECTOR3 m_s_charpos;
		D3DXVECTOR3 m_s_namepos;
};

#endif

/////////////EOF////////////