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

//*****************************************************************************
// グローバル変数
//*****************************************************************************
//=============================================================================
// コンストラクタ
//=============================================================================
CSelect :: CSelect(void)
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
	m_pCharPicture[CHARCTER_TYPE::TYPE_1] = CCharPicture::Create(pDevice, s_0, D3DXVECTOR3(350.0f, 350.0f, 0.0f), 400, 100);
	m_pCharPicture[CHARCTER_TYPE::TYPE_2] = CCharPicture::Create(pDevice, s_1, D3DXVECTOR3(1000.0f, 350.0f, 0.0f), 400, 100);
	m_pCharPicture[CHARCTER_TYPE::TYPE_3] = CCharPicture::Create(pDevice, s_2, D3DXVECTOR3(350.0f, 600.0f, 0.0f), 400, 100);
	m_pCharPicture[CHARCTER_TYPE::TYPE_4] = CCharPicture::Create(pDevice, s_3, D3DXVECTOR3(1000.0f, 600.0f, 0.0f), 400, 100);

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

	// ボタン選択
	SelectByButton();

	m_fDiffuse-=0.01f;

	if(m_fDiffuse<0.5f)
	{
		m_fDiffuse=1.0f;
	}

	m_pCharPicture[m_nCursor]->SetDiffuse(m_fDiffuse,m_fDiffuse,m_fDiffuse,1.0f);

	UpdateFade();

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
// 描画
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
/////////////EOF////////////