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
// インクルードファイル
//*****************************************************************************
#include "../../common.h"

#define CAMERA_MOVE_SPEED (2.0f)		//カメラ移動速度

typedef enum							//カメラのモード
{
	DEBUG_MODE =0,
	GAMEEND_MODE,
	RELEASE_MODE,
	SKILL_MODE
}CAMERA;
//*****************************************************************************
// クラス定義
//*****************************************************************************

class CCamera
{
	public:
		CCamera(void);				//コンストラクタ
		~CCamera(void);				//デストラクタ

		HRESULT Init(void);						//初期化
		void Uninit(void);						//終了
		void Update(void);						//更新
		void Set(LPDIRECT3DDEVICE9 pDevice);	//描画

		D3DXVECTOR3 GetRotCamera(void){return m_rotCamera;};							//カメラの向き受け渡し
		D3DXMATRIX GetMtxView (void){return m_mtxView;};		//ビューマトリクス受け渡し
		D3DXVECTOR3 GetPointView(void){return m_posPointView;};	//注視点の受け渡し

		D3DXVECTOR3 GetPosP(void){ return m_posCameraP; }
		D3DXVECTOR3 GetPosR(void){ return m_posCameraR; }
		D3DXVECTOR3 GetVecUp(void){ return m_posCameraU; }
	private:

		D3DXVECTOR3	m_posCameraP;	//カメラの視点
		D3DXVECTOR3	m_posCameraR;	//カメラの注視点
		D3DXVECTOR3	m_posCameraU;	//カメラの上方向ベクトル

		D3DXVECTOR3	m_rotCamera;	//カメラの向き

		D3DXMATRIX	m_mtxView;		//ビューマトリクス
		D3DXMATRIX	m_mtxProjection;//プロジェクションマトリクス

		float		m_fVectCamera;	//視点から注視点までの距離
		float		m_fVectCamera2;

		float		Distance;

		D3DXVECTOR3	m_posCameraPDest;//目的の視点
		D3DXVECTOR3	m_posCameraRDest;//目的の注視点

		CAMERA		m_CameraMode;	//カメラのモード
		D3DXVECTOR3 m_posPointView;	//注視点の場所

		//現在未使用
		float		m_fCountSkillY;
		float		m_fCountSkillX;


};

#endif

/////////////EOF////////////