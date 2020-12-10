#include "Box2DBody.h"
#include "Box2DBindModule.h"

IMPLEMENT_CLASS_INFO(Box2DBody)

IMPLEMENT_CONSTRUCTOR(Box2DBody)
{

}

Box2DBody::~Box2DBody()
{
	if (mBody)
	{
		Box2DBindModule* b2dmodule = (Box2DBindModule*)KigsCore::GetModule("Box2DBindModule");
		b2dmodule->GetWorld()->DestroyBody(mBody);
	}
	mBody = nullptr;
}