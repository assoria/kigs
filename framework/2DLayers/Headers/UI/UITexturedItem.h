#ifndef _UITexturedItem_H_
#define _UITexturedItem_H_

#include "UI/UIDrawableItem.h"
#include "UI/UIShapeDelegate.h"
#include "UIVerticesInfo.h"
#include "SmartPointer.h"
#include "Texture.h"

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

	Texture* GetTexture() { return mTexturePointer.get(); }
	void     SetTexture(Texture* t);

	// manage texture directly added 
	bool	addItem(const CMSP& item, ItemPosition pos = Last DECLARE_DEFAULT_LINK_NAME) override;
	bool	removeItem(const CMSP& item DECLARE_DEFAULT_LINK_NAME) override;

	const v2f& getUVMin() const
	{
		return mUVMin;
	}
	const v2f& getUVMax() const
	{
		return mUVMax;
	}
protected:
	virtual ~UITexturedItem();
	void NotifyUpdate(const unsigned int labelid) override;

	void SetTexUV(UIVerticesInfo * aQI) override;

	int GetTransparencyType() override;
	void PreDraw(TravState* state) override;  // use for texture predraw if needed
	void PostDraw(TravState* state) override; // use for texture postdraw if needed

	SmartPointer<Texture>				mTexturePointer;

	v2f mUVMin{ FLT_MAX, FLT_MAX };
	v2f mUVMax{ FLT_MAX, FLT_MAX };

};

#endif //_UIItem_H_
