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

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//*****************************************************************************
// グローバル変数
//*****************************************************************************
//=============================================================================
// コンストラクタ
//=============================================================================
CSelect :: CSelect(void):
m_nType(SELECT_TYPE::TYPE_BUTTON),
m_bChangeFlag(false),
m_nCursor(0),
m_bVsSelectFlag(CScene::GetVSFlag()),
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
	m_pCharPicture[CHARCTER_TYPE::TYPE_1] = CButton::Create(pDevice, s_0, D3DXVECTOR3(325.0f, 187.5f, 0.0f), 650, 375);
	m_pCharPicture[CHARCTER_TYPE::TYPE_2] = CButton::Create(pDevice, s_1, D3DXVECTOR3(975.0f, 187.5f, 0.0f), 650, 375);
	m_pCharPicture[CHARCTER_TYPE::TYPE_3] = CButton::Create(pDevice, s_2, D3DXVECTOR3(325.0f, 562.5f, 0.0f), 650, 375);
	m_pCharPicture[CHARCTER_TYPE::TYPE_4] = CButton::Create(pDevice, s_3, D3DXVECTOR3(975.0f, 562.5f, 0.0f), 650, 375);
	m_pCursor = CCursor::Create(pDevice, s_4, D3DXVECTOR3(1000.0f, 600.0f, 0.0f), 128, 128);

	// 選択状態にしておく
	m_pCharPicture[m_nCursor]->SetButtonState(BUTTON_STATE::SELECTED);

	//フェードの作成
	m_pFade=CFade::Create(pDevice,1);
	m_pFade->StartFade(FADE_OUT, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

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
	int tmpCursorOld = m_nCursor;

	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//F1キーが押された場合
	if (pInputKeyboard->GetKeyTrigger(DIK_1)
		&& m_bChangeFlag == false)
	{
		m_nType = SELECT_TYPE::TYPE_BUTTON;

	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_2)
		&& m_bChangeFlag == false)
	{
		m_pCursor->SetTime(0.0f);
		m_nType = SELECT_TYPE::TYPE_CURSOR;

	}
	// ボタン選択
	if (m_nType == SELECT_TYPE::TYPE_BUTTON)
	{
		SelectByButton();
		m_pCursor->SyncCharPos(m_pCharPicture[m_nCursor]->GetPos());
	}
	// カーソル移動
	else if (m_nType == SELECT_TYPE::TYPE_CURSOR)
	{
		SelectByCursor();

	}

	UpdateFade();

	// 違うボタンに移ったら
	if (tmpCursorOld != m_nCursor)
	{
		CButton::ChangeSelectButtonState(m_pCharPicture[tmpCursorOld], m_pCharPicture[m_nCursor]);

	}

#ifdef _DEBUG

	CDebugProc::Print("選択中のボタン:%d\n", m_nCursor);
	CDebugProc::Print("モード選択:%d\n ※0:ボタン 1:カーソル", m_nType);

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

	m_pCursor->Draw();

	//フェードの作成
	m_pFade->Draw();
}
//=============================================================================
// フェードの更新
//=============================================================================
void CSelect::UpdateFade(void)
{
	if (m_bChangeFlag == true)
	{
		//pSound->Play(SOUND_LABEL_SE_SELECT002);
		m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_bChangeFlag = false;
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
void CSelect::SelectByButton(void)
{

	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//エンターキーが押された場合
	if ((pInputKeyboard->GetKeyTrigger(DIK_RETURN) && m_bChangeFlag == false))
	{

		m_pCursor->SetTime(0.0f);
		// 遷移処理
		m_bChangeFlag = true;

		// 選択したキャラを保存
		CScene::SetFrame(m_nCursor);
		//pSound->PlayVoice(m_nCursor,VOICE_LABEL_SE_START);

		if (m_bVsSelectFlag == false)
		{
			CScene::SetEnemy(rand() % 3);
			if (m_pFade->GetPlayFade() == false)
			{
				//pSound->Play(SOUND_LABEL_SE_SELECT001);
				m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			}
		}
	}
	else if (m_bChangeFlag != true)
	{
		if (pInputKeyboard->GetKeyTrigger(DIK_W) || pInputKeyboard->GetKeyTrigger(DIK_UP))
		{
			m_pCursor->SetTime(0.0f);

			// 選択状態から解除
			//pSound->Play(SOUND_LABEL_SE_SELECT000);

			// 各配置によって移動する
			if (m_nCursor == TYPE_1
				|| m_nCursor == TYPE_2)
			{

				m_nCursor += 2;

			}
			else
			{
				m_nCursor -= 2;

			}

		}
		else if (pInputKeyboard->GetKeyTrigger(DIK_S) || pInputKeyboard->GetKeyTrigger(DIK_DOWN))
		{
			m_pCursor->SetTime(0.0f);

			//pSound->Play(SOUND_LABEL_SE_SELECT000);

			// 各配置によって移動する
			if (m_nCursor == TYPE_1
				|| m_nCursor == TYPE_2){

				m_nCursor += 2;

			}
			else
			{

				m_nCursor -= 2;

			}
		}
		if (pInputKeyboard->GetKeyTrigger(DIK_A) || pInputKeyboard->GetKeyTrigger(DIK_LEFT))
		{
			m_pCursor->SetTime(0.0f);

			//pSound->Play(SOUND_LABEL_SE_SELECT000);

			// 各配置によって移動する
			if (m_nCursor == TYPE_1
				|| m_nCursor == TYPE_3)
			{

				m_nCursor++;

			}
			else
			{
				m_nCursor--;

			}

		}
		else if (pInputKeyboard->GetKeyTrigger(DIK_D) || pInputKeyboard->GetKeyTrigger(DIK_RIGHT))
		{
			m_pCursor->SetTime(0.0f);
			//pSound->Play(SOUND_LABEL_SE_SELECT000);

			// 各配置によって移動する
			if (m_nCursor == TYPE_1
				|| m_nCursor == TYPE_3)
			{

				m_nCursor++;

			}
			else
			{
				m_nCursor--;

			}
		}
	}
}
//=============================================================================
// カール移動での選択
//=============================================================================
void CSelect::SelectByCursor(void){

	// 変数定義
	D3DXVECTOR3 tmpCurPos = m_pCursor->GetPos();
	D3DXVECTOR3 tmpCharPos(0.0f, 0.0f, 0.0f);
	bool tmpOnFlg(false);
	D3DXVECTOR3 tmpCursorLen(0.0f, 0.0f, 0.0f);

	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//すべてのキャラ項目を対象に検索
	for (int i = 0; i < CHARCTER_TYPE::TYPE_MAX; i++)
	{

		// 座標の取得
		tmpCharPos = m_pCharPicture[i]->GetPos();

		// 矩形でのあたり判定
		if (CCursor::HitChkRect(tmpCurPos, tmpCharPos, m_pCursor->GetLen(), m_pCharPicture[i]->GetLen()))
		{

			// 当たっていることを記録
			tmpOnFlg = true;
		
			// 選択中のカーソルの更新
			m_nCursor = i;

			break;
		}
		else{


		}
	}
	// 決定ボタンを押したら
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{

		// どれかのキャラボタンに乗っかっていたら
		if (tmpOnFlg)
		{
			// 遷移処理
			m_bChangeFlag = true;

			// 選択したキャラを保存
			CScene::SetFrame(m_nCursor);
			//pSound->PlayVoice(m_nCursor,VOICE_LABEL_SE_START);

			if (m_bVsSelectFlag == false)
			{
				CScene::SetEnemy(rand() % 3);
				if (m_pFade->GetPlayFade() == false)
				{
					//pSound->Play(SOUND_LABEL_SE_SELECT001);
					m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				}
			}
		}

	}// if
	else if (m_bChangeFlag != true)
	{
		m_pCursor->MoveByKeybord();
	}


#ifdef _DEBUG

	CDebugProc::Print("マウス座標X:%f\n", tmpCurPos.x);
	CDebugProc::Print("マウス座標Y:%f\n", tmpCurPos.y);

#endif

}// SelectByCursor


/////////////EOF////////////