

#include "TextureHandler.h"
#include "TextureFileManager.h"
#include "Core.h"

IMPLEMENT_CLASS_INFO(TextureHandler)
IMPLEMENT_CLASS_INFO(SpritesheetAnimationHandler)

SpritesheetAnimationHandler::SpritesheetAnimationHandler(const kstl::string& name, CLASS_NAME_TREE_ARG) : ParentClassType(name, PASS_CLASS_NAME_TREE_ARG)
{

}

TextureHandler::TextureHandler(const kstl::string& name, CLASS_NAME_TREE_ARG) : ParentClassType(name, PASS_CLASS_NAME_TREE_ARG)
{
	
}

TextureHandler::~TextureHandler()
{
	clearSpritesheetAndAnimationData();
}

void	TextureHandler::InitModifiable()
{
	// avoid double init
	if (_isInit)
	{
		return;
	}
	ParentClassType::InitModifiable();
	if (_isInit)
	{
		if (((std::string)mTextureName) != "")
		{
			changeTexture();
		}
		mTextureName.changeNotificationLevel(Owner);
	}
}

void TextureHandler::SpriteSheetData::sortAnimation(CoreItemSP& _FrameVector)
{
	std::vector<std::string>  str;
	std::string AnimeName;
	std::string CurrentName;

	for (auto it : _FrameVector)
	{
		CoreItemSP L_Frame = it["filename"];
		CurrentName = L_Frame->toString();

		std::vector<std::string>  str = SplitStringByCharacter(CurrentName, '/');

		//create Frame
		auto L_FrameInfo = std::make_unique<SpriteSheetFrameData>();

		{
			CoreItemSP L_map = it["frame"];

			if (L_map->size())
			{
				L_FrameInfo->FramePos_X = L_map["x"];
				L_FrameInfo->FramePos_Y = L_map["y"];

				L_FrameInfo->FrameSize_X = L_map["w"];
				L_FrameInfo->FrameSize_Y = L_map["h"];
			}
		}

		{
			CoreItemSP L_map = it["sourceSize"];

			if (L_map->size())
			{
				L_FrameInfo->SourceSize_X = L_map["w"];
				L_FrameInfo->SourceSize_Y = L_map["h"];
			}
		}

		{
			CoreItemSP L_map = it["spriteSourceSize"];

			if (L_map->size())
			{
				L_FrameInfo->Decal_X = L_map["x"];
				L_FrameInfo->Decal_Y = L_map["y"];
			}
		}

		{
			L_FrameInfo->Rotated = it["rotated"];
		}

		{
			L_FrameInfo->Trimmed = it["trimmed"];
		}

		// add in anim list if needed
		if (str.size() == 2)
		{
			AnimeName = str[0];
			auto& FrameVector = mAnimationList[AnimeName];
			FrameVector.push_back(L_FrameInfo.get());
		}
		mAllFrameList[CurrentName] = std::move(L_FrameInfo);
	}
}

TextureHandler::SpriteSheetData::SpriteSheetData(const std::string& json, std::string& texture)
{
	JSonFileParser L_JsonParser;
	CoreItemSP L_Dictionary = L_JsonParser.Get_JsonDictionary(json);
	if (!L_Dictionary.isNil())
	{
		CoreItemSP	L_vFrames = L_Dictionary["frames"];

		sortAnimation(L_vFrames);

		CoreItemSP L_Meta = L_Dictionary["meta"];

		if (!L_Meta.isNil())
		{
			auto L_Value = L_Meta["image"];
			L_Value->getValue(texture);
		}
		mJSonFilename = json;
	}
}

void	TextureHandler::initFromSpriteSheet(const std::string& jsonfilename)
{
	// check that spritesheet has changed 
	if (mSpriteSheetData)
	{
		if (mSpriteSheetData->mJSonFilename == jsonfilename)
		{
			return;
		}
	}

	clearSpritesheetAndAnimationData();

	std::string	texturename;
	SpriteSheetData* newspritesheet = new SpriteSheetData(jsonfilename,texturename);
	if (!newspritesheet->isOK())
	{
		delete newspritesheet;
		newspritesheet = nullptr;
	}
	
	// load texture
	auto& textureManager = KigsCore::Singleton<TextureFileManager>();
	mTexture = textureManager->GetTexture(texturename);

	if(mTexture.isNil())
	{
		delete newspritesheet;
		newspritesheet = nullptr;
	}

	mSpriteSheetData = newspritesheet;

}

void	TextureHandler::setCurrentFrame(const std::string& framename)
{
	// TODO
}

void	TextureHandler::initFromPicture(const std::string& picfilename)
{

	auto& textureManager = KigsCore::Singleton<TextureFileManager>();
	SP<Texture> loaded=	textureManager->GetTexture(picfilename);

	if (loaded.get() == mTexture.get()) // nothing changed
	{
		return;
	}
	clearSpritesheetAndAnimationData();

	// replace texture
	mTexture = loaded;

}

void	TextureHandler::changeTexture()
{
	std::string texname = mTextureName;

	// check texture type
	auto arr = SplitStringByCharacter(mTextureName, ':');
	if (arr.size() > 1) // use a sprite in a spritesheet
	{
		initFromSpriteSheet(arr[0]);
		setCurrentFrame(arr[1]);
		return;
	}
	else
	{
		if (texname.find(".json") != std::string::npos) // load a spritesheet
		{
			initFromSpriteSheet(texname);
		}
		else
		{
			initFromPicture(texname);
		}
	}
}

void TextureHandler::NotifyUpdate(const unsigned int  labelid)
{
	if (labelid == mTextureName.getID())
	{
		changeTexture();
	}
}
