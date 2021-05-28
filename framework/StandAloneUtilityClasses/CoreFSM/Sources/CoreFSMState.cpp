#include "CoreFSMState.h"


CoreFSMStateBase* CoreFSMStateBase::Update(CoreModifiable* currentParentClass, CoreFSM* currentFSM, u32& specialOrder)
{
	CoreFSMStateBase* found=nullptr;
	for (auto t : mTransitions)
	{
		found = t->checkTransition(currentParentClass, currentFSM, specialOrder);
		if (found)
		{
			return found;
		}
	}
	return nullptr;
}
