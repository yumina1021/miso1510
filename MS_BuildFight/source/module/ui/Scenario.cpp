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

	m_window = Cform2D::Create(pDevice, "data/TEXTURE/window.png", D3DXVECTOR3(SCREEN_WIDTH / 2, 650.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1300, 200);

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CScenario :: Uninit(void)
{
	//様々なオブジェクトの終了（開放）処理
	//m_CCharacter->Uninit();
	//m_window->Uninit();
}
//=============================================================================
// 更新
//=============================================================================
void CScenario::Update(CInputKeyboard* input)
{
	//キーボードインプットの受け取り
	if (input->GetKeyTrigger(DIK_1))
	{
		m_CCharacter->SetCharaType(smile);
	}
	if (input->GetKeyTrigger(DIK_2))
	{
		m_CCharacter->SetCharaType(smile2);
	}
	if (input->GetKeyTrigger(DIK_3))
	{
		m_CCharacter->SetCharaType(star);
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
	}
}
/////////////EOF////////////