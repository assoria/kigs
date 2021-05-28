#pragma once
#include "CoreModifiable.h"
#include "Upgrador.h"
#include "CoreFSMTransition.h"

class CoreFSM;

// base class for state, multiple inheritance
class CoreFSMStateBase
{
public:

	virtual CoreFSMStateBase* Update(CoreModifiable* currentParentClass, CoreFSM* currentFSM, u32& specialOrder);

	const KigsID&	getID()
	{
		return dynamic_cast<UpgradorBase*>(this)->getID();
	}

protected:
	bool mIsInit = false; 
	bool mIsPersistent = false; 
	std::vector<SP<CoreFSMTransition>> mTransitions;

};

#define CoreFSMStateClass(baseclassname,statename)  CoreFSMState##baseclassname##statename

#define StringifyClassName(a) #a

#define CoreFSMStateClassName(baseclassname,statename)  StringifyClassName(CoreFSMState##baseclassname##statename)

#define START_DECLARE_COREFSMSTATE(baseclassname,statename) \
class 	CoreFSMState##baseclassname##statename : public Upgrador<baseclassname>,public CoreFSMStateBase \
{ \
protected: \
	START_UPGRADOR(CoreFSMState##baseclassname##statename);\
	

#define ADD_STATE_METHODS(...) UPGRADOR_METHODS(__VA_ARGS__);

#define END_DECLARE_COREFSMSTATE() \
};