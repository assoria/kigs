#include "CoreFSM.h"
#include "Core.h"
#include "CoreBaseApplication.h"
#include "CoreFSMState.h"

IMPLEMENT_CLASS_INFO(CoreFSM)

CoreFSM::CoreFSM(const kstl::string& name, CLASS_NAME_TREE_ARG) : CoreModifiable(name, PASS_CLASS_NAME_TREE_ARG)
{
	KigsCore::GetCoreApplication()->AddAutoUpdate(this);
}

void CoreFSM::Update(const Timer& timer, void* addParam) 
{
	if (!IsInit()) // if not init, try to init
	{
		Init();
	}
	if (!IsInit())
	{
		return;
	}
	u32 specialOrder = 0;
	CoreFSMStateBase* nextState = mCurrentState.back()->Update(mAttachedObject, this,specialOrder);

	if (specialOrder == (u32)FSMStateSpecialOrder::POP_TRANSITION)
	{
		// TODO mCurrentState.back()->endState();
		popCurrentState();
		return;
	}
	if (nextState)
	{
		// TODO mCurrentState.back()->endState();
		if (specialOrder == (u32)FSMStateSpecialOrder::PUSH_TRANSITION)
		{
			pushCurrentState(nextState);
		}
		else
		{
			changeCurrentState(nextState);
		}
	}

}

void	CoreFSM::changeCurrentState(CoreFSMStateBase* newone)
{
	if (mCurrentState.size())
	{
		mAttachedObject->Downgrade(mCurrentState.back()->getID());
		mCurrentState.back() = newone;
		mAttachedObject->Upgrade(dynamic_cast<UpgradorBase*>(newone));
	}
}

void	CoreFSM::pushCurrentState(CoreFSMStateBase* newone)
{
	if (mCurrentState.size())
	{
		mAttachedObject->Downgrade(mCurrentState.back()->getID());
	}
	mCurrentState.push_back(newone);
	mAttachedObject->Upgrade(dynamic_cast<UpgradorBase*>(newone));

}
void	CoreFSM::popCurrentState()
{
	if (mCurrentState.size())
	{
		mAttachedObject->Downgrade(mCurrentState.back()->getID());
		mCurrentState.pop_back();
	}
	if (mCurrentState.size())
	{
		mAttachedObject->Upgrade(dynamic_cast<UpgradorBase*>(mCurrentState.back()));
	}
}

void	CoreFSM::setStartState(const KigsID& id)
{
	if (mPossibleStates.find(id) != mPossibleStates.end())
	{
		pushCurrentState(mPossibleStates[id]);
	}
	else
	{
		KIGS_ERROR("FSM State not available", 2);
	}
}

void	CoreFSM::addState(const KigsID& id, CoreFSMStateBase* base)
{
	if (IsInit())
	{
		KIGS_ERROR("try to add states on an initialized FSM", 2);
		return;
	}

	if (mPossibleStates.find(id) != mPossibleStates.end()) // already there ?
	{

	}
}

void	CoreFSM::InitModifiable()
{
	ParentClassType::InitModifiable();
	if (IsInit())
	{
		if (GetParents().size() || (mCurrentState.size()==0)) // can't init without parent or start state
		{
			mAttachedObject = GetParents()[0];
		}
		else
		{
			UnInit();
		}
	}
}

CoreFSM::~CoreFSM()
{
	KigsCore::GetCoreApplication()->RemoveAutoUpdate(this);
}


void	initCoreFSM()
{
	DECLARE_FULL_CLASS_INFO(KigsCore::Instance(), CoreFSM, CoreFSM, CoreFSM);
	DECLARE_FULL_CLASS_INFO(KigsCore::Instance(), CoreFSMOnSignalTransition, CoreFSMOnSignalTransition, CoreFSM);
}