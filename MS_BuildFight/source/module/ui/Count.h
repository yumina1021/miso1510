//=============================================================================
//
// MS_BuildFight [Count.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CCOUNT_H_
#define _CCOUNT_H_
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
#define FIGURE_MAX			(2)
#define SCORE_MAX			(99)

class CNumber;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CCount  : public Cform
{
	public:
		CCount(int nPriority = 7);//�R���X�g���N�^
		~CCount(void);//�f�X�g���N�^

		static CCount *Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot,int initCnt);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos,D3DXVECTOR3 rot,int initCnt);//������
		void Uninit(void);//�I��
		void Update(void);//�X�V
		void Draw(void);//�`��

		void AddCount(int nValue);
		void ResetCount(int nSet);
		void ChangeColor(D3DXCOLOR color);

		void SetPos(D3DXVECTOR3 pos){m_Pos=pos;};
		void SetPos(float fx,float fy,float fz){m_Pos.x=fx;m_Pos.y=fy;m_Pos.z=fz;};
		D3DXVECTOR3 GetPos(void){return m_Pos;};
		void SetRot(D3DXVECTOR3 rot){m_Rot=rot;};
		void SetRot(float fx,float fy,float fz){m_Rot.x=fx;m_Rot.y=fy;m_Rot.z=fz;};
		D3DXVECTOR3 GetRot(void){return m_Rot;};
		void SetMtxView (D3DXMATRIX changeMtx){};

		void SetRotCamera (D3DXVECTOR3 rotCamera){};

		int GetCount (void){return m_nCount;};


	private:
		LPDIRECT3DDEVICE9		m_pDevice;		// pDevice�I�u�W�F�N�g(�`��ɕK�v)	

		D3DXVECTOR3				m_Pos;			//�ʒu
		D3DXVECTOR3				m_Rot;			//����

		CNumber					*m_pNumber[FIGURE_MAX];

		int						m_nCount;
};

#endif

/////////////EOF////////////