//=============================================================================
//
// MS_BuildFight [CBall.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CBUILDING_H_
#define _CBUILDING_H_
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "../../form/formX.h"
//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************

//*****************************************************************************
// �}�N����`
//*****************************************************************************
class CLocusEffect;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBall  : public CformX
{
	public:
		CBall();//�R���X�g���N�^
		~CBall(void);//�f�X�g���N�^

		static CBall *Create(LPDIRECT3DDEVICE9 pDevice,int nType,D3DXVECTOR3 pos,D3DXVECTOR3 rot);

		HRESULT Init(LPDIRECT3DDEVICE9 pDevice,int nType);//������
		void Uninit(void);//�I��
		void Update(void);//�X�V
		void Draw(void);//�`��
		void SetViewFlag(bool change){ m_bViewFlag = change; };

		void SetGoalFlag(bool change){ m_bGoal = change; };
		bool GetGoalFlag(void){ return m_bGoal; };

		void SetShotNum(int num){ shot_num = num; };
		int GetShotNum(void){ return shot_num; };

		void AddForce(D3DXVECTOR3 Force, D3DXVECTOR3 Position);
		void AddForce(D3DXVECTOR3 Force);

		D3DXVECTOR3 GetVelocity(void){ return m_MovVelocity; }
		void SetVelocity(D3DXVECTOR3 vel){ m_MovVelocity = vel; }
		void SetAlpha(float alpha){ m_alpha = alpha; }
		void SetCircle(D3DXVECTOR3 circle){ m_CircleVec = circle; }

		void SetMoveFlag(bool mov){ m_bmove = mov; };
	private:
		LPDIRECT3DDEVICE9	m_pDevice;				// pDevice�I�u�W�F�N�g(�`��ɕK�v)
		static const LPSTR	m_ModelName[];			//Model�̖��O�z��
		bool				m_bViewFlag;			//�\���t���O
		SHADER_SET			shaderSet;				//�V�F�[�_�[���
		bool				m_bGoal;				//�S�[����������
		CLocusEffect*		m_pLocusEffect;
		int					shot_num;

		float m_Mass;
		float m_MOI;
		float m_MovResist;
		float m_RotResist;
		D3DXVECTOR3 m_MovVelocity;
		D3DXVECTOR3 m_RotVelocity;
		D3DXVECTOR3 m_CircleVec;
		float m_alpha;
		bool m_bmove;
};

#endif

/////////////EOF////////////