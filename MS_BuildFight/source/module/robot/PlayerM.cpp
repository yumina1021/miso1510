//=============================================================================
//
// MS_BuildFight [CPlayerM.cpp]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#include "PlayerM.h"
#include "Model.h"
#include "robotmotiondata.h"

#include "../field/Field.h"

#include "../etc/Camera.h"

#include "../../administer/Input.h"
#include "../../administer/Maneger.h"
#include "../../administer/debugproc.h"
#include "../../administer/Sound.h"

#include "../../administer/scene/Game.h"

#include "../../exten_common.h"

#include "../../administer/Texture.h"
//*****************************************************************************
// �ÓI�ϐ�
//*****************************************************************************

#define SHOT_MOTION_COUNT_MAX	(80)
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayerM :: CPlayerM(OBJTYPE objtype,int nPriority) : Cform(objtype,nPriority)
{
	for(int nCntModel = 0; nCntModel < MODELPARTS_MAX; nCntModel++)
	{
		m_apModel[nCntModel] = NULL;
	}

	//m_pD3DTex=NULL;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayerM :: ~CPlayerM(void)
{
}
//=============================================================================
// CPlayerM����
//=============================================================================
CPlayerM *CPlayerM::Create(LPDIRECT3DDEVICE9 pDevice,int nTypeModel,D3DXVECTOR3 movePos,D3DXVECTOR3 moveRot)
{
	CPlayerM *pformX;

	pformX = new CPlayerM();
	pformX->Init(pDevice,nTypeModel,movePos,moveRot,false);

	return pformX;
}
//=============================================================================
// ������
//=============================================================================
HRESULT CPlayerM :: Init(LPDIRECT3DDEVICE9 pDevice,int nTypeModel,D3DXVECTOR3 pos, D3DXVECTOR3 rot,bool CPU)
{
	//�f�o�C�X�̎擾
	m_pDevice=pDevice;

	//�^�C�v�̕ۑ�
	m_nType=nTypeModel;

	for(int nCntModel = 0; nCntModel < MODELPARTS_MAX; nCntModel++)
	{
		m_apModel[nCntModel] = CModel::Create(pDevice,nCntModel,nTypeModel*12,
			D3DXVECTOR3(g_aKeyDef[nCntModel][0], g_aKeyDef[nCntModel][1], g_aKeyDef[nCntModel][2]),
			D3DXVECTOR3(g_aKeyDef[nCntModel][3], g_aKeyDef[nCntModel][4], g_aKeyDef[nCntModel][5]));
	}

	// ���f���p�[�c�K�w�\���ݒ�
	m_apModel[0]->SetParent(NULL);			// [0]��   �� (�e)NULL
	m_apModel[1]->SetParent(m_apModel[0]);	// [1]��   �� (�e)[0]��
	m_apModel[2]->SetParent(m_apModel[0]);	// [2]�E�r �� (�e)[0]��
	m_apModel[3]->SetParent(m_apModel[2]);	// [3]�E�� �� (�e)[2]�E�r
	m_apModel[4]->SetParent(m_apModel[3]);	// [3]�E�� �� (�e)[2]�E�r
	m_apModel[5]->SetParent(m_apModel[0]);	// [4]���r �� (�e)[0]��
	m_apModel[6]->SetParent(m_apModel[5]);	// [5]���� �� (�e)[4]���r
	m_apModel[7]->SetParent(m_apModel[6]);	// [5]���� �� (�e)[4]���r
	m_apModel[8]->SetParent(m_apModel[0]);	// [6]�E�� �� (�e)[0]��
	m_apModel[9]->SetParent(m_apModel[8]);	// [7]�E�� �� (�e)[6]�E��
	m_apModel[10]->SetParent(m_apModel[0]);	// [8]���� �� (�e)[0]��
	m_apModel[11]->SetParent(m_apModel[10]);	// [9]���� �� (�e)[8]����

	m_Pos = pos;
	m_PosOld = pos;
	m_Rot = rot;
	m_rotDestModel = rot;
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�p�[�c�������i�[
	m_nNumModel = MODELPARTS_MAX;

	m_nNumKey = 0;
	m_pKeyInfo = NULL;
	m_nKey = 0;

	m_nCountMotion = 0;

	m_fShotMotionRatio = 0.0f;
	m_nShotMotionCntPlus = 0;

	m_bLoopMotion = false;

	m_bMotion = false;
	m_bFinishMotion = false;

	m_bPause = false;

	m_bDispDebug = true;

	m_Min=D3DXVECTOR3(-30.0f,-20.0f,-30.0f);
	m_Max=D3DXVECTOR3(30.0f,20.0f,30.0f);

	// �A�j���[�V�����ݒ�
	SetMotion(MOTIONTYPE_NEUTRAL);

	//�s�N�Z���V�F�[�_�[�p�ɕϊ�1
	Create_PS("source/shader/basicPS.hlsl", "PS_CHARCTER", &shaderSet.ps, &shaderSet.psc,m_pDevice);

	//�o�[�e�b�N�X�V�F�[�_�[�p�ɕϊ�1
	Create_VS("source/shader/basicVS.hlsl", "VS_CHARCTER", &shaderSet.vs, &shaderSet.vsc, m_pDevice);

	//�e�N�X�`�����
	m_texid = TEXTURE_CHARA;
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/chara.png", &m_pD3DTex);

	return S_OK;
}
//=============================================================================
// �I��
//=============================================================================
void CPlayerM :: Uninit(void)
{
	//�l�X�ȃI�u�W�F�N�g�̏I���i�J���j����

	// ���f���̊J��
	for(int nCntModel = 0; nCntModel < MODELPARTS_MAX; nCntModel++)
	{
		if(m_apModel[nCntModel])
		{
			m_apModel[nCntModel]->Uninit();
			delete m_apModel[nCntModel];
			m_apModel[nCntModel] = NULL;
		}
	}

	if(m_pKeyInfo)
	{
		m_pKeyInfo = NULL;
	}

	//m_pD3DTex->Release();
	//m_pD3DTex = NULL;

	if (shaderSet.ps != NULL)	shaderSet.ps->Release();
	if (shaderSet.psc != NULL)	shaderSet.psc->Release();
	if (shaderSet.vs != NULL)	shaderSet.vs->Release();
	if (shaderSet.vsc != NULL)	shaderSet.vsc->Release();
	Cform::Release();

}
void CPlayerM :: Restart(D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	m_Pos = pos;
	m_PosOld = pos;
	m_Rot = rot;
	m_rotDestModel = rot;
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nNumKey = 0;
	m_pKeyInfo = NULL;
	m_nKey = 0;
	m_nCountMotion = 0;
	m_bLoopMotion = false;

	m_bMotion = false;
	m_bFinishMotion = false;

	m_bPause = false;

	m_bDispDebug = true;

	// �A�j���[�V�����ݒ�
	SetMotion(MOTIONTYPE_NEUTRAL);


}
//=============================================================================
// �X�V
//=============================================================================
void CPlayerM :: Update(void)
{
	//�T�E���h�̎擾
	CSound	*pSound;
	pSound = CManager::GetSound();

	//�L�[�{�[�h�̎擾
	CInputKeyboard	*pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�@���i�܂����g�p�j
	D3DXVECTOR3 normal;

	//�ϐ���`
	float fDiffRotY=0;


	if (m_bPause == false)
	{
		//// �ړI�̊p�x�܂ł̍���
		//fDiffRotY = Rotation_Normalizer(m_rotDestModel.y - m_Rot.y);

		//// �ړI�̊p�x�܂Ŋ�����������
		//m_Rot.y +=fDiffRotY * RATE_ROTATE_PLAYER;

		//m_Rot.y = Rotation_Normalizer(m_Rot.y);

		//// �ʒu�ړ�
		//m_Pos.x += m_Move.x;
		//m_Pos.z += m_Move.z;

		//m_Move.x += (0.0f - m_Move.x) * REGIST_MOVE;
		//m_Move.z += (0.0f - m_Move.z) * REGIST_MOVE;

		if((m_motionType == MOTIONTYPE_SHOT && IsFinishMotion() == true))
		{// �V���b�g���[�V�����I��
			// �j���[�g�������[�V�����Đ�
			SetMotion(MOTIONTYPE_NEUTRAL);
		}
		
		CDebugProc::Print("���݂̃��[�V�����F%d,Key���F%d\n", m_motionType,m_nKey);
		CDebugProc::Print("�����F%f\n", m_fShotMotionRatio);


		if (pInputKeyboard->GetKeyPress(DIK_U))
		{
			m_fShotMotionRatio = 0.0f;
			m_nShotMotionCntPlus = 0;
			SetMotion(MOTIONTYPE_SHOT);
		}

		if (pInputKeyboard->GetKeyPress(DIK_I))
		{
			m_fShotMotionRatio ++;
		}
		if (pInputKeyboard->GetKeyPress(DIK_O))
		{
			m_fShotMotionRatio --;
		}

		// �A�j���[�V�����X�V
		if (m_motionType == MOTIONTYPE_SHOT)
		{
			UpdateShotMotion();
		}
		else
		{
			UpdateMotion();
		}
		
	}

}
//=============================================================================
// �`��
//=============================================================================
void CPlayerM::Draw(void)
{
	D3DXMATRIX mtxScale, mtxRot, mtxTranslate;

	CCamera* pCamera = CManager::GetCamera();

	//SetRotCamera(pCamera->GetRotCamera());

	//SetMtxView(pCamera->GetMtxView());

	//// ���[���h�}�g���b�N�X�̏�����
	//D3DXMatrixIdentity(&m_mtxWorld);

	//// ��]�𔽉f
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//// �ړ��𔽉f
	//D3DXMatrixTranslation(&mtxTranslate, m_Pos.x, m_Pos.y, m_Pos.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�

	CDebugProc::Print("PlayerM%f,%f,%f\n", m_Pos.x, m_Pos.y, m_Pos.z);
	CDebugProc::Print("PlayerM%f,%f,%f\n", m_Rot.x, m_Rot.y, m_Rot.z);
	// ���f���p�[�c�̕`��
	m_apModel[0]->SetPosOrg(m_Pos);
	m_apModel[0]->SetRot(m_Rot);
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		if (m_apModel[nCntModel])
		{
			m_apModel[nCntModel]->Draw(CTexture::GetTex(m_texid), &shaderSet, pCamera);
		}
	}
}
//=============================================================================
// ���[�V�����ݒ�
//=============================================================================
void CPlayerM::SetMotion(MOTIONTYPE motionType)
{

	switch(motionType)
	{
	case MOTIONTYPE_NEUTRAL:
		m_pKeyInfo = &g_aKeyNeutral[0];
		m_nNumKey = sizeof g_aKeyNeutral / sizeof(KEY_INFO);
		m_bLoopMotion = true;
		break;

	case MOTIONTYPE_SHOT:
		m_pKeyInfo = &g_aKeyShot[0];
		m_nNumKey = sizeof g_aKeyShot / sizeof(KEY_INFO);
		m_bLoopMotion = false;
		break;
	}

	m_motionType = motionType;
	m_nKey = 0;
	
	m_nCountMotion = 0;
	m_bMotion = true;
	m_bFinishMotion = false;

	// �����l�ݒ�
	for(int nCntModel = 0; nCntModel < MODELPARTS_MAX; nCntModel++)
	{
		m_apModel[nCntModel]->SetPos(m_pKeyInfo->aKey[nCntModel].fPosX,
											m_pKeyInfo->aKey[nCntModel].fPosY,
											m_pKeyInfo->aKey[nCntModel].fPosZ);

		m_apModel[nCntModel]->SetRot(m_pKeyInfo->aKey[nCntModel].fRotX,
											m_pKeyInfo->aKey[nCntModel].fRotY,
											m_pKeyInfo->aKey[nCntModel].fRotZ);
	}
}

//=============================================================================
// ���[�V�����X�V
//=============================================================================
void CPlayerM::UpdateMotion(void)
{
	if(m_bMotion == true)
	{// ���[�V��������
		for(int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
		{
			if(m_apModel[nCntModel])
			{// ���f������

				KEY *pKey, *pKeyNext;
				float fDiffMotion;
				float fRateMotion;

				float fPosX, fPosY, fPosZ;
				float fRotX, fRotY, fRotZ;

				// ���݂̃L�[
				pKey = &m_pKeyInfo[m_nKey].aKey[nCntModel];
				// ���̃L�[
				pKeyNext = &m_pKeyInfo[((m_nKey + 1) % m_nNumKey)].aKey[nCntModel];
				// ���݂̃L�[�̍Đ��t���[���S�̂ɑ΂��鑊�Βl
				fRateMotion = (float)m_nCountMotion / (float)m_pKeyInfo[m_nKey].nFrame;

				// X�ړ�
				fDiffMotion = pKeyNext->fPosX - pKey->fPosX;
				fPosX = (pKey->fPosX + (fDiffMotion * fRateMotion));

				// Y�ړ�
				fDiffMotion = pKeyNext->fPosY - pKey->fPosY;
				fPosY = pKey->fPosY + (fDiffMotion * fRateMotion);

				// Z�ړ�
				fDiffMotion = pKeyNext->fPosZ - pKey->fPosZ;
				fPosZ = pKey->fPosZ + (fDiffMotion * fRateMotion);

				// X��]
				fDiffMotion = Rotation_Normalizer(pKeyNext->fRotX - pKey->fRotX);


				fRotX = Rotation_Normalizer(pKey->fRotX + (fDiffMotion * fRateMotion));

				// Y��]
				fDiffMotion = Rotation_Normalizer(pKeyNext->fRotY - pKey->fRotY);

				fRotY = Rotation_Normalizer(pKey->fRotY + (fDiffMotion * fRateMotion));

				// Z��]
				fDiffMotion = Rotation_Normalizer(pKeyNext->fRotZ - pKey->fRotZ);

				fRotZ = Rotation_Normalizer(pKey->fRotZ + (fDiffMotion * fRateMotion));

				// �ʒu(�I�t�Z�b�g)��ݒ�
				m_apModel[nCntModel]->SetPos(fPosX, fPosY, fPosZ);

				// ��]��ݒ�
				m_apModel[nCntModel]->SetRot(fRotX, fRotY, fRotZ);
			}
		}

		m_nCountMotion++;

		if(m_nCountMotion > m_pKeyInfo[m_nKey].nFrame)
		{// �L�[�̍Đ��t���[�����ɒB����
			if(m_bLoopMotion == false && (m_nKey + 2) >= m_nNumKey)
			{// �P�����[�V�����ōŏI�L�[�ɒB����
				m_bFinishMotion = true;
				m_nCountMotion = m_pKeyInfo[(m_nNumKey - 1)].nFrame;
			}
			else
			{
				m_nKey = (m_nKey + 1) % m_nNumKey;
				m_nCountMotion = 0;
			}	
		}
	}
}
//=============================================================================
// �ł��[�V�����X�V
//=============================================================================
void CPlayerM::UpdateShotMotion(void)
{
	if (m_bMotion == true)
	{// ���[�V��������
		for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
		{
			if (m_apModel[nCntModel])
			{// ���f������

				KEY *pKey, *pKeyNext;
				float fDiffMotion;
				float fRateMotion;

				float fPosX, fPosY, fPosZ;
				float fRotX, fRotY, fRotZ;

				// ���݂̃L�[
				pKey = &m_pKeyInfo[m_nKey].aKey[nCntModel];
				// ���̃L�[
				pKeyNext = &m_pKeyInfo[((m_nKey + 1) % m_nNumKey)].aKey[nCntModel];

				// ���݂̃L�[�̍Đ��t���[���S�̂ɑ΂��鑊�Βl
				fRateMotion = (m_fShotMotionRatio - m_nShotMotionCntPlus) / (float)m_pKeyInfo[m_nKey].nFrame;

				// X�ړ�
				fDiffMotion = pKeyNext->fPosX - pKey->fPosX;
				fPosX = (pKey->fPosX + (fDiffMotion * fRateMotion));

				// Y�ړ�
				fDiffMotion = pKeyNext->fPosY - pKey->fPosY;
				fPosY = pKey->fPosY + (fDiffMotion * fRateMotion);

				// Z�ړ�
				fDiffMotion = pKeyNext->fPosZ - pKey->fPosZ;
				fPosZ = pKey->fPosZ + (fDiffMotion * fRateMotion);

				// X��]
				fDiffMotion = Rotation_Normalizer(pKeyNext->fRotX - pKey->fRotX);

				fRotX = Rotation_Normalizer(pKey->fRotX + (fDiffMotion * fRateMotion));

				// Y��]
				fDiffMotion = Rotation_Normalizer(pKeyNext->fRotY - pKey->fRotY);

				fRotY = Rotation_Normalizer(pKey->fRotY + (fDiffMotion * fRateMotion));

				// Z��]
				fDiffMotion = Rotation_Normalizer(pKeyNext->fRotZ - pKey->fRotZ);

				fRotZ = Rotation_Normalizer(pKey->fRotZ + (fDiffMotion * fRateMotion));

				// �ʒu(�I�t�Z�b�g)��ݒ�
				m_apModel[nCntModel]->SetPos(fPosX, fPosY, fPosZ);

				// ��]��ݒ�
				m_apModel[nCntModel]->SetRot(fRotX, fRotY, fRotZ);
			}
		}

		if (m_fShotMotionRatio < 0.0f)
		{
			m_fShotMotionRatio = 0.0f;
		}

		// �L�[�̍Đ��t���[�����ɒB����
		if (m_fShotMotionRatio > m_pKeyInfo[m_nKey].nFrame + m_nShotMotionCntPlus)
		{
			if (m_fShotMotionRatio > SHOT_MOTION_COUNT_MAX)
			{
				m_fShotMotionRatio = SHOT_MOTION_COUNT_MAX;
				m_bFinishMotion = true;
				m_nCountMotion = m_pKeyInfo[(m_nNumKey - 1)].nFrame;
			}
			else
			{
				m_nKey = (m_nKey + 1) % m_nNumKey;
				m_nShotMotionCntPlus = m_fShotMotionRatio;
			}
		}

		//�������[�V�������߂�����
		if (m_nShotMotionCntPlus > m_fShotMotionRatio)
		{
			m_nKey = (m_nKey - 1) % m_nNumKey;
			m_fShotMotionRatio = m_nShotMotionCntPlus;
			m_nShotMotionCntPlus = 0.0f;
		}
	}
}

D3DXVECTOR3 CPlayerM ::lerpVec(D3DXVECTOR3 a,D3DXVECTOR3 b,float per)
{
	D3DXVECTOR3 c;

	c.x=lerp(a.x,b.x,per);
	c.y=lerp(a.y,b.y,per);
	c.z=lerp(a.z,b.z,per);

	return c;
}

/////////////EOF////////////