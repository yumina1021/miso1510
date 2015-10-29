//=============================================================================
//
// MS_BuildFight [Gauge.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CGAUGE_H_
#define _CGAUGE_H_
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "../../form/form.h"
//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FIGURE_G_MAX		(6)
#define SCORE_G_MAX			(3000)

class CBar;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGauge  : public Cform
{
	public:
		CGauge(int nPriority = 7);//�R���X�g���N�^
		~CGauge(void);//�f�X�g���N�^

		static CGauge *Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot,bool Etype);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot,bool Etype);//������
		void Uninit(void);//�I��
		void Update(void);//�X�V
		void Draw(void);//�`��

		void AddGauge(int nValue);
		void ResetGauge(int nSet);

		void SetPos(D3DXVECTOR3 pos){m_Pos=pos;};
		void SetPos(float fx,float fy,float fz){m_Pos.x=fx;m_Pos.y=fy;m_Pos.z=fz;};
		D3DXVECTOR3 GetPos(void){return m_Pos;};
		void SetRot(D3DXVECTOR3 rot){m_Rot=rot;};
		void SetRot(float fx,float fy,float fz){m_Rot.x=fx;m_Rot.y=fy;m_Rot.z=fz;};
		D3DXVECTOR3 GetRot(void){return m_Rot;};
		void SetMtxView (D3DXMATRIX changeMtx){};
		void SetRotCamera (D3DXVECTOR3 rotCamera){};
		int GetGauge(void){return m_nGauge;};

	private:
		LPDIRECT3DDEVICE9		m_pDevice;		// pDevice�I�u�W�F�N�g(�`��ɕK�v)	

		D3DXVECTOR3				m_Pos;			//�ʒu
		D3DXVECTOR3				m_Rot;			//����

		CBar					*m_pBar[FIGURE_G_MAX];

		int						m_nGauge;
		int						m_nGaugeFigure;
		float					m_fView;
		bool					m_bEtype;
};

#endif

/////////////EOF////////////