//=============================================================================
//
// MS_BuildFight [CVsend.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "Vsend.h"

#include "../Input.h"
#include "../Maneger.h"
#include "../Sound.h"
#include "../netClient.h"

#include "../../module/etc/Fade.h"

#include "../../module/ui/BackGround.h"
#include "../../module/ui/ResultScore.h"
#include "../../module/ui/Effect.h"
//*****************************************************************************
// グローバル変数
//*****************************************************************************
CBackGround *CVsend::m_pBackGround = NULL;
CFade		*CVsend::m_pFade=NULL;
CEffect		*CVsend::m_pEffect = NULL;
//=============================================================================
// コンストラクタ
//=============================================================================
CVsend :: CVsend(void)
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CVsend :: ~CVsend(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CVsend :: Init(LPDIRECT3DDEVICE9 pDevice)
{
	//背景の作成
	m_pBackGround=CBackGround::Create(pDevice,BACKGROUND_VSEND);

	//サウンド取得の作成
	CSound *pSound;
	pSound = CManager::GetSound();

	//サウンド再生の作成
	//pSound->Play(SOUND_LABEL_BGM002);

	int time=CScene::GetTime();
	int score=CScene::GetScore();
	bool vs = CScene::GetVSFlag();

	if(vs==true)
	{
		m_pEffect=CEffect::Create(pDevice,Glose,D3DXVECTOR3(650.0f,375.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));
	}else
	{
		m_pEffect=CEffect::Create(pDevice,Gwin,D3DXVECTOR3(650.0f,375.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));
	}

	//CReScore::Create(pDevice,score,D3DXVECTOR3(SCREEN_WIDTH/2,450.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));

	//フェードの作成
	m_pFade=CFade::Create(pDevice,1);

	m_pFade->StartFade(FADE_OUT,50,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

	CNetClient::SetEndGameFlag(false);
	CNetClient::SetEndGameTimeFlag(false);
	CNetClient::SetStartFlag(false);
	CNetClient::SetEndGameLoseFlag(false);

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CVsend :: Uninit(void)
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
void CVsend :: Update(void)
{
	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	m_pEffect->SetViewFlag(true,1);

	//フェードの開始
	if(pInputKeyboard->GetKeyTrigger(DIK_RETURN)||pInputKeyboard->GetKeyTrigger(DIK_Z))
	{
		CSound *pSound;
		pSound = CManager::GetSound();
		//pSound->Play(SOUND_LABEL_SE_SELECT001);
		m_pFade->StartFade(FADE_IN,100,D3DXCOLOR(1.0f,1.0f,1.0f,0.0f));
	}

	//フェードインが終わったら
	if(m_pFade->GetFade()==FADE_IN_END)
	{
		//次のフェーズを変える
		CManager::SetAfterScene(PHASETYPE_TITLE);
	}
}
//=============================================================================
// 描画
//=============================================================================
void CVsend :: Draw(void)
{

}
/////////////EOF////////////