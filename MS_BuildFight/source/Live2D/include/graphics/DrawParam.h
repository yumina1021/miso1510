/**
 * DrawParam.h
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */
#ifndef __LIVE2D_DRAWPARAM_H__
#define __LIVE2D_DRAWPARAM_H__


#include "../Live2D.h"
#include "../memory/LDObject.h"
#include "../type/LDVector.h"

#include "../id/DrawDataID.h"

//------------ LIVE2D NAMESPACE ------------
namespace live2d
{ 


	class TextureInfo :public LDObject{
	public:
		TextureInfo();
		float a;
		float r;
		float g;
		float b;

		float scale;
		float interpolate;

		int blendMode;
	};

	
	class DrawParam  : public live2d::LDObject 
	{
	public:
		static const int DEFAULT_FIXED_TEXTURE_COUNT = 32 ;
		
	public:
		DrawParam();
		virtual ~DrawParam();
	
	public:
		//  æç»ã®ã»ã?ã¢ã??ãå¿?¦ã«å¿ãã¦ãªã¼ãã?ã©ã¤ãããã?
		virtual void setupDraw(){} ;
	
	
        
		virtual void drawTexture( int textureNo , int indexCount , int vertexCount , l2d_index * indexArray
				 , l2d_pointf * vertexArray , l2d_uvmapf * uvArray , float opacity, int colorCompositionType ) = 0 ;
	
	
		// æ°ããå©ç¨ã§ããModelã®ã?¯ã¹ãã£çªå·ãç¢ºä¿?
		virtual int generateModelTextureNo() ;
		
		// Modelã®ã?¯ã¹ãã£çªå·ãçæ?
		virtual void releaseModelTextureNo(int no) ;
	
		// ã¢ã?«æç»ã®éã?å¨ä½ã«æãåããããè²è¨­å®ã?å?²0..1 (1ãæ¨æºã?ç¶æï¼?
		virtual void setBaseColor( float alpha , float red , float green , float blue ) ;
	
		// ã«ãªã³ã°?çé¢æç»?ãè¡ãå ´åã?trueãã»ã?ããã?
		void setCulling( bool culling ){ this->culling = culling ; }
	
		//  éå?ã¯è¤?£½ãããã?ã§å??éå?ã¯å¤ã§ç ´æ£?ã¦è¯ã?
	    void setMatrix( float* _matrix4x4 )
	    {
	        for( int i = 0 ; i < 16 ; i++ )
			{
				matrix4x4[i] = _matrix4x4[i] ;
			}
	    }

		void setPremultipliedAlpha(bool enable);
		bool isPremultipliedAlpha();

		void setAnisotropy(int n);
		int getAnisotropy();

		void setTextureColor(int textureNo, float r, float g, float b, float a=1);
		void setTextureScale(int textureNo, float scale);
		void setTextureInterpolate(int textureNo, float interpolate);
		void setTextureBlendMode(int textureNo, int mode);

		bool enabledTextureInfo(int textureNo);

		void setpCurrentDrawDataID(DrawDataID* pDrawDataID);
		DrawDataID* getpCurrentDrawDataID();

	protected:
		int 	fixedTexureCount ;
		
		float 	baseAlpha ;
		float 	baseRed ;
		float 	baseGreen ;
		float 	baseBlue ;
	
		bool	culling	;
		float 	matrix4x4[16] ;
		
		bool 	premultipliedAlpha;
		int 	anisotropy;


		LDVector<TextureInfo*> 		texturesInfo;

		DrawDataID*     pCurrentDrawDataID;//D3Dç¨ã«ç¾å¨ã®æç»ãªãã¸ã§ã¯ãã?ã¤ã³ã?ã¯ã¹ãæ¸¡ãå¿?¦ãããã®ã§ãè¿½å??ä»ã?ã©ã?ãã©ã¼ã?§ã¯ä½¿ç¨ããã?

	private:
		//Prevention of copy Constructor
		DrawParam( const DrawParam & ) ;			
		DrawParam& operator=( const DrawParam & ) ;
	};
}
//------------ LIVE2D NAMESPACE ------------

#endif		// __LIVE2D_DRAWPARAM_H__

