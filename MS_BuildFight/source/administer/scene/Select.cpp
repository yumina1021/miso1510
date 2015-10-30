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
	m_pCharPicture[5] = { };
	m_pEffect[6] = {};
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

	//キャラ画像配置
	m_pEffect[0]=CEffect::Create(pDevice,Selecteffect001,D3DXVECTOR3(650.0f,375.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));
	m_pEffect[1]=CEffect::Create(pDevice,Selecteffect002,D3DXVECTOR3(650.0f,375.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));
	m_pEffect[2]=CEffect::Create(pDevice,Selecteffect003,D3DXVECTOR3(650.0f,375.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));

	//文字の配置
	m_pCharPicture[0]=CCharPicture::Create(pDevice,s_1,D3DXVECTOR3(200.0f,200.0f,0.0f),400,100);
	m_pCharPicture[1]=CCharPicture::Create(pDevice,s_2,D3DXVECTOR3(200.0f,300.0f,0.0f),400,100);
	m_pCharPicture[2]=CCharPicture::Create(pDevice,s_3,D3DXVECTOR3(200.0f,400.0f,0.0f),400,100);


	//隠しキャラ
	if(CManager::Getnight0PlayFlag()==true)
	{
		m_pCharPicture[3] = CCharPicture::Create(pDevice, s_0, D3DXVECTOR3(200.0f, 500.0f, 0.0f), 400, 100);
		m_pEffect[3]=CEffect::Create(pDevice,Selecteffect000,D3DXVECTOR3(650.0f,375.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));
		m_pCharPicture[4] = CCharPicture::Create(pDevice, n_b, D3DXVECTOR3(200.0f, 600.0f, 0.0f), 400, 100);
		m_pEffect[4] = CEffect::Create(pDevice, Selecteffect010, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	else
	{
		m_pCharPicture[3] = CCharPicture::Create(pDevice, s_99, D3DXVECTOR3(200.0f, 500.0f, 0.0f), 400, 100);
		m_pEffect[3] = CEffect::Create(pDevice, Selecteffect999, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_pCharPicture[4] = CCharPicture::Create(pDevice, s_99, D3DXVECTOR3(200.0f, 600.0f, 0.0f), 400, 100);
		m_pEffect[4] = CEffect::Create(pDevice, Selecteffect1000, D3DXVECTOR3(650.0f, 375.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	//マッチング待機
	m_pEffect[5]=CEffect::Create(pDevice,SelecteffectMatching,D3DXVECTOR3(650.0f,375.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f));

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

	//エスケープキーが押された場合
	if(pInputKeyboard->GetKeyTrigger(DIK_BACKSPACE))
	{
		m_bTitleBackFlag=true;
		//pSound->Play(SOUND_LABEL_SE_SELECT000);
		m_pFade->StartFade(FADE_IN,100,D3DXCOLOR(1.0f,1.0f,1.0f,0.0f));
	}

	//隠しキャラが使えない状態で隠しキャラが選ばれた場合
	if ((pInputKeyboard->GetKeyTrigger(DIK_RETURN) || pInputKeyboard->GetKeyTrigger(DIK_Z)) && CManager::Getnight0PlayFlag() == false && (m_nCursor == 3 || m_nCursor == 4) && m_bChangeFlag == false)
	{

	}else
	//エンターキーが押された場合
	if((pInputKeyboard->GetKeyTrigger(DIK_RETURN)||pInputKeyboard->GetKeyTrigger(DIK_Z))&&m_bChangeFlag==false)
	{
		//カーソルが合っているコマンドを発動
		switch(m_nCursor)
		{
			//1号機
			case 0 :	m_bChangeFlag=true;
						CScene::SetFrame(0);
						//pSound->PlayVoice(0,VOICE_LABEL_SE_START);
						break;
			//２号機
			case 1 :	m_bChangeFlag=true;
						CScene::SetFrame(1);
						//pSound->PlayVoice(1,VOICE_LABEL_SE_START);
						break;
			//３号機
			case 2 :	m_bChangeFlag=true;
						CScene::SetFrame(2);
						//pSound->PlayVoice(2,VOICE_LABEL_SE_START);
						break;
			if(CManager::Getnight0PlayFlag()==true)
			{
				//０号機
				case 3 :	m_bChangeFlag=true;
							CScene::SetFrame(3);
							//pSound->PlayVoice(3,VOICE_LABEL_SE_START);
							break;
				//０号機
				case 4:		m_bChangeFlag = true;
							CScene::SetFrame(4);
							//pSound->PlayVoice(3, VOICE_LABEL_SE_START);
							break;
			}
			default : break;
		}

		CScene::SetMap(0);

		if(m_bVsSelectFlag==false)
		{
			CScene::SetEnemy(rand()%3);
			if(m_pFade->GetPlayFade()==false)
			{
				//pSound->Play(SOUND_LABEL_SE_SELECT001);
				m_pFade->StartFade(FADE_IN,100,D3DXCOLOR(1.0f,1.0f,1.0f,0.0f));
			}
		}else
		{
			m_pEffect[5]->SetViewFlag(true,90000);
		}
	}
	else if(m_bChangeFlag!=true)
	{
		if(pInputKeyboard->GetKeyTrigger(DIK_W)||pInputKeyboard->GetKeyTrigger(DIK_UP))
		{
			m_pEffect[m_nCursor]->SetViewFlag(false,1);
			m_pCharPicture[m_nCursor]->SetDiffuse(1.0f,1.0f,1.0f,1.0f);
			m_nCursor--;
			//pSound->Play(SOUND_LABEL_SE_SELECT000);
			if(m_nCursor<0)
			{
					m_nCursor=4;
			}
		}else if(pInputKeyboard->GetKeyTrigger(DIK_S)||pInputKeyboard->GetKeyTrigger(DIK_DOWN))
		{
			m_pEffect[m_nCursor]->SetViewFlag(false,1);
			m_pCharPicture[m_nCursor]->SetDiffuse(1.0f,1.0f,1.0f,1.0f);
			m_nCursor++;
			//pSound->Play(SOUND_LABEL_SE_SELECT000);
			if(m_nCursor>4)
			{
			m_nCursor=0;
			}

		}
	}

	m_fDiffuse-=0.01f;

	if(m_fDiffuse<0.5f)
	{
		m_fDiffuse=1.0f;
	}

	m_pCharPicture[m_nCursor]->SetDiffuse(m_fDiffuse,m_fDiffuse,m_fDiffuse,1.0f);

	m_pEffect[m_nCursor]->SetViewFlag(true,1);


	//フェードインが終わったら
	if(m_pFade->GetFade()==FADE_IN_END)
	{
		if(m_bTitleBackFlag==false)
		{
			//次のフェーズを変える
			CManager::SetAfterScene(PHASETYPE_GAME);
		}else
		{
			//次のフェーズを変える
			CManager::SetAfterScene(PHASETYPE_TITLE);
		}
	}
	if (m_bChangeFlag == true && m_pFade->GetFade() == FADE_NONE)
	{
		//pSound->Play(SOUND_LABEL_SE_SELECT002);
		m_pFade->StartFade(FADE_IN,100,D3DXCOLOR(1.0f,1.0f,1.0f,0.0f));
	}
}
//=============================================================================
// 描画
//=============================================================================
void CSelect :: Draw(void)
{
	m_pBackGround->Draw();

	for (int i = 0; i < 5; i++)
	{
		m_pEffect[i]->Draw();
		m_pCharPicture[i]->Draw();
	}

	m_pEffect[5]->Draw();

	//フェードの作成
	m_pFade->Draw();
}
/////////////EOF////////////