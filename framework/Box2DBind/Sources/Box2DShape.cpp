#include "Box2DShape.h"

IMPLEMENT_CLASS_INFO(Box2DShape)

IMPLEMENT_CONSTRUCTOR(Box2DShape)
{

}

Box2DShape::~Box2DShape()
{
	if (mShape)
		delete mShape;

	mShape = nullptr;
}