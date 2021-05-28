#pragma once
#include "CoreModifiable.h"

class CoreFSM;
class CoreFSMStateBase;


class CoreFSMTransition : public CoreModifiable
{
public:
	DECLARE_ABSTRACT_CLASS_INFO(CoreFSMTransition, CoreModifiable, CoreFSM);
	DECLARE_CONSTRUCTOR(CoreFSMTransition);

	friend class CoreFSM;
	friend class CoreFSMStateBase;

protected:
	void	setState(CoreFSMStateBase* gotoState)
	{
		mGotoState = gotoState;
	}
	virtual CoreFSMStateBase* checkTransition(CoreModifiable* currentParentClass, CoreFSM* currentFSM,u32& specialOrder) = 0;

	CoreFSMStateBase*	mGotoState;
};

class CoreFSMOnSignalTransition : public CoreFSMTransition
{
public:
	DECLARE_CLASS_INFO(CoreFSMOnSignalTransition, CoreFSMTransition, CoreFSM);
	DECLARE_CONSTRUCTOR(CoreFSMOnSignalTransition);

	CoreFSMStateBase* checkTransition(CoreModifiable* currentParentClass, CoreFSM* currentFSM, u32& specialOrder) override
	{
		if (mSignalReceived)
		{
			mSignalReceived = false;
			return mGotoState;
		}
		return nullptr;
	}

protected:

	bool		mSignalReceived = false;
};