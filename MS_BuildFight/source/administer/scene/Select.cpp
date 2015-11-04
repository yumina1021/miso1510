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

#include "../../administer/Debugproc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
const float CURSOR_MOVE_COFF(10.0f);
//*****************************************************************************
// グローバル変数
//*****************************************************************************
//=============================================================================
// コンストラクタ
//=============================================================================
CSelect :: CSelect(void):
m_nType(SELECT_TYPE::TYPE_BUTTON)
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
	m_pCharPicture[CHARCTER_TYPE::TYPE_1] = CCharPicture::Create(pDevice, s_0, D3DXVECTOR3(325.0f, 187.5f, 0.0f), 650, 375);
	m_pCharPicture[CHARCTER_TYPE::TYPE_2] = CCharPicture::Create(pDevice, s_1, D3DXVECTOR3(975.0f, 187.5f, 0.0f), 650, 375);
	m_pCharPicture[CHARCTER_TYPE::TYPE_3] = CCharPicture::Create(pDevice, s_2, D3DXVECTOR3(325.0f, 562.5f, 0.0f), 650, 375);
	m_pCharPicture[CHARCTER_TYPE::TYPE_4] = CCharPicture::Create(pDevice, s_3, D3DXVECTOR3(975.0f, 562.5f, 0.0f), 650, 375);
	m_pCursor = CCharPicture::Create(pDevice, s_4, D3DXVECTOR3(1000.0f, 600.0f, 0.0f), 128, 128);

	//フェードの作成
	m_pFade=CFade::Create(pDevice,1);

	//サウンド取得の作成
	CSound *pSound;
	pSound = CManager::GetSound();

	//サウンド再生の作成
	//pSound->Play(SOUND_LABEL_BGM004);

	m_bChangeFlag=false;
	m_nCursor=0;

	m_fDiffuse=1.0f;

	m_bVsSelectFlag = CScene::GetVSFlag();

	m_bTitleBackFlag=false;

	m_pFade->StartFade(FADE_OUT,50,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
	m_bSendData=false;

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

	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//エンターキーが押された場合
	if (pInputKeyboard->GetKeyTrigger(DIK_F1)
		&& m_bChangeFlag == false)
	{
		m_nType = SELECT_TYPE::TYPE_BUTTON;

	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_F2)
		&& m_bChangeFlag == false)
	{
		m_nType = SELECT_TYPE::TYPE_CURSOR;

	}
	// ボタン選択
	if (m_nType == SELECT_TYPE::TYPE_BUTTON)
	{

		SelectByButton();

	}
	// カーソル移動
	else if (m_nType == SELECT_TYPE::TYPE_CURSOR)
	{
		SelectByCursor();

	}

	m_fDiffuse-=0.01f;

	if(m_fDiffuse<0.5f)
	{
		m_fDiffuse=1.0f;
	}

	m_pCharPicture[m_nCursor]->SetDiffuse(m_fDiffuse,m_fDiffuse,m_fDiffuse,1.0f);

	UpdateFade();

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
void CSelect::SelectByButton(void)
{

	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//エンターキーが押された場合
	if ((pInputKeyboard->GetKeyTrigger(DIK_RETURN) || pInputKeyboard->GetKeyTrigger(DIK_Z)) && m_bChangeFlag == false)
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
	else if (m_bChangeFlag != true)
	{
		if (pInputKeyboard->GetKeyTrigger(DIK_W) || pInputKeyboard->GetKeyTrigger(DIK_UP))
		{
			m_pCharPicture[m_nCursor]->SetDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
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
			m_pCharPicture[m_nCursor]->SetDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
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
			m_pCharPicture[m_nCursor]->SetDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
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
			m_pCharPicture[m_nCursor]->SetDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
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
	POINT tmpCurPos;
	D3DXVECTOR3 tmpPos = m_pCursor->GetPos();
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
		if (HitChkRect(tmpPos, tmpCharPos, m_pCursor->GetLen(), m_pCharPicture[i]->GetLen()))
		{

			// 当たっていることを記録
			tmpOnFlg = true;
		
			// 選択中から外れた項目のα値を初期化
			m_pCharPicture[m_nCursor]->SetDiffuse(1.0f, 1.0f, 1.0f, 1.0f);

			// 選択中のカーソルの更新
			m_nCursor = i;
			break;
		}
		else{


		}

	}

	// 左クリックしたら
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN))
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
		if (pInputKeyboard->GetKeyPress(DIK_W) || pInputKeyboard->GetKeyPress(DIK_UP))
		{

			tmpPos.y -= CURSOR_MOVE_COFF;

		}
		else if (pInputKeyboard->GetKeyPress(DIK_S) || pInputKeyboard->GetKeyPress(DIK_DOWN))
		{
			tmpPos.y += CURSOR_MOVE_COFF;

		}
		if (pInputKeyboard->GetKeyPress(DIK_A) || pInputKeyboard->GetKeyPress(DIK_LEFT))
		{

			tmpPos.x -= CURSOR_MOVE_COFF;

		}
		else if (pInputKeyboard->GetKeyPress(DIK_D) || pInputKeyboard->GetKeyPress(DIK_RIGHT))
		{
			tmpPos.x += CURSOR_MOVE_COFF;

		}
	}
	// カーソルの座標の更新
	m_pCursor->SetPos(tmpPos);

#ifdef _DEBUG

	CDebugProc::Print("マウス座標X:%f\n", tmpPos.x);
	CDebugProc::Print("マウス座標Y:%f\n", tmpPos.y);

#endif

}// SelectByCursor
//=============================================================================
// カール移動での選択
//=============================================================================
bool CSelect::HitChkRect(const D3DXVECTOR3& paramPos1,
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
/////////////EOF////////////