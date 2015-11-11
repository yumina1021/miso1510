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
CScenario *CScenario::Create(LPDIRECT3DDEVICE9 pDevice,bool viewflag)
{
	CScenario *pScenario;

	pScenario = new CScenario();
	pScenario->Init(pDevice, viewflag);

	return pScenario;
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CScenario::Init(LPDIRECT3DDEVICE9 pDevice, bool viewflag)
{
	m_pDevice = pDevice;

	m_ViewFlag = viewflag;

	//フィールドの初期化
	m_CCharacter = CCharacter::Create(m_pDevice, 0, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_window = Cform2D::Create(m_pDevice, "data/TEXTURE/window.png", D3DXVECTOR3(SCREEN_WIDTH / 2, 650.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1300, 200);

	//文字表示
	m_textbox = new TextBox(m_pDevice, FontTexture::TYPE_MEIRYO, 60);
	m_textbox->Initialize();

	m_CCharacter->SetFacialType(FACIAL_HAWAWA);

	m_textbox->__position(D3DXVECTOR2(210, 590));
	m_textbox->__show_speed(10);
	m_textbox->Print("わわわっ！\nわわわわわっ！");

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
	//キーボードインプットの受け取り
	if (input->GetKeyTrigger(DIK_1))
	{
		m_CCharacter->SetFacialType(FACIAL_SMILE);

		m_textbox->Clear();
		m_textbox->__position(D3DXVECTOR2(210, 590));
		m_textbox->__show_speed(10);
		m_textbox->Print("えへへ");
	}
	if (input->GetKeyTrigger(DIK_2))
	{
		m_CCharacter->SetFacialType(FACIAL_SMILE2);

		m_textbox->Clear();
		m_textbox->__position(D3DXVECTOR2(210, 590));
		m_textbox->__show_speed(10);
		m_textbox->Print("わははははは");
	}
	if (input->GetKeyTrigger(DIK_3))
	{
		m_CCharacter->SetFacialType(FACIAL_STAR);

		m_textbox->Clear();
		m_textbox->__position(D3DXVECTOR2(210, 590));
		m_textbox->__show_speed(10);
		m_textbox->Print("なのです!", D3DXCOLOR(1.0f, 0.8f, 0.0f, 1.0f));
	}
	if (input->GetKeyTrigger(DIK_4))
	{
		m_CCharacter->SetFacialType(FACIAL_ANGERY);

		m_textbox->Clear();
		m_textbox->__position(D3DXVECTOR2(210, 590));
		m_textbox->__show_speed(10);
		m_textbox->Print("あ？", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}

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
/////////////EOF////////////