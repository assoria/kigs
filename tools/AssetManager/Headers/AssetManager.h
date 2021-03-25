#pragma once

#include <CoreBaseApplication.h>

class AssetManager : public CoreBaseApplication
{
public:
	DECLARE_CLASS_INFO(AssetManager, CoreBaseApplication, Core);
	DECLARE_CONSTRUCTOR(AssetManager);

protected:
	void	ProtectedInit() override;
	void	ProtectedUpdate() override;
	void	ProtectedClose() override;
};
