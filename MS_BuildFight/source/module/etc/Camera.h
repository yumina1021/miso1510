//=============================================================================
//
// MS_BuildFight [CCamera.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CCAMERA_H_
#define _CCAMERA_H_
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "../../common.h"

#define CAMERA_MOVE_SPEED (2.0f)		//�J�����ړ����x

typedef enum							//�J�����̃��[�h
{
	DEBUG_MODE =0,
	GAMEEND_MODE,
	RELEASE_MODE,
	SKILL_MODE
}CAMERA;
//*****************************************************************************
// �N���X��`
//*****************************************************************************

class CCamera
{
	public:
		CCamera(void);				//�R���X�g���N�^
		~CCamera(void);				//�f�X�g���N�^

		HRESULT Init(void);						//������
		void Uninit(void);						//�I��
		void Update(void);						//�X�V
		void Set(LPDIRECT3DDEVICE9 pDevice);	//�`��

		void SceneGame(void);
		void StartCamera(void);
		void ShotCamera(void);
		void PowerCamera(void);
		void MoveCamera(void);
		void JudgeCamera(void);
		void ChangeCamera(void);

		D3DXVECTOR3 GetRotCamera(void){return m_rotCamera;};							//�J�����̌����󂯓n��
		D3DXMATRIX GetMtxView (void){return m_mtxView;};		//�r���[�}�g���N�X�󂯓n��
		D3DXVECTOR3 GetPointView(void){return m_posPointView;};	//�����_�̎󂯓n��

		D3DXVECTOR3 GetPosP(void){ return m_posCameraP; }
		D3DXVECTOR3 GetPosR(void){ return m_posCameraR; }
		D3DXVECTOR3 GetVecUp(void){ return m_posCameraU; }
	private:

		D3DXVECTOR3	m_posCameraP;	//�J�����̎��_
		D3DXVECTOR3	m_posCameraR;	//�J�����̒����_
		D3DXVECTOR3	m_posCameraU;	//�J�����̏�����x�N�g��

		D3DXVECTOR3	m_rotCamera;	//�J�����̌���

		D3DXMATRIX	m_mtxView;		//�r���[�}�g���N�X
		D3DXMATRIX	m_mtxProjection;//�v���W�F�N�V�����}�g���N�X

		float		m_fVectCamera;	//���_���璍���_�܂ł̋���
		float		m_fVectCamera2;

		float		Distance;

		D3DXVECTOR3	m_posCameraPDest;//�ړI�̎��_
		D3DXVECTOR3	m_posCameraRDest;//�ړI�̒����_

		CAMERA		m_CameraMode;	//�J�����̃��[�h
		D3DXVECTOR3 m_posPointView;	//�����_�̏ꏊ

		//���ݖ��g�p
		float		m_fCountSkillY;
		float		m_fCountSkillX;


};

#endif

/////////////EOF////////////