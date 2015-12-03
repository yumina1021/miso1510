//=============================================================================
//
// MS_BuildFight [Gimmick.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CGIMMICK_H_
#define _CGIMMICK_H_
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
//�I�u�W�F�N�g�̎��
typedef enum
{
	GIMMICK_CUBE=0,		//�l�p�̕s���̋�������
	GIMMICK_CLOUD,		//�ϗ��_
	GIMMICK_CROW,		//�J���X
	GIMMICK_UFO,		//UFO
	GIMMICK_WIND,		//��
	GIMMICK_TORNADO,	//����
	GIMMICK_MAX,
}GIMMICKTYPE;

typedef enum
{
	MOVETYPE_STOP=0,	//��~
	MOVETYPE_UPDOWN,	//�㉺�ړ�
	MOVETYPE_SLIDE,		//�X���C�h
	MOVETYPE_MAX
}MOVETYPE;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGimmick : public CformX
{
	public:
		CGimmick();						//�R���X�g���N�^
		~CGimmick(void);		//�f�X�g���N�^
	
		static CGimmick *Create(LPDIRECT3DDEVICE9 pDevice, GIMMICKTYPE GimmickType,MOVETYPE MoveType, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	
		HRESULT Init(LPDIRECT3DDEVICE9 pDevice, int nType, MOVETYPE MoveType);			//������
		void Uninit(void);											//�I��
		void Update(void);											//�X�V
		void Draw(void);											//�`��
		void SetViewFlag(bool change){ m_bViewFlag = change; };

		void SetSize(D3DXVECTOR3 Size){ m_Size = Size; };
		D3DXVECTOR3 GetSize(void){ return m_Size; };

		void SetPos(D3DXVECTOR3 Pos){ m_Pos = Pos; };
		D3DXVECTOR3 GetPos(void){ return m_Pos; };


		void SetGimmickType(GIMMICKTYPE GimmickType){ m_GimmickType = GimmickType; };
		GIMMICKTYPE GetGimmickType(void){ return m_GimmickType; };

		void SetMoveType(MOVETYPE MoveType){ m_MoveType = MoveType; };
		MOVETYPE GetMoveType(void){ return m_MoveType; };

	private:
		void _UpdateObject(void);
		void _UpdateCube(void);
		void _UpdateCloud(void);
		void _UpdateCrow(void);
		void _UpdateUFO(void);
		void _UpdateWind(void);
		void _UpdateTornado(void);

		//�l�p�̕��̂̈ړ��֌W
		void UpdateCubeMoveStop(void);
		void UpdateCubeMoveSlide(void);
		void UpdateCubeMoveUpDown(void);

		//�_�̈ړ��֌W
		void UpdateCloudMoveStop(void);
		void UpdateCloudMoveSlide(void);
		void UpdateCloudMoveUpDown(void);

		//�J���X�̈ړ��֌W
		void UpdateCrowMoveStop(void);
		void UpdateCrowMoveSlide(void);
		void UpdateCrowMoveUpDown(void);

		//UFO�̈ړ��֌W
		void UpdateUFOMoveStop(void);
		void UpdateUFOMoveSlide(void);
		void UpdateUFOMoveUpDown(void);

		//��
		void UpdateWindMoveStop(void);
		void UpdateWindMoveSlide(void);
		void UpdateWindMoveUpDown(void);

		//����
		void UpdateTornadoMoveStop(void);
		void UpdateTornadoMoveSlide(void);
		void UpdateTornadoMoveUpDown(void);

		LPDIRECT3DDEVICE9	m_pDevice;				// pDevice�I�u�W�F�N�g(�`��ɕK�v)
		static const LPSTR	m_ModelName[];			//Model�̖��O�z��
		bool				m_bViewFlag;			//�\���t���O
		GIMMICKTYPE			m_GimmickType;
		MOVETYPE			m_MoveType;
		D3DXVECTOR3			m_Size;
		D3DXVECTOR3			m_Pos;
		D3DXVECTOR3			m_Rot;
		D3DXVECTOR3			m_Scl;
		float				m_Speed;				//���x
		D3DXVECTOR3			m_Work;
};

#endif

/////////////EOF////////////