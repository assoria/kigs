#include "CoreModifiable.h"
#include "Upgrador.h"
#include "CoreFSMTransition.h"


#define START_DECLARE_COREFSMSTATE(baseclassname,statename) \
class 	CoreFSMState##baseclassname##statename : public Upgrador<baseclassname> \
{ \
protected: \
	START_UPGRADOR(CoreFSMState##baseclassname##statename);\
	

#define ADD_STATE_METHODS(...) UPGRADOR_METHODS(__VA_ARGS__);

#define END_DECLARE_COREFSMSTATE() \
protected:\
	bool mIsInit = false;\
	bool mIsPersistent = false;\
	std::vector<SP<CoreFSMTransition>> mTransitions;\
};