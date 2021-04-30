// #### 2DLayers Include 
#include "UI/UITexturedItem.h"
// #### Core Include
#include "Core.h"
// #### Renderer Include
#include "ModuleRenderer.h"
#include "Texture.h"


//#//////////////////////////////
//#		UITexturedItem
//#//////////////////////////////
//IMPLEMENT_AND_REGISTER_CLASS_INFO(UITexturedItem, UITexturedItem, 2DLayers);
IMPLEMENT_CLASS_INFO(UITexturedItem)

IMPLEMENT_CONSTRUCTOR(UITexturedItem)
{
	// create empty Textured Item
	mTexturePointer = KigsCore::GetInstanceOf(getName()+"_TextureHandler", "TextureHandler");
	mTexturePointer->Init();
	bool is_bgr = false;
	mTexturePointer->getValue("IsBGR", is_bgr);
	ChangeNodeFlag(Node2D_hasBGRTexture, is_bgr);

	KigsCore::Connect(mTexturePointer.get(), "NotifyUpdate", this , "TextureNotifyUpdate");
}

void UITexturedItem::SetTexUV(UIVerticesInfo * aQI)
{
	
	if (!mTexturePointer.isNil())
	{
		if (mTexturePointer->getTexture().isNil())
		{
			return;
		}
		aQI->Flag |= UIVerticesInfo_Texture;

		if(GetNodeFlag(Node2D_hasBGRTexture))
		{
			aQI->Flag |= UIVerticesInfo_BGRTexture;
		}

		if (mShape)
		{
			return mShape->SetTexUV(this, aQI);
		}
		
		v2f isize;
		mTexturePointer->GetSize(isize.x, isize.y);

		VInfo2D::Data* buf = reinterpret_cast<VInfo2D::Data*>(aQI->Buffer());

		auto slice_size = (v2f)mSliced;
		if (slice_size == v2f(0, 0))
		{
			// triangle strip order
			v2f uvpos = mTexturePointer->getUVforPosInPixels({ 0.f,0.f });
			buf[0].setTexUV(uvpos.x, uvpos.y);
			uvpos = mTexturePointer->getUVforPosInPixels({ 0.f,isize.y});
			buf[1].setTexUV(uvpos.x, uvpos.y);
			uvpos = mTexturePointer->getUVforPosInPixels({ isize.x,isize.y});
			buf[3].setTexUV(uvpos.x, uvpos.y);
			uvpos = mTexturePointer->getUVforPosInPixels({ isize.x,0.0f });
			buf[2].setTexUV(uvpos.x, uvpos.y);
		}
		else
		{
			auto set_quad_uv = [&](v2f*& pts, v2f start_pos, v2f size)
			{
				v2f uvpos = mTexturePointer->getUVforPosInPixels(start_pos);
				pts[0] = uvpos;
				uvpos = mTexturePointer->getUVforPosInPixels({ start_pos.x,start_pos.y + size.y });
				pts[1] = uvpos;
				pts[4] = uvpos;
				uvpos = mTexturePointer->getUVforPosInPixels({ start_pos.x+size.x ,start_pos.y });
				pts[2] = uvpos;
				pts[3] = uvpos;
				uvpos = mTexturePointer->getUVforPosInPixels({ start_pos.x + size.x ,start_pos.y+size.y });
				pts[5] = uvpos;
				
				pts += 6;
			};

			v2f uvs[6 * 9];
			v2f* current_uv = uvs;
			
			// Top Left
			set_quad_uv(current_uv, v2f(0, 0), slice_size);
			// Top
			set_quad_uv(current_uv, v2f(slice_size.x, 0), v2f((isize.x - slice_size.x * 2.0f), slice_size.y));
			// Top Right
			set_quad_uv(current_uv, v2f(isize.x - slice_size.x, 0), slice_size);
			// Left
			set_quad_uv(current_uv, v2f(0, slice_size.y), v2f(slice_size.x, (isize.y - slice_size.y * 2.0f)));
			// Center
			set_quad_uv(current_uv, v2f(slice_size.x, slice_size.y), isize - slice_size * 2.0f);
			// Right
			set_quad_uv(current_uv, v2f(isize.x - slice_size.x, slice_size.y), v2f(slice_size.x, isize.y - slice_size.y * 2.0f));
			// Bottom Left
			set_quad_uv(current_uv, v2f(0, isize.y - slice_size.y), slice_size);
			// Bottom
			set_quad_uv(current_uv, v2f(slice_size.x, isize.y - slice_size.y), v2f(isize.x - slice_size.x * 2.0f, slice_size.y));
			// Bottom Right
			set_quad_uv(current_uv, v2f(isize.x - slice_size.x, isize.y - slice_size.y), slice_size);

			for (int i = 0; i < 6 * 9; ++i)
				buf[i].setTexUV(uvs[i]);

		}
	}
}

UITexturedItem::~UITexturedItem()
{
	if(!mTexturePointer.isNil())
		KigsCore::Disconnect(mTexturePointer.get(), "NotifyUpdate", this, "TextureNotifyUpdate");
	mTexturePointer = NULL;
}

void UITexturedItem::PreDraw(TravState* state)
{
	if (mTexturePointer)
		mTexturePointer->DoPreDraw(state);
}

void UITexturedItem::PostDraw(TravState* state)
{
	if (mTexturePointer)
		mTexturePointer->DoPostDraw(state);
}

int UITexturedItem::GetTransparencyType()
{
	if (mTexturePointer && GetOpacity() == 1.0f)
		return mTexturePointer->GetTransparency();
	else // overall transparency
		return 2;
}

bool UITexturedItem::addItem(const CMSP& item, ItemPosition pos DECLARE_LINK_NAME)
{
	if (item->isSubType(Texture::mClassID))
	{
		mTexturePointer->setTexture((SP<Texture>&)item);

		SetNodeFlag(Node2D_SizeChanged);

		if (mTexturePointer && getAttribute("HasDynamicTexture"))
			mTexturePointer->setValue("IsDynamic", true);
	}

	return UIDrawableItem::addItem(item, pos PASS_LINK_NAME(linkName));
}

bool UITexturedItem::removeItem(const CMSP& item DECLARE_LINK_NAME)
{
	if (item->isSubType(Texture::mClassID))
	{
		if (item.get() == mTexturePointer->getTexture().get())
		{
			mTexturePointer->setTexture(nullptr);
			SetNodeFlag(Node2D_SizeChanged);
		}
	}
	return UIDrawableItem::removeItem(item PASS_LINK_NAME(linkName));
}

void	UITexturedItem::TextureNotifyUpdate(const unsigned int  labelid)
{
	if (labelid == KigsID("TextureName"))
	{
		SetNodeFlag(Node2D_SizeChanged);

		bool is_bgr = false;
		mTexturePointer->getValue("IsBGR", is_bgr);
		
		ChangeNodeFlag(Node2D_hasBGRTexture, is_bgr);
		
	}
}