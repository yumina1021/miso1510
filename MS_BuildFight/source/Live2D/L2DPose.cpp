/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#include "L2DPose.h"

namespace live2d
{
	namespace framework
	{
		L2DPose::L2DPose() :lastModel(NULL),lastTime(0)
		{
		}
		
		
		/*
		 * ���f���̃p�����[�^���X�V�B
		 * @param model
		 */
		void L2DPose::updateParam(ALive2DModel* model)
		{
			// �O��̃��f���Ɠ����ł͂Ȃ��Ƃ��͏��������K�v
			if( model != lastModel )
			{
				//  �p�����[�^�C���f�b�N�X�̏�����
				initParam(model);
			}
			lastModel = model;
			
			l2d_int64  curTime = UtSystem::getTimeMSec();
			float deltaTimeSec = ( (lastTime == 0 ) ? 0 : ( curTime - lastTime )/1000.0f);
			lastTime = curTime;
			
			// �ݒ肩�玞�Ԃ�ύX����ƁA�o�ߎ��Ԃ��}�C�i�X�ɂȂ邱�Ƃ�����̂ŁA�o�ߎ���0�Ƃ��đΉ��B
			if (deltaTimeSec < 0) deltaTimeSec = 0;
			
			int offset=0;
			for (unsigned int i = 0; i < groupRows.size(); i++)
			{
				int rowCount=groupRows[i];
				normalizePartsOpacityGroup(model,deltaTimeSec,offset,rowCount);
				offset+=rowCount;
			}
			copyOpacityOtherParts(model);
		}
		
		
		/*
		 * �\�����������B
		 * ���̏����l��0�łȂ��p�����[�^�́A����1�ɐݒ肷��B
		 * @param model
		 */
		void L2DPose::initParam(ALive2DModel* model)
		{
			int offset=0;
			for (unsigned int i=0; i<groupRows.size(); i++) {
				int rowCount=groupRows[i];
				for (int j = offset; j < offset+rowCount; j++)
				{
					partsGroups[j].initIndex(model);
					int partsIndex = partsGroups[j].partsIndex ;
					int paramIndex = partsGroups[j].paramIndex ;
					
					if(partsIndex<0)continue;
					
					model->setPartsOpacity(partsIndex , (j==offset ? 1.0f : 0.0f) ) ;
					model->setParamFloat(paramIndex , (j==offset ? 1.0f : 0.0f) ) ;
					
					for (unsigned int k = 0; k < partsGroups[j].link.size(); k++)
					{
						partsGroups[j].link[k].initIndex(model);
					}
				}
				offset+=rowCount;
			}
			
		}
		
		
		/*
		 * �p�[�c�̃t�F�[�h�C���A�t�F�[�h�A�E�g��ݒ肷��B
		 * @param model
		 * @param partsGroup
		 * @param deltaTimeSec
		 */
		void L2DPose::normalizePartsOpacityGroup( ALive2DModel* model , float deltaTimeSec ,int offset ,int rowCount)
		{
			int visibleParts = -1 ;
			float visibleOpacity = 1.0f ;
			
			float CLEAR_TIME_SEC = 0.5f ;// ���̎��Ԃŕs�����ɂȂ�
			float phi = 0.5f ;// �w�i���o�ɂ����悤�ɁA�P���O�ւ̕ω���x�点��ꍇ�́A0.5�����傫������B�������A���܂莩�R�ł͂Ȃ�
			float maxBackOpacity = 0.15f ;
			
			
			//  ���݁A�\����ԂɂȂ��Ă���p�[�c���擾
			for (int i = offset ; i < offset + rowCount; i++ )
			{
				int partsIndex = partsGroups[i].partsIndex;
				int paramIndex = partsGroups[i].paramIndex;
				
				if( model->getParamFloat( paramIndex ) != 0 )
				{
					if( visibleParts >= 0 )
					{
						break ;
					}
					
					visibleParts = i ;
					visibleOpacity = model->getPartsOpacity(partsIndex) ;
					
					//  �V����Opacity���v�Z
					visibleOpacity += deltaTimeSec / CLEAR_TIME_SEC ;
					if( visibleOpacity > 1 )
					{
						visibleOpacity = 1 ;
					}
				}
			}
			
			if( visibleParts < 0 )
			{
				visibleParts = 0 ;
				visibleOpacity = 1 ;
			}
			
			//  �\���p�[�c�A��\���p�[�c�̓����x��ݒ肷��
			for (int i = offset ; i < offset + rowCount ; i++ )
			{
				int partsIndex = partsGroups[i].partsIndex;
				
				//  �\���p�[�c�̐ݒ�
				if( visibleParts == i )
				{
					model->setPartsOpacity(partsIndex , visibleOpacity ) ;// ��ɐݒ�
				}
				//  ��\���p�[�c�̐ݒ�
				else
				{
					float opacity = model->getPartsOpacity(partsIndex) ;
					float a1 ;// �v�Z�ɂ���ċ��߂��铧���x
					if( visibleOpacity < phi )
					{
						a1 = visibleOpacity*(phi-1)/phi + 1 ; //  (0,1),(phi,phi)��ʂ钼����
					}
					else
					{
						a1 = (1-visibleOpacity)*phi/(1-phi) ; //  (1,0),(phi,phi)��ʂ钼����
					}
					
					// �w�i�̌����銄���𐧌�����ꍇ
					float backOp = (1-a1)*(1-visibleOpacity) ;
					if( backOp > maxBackOpacity )
					{
						a1 = 1 - maxBackOpacity/( 1- visibleOpacity ) ;
					}
					
					if( opacity > a1 )
					{
						opacity = a1 ;//  �v�Z�̓����x�����傫����΁i�Z����΁j�����x���グ��
					}
					model->setPartsOpacity(partsIndex , opacity ) ;
				}
			}
		}
		
		
		/*
		 * �p�[�c�̃���A������B
		 * @param model
		 * @param partsGroup
		 */
		void L2DPose::copyOpacityOtherParts(ALive2DModel* model)
		{
			for (unsigned int i_group = 0; i_group < partsGroups.size(); i_group++)
			{
				L2DPartsParam &partsParam = partsGroups[i_group];
				
				if(partsParam.link.size()==0)continue;// �����N����p�����[�^�͂Ȃ�
				
				int partsIndex = partsGroups[i_group].partsIndex;
				
				float opacity = model->getPartsOpacity( partsIndex );
				
				for (unsigned int i_link = 0; i_link < partsParam.link.size(); i_link++)
				{
					L2DPartsParam &linkParts = partsParam.link[i_link];
					
					int linkPartsIndex = linkParts.partsIndex;
					
					if(linkPartsIndex < 0)continue;
					model->setPartsOpacity(linkPartsIndex, opacity);
				}
			}
		}
		
		
		/**
		 * JSON�t�@�C������ǂݍ���
		 * �d�l�ɂ��Ă̓}�j���A���Q�ƁBJSON�X�L�[�}�̌`���̎d�l������B
		 * @param buf
		 * @return
		 */
		L2DPose* L2DPose::load(const void* buf ,int size)
		{
			L2DPose* ret = new L2DPose();
			
			Json* json = Json::parseFromBytes( (const char*)buf , size ) ;
			
			Value& root = json->getRoot() ;
			
			// �p�[�c�؂�ւ��ꗗ
			Value& poseListInfo = root["parts_visible"];
			int poseNum = poseListInfo.size();
			
			for (int i_pose = 0; i_pose < poseNum; i_pose++)
			{
				Value& poseInfo = poseListInfo[i_pose];
				
				// ID���X�g�̐ݒ�
				Value& idListInfo = poseInfo["group"];
				int idNum = idListInfo.size();
				int rowCount=0;
				for (int i_group = 0; i_group < idNum; i_group++)
				{
					Value& partsInfo=idListInfo[i_group];
					L2DPartsParam parts;
					LDString paramID=partsInfo["id"].toString();
					parts.partsID=paramID;
					
					// �����N����p�[�c�̐ݒ�
					if(partsInfo["link"].isNull())
					{
						// �����N�������Ƃ�������
					}
					else
					{
						Value &linkListInfo = partsInfo["link"];
						int linkNum = linkListInfo.size();
						
						for (int i_link = 0; i_link< linkNum; i_link++)
						{
							L2DPartsParam linkParts;
							LDString linkID=linkListInfo[i_link].toString();
							linkParts.partsID=linkID;
							parts.link.push_back(linkParts);
						}
					}
					ret->partsGroups.push_back(parts);
					rowCount++;
				}
				ret->groupRows.push_back(rowCount);
				
			}
			
			delete json;
			return ret;
		}
	}
}