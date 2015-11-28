//=============================================================================
//
// ���͏��� [input.h]
// Author : TOMOKI�@OOHASHI
//	AT12A241		2013/07/02
//=============================================================================
#ifndef _WIIREMOTE_H_
#define _WIIREMOTE_H_

#include "wiimote.h"
#include "../../common.h"
//
//
//


#define DOWN_ACTION	 0x01
#define UP_ACTION	 0x02
#define RIGHT_ACTION 0x04
#define LEFT_ACTION	 0x08
#define FRONT_ACTION 0x10
#define BACK_ACTION	 0x20

enum WII_BUTTOM
{
	WII_BUTTOM_A = 0,
	WII_BUTTOM_B,
	WII_BUTTOM_1,
	WII_BUTTOM_2,
	WII_BUTTOM_PLUS,
	WII_BUTTOM_MINUS,
	WII_BUTTOM_UP,
	WII_BUTTOM_DOWN,
	WII_BUTTOM_RIGHT,
	WII_BUTTOM_LEFT,
	WII_BUTTOM_MAX,
};
enum 
{
	SAMPLE_SHOT = 0,
	SAMPLE_MAX,
};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
class WiiRemote
{
public:
	WiiRemote(){};
	~WiiRemote(){};
	bool Init(BYTE light);
	void Uninit(void);
	void Update(void);
	void UpdateButtom(void);
	void UpdateState(void);
	void CheckAction(void);

	bool GetKeyPress(int nKey);
	bool GetKeyTrigger(int nKey);
	bool GetKeyRepeat(int nKey);
	bool GetKeyRelease(int nKey);
	D3DXVECTOR2 GetWiiIRPos(void);		// X���W�擾
	D3DXVECTOR3 GetWiiSlope(void);		// wii�����R���X��
	float ShakeLevel(void);				// if (ShakeLevel(void) > 5);

	float GetWiiYaw(void);		// X���W�擾
	float GetWiiPitch(void);		// Y���W�擾
	float GetWiiRoll(void);		// X���W�擾
	char ShakeDirection(void);
	void WiiPlaySquare(speaker_freq, BYTE);
	void WiiPlaySquare(int id);
	void WiiStopSpeaker();
	void VibeLation(bool);

private:
	BYTE m_PressWii[WII_BUTTOM_MAX];		//�}�E�X�{�^���̃g���K�[���
	BYTE m_CurrentWii[WII_BUTTOM_MAX];	//�}�E�X�{�^���̃g���K�[���
	BYTE m_TriggerWii[WII_BUTTOM_MAX];	//�}�E�X�{�^���̃g���K�[���
	BYTE m_ReleaseWii[WII_BUTTOM_MAX];	//�}�E�X�{�^���̃����[�X���
	BYTE m_RepeatWii[WII_BUTTOM_MAX];	// ���s�[�g�L�[����
	int	 m_CountWii[WII_BUTTOM_MAX];	// ���s�[�g�L�[�p�̃J�E���^
	D3DXVECTOR2 m_nowIRpos;				//IR���W
	D3DXVECTOR2 m_currentIRpos;			//1F�OIR���W
	D3DXVECTOR3 m_Accel;					//�����x
	D3DXVECTOR3 m_CurrentAccel;				//�X
	D3DXVECTOR3 m_Roatation;				//�X��
	D3DXVECTOR2 m_YawPitch;				//�X��
	D3DXVECTOR3 m_MotionPlus;
	D3DXVECTOR3 m_MotionRaw;
	wiimote wiicont;
	bool m_bVibe;
	bool m_bSound;
	speaker_freq m_speaker;
	wiimote_sample m_sample;
	BYTE m_Volume;
};
#endif _CWii_H_