

#include "TextureHandler.h"
#include "TextureFileManager.h"
#include "Core.h"

IMPLEMENT_CLASS_INFO(TextureHandler)

TextureHandler::TextureHandler(const kstl::string& name, CLASS_NAME_TREE_ARG) : Drawable(name, PASS_CLASS_NAME_TREE_ARG)
{
	
}

TextureHandler::~TextureHandler()
{
}

void	TextureHandler::InitModifiable()
{
	// avoid double init
	if (_isInit)
	{
		return;
	}
	Drawable::InitModifiable();
	if (_isInit)
	{
		if (((std::string)mTextureName) != "")
		{
			changeTexture();
		}
		mTextureName.changeNotificationLevel(Owner);
	}
}

void	TextureHandler::changeTexture()
{
	auto& textureManager = KigsCore::Singleton<TextureFileManager>();
	mTexture = textureManager->GetTexture(mTextureName);
}

void TextureHandler::NotifyUpdate(const unsigned int  labelid)
{
	if (labelid == mTextureName.getID())
	{
		changeTexture();
	}
}