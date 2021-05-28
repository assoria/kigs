#include "CoreModifiable.h"
#include "Upgrador.h"
#include "CoreFSM.h"

class CoreFSMTransition : public CoreModifiable
{
public:
	DECLARE_ABSTRACT_CLASS_INFO(CoreFSMTransition, CoreModifiable, CoreFSM);
	DECLARE_CONSTRUCTOR(CoreFSMTransition);


	friend class CoreFSM;


protected:
	void	setState(UpgradorBase* gotoState)
	{
		mGotoState = gotoState;
	}
	virtual UpgradorBase* checkTransition(CoreModifiable* currentParentClass, CoreFSM* currentFSM) = 0;

	UpgradorBase*	mGotoState;
};

class CoreFSMOnSignalTransition : public CoreFSMTransition
{
public:
	DECLARE_CLASS_INFO(CoreFSMOnSignalTransition, CoreFSMTransition, CoreFSM);
	DECLARE_CONSTRUCTOR(CoreFSMOnSignalTransition);

	UpgradorBase* checkTransition(CoreModifiable* currentParentClass, CoreFSM* currentFSM) override
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