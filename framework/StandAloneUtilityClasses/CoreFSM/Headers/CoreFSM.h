#include "CoreModifiable.h"

void	initCoreFSM();

class CoreFSM : public CoreModifiable
{
public:
	DECLARE_CLASS_INFO(CoreFSM, CoreModifiable, CoreFSM);
	DECLARE_CONSTRUCTOR(CoreFSM);

	void	addState(const KigsID& id, UpgradorBase* base);

	void	setStartState(const KigsID& id);

	void	InitModifiable()override;

	void Update(const Timer& timer, void* addParam) override;

	virtual ~CoreFSM();

protected:

	void	changeCurrentState(UpgradorBase*);

	CoreModifiable* mAttachedObject = nullptr;
	UpgradorBase*	mCurrentState=nullptr;

	std::unordered_map<KigsID, UpgradorBase*>	mPossibleStates;
};