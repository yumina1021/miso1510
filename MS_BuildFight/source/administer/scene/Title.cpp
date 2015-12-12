//=============================================================================
//
// MS_BuildFight [CTitle.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "Title.h"
#include "../Input.h"
#include "../Maneger.h"
#include "../Sound.h"

#include "../../module/ui/BackGround.h"
#include "../../module/ui/Button.h"
#include "../../module/ui/Cursor.h"

#include "../../module/etc/Camera.h"
#include "../../module/field/Dome.h"
#include "../../module/field/Field.h"
#include "../../module/field/meshfielddata.h"
#include "../../module/field/Domeunder.h"
#include "../../form/formX.h"
#include "../../form/form2D.h"
#include "../../module/robot/PlayerM.h"

#include "../wiicon/wiimote.h"

#include "../../administer/Debugproc.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
const float CAMERA_POS_X(0.0f);
const float CAMERA_POS_Y(0.0f);
const float CAMERA_POS_Z(-5000.0f);
const float MENU_WIDTH(400.0f);			//メニューの横サイズ
const float MENU_HEIGHT(100.0f);			//メニューの縦サイズ
const float MENU_X((float)SCREEN_WIDTH / 2.0f - MENU_WIDTH / 2.0f);	//メニューのX位置
const float MENU_Y(675.0f);			//メニューのY位置

const float CHAR_POS_X((float)SCREEN_WIDTH / 2.0f);
const float CHAR_POS_Y(300.0f);
const float CHAR_WIDTH(450.0f);
const float CHAR_HEIGHT(600.0f);

const int LOGO_WIDTH(800.0f);			//メニューの横サイズ
const int LOGO_HEIGHT(250.0f);			//メニューの縦サイズ

//=============================================================================
// コンストラクタ
//=============================================================================
CTitle :: CTitle(void) : 
m_bChangeFlag(false),
m_nCursor(GAME_START),
m_fDiffuse(1.0f),
m_nType(SELECT_TYPE::TYPE_BUTTON)
{
	m_pBackGround = NULL;
	m_pFade = NULL;
	m_pMenueButton[0] = { };
	m_pMenueButton[1] = { };
	m_pMenueButton[2] = { };
	m_pMenueButton[3] = { };

	// カメラの取得
	CCamera* pTmpCamera = CManager::GetCamera();

	pTmpCamera->SetPosP(D3DXVECTOR3(CAMERA_POS_X, CAMERA_POS_Y, CAMERA_POS_Z));

}
//=============================================================================
// デストラクタ
//=============================================================================
CTitle :: ~CTitle(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CTitle :: Init(LPDIRECT3DDEVICE9 pDevice)
{

	//背景の作成
	//m_pBackGround=CBackGround::Create(pDevice,BACKGROUND_TITLE);

	m_pLogo = CButton::Create(pDevice, s_7, D3DXVECTOR3(SCREEN_WIDTH / 2, 500.0f, 0.0f), LOGO_WIDTH, LOGO_HEIGHT);
	m_pLogo->SetDiffuse(0.0f, 0.0f, 1.0f, 1.0f);

	//空の作成
	m_pDome = CDome::Create(pDevice, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//空の作成
	m_pDome2 = CDomeU::Create(pDevice, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//文字の配置
	m_pMenueButton[GAME_START] = CButton::Create(pDevice, t_stert, D3DXVECTOR3(MENU_X - 10.0f, MENU_Y, 0.0f), MENU_WIDTH, MENU_HEIGHT);
	m_pMenueButton[GAME_END] = CButton::Create(pDevice, t_end, D3DXVECTOR3(MENU_X + MENU_WIDTH + 10.0f, MENU_Y, 0.0f), MENU_WIDTH, MENU_HEIGHT);
	m_pCursor[0] = CCursor::Create(pDevice, s_4, D3DXVECTOR3(1000.0f, 600.0f, 0.0f), 64, 64);
	m_pCursor[1] = CCursor::Create(pDevice, s_4, D3DXVECTOR3(200.0f, 600.0f, 0.0f), 64, 64);

	// ロゴ用キャラクター
	//m_pCharcterPic[0] = Cform2D::Create(pDevice, "data/TEXTURE/Rosa.png", D3DXVECTOR3(CHAR_POS_X, CHAR_POS_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_WIDTH, CHAR_HEIGHT);
	//m_pCharcterPic[1] = Cform2D::Create(pDevice, "data/TEXTURE/Lila.png", D3DXVECTOR3(CHAR_POS_X - CHAR_WIDTH, CHAR_POS_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_WIDTH, CHAR_HEIGHT);
	//m_pCharcterPic[2] = Cform2D::Create(pDevice, "data/TEXTURE/Licht.png", D3DXVECTOR3(CHAR_POS_X + CHAR_WIDTH, CHAR_POS_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_WIDTH, CHAR_HEIGHT);

	// 選択状態にしておく
	m_pMenueButton[m_nCursor]->SetButtonState(BUTTON_STATE::SELECTED);

	//サウンド取得の作成
	CSound *pSound;
	pSound = CManager::GetSound();

	//サウンド再生の作成
	//pSound->Play(SOUND_LABEL_BGM000);


	//フェードの作成
	m_pFade = CFade::Create(pDevice, 1);
	m_pFade->StartFade(FADE_OUT,50,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),CManager::GetSelectChar(0));

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CTitle :: Uninit(void)
{
	//サウンド取得の作成
	CSound *pSound;
	pSound = CManager::GetSound();

	//サウンド再生の作成
	//pSound->Stop();

	//シーンを全て終了
	Cform::ReleaseAll();
}
//=============================================================================
// 更新
//=============================================================================
void CTitle :: Update(void)
{
	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//LookAround();
	CCamera* pTmpCamera = CManager::GetCamera();
	D3DXVECTOR3 fTmpRot = pTmpCamera->GetRotCamera();
	D3DXVECTOR3 fTmpPosR = pTmpCamera->GetPosR();
	D3DXVECTOR3 fTmpPosP = pTmpCamera->GetPosP();

	fTmpRot.y -= (D3DX_PI / 180.0f);

	// カメラ視点右
	fTmpPosR.x = fTmpPosP.x + sinf(fTmpRot.y / 180.0f * D3DX_PI) * -5000.0f;
	fTmpPosR.z = fTmpPosP.z + cosf(fTmpRot.y / 180.0f * D3DX_PI) * 5000.0f;

	pTmpCamera->SetRotCamera(fTmpRot);
	pTmpCamera->SetPosR(fTmpPosR);
	
	// 一時的に保存
	int tmpCursorOld = m_nCursor;

	UpdateFade();

	// F1キーが押された場合
	if (pInputKeyboard->GetKeyTrigger(DIK_1)
		&& m_bChangeFlag == false)
	{
		m_nType = SELECT_TYPE::TYPE_BUTTON;

	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_2)
		&& m_bChangeFlag == false)
	{
		m_pCursor[0]->SetTime(0.0f);
		m_nType = SELECT_TYPE::TYPE_CURSOR;

	}
	// ボタン選択
	if (m_nType == SELECT_TYPE::TYPE_BUTTON)
	{
		KeyCommand();
		m_pCursor[0]->SyncCharPos(m_pMenueButton[m_nCursor]->GetPos());

	}
	// カーソル移動
	else if (m_nType == SELECT_TYPE::TYPE_CURSOR)
	{
			SelectByCursor();
	}

	// 違うボタンに移ったら
	if (tmpCursorOld != m_nCursor)
	{
		CButton::ChangeSelectButtonState(m_pMenueButton[tmpCursorOld], m_pMenueButton[m_nCursor]);

	}

#ifdef _DEBUG

	CDebugProc::Print("選択中のボタン:%d\n", m_nCursor);
	CDebugProc::Print("モード選択:%d\n ※0:ボタン 1:カーソル", m_nType);

#endif
}
//=============================================================================
// 描画
//=============================================================================
void CTitle :: Draw(void)
{
	//m_pBackGround->Draw();

	m_pDome->Draw();
	m_pDome2->Draw();

	m_pMenueButton[GAME_START]->Draw();
	m_pMenueButton[GAME_END]->Draw();

	//文字
	for (int i = 0; i < 2; i++)
	{

		m_pCursor[i]->Draw();

	}

	for (int i = 0; i < 3; i++)
	{

		//m_pCharcterPic[i]->Draw();

	}

	m_pLogo->Draw();

	//フェード
	m_pFade->Draw();

}
//=============================================================================
// 入力
//=============================================================================
void CTitle::KeyCommand(void)
{

	// Wiiコンの取得
	WiiRemote* pTmpPad = CManager::GetWii(0);

	//サウンド取得の作成
	CSound *pSound;
	pSound = CManager::GetSound();

	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//エンターキーが押された場合
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || pTmpPad->GetKeyTrigger(WII_BUTTOM_A))
	{

		ChangeState();

	}
	else if (m_bChangeFlag != true)
	{

		if (pInputKeyboard->GetKeyTrigger(DIK_D) || pTmpPad->GetKeyTrigger(WII_BUTTOM_RIGHT))
		{
			m_nCursor--;
			//pSound->Play(SOUND_LABEL_SE_SELECT000);
			if (m_nCursor < GAME_START)
			{
				m_nCursor = GAME_END;
			}

		}
		else if (pInputKeyboard->GetKeyTrigger(DIK_A) || pTmpPad->GetKeyTrigger(WII_BUTTOM_LEFT))
		{
			m_nCursor++;
			//pSound->Play(SOUND_LABEL_SE_SELECT000);

			if (m_nCursor > GAME_END)
			{
				m_nCursor = GAME_START;
			}
		}
	}

}
//=============================================================================
// カール移動での選択
//=============================================================================
void CTitle::SelectByCursor(void){

	// 変数定義
	D3DXVECTOR3 tmpCurPos = m_pCursor[0]->GetPos();
	D3DXVECTOR3 tmpCharPos(0.0f, 0.0f, 0.0f);
	bool tmpOnFlg(false);
	D3DXVECTOR3 tmpCursorLen(0.0f, 0.0f, 0.0f);

	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//すべてのキャラ項目を対象に検索
	for (int i = 0; i < MAX; i++)
	{

		// 座標の取得
		tmpCharPos = m_pMenueButton[i]->GetPos();

		// 矩形でのあたり判定
		if (CCursor::HitChkRect(tmpCurPos, tmpCharPos, m_pCursor[0]->GetLen(), m_pMenueButton[i]->GetLen()))
		{

			// 当たっていることを記録
			tmpOnFlg = true;

			// 選択状態から解除
			m_pMenueButton[m_nCursor]->SetButtonState(BUTTON_STATE::PUSH_OFF);

			// 選択中のカーソルの更新
			m_nCursor = i;

			// 選択状態にしておく
			m_pMenueButton[m_nCursor]->SetButtonState(BUTTON_STATE::SELECTED);

			break;
		}
		else{


		}
	}
	// 決定ボタンを押したら
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{

		ChangeState();

	}// if
	else if (m_bChangeFlag != true)
	{
		m_pCursor[0]->MoveByKeybord();
	}


#ifdef _DEBUG

	CDebugProc::Print("マウス座標X:%f\n", tmpCurPos.x);
	CDebugProc::Print("マウス座標Y:%f\n", tmpCurPos.y);

#endif

}// SelectByCursor
//=============================================================================
// 状態の遷移
//=============================================================================
void CTitle::ChangeState(){

	//カーソルが合っているコマンドを発動
	switch (m_nCursor)
	{
		//スタート
	case 0: m_bChangeFlag = true;
		//pSound->Play(SOUND_LABEL_SE_SELECT001);
		if (m_pFade->GetPlayFade() == false)
		{
			m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f),CManager::GetSelectChar(0));
			CScene::SetVSFlag(false);
		}
		break;
		//エンド
	case 1:	m_bChangeFlag = false;
		//pSound->Play(SOUND_LABEL_SE_SELECT001);
		GameEnd();
		break;

	default: break;
	}
}
//=============================================================================
// 
//=============================================================================
void CTitle::UpdateFade(void)
{

	//フェードインが終わったら
	if (m_pFade->GetFade() == FADE_IN_END)
	{
		if (m_nCursor == 0 || m_nCursor == 1)
		{
			//次のフェーズを変える
			CScene::SetReplayFlag(false);
			CManager::SetAfterScene(PHASETYPE_SELECT);
		}
		else if (m_nCursor == 2)
		{
			//次のフェーズを変える
			CManager::SetAfterScene(PHASETYPE_TUTRIAL);
		}
	}
}
/////////////EOF////////////