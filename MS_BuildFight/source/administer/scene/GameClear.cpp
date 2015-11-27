//=============================================================================
//
// MS_BuildFight [CGameClear.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "GameClear.h"

#include "../Input.h"
#include "../Maneger.h"
#include "../Sound.h"

#include "../../module/etc/Fade.h"

#include "../../module/ui/CharPicture.h"
#include "../../module/ui/Effect.h"
#include "../../module/ui/BackGround.h"
//*****************************************************************************
// グローバル変数
//*****************************************************************************
CBackGround *CGameClear::m_pBackGround = NULL;
CFade *CGameClear::m_pFade=NULL;
CEffect *CGameClear::m_pEffect[] = {};
//=============================================================================
// コンストラクタ
//=============================================================================
CGameClear :: CGameClear(void)
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CGameClear :: ~CGameClear(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CGameClear :: Init(LPDIRECT3DDEVICE9 pDevice)
{
	//背景の作成
	m_pBackGround=CBackGround::Create(pDevice,BACKGROUND_GAMECLEAR);

	//文字の配置
	m_pEffect[0] = CEffect::Create(pDevice, ready1, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pEffect[1] = CEffect::Create(pDevice, ready1, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pEffect[0]->SetView(true);
	m_pEffect[1]->SetView(true);

	//フェードの作成
	m_pFade=CFade::Create(pDevice,1);

	//サウンド取得の作成
	CSound *pSound;
	pSound = CManager::GetSound();

	//サウンド再生の作成
	//pSound->Play(SOUND_LABEL_BGM002);

	m_nCount=0;

	m_pFade->StartFade(FADE_OUT,50,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),CManager::GetSelectChar(0));

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CGameClear :: Uninit(void)
{
	//サウンド取得の作成
	CSound *pSound;
	pSound = CManager::GetSound();

	//サウンド再生の作成
	//pSound->Stop(SOUND_LABEL_BGM002);

	//シーンを全て終了
	Cform::ReleaseAll();
}
//=============================================================================
// 更新
//=============================================================================
void CGameClear :: Update(void)
{
	//サウンド取得の作成
	CSound *pSound;
	pSound = CManager::GetSound();

	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//エンターキーが押された場合
	if(pInputKeyboard->GetKeyTrigger(DIK_RETURN)||pInputKeyboard->GetKeyTrigger(DIK_Z))
	{
		m_pEffect[0]->SetView(false);
		//pSound->Play(SOUND_LABEL_SE_SELECT000);

		if(m_nCount>=1)
		{
			//pSound->Play(SOUND_LABEL_SE_SELECT001);
			m_pFade->StartFade(FADE_IN,100,D3DXCOLOR(0.0f,0.0f,0.0f,0.0f),CManager::GetSelectChar(0));
		}else
		{
			m_nCount++;
		}
	}

	//フェードインが終わったら
	if(m_pFade->GetFade()==FADE_IN_END)
	{
		//次のフェーズを変える
		CScene::SetEnemy(3);
		CManager::SetAfterScene(PHASETYPE_GAME);
	}
}
//=============================================================================
// 描画
//=============================================================================
void CGameClear :: Draw(void)
{

}
/////////////EOF////////////