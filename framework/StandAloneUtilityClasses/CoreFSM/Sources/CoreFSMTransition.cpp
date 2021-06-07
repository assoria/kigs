#include "CoreFSMTransition.h"
#include "CoreBaseApplication.h"
#include "NotificationCenter.h"

IMPLEMENT_CLASS_INFO(CoreFSMTransition)
IMPLEMENT_CLASS_INFO(CoreFSMOnSignalTransition)
IMPLEMENT_CLASS_INFO(CoreFSMOnEventTransition)
IMPLEMENT_CLASS_INFO(CoreFSMDelayTransition)
IMPLEMENT_CLASS_INFO(CoreFSMOnValueTransition)
IMPLEMENT_CLASS_INFO(CoreFSMOnMethodTransition)

CoreFSMTransition::CoreFSMTransition(const kstl::string& name, CLASS_NAME_TREE_ARG) : CoreModifiable(name, PASS_CLASS_NAME_TREE_ARG)
{

}


bool CoreFSMDelayTransition::checkTransition(CoreModifiable* currentParentClass)
{
	if (!IsInit())
	{
		Init();
	}
	
	double delay = KigsCore::GetCoreApplication()->GetApplicationTimer()->GetDelay(this);
	if (delay > mDelay)
	{
		return true;
	}
	return false;
}


bool CoreFSMOnValueTransition::checkTransition(CoreModifiable* currentParentClass)
{
	if (!IsInit())
	{
		Init();
	}

	return currentParentClass->getValue<bool>((std::string)mValueName);

}

bool CoreFSMOnMethodTransition::checkTransition(CoreModifiable* currentParentClass)
{
	if (!IsInit())
	{
		Init();
	}

	return currentParentClass->SimpleCall((std::string)mMethodName);

}

void CoreFSMOnEventTransition::InitModifiable()
{
	if (IsInit())
		return;

	ParentClassType::InitModifiable();
	KigsCore::GetNotificationCenter()->addObserver(this, "EventReceived", (std::string)mEventName);

}