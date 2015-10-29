//=============================================================================
//
// MS_BuildFight [CTutorial.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "Tutorial.h"

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
CTutorial :: CTutorial(void)
{
	m_pBackGround = NULL;
	m_pFade = NULL;
	m_pEffect[7] = { };
}
//=============================================================================
// デストラクタ
//=============================================================================
CTutorial :: ~CTutorial(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CTutorial :: Init(LPDIRECT3DDEVICE9 pDevice)
{
	//背景の作成
	m_pBackGround=CBackGround::Create(pDevice,BACKGROUND_TUTORIAL);

	//文字の配置
	m_pEffect[0]=CEffect::Create(pDevice,Tutorialeffect001,D3DXVECTOR3(650.0f,375.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));
	m_pEffect[1]=CEffect::Create(pDevice,Tutorialeffect002,D3DXVECTOR3(650.0f,375.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));
	m_pEffect[2]=CEffect::Create(pDevice,Tutorialeffect003,D3DXVECTOR3(650.0f,375.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));
	m_pEffect[3]=CEffect::Create(pDevice,Tutorialeffect004,D3DXVECTOR3(650.0f,375.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));
	m_pEffect[4]=CEffect::Create(pDevice,Tutorialeffect005,D3DXVECTOR3(650.0f,375.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));
	m_pEffect[5]=CEffect::Create(pDevice,Tutorialeffect006,D3DXVECTOR3(650.0f,375.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));
	m_pEffect[6]=CEffect::Create(pDevice,Tutorialeffect007,D3DXVECTOR3(650.0f,375.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));
	m_pEffect[7]=CEffect::Create(pDevice,Tutorialeffect008,D3DXVECTOR3(650.0f,375.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));

	//フェードの作成
	m_pFade=CFade::Create(pDevice,1);

	//サウンド取得の作成
	CSound *pSound;
	pSound = CManager::GetSound();

	//サウンド再生の作成
	//pSound->Play(SOUND_LABEL_BGM003);

	m_nCount=0;

	m_pFade->StartFade(FADE_OUT,50,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CTutorial :: Uninit(void)
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
void CTutorial :: Update(void)
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
		m_pEffect[m_nCount-1]->SetViewFlag(false,1);
		//pSound->Play(SOUND_LABEL_SE_SELECT000);
		if(m_nCount>=7)
		{
			//pSound->Play(SOUND_LABEL_SE_SELECT001);
			m_pFade->StartFade(FADE_IN,100,D3DXCOLOR(1.0f,1.0f,1.0f,0.0f));
		}else
		{
			m_nCount++;
		}
	}
	//エスケープキーが押された場合
	if(pInputKeyboard->GetKeyTrigger(DIK_ESCAPE))
	{
		m_pFade->StartFade(FADE_IN,100,D3DXCOLOR(1.0f,1.0f,1.0f,0.0f));
	}

	m_pEffect[m_nCount]->SetViewFlag(true,1);

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
void CTutorial :: Draw(void)
{
	m_pBackGround->Draw();

	m_pEffect[0]->Draw();
	m_pEffect[1]->Draw();
	m_pEffect[2]->Draw();
	m_pEffect[3]->Draw();
	m_pEffect[4]->Draw();
	m_pEffect[5]->Draw();
	m_pEffect[6]->Draw();
	m_pEffect[7]->Draw();

	m_pFade->Draw();

}
/////////////EOF////////////