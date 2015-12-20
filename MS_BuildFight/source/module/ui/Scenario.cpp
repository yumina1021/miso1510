//=============================================================================
//
// MS_BuildFight [CScenario.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#include "Scenario.h"
#include "Character.h"

#include "../../form/form2D.h"

#include "../../administer/Input.h"

#include "Scenario\GameScenario.h"
#include "Scenario\ResultScenario.h"

//*****************************************************************************
// 静的変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CScenario :: CScenario()
{
	m_nCount=0;
	m_ViewFlag=false;
	m_CCharacter = NULL;
	m_window = NULL;
	m_textbox = NULL;
}
//=============================================================================
// デストラクタ
//=============================================================================
CScenario :: ~CScenario(void)
{
}
//=============================================================================
// 生成
//=============================================================================
CScenario *CScenario::Create(LPDIRECT3DDEVICE9 pDevice, Character chara,bool viewflag)
{
	CScenario *pScenario;

	pScenario = new CScenario();
	pScenario->Init(pDevice,chara, viewflag);

	return pScenario;
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CScenario::Init(LPDIRECT3DDEVICE9 pDevice, Character chara, bool viewflag)
{
	m_pDevice = pDevice;

	m_ViewFlag = viewflag;

	m_charaType = chara;

	m_bScenarioEndFlag = false;

	//フィールドの初期化
	m_CCharacter = CCharacter::Create(m_pDevice, chara, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_window = Cform2D::Create(m_pDevice, "data/TEXTURE/window.png", D3DXVECTOR3(SCREEN_WIDTH / 2, 650.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1300, 200);

	//文字表示
	m_textbox = new TextBox(m_pDevice, FontTexture::TYPE_MEIRYO, 60);
	m_textbox->Initialize();

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CScenario :: Uninit(void)
{
	//様々なオブジェクトの終了（開放）処理
	m_textbox->Uninitialize();
	delete m_textbox;
	m_textbox = NULL;
}
//=============================================================================
// 更新
//=============================================================================
void CScenario::Update(CInputKeyboard* input)
{
	m_CCharacter->Update();
}
//=============================================================================
// 描画
//=============================================================================
void CScenario :: Draw(void)
{
	if(m_ViewFlag)
	{
		m_CCharacter->Draw();
		m_window->Draw();

		m_textbox->Draw();

	}
}
//=============================================================================
// ゲーム内でのシナリオ
//=============================================================================
void CScenario::GameScenario(int count, GameAffair affair)
{
	if (m_nCount <= count)
	{
		GameScenarioData data;

		m_nCount = count;

		switch (affair)
		{
			case AFFAIR_START :
				switch (m_charaType)
				{
				case 0:data = scenario_rosa_start[m_nCount]; break;
				case 1:data = scenario_lila_start[m_nCount]; break;
				case 2:data = scenario_ojyo_start[m_nCount]; break;
				case 3:data = scenario_tutorial_start[m_nCount]; break;
				}
			break;
			case AFFAIR_WIN:
				switch (m_charaType)
				{
				case 0:data = scenario_rosa_win[m_nCount]; break;
				case 1:data = scenario_lila_win[m_nCount]; break;
				case 2:data = scenario_ojyo_win[m_nCount]; break;
				case 3:data = scenario_tutorial_win[m_nCount]; break;
				}
			break;
			case AFFAIR_LOSE:
				switch (m_charaType)
				{
				case 0:data = scenario_rosa_lose[m_nCount]; break;
				case 1:data = scenario_lila_lose[m_nCount]; break;
				case 2:data = scenario_ojyo_lose[m_nCount]; break;
				case 3:data = scenario_tutorial_lose[m_nCount]; break;
				}
			break;
			case AFFAIR_HALF:
				switch (m_charaType)
				{
				case 0:data = scenario_rosa_harf[m_nCount]; break;
				case 1:data = scenario_lila_harf[m_nCount]; break;
				case 2:data = scenario_ojyo_harf[m_nCount]; break;
				case 3:data = scenario_tutorial_harf[m_nCount]; break;
				}
			break;
		}

		if (data.lastflag == true)
		{
			m_bScenarioEndFlag = true;
		}

		//キーボードインプットの受け取り
		m_CCharacter->SetFacialType(data.type);

		m_textbox->Clear();
		m_textbox->__position(D3DXVECTOR2(data.x, data.y));
		m_textbox->__show_speed(data.speed);
		m_textbox->Print(data.font);
	}
}


void CScenario::ResultScenario(int count)
{
	if (m_nCount <= count)
	{
		ResultScenarioData data;

		m_nCount = count;

			switch (m_charaType)
			{
			case 0:data = result_rosa[m_nCount]; break;
			case 1:data = result_ojyo[m_nCount]; break;
			case 2:data = result_lila[m_nCount]; break;
			case 3:data = result_tutorial[m_nCount]; break;
			}

		if (data.lastflag == true)
		{
			m_bScenarioEndFlag = true;
		}

		//キーボードインプットの受け取り
		m_CCharacter->SetViewFlag(false,0);

		m_textbox->Clear();
		m_textbox->__position(D3DXVECTOR2(data.x, data.y));
		m_textbox->__show_speed(data.speed);
		m_textbox->Print(data.font);
	}

}

/////////////EOF////////////