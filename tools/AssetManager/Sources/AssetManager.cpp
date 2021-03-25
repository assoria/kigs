#include <AssetManager.h>

IMPLEMENT_CLASS_INFO(AssetManager);

IMPLEMENT_CONSTRUCTOR(AssetManager)
{

}

void	AssetManager::ProtectedInit()
{
	// Base modules have been created at this point
	// lets say that the update will sleep 1ms
	SetUpdateSleepTime(1);
}

void	AssetManager::ProtectedUpdate()
{
}

void	AssetManager::ProtectedClose()
{
}
