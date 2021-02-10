#ifndef _TEXTUREHANDLER_H_
#define _TEXTUREHANDLER_H_

#include "Drawable.h"
#include "TinyImage.h"
#include "TecLibs/2D/BBox2DI.h"


struct SpriteSheetFrameData
{
	int FramePos_X;
	int FramePos_Y;
	int Decal_X;
	int Decal_Y;
	int FrameSize_X;
	int FrameSize_Y;
	int SourceSize_X;
	int SourceSize_Y;
	bool Rotated;
	bool Trimmed;
};

class SpritesheetAnimationHandler : public CoreModifiable
{
public:

	DECLARE_CLASS_INFO(SpritesheetAnimationHandler, CoreModifiable, Renderer)
	SpritesheetAnimationHandler(const kstl::string& name, DECLARE_CLASS_NAME_TREE_ARG);

protected:


	/**
	* \brief	initialize modifiable
	* \fn		virtual	void	InitModifiable();
	*/
	void	InitModifiable() override
	{
		// TODO
	}

protected:
	maBool	mIsLooping = BASE_ATTRIBUTE(IsLooping, false);

};

// ****************************************
// * TextureHandler class
// * --------------------------------------
/**
* \file	TextureHandler.h
* \class	TextureHandler
* \ingroup Renderer
* \brief handle texture drawing. A TextureHandler is used to manipulate a texture or animated texture or sprite in a texture the same way
*
*/
// ****************************************
class TextureHandler : public CoreModifiable
{
public:
	
	DECLARE_CLASS_INFO(TextureHandler, CoreModifiable,Renderer)

	/**
	* \brief	constructor
	* \fn 		TextureHandler(const kstl::string& name,DECLARE_CLASS_NAME_TREE_ARG);
	* \param	name : instance name
	* \param	DECLARE_CLASS_NAME_TREE_ARG : list of arguments
	*/
	TextureHandler(const kstl::string& name,DECLARE_CLASS_NAME_TREE_ARG);

protected:


	/**
	* \brief	initialize modifiable
	* \fn		virtual	void	InitModifiable();
	*/
	void	InitModifiable() override;

	/**
	* \brief	this method is called to notify this that one of its attribute has changed.
	* \fn 		virtual void NotifyUpdate(const unsigned int);
	* \param	int : not used
	*/
	void NotifyUpdate(const unsigned int /* labelid */) override;

	/**
	* \brief	destructor
	* \fn 		~TextureHandler();
	*/
	virtual ~TextureHandler();

	// use mTextureName to load texture
	void	changeTexture();

	SP<Texture>	mTexture = nullptr;

	maString mTextureName = BASE_ATTRIBUTE(TextureName, "");

	v2f mUVMin{ FLT_MAX, FLT_MAX };
	v2f mUVMax{ FLT_MAX, FLT_MAX };

	class 	SpriteSheetData
	{
	public:
		SpriteSheetData(const std::string& json, std::string& texture);
		~SpriteSheetData()
		{
			// nothing to do
		}

		bool	isOK()
		{
			return mAllFrameList.size();
		}

		void sortAnimation(CoreItemSP& _FrameVector);

		// keep track of json filename
		std::string													mJSonFilename;
		
		// list of frame per animation
		std::map<std::string, std::vector<SpriteSheetFrameData*>>		mAnimationList;
		// list of frame per frame name
		std::map<std::string, std::unique_ptr<SpriteSheetFrameData>>	mAllFrameList;
	};

	void	clearSpritesheetAndAnimationData()
	{
		if (mSpriteSheetData)
		{
			delete mSpriteSheetData;
			mSpriteSheetData = nullptr;
		}
		if (mAnimationData)
		{
			mAnimationData = nullptr;
		}
	}

	void	initFromSpriteSheet(const std::string& jsonfilename);
	void	initFromPicture(const std::string& picfilename);
	void	setCurrentFrame(const std::string& framename);

	SpriteSheetData*	mSpriteSheetData = nullptr;
	SP<SpritesheetAnimationHandler>		mAnimationData = nullptr;
};

#endif //_TEXTUREHANDLER_H_
