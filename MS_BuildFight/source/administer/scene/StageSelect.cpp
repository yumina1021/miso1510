//=============================================================================
//
// MS_BuildFight [CStageSelect.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "StageSelect.h"

#include "../Input.h"
#include "../Maneger.h"
#include "../Sound.h"

#include "../../module/etc/Fade.h"
#include "../../module/ui/BackGround.h"
#include "../../module/ui/CharPicture.h"
#include "../../module/ui/Effect.h"
#include "../../module/ui/Cursor.h"
#include "../../module/ui/Button.h"

#include "../../module/etc/Camera.h"

#include "../../module/etc/Ball.h"
#include "../../form/formX.h"
#include "../../form/form3D.h"
#include "../../module/field/Field.h"

#include "../../administer/Debugproc.h"

#include "../wiicon/wiimote.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
const float CURSOR_MOVE_COFF(10.0f);
const float STAGE_DIST_CENT(300.0f);
const float CAMERA_POS_X(0.0f);
const float CAMERA_POS_Y(0.0f);
const float CAMERA_POS_Z(-500.0f);

LPSTR pModName[MAX_BALL]
{

	"data/MODEL/stage1.x",
	"data/MODEL/stage2.x",
	"data/MODEL/stage3.x",
	"data/MODEL/stage4.x",

};

//*****************************************************************************
// グローバル変数
//*****************************************************************************
float cnt = 0.0f;
D3DXVECTOR3 tmpRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//=============================================================================
// コンストラクタ
//=============================================================================
CStageSelect::CStageSelect(void):
m_fTime(0.0f),
m_nState(STATE::NORMAL)
{
	m_pBackGround = NULL;
	m_pFade = NULL;
	
	// カメラの取得
	CCamera* pTmpCamera = CManager::GetCamera();

	pTmpCamera->SetPosP(D3DXVECTOR3(CAMERA_POS_X, CAMERA_POS_Y, CAMERA_POS_Z));

}
//=============================================================================
// デストラクタ
//=============================================================================
CStageSelect :: ~CStageSelect(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CStageSelect :: Init(LPDIRECT3DDEVICE9 pDevice)
{
	//背景の作成
	m_pBackGround = Cform3D::Create(pDevice, "data/TEXTURE/Select.png", D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//フェードの作成
	m_pFade=CFade::Create(pDevice,1);

	//サウンド取得の作成
	CSound *pSound;
	pSound = CManager::GetSound();

	//サウンド再生の作成
	//pSound->Play(SOUND_LABEL_BGM004);

	m_playerData[0].pCursor = CCursor::Create(pDevice, s_4, D3DXVECTOR3(1000.0f, 600.0f, 0.0f), 128, 128);
	m_playerData[0].nSelectNum = 0;

	m_playerData[1].pCursor = CCursor::Create(pDevice, s_5, D3DXVECTOR3(400.0f, 600.0f, 0.0f), 128, 128);
	m_playerData[1].nSelectNum = 0;

	m_fDiffuse=1.0f;

	m_bVsSelectFlag = CScene::GetVSFlag();

	m_bTitleBackFlag=false;

	m_pFade->StartFade(FADE_OUT,50,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
	m_bSendData=false;

	float fTmpRad = (D3DX_PI * 2.0f) / MAX_BALL;
	float tmpRot((D3DX_PI * 2.0f));

	for (int i = 0; i < MAX_BALL; i++)
	{
		m_Obj[i].pDispObj = CformX::Create(pDevice, pModName[i], D3DXVECTOR3(0.0f, 100.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_Obj[i].fLenCoff = fTmpRad * static_cast<float>(i);
		m_Obj[i].fLenCoffDest = m_Obj[i].fLenCoff;
		m_Obj[i].nDestCnt = i;

		D3DXVECTOR3 tmpObjPos;
		tmpObjPos = m_Obj[i].pDispObj->GetPos();

		//		// 衛星軌道用の係数をイージング曲線で求める
		m_Obj[i].fLenCoff = CCursor::EsasingNone(m_Obj[i].fLenCoff, m_Obj[m_Obj[i].nDestCnt].fLenCoffDest, m_fTime);

		// 原点0を中心として衛星軌道用の座標を求める
		tmpObjPos.x = 0.0f + sinf(m_Obj[i].fLenCoff) * STAGE_DIST_CENT;
		tmpObjPos.y = 0.0f;
		tmpObjPos.z = 0.0f + cosf(m_Obj[i].fLenCoff) * -STAGE_DIST_CENT;

		// 座標を更新
		m_Obj[i].pDispObj->SetPos(tmpObjPos);
	}

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CStageSelect :: Uninit(void)
{
	//サウンド取得の作成
	CSound *pSound;
	pSound = CManager::GetSound();

	//サウンド再生の作成
	pSound->Stop();



	//シーンを全て終了
	Cform::ReleaseAll();
}
//=============================================================================
// 更新
//=============================================================================
void CStageSelect :: Update(void)
{

	//現在の状態によって分岐
	switch (m_nState)
	{
	case STATE::NORMAL:

		// ボタンでステージを選択
		SelectByButton();

		break;

	case STATE::SATELLITE_ORBIT:

		// 衛星軌道時の
		UpdateSelectObject();

		break;

	case STATE::CHANGE_SCENE:
		UpdateFade();

		break;
	default:
		break;
	}


	
#ifdef _DEBUG

	CDebugProc::Print("選択中のボタン:%d\n", m_playerData[0].nSelectNum);

#endif
}
//=============================================================================
// 描画
//=============================================================================
void CStageSelect :: Draw(void)
{
	m_pBackGround->Draw();

	for (int i = 0; i < MAX_BALL; i++)
	{

		m_Obj[i].pDispObj->Draw();

	}

	for (int i = 0; i < 2; i++)
	{
		m_playerData[i].pCursor->Draw();

	}
	//フェードの作成
	m_pFade->Draw();
}
//=============================================================================
// 描画
//=============================================================================
void CStageSelect::UpdateSelectObject()
{
	D3DXVECTOR3 tmpObjPos;

	for (int i = 0; i < MAX_BALL; i++)
	{

		tmpObjPos = m_Obj[i].pDispObj->GetPos();

		//		// 衛星軌道用の係数をイージング曲線で求める
		m_Obj[i].fLenCoff = CCursor::EsasingNone(m_Obj[i].fLenCoff, m_Obj[m_Obj[i].nDestCnt].fLenCoffDest, m_fTime);

		// 原点0を中心として衛星軌道用の座標を求める
		tmpObjPos.x = 0.0f + sinf(m_Obj[i].fLenCoff) * STAGE_DIST_CENT;
		tmpObjPos.y = 0.0f;
		tmpObjPos.z = 0.0f + cosf(m_Obj[i].fLenCoff) * -STAGE_DIST_CENT;

		// 座標を更新
		m_Obj[i].pDispObj->SetPos(tmpObjPos);

#ifdef _DEBUG

		//CDebugProc::Print("X座標:%f\n", tmpObjPos.x);
		//CDebugProc::Print("Z座標:%f\n", tmpObjPos.z);
		CDebugProc::Print("衛星軌道用の係数:%f\n", m_Obj[i].fLenCoff);

#endif

	}

	// イージング曲線用タイマーの更新
	if (m_fTime >= 1.0f)
	{
		m_fTime = 0.0f;

		m_nState = STATE::NORMAL;

		for (int i = 0; i < MAX_BALL; i++)
		{
			m_Obj[i].fLenCoff = m_Obj[m_Obj[i].nDestCnt].fLenCoffDest;
		}
	}
	else
	{
		m_fTime += 0.025f;
	}

}
//=============================================================================
// フェードの更新
//=============================================================================
void CStageSelect::UpdateFade(void)
{
	//フェードインが終わったら
	if (m_pFade->GetFade() == FADE_IN_END)
	{
		if (m_bTitleBackFlag == false)
		{
			//次のフェーズを変える
			CManager::SetAfterScene(PHASETYPE_GAME);
		}
		else
		{
			//次のフェーズを変える
			CManager::SetAfterScene(PHASETYPE_TITLE);
		}
	}
}
//=============================================================================
// キーボードでの選択
//=============================================================================
void CStageSelect::SelectByButton(void)
{

	// Wiiコンの取得
	WiiRemote* pTmpPad = CManager::GetWii(1);

	//サウンド取得の作成
	CSound *pSound;
	pSound = CManager::GetSound();

	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	float fTmpRad = (D3DX_PI * 2.0f) / MAX_BALL;
	float tmpRot((D3DX_PI * 2.0f));

	//エンターキーが押された場合
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || pTmpPad->GetKeyTrigger(WII_BUTTOM_A))
	{

		// 遷移処理
		m_nState = STATE::CHANGE_SCENE;

		// 選択したマップを保存
		CManager::SetSelectMap(m_playerData[0].nSelectNum);

		m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		//pSound->PlayVoice(m_playerData[0].nSelectNum,VOICE_LABEL_SE_START);

	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_A) || pInputKeyboard->GetKeyTrigger(DIK_LEFT) || pTmpPad->GetKeyTrigger(WII_BUTTOM_LEFT))
	{

		//pSound->Play(SOUND_LABEL_SE_SELECT000);

		m_playerData[0].nSelectNum--;
		NomalizeSelectObject(m_playerData[0].nSelectNum);

		for (int i = 0; i < MAX_BALL; i++)
		{
			m_Obj[i].nDestCnt--;
			NomalizeSelectObject(m_Obj[i].nDestCnt);
			
			if (m_Obj[i].fLenCoff <= 0.0f)
			{
				m_Obj[i].fLenCoff = tmpRot;
			}
		}
		m_fTime = 0.0f;

		m_nState = STATE::SATELLITE_ORBIT;

	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_D) || pInputKeyboard->GetKeyTrigger(DIK_RIGHT) || pTmpPad->GetKeyTrigger(WII_BUTTOM_RIGHT))
	{
		//pSound->Play(SOUND_LABEL_SE_SELECT000);

		m_playerData[0].nSelectNum++;
		NomalizeSelectObject(m_playerData[0].nSelectNum);

		for (int i = 0; i < MAX_BALL; i++)
		{
			m_Obj[i].nDestCnt++;
			NomalizeSelectObject(m_Obj[i].nDestCnt);

			if (m_Obj[i].fLenCoff >= tmpRot - fTmpRad)
			{
				m_Obj[i].fLenCoff = 0.0f - fTmpRad;
			}


		}
		m_fTime = 0.0f;

		m_nState = STATE::SATELLITE_ORBIT;

	}
	
}
//=============================================================================
// カール移動での選択
//=============================================================================
bool CStageSelect::HitChkRect(const D3DXVECTOR3& paramPos1,
							const D3DXVECTOR3& paramPos2,
							const D3DXVECTOR3& paramLen1,
							const D3DXVECTOR3& paramLen2){

	if (abs(paramPos1.x - paramPos2.x) < (paramLen1.x * 0.5f + paramLen2.x * 0.5f) //横の判定
		&& abs(paramPos1.y - paramPos2.y) < (paramLen1.y * 0.5f + paramLen2.y * 0.5f)) //縦の判定
	{

		// 当たった
		return true;

	}

	// 当たってない
	return false;


}
//=============================================================================
// 正規化
//=============================================================================
void CStageSelect::NomalizeSelectObject(int& nParamVal)
{
	// 各配置によって移動する
	if (nParamVal < 0)
	{

		nParamVal = MAX_BALL - 1;

	}
	else if (nParamVal >= MAX_BALL)
	{

		nParamVal = 0;

	}

}////////////EOF////////////