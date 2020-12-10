#ifndef _BOX2DBINDMODULE_H_
#define _BOX2DBINDMODULE_H_

#include "ModuleBase.h"
#include "AttributePacking.h"

#include "box2d/b2_world.h"


// ****************************************
// * Box2DBindModule class
// * --------------------------------------
/**
 * \file	Box2DBindModule.h
 * \class	Box2DBindModule
 * \ingroup Module
 * \brief	Generic module for Box2D integration.
 */
 // ****************************************

class Box2DBindModule : public ModuleBase
{
public:
	DECLARE_CLASS_INFO(Box2DBindModule, ModuleBase, Box2DBind)
	DECLARE_CONSTRUCTOR(Box2DBindModule);
    
	//! module init
    void Init(KigsCore* core, const kstl::vector<CoreModifiableAttribute*>* params) override;
	
	//! module close
    void Close() override;
	
	
protected:

	void NotifyUpdate(const unsigned int labelID) override;
	
	void Update(const Timer& timer, void* addParam) override
	{
		// nothing to do
	}

	maVect2DF	mGravity = BASE_ATTRIBUTE(Gravity, 0.0f, -10.0f);

	b2World		mWorld;
}; 



#endif //_BOX2DBINDMODULE_H_
