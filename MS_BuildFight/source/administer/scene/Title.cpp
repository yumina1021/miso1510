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
CTitle :: CTitle(void)
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
	m_pCharPicture[0] = CCharPicture::Create(pDevice, t_stert, D3DXVECTOR3(MENU_X, 450.0f, 0.0f), MENU_WIDTH, MENU_HEIGHT);
	m_pCharPicture[1] = CCharPicture::Create(pDevice, t_vs, D3DXVECTOR3(MENU_X, MENU_Y + 75.0f, 0.0f), MENU_WIDTH, MENU_HEIGHT);
	m_pCharPicture[2] = CCharPicture::Create(pDevice, t_tutorial, D3DXVECTOR3(MENU_X, MENU_Y + (75.0f * 2), 0.0f), MENU_WIDTH, MENU_HEIGHT);
	m_pCharPicture[3] = CCharPicture::Create(pDevice, t_end, D3DXVECTOR3(MENU_X, MENU_Y + (75.0f * 3), 0.0f), MENU_WIDTH, MENU_HEIGHT);

	//フェードの作成
	m_pFade=CFade::Create(pDevice,1);

	//サウンド取得の作成
	CSound *pSound;
	pSound = CManager::GetSound();

	//サウンド再生の作成
	//pSound->Play(SOUND_LABEL_BGM000);

	m_bChangeFlag=false;
	m_nCursor=0;

	m_fDiffuse=1.0f;

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
	KeyCommand();

	m_pCharPicture[m_nCursor]->SetDiffuse(m_fDiffuse,m_fDiffuse,m_fDiffuse,1.0f);

	//フェードインが終わったら
	if(m_pFade->GetFade()==FADE_IN_END)
	{
		if(m_nCursor==0||m_nCursor==1)
		{
			//次のフェーズを変える
			CScene::SetReplayFlag(false);
			CManager::SetAfterScene(PHASETYPE_SELECT);
		}else if(m_nCursor==2)
		{
			//次のフェーズを変える
			CManager::SetAfterScene(PHASETYPE_RESULT);
		}
	}
}
//=============================================================================
// 描画
//=============================================================================
void CTitle :: Draw(void)
{
	m_pBackGround->Draw();

	//文字
	m_pCharPicture[0]->Draw();
	m_pCharPicture[1]->Draw();
	m_pCharPicture[2]->Draw();
	m_pCharPicture[3]->Draw();

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
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || pInputKeyboard->GetKeyTrigger(DIK_Z))
	{
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
	else if (m_bChangeFlag != true)
	{
		if (pInputKeyboard->GetKeyTrigger(DIK_W) || pInputKeyboard->GetKeyTrigger(DIK_UP))
		{
			m_pCharPicture[m_nCursor]->SetDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
			m_nCursor--;
			//pSound->Play(SOUND_LABEL_SE_SELECT000);
			if (m_nCursor<0)
			{
				m_nCursor = 3;
			}
		}
		else if (pInputKeyboard->GetKeyTrigger(DIK_S) || pInputKeyboard->GetKeyTrigger(DIK_DOWN))
		{
			m_pCharPicture[m_nCursor]->SetDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
			m_nCursor++;
			//pSound->Play(SOUND_LABEL_SE_SELECT000);
			if (m_nCursor>3)
			{
				m_nCursor = 0;
			}
		}
	}
	if (pInputKeyboard->GetKeyTrigger(DIK_F5))
	{
		if (CManager::Getnight0PlayFlag() == true)
		{
			CManager::Setnight0PlayFlag(false);
		}
		else
		{
			CManager::Setnight0PlayFlag(true);
		}
	}

	m_fDiffuse -= 0.01f;

	if (m_fDiffuse<0.5f)
	{
		m_fDiffuse = 1.0f;
	}
}
/////////////EOF////////////