//=============================================================================
//
// MS_BuildFight [CStageSelect.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "StageSelect.h"

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
CStageSelect :: CStageSelect(void)
{

	m_pBackGround = NULL;
	m_pFade = NULL;
}
//=============================================================================
// デストラクタ
//=============================================================================
CStageSelect :: ~CStageSelect(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CStageSelect :: Init(LPDIRECT3DDEVICE9 pDevice)
{
	//背景の作成
	m_pBackGround=CBackGround::Create(pDevice,BACKGROUND_SELECT);

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
	m_bChangeFlag = false;
	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CStageSelect :: Uninit(void)
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
void CStageSelect :: Update(void)
{
	//サウンド取得の作成
	CSound *pSound;
	pSound = CManager::GetSound();	

	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	m_fDiffuse-=0.01f;

	if(m_fDiffuse<0.5f)
	{
		m_fDiffuse=1.0f;
	}

	UpdateFade();
	//エンターキーが押された場合
	if ((pInputKeyboard->GetKeyTrigger(DIK_RETURN) && m_bChangeFlag == false))
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

#ifdef _DEBUG


#endif


}
//=============================================================================
// 描画
//=============================================================================
void CStageSelect :: Draw(void)
{
	m_pBackGround->Draw();



	//フェードの作成
	m_pFade->Draw();
}
//=============================================================================
// フェードの更新
//=============================================================================
void CStageSelect::UpdateFade(void)
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
// カール移動での選択
//=============================================================================
bool CStageSelect::HitChkRect(const D3DXVECTOR3& paramPos1,
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