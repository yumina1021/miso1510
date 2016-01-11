/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#pragma once

#include <stdlib.h>
#include <math.h>
#include <string>
//Live2D lib
#include "include\ALive2DModel.h"
#include "include\util/UtSystem.h"

namespace live2d
{
	namespace framework
	{
		class L2DEyeBlink
		{
		public:
			// ��̏�Ԓ萔
			enum EYE_STATE{
				STATE_FIRST = 0 ,
				STATE_INTERVAL ,
				STATE_CLOSING ,// ���Ă����r��
				STATE_CLOSED , // ���Ă�����
				STATE_OPENING// �J���Ă����r��
			};
			
			L2DEyeBlink();
			virtual ~L2DEyeBlink(){}
			
			l2d_int64 calcNextBlink() ;
			void setInterval( int blinkIntervalMsec) ;
			void setEyeMotion( int closingMotionMsec , int closedMotionMsec , int openingMotionMsec ) ;
			
			// ���f���̃p�����[�^���X�V
			void setParam( live2d::ALive2DModel *model ) ;
			
		private:
			l2d_int64 nextBlinkTime ;// �����p�`���鎞���imsec�j
			int eyeState ;// ���݂̏��
			l2d_int64 stateStartTime ;// ���݂�state���J�n��������
			bool closeIfZero;// ID�Ŏw�肳�ꂽ��̃p�����[�^���A0�̂Ƃ��ɕ���Ȃ� true �A1�̎��ɕ���Ȃ� false
			
			// ���E�̖ڂ̃p�����[�^
			std::string eyeID_L ;
			std::string eyeID_R ;
			
			// �ݒ�
			int blinkIntervalMsec ;// �u���̊Ԋu
			int closingMotionMsec ;// �Ⴊ����܂ł̎���
			int closedMotionMsec  ;// �����܂܂ł��鎞��
			int openingMotionMsec ;// �Ⴊ�J���܂ł̎���
		};
	}
}