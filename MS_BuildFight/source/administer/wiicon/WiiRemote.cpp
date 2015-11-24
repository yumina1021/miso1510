

#include <math.h>
#include "WiiRemote.h"
#include "../debugproc.h"
#include <time.h>

#define WAIT_TIME	(20)
#define PAWER_TWEAK	(0.0f)
#define	PLUS_ZERO	(7990.0f)
bool g_IR_connect;
bool g_Connect = false;
clock_t timer1, timer2;


void on_state_change(wiimote &remote,
	state_change_flags  changed,
	const wiimote_state &new_state)
{
	if (changed & CONNECTED)
	{
		remote.SetReportType(wiimote::IN_BUTTONS_ACCEL);
	}
	if (changed & CHANGED_ALL)
	{
		remote.RefreshState();
	}
}
//=============================================================================
// wiiリモコンの初期化処理
//=============================================================================
bool WiiRemote::Init(BYTE light)
{
	bool tf;
	m_nowIRpos = D3DXVECTOR2(0, 0);
	m_currentIRpos = D3DXVECTOR2(0, 0);
	m_Accel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_CurrentAccel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	wiicont.ChangedCallback = on_state_change;
	wiicont.CallbackTriggerFlags = (state_change_flags)(CONNECTED | CHANGED_ALL);

	tf = wiicont.Connect();
	if (tf)wiicont.SetLEDs(light);
	timer1 = clock();
	g_Connect = tf;
	m_bVibe = false;
	m_bSound = false;
	m_speaker = FREQ_NONE;
	m_Volume = 0x00;
	m_sample.freq = FREQ_NONE;
	m_sample.samples = NULL;
	return tf;
}

//=============================================================================
// wiiリモコンの終了処理
//=============================================================================
void WiiRemote::Uninit(void)
{
}

//=============================================================================
// wiiリモコンの更新処理
//=============================================================================
void WiiRemote::Update(void)
{
	wiicont.RefreshState();
	UpdateButtom();
	UpdateState();
	// 各入力系更新
	for (int cnt = 0; cnt<WII_BUTTOM_MAX; cnt++)
	{
		m_TriggerWii[cnt] = (m_PressWii[cnt]^m_CurrentWii[cnt])&~m_CurrentWii[cnt];
		m_ReleaseWii[cnt] = (m_PressWii[cnt]^m_CurrentWii[cnt])&m_CurrentWii[cnt];

		// リピートキー判定
		if( m_CountWii[cnt] == 0 )
		{
			m_RepeatWii[cnt] = m_TriggerWii[cnt];
		}
		else if( m_CountWii[cnt] % WAIT_TIME == 0 )
		{
			m_RepeatWii[cnt] = m_PressWii[cnt];
		}
		m_CurrentWii[cnt] = m_PressWii[cnt];
	}
#ifdef _DEBUG
	CDebugProc::Print("赤外線	::	X:%f Y:%f\n", m_nowIRpos.x, m_nowIRpos.y);
	CDebugProc::Print("傾き		::	X:%f Y:%f Z:%f\n", m_Accel.x, m_Accel.y, m_Accel.z);
	CDebugProc::Print("加速度	::	X:%f Y:%f Z:%f\n", m_Roatation.x, m_Roatation.y, m_Roatation.z);
#endif
}
//=============================================================================
// 各ステートの更新
//=============================================================================
void WiiRemote::UpdateState(void)
{
	m_CurrentAccel = m_Accel;
	m_currentIRpos = m_nowIRpos;
	//m_Plus = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Accel.x = wiicont.Acceleration.X;
	m_Accel.y = wiicont.Acceleration.Y;
	m_Accel.z = wiicont.Acceleration.Z;
	m_Roatation.x = wiicont.Acceleration.Orientation.X;
	m_Roatation.y = wiicont.Acceleration.Orientation.Y;
	m_Roatation.z = wiicont.Acceleration.Orientation.Z;
	if (wiicont.IsConnected())
	{
		m_nowIRpos.x = SCREEN_WIDTH - (float)wiicont.IR.Dot[0].X * SCREEN_WIDTH;
		m_nowIRpos.y = SCREEN_WIDTH - (float)wiicont.IR.Dot[0].Y * SCREEN_WIDTH;
	}
}
//=============================================================================
// wiiリモコンのIR_X座標取得
//=============================================================================
void WiiRemote::CheckAction(void)
{
	wiicont.SetRumble(m_bVibe);
	if (m_bSound)wiicont.PlaySquareWave(FREQ_3130HZ, 0x20);
	if (!m_bSound)wiicont.EnableSpeaker(false);
}
//=============================================================================
// wiiリモコンのIR_X座標取得
//=============================================================================
D3DXVECTOR2 WiiRemote::GetWiiIRPos(void)
{
	return m_nowIRpos;
}
//=============================================================================
// wiiリモコンのプレス取得
//=============================================================================
bool WiiRemote::GetKeyPress(int nKey)
{
	if (!g_Connect) return false;
	return m_PressWii[nKey] ? true:false;
}
//=============================================================================
// wiiリモコンのトリガー取得
//=============================================================================
bool WiiRemote::GetKeyTrigger(int nKey)
{
	if (!g_Connect) return false;
	return m_TriggerWii[nKey] ? true:false;
}
//=============================================================================
// wiiリモコンのリリース取得
//=============================================================================
bool WiiRemote::GetKeyRelease(int nKey)
{
	if (!g_Connect) return false;
	return m_ReleaseWii[nKey] ? true:false;
}
//=============================================================================
// wiiリモコンのリリース取得
//=============================================================================
bool WiiRemote::GetKeyRepeat(int nKey)
{
	if (!g_Connect) return false;
	return m_RepeatWii[nKey] ? true:false;
}
float WiiRemote::GetWiiYaw(void)
{
	return 0.0f;
	if (!g_Connect) return 0.0f;
	//return wiicont.MotionPlus.Raw.Yaw;
}
float WiiRemote::GetWiiPitch(void)
{
	return 0.0f;
	if (!g_Connect) return 0.0f;
	//return wiicont.MotionPlus.Raw.Pitch;
}
float WiiRemote::GetWiiRoll(void)
{
	return 0.0f;
	if (!g_Connect) return 0.0f;
	//return wiicont.MotionPlus.Raw.Roll;
}
//=============================================================================
// wiiリモコンの傾き　兼　加速度
//=============================================================================
D3DXVECTOR3 WiiRemote::GetWiiSlope(void)
{
	if (!g_Connect) return D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 slope = D3DXVECTOR2(0.0f,0.0f);
	slope.x = m_Roatation.x;
	slope.y = m_Roatation.y;
	slope.z = m_Roatation.z;
	return slope;
}
//=============================================================================
// wiiリモコンの振ったかどうか
//=============================================================================
float WiiRemote::ShakeLevel(void)
{
	if (!g_Connect) return 0.0f;
	int x,y,z;
	x = abs(m_Accel.x);
	y = abs(m_Accel.y);
	z = abs(m_Accel.z);
	return (x + y + z);
}
//=============================================================================
// wiiリモコンボタン更新
//=============================================================================
void WiiRemote::UpdateButtom(void)
{
	m_PressWii[0] = wiicont.Button.A();
	m_PressWii[1] = wiicont.Button.B();
	m_PressWii[2] = wiicont.Button.One();
	m_PressWii[3] = wiicont.Button.Two();
	m_PressWii[4] = wiicont.Button.Plus();
	m_PressWii[5] = wiicont.Button.Minus();
	m_PressWii[6] = wiicont.Button.Up();
	m_PressWii[7] = wiicont.Button.Down();
	m_PressWii[8] = wiicont.Button.Right();
	m_PressWii[9] = wiicont.Button.Left();
}
//=============================================================================
// wiiリモコンブィイィイイイイイイイイイイイイイイイイイイイン
//=============================================================================
void WiiRemote::VibeLation(bool onoff)
{
	if (!g_Connect) return;
	m_bVibe = onoff;
}
//=============================================================================
// 振った方向を出力（縦）
//=============================================================================
char WiiRemote::ShakeDirection(void)
{
	if (!g_Connect) return 0;
	D3DXVECTOR3 slope = m_Accel;
	D3DXVECTOR3 slope2 = m_CurrentAccel;
	char work = 0x00;
	if (slope.z > slope2.z)
	{
		if (slope.z - slope2.z > PAWER_TWEAK)work += DOWN_ACTION;
	}
	else if (slope.z < slope2.z)
	{
		if (slope2.z - slope.z > PAWER_TWEAK)work += UP_ACTION;
	}

	if (slope.y > slope2.y)
	{
		if (slope.y - slope2.y > PAWER_TWEAK)work += BACK_ACTION;
	}
	else if (slope.y < slope2.y)
	{
		if (slope2.y - slope.y > PAWER_TWEAK)work += FRONT_ACTION;
	}

	if (slope.x > slope2.x)
	{
		if (slope.x - slope2.x > PAWER_TWEAK)work += RIGHT_ACTION;
	}
	else if (slope.x < slope2.x)
	{
		if (slope2.x - slope.x > PAWER_TWEAK)work += LEFT_ACTION;
	}
	return work;
}
void WiiRemote::WiiStopSpeaker()
{
	m_bSound = false;
	m_speaker = FREQ_NONE;
	m_Volume = 0x00;
}
void WiiRemote::WiiPlaySquare(speaker_freq freq, BYTE volume)
{
	m_bSound = true;
	m_speaker = freq;
	m_Volume = volume;
}
void WiiRemote::WiiPlaySquare(int id)
{

}
// EOF