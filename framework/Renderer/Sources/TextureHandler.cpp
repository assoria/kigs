

#include "TextureHandler.h"
#include "TextureFileManager.h"
#include "Core.h"




IMPLEMENT_CLASS_INFO(TextureHandler)


TextureHandler::TextureHandler(const kstl::string& name, CLASS_NAME_TREE_ARG) : ParentClassType(name, PASS_CLASS_NAME_TREE_ARG)
{
	// we want TextureHandler to be alert on texture change as soon as possible
	mTextureName.changeNotificationLevel(Owner);
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
		
	}
}

void SpriteSheetData::sortAnimation(CoreItemSP& _FrameVector)
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



bool	SpriteSheetData::Init(const std::string& json, std::string& texturename)
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
			texturename = L_Meta["image"];
		}
		mJSonFilename = json;
		return true;
	}
	return false;
}

//  remove dynamic attributes and disconnect events
void	SpriteSheetData::Destroy(CoreModifiable* toDowngrade)
{
	
}


void	TextureHandler::initFromSpriteSheet(const std::string& jsonfilename)
{
	auto& textureManager = KigsCore::Singleton<TextureFileManager>();
	std::string texturename = textureManager->GetTextureFromSpriteSheetJSON(jsonfilename);

	if (!mTexture.isNil())
	{
		if (mTexture->getValue<std::string>("TextureName") == texturename) // same texture, just returns
		{
			return;
		}
	}

	clearSpritesheetAndAnimationData();

	// if texture was already init in texture manager, just get texture
	if (texturename != "")
	{
		// load texture
		mTexture = textureManager->GetTexture(texturename);
		return;
	}

	// else create the upgrador 
	SpriteSheetData* newspritesheet = (SpriteSheetData*)KigsCore::Instance()->GetUpgradorFactory()->CreateClassInstance("SpriteSheetData");
	if (newspritesheet)
	{
		if (newspritesheet->Init(jsonfilename, texturename))
		{
			mTexture = textureManager->GetTexture(texturename);

			if ((!newspritesheet->isOK()) || mTexture.isNil())
			{
				delete newspritesheet;
				newspritesheet = nullptr;
				return;
			}

			mTexture->Upgrade(newspritesheet);
			mIsSpriteSheet = true;
		}
	}
}

void	TextureHandler::refreshSizeAndUVs()
{
	Point2D s, r;
	mTexture->GetSize(s.x, s.y);
	mTexture->GetRatio(r.x, r.y);
	s /= r;

	kfloat dx = 0.5f / s.x;
	kfloat dy = 0.5f / s.y;

	mUV[0].Set(dx, dy);
	mUV[1].Set(dx, r.y - dy);
	mUV[2].Set(r.x - dx, r.y - dy);
	mUV[3].Set(r.x - dx, dy);

	mTexture->GetSize(mSize.x, mSize.y);
}

void	TextureHandler::setCurrentFrame(const SpriteSheetFrameData* ssf)
{
	mSize.x = ssf->SourceSize_X;
	mSize.y = ssf->SourceSize_Y;

	// TODO
	Point2D s, r;
	mTexture->GetSize(s.x, s.y);
	mTexture->GetRatio(r.x, r.y);
	s /= r;

	kfloat dx = 0.5f / s.x;
	kfloat dy = 0.5f / s.y;

	mUV[0].Set(dx, dy);
	mUV[1].Set(dx, r.y - dy);
	mUV[2].Set(r.x - dx, r.y - dy);
	mUV[3].Set(r.x - dx, dy);
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

	if (mTexture) // init uv min max
	{
		refreshSizeAndUVs();
	}
}

void	TextureHandler::changeTexture()
{
	std::string texname = mTextureName;

	// check texture type
	auto arr = SplitStringByCharacter(mTextureName, ':');
	if (arr.size() > 1) // use a sprite in a spritesheet 
	{
		initFromSpriteSheet(arr[0]);
		SpriteSheetData* currentspritesheet = mTexture->getSpriteSheetData();
		if (currentspritesheet)
		{
			const SpriteSheetFrameData* ssdata=currentspritesheet->getFrame(arr[1]);
			if (ssdata)
			{
				setCurrentFrame(ssdata);
			}
			else // is it an animation ?
			{
				const std::vector<SpriteSheetFrameData*>* ssanim = currentspritesheet->getAnimation(arr[1]);
				if (ssanim)
				{
					Upgrade("AnimationUpgrador");
					setCurrentFrame((*ssanim)[0]);
				}
			}

		}
		return;
	}
	else
	{
		if (texname.find(".json") != std::string::npos) // load a spritesheet
		{
			initFromSpriteSheet(texname);
			Upgrade("AnimationUpgrador");
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
	else
	{
		ParentClassType::NotifyUpdate(labelid);
	}
}

SP<Texture>	TextureHandler::GetEmptyTexture(const std::string& name)
{
	if (mTexture || (name == ""))
	{
		return mTexture;
	}

	mTexture = KigsCore::GetInstanceOf(name, "Texture");
	mTexture->Init();

	return mTexture;
}


// connect to events and create attributes
void	AnimationUpgrador::Init(CoreModifiable* toUpgrade)
{
	// Connect notify update
	KigsCore::Connect(toUpgrade, "NotifyUpdate", toUpgrade, "AnimationNotifyUpdate");

	mCurrentAnimation = (maString*)toUpgrade->AddDynamicAttribute(CoreModifiable::ATTRIBUTE_TYPE::STRING, "CurrentAnimation", "");
	mCurrentAnimation->changeNotificationLevel(Owner);
	mFramePerSecond = (maUInt*)toUpgrade->AddDynamicAttribute(CoreModifiable::ATTRIBUTE_TYPE::UINT, "FramePerSecond", 24);
	mFramePerSecond->changeNotificationLevel(Owner);
	mLoop = (maBool*)toUpgrade->AddDynamicAttribute(CoreModifiable::ATTRIBUTE_TYPE::BOOL, "Loop", false);
	mLoop->changeNotificationLevel(Owner);

	// check if already in auto update mode
	if (toUpgrade->isFlagAsAutoUpdateRegistered())
		mWasdAutoUpdate = true;
	else
		KigsCore::GetCoreApplication()->AddAutoUpdate(toUpgrade);
	
}

//  remove dynamic attributes and disconnect events
void	AnimationUpgrador::Destroy(CoreModifiable* toDowngrade)
{
	KigsCore::Disconnect(toDowngrade, "NotifyUpdate", toDowngrade, "AnimationNotifyUpdate");

	toDowngrade->RemoveDynamicAttribute("CurrentAnimation");
	toDowngrade->RemoveDynamicAttribute("FramePerSecond");
	toDowngrade->RemoveDynamicAttribute("Loop");

	if (!mWasdAutoUpdate)
		KigsCore::GetCoreApplication()->RemoveAutoUpdate(toDowngrade);
}

DEFINE_UPGRADOR_METHOD(AnimationUpgrador, Play)
{
	if (!params.empty())
	{
		u32 labelID;
		params[1]->getValue(labelID);

		/*if (GetUpgrador()->mTarget->getLabelID() == labelID)
		{
			GetUpgrador()->mCurrentTarget = (Node3D*)(CoreModifiable*)(*(maReference*)(GetUpgrador()->mTarget));
		}*/

	}
	return false;
}

void	AnimationUpgrador::NotifyUpdate(const unsigned int  labelid, TextureHandler* parent)
{
	if (labelid == mCurrentAnimation->getLabelID())
	{
		mCurrentFrame = 0;
		mElpasedTime = 0.0;

		SpriteSheetData* currentspritesheet = parent->mTexture->getSpriteSheetData();
		const std::vector<SpriteSheetFrameData*>* ssanim = currentspritesheet->getAnimation(*mCurrentAnimation);
		if(ssanim)
		{
			mFrameNumber = ssanim->size();
			parent->setCurrentFrame((*ssanim)[mCurrentFrame]);
		}
	}
}

DEFINE_UPGRADOR_METHOD(AnimationUpgrador, AnimationNotifyUpdate)
{
	if (!params.empty())
	{
		u32 labelID;
		params[1]->getValue(labelID);
		AnimationUpgrador* currentAnim = static_cast<AnimationUpgrador*>(GetUpgrador());
		currentAnim->NotifyUpdate(labelID,this);
	}
	return false;
}

void	AnimationUpgrador::Update(const Timer& _timer, TextureHandler* parent)
{
	double L_delta = ((Timer&)_timer).GetDt(parent);
	u32 prevCurrentFrame = mCurrentFrame;
	if (mFrameNumber > 0)
	{
		mElpasedTime += L_delta;
		auto animationSpeed = 1.0f / (float)((unsigned int)(*mFramePerSecond));
		if (mElpasedTime >= animationSpeed)
		{
			int L_temp = (int)(mElpasedTime / animationSpeed);
			mCurrentFrame += L_temp;
			if ((bool)(*mLoop))
			{
				mCurrentFrame = mCurrentFrame % mFrameNumber;
			}
			else if (mCurrentFrame >= mFrameNumber)
			{
				mCurrentFrame = mFrameNumber - 1;
			}
			mElpasedTime -= animationSpeed * ((float)(L_temp));
		}
	}
	else
	{
		mElpasedTime = 0;
	}
	if (prevCurrentFrame != mCurrentFrame)
	{
		SpriteSheetData* currentspritesheet = parent->mTexture->getSpriteSheetData();
		const std::vector<SpriteSheetFrameData*>* ssanim = currentspritesheet->getAnimation(*mCurrentAnimation);
		if (ssanim)
		{
			parent->setCurrentFrame((*ssanim)[mCurrentFrame]);
		}
	}
}

DEFINE_UPGRADOR_UPDATE(AnimationUpgrador)
{
	AnimationUpgrador* currentAnim=static_cast<AnimationUpgrador*>(GetUpgrador());
	currentAnim->Update(timer,this);
}
