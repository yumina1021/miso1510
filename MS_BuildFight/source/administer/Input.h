//=============================================================================
//
// MS_BuildFight [CInput.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CINPUT_H_
#define _CINPUT_H_

#include "../common.h"

#define REPEAT_TIME		(20)
enum
{
	COMMAND_SHOT   = 1<<0,
	COMMAND_ATTACK = 1<<1,
	COMMAND_JUMP   = 1<<2,
	COMMAND_OVER   = 1<<3,
	COMMAND_UP     = 1<<4,
	COMMAND_DOWN   = 1<<5,
	COMMAND_RIGHT  = 1<<6,
	COMMAND_LEFT   = 1<<7,
};
struct key2Con
{
	unsigned char key;
	unsigned char command;
};

//=============================================================================
// �N���X�錾
//=============================================================================
class CInput
{
	public:
		CInput(void);
		virtual ~CInput(void);

		virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
		virtual void Uninit(void);
		virtual HRESULT Update(void)=0;

		static LPDIRECTINPUT8	m_pDInput;
		LPDIRECTINPUTDEVICE8	m_pDIDevice;
		unsigned int m_input[60*180];
		int			  m_num;

		unsigned int m_replay[60*180];
		int	ReplayKey;
		static bool m_bReplayFlag;
		static int	m_nReplayCount;
		static int	GetReplayCount(void){return m_nReplayCount;};
		static void SetReplayFlag(bool Change){m_bReplayFlag=Change;};
		void Save(void);
		void Load(void);
		int ReplayKeyTrigger;			// �g���K�[�L�[
		BOOL GetReplayKey(int nKey);
		BOOL GetReplayKeyTrigger(int nKey);
};
//*********************************************************
// �L�[�{�[�h���̓N���X
//*********************************************************
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	HRESULT Init(HINSTANCE hInst, HWND hWnd);
	void Uninit(void);
	HRESULT Update(void);
	void SetInput(int num,unsigned char command){m_input[num]=command;};
	unsigned char GetInput(int num){return m_replay[num];};


	BOOL GetKeyPress(int nKey);
	BOOL GetKeyTrigger(int nKey);
	BOOL GetKeyRelease(int nKey);
	BOOL GetKeyRepeat(int nKey);

private:
	BYTE	m_aKeyState[256];			// �L�[�{�[�h�̏��
	BYTE	m_aKeyTrigger[256];			// �g���K�[�L�[
	BYTE	m_aKeyRelease[256];			// �����[�X�L�[
	BYTE	m_aKeyRepeat[256];			// ���s�[�g�L�[
	int		m_aKeyRepeatCnt[256];		// ���s�[�g�p�J�E���^
};
//*********************************************************
// �}�E�X���̓N���X
//*********************************************************
class CInputMouse : public CInput
{
public:
	CInputMouse();
	~CInputMouse();

	HRESULT Init(HINSTANCE hInst, HWND hWnd);
	void Uninit(void);
	HRESULT Update(void);

	BOOL GetLeftPress(void);
	BOOL GetLeftTrigger(void);
	BOOL GetRightPress(void);
	BOOL GetRightTrigger(void);
	BOOL GetCenterPress(void);
	BOOL GetCenterTrigger(void);
	LONG GetAxisX(void);
	LONG GetAxisY(void);
	LONG GetAxisZ(void);
	POINT *GetPosWorld(void){ return &m_posMouseWorld; }

private:
	DIMOUSESTATE2	m_mouseState;				// �}�E�X�̏�Ԃ��󂯎�郏�[�N
	DIMOUSESTATE2	m_mouseStateTrigger;		// �g���K�[���[�N
	POINT			m_posMouseWorld;			// �}�E�X�̃X�N���[�����W
};

//*********************************************************
// �W���C�p�b�h���̓N���X
//*********************************************************
class CInputJoypad : public CInput
{
public:
	CInputJoypad();
	~CInputJoypad();

	HRESULT Init(HINSTANCE hInst, HWND hWnd);
	void Uninit(void);
	HRESULT Update(void);

	// �L�[�̎��
	typedef enum
	{
		KEY_LEFT = 0,
		KEY_RIGHT,
		KEY_UP,
		KEY_DOWN,
		KEY_JUMP,
		KEY_SHOT,
		KEY_TURN_LEFT,
		KEY_TURN_RIGHT,
		KEY_TURN_UP,
		KEY_TURN_DOWN,
		KEY_START,
		KEY_SELECT,
		KEY_MAX
	}KEY;

	bool GetKeyPress(KEY key);
	bool GetKeyTrigger(KEY key);
	bool GetKeyRelease(KEY key);
	bool GetKeyRepeat(KEY key);

private:
	static BOOL CALLBACK EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef);
	static BOOL CALLBACK EnumAxesCallback(const LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);
	void SetKeyState(void);

	DIJOYSTATE2		m_joypadState;					// �W���C�p�b�h��Ԃ��󂯎�郏�[�N
	bool			m_aKeyState[KEY_MAX];			// �v���X���[�N
	bool			m_aKeyStateTrigger[KEY_MAX];	// �g���K�[���[�N
	bool			m_aKeyStateRelease[KEY_MAX];	// �����[�X���[�N
	bool			m_aKeyStateRepeat[KEY_MAX];		// ���s�[�g���[�N
	int				m_aKeyStateRepeatCnt[KEY_MAX];	// ���s�[�g�J�E���^
};

#endif