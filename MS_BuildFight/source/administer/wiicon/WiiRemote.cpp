

#include <math.h>
#include "WiiRemote.h"
#include "../debugproc.h"
#include <MMSystem.h>

#define CONNECT_TRY_NUM 2
#define STATIC_CALIB_NUM 100
#define WAIT_TIME	(20)
#define PAWER_TWEAK	(0.45f)
#define	PLUS_ZERO	(7990.0f)
bool g_IR_connect;
bool g_Connect = false;

D3DXVECTOR3 test(0.f,0.f,0.f);
void on_state_change(wiimote &remote,
	state_change_flags  changed,
	const wiimote_state &new_state)
{
	// we use this callback to set report types etc. to respond to key events
	//  (like the wiimote connecting or extensions (dis)connecting).

	// NOTE: don't access the public state from the 'remote' object here, as it will
	//		  be out-of-date (it's only updated via RefreshState() calls, and these
	//		  are reserved for the main application so it can be sure the values
	//		  stay consistent between calls).  Instead query 'new_state' only.

	// the wiimote just connected
	if (changed & CONNECTED)
	{
		// ask the wiimote to report everything (using the 'non-continous updates'
		//  default mode - updates will be frequent anyway due to the acceleration/IR
		//  values changing):

		// note1: you don't need to set a report type for Balance Boards - the
		//		   library does it automatically.

		// note2: for wiimotes, the report mode that includes the extension data
		//		   unfortunately only reports the 'BASIC' IR info (ie. no dot sizes),
		//		   so let's choose the best mode based on the extension status:
		if (new_state.ExtensionType != wiimote::BALANCE_BOARD)
		{
			if (new_state.bExtension)
				remote.SetReportType(wiimote::IN_BUTTONS_ACCEL_IR_EXT); // no IR dots
			else
				remote.SetReportType(wiimote::IN_BUTTONS_ACCEL_IR);		//    IR dots
		}
	}
	// a MotionPlus was detected
	if (changed & MOTIONPLUS_DETECTED)
	{
		// enable it if there isn't a normal extension plugged into it
		// (MotionPlus devices don't report like normal extensions until
		//  enabled - and then, other extensions attached to it will no longer be
		//  reported (so disable the M+ when you want to access them again).
		if (remote.ExtensionType == wiimote_state::NONE) {
			bool res = remote.EnableMotionPlus();
			_ASSERT(res);
		}
	}
	// an extension is connected to the MotionPlus
	else if (changed & MOTIONPLUS_EXTENSION_CONNECTED)
	{
		// We can't read it if the MotionPlus is currently enabled, so disable it:
		if (remote.MotionPlusEnabled())
			remote.DisableMotionPlus();
	}
	// an extension disconnected from the MotionPlus
	else if (changed & MOTIONPLUS_EXTENSION_DISCONNECTED)
	{
		// enable the MotionPlus data again:
		if (remote.MotionPlusConnected())
			remote.EnableMotionPlus();
	}
	// another extension was just connected:
	else if (changed & EXTENSION_CONNECTED)
	{
#ifdef USE_BEEPS_AND_DELAYS
		Beep(1000, 200);
#endif
		// switch to a report mode that includes the extension data (we will
		//  loose the IR dot sizes)
		// note: there is no need to set report types for a Balance Board.
		if (!remote.IsBalanceBoard())
			remote.SetReportType(wiimote::IN_BUTTONS_ACCEL_IR_EXT);
	}
	// extension was just disconnected:
	else if (changed & EXTENSION_DISCONNECTED)
	{
#ifdef USE_BEEPS_AND_DELAYS
		Beep(200, 300);
#endif
		// use a non-extension report mode (this gives us back the IR dot sizes)
		remote.SetReportType(wiimote::IN_BUTTONS_ACCEL_IR);
	}
}
//=============================================================================
// wiiリモコンの初期化処理
//=============================================================================
bool WiiRemote::Init(BYTE light)
{
	m_nowIRpos = D3DXVECTOR2(0, 0);
	m_currentIRpos = D3DXVECTOR2(0, 0);
	m_Accel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_CurrentAccel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_YawPitch = D3DXVECTOR2(0.0f,0.0f);
	m_MotionPlus = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_MotionRaw = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_Posture = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_PlusSpeed = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_PlusAngle = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_PlusSpeedOld = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_OffsetPosture = D3DXVECTOR3(5,9,18);
	wiicont.ChangedCallback = on_state_change;
	wiicont.CallbackTriggerFlags = (state_change_flags)(CONNECTED | CHANGED_ALL);
	wiicont.Connect();
	wiicont.MotionPlusConnected();
	m_count = 0; 
	g_time = timeGetTime();
	
	if (wiicont.IsConnected())wiicont.SetLEDs(light);
	g_Connect = wiicont.IsConnected();
	m_bVibe = false;
	m_bSound = false;
	m_Postureflag = false;
	m_resetflag = false;
	m_speaker = FREQ_NONE;
	m_Volume = 0x00;
	m_sample.freq = FREQ_NONE;
	m_sample.samples = NULL;
	return wiicont.IsConnected();
}

//=============================================================================
// wiiリモコンの終了処理
//=============================================================================
void WiiRemote::Uninit(void)
{
	wiicont.Disconnect();
}

//=============================================================================
// wiiリモコンの更新処理
//=============================================================================
void WiiRemote::Update(void)
{
	wiicont.RefreshState();
	UpdateButtom();
	UpdateState();
	PostureUpdate();
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
		CDebugProc::Print("赤外線:: X:%f Y:%f\n", m_nowIRpos.x, m_nowIRpos.y);
		CDebugProc::Print("R   P :: Roll:%f Pitch:%f\n", m_YawPitch.x, m_YawPitch.y);
		CDebugProc::Print("傾き  :: X:%f Y:%f Z:%f\n", m_Accel.x, m_Accel.y, m_Accel.z);
		CDebugProc::Print("加速度:: X:%f Y:%f Z:%f\n", m_Roatation.x, m_Roatation.y, m_Roatation.z);
		CDebugProc::Print("PLUS  :: X:%f Y:%f Z:%f\n", m_MotionPlus.x, m_MotionPlus.y, m_MotionPlus.z);
		CDebugProc::Print("RAW   :: X:%f Y:%f Z:%f\n", m_MotionRaw.x, m_MotionRaw.y, m_MotionRaw.z);
		CDebugProc::Print("Plus  :: X:%f Y:%f Z:%f\n", m_PlusAngle.x, m_PlusAngle.y, m_PlusAngle.z);	
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
	m_YawPitch.x = wiicont.Acceleration.Orientation.Roll;
	m_YawPitch.y = wiicont.Acceleration.Orientation.Pitch;
	m_MotionPlus.x = wiicont.MotionPlus.Speed.Yaw;
	m_MotionPlus.y = wiicont.MotionPlus.Speed.Pitch;
	m_MotionPlus.z = wiicont.MotionPlus.Speed.Roll;
	m_MotionRaw.x = wiicont.MotionPlus.Raw.Yaw;
	m_MotionRaw.y = wiicont.MotionPlus.Raw.Pitch;
	m_MotionRaw.z = wiicont.MotionPlus.Raw.Roll;
	m_PlusSpeed.x = wiicont.MotionPlus.Speed.Yaw;
	m_PlusSpeed.y = wiicont.MotionPlus.Speed.Pitch;
	m_PlusSpeed.z = wiicont.MotionPlus.Speed.Roll;
	if (wiicont.IsConnected())
	{
		m_nowIRpos.x = SCREEN_WIDTH - (float)wiicont.IR.Dot[0].X * SCREEN_WIDTH;
		m_nowIRpos.y = SCREEN_WIDTH - (float)wiicont.IR.Dot[0].Y * SCREEN_WIDTH;
	}
}
void WiiRemote::PostureUpdate()
{
	// 静的キャリブレーション
	if (m_Postureflag) {
		m_OffsetPosture += m_MotionPlus;

		m_count++;
		if (m_count >= STATIC_CALIB_NUM) {
			m_OffsetPosture = m_Posture / STATIC_CALIB_NUM;

			m_Posture = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_Postureflag = false;
			m_count = 0;
		}
	}
	// 角速度補正
	m_PlusSpeed -= m_OffsetPosture;
	DWORD frametime = timeGetTime() - g_time;
	g_time = timeGetTime();
	// 角度算出
	if (m_PlusSpeed.x > 10 || m_PlusSpeed.x < - 10) {
		float yaw = (m_PlusSpeed.x + m_PlusSpeedOld.x) * frametime / 2000;
		m_PlusAngle.x += yaw;
		m_PlusSpeedOld.x = m_PlusSpeed.x;
	}
	if (m_PlusSpeed.y > 10 || m_PlusSpeed.y < -10) {
		float pitch = (m_PlusSpeed.y + m_PlusSpeedOld.y) * frametime / 2000;
		m_PlusAngle.y += pitch;
		m_PlusSpeedOld.y = m_PlusSpeed.y;
	}
	if (m_PlusSpeed.z > 10 || m_PlusSpeed.z < -10) {
		float roll = (m_PlusSpeed.z + m_PlusSpeedOld.z) * frametime / 2000;
		m_PlusAngle.z += roll;
		m_PlusSpeedOld.z = m_PlusSpeed.z;
	}
	// 姿勢のリセット
	if (m_resetflag) {
		m_PlusAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_resetflag = false;
	}

	// 角度のオーバーフロー対策
	if (m_PlusAngle.x <= -180)m_PlusAngle.x = 180;
	if (m_PlusAngle.x > 180)m_PlusAngle.x = -180;
	if (m_PlusAngle.y <= -180)m_PlusAngle.y = 180;
	if (m_PlusAngle.y > 180)m_PlusAngle.y = -180;
	if (m_PlusAngle.z <= -180)m_PlusAngle.z = 180;
	if (m_PlusAngle.z > 180)m_PlusAngle.z = -180;
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
	return m_PlusAngle.x;
}
float WiiRemote::GetWiiPitch(void)
{
	return m_PlusAngle.y;
}
float WiiRemote::GetWiiRoll(void)
{
	return m_PlusAngle.z;
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
	float x,y,z;
	x = abs(m_Accel.x);
	y = abs(m_Accel.y);
	z = abs(m_Accel.z);
	return (float)(x + y + z);
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
		if (slope.x - slope2.x > PAWER_TWEAK)work += LEFT_ACTION;
	}
	else if (slope.x < slope2.x)
	{
		if (slope2.x - slope.x > PAWER_TWEAK)work += RIGHT_ACTION;
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