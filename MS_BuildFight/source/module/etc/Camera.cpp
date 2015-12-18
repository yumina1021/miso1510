//=============================================================================
//
// MS_BuildFight [CCamera.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#include "Camera.h"

#include "../robot/PlayerM.h"

#include "../../administer/Input.h"
#include "../../administer/Maneger.h"
#include "../../administer/Debugproc.h"

#include "../../administer/scene/Game.h"
#include "../../module/etc/Ball.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCamera :: CCamera(void)
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera :: ~CCamera(void)
{
}
//=============================================================================
// ������
//=============================================================================
HRESULT CCamera :: Init(void)
{
	//���W������
	m_posCameraP = D3DXVECTOR3(0.0f,50.0f,200.0f);
	m_posCameraR = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_posCameraU = D3DXVECTOR3(0.0f,1.0f,0.0f);

	//�x�N�g���̏�����
	m_fVectCamera = sqrtf((m_posCameraR.x-m_posCameraP.x)*(m_posCameraR.x-m_posCameraP.x)+(m_posCameraR.z-m_posCameraP.z)*(m_posCameraR.z-m_posCameraP.z));
	m_fVectCamera2 = sqrtf((m_posCameraR.z-m_posCameraP.z)*(m_posCameraR.z-m_posCameraP.z)+(m_posCameraR.y-m_posCameraP.y)*(m_posCameraR.y-m_posCameraP.y));
	
	//���_���璍���_�ւ̊p�x��ݒ�
	m_rotCamera.y = atan2f((m_posCameraR.x-m_posCameraP.x),(m_posCameraR.z-m_posCameraP.z));
	m_rotCamera.x = atan2f((m_posCameraR.z-m_posCameraP.z),(m_posCameraR.y-m_posCameraP.y));

	//���[�h�̏�����
	m_CameraMode= RELEASE_MODE;

	//�����_�̏�����
	m_posPointView=D3DXVECTOR3(0.0f,0.0f,0.0f);

	Distance=0.0f;

	//���g�p
	//m_fCountSkillY=0;
	//m_fCountSkillX=0;

	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CCamera :: Uninit(void)
{
}
//=============================================================================
// �X�V
//=============================================================================
void CCamera :: Update(void)
{
	if(CManager::GetSceneType()==PHASETYPE_GAME)
	{
		SceneGame();
	//	switch (m_CameraMode)
	//	{
	//		case RELEASE_MODE:
	//		{
	//			//�ړI�̎��_�ݒ�
	//			m_posCameraPDest.x = posModel.x - sinf(ErotModel.y) * 150;
	//			m_posCameraPDest.y = posModel.y + 75;
	//			m_posCameraPDest.z = posModel.z - cosf(ErotModel.y) * 200;

	//			//�ړI�̒����_�ݒ�
	//			m_posCameraRDest.x = m_posPointView.x - sinf(rotModel.y) * 45;
	//			m_posCameraRDest.y = m_posPointView.y - 10;
	//			m_posCameraRDest.z = m_posPointView.z - cosf(rotModel.y) * 30;

	//#ifdef _DEBUG
	//			CDebugProc::Print("Distance:%f\n", Distance);
	//			CDebugProc::Print("posY:%f\n", posModel.y);
	//#endif
	//			if (Distance < 200.0f)
	//			{
	//				m_posCameraPDest.y = posModel.y + 75 + (100- Distance*0.5f);
	//				m_posCameraPDest.z = posModel.z - cosf(ErotModel.y) * (200 + (100 - Distance*0.5f));
	//				m_posCameraRDest.y =  EposModel.y - 10 + (120 - Distance);
	//			}

	//			float yset = posModel.y;
	//			if (yset > 50.0f){ yset = 50.0f; }

	//			m_posCameraP.x += (m_posCameraPDest.x - m_posCameraP.x)*(0.10f - (yset*0.0016f));
	//			if (m_posCameraPDest.y - posModel.y <= 110)
	//			{
	//				m_posCameraP.y += (m_posCameraPDest.y - m_posCameraP.y)*0.1f;
	//			}
	//			m_posCameraP.z += (m_posCameraPDest.z - m_posCameraP.z)*(0.10f - (yset*0.0016f));
	//			//���݂̒����_�ɖړI�̒����_�Ƃ̍��𑫂��Ă���
	//			m_posCameraR.x += (m_posCameraRDest.x - m_posCameraR.x)*0.14f;
	//			if (m_posCameraRDest.y - posModel.y <= 110)
	//			{
	//				m_posCameraR.y += (m_posCameraRDest.y - m_posCameraR.y)*0.12f;
	//			}
	//			m_posCameraR.z += (m_posCameraRDest.z - m_posCameraR.z)*0.14f;

	//			break;

	//			m_posCameraP = D3DXVECTOR3(0.0f, 100.0f, 100.0f);
	//			m_posCameraR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//		}

	//		case GAMEEND_MODE:
	//				m_posCameraPDest.x = m_posPointView.x;
	//				m_posCameraPDest.y = m_posPointView.y + 100;
	//				m_posCameraPDest.z = m_posPointView.z + 300;

	//				//�ړI�̒����_�ݒ�
	//				m_posCameraRDest.x = m_posPointView.x;
	//				m_posCameraRDest.y = m_posPointView.y - 10;
	//				m_posCameraRDest.z = m_posPointView.z;
	//				break;
	//		//���ݖ��g�p


	//		case SKILL_MODE:
	//					//�ړI�̎��_�ݒ�
	//					m_posCameraPDest.x= posModel.x;
	//					m_posCameraPDest.y= posModel.y+(130+(m_fCountSkillY));
	//					m_posCameraPDest.z= posModel.z+300-m_fCountSkillX;
	//				
	//					if(m_fCountSkillX<90)
	//					{
	//						if(m_fCountSkillY<250)
	//						{
	//							m_fCountSkillY+=1.0f;
	//						}else
	//						{
	//							m_fCountSkillY+=0.3f;
	//							m_fCountSkillX+=1.0f;
	//						}
	//					}else
	//					{
	//						m_CameraMode=RELEASE_MODE;

	//						posModel = pPlayerM->GetPos();
	//						rotModel = pPlayerM->GetRot();
	//						CCamera :: Init();

	//						//�ړI�̎��_�ݒ�
	//						m_posCameraPDest.x= posModel.x;
	//						m_posCameraPDest.y= posModel.y+75;
	//						m_posCameraPDest.z= posModel.z+150;
	//				
	//						//�ړI�̒����_�ݒ�
	//						m_posCameraRDest.x= m_posPointView.x - sinf(rotModel.y)*45;
	//						m_posCameraRDest.y= m_posPointView.y -10;
	//						m_posCameraRDest.z= m_posPointView.z - cosf(rotModel.y)*30;
	//					}

	//					//�ړI�̒����_�ݒ�
	//					m_posCameraRDest.x= posModel.x;
	//					m_posCameraRDest.y= posModel.y+(100+(m_fCountSkillY));
	//					m_posCameraRDest.z= posModel.z;

	//					//���݂̎��_�ɖړI�̎��_�Ƃ̍��𑫂��Ă���
	//					m_posCameraP.x+=(m_posCameraPDest.x-m_posCameraP.x)*0.12f;
	//					m_posCameraP.y+=(m_posCameraPDest.y-m_posCameraP.y);
	//					m_posCameraP.z+=(m_posCameraPDest.z-m_posCameraP.z)*0.12f;

	//					//���݂̒����_�ɖړI�̒����_�Ƃ̍��𑫂��Ă���
	//					m_posCameraR.x+=(m_posCameraRDest.x-m_posCameraR.x)*0.14f;
	//					m_posCameraR.y+=(m_posCameraRDest.y-m_posCameraR.y);
	//					m_posCameraR.z+=(m_posCameraRDest.z-m_posCameraR.z)*0.14f;
	//					break;

	//		case DEBUG_MODE:

	//					//�J�����̈ړ�
	//					if(pInputKeyboard->GetKeyPress(DIK_K))
	//					{
	//						m_posCameraP.x -= sinf(m_rotCamera.y)*CAMERA_MOVE_SPEED;
	//						m_posCameraP.z -= cosf(m_rotCamera.y)*CAMERA_MOVE_SPEED;
	//					}
	//					else if(pInputKeyboard->GetKeyPress(DIK_I))
	//					{
	//						m_posCameraP.x += sinf(m_rotCamera.y)*CAMERA_MOVE_SPEED;
	//						m_posCameraP.z += cosf(m_rotCamera.y)*CAMERA_MOVE_SPEED;
	//					}
	//					if(pInputKeyboard->GetKeyPress(DIK_J))
	//					{
	//						m_posCameraP.x -= sinf(m_rotCamera.y+90*(D3DX_PI/180))*CAMERA_MOVE_SPEED;
	//						m_posCameraP.z -= cosf(m_rotCamera.y+90*(D3DX_PI/180))*CAMERA_MOVE_SPEED;
	//					}
	//					else if(pInputKeyboard->GetKeyPress(DIK_L))
	//					{
	//						m_posCameraP.x += sinf(m_rotCamera.y+90*(D3DX_PI/180))*CAMERA_MOVE_SPEED;
	//						m_posCameraP.z += cosf(m_rotCamera.y+90*(D3DX_PI/180))*CAMERA_MOVE_SPEED;
	//					}

	//					//�J�����̏��~
	//					if(pInputKeyboard->GetKeyPress(DIK_Y))
	//					{
	//						m_posCameraP.y +=2;
	//					}
	//					else if(pInputKeyboard->GetKeyPress(DIK_N))
	//					{
	//						m_posCameraP.y -=2;
	//					}

	//					//�J�����̐���
	//					if(pInputKeyboard->GetKeyPress(DIK_Z))
	//					{
	//						m_rotCamera.y +=D3DX_PI/180;
	//						m_posCameraP.x = m_posCameraR.x - sinf(m_rotCamera.y)*m_fVectCamera;
	//						m_posCameraP.z = m_posCameraR.z - cosf(m_rotCamera.y)*m_fVectCamera;
	//					}
	//					else if(pInputKeyboard->GetKeyPress(DIK_C))

	//					{
	//						m_rotCamera.y -=D3DX_PI/180;
	//						m_posCameraP.x = m_posCameraR.x - sinf(m_rotCamera.y)*m_fVectCamera;
	//						m_posCameraP.z = m_posCameraR.z - cosf(m_rotCamera.y)*m_fVectCamera;
	//					}

	//					//�J�����̎�ӂ�
	//					if(pInputKeyboard->GetKeyPress(DIK_Q))
	//					{
	//						m_rotCamera.y -= (D3DX_PI/180);
	//					}
	//					else if(pInputKeyboard->GetKeyPress(DIK_E))
	//					{
	//						m_rotCamera.y += (D3DX_PI/180);
	//					}
	//					if(pInputKeyboard->GetKeyPress(DIK_T))
	//					{
	//						m_rotCamera.x += (D3DX_PI/180);
	//					}
	//					else if(pInputKeyboard->GetKeyPress(DIK_B))
	//					{
	//						m_rotCamera.x -= (D3DX_PI/180);
	//					}
	//					if(pInputKeyboard->GetKeyPress(DIK_0))
	//					{
	//						m_posCameraP = D3DXVECTOR3(0.0f,50.0f,-130.0f);
	//						m_posCameraR = D3DXVECTOR3(0.0f,0.0f,0.0f);
	//						m_posCameraU = D3DXVECTOR3(0.0f,1.0f,0.0f);
	//					}
	//					break;
	//	}

	//	//�J�����̃��[�h�̐؂�ւ�
	//	if(pInputKeyboard->GetKeyTrigger(DIK_F12))
	//	{
	//		if(m_CameraMode==DEBUG_MODE)
	//		{
	//			m_CameraMode=RELEASE_MODE;

	//			posModel = pPlayerM->GetPos();
	//			rotModel = pPlayerM->GetRot();
	//			CCamera :: Init();

	//			//�ړI�̎��_�ݒ�
	//			m_posCameraPDest.x= posModel.x;
	//			m_posCameraPDest.y= posModel.y+75;
	//			m_posCameraPDest.z= posModel.z+150;
	//				
	//			//�ړI�̒����_�ݒ�
	//			m_posCameraRDest.x= m_posPointView.x - sinf(rotModel.y)*45;
	//			m_posCameraRDest.y= m_posPointView.y -10;
	//			m_posCameraRDest.z= m_posPointView.z - cosf(rotModel.y)*30;

	//		}else
	//		{
	//			m_CameraMode=DEBUG_MODE;
	//		}
	//	}

		////�J�����̃��[�h�̐؂�ւ�
		//if((pInputKeyboard->GetKeyTrigger(DIK_F10))||(pInputKeyboard->GetKeyTrigger(DIK_F)))
		////if(pInputKeyboard->GetKeyTrigger(DIK_F10))
		//{
		//	if(m_CameraMode==SKILL_MODE)
		//	{
		//		m_CameraMode=RELEASE_MODE;

		//		posModel = pPlayerM->GetPos();
		//		rotModel = pPlayerM->GetRot();
		//		CCamera :: Init();

		//		//�ړI�̎��_�ݒ�
		//		m_posCameraPDest.x= posModel.x;
		//		m_posCameraPDest.y= posModel.y+75;
		//		m_posCameraPDest.z= posModel.z+150;
		//			
		//		//�ړI�̒����_�ݒ�
		//		m_posCameraRDest.x= m_posPointView.x - sinf(rotModel.y)*45;
		//		m_posCameraRDest.y= m_posPointView.y -10;
		//		m_posCameraRDest.z= m_posPointView.z - cosf(rotModel.y)*30;
		//	}else
		//	{
		//		m_CameraMode=SKILL_MODE;
		//		m_fCountSkillY=0;
		//		m_fCountSkillX=0;
		//	}
		//}


		//�J���������ύX
		//m_rotCamera.y = atan2f((m_posCameraR.x-m_posCameraP.x),(m_posCameraR.z-m_posCameraP.z));
		//m_rotCamera.x = atan2f((m_posCameraR.z-m_posCameraP.z),(m_posCameraR.y-m_posCameraP.y));
	}

}
//=============================================================================
// �Q�[��
//=============================================================================
void CCamera :: SceneGame(void)
{
	int phase = CGame::GetPhase();
	switch (phase)
	{
	case START_PHASE:	StartCamera(); break;
	case SCENARIO_PHASE:ShotCamera(); break;
	case ANGLE_PHASE:	ShotCamera(); break;
	case POWER_PHASE:	PowerCamera(); break;
	case MOVE_PHASE:	MoveCamera(); break;
	case JUDGE_PHASE:	JudgeCamera(); break;
	case END_PHASE:		JudgeCamera(); break;
	case CHANGE_PHASE:	ChangeCamera(); break;
	}
}
//=============================================================================
// �`��
//=============================================================================
void CCamera :: Set(LPDIRECT3DDEVICE9 pDevice)
{
	//�r���[�}�g���b�N�X�̐ݒ�
	CDebugProc::Print("%f,%f,%f\n", m_posCameraP.x, m_posCameraP.y, m_posCameraP.z);
	D3DXMatrixIdentity(&m_mtxView);
	D3DXMatrixLookAtLH(&m_mtxView,&m_posCameraP,&m_posCameraR,&m_posCameraU);
	pDevice->SetTransform(D3DTS_VIEW,&m_mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	D3DXMatrixIdentity(&m_mtxProjection);

	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,D3DX_PI/4.0f,(float)SCREEN_WIDTH/SCREEN_HEIGHT,10.0f,10000.0f);
	pDevice->SetTransform(D3DTS_PROJECTION,&m_mtxProjection);
}
//=============================================================================
// �L�����N�^�[�J�n����
//=============================================================================
void CCamera::StartCamera(void)
{
	D3DXVECTOR3 posModel = CGame::GetPlayerCamera();
	D3DXVECTOR3 rotModel = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 moveModel = D3DXVECTOR3(0, 0, 0);

	//�{�[���̎󂯎��
	CBall *pBall;
	pBall = CGame::GetBall(CGame::GetPlayerCount());

	m_posCameraP = posModel;
	m_posCameraR = pBall->GetPos();

	//�{�[���̈ʒu�������擾
	D3DXVECTOR3 EposModel = pBall->GetPos();
	D3DXVECTOR3 ErotModel = D3DXVECTOR3(0, 0, 0);

	Distance = (float)sqrt((double)(posModel.x - EposModel.x)*(double)(posModel.x - EposModel.x) + (double)(posModel.y - EposModel.y)*(double)(posModel.y - EposModel.y) + (double)(posModel.z - EposModel.z)*(double)(posModel.z - EposModel.z));

	//�����_���W�ݒ�
	m_posCameraP = posModel + D3DXVECTOR3(250.0f, 250.0f, 250.0f);
	m_posCameraR = posModel;
}
//=============================================================================
// �ˏo�p�x�ݒ�t�F�C�Y
//=============================================================================
void CCamera :: ShotCamera(void)
{
	D3DXVECTOR3 posModel = CGame::GetPlayerCamera();
	D3DXVECTOR3 rotModel = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 moveModel = D3DXVECTOR3(0, 0, 0);

	//�{�[���̎󂯎��
	CBall *pBall;
	pBall = CGame::GetBall(CGame::GetPlayerCount());

	//�{�[���̈ʒu�������擾
	D3DXVECTOR3 EposModel = pBall->GetPos();
	D3DXVECTOR3 ErotModel = CGame::GetVectorShot();

	Distance = (float)sqrt((double)(posModel.x - EposModel.x)*(double)(posModel.x - EposModel.x) + (double)(posModel.y - EposModel.y)*(double)(posModel.y - EposModel.y) + (double)(posModel.z - EposModel.z)*(double)(posModel.z - EposModel.z));

	//�����_���W�ݒ�
	//m_posPointView = pBall->GetPos();
	m_posCameraP = posModel;
	m_posCameraR = EposModel;
	//m_posCameraP = posModel;
}
//=============================================================================
// �{�[�������Ă�Ȃ�
//=============================================================================
void CCamera::MoveCamera(void)
{
	D3DXVECTOR3 posModel = CGame::GetPlayerCamera();
	D3DXVECTOR3 rotModel = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 moveModel = D3DXVECTOR3(0, 0, 0);

	//�{�[���̎󂯎��
	CBall *pBall;
	pBall = CGame::GetBall(CGame::GetPlayerCount());

	m_posCameraP = posModel;
	m_posCameraR = pBall->GetPos();

	//�{�[���̈ʒu�������擾
	D3DXVECTOR3 EposModel = pBall->GetPos();
	D3DXVECTOR3 ErotModel = CGame::GetVectorShot();

	Distance = (float)sqrt((double)(posModel.x - EposModel.x)*(double)(posModel.x - EposModel.x) + (double)(posModel.y - EposModel.y)*(double)(posModel.y - EposModel.y) + (double)(posModel.z - EposModel.z)*(double)(posModel.z - EposModel.z));

	//�����_���W�ݒ�
	m_posCameraP = EposModel + ErotModel * -200.0f;
	m_posCameraR = EposModel;
	//m_posPointView = pBall->GetPos();
}
//=============================================================================
// �~�܂������̃W���b�W
//=============================================================================
void CCamera::JudgeCamera(void)
{
	D3DXVECTOR3 posModel = CGame::GetPlayerCamera();
	D3DXVECTOR3 rotModel = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 moveModel = D3DXVECTOR3(0, 0, 0);

	//�{�[���̎󂯎��
	CBall *pBall;
	pBall = CGame::GetBall(CGame::GetPlayerCount());

	m_posCameraP = posModel;
	m_posCameraR = pBall->GetPos();

	//�{�[���̈ʒu�������擾
	D3DXVECTOR3 EposModel = pBall->GetPos();
	D3DXVECTOR3 ErotModel = CGame::GetVectorShot();

	Distance = (float)sqrt((double)(posModel.x - EposModel.x)*(double)(posModel.x - EposModel.x) + (double)(posModel.y - EposModel.y)*(double)(posModel.y - EposModel.y) + (double)(posModel.z - EposModel.z)*(double)(posModel.z - EposModel.z));

	//�����_���W�ݒ�
	m_posCameraP = posModel;
	m_posCameraR = EposModel;
}
//=============================================================================
// �͌��߂����
//=============================================================================
void CCamera::PowerCamera(void)
{

	//�v���C���[�̈ʒu�������擾
	D3DXVECTOR3 posModel = CGame::GetPlayerCamera();
	D3DXVECTOR3 rotModel = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 moveModel = D3DXVECTOR3(0, 0, 0);

	//�{�[���̎󂯎��
	CBall *pBall;
	pBall = CGame::GetBall(CGame::GetPlayerCount());

	m_posCameraP = posModel;
	m_posCameraR = pBall->GetPos();

	//�{�[���̈ʒu�������擾
	D3DXVECTOR3 EposModel = pBall->GetPos();
	D3DXVECTOR3 ErotModel = CGame::GetVectorShot();

	Distance = (float)sqrt((double)(posModel.x - EposModel.x)*(double)(posModel.x - EposModel.x) + (double)(posModel.y - EposModel.y)*(double)(posModel.y - EposModel.y) + (double)(posModel.z - EposModel.z)*(double)(posModel.z - EposModel.z));

	//�����_���W�ݒ�
	m_posCameraP = m_posCameraR + ErotModel * -150.0f;
	m_posCameraR = EposModel;
}
//=============================================================================
// �Q�[��
//=============================================================================
void CCamera::ChangeCamera(void)
{
}
/////////////EOF////////////