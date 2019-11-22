#pragma once

#include <CoreBaseApplication.h>

class MacOSConsole : public CoreBaseApplication
{
public:
	DECLARE_CLASS_INFO(MacOSConsole, CoreBaseApplication, Core);
	DECLARE_CONSTRUCTOR(MacOSConsole);

protected:
	void	ProtectedInit() override;
	void	ProtectedUpdate() override;
	void	ProtectedClose() override;
};
