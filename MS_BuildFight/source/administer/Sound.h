//=============================================================================
//
// MS_BuildFight [Sound.h]
// 15/08/20
// Author : YOSHIKI ITOU
//
//=============================================================================
#ifndef _CSOUND_H_
#define _CSOUND_H_
//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "../common.h"
#include "xaudio2.h"
//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM2
	SOUND_LABEL_BGM002,			// BGM1
	SOUND_LABEL_BGM003,			// BGM2
	SOUND_LABEL_BGM_EXTRA,		// �G�N�X�g��BGM
	SOUND_LABEL_SE_SELECT000,	// �J�[�\����
	SOUND_LABEL_SE_SELECT001,	// ���艹
	SOUND_LABEL_SE_ORGAN,		// �I���K��
	SOUND_LABEL_SE_SENI,		// �V�[���J�ډ�
	SOUND_LABEL_SE_SHINE,		// �V����������
	SOUND_LABEL_SE_TRUMPET,		// �g�����y�b�g
	SOUND_LABEL_SE_SHOT,		// �V���b�g��
	SOUND_LABEL_SE_SELECT002,	// �I�������
	SOUND_LABEL_MAX
} SOUND_LABEL;

typedef enum
{
	VOICE_LABEL_SE_WIN=0,		// 
	VOICE_LABEL_MAX
} VOICE_LABEL;

#define CHARACTER_MAX (4)
//*****************************************************************************
// �p�����[�^�\���̒�`
//*****************************************************************************
typedef struct
{
	char *pFilename;	// �t�@�C����
	bool bLoop;			// ���[�v���邩�ǂ���
} PARAM;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSound
{
	public:
		CSound(void);				//�R���X�g���N�^
		~CSound(void);				//�f�X�g���N�^

		HRESULT Init(HWND hWnd);				//������
		void Uninit(void);						//�I��

		HRESULT Play(SOUND_LABEL label);		//�X�V
		HRESULT PlayVoice(int nType,VOICE_LABEL label);	//�X�V

		void Stop(void);						//�`��
		void Stop(SOUND_LABEL label);
		void StopVoice(int nType,VOICE_LABEL label);

#ifdef _DEBUG
		void Setm_nCountFPS(int set);
#endif

	private:
		HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
		HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

		LPDIRECT3D9				m_pD3D;								// Direct3D�I�u�W�F�N�g
		LPDIRECT3DDEVICE9		m_pD3DDevice;						// pDevice�I�u�W�F�N�g(�`��ɕK�v)	
		IXAudio2				*g_pXAudio2;						// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
		IXAudio2MasteringVoice	*g_pMasteringVoice;					// �}�X�^�[�{�C�X

		IXAudio2SourceVoice		*g_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
		BYTE					*g_apDataAudio[SOUND_LABEL_MAX];	// �I�[�f�B�I�f�[�^
		DWORD					g_aSizeAudio[SOUND_LABEL_MAX];

		IXAudio2SourceVoice		*g_apSourceVoice2[VOICE_LABEL_MAX*CHARACTER_MAX];	// �\�[�X�{�C�X
		BYTE					*g_apDataAudio2[VOICE_LABEL_MAX*CHARACTER_MAX];	// �I�[�f�B�I�f�[�^
		DWORD					g_aSizeAudio2[VOICE_LABEL_MAX*CHARACTER_MAX];
};

#endif

/////////////EOF////////////