//=============================================================================
//
// MS_BuildFight [CManager.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CMANAGER_H_
#define _CMANAGER_H_
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <windows.h>
#include "../common.h"


#define SCENE_MAX	(10)


typedef enum			//�t�F�[�Y�̎��
{
	PHASETYPE_TITLE =0,
	PHASETYPE_TUTRIAL,
	PHASETYPE_SELECT,
	PHASETYPE_STAGE_SELECT,
	PHASETYPE_LOAD,
	PHASETYPE_GAME,
	PHASETYPE_RESULT,
	PHASETYPE_CLEAR,
	PHASETYPE_GAMEOVER,
	PHASETYPE_VSEND,
	PHASETYPE_MAX
}PHASETYPE;

struct RenderTagets		//�����_�[�^�[�Q�b�g
{
	LPDIRECT3DTEXTURE9		texture;		//�e�N�X�`���p�|�C���^
	LPDIRECT3DSURFACE9		surface;		//�J���[�o�b�t�@�p�T�[�t�F�X
	LPDIRECT3DSURFACE9		surfaceDepth;	//�y�o�b�t�@�p�T�[�t�F�X
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
};
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CInputKeyboard;	//�O���錾
class CInputMouse;
class CInputJoypad;
class CSound;
class CScene;
class CCamera;
class CGame;
class Cform;
class CLight;

#ifdef _DEBUG
class CDebugProc;
#endif

class CManager
{
	public:
		CManager(void);					//�R���X�g���N�^
		~CManager(void);				//�f�X�g���N�^

		HRESULT Init(HINSTANCE hInstance,HWND hWnd,BOOL bWindow);	//������
		void Uninit(void);						//�I��
		void Update(void);						//�X�V
		void Draw(void);						//�`��

		void Addform(Cform* pform);				//�V�[���̓o�^�p

		static void SetAfterScene(PHASETYPE phase){m_afterSceneType=phase;};	//���̃t�F�[�Y�󂯎��

		static CInputKeyboard* GetInputKeyboard(void){ return m_pKeyboard; };
		static CInputMouse* GetInputMouse(void){ return m_pMouse; };
		static CInputJoypad* GetInputJoypad(void){ return m_pJoypad; };
		static CSound *GetSound(void){ return m_pSound; };
		static CScene *GetScene(void){ return m_pScene; };
		static CCamera* GetCamera(void){ return m_pCamera; };
		static CLight *GetLight(void){ return m_pLight; }

		static LPDIRECT3DDEVICE9 GetDevice(void){ return m_pD3DDevice; };	//�f�o�C�X�̎擾
		void SetDevice(LPDIRECT3DDEVICE9 device){ m_pD3DDevice = device; };	//�f�o�C�X�̎擾

		static PHASETYPE GetSceneType(void){ return m_phaseType; };
		static PHASETYPE GetAfetrSceneType(void){ return m_afterSceneType; };

		static void SetpauseFlag(bool pause){m_pauseFlag =pause;};
		static bool GetpauseFlag(void){return m_pauseFlag;};

		static void SetgameEndFlag(bool pause){m_gameEndFlag =pause;};
		static bool GetgameEndFlag(void){return m_gameEndFlag;};

		static void Setnight0PlayFlag(bool pause){m_night0PlayFlag =pause;};
		static bool Getnight0PlayFlag(void){return m_night0PlayFlag;};

		static void SetSetWndHandle(HWND paramWnd){ m_hwnd = paramWnd; };
		static HWND GetSetWndHandle(void){ return m_hwnd; };

		int SetRenderTargets(float width, float height);
		void RemoveRenderTargets(int i);
		RenderTagets* GetRenderTargets(int i){ return m_renderTargets[i]; };

	private:
		void RenderTargetDraw(void);
		HRESULT RenderInit(HWND hWnd, BOOL bWindow);
		
		HRESULT SetShader(void);

		void ChangeScene(void);						//�t�F�[�Y�̕ύX

		LPDIRECT3D9					m_pD3D;					// Direct3D�I�u�W�F�N�g
		static LPDIRECT3DDEVICE9	m_pD3DDevice;			// pDevice�I�u�W�F�N�g(�`��ɕK�v)

		Cform*					m_apforms[SCENE_MAX];	//�V�[���o�^�p�|�C���^
		int						m_nCountform;			//�o�^��
		bool					m_bWirerFlag;			//���C���[�t���[���\���t���O

		static CInputKeyboard*	m_pKeyboard;		//�L�[�{�[�h�ւ̃|�C���^
		static CInputMouse*		m_pMouse;			//�}�E�X�ւ̃|�C���^
		static CInputJoypad*	m_pJoypad;			//�W���C�p�b�h�ւ̃|�C���^
		static CSound*			m_pSound;			//�T�E���h�̃|�C���^�[
		static CScene*			m_pScene;			//�t�F�[�Y�̃|�C���^�[
		static CScene*			m_pSceneT;			//�t�F�[�Y�̃|�C���^�[
		static CCamera*			m_pCamera;				//�J�����̃|�C���^
		static CLight*			m_pLight;			// ���C�g�ւ̃|�C���^

		static PHASETYPE		m_phaseType;		//���݂̃t�F�[�Y�^�C�v
		static PHASETYPE		m_afterSceneType;	//���̃t�F�[�Y�^�C�v
		static HWND				m_hwnd;

#ifdef _DEBUG
		static  CDebugProc *m_pDebugProc;			//�f�o�b�O�����ւ̃|�C���^
#endif

		static bool				m_pauseFlag;		//�|�[�Y�����Ă��邩�̃t���O
		static bool				m_gameEndFlag;		//�Q�[���I�������̃t���O
		static bool				m_night0PlayFlag;	//�i�C�g�O�Ɛ�������ǂ����H

		RenderTagets*			m_renderTargets[5];

		LPDIRECT3DSURFACE9		m_pSurfaceBack;	//�o�b�N�o�b�t�@�p�T�[�t�F�X
		LPDIRECT3DSURFACE9		m_pSurfaceBackD;//�o�b�N�o�b�t�@�p�T�[�t�F�X

		D3DVIEWPORT9			m_pViewport;	//�r���[�|�[�g�ۑ��p

		LPDIRECT3DPIXELSHADER9 _ps[3];			//�s�N�Z���V�F�[�_�[
		LPD3DXCONSTANTTABLE    _psc[3];		//�s�N�Z���V�F�[�_�[�p�R���X�^���g�e�[�u��

};

#endif

/////////////EOF////////////