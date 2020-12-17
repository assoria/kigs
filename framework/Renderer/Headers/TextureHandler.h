#ifndef _TEXTUREHANDLER_H_
#define _TEXTUREHANDLER_H_

#include "Drawable.h"
#include "TinyImage.h"
#include "TecLibs/2D/BBox2DI.h"

// ****************************************
// * TextureHandler class
// * --------------------------------------
/**
* \file	TextureHandler.h
* \class	TextureHandler
* \ingroup Renderer
* \brief handle texture drawing. A TextureHandler is used to manipulate a texture or animated texture the same way
*
*/
// ****************************************
class TextureHandler : public Drawable
{
public:
	
	DECLARE_ABSTRACT_CLASS_INFO(TextureHandler,Drawable,Renderer)

	/**
	* \brief	constructor
	* \fn 		TextureHandler(const kstl::string& name,DECLARE_CLASS_NAME_TREE_ARG);
	* \param	name : instance name
	* \param	DECLARE_CLASS_NAME_TREE_ARG : list of arguments
	*/
	TextureHandler(const kstl::string& name,DECLARE_CLASS_NAME_TREE_ARG);

	unsigned int	GetSelfDrawingNeeds() override
	{
		return ((unsigned int)Need_Predraw)|((unsigned int)Need_Postdraw);
	}

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


};

#endif //_TEXTUREHANDLER_H_
