#include "CoreFSMTransition.h"

IMPLEMENT_CLASS_INFO(CoreFSMTransition)
IMPLEMENT_CLASS_INFO(CoreFSMOnSignalTransition)

CoreFSMTransition::CoreFSMTransition(const kstl::string& name, CLASS_NAME_TREE_ARG) : CoreModifiable(name, PASS_CLASS_NAME_TREE_ARG)
{

}

CoreFSMOnSignalTransition::CoreFSMOnSignalTransition(const kstl::string& name, CLASS_NAME_TREE_ARG) : CoreFSMTransition(name, PASS_CLASS_NAME_TREE_ARG)
{

}
