#include "CoreFSM.h"
#include "Core.h"
#include "CoreBaseApplication.h"
#include "CoreFSMTransition.h"

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



}

void	CoreFSM::setStartState(const KigsID& id)
{
	if (mPossibleStates.find(id) != mPossibleStates.end())
	{
		changeCurrentState(mPossibleStates[id]);
	}
	else
	{
		KIGS_ERROR("FSM State not available", 2);
	}
}

void	CoreFSM::addState(const KigsID& id, UpgradorBase* base)
{
	if (mPossibleStates.find(id) != mPossibleStates.end()) // already there ?
	{

	}
}

void	CoreFSM::InitModifiable()
{
	ParentClassType::InitModifiable();
	if (IsInit())
	{
		if (GetParents().size()) // can't init without parent
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