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
#include "../../module/ui/CharPicture.h"
#include "../../module/ui/Button.h"
#include "../../module/ui/Cursor.h"

#include "../../administer/Debugproc.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************

#define MENU_X	(SCREEN_WIDTH/2)	//メニューのX位置
#define MENU_Y	(450.0f)			//メニューのY位置

#define MENU_WIDTH	(400)			//メニューの横サイズ
#define MENU_HEIGHT	(100)			//メニューの縦サイズ

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
	m_pCharPicture[0] = { };
	m_pCharPicture[1] = { };
	m_pCharPicture[2] = { };
	m_pCharPicture[3] = { };
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
	m_pBackGround=CBackGround::Create(pDevice,BACKGROUND_TITLE);

	//文字の配置
	m_pCharPicture[GAME_START] = CButton::Create(pDevice, t_stert, D3DXVECTOR3(MENU_X, 450.0f, 0.0f), MENU_WIDTH, MENU_HEIGHT);
	m_pCharPicture[VS_MODE] = CButton::Create(pDevice, t_vs, D3DXVECTOR3(MENU_X, MENU_Y + 75.0f, 0.0f), MENU_WIDTH, MENU_HEIGHT);
	m_pCharPicture[TUTORIAL] = CButton::Create(pDevice, t_tutorial, D3DXVECTOR3(MENU_X, MENU_Y + (75.0f * 2), 0.0f), MENU_WIDTH, MENU_HEIGHT);
	m_pCharPicture[GAME_END] = CButton::Create(pDevice, t_end, D3DXVECTOR3(MENU_X, MENU_Y + (75.0f * 3), 0.0f), MENU_WIDTH, MENU_HEIGHT);
	m_pCursor = CCursor::Create(pDevice, s_4, D3DXVECTOR3(1000.0f, 600.0f, 0.0f), 32, 32);

	// 選択状態にしておく
	m_pCharPicture[m_nCursor]->SetButtonState(BUTTON_STATE::SELECTED);

	//フェードの作成
	m_pFade=CFade::Create(pDevice,1);

	//サウンド取得の作成
	CSound *pSound;
	pSound = CManager::GetSound();

	//サウンド再生の作成
	//pSound->Play(SOUND_LABEL_BGM000);

	
	m_pFade->StartFade(FADE_OUT,50,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

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
		m_pCursor->SetTime(0.0f);
		m_nType = SELECT_TYPE::TYPE_CURSOR;

	}
	// ボタン選択
	if (m_nType == SELECT_TYPE::TYPE_BUTTON)
	{
		KeyCommand();
		m_pCursor->SyncCharPos(m_pCharPicture[m_nCursor]->GetPos());

	}
	// カーソル移動
	else if (m_nType == SELECT_TYPE::TYPE_CURSOR)
	{
			SelectByCursor();
	}

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
void CTitle :: Draw(void)
{
	m_pBackGround->Draw();
	m_pCursor->Draw();
	//文字
	for (int i = 0; i < MAX; i++)
	{

		m_pCharPicture[i]->Draw();

	}

	//フェード
	m_pFade->Draw();

}
//=============================================================================
// 入力
//=============================================================================
void CTitle::KeyCommand(void)
{

	//サウンド取得の作成
	CSound *pSound;
	pSound = CManager::GetSound();

	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//エンターキーが押された場合
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{

		ChangeState();

	}
	else if (m_bChangeFlag != true)
	{

		if (pInputKeyboard->GetKeyTrigger(DIK_W) || pInputKeyboard->GetKeyTrigger(DIK_UP))
		{
			m_nCursor--;
			//pSound->Play(SOUND_LABEL_SE_SELECT000);
			if (m_nCursor < GAME_START)
			{
				m_nCursor = GAME_END;
			}

		}
		else if (pInputKeyboard->GetKeyTrigger(DIK_S) || pInputKeyboard->GetKeyTrigger(DIK_DOWN))
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
	D3DXVECTOR3 tmpCurPos = m_pCursor->GetPos();
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
		tmpCharPos = m_pCharPicture[i]->GetPos();

		// 矩形でのあたり判定
		if (CCursor::HitChkRect(tmpCurPos, tmpCharPos, m_pCursor->GetLen(), m_pCharPicture[i]->GetLen()))
		{

			// 当たっていることを記録
			tmpOnFlg = true;

			// 選択状態から解除
			m_pCharPicture[m_nCursor]->SetButtonState(BUTTON_STATE::PUSH_OFF);

			// 選択中のカーソルの更新
			m_nCursor = i;

			// 選択状態にしておく
			m_pCharPicture[m_nCursor]->SetButtonState(BUTTON_STATE::SELECTED);

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
		m_pCursor->MoveByKeybord();
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
	case 0:	m_bChangeFlag = true;
		//pSound->Play(SOUND_LABEL_SE_SELECT001);
		if (m_pFade->GetPlayFade() == false)
		{
			m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			CScene::SetVSFlag(false);
		}
		break;
		//VS
	case 1:	m_bChangeFlag = true;
		//pSound->Play(SOUND_LABEL_SE_SELECT001);
		if (m_pFade->GetPlayFade() == false)
		{
			m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			CScene::SetVSFlag(true);
		}
		break;
		//コンフィグ
	case 2:	m_bChangeFlag = true;
		//pSound->Play(SOUND_LABEL_SE_SELECT001);
		if (m_pFade->GetPlayFade() == false)
		{
			m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
		break;
		//エンド
	case 3:	m_bChangeFlag = false;
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