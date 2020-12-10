#pragma once

#include "CoreModifiable.h"
#include "CoreModifiableAttribute.h"
#include "TecLibs/Tec3D.h"

#include <box2D/b2_shape.h>

// ****************************************
// * Box2DShape class
// * --------------------------------------
/**
* \file	Box2DShape.h
* \class	Box2DShape
* \ingroup  Box2DBind
* \brief	Wrap a box2D shape 
*
*/
// ****************************************

class Box2DShape : public CoreModifiable
{
public:
	DECLARE_CLASS_INFO(Box2DShape, CoreModifiable, Box2DBind)
	DECLARE_CONSTRUCTOR(Box2DShape);
protected:

	virtual ~Box2DShape();

	b2Shape* mShape=nullptr;

};