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
#include "../../module/ui/BackGround.h"
#include "../../module/ui/CharPicture.h"
#include "../../module/ui/Effect.h"
#include "../../module/ui/Button.h"
#include "../../module/ui/Cursor.h"

#include "../../administer/Debugproc.h"

#include "../wiicon/wiimote.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
const int MAX_PLAYER(2);
const float CHAR_BUTTON_WIDTH(650.0f);
const float CHAR_BUTTON_HEIGHT(375.0f);

const float CURSOR_WIDTH(128.0f);
const float CURSOR_HEIGHT(128.0f);
//*****************************************************************************
// グローバル変数
//*****************************************************************************
//=============================================================================
// コンストラクタ
//=============================================================================
CSelect :: CSelect(void):
m_nType(SELECT_TYPE::TYPE_BUTTON),
m_bChangeFlag(false),
m_bVsSelectFlag(false),
m_bTitleBackFlag(false),
m_bSendData(false)
{

	m_pBackGround = NULL;
	m_pFade = NULL;
	m_pCharPicture[CHARCTER_TYPE::TYPE_MAX] = {};

	
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
HRESULT CSelect :: Init(LPDIRECT3DDEVICE9 pDevice)
{
	//背景の作成
	m_pBackGround=CBackGround::Create(pDevice,BACKGROUND_SELECT);

	//文字の配置
	m_pCharPicture[CHARCTER_TYPE::TYPE_1] = CButton::Create(pDevice, s_0, D3DXVECTOR3(325.0f, 187.5f, 0.0f), CHAR_BUTTON_WIDTH, CHAR_BUTTON_HEIGHT);
	m_pCharPicture[CHARCTER_TYPE::TYPE_2] = CButton::Create(pDevice, s_1, D3DXVECTOR3(975.0f, 187.5f, 0.0f), CHAR_BUTTON_WIDTH, CHAR_BUTTON_HEIGHT);
	m_pCharPicture[CHARCTER_TYPE::TYPE_3] = CButton::Create(pDevice, s_2, D3DXVECTOR3(325.0f, 562.5f, 0.0f), CHAR_BUTTON_WIDTH, CHAR_BUTTON_HEIGHT);
	m_pCharPicture[CHARCTER_TYPE::TYPE_4] = CButton::Create(pDevice, s_3, D3DXVECTOR3(975.0f, 562.5f, 0.0f), CHAR_BUTTON_WIDTH, CHAR_BUTTON_HEIGHT);
	m_pLogo = CButton::Create(pDevice, s_6, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 900, 100);

	m_Select[0].pCursor = CCursor::Create(pDevice, s_4, D3DXVECTOR3(1000.0f, 600.0f, 0.0f), CURSOR_WIDTH, CURSOR_HEIGHT);
	m_Select[1].pCursor = CCursor::Create(pDevice, s_5, D3DXVECTOR3(200.0f, 600.0f, 0.0f), CURSOR_WIDTH, CURSOR_HEIGHT);

	m_OnCursorPos[CHARCTER_TYPE::TYPE_1] = D3DXVECTOR3(587.0f, 310.0f, 0.0f);
	m_OnCursorPos[CHARCTER_TYPE::TYPE_2] = D3DXVECTOR3(715.0f, 310.0f, 0.0f);
	m_OnCursorPos[CHARCTER_TYPE::TYPE_3] = D3DXVECTOR3(587.0f, 450.0f, 0.0f);
	m_OnCursorPos[CHARCTER_TYPE::TYPE_4] = D3DXVECTOR3(715.0f, 450.0f, 0.0f);
	m_Select[0].nSelect = 0;
	m_Select[1].nSelect = 1;

	m_Select[0].bDecisionFlg = false;
	m_Select[1].bDecisionFlg = false;

	// 選択状態にしておく
	m_pCharPicture[m_Select[0].nSelect]->SetButtonState(BUTTON_STATE::SELECTED);
	m_pCharPicture[m_Select[1].nSelect]->SetButtonState(BUTTON_STATE::SELECTED);

	//フェードの作成
	m_pFade=CFade::Create(pDevice,1);
	m_pFade->StartFade(FADE_OUT, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),CManager::GetSelectChar(0));

	//サウンド取得の作成
	CSound *pSound;
	pSound = CManager::GetSound();

	//サウンド再生の作成
	//pSound->Play(SOUND_LABEL_BGM004);

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CSelect :: Uninit(void)
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
void CSelect :: Update(void)
{
	//サウンド取得の作成
	CSound *pSound;
	pSound = CManager::GetSound();	

	// 一時的に保存
	int tmpCursorOld[2];

	for (int i = 0; i < MAX_PLAYER; i++)
	{

		tmpCursorOld[i] = m_Select[i].nSelect;

	}

	UpdateFade();

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
#ifdef _DEBUG

	CDebugProc::Print("プレイヤー選択中のボタン:%d\n", m_Select[0].nSelect);
	CDebugProc::Print("選択中のボタン:%d\n", m_Select[1].nSelect);
	CDebugProc::Print("プレイヤー1はＷＡＳＤで移動でＥＮＴＥＲで決定\n");
	CDebugProc::Print("プレイヤー2は↑←↓→で移動でＳＥＬＥＣＴで決定\n");

#endif


}
//=============================================================================
// 描画
//=============================================================================
void CSelect :: Draw(void)
{
	m_pBackGround->Draw();

	for (int i = 0; i < CHARCTER_TYPE::TYPE_MAX; i++)
	{
		m_pCharPicture[i]->Draw();
	}

	// 
	for (int i = 0; i < MAX_CURSOR; i++)
	{

		m_Select[i].pCursor->Draw();

	}

	m_pLogo->Draw();

	//フェードの作成
	m_pFade->Draw();
}
//=============================================================================
// フェードの更新
//=============================================================================
void CSelect::UpdateFade(void)
{
	//if (m_bChangeFlag == true)
	//{
	//	//pSound->Play(SOUND_LABEL_SE_SELECT002);
	//	m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f),CManager::GetSelectChar(0));
	//	m_bChangeFlag = false;
	//}

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

	// 
	if (m_bChangeFlag){ return; }

	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//エンターキーが押された場合
	if ((pInputKeyboard->GetKeyTrigger(DIK_SPACE)) || pTmpPad->GetKeyTrigger(WII_BUTTOM_A))
	{

		// 選択された場合はスキップ
		if (m_Select[1].bDecisionFlg){ return; }

		// 矩形でのあたり判定
		if (CCursor::HitChkRect(m_Select[1].pCursor->GetPos(),
			m_pCharPicture[m_Select[1].nSelect]->GetPos(),
			m_Select[1].pCursor->GetLen(),
			m_pCharPicture[m_Select[1].nSelect]->GetLen()))
		{

			if ((m_Select[0].bDecisionFlg
				&& m_Select[0].nSelect != m_Select[1].nSelect)
				|| !m_Select[0].bDecisionFlg)
			{

				m_Select[1].pCursor->SetTime(0.0f);
				CheckSelectAllCorsor(1);

				//pSound->PlayVoice(m_Select[1].nSelect,VOICE_LABEL_SE_START);

			}

		}



	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_UP) || pTmpPad->GetKeyTrigger(WII_BUTTOM_UP))
	{
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

		// 選択された場合はスキップ
		if (m_Select[0].bDecisionFlg){ return; }

		// 矩形でのあたり判定
		if (CCursor::HitChkRect(m_Select[0].pCursor->GetPos(),
			m_pCharPicture[m_Select[0].nSelect]->GetPos(),
			m_Select[0].pCursor->GetLen(),
			m_pCharPicture[m_Select[0].nSelect]->GetLen()))
		{

			if ((m_Select[1].bDecisionFlg
				&& m_Select[1].nSelect != m_Select[0].nSelect)
				|| !m_Select[1].bDecisionFlg)
			{
				m_Select[0].pCursor->SetTime(0.0f);
				CheckSelectAllCorsor(0);

				//pSound->PlayVoice(m_Select[0].nSelect,VOICE_LABEL_SE_START);
			}
		}


		
	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_W) || pTmpPad->GetKeyTrigger(WII_BUTTOM_UP))
	{
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
// 全てのプレイヤーがキャラを決定したかどうかのフラグ
//=============================================================================
void CSelect::CheckSelectAllCorsor(int nParamDecisionCursor){

	// 全てのプレイヤーが選択を完了したら
	if (m_Select[0].bDecisionFlg
		|| m_Select[1].bDecisionFlg)
	{
		// 遷移処理
		m_bChangeFlag = true;

		// 各キャラクターの決定
		CManager::SetSelectChar(0, m_Select[0].nSelect);
		CManager::SetSelectChar(1, m_Select[1].nSelect);

		// 選択したキャラを保存
		m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f),CManager::GetSelectChar(0));

	}
	else
	{
		m_Select[nParamDecisionCursor].bDecisionFlg = true;

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

/////////////EOF////////////