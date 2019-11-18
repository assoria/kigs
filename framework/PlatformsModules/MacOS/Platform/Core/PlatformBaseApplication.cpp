#include "PrecompiledHeaders.h"
#include "PlatformBaseApplication.h"
#include "CoreIncludes.h"


#ifdef KIGS_INPUT_AVAILABLE
#include "../../../../Input/Headers/ModuleInput.h"
#include "../../../../Input/Headers/KeyboardDevice.h"
#include "../../../../Input/Headers/DeviceItem.h"
#include "Platform/Input/KeyDefine.h"
#endif

#include "CoreBaseApplication.h"


void	PlatformBaseApplication::OpenLink(const char* a_link)
{
    // TODO
//	ShellExecuteA(0, "open", a_link, 0, 0, SW_SHOW);
}

void	PlatformBaseApplication::OpenLink(const unsigned short* a_link, unsigned int a_length)
{
    //TODO
	//ShellExecuteW(0, 0, (LPCWSTR)a_link, 0, 0, SW_SHOW);
}

const char* platformName = "MacOS";

const char* PlatformBaseApplication::getPlatformName()
{
	return platformName;
}

bool	PlatformBaseApplication::CheckBackKeyPressed()
{
#ifdef KIGS_INPUT_AVAILABLE
	// TODO check if esc key is pressed here ?

	if (myKeyboard == 0)
	{
		static int countTest = 0;
		if (countTest == 0)
		{
			ModuleInput* theInputModule = static_cast<ModuleInput*>(CoreGetModule(ModuleInput));
			if (theInputModule)
			{
				myKeyboard = theInputModule->GetKeyboard();
			}
			else
			{
				countTest = 10;
			}
		}
		countTest--;
	}

	if (myKeyboard)
	{
		if (myKeyboard->getKeyState(CM_KEY_ESCAPE).GetTypedValue(int))
		{
			return true;
		}
	}
#endif
	return false;
}

//#define CHECK_INTERNET
bool	PlatformBaseApplication::CheckConnexion()
{
/*#if CHECK_INTERNET
	bool bConnect = InternetCheckConnectionA("http://www.google.com", FLAG_ICC_FORCE_CONNECTION, 0);
	return bConnect;
#else
 */
	return false;
//#endif
}

// get number of core / processor
unsigned int PlatformBaseApplication::getProcessorCount()
{
    // TODO
	/*SYSTEM_INFO sysinfo;
	GetSystemInfo( &sysinfo );

	return sysinfo.dwNumberOfProcessors;
     */
    return 1;
}

int PlatformBaseApplication::getCpuId() {

    // TODO
/*
	unsigned cpu = GetCurrentProcessorNumber();
		
	return (int)cpu;*/

    return 1;
}

void		PlatformBaseApplication::setCurrentThreadAffinityMask(int mask)
{
    // TODO
	//SetThreadAffinityMask(GetCurrentThread(), mask);
}

void		PlatformBaseApplication::setThreadAffinityMask(void* h,int mask)
{
    // TODO
	//SetThreadAffinityMask(h, mask);
}
