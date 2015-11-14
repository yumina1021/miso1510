//=============================================================================
//
// MS_BuildFight [CCamera.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "Camera.h"

#include "../robot/PlayerM.h"
#include "../robot/EnemyM.h"

#include "../../administer/Input.h"
#include "../../administer/Maneger.h"
#include "../../administer/Debugproc.h"

#include "../../administer/scene/Game.h"
#include "../../module/etc/Ball.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CCamera :: CCamera(void)
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CCamera :: ~CCamera(void)
{
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CCamera :: Init(void)
{
	//座標初期化
	m_posCameraP = D3DXVECTOR3(0.0f,50.0f,+200.0f);
	m_posCameraR = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_posCameraU = D3DXVECTOR3(0.0f,1.0f,0.0f);

	//ベクトルの初期化
	m_fVectCamera = sqrtf((m_posCameraR.x-m_posCameraP.x)*(m_posCameraR.x-m_posCameraP.x)+(m_posCameraR.z-m_posCameraP.z)*(m_posCameraR.z-m_posCameraP.z));
	m_fVectCamera2 = sqrtf((m_posCameraR.z-m_posCameraP.z)*(m_posCameraR.z-m_posCameraP.z)+(m_posCameraR.y-m_posCameraP.y)*(m_posCameraR.y-m_posCameraP.y));
	
	//視点から注視点への角度を設定
	m_rotCamera.y = atan2f((m_posCameraR.x-m_posCameraP.x),(m_posCameraR.z-m_posCameraP.z));
	m_rotCamera.x = atan2f((m_posCameraR.z-m_posCameraP.z),(m_posCameraR.y-m_posCameraP.y));

	//モードの初期化
	m_CameraMode= RELEASE_MODE;

	//注視点の初期化
	m_posPointView=D3DXVECTOR3(0.0f,0.0f,0.0f);

	Distance=0.0f;

	//未使用
	//m_fCountSkillY=0;
	//m_fCountSkillX=0;

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CCamera :: Uninit(void)
{
}
//=============================================================================
// 更新
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
	//			//目的の視点設定
	//			m_posCameraPDest.x = posModel.x - sinf(ErotModel.y) * 150;
	//			m_posCameraPDest.y = posModel.y + 75;
	//			m_posCameraPDest.z = posModel.z - cosf(ErotModel.y) * 200;

	//			//目的の注視点設定
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
	//			//現在の注視点に目的の注視点との差を足していく
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

	//				//目的の注視点設定
	//				m_posCameraRDest.x = m_posPointView.x;
	//				m_posCameraRDest.y = m_posPointView.y - 10;
	//				m_posCameraRDest.z = m_posPointView.z;
	//				break;
	//		//現在未使用


	//		case SKILL_MODE:
	//					//目的の視点設定
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

	//						//目的の視点設定
	//						m_posCameraPDest.x= posModel.x;
	//						m_posCameraPDest.y= posModel.y+75;
	//						m_posCameraPDest.z= posModel.z+150;
	//				
	//						//目的の注視点設定
	//						m_posCameraRDest.x= m_posPointView.x - sinf(rotModel.y)*45;
	//						m_posCameraRDest.y= m_posPointView.y -10;
	//						m_posCameraRDest.z= m_posPointView.z - cosf(rotModel.y)*30;
	//					}

	//					//目的の注視点設定
	//					m_posCameraRDest.x= posModel.x;
	//					m_posCameraRDest.y= posModel.y+(100+(m_fCountSkillY));
	//					m_posCameraRDest.z= posModel.z;

	//					//現在の視点に目的の視点との差を足していく
	//					m_posCameraP.x+=(m_posCameraPDest.x-m_posCameraP.x)*0.12f;
	//					m_posCameraP.y+=(m_posCameraPDest.y-m_posCameraP.y);
	//					m_posCameraP.z+=(m_posCameraPDest.z-m_posCameraP.z)*0.12f;

	//					//現在の注視点に目的の注視点との差を足していく
	//					m_posCameraR.x+=(m_posCameraRDest.x-m_posCameraR.x)*0.14f;
	//					m_posCameraR.y+=(m_posCameraRDest.y-m_posCameraR.y);
	//					m_posCameraR.z+=(m_posCameraRDest.z-m_posCameraR.z)*0.14f;
	//					break;

	//		case DEBUG_MODE:

	//					//カメラの移動
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

	//					//カメラの昇降
	//					if(pInputKeyboard->GetKeyPress(DIK_Y))
	//					{
	//						m_posCameraP.y +=2;
	//					}
	//					else if(pInputKeyboard->GetKeyPress(DIK_N))
	//					{
	//						m_posCameraP.y -=2;
	//					}

	//					//カメラの旋回
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

	//					//カメラの首ふり
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

	//	//カメラのモードの切り替え
	//	if(pInputKeyboard->GetKeyTrigger(DIK_F12))
	//	{
	//		if(m_CameraMode==DEBUG_MODE)
	//		{
	//			m_CameraMode=RELEASE_MODE;

	//			posModel = pPlayerM->GetPos();
	//			rotModel = pPlayerM->GetRot();
	//			CCamera :: Init();

	//			//目的の視点設定
	//			m_posCameraPDest.x= posModel.x;
	//			m_posCameraPDest.y= posModel.y+75;
	//			m_posCameraPDest.z= posModel.z+150;
	//				
	//			//目的の注視点設定
	//			m_posCameraRDest.x= m_posPointView.x - sinf(rotModel.y)*45;
	//			m_posCameraRDest.y= m_posPointView.y -10;
	//			m_posCameraRDest.z= m_posPointView.z - cosf(rotModel.y)*30;

	//		}else
	//		{
	//			m_CameraMode=DEBUG_MODE;
	//		}
	//	}

		////カメラのモードの切り替え
		//if((pInputKeyboard->GetKeyTrigger(DIK_F10))||(pInputKeyboard->GetKeyTrigger(DIK_F)))
		////if(pInputKeyboard->GetKeyTrigger(DIK_F10))
		//{
		//	if(m_CameraMode==SKILL_MODE)
		//	{
		//		m_CameraMode=RELEASE_MODE;

		//		posModel = pPlayerM->GetPos();
		//		rotModel = pPlayerM->GetRot();
		//		CCamera :: Init();

		//		//目的の視点設定
		//		m_posCameraPDest.x= posModel.x;
		//		m_posCameraPDest.y= posModel.y+75;
		//		m_posCameraPDest.z= posModel.z+150;
		//			
		//		//目的の注視点設定
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


		//カメラ向き変更
		//m_rotCamera.y = atan2f((m_posCameraR.x-m_posCameraP.x),(m_posCameraR.z-m_posCameraP.z));
		//m_rotCamera.x = atan2f((m_posCameraR.z-m_posCameraP.z),(m_posCameraR.y-m_posCameraP.y));
	}

}
//=============================================================================
// ゲーム
//=============================================================================
void CCamera :: SceneGame(void)
{
	int phase = CGame::GetPhase();
	switch (phase)
	{
	case START_PHASE:	StartCamera(); break;
	case ANGLE_PHASE:	ShotCamera(); break;
	case POWER_PHASE:	PowerCamera(); break;
	case MOVE_PHASE:	MoveCamera(); break;
	case JUDGE_PHASE:	JudgeCamera(); break;
	case END_PHASE:		JudgeCamera(); break;
	case CHANGE_PHASE:	ChangeCamera(); break;
	}
}
//=============================================================================
// 描画
//=============================================================================
void CCamera :: Set(LPDIRECT3DDEVICE9 pDevice)
{
	//ビューマトリックスの設定
	CDebugProc::Print("%f,%f,%f\n", m_posCameraP.x, m_posCameraP.y, m_posCameraP.z);
	D3DXMatrixIdentity(&m_mtxView);
	D3DXMatrixLookAtLH(&m_mtxView,&m_posCameraP,&m_posCameraR,&m_posCameraU);
	pDevice->SetTransform(D3DTS_VIEW,&m_mtxView);

	//プロジェクションマトリックスの設定
	D3DXMatrixIdentity(&m_mtxProjection);

	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,D3DX_PI/4.0f,(float)SCREEN_WIDTH/SCREEN_HEIGHT,10.0f,10000.0f);
	pDevice->SetTransform(D3DTS_PROJECTION,&m_mtxProjection);
}
//=============================================================================
// キャラクター開始処理
//=============================================================================
void CCamera::StartCamera(void)
{
	//プレイヤーの受け取り
	CPlayerM *pPlayerM;
	pPlayerM = CGame::GetPlayer(CGame::GetPlayerCount());

	//プレイヤーの位置＆向き取得
	D3DXVECTOR3 posModel = pPlayerM->GetPos();
	D3DXVECTOR3 rotModel = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 moveModel = D3DXVECTOR3(0, 0, 0);

	//ボールの受け取り
	CBall *pBall;
	pBall = CGame::GetBall(CGame::GetPlayerCount());

	m_posCameraP = posModel;
	m_posCameraR = pBall->GetPos();

	//ボールの位置＆向き取得
	D3DXVECTOR3 EposModel = pBall->GetPos();
	D3DXVECTOR3 ErotModel = D3DXVECTOR3(0, 0, 0);

	Distance = (float)sqrt((double)(posModel.x - EposModel.x)*(double)(posModel.x - EposModel.x) + (double)(posModel.y - EposModel.y)*(double)(posModel.y - EposModel.y) + (double)(posModel.z - EposModel.z)*(double)(posModel.z - EposModel.z));

	//注視点座標設定
	m_posCameraP = posModel + D3DXVECTOR3(250.0f, 250.0f, 250.0f);
	m_posCameraR = posModel;
}
//=============================================================================
// 射出角度設定フェイズ
//=============================================================================
void CCamera :: ShotCamera(void)
{
	//プレイヤーの受け取り
	// hack 複数プレイヤー
	CPlayerM *pPlayerM;
	pPlayerM = CGame::GetPlayer(CGame::GetPlayerCount());

	//プレイヤーの位置＆向き取得
	D3DXVECTOR3 posModel = pPlayerM->GetPos();
	D3DXVECTOR3 rotModel = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 moveModel = D3DXVECTOR3(0, 0, 0);

	//ボールの受け取り
	CBall *pBall;
	pBall = CGame::GetBall(CGame::GetPlayerCount());

	//ボールの位置＆向き取得
	D3DXVECTOR3 EposModel = pBall->GetPos();
	D3DXVECTOR3 ErotModel = D3DXVECTOR3(0, 0, 0);

	Distance = (float)sqrt((double)(posModel.x - EposModel.x)*(double)(posModel.x - EposModel.x) + (double)(posModel.y - EposModel.y)*(double)(posModel.y - EposModel.y) + (double)(posModel.z - EposModel.z)*(double)(posModel.z - EposModel.z));

	//注視点座標設定
	//m_posPointView = pBall->GetPos();
	m_posCameraP = posModel;
	m_posCameraR = pBall->GetPos();
	//m_posCameraP = posModel;
}
//=============================================================================
// ボール動いてるなう
//=============================================================================
void CCamera::MoveCamera(void)
{
	//プレイヤーの受け取り
	CPlayerM *pPlayerM;
	pPlayerM = CGame::GetPlayer(CGame::GetPlayerCount());

	//プレイヤーの位置＆向き取得
	D3DXVECTOR3 posModel = pPlayerM->GetPos();
	D3DXVECTOR3 rotModel = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 moveModel = D3DXVECTOR3(0, 0, 0);

	//ボールの受け取り
	CBall *pBall;
	pBall = CGame::GetBall(CGame::GetPlayerCount());

	m_posCameraP = posModel;
	m_posCameraR = pBall->GetPos();

	//ボールの位置＆向き取得
	D3DXVECTOR3 EposModel = pBall->GetPos();
	D3DXVECTOR3 ErotModel = D3DXVECTOR3(0, 0, 0);

	Distance = (float)sqrt((double)(posModel.x - EposModel.x)*(double)(posModel.x - EposModel.x) + (double)(posModel.y - EposModel.y)*(double)(posModel.y - EposModel.y) + (double)(posModel.z - EposModel.z)*(double)(posModel.z - EposModel.z));

	//注視点座標設定
	m_posCameraP = posModel;
	m_posCameraR = EposModel;
	//m_posPointView = pBall->GetPos();
}
//=============================================================================
// 止まった時のジャッジ
//=============================================================================
void CCamera::JudgeCamera(void)
{
	//プレイヤーの受け取り
	CPlayerM *pPlayerM;
	pPlayerM = CGame::GetPlayer(CGame::GetPlayerCount());

	//プレイヤーの位置＆向き取得
	D3DXVECTOR3 posModel = pPlayerM->GetPos();
	D3DXVECTOR3 rotModel = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 moveModel = D3DXVECTOR3(0, 0, 0);

	//ボールの受け取り
	CBall *pBall;
	pBall = CGame::GetBall(CGame::GetPlayerCount());

	m_posCameraP = posModel;
	m_posCameraR = pBall->GetPos();

	//ボールの位置＆向き取得
	D3DXVECTOR3 EposModel = pBall->GetPos();
	D3DXVECTOR3 ErotModel = D3DXVECTOR3(0, 0, 0);

	Distance = (float)sqrt((double)(posModel.x - EposModel.x)*(double)(posModel.x - EposModel.x) + (double)(posModel.y - EposModel.y)*(double)(posModel.y - EposModel.y) + (double)(posModel.z - EposModel.z)*(double)(posModel.z - EposModel.z));

	//注視点座標設定
	m_posCameraP = posModel;
	m_posCameraR = EposModel;
}
//=============================================================================
// 力決めだんべ
//=============================================================================
void CCamera::PowerCamera(void)
{
	//プレイヤーの受け取り
	CPlayerM *pPlayerM;
	pPlayerM = CGame::GetPlayer(CGame::GetPlayerCount());

	//プレイヤーの位置＆向き取得
	D3DXVECTOR3 posModel = pPlayerM->GetPos();
	D3DXVECTOR3 rotModel = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 moveModel = D3DXVECTOR3(0, 0, 0);

	//ボールの受け取り
	CBall *pBall;
	pBall = CGame::GetBall(CGame::GetPlayerCount());

	m_posCameraP = posModel;
	m_posCameraR = pBall->GetPos();

	//ボールの位置＆向き取得
	D3DXVECTOR3 EposModel = pBall->GetPos();
	D3DXVECTOR3 ErotModel = D3DXVECTOR3(0, 0, 0);

	Distance = (float)sqrt((double)(posModel.x - EposModel.x)*(double)(posModel.x - EposModel.x) + (double)(posModel.y - EposModel.y)*(double)(posModel.y - EposModel.y) + (double)(posModel.z - EposModel.z)*(double)(posModel.z - EposModel.z));

	//注視点座標設定
	m_posCameraP = posModel;
	m_posCameraR = EposModel;
}
//=============================================================================
// ゲーム
//=============================================================================
void CCamera::ChangeCamera(void)
{
}
/////////////EOF////////////