#pragma once
#include "CoreModifiable.h"
#include "CoreModifiableAttribute.h"
#include "TecLibs/Tec3D.h"

#include <box2D/b2_body.h>

// ****************************************
// * Box2DBody class
// * --------------------------------------
/**
* \file	Box2DBody.h
* \class	Box2DBody
* \ingroup  Box2DBind
* \brief	Wrap a box2D body (<=> rigid body).
*
*/
// ****************************************

class Box2DBody : public CoreModifiable
{
public:
	DECLARE_CLASS_INFO(Box2DBody, CoreModifiable, Box2DBind)
	DECLARE_CONSTRUCTOR(Box2DBody);

protected:

	virtual ~Box2DBody();

	b2Body* mBody;
};