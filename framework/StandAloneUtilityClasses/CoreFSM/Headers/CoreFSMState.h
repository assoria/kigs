#pragma once
#include "CoreModifiable.h"
#include "Upgrador.h"
#include "CoreFSMTransition.h"

class CoreFSM;

// base class for state, multiple inheritance
class CoreFSMStateBase
{
public:

	virtual void	start(CoreModifiable* currentParentClass, CoreFSMStateBase* prevstate);
	virtual void	stop(CoreModifiable* currentParentClass, CoreFSMStateBase* nextstate);
	virtual bool	Update(CoreModifiable* currentParentClass, u32& specialOrder, KigsID& newstate);

	const KigsID&	getID()
	{
		return dynamic_cast<UpgradorBase*>(this)->getID();
	}

	void	AddTransition(SP<CoreFSMTransition> t)
	{
		mTransitions.push_back(t);
	}

	virtual ~CoreFSMStateBase()
	{
		mTransitions.clear();
	}

	SP<CoreFSMTransition>	getTransition(const KigsID& transitionname)
	{
		for (auto t : mTransitions)
		{
			if (t->getNameID() == transitionname)
			{
				return t;
			}
		}
		return nullptr;
	}

protected:

	bool mIsInit = false; 
	bool mIsPersistent = false; 
	std::vector<SP<CoreFSMTransition>> mTransitions;

};

#define CoreFSMStateClass(baseclassname,statename)  CoreFSMState##baseclassname##statename

#define CoreFSMStartMethod(baseclassname,statename)  CoreFSMState##baseclassname##statename::UpgradorMethods::start(class CoreFSMStateBase*)
#define CoreFSMStopMethod(baseclassname,statename)  CoreFSMState##baseclassname##statename::UpgradorMethods::stop(class CoreFSMStateBase*)

#define StringifyClassName(a) #a

#define CoreFSMStateClassName(baseclassname,statename)  StringifyClassName(CoreFSMState##baseclassname##statename)

#define START_DECLARE_COREFSMSTATE(baseclassname,statename) \
class 	CoreFSMState##baseclassname##statename : public Upgrador<baseclassname>,public CoreFSMStateBase \
{ \
protected: \
	START_UPGRADOR(CoreFSMState##baseclassname##statename);

#define DO_COREFSMSTATE_SUBCLASS_DECLARATION() class UpgradorMethods : public currentBaseClass \
{ \
 public:\
	UpgradorType*	GetUpgrador(){return (UpgradorType*)CoreModifiable::GetUpgrador();}\
	void			UpgradorUpdate(const Timer& timer, void* addParam);\
	void			start(CoreFSMStateBase* prevstate);\
	void			stop(CoreFSMStateBase* nextstate);

#define DO_COREFSMSTATE_BASE_METHOD_DEFINITION() };\
public:\
void	UpgradorUpdate(CoreModifiable* toUpdate, const Timer& timer, void* addParam) override\
{\
	((UpgradorMethods*)toUpdate)->UpgradorUpdate(timer, addParam);\
}\
virtual void	start(CoreModifiable* toStart,CoreFSMStateBase* prevstate) override\
{\
	((UpgradorMethods*)toStart)->start(prevstate);\
	CoreFSMStateBase::start(toStart,prevstate);\
}\
virtual void	stop(CoreModifiable* toStop,CoreFSMStateBase* nextstate) override\
{\
	CoreFSMStateBase::stop(toStop,nextstate);\
	((UpgradorMethods*)toStop)->stop(nextstate);\
}

#define COREFSMSTATE_WITHOUT_METHODS() DO_COREFSMSTATE_SUBCLASS_DECLARATION() \
DO_COREFSMSTATE_BASE_METHOD_DEFINITION() \
virtual void GetMethodTable(kstl::vector<std::pair<KigsID, CoreModifiable::ModifiableMethod>>& table) override\
{\
}

#define COREFSMSTATE_METHODS(...) DO_COREFSMSTATE_SUBCLASS_DECLARATION() \
FOR_EACH(DECLARE_METHOD, __VA_ARGS__)\
DO_COREFSMSTATE_BASE_METHOD_DEFINITION() \
virtual void GetMethodTable(kstl::vector<std::pair<KigsID, CoreModifiable::ModifiableMethod>>& table) override\
{\
	FOR_EACH(UPGRADOR_METHOD_PUSH_BACK, __VA_ARGS__)\
}

#define END_DECLARE_COREFSMSTATE() \
};