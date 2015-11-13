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

	private:
		LPDIRECT3DDEVICE9	m_pDevice;				// pDevice�I�u�W�F�N�g(�`��ɕK�v)
		static const LPSTR	m_ModelName[];			//Model�̖��O�z��
		bool				m_bViewFlag;			//�\���t���O
		SHADER_SET			shaderSet;				//�V�F�[�_�[���
		bool				m_bGoal;				//�S�[����������
		CLocusEffect*		m_pLocusEffect;
};

#endif

/////////////EOF////////////