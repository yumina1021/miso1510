//=============================================================================
//
// MS_BuildFight [CSelect.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "Select.h"

#include "../Input.h"
#include "../Maneger.h"
#include "../Sound.h"

#include "../../module/etc/Fade.h"
#include "../../module/ui/CharPicture.h"
#include "../../module/ui/Effect.h"
#include "../../module/ui/Button.h"
#include "../../module/ui/Cursor.h"
#include "../../module/etc/Camera.h"

#include "../../module/field/Domeunder.h"
#include "../../module/field/Dome.h"

#include "../../form/form3D.h"
#include "../../form/formX.h"
#include "../../module/robot/PlayerM.h"

#include "../../administer/Debugproc.h"

#include "../wiicon/wiimote.h"
#include "../Texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
const float CHAR_BUTTON_WIDTH(300.0f);
const float CHAR_BUTTON_HEIGHT(162.0f);

const float CHAR_NAME_WIDTH(400.0f);
const float CHAR_NAME_HEIGHT(200.5f);

const float CURSOR_WIDTH(100.0f);
const float CURSOR_HEIGHT(100.0f);

const float CAMERA_POS_X(0.0f);
const float CAMERA_POS_Y(0.0f);
const float CAMERA_POS_Z(-200.0f);
//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CSelect::CSelect(void) :
m_nType(SELECT_TYPE::TYPE_BUTTON),
m_bChangeFlag(false),
m_bVsSelectFlag(false),
m_bTitleBackFlag(false),
m_bSendData(false)
{

	m_pBackGround = NULL;
	m_pFade = NULL;
	m_pCharPicture[CHARCTER_TYPE::TYPE_MAX] = {};

	// カメラの取得
	CCamera* pTmpCamera = CManager::GetCamera();

	pTmpCamera->SetPosP(D3DXVECTOR3(CAMERA_POS_X, CAMERA_POS_Y, CAMERA_POS_Z));

	pTmpCamera->SetRotCamera(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pTmpCamera->SetPosR(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}
//=============================================================================
// デストラクタ
//=============================================================================
CSelect :: ~CSelect(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CSelect::Init(LPDIRECT3DDEVICE9 pDevice)
{
	int pModName[CHARCTER_TYPE::TYPE_MAX]
	{
		TEXTURE_STAGENAME1,
		TEXTURE_STAGENAME2,
		TEXTURE_STAGENAME3,
		TEXTURE_STAGENAME4,
	};

	int pCharNameTex[CHARCTER_TYPE::TYPE_MAX]
	{
		TEXTURE_CHARANAME1,
		TEXTURE_CHARANAME2,
		TEXTURE_CHARANAME3,
		TEXTURE_CHARANAME4,
	};

	//空の作成
	m_pDome = CDome::Create(pDevice, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//空の作成
	m_pDome2 = CDomeU::Create(pDevice, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//サウンド取得の作成
	CSound *pSound;
	pSound = CManager::GetSound();

	//サウンド再生の作成
	pSound->Play(SOUND_LABEL_BGM001);

	//背景の作成
	m_pBackGround = Cform3D::Create(pDevice, TEXTURE_SELECT, D3DXVECTOR3(0.0f, 0.0f, 406.0f), D3DXVECTOR3(-D3DX_PI / 2.0f, 0.0f, 0.0f), SCREEN_WIDTH-390, SCREEN_HEIGHT-220);
	m_pBackGround->SetDiffuse(1.0f, 1.0f, 1.0f, 0.6f);

	float fScreenWidthHalf((float)SCREEN_WIDTH / 2.0f);
	float fScreenHeightHalf((float)SCREEN_HEIGHT / 2.0f);
	float fCharPicWidthHalf(CHAR_BUTTON_WIDTH / 2.0f);
	float fCharPicHeightHalf(CHAR_BUTTON_HEIGHT / 2.0f);

	// キャラ画像
	m_pCharPicture[CHARCTER_TYPE::TYPE_1] = CButton::Create(pDevice, s_0, D3DXVECTOR3(fScreenWidthHalf - fCharPicWidthHalf, fScreenHeightHalf - fCharPicHeightHalf, 0.0f), CHAR_BUTTON_WIDTH, CHAR_BUTTON_HEIGHT);
	m_pCharPicture[CHARCTER_TYPE::TYPE_2] = CButton::Create(pDevice, s_1, D3DXVECTOR3(fScreenWidthHalf + fCharPicWidthHalf, fScreenHeightHalf - fCharPicHeightHalf, 0.0f), CHAR_BUTTON_WIDTH, CHAR_BUTTON_HEIGHT);
	m_pCharPicture[CHARCTER_TYPE::TYPE_3] = CButton::Create(pDevice, s_2, D3DXVECTOR3(fScreenWidthHalf - fCharPicWidthHalf, fScreenHeightHalf + fCharPicHeightHalf, 0.0f), CHAR_BUTTON_WIDTH, CHAR_BUTTON_HEIGHT);
	m_pCharPicture[CHARCTER_TYPE::TYPE_4] = CButton::Create(pDevice, s_3, D3DXVECTOR3(fScreenWidthHalf + fCharPicWidthHalf, fScreenHeightHalf + fCharPicHeightHalf, 0.0f), CHAR_BUTTON_WIDTH, CHAR_BUTTON_HEIGHT);

	// 決定時に表示する画像
	m_pSelectCfm[0] = Cform2D::Create(pDevice, TEXTURE_SELECTPLAYER1, D3DXVECTOR3(fScreenWidthHalf + fCharPicWidthHalf, fScreenHeightHalf + fCharPicHeightHalf, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_BUTTON_WIDTH, CHAR_BUTTON_HEIGHT);
	m_pSelectCfm[1] = Cform2D::Create(pDevice, TEXTURE_SELECTPLAYER2, D3DXVECTOR3(fScreenWidthHalf - fCharPicWidthHalf, fScreenHeightHalf + fCharPicHeightHalf, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_BUTTON_WIDTH, CHAR_BUTTON_HEIGHT);

	// キャラ画像
	m_SelectCfmPos[CHARCTER_TYPE::TYPE_1] = D3DXVECTOR3(fScreenWidthHalf - fCharPicWidthHalf, fScreenHeightHalf - fCharPicHeightHalf, 0.0f);
	m_SelectCfmPos[CHARCTER_TYPE::TYPE_2] = D3DXVECTOR3(fScreenWidthHalf + fCharPicWidthHalf, fScreenHeightHalf - fCharPicHeightHalf, 0.0f);
	m_SelectCfmPos[CHARCTER_TYPE::TYPE_3] = D3DXVECTOR3(fScreenWidthHalf - fCharPicWidthHalf, fScreenHeightHalf + fCharPicHeightHalf, 0.0f);
	m_SelectCfmPos[CHARCTER_TYPE::TYPE_4] = D3DXVECTOR3(fScreenWidthHalf + fCharPicWidthHalf, fScreenHeightHalf + fCharPicHeightHalf, 0.0f);

	// 外枠フレーム
	m_pCharFrame[CHARCTER_TYPE::TYPE_1] = Cform2D::Create(pDevice, TEXTURE_CHARAFRAME, D3DXVECTOR3(fScreenWidthHalf - fCharPicWidthHalf, fScreenHeightHalf - fCharPicHeightHalf, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_BUTTON_WIDTH, CHAR_BUTTON_HEIGHT);
	m_pCharFrame[CHARCTER_TYPE::TYPE_2] = Cform2D::Create(pDevice, TEXTURE_CHARAFRAME, D3DXVECTOR3(fScreenWidthHalf + fCharPicWidthHalf, fScreenHeightHalf - fCharPicHeightHalf, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_BUTTON_WIDTH, CHAR_BUTTON_HEIGHT);
	m_pCharFrame[CHARCTER_TYPE::TYPE_3] = Cform2D::Create(pDevice, TEXTURE_CHARAFRAME, D3DXVECTOR3(fScreenWidthHalf - fCharPicWidthHalf, fScreenHeightHalf + fCharPicHeightHalf, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_BUTTON_WIDTH, CHAR_BUTTON_HEIGHT);
	m_pCharFrame[CHARCTER_TYPE::TYPE_4] = Cform2D::Create(pDevice, TEXTURE_CHARAFRAME, D3DXVECTOR3(fScreenWidthHalf + fCharPicWidthHalf, fScreenHeightHalf + fCharPicHeightHalf, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_BUTTON_WIDTH, CHAR_BUTTON_HEIGHT);

	// 選択したキャラのモデル
	m_pCharModPlayer1[CHARCTER_TYPE::TYPE_1] = CPlayerM::Create(pDevice, 0, D3DXVECTOR3(-53.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 8.0f, 0.0f));
	m_pCharModPlayer1[CHARCTER_TYPE::TYPE_2] = CPlayerM::Create(pDevice, 1, D3DXVECTOR3(-53.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 8.0f, 0.0f));
	m_pCharModPlayer1[CHARCTER_TYPE::TYPE_3] = CPlayerM::Create(pDevice, 2, D3DXVECTOR3(-53.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 8.0f, 0.0f));
	m_pCharModPlayer1[CHARCTER_TYPE::TYPE_4] = CPlayerM::Create(pDevice, 3, D3DXVECTOR3(-53.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 8.0f, 0.0f));
	m_pCharModPlayer2[CHARCTER_TYPE::TYPE_1] = CPlayerM::Create(pDevice, 0, D3DXVECTOR3(53.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, D3DX_PI / 9.0f, 0.0f));
	m_pCharModPlayer2[CHARCTER_TYPE::TYPE_2] = CPlayerM::Create(pDevice, 1, D3DXVECTOR3(53.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, D3DX_PI / 9.0f, 0.0f));
	m_pCharModPlayer2[CHARCTER_TYPE::TYPE_3] = CPlayerM::Create(pDevice, 2, D3DXVECTOR3(53.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, D3DX_PI / 9.0f, 0.0f));
	m_pCharModPlayer2[CHARCTER_TYPE::TYPE_4] = CPlayerM::Create(pDevice, 3, D3DXVECTOR3(53.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, D3DX_PI / 9.0f, 0.0f));

	// 外枠フレーム
	m_pCharNamePlayer1[CHARCTER_TYPE::TYPE_1] = Cform2D::Create(pDevice, pCharNameTex[CHARCTER_TYPE::TYPE_1], D3DXVECTOR3(300.0f, 600.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_NAME_WIDTH, CHAR_NAME_HEIGHT);
	m_pCharNamePlayer1[CHARCTER_TYPE::TYPE_2] = Cform2D::Create(pDevice, pCharNameTex[CHARCTER_TYPE::TYPE_2], D3DXVECTOR3(300.0f, 600.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_NAME_WIDTH, CHAR_NAME_HEIGHT);
	m_pCharNamePlayer1[CHARCTER_TYPE::TYPE_3] = Cform2D::Create(pDevice, pCharNameTex[CHARCTER_TYPE::TYPE_3], D3DXVECTOR3(300.0f, 600.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_NAME_WIDTH, CHAR_NAME_HEIGHT);
	m_pCharNamePlayer1[CHARCTER_TYPE::TYPE_4] = Cform2D::Create(pDevice, pCharNameTex[CHARCTER_TYPE::TYPE_4], D3DXVECTOR3(300.0f, 600.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_NAME_WIDTH, CHAR_NAME_HEIGHT);
	m_pCharNamePlayer2[CHARCTER_TYPE::TYPE_1] = Cform2D::Create(pDevice, pCharNameTex[CHARCTER_TYPE::TYPE_1], D3DXVECTOR3(1000.0f, 600.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_NAME_WIDTH, CHAR_NAME_HEIGHT);
	m_pCharNamePlayer2[CHARCTER_TYPE::TYPE_2] = Cform2D::Create(pDevice, pCharNameTex[CHARCTER_TYPE::TYPE_2], D3DXVECTOR3(1000.0f, 600.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_NAME_WIDTH, CHAR_NAME_HEIGHT);
	m_pCharNamePlayer2[CHARCTER_TYPE::TYPE_3] = Cform2D::Create(pDevice, pCharNameTex[CHARCTER_TYPE::TYPE_3], D3DXVECTOR3(1000.0f, 600.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_NAME_WIDTH, CHAR_NAME_HEIGHT);
	m_pCharNamePlayer2[CHARCTER_TYPE::TYPE_4] = Cform2D::Create(pDevice, pCharNameTex[CHARCTER_TYPE::TYPE_4], D3DXVECTOR3(1000.0f, 600.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CHAR_NAME_WIDTH, CHAR_NAME_HEIGHT);

	// キャラ選択用ロゴ
	m_pLogo = CButton::Create(pDevice, s_8, D3DXVECTOR3(SCREEN_WIDTH / 2, 100.0f, 0.0f), 500, 100);

	// カーソル
	m_Select[0].pCursor = CCursor::Create(pDevice, s_4, D3DXVECTOR3(1000.0f, 600.0f, 0.0f), CURSOR_WIDTH, CURSOR_HEIGHT);
	m_Select[1].pCursor = CCursor::Create(pDevice, s_5, D3DXVECTOR3(200.0f, 600.0f, 0.0f), CURSOR_WIDTH, CURSOR_HEIGHT);

	// カーソルの目標座標
	m_OnCursorPos[CHARCTER_TYPE::TYPE_1] = D3DXVECTOR3(587.0f, 310.0f, 0.0f);
	m_OnCursorPos[CHARCTER_TYPE::TYPE_2] = D3DXVECTOR3(715.0f, 310.0f, 0.0f);
	m_OnCursorPos[CHARCTER_TYPE::TYPE_3] = D3DXVECTOR3(587.0f, 450.0f, 0.0f);
	m_OnCursorPos[CHARCTER_TYPE::TYPE_4] = D3DXVECTOR3(715.0f, 450.0f, 0.0f);

	// 選択中の項目
	m_Select[0].nSelect = 0;
	m_Select[1].nSelect = 1;
	m_Select[0].bDecisionFlg = false;
	m_Select[1].bDecisionFlg = false;

	// 選択状態にしておく
	m_pCharPicture[m_Select[0].nSelect]->SetButtonState(BUTTON_STATE::SELECTED);
	m_pCharPicture[m_Select[1].nSelect]->SetButtonState(BUTTON_STATE::SELECTED);

	//フェードの作成
	m_pFade = CFade::Create(pDevice, 1);
	m_pFade->StartFade(FADE_OUT, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CManager::GetSelectChar(0));

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CSelect::Uninit(void)
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
void CSelect::Update(void)
{
	//サウンド取得の作成
	CSound *pSound;
	pSound = CManager::GetSound();

	// 一時的に保存
	int tmpCursorOld[2];

	for (int i = 0; i < MAX_PLAYER; i++)
	{

		tmpCursorOld[i] = m_Select[i].nSelect;

		CheckSelectAllCorsor(i);
	}

	UpdateFade();

	//for (int i = 0; i < 4; i++)
	//{
	//	D3DXVECTOR3 rot1 = m_pCharModPlayer1[i]->GetRot();
	//	D3DXVECTOR3 rot2 = m_pCharModPlayer2[i]->GetRot();
	//	rot1.y += 0.1f;
	//	rot2.y += 0.1f;
	//	m_pCharModPlayer1[i]->SetRot(rot1);
	//	m_pCharModPlayer2[i]->SetRot(rot2);

	//}

	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	////F1キーが押された場合
	//if (pInputKeyboard->GetKeyTrigger(DIK_1)
	//	&& m_bChangeFlag == false)
	//{
	//	m_nType = SELECT_TYPE::TYPE_BUTTON;

	//}
	//else if (pInputKeyboard->GetKeyTrigger(DIK_2)
	//	&& m_bChangeFlag == false)
	//{
	//	m_pCursor->SetTime(0.0f);
	//	m_nType = SELECT_TYPE::TYPE_CURSOR;

	//}
	// ボタン選択
	if (m_nType == SELECT_TYPE::TYPE_BUTTON)
	{
		// 1Pの操作
		SelectByKeyboardPlayer1();
		m_Select[0].pCursor->SyncCharPos(m_OnCursorPos[m_Select[0].nSelect]);

		// 2Pの操作
		SelectByKeyboardPlayer2();
		m_Select[1].pCursor->SyncCharPos(m_OnCursorPos[m_Select[1].nSelect]);


	}
	// カーソル移動
	else if (m_nType == SELECT_TYPE::TYPE_CURSOR)
	{
		// とりあえずコメントアウトで後日どうするか決める
		//SelectByCursor();

	}

	// 違うボタンに移ったら
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		if (tmpCursorOld[i] != m_Select[i].nSelect)
		{
			CButton::ChangeSelectButtonState(m_pCharPicture[tmpCursorOld[i]], m_pCharPicture[m_Select[i].nSelect]);

		}

		// 選択状態にしておく
		m_pCharPicture[m_Select[i].nSelect]->SetButtonState(BUTTON_STATE::SELECTED);

	}
	// キャラクター表示用モデル
	m_pCharModPlayer1[m_Select[0].nSelect]->Update();
	m_pCharModPlayer2[m_Select[1].nSelect]->Update();

#ifdef _DEBUG

	CDebugProc::Print("プレイヤー選択中のボタン:%d\n", m_Select[0].nSelect);
	CDebugProc::Print("選択中のボタン:%d\n", m_Select[1].nSelect);
	CDebugProc::Print("プレイヤー1はＷＡＳＤで移動でＥＮＴＥＲで決定\n");
	CDebugProc::Print("プレイヤー2は↑←↓→で移動でＳＥＬＥＣＴで決定\n");
	CDebugProc::Print("選択中のボタン:%f\n", m_pCharModPlayer1[0]->GetRot().y);
	CDebugProc::Print("選択中のボタン:%f\n", m_pCharModPlayer2[0]->GetRot().y);

#endif


}
//=============================================================================
// 描画
//=============================================================================
void CSelect::Draw(void)
{

	m_pDome->Draw();
	m_pDome2->Draw();

	// キャラクター表示用モデル
	m_pCharModPlayer1[m_Select[0].nSelect]->Draw();
	m_pCharModPlayer2[m_Select[1].nSelect]->Draw();

	// 背景
	m_pBackGround->Draw();

	// キャラクター名表示用
	m_pCharNamePlayer1[m_Select[0].nSelect]->Draw();
	m_pCharNamePlayer2[m_Select[1].nSelect]->Draw();


	// 選択用キャラ画像
	for (int i = 0; i < CHARCTER_TYPE::TYPE_MAX; i++)
	{
		m_pCharPicture[i]->Draw();

	}

	// 選択用キャラ画像
	for (int i = 0; i < MAX_PLAYER; i++)
	{

		if (m_Select[i].bDecisionFlg)
		{
			m_pSelectCfm[i]->Draw();
		}

	}

	// 選択用キャラ画像
	for (int i = 0; i < CHARCTER_TYPE::TYPE_MAX; i++)
	{
		m_pCharFrame[i]->Draw();

	}
	// カーソル
	for (int i = 0; i < MAX_CURSOR; i++)
	{

		m_Select[i].pCursor->Draw();

	}


	// キャラ選択画面ロゴ
	m_pLogo->Draw();

	//フェードの作成
	m_pFade->Draw();
}
//=============================================================================
// フェードの更新
//=============================================================================
void CSelect::UpdateFade(void)
{
	if (m_bChangeFlag
		&& m_pFade->GetFade() == FADE_NONE)
	{
		//pSound->Play(SOUND_LABEL_SE_SELECT002);
		// 選択したキャラを保存
		//m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), CManager::GetSelectChar(0));
	}

	//フェードインが終わったら
	if (m_pFade->GetFade() == FADE_IN_END)
	{
		if (m_bTitleBackFlag == false)
		{
			//次のフェーズを変える
			CManager::SetAfterScene(PHASETYPE_STAGE_SELECT);
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
void CSelect::SelectByKeyboardPlayer2(void)
{

	// Wiiコンの取得
	WiiRemote* pTmpPad = CManager::GetWii(1);

	//サウンド取得の作成
	CSound *pSound;
	pSound = CManager::GetSound();
	// 
	if (m_bChangeFlag){ return; }

	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//エンターキーが押された場合
	if ((pInputKeyboard->GetKeyTrigger(DIK_SPACE)) || pTmpPad->GetKeyTrigger(WII_BUTTOM_A))
	{

		pSound->Play(SOUND_LABEL_SE_SELECT002);
		// エンターキーを押した場合
		ChkSelectButton(1);
		m_pSelectCfm[1]->SetPos(m_SelectCfmPos[m_Select[1].nSelect]);


	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_UP) || pTmpPad->GetKeyTrigger(WII_BUTTOM_UP))
	{
		pSound->Play(SOUND_LABEL_SE_SELECT000);
		m_Select[1].pCursor->SetTime(0.0f);

		// 選択状態から解除
		//pSound->Play(SOUND_LABEL_SE_SELECT000);

		// 各配置によって移動する
		if (m_Select[1].nSelect == TYPE_1
			|| m_Select[1].nSelect == TYPE_2)
		{

			m_Select[1].nSelect += 2;

		}
		else
		{
			m_Select[1].nSelect -= 2;

		}

	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_DOWN) || pTmpPad->GetKeyTrigger(WII_BUTTOM_DOWN))
	{
		pSound->Play(SOUND_LABEL_SE_SELECT000);
		m_Select[1].pCursor->SetTime(0.0f);

		//pSound->Play(SOUND_LABEL_SE_SELECT000);

		// 各配置によって移動する
		if (m_Select[1].nSelect == TYPE_1
			|| m_Select[1].nSelect == TYPE_2){

			m_Select[1].nSelect += 2;

		}
		else
		{

			m_Select[1].nSelect -= 2;

		}
	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_LEFT) || pTmpPad->GetKeyTrigger(WII_BUTTOM_LEFT))
	{
		pSound->Play(SOUND_LABEL_SE_SELECT000);
		m_Select[1].pCursor->SetTime(0.0f);

		//pSound->Play(SOUND_LABEL_SE_SELECT000);

		// 各配置によって移動する
		if (m_Select[1].nSelect == TYPE_1
			|| m_Select[1].nSelect == TYPE_3)
		{

			m_Select[1].nSelect++;

		}
		else
		{
			m_Select[1].nSelect--;

		}

	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_RIGHT) || pTmpPad->GetKeyTrigger(WII_BUTTOM_RIGHT))
	{
		pSound->Play(SOUND_LABEL_SE_SELECT000);
		m_Select[1].pCursor->SetTime(0.0f);
		//pSound->Play(SOUND_LABEL_SE_SELECT000);

		// 各配置によって移動する
		if (m_Select[1].nSelect == TYPE_1
			|| m_Select[1].nSelect == TYPE_3)
		{

			m_Select[1].nSelect++;

		}
		else
		{
			m_Select[1].nSelect--;

		}
	}
}
//=============================================================================
// キーボードでの選択
//=============================================================================
void CSelect::SelectByKeyboardPlayer1(void)
{

	CSound *pSound;
	pSound = CManager::GetSound();
	// Wiiコンの取得
	WiiRemote* pTmpPad = CManager::GetWii(0);

	// 
	if (m_bChangeFlag){ return; }

	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//エンターキーが押された場合
	if ((pInputKeyboard->GetKeyTrigger(DIK_RETURN)) || pTmpPad->GetKeyTrigger(WII_BUTTOM_A))
	{
		pSound->Play(SOUND_LABEL_SE_SELECT002);
		if (!m_Select[0].bDecisionFlg)
		{

			// 
			ChkSelectButton(0);

			m_pSelectCfm[0]->SetPos(m_SelectCfmPos[m_Select[0].nSelect]);

		}
		else
		{

		}

	}
	else if ((pInputKeyboard->GetKeyTrigger(DIK_BACKSPACE)) || pTmpPad->GetKeyTrigger(WII_BUTTOM_A))
	{
		m_Select[0].bDecisionFlg = false;

	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_W) || pTmpPad->GetKeyTrigger(WII_BUTTOM_UP))
	{
		pSound->Play(SOUND_LABEL_SE_SELECT000);
		m_Select[0].pCursor->SetTime(0.0f);

		// 選択状態から解除
		//pSound->Play(SOUND_LABEL_SE_SELECT000);

		// 各配置によって移動する
		if (m_Select[0].nSelect == TYPE_1
			|| m_Select[0].nSelect == TYPE_2)
		{

			m_Select[0].nSelect += 2;

		}
		else
		{
			m_Select[0].nSelect -= 2;

		}

	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_S) || pTmpPad->GetKeyTrigger(WII_BUTTOM_DOWN))
	{
		pSound->Play(SOUND_LABEL_SE_SELECT000);
		m_Select[0].pCursor->SetTime(0.0f);

		//pSound->Play(SOUND_LABEL_SE_SELECT000);

		// 各配置によって移動する
		if (m_Select[0].nSelect == TYPE_1
			|| m_Select[0].nSelect == TYPE_2){

			m_Select[0].nSelect += 2;

		}
		else
		{

			m_Select[0].nSelect -= 2;

		}
	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_A) || pTmpPad->GetKeyTrigger(WII_BUTTOM_LEFT))
	{
		pSound->Play(SOUND_LABEL_SE_SELECT000);
		m_Select[0].pCursor->SetTime(0.0f);

		//pSound->Play(SOUND_LABEL_SE_SELECT000);

		// 各配置によって移動する
		if (m_Select[0].nSelect == TYPE_1
			|| m_Select[0].nSelect == TYPE_3)
		{

			m_Select[0].nSelect++;

		}
		else
		{
			m_Select[0].nSelect--;

		}

	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_D) || pTmpPad->GetKeyTrigger(WII_BUTTOM_RIGHT))
	{
		pSound->Play(SOUND_LABEL_SE_SELECT000);
		m_Select[0].pCursor->SetTime(0.0f);
		//pSound->Play(SOUND_LABEL_SE_SELECT000);

		// 各配置によって移動する
		if (m_Select[0].nSelect == TYPE_1
			|| m_Select[0].nSelect == TYPE_3)
		{

			m_Select[0].nSelect++;

		}
		else
		{
			m_Select[0].nSelect--;

		}
	}

}
//=============================================================================
// 
//=============================================================================
void CSelect::ChkSelectButton(int nParamSelectCursor)
{

	// 選択された場合はスキップ
	if (m_Select[nParamSelectCursor].bDecisionFlg){ return; }

	// 矩形でのあたり判定
	if (CCursor::HitChkRect(m_Select[nParamSelectCursor].pCursor->GetPos(),
		m_pCharPicture[m_Select[nParamSelectCursor].nSelect]->GetPos(),
		m_Select[nParamSelectCursor].pCursor->GetLen(),
		m_pCharPicture[m_Select[nParamSelectCursor].nSelect]->GetLen()))
	{

		// 既に選択されていない場合
		if (m_Select[1].nSelect != m_Select[0].nSelect)
		{

			// 
			m_Select[nParamSelectCursor].pCursor->SetTime(0.0f);
			CheckSelectAllCorsor(nParamSelectCursor);

			//pSound->PlayVoice(m_Select[0].nSelect,VOICE_LABEL_SE_START);

			m_Select[nParamSelectCursor].bDecisionFlg = true;

		}

	}

}
//=============================================================================
// 全てのプレイヤーがキャラを決定したかどうかのフラグ
//=============================================================================
void CSelect::CheckSelectAllCorsor(int nParamDecisionCursor)
{

	if (m_bChangeFlag){ return; }

	// 全てのプレイヤーが選択を完了したら
	if (m_Select[nParamDecisionCursor].bDecisionFlg
		&& m_Select[nParamDecisionCursor - 1].bDecisionFlg)
	{

		// 遷移処理
		m_bChangeFlag = true;

		// 決定状態にする
		m_Select[nParamDecisionCursor].bDecisionFlg = true;

		// 各キャラクターの決定
		CManager::SetSelectChar(0, m_Select[0].nSelect);
		CManager::SetSelectChar(1, m_Select[1].nSelect);

		m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), CManager::GetSelectChar(0));

	}

}
//=============================================================================
// カール移動での選択
// 複数対応はマウスでは難しいのでとりあえずコメントアウト
//=============================================================================
void CSelect::SelectByCursor(void){

	//	// 変数定義
	//	D3DXVECTOR3 tmpCurPos[MAX_CURSOR];
	//	D3DXVECTOR3 tmpCharPos(0.0f, 0.0f, 0.0f);
	//	bool tmpOnFlg(false);
	//	D3DXVECTOR3 tmpCursorLen(0.0f, 0.0f, 0.0f);
	//
	//	tmpCurPos[0] = m_Select[0].pCursor->GetPos();
	//	tmpCurPos[1] = m_Select[1].pCursor->GetPos();
	//
	//	//キーボードインプットの受け取り
	//	CInputKeyboard *pInputKeyboard;
	//	pInputKeyboard = CManager::GetInputKeyboard();
	//
	//	//すべてのキャラ項目を対象に検索
	//	for (int i = 0; i < CHARCTER_TYPE::TYPE_MAX; i++)
	//	{
	//
	//		// 座標の取得
	//		tmpCharPos = m_pCharPicture[i]->GetPos();
	//
	//		// 矩形でのあたり判定
	//		if (CCursor::HitChkRect(tmpCurPos, tmpCharPos, m_pCursor->GetLen(), m_pCharPicture[i]->GetLen()))
	//		{
	//
	//			// 当たっていることを記録
	//			tmpOnFlg = true;
	//		
	//			// 選択中のカーソルの更新
	//			m_Select[0].nSelect = i;
	//
	//			break;
	//		}
	//		else{
	//
	//
	//		}
	//	}
	//	// 決定ボタンを押したら
	//	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	//	{
	//
	//		// どれかのキャラボタンに乗っかっていたら
	//		if (tmpOnFlg)
	//		{
	//			// 遷移処理
	//			m_bChangeFlag = true;
	//
	//			// 選択したキャラを保存
	//			CScene::SetFrame(m_Select[0].nSelect);
	//			//pSound->PlayVoice(m_Select[0].nSelect,VOICE_LABEL_SE_START);
	//
	//			if (m_bVsSelectFlag == false)
	//			{
	//				CScene::SetEnemy(rand() % 3);
	//				if (m_pFade->GetPlayFade() == false)
	//				{
	//					//pSound->Play(SOUND_LABEL_SE_SELECT001);
	//					m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f),CManager::GetSelectChar(0));
	//				}
	//			}
	//		}
	//
	//	}// if
	//	else if (m_bChangeFlag != true)
	//	{
	//		m_pCursor->MoveByKeybord();
	//	}
	//
	//
	//#ifdef _DEBUG
	//
	//	CDebugProc::Print("マウス座標X:%f\n", tmpCurPos.x);
	//	CDebugProc::Print("マウス座標Y:%f\n", tmpCurPos.y);
	//
	//#endif

}// SelectByCursor
//=============================================================================
// 正規化
//=============================================================================
int CSelect::NomalizeSelectPlayer(int nParamVal)
{
	// 各配置によって移動する
	if (nParamVal < 0)
	{

		return MAX_PLAYER - 1;

	}
	else
	{

		return 0;

	}

}
/////////////EOF////////////