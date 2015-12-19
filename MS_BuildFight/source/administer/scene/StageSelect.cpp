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
#include "../../module/ui/Cursor.h"
#include "../../module/ui/Button.h"

#include "../../module/etc/Camera.h"

#include "../../module/field/Domeunder.h"
#include "../../module/field/Dome.h"

#include "../../module/etc/Ball.h"
#include "../../form/formX.h"
#include "../../form/form3D.h"
#include "../../form/form2D.h"
#include "../../module/field/Field.h"

#include "../../module/robot/PlayerM.h"

#include "../../administer/Debugproc.h"

#include "../wiicon/wiimote.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
const float CURSOR_MOVE_COFF(10.0f);
const float STAGE_DIST_CENT(300.0f);
const float CAMERA_POS_X(0.0f);
const float CAMERA_POS_Y(0.0f);
const float CAMERA_POS_Z(-500.0f);

const float NAME_POS_X(650.0f);
const float NAME_POS_Y(550.0f);
const float NAME_WIDTH(450.0f);
const float NAME_HEIGHT(150.0f);

const float STAR_OFFSET(0.0f);
const float STAR_POS_Y(NAME_POS_Y + 90.0f);
const float STAR_WIDTH(64.0f);
const float STAR_HEIGHT(64.0f);

LPSTR pModName[MAX_STAGE]
{

	"data/MODEL/stage1.x",
		"data/MODEL/stage2.x",
		"data/MODEL/stage3.x",
		"data/MODEL/stage4.x",

};

//*****************************************************************************
// グローバル変数
//*****************************************************************************
float cnt = 0.0f;
D3DXVECTOR3 tmpRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//=============================================================================
// コンストラクタ
//=============================================================================
CStageSelect::CStageSelect(void) :
m_fTime(0.0f),
m_nState(STATE::NORMAL)
{
	m_pBackGround = NULL;
	m_pFade = NULL;

	// カメラの取得
	CCamera* pTmpCamera = CManager::GetCamera();

	pTmpCamera->SetPosP(D3DXVECTOR3(CAMERA_POS_X, CAMERA_POS_Y, CAMERA_POS_Z));

}
//=============================================================================
// デストラクタ
//=============================================================================
CStageSelect :: ~CStageSelect(void)
{
}
int selectStageOld = 0;

//=============================================================================
// 初期化
//=============================================================================
HRESULT CStageSelect::Init(LPDIRECT3DDEVICE9 pDevice)
{
	//サウンド取得の作成
	CSound *pSound;
	pSound = CManager::GetSound();

	//サウンド再生の作成
	//pSound->Play(SOUND_LABEL_BGM004);

	//空の作成
	m_pDome = CDome::Create(pDevice, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//空の作成
	m_pDome2 = CDomeU::Create(pDevice, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// キャラ選択用ロゴ
	m_pLogo = CButton::Create(pDevice, s_6, D3DXVECTOR3(SCREEN_WIDTH / 2, 100.0f, 0.0f), 900, 100);

	//背景の作成
	m_pBackGround = Cform3D::Create(pDevice, "data/TEXTURE/Select.png", D3DXVECTOR3(0.0f, 0.0f, 406.0f), D3DXVECTOR3(-D3DX_PI / 2.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
	m_pBackGround->SetDiffuse(1.0f, 1.0f, 1.0f, 0.6f);

	//フェードの作成
	m_pFade = CFade::Create(pDevice, 1);

	// カーソルの作成
	m_playerData[0].pCursor = CCursor::Create(pDevice, s_4, D3DXVECTOR3(1000.0f, 600.0f, 0.0f), 128, 128);
	m_playerData[1].pCursor = CCursor::Create(pDevice, s_5, D3DXVECTOR3(400.0f, 600.0f, 0.0f), 128, 128);
	m_playerData[0].nSelectNum = 0;
	m_playerData[1].nSelectNum = 0;

	// ステージ名
	m_pStageName[0] = CCharPicture::Create(pDevice, sn1, D3DXVECTOR3(NAME_POS_X, NAME_POS_Y, 0.0f), NAME_WIDTH, NAME_HEIGHT);
	m_pStageName[1] = CCharPicture::Create(pDevice, sn2, D3DXVECTOR3(NAME_POS_X, NAME_POS_Y, 0.0f), NAME_WIDTH, NAME_HEIGHT);
	m_pStageName[2] = CCharPicture::Create(pDevice, sn3, D3DXVECTOR3(NAME_POS_X, NAME_POS_Y, 0.0f), NAME_WIDTH, NAME_HEIGHT);
	m_pStageName[3] = CCharPicture::Create(pDevice, sn4, D3DXVECTOR3(NAME_POS_X, NAME_POS_Y, 0.0f), NAME_WIDTH, NAME_HEIGHT);

	// 変数定義
	float fTmpRad((D3DX_PI * 2.0f) / MAX_STAGE);
	float tmpRot((D3DX_PI * 2.0f));
	D3DXVECTOR3 tmpObjPos;
	int nlevelArray[MAX_STAGE]{1, 3, 6, 10};

	// 全てのステージを生成
	for (int i = 0; i < MAX_STAGE; i++)
	{

		// 生成
		m_Obj[i].pDispObj = CformX::Create(pDevice, pModName[i], D3DXVECTOR3(0.0f, 100.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		// 各値の設定
		m_Obj[i].fLenCoff = fTmpRad * static_cast<float>(i);
		m_Obj[i].fLenCoffDest = m_Obj[i].fLenCoff;
		m_Obj[i].nDestCnt = i;
		tmpObjPos = m_Obj[i].pDispObj->GetPos();

		// 衛星軌道用の係数をイージング曲線で求める
		m_Obj[i].fLenCoff = CCursor::EsasingNone(m_Obj[i].fLenCoff, m_Obj[m_Obj[i].nDestCnt].fLenCoffDest, m_fTime);

		// 原点0を中心として衛星軌道用の座標を求める
		tmpObjPos.x = 0.0f + sinf(m_Obj[i].fLenCoff) * STAGE_DIST_CENT;
		tmpObjPos.y = 0.0f;
		tmpObjPos.z = 0.0f + cosf(m_Obj[i].fLenCoff) * -STAGE_DIST_CENT;

		// 座標を更新
		m_Obj[i].pDispObj->SetPos(tmpObjPos);

		// 難易度の設定
		m_Obj[i].nlevel = nlevelArray[i];

	}

	int levelCnt(1);
	float posX(0.0f);
	D3DXCOLOR tmpCol;

	// 難易度可視化用の★
	for (int i = 0; i < MAX_LEVEL; i++)
	{
		// 座標の計算
		posX = (NAME_POS_X - NAME_WIDTH * 0.25f) + STAR_WIDTH * i;

		// 生成
		m_pLevelStar[i] = CCharPicture::Create(pDevice, ls, D3DXVECTOR3(posX, STAR_POS_Y, 0.0f), STAR_WIDTH, STAR_HEIGHT);

		// 色付け
		// 中間
		if (levelCnt > 3 && levelCnt < 8)
		{
			tmpCol = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		}
		else if (levelCnt > 7)
		{
			tmpCol = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		}
		else
		{
			tmpCol = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		}

		m_pLevelStar[i]->SetDiffuse(tmpCol.r, tmpCol.g, tmpCol.b, tmpCol.a);
		m_pLevelStar[i]->SetDiff(tmpCol);

		levelCnt++;

	}
	// フェードアウトの開始
	m_pFade->StartFade(FADE_OUT, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CManager::GetSelectChar(0));

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CStageSelect::Uninit(void)
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
void CStageSelect::Update(void)
{


	//現在の状態によって分岐
	switch (m_nState)
	{
	case STATE::NORMAL:

		// ボタンでステージを選択
		SelectByButton();

		break;

	case STATE::SATELLITE_ORBIT:

		// 衛星軌道時の
		UpdateSelectObject();

		break;

	case STATE::CHANGE_SCENE:

		// フェードの更新
		UpdateFade();

		break;
	default:
		break;
	}

	// 全てのステージ
	for (int i = 0; i < MAX_STAGE; i++)
	{
		m_pStageName[i]->ChangeGuiState(m_pStageName[i]->GetGuiMode());;

		// 難易度可視化用の★
		for (int j = 0; j < m_Obj[selectStageOld].nlevel; j++)
		{

			m_pLevelStar[j]->ChangeGuiState(m_pLevelStar[j]->GetGuiMode());

		}
	}
#ifdef _DEBUG

	CDebugProc::Print("選択中のボタン:%d\n", m_playerData[0].nSelectNum);

#endif
}

//=============================================================================
// 描画
//=============================================================================
void CStageSelect::Draw(void)
{

	m_pDome->Draw();
	m_pDome2->Draw();

	// 背景の描画
	m_pBackGround->Draw();


	// 全てのステージ
	for (int i = 0; i < MAX_STAGE; i++)
	{

		// 描画
		m_Obj[i].pDispObj->Draw();

	}

	// 全てのカーソル
	for (int i = 0; i < 2; i++)
	{

		// 描画
		m_playerData[i].pCursor->Draw();

	}

	// 難易度設定用の★
	for (int i = 0; i < m_Obj[selectStageOld].nlevel; i++)
	{
		m_pLevelStar[i]->Draw();
	}

	// ロゴ
	m_pLogo->Draw();

	// 現在選択中のステージ名
	m_pStageName[selectStageOld]->Draw();

	//フェード
	m_pFade->Draw();

}
float tmpTime = 0.0f;
//=============================================================================
// 描画
//=============================================================================
void CStageSelect::UpdateSelectObject()
{
	D3DXVECTOR3 tmpObjPos;

	// 全てのステージ
	for (int i = 0; i < MAX_STAGE; i++)
	{

		// 座標の取得
		tmpObjPos = m_Obj[i].pDispObj->GetPos();

		// 衛星軌道用の係数をイージング曲線で求める
		m_Obj[i].fLenCoff = CCursor::EsasingNone(m_Obj[i].fLenCoff, m_Obj[m_Obj[i].nDestCnt].fLenCoffDest, m_fTime);

		// 原点0を中心として衛星軌道用の座標を求める
		tmpObjPos.x = 0.0f + sinf(m_Obj[i].fLenCoff) * STAGE_DIST_CENT;
		tmpObjPos.y = 0.0f;
		tmpObjPos.z = 0.0f + cosf(m_Obj[i].fLenCoff) * -STAGE_DIST_CENT;

		// 座標を更新
		m_Obj[i].pDispObj->SetPos(tmpObjPos);

		// 
		tmpTime = CCursor::EsasingNone(tmpTime, 1.0f, m_fTime);

		// 全てのステージ
		m_pStageName[i]->SetDiffuse(1.0f, 1.0f, 1.0f, 1.0f - tmpTime);
		m_pStageName[i]->SetDiff(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - tmpTime));
		m_pStageName[i]->ChangeGuiState(GUI_MODE::GRADUALLY_DESELECT);

#ifdef _DEBUG

		//CDebugProc::Print("X座標:%f\n", tmpObjPos.x);
		//CDebugProc::Print("Z座標:%f\n", tmpObjPos.z);
		CDebugProc::Print("衛星軌道用の係数:%f\n", m_Obj[i].fLenCoff);

#endif

	}

	int levelCnt(1);
	D3DXCOLOR tmpCol;
	// 難易度可視化用の★
	for (int j = 0; j < MAX_LEVEL; j++)
	{

		tmpCol = m_pLevelStar[j]->GetDiff();
		m_pLevelStar[j]->SetDiffuse(tmpCol.r, tmpCol.g, tmpCol.b, 1.0f - tmpTime);
		m_pLevelStar[j]->SetDiff(D3DXCOLOR(tmpCol.r, tmpCol.g, tmpCol.b, 1.0f - tmpTime));
		m_pStageName[j]->ChangeGuiState(GUI_MODE::GRADUALLY_DESELECT);

	}

	// イージング曲線用タイマーの更新
	if (m_fTime >= 1.0f)
	{
		m_fTime = 0.0f;

		m_nState = STATE::NORMAL;

		for (int i = 0; i < MAX_STAGE; i++)
		{
			m_Obj[i].fLenCoff = m_Obj[m_Obj[i].nDestCnt].fLenCoffDest;
			m_pStageName[i]->ChangeGuiState(GUI_MODE::GRADUALLY_SELECT);
			tmpTime = 0.0f;
		}

		// 難易度可視化用の★
		for (int j = 0; j < MAX_LEVEL; j++)
		{

			m_pStageName[j]->ChangeGuiState(GUI_MODE::GRADUALLY_SELECT);

		}

		selectStageOld = m_playerData[0].nSelectNum;


	}
	else
	{
		m_fTime += 0.025f;
	}

}
//=============================================================================
// フェードの更新
//=============================================================================
void CStageSelect::UpdateFade(void)
{

	//フェードインが終わったら
	if (m_pFade->GetFade() == FADE_IN_END)
	{
		//次のフェーズを変える
		CManager::SetAfterScene(PHASETYPE_GAME);
	}

}
//=============================================================================
// キーボードでの選択
//=============================================================================
void CStageSelect::SelectByButton(void)
{

	// Wiiコンの取得
	WiiRemote* pTmpPad = CManager::GetWii(1);

	//サウンド取得の作成
	CSound *pSound;
	pSound = CManager::GetSound();

	//キーボードインプットの受け取り
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	float fTmpRad = (D3DX_PI * 2.0f) / MAX_STAGE;
	float tmpRot((D3DX_PI * 2.0f));

	//エンターキーが押された場合
	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN) || pTmpPad->GetKeyTrigger(WII_BUTTOM_A))
	{

		// 遷移処理
		m_nState = STATE::CHANGE_SCENE;

		// 選択したマップを保存
		CManager::SetSelectMap(m_playerData[0].nSelectNum);

		m_pFade->StartFade(FADE_IN, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), CManager::GetSelectChar(0));
		//pSound->PlayVoice(m_playerData[0].nSelectNum,VOICE_LABEL_SE_START);

	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_A) || pInputKeyboard->GetKeyTrigger(DIK_LEFT) || pTmpPad->GetKeyTrigger(WII_BUTTOM_LEFT))
	{

		//pSound->Play(SOUND_LABEL_SE_SELECT000);
		selectStageOld = m_playerData[0].nSelectNum;

		m_playerData[0].nSelectNum--;
		NomalizeSelectObject(m_playerData[0].nSelectNum);

		for (int i = 0; i < MAX_STAGE; i++)
		{
			m_Obj[i].nDestCnt--;
			NomalizeSelectObject(m_Obj[i].nDestCnt);

			if (m_Obj[i].fLenCoff <= 0.0f)
			{
				m_Obj[i].fLenCoff = tmpRot;
			}
		}
		m_fTime = 0.0f;

		m_nState = STATE::SATELLITE_ORBIT;

	}
	else if (pInputKeyboard->GetKeyTrigger(DIK_D) || pInputKeyboard->GetKeyTrigger(DIK_RIGHT) || pTmpPad->GetKeyTrigger(WII_BUTTOM_RIGHT))
	{
		//pSound->Play(SOUND_LABEL_SE_SELECT000);
		selectStageOld = m_playerData[0].nSelectNum;

		m_playerData[0].nSelectNum++;
		NomalizeSelectObject(m_playerData[0].nSelectNum);

		for (int i = 0; i < MAX_STAGE; i++)
		{
			m_Obj[i].nDestCnt++;
			NomalizeSelectObject(m_Obj[i].nDestCnt);

			if (m_Obj[i].fLenCoff >= tmpRot - fTmpRad)
			{
				m_Obj[i].fLenCoff = 0.0f - fTmpRad;
			}


		}
		m_fTime = 0.0f;

		m_nState = STATE::SATELLITE_ORBIT;

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
//=============================================================================
// 正規化
//=============================================================================
void CStageSelect::NomalizeSelectObject(int& nParamVal)
{
	// 各配置によって移動する
	if (nParamVal < 0)
	{

		nParamVal = MAX_STAGE - 1;

	}
	else if (nParamVal >= MAX_STAGE)
	{

		nParamVal = 0;

	}

}
////////////EOF////////////