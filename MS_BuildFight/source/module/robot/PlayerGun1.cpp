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
#include "../../administer/netClient.h"
#include "../../administer/Sound.h"

#include "../../administer/scene/Game.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPGunNight1 :: CPGunNight1(int nPriority) : CPlayerM(OBJTYPE_PLAYER,nPriority)
{
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPGunNight1 :: ~CPGunNight1(void)
{
}
//=============================================================================
// CPGunNight1����
//=============================================================================
CPGunNight1 *CPGunNight1::Create(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos, D3DXVECTOR3 rot,bool CPU)
{
	CPGunNight1 *pformX;

	pformX = new CPGunNight1();
	pformX->Init(pDevice,pos,rot,CPU);

	return pformX;
}
//=============================================================================
// ������
//=============================================================================
HRESULT CPGunNight1 :: Init(LPDIRECT3DDEVICE9 pDevice,D3DXVECTOR3 pos, D3DXVECTOR3 rot,bool CPU)
{
	// ���f���p�[�c�f�[�^����
	CPlayerM::Init(pDevice,1,pos,rot,CPU);

	//�e�N�X�`���ݒ�
	SetTexture("data/TEXTURE/toumei3.png",1);
	SetTexture("data/TEXTURE/toumei.png",2);
	SetTexture("data/TEXTURE/toumei5.png",3);

	m_nEffectFinishCount=0;

	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CPGunNight1 :: Uninit(void)
{
	//�l�X�ȃI�u�W�F�N�g�̏I���i�J���j����
	CPlayerM::Uninit();

}
//=============================================================================
// �X�V
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

	// �O��̈ʒu��ۑ�
	m_PosOld = m_Pos;

	PlayerMove(0,m_bJump,false,pInputKeyboard,&m_Move,&m_rotDestModel,&m_RotCamera);

	int boostcount = 100;

	if(pInputKeyboard->GetKeyRepeat(DIK_SPACE)&& boostcount > 0 ||pInputKeyboard->GetReplayKey(DIK_SPACE))
	{// �W�����v

		m_Move.y = VALUE_JUMP;
		m_bJump = true;

		// �W�����v���[�V�����Đ�
		SetMotion(MOTIONTYPE_JUMP);
	}

	if(pInputKeyboard->GetKeyTrigger(DIK_1)||pInputKeyboard->GetKeyTrigger(DIK_X))
	{// �p���`(��)
		// �p���`(��)���[�V�����Đ�
		SetMotion(MOTIONTYPE_PUNCH_W);
		//pSound->Play(SOUND_LABEL_SE_SLASH);
	}

	if(pInputKeyboard->GetKeyTrigger(DIK_2))
	{// �p���`(��)
		// �p���`(��)���[�V�����Đ�
		SetMotion(MOTIONTYPE_PUNCH_S);
		//pSound->Play(SOUND_LABEL_SE_SLASH);
	}

	if(pInputKeyboard->GetKeyTrigger(DIK_3))
	{// �L�b�N(��)
		// �L�b�N(��)���[�V�����Đ�
		SetMotion(MOTIONTYPE_KICK_W);
	}

	if(pInputKeyboard->GetKeyTrigger(DIK_4)||pInputKeyboard->GetKeyTrigger(DIK_C))
	{// �L�b�N(��)
		// �L�b�N(��)���[�V�����Đ�
		SetMotion(MOTIONTYPE_KICK_S);
	}

	//if(pInputKeyboard->GetKeyTrigger(DIK_5)||pInputKeyboard->GetKeyTrigger(DIK_F))
	//{// �L�b�N(��)
	//	// �L�b�N(��)���[�V�����Đ�
	//	SetMotion(MOTIONTYPE_ATTACK);
	//	pSound->PlayVoice(0,(VOICE_LABEL)(rand()%2+4));
	//}

	//�X�L������
	if(pInputKeyboard->GetKeyTrigger(DIK_V)||pInputKeyboard->GetReplayKey(DIK_V))
	{

	}
	//�e����
	if(pInputKeyboard->GetKeyTrigger(DIK_Z)||pInputKeyboard->GetReplayKey(DIK_Z))
	{
		if (m_bVsFlag)
		{
			// �f�[�^���M
			DATA data;
			data.Type = DATA_TYPE_SHOT;

			data.Motion.motion = 0;

			CNetClient::SendData(data);
		}

		SetMotion(MOTIONTYPE_SHOT);
		//pSound->Play(SOUND_LABEL_SE_HIT000);

		//pSound->PlayVoice(0,(VOICE_LABEL)(rand()%3+1));
	}

	// �͈̓`�F�b�N
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
	{// �X�L�����[�V�����I��
		// �j���[�g�������[�V�����Đ�
		SetMotion(MOTIONTYPE_NEUTRAL);
	}

	// �A�j���[�V�����X�V
	CPlayerM::Update();
}
//=============================================================================
// �`��
//=============================================================================
void CPGunNight1 :: Draw(void)
{
	CPlayerM::Draw();
}
//=============================================================================
// �ĊJ
//=============================================================================
void CPGunNight1 :: Restart(D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	// ���f���p�[�c�f�[�^����
	CPlayerM::Restart(pos,rot);

	m_nEffectFinishCount=0;

}
/////////////EOF////////////