#ifndef _UITexturedItem_H_
#define _UITexturedItem_H_

#include "UI/UIDrawableItem.h"
#include "UI/UIShapeDelegate.h"
#include "UIVerticesInfo.h"
#include "SmartPointer.h"
#include "TextureHandler.h"

// ****************************************
// * UITexturedItem class
// * --------------------------------------
/**
* \file	UITexturedItem.h
* \class	UITexturedItem
* \ingroup 2DLayers
* \brief	Textured UIDrawableItem
*
*/
// ****************************************

class UITexturedItem : public UIDrawableItem
{
public:
	DECLARE_CLASS_INFO(UITexturedItem, UIDrawableItem, 2DLayers);

	/**
	* \brief	constructor
	* \param	name : instance name
	* \param	DECLARE_CLASS_NAME_TREE_ARG : list of arguments
	*/
	UITexturedItem(const kstl::string& name, DECLARE_CLASS_NAME_TREE_ARG);

	// TODO check if needed
	/*SP<TextureHandler> GetTexture() { return mTexturePointer; }
	void     SetTexture(const SP<TextureHandler>& t);*/

	// manage texture directly added 
	bool	addItem(const CMSP& item, ItemPosition pos = Last DECLARE_DEFAULT_LINK_NAME) override;
	bool	removeItem(const CMSP& item DECLARE_DEFAULT_LINK_NAME) override;

	const v2f* getUVs() const
	{
		if (mTexturePointer.isNil())
		{
			return &mInvalidUV;
		}
		return mTexturePointer->getUVs();
	}
	
protected:
	virtual ~UITexturedItem();
	void NotifyUpdate(const unsigned int labelid) override;

	void SetTexUV(UIVerticesInfo * aQI) override;

	int GetTransparencyType() override;
	void PreDraw(TravState* state) override;  // use for texture predraw if needed
	void PostDraw(TravState* state) override; // use for texture postdraw if needed

	INSERT_FORWARDSP(TextureHandler,mTexturePointer);

	static const v2f mInvalidUV;

};

#endif //_UIItem_H_
