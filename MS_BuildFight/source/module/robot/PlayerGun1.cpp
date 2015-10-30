//=============================================================================
//
// MS_BuildFight [CPGunNight1.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#include "PlayerGun1.h"
#include "robotmotiondata.h"
#include "EnemyM.h"

#include "../etc/LocusEffect.h"

#include "../ui/Count.h"
#include "../ui/Effect.h"

#include "../../administer/Input.h"
#include "../../administer/Maneger.h"
#include "../../administer/Sound.h"

#include "../../administer/scene/Game.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CPGunNight1 :: CPGunNight1(int nPriority) : CPlayerM(OBJTYPE_PLAYER,nPriority)
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CPGunNight1 :: ~CPGunNight1(void)
{
}
//=============================================================================
// CPGunNight1生成
//=============================================================================
CPGunNight1 *CPGunNight1::Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos, D3DXVECTOR3 rot,bool CPU)
{
	CPGunNight1 *pformX;

	pformX = new CPGunNight1();
	pformX->Init(pDevice,pos,rot,CPU);

	return pformX;
}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CPGunNight1 :: Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos, D3DXVECTOR3 rot,bool CPU)
{
	// モデルパーツデータ生成
	CPlayerM::Init(pDevice,1,pos,rot,CPU);

	//テクスチャ設定
	SetTexture("data/TEXTURE/toumei3.png",1);
	SetTexture("data/TEXTURE/toumei.png",2);
	SetTexture("data/TEXTURE/toumei5.png",3);

	m_nEffectFinishCount=0;

	return S_OK;
}
//=============================================================================
// 終了
//=============================================================================
void CPGunNight1 :: Uninit(void)
{
	//様々なオブジェクトの終了（開放）処理
	CPlayerM::Uninit();

}
//=============================================================================
// 更新
//=============================================================================
void CPGunNight1 :: Update(void)
{
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	CSound	*pSound;
	pSound = CManager::GetSound();

	CEnemyM *pEnemyM;
	pEnemyM = CGame::GetEnemy(0);

	D3DXVECTOR3 enemyPos = pEnemyM->GetPos();

	// 前回の位置を保存
	m_PosOld = m_Pos;

	PlayerMove(0,m_bJump,false,pInputKeyboard,&m_Move,&m_rotDestModel,&m_RotCamera);

	int boostcount = 100;

	if(pInputKeyboard->GetKeyRepeat(DIK_SPACE)&& boostcount > 0 ||pInputKeyboard->GetReplayKey(DIK_SPACE))
	{// ジャンプ

		m_Move.y = VALUE_JUMP;
		m_bJump = true;

		// ジャンプモーション再生
		SetMotion(MOTIONTYPE_JUMP);
	}

	if(pInputKeyboard->GetKeyTrigger(DIK_1)||pInputKeyboard->GetKeyTrigger(DIK_X))
	{// パンチ(弱)
		// パンチ(弱)モーション再生
		SetMotion(MOTIONTYPE_PUNCH_W);
		//pSound->Play(SOUND_LABEL_SE_SLASH);
	}

	if(pInputKeyboard->GetKeyTrigger(DIK_2))
	{// パンチ(強)
		// パンチ(強)モーション再生
		SetMotion(MOTIONTYPE_PUNCH_S);
		//pSound->Play(SOUND_LABEL_SE_SLASH);
	}

	if(pInputKeyboard->GetKeyTrigger(DIK_3))
	{// キック(弱)
		// キック(弱)モーション再生
		SetMotion(MOTIONTYPE_KICK_W);
	}

	if(pInputKeyboard->GetKeyTrigger(DIK_4)||pInputKeyboard->GetKeyTrigger(DIK_C))
	{// キック(強)
		// キック(強)モーション再生
		SetMotion(MOTIONTYPE_KICK_S);
	}

	//if(pInputKeyboard->GetKeyTrigger(DIK_5)||pInputKeyboard->GetKeyTrigger(DIK_F))
	//{// キック(強)
	//	// キック(強)モーション再生
	//	SetMotion(MOTIONTYPE_ATTACK);
	//	pSound->PlayVoice(0,(VOICE_LABEL)(rand()%2+4));
	//}

	//スキル発動
	if(pInputKeyboard->GetKeyTrigger(DIK_V)||pInputKeyboard->GetReplayKey(DIK_V))
	{

	}
	//弾発射
	if(pInputKeyboard->GetKeyTrigger(DIK_Z)||pInputKeyboard->GetReplayKey(DIK_Z))
	{
		SetMotion(MOTIONTYPE_SHOT);
		//pSound->Play(SOUND_LABEL_SE_HIT000);

		//pSound->PlayVoice(0,(VOICE_LABEL)(rand()%3+1));
	}

	// 範囲チェック
	if(m_Pos.x > 900.0f-PLAYER_SIZE)
	{
		m_Pos.x = 900.0f-PLAYER_SIZE;
	}
	if(m_Pos.x < -900.0f+PLAYER_SIZE)
	{
		m_Pos.x = -900.0f+PLAYER_SIZE;
	}
	if(m_Pos.z > 900.0f-PLAYER_SIZE)
	{
		m_Pos.z = 900.0f-PLAYER_SIZE;
	}
	if(m_Pos.z < -900.0f+PLAYER_SIZE)
	{
		m_Pos.z = -900.0f+PLAYER_SIZE;
	}
	if(m_Pos.y > 700.0f+PLAYER_SIZE)
	{
		m_Pos.y=700.0f+PLAYER_SIZE;
	}

	if((m_motionType == MOTIONTYPE_OVER_LOAD && IsFinishMotion() == true)
	||(m_motionType == MOTIONTYPE_OVER_LOAD2 && IsFinishMotion() == true))
	{// スキルモーション終了
		// ニュートラルモーション再生
		SetMotion(MOTIONTYPE_NEUTRAL);
	}

	// アニメーション更新
	CPlayerM::Update();
}
//=============================================================================
// 描画
//=============================================================================
void CPGunNight1 :: Draw(void)
{
	CPlayerM::Draw();
}
//=============================================================================
// 再開
//=============================================================================
void CPGunNight1 :: Restart(D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	// モデルパーツデータ生成
	CPlayerM::Restart(pos,rot);

	m_nEffectFinishCount=0;

}
/////////////EOF////////////