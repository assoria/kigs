#include <MacOSConsole.h>
#include "Core.h"
#include "FilePathManager.h"
#include "ModuleFileManager.h"

IMPLEMENT_CLASS_INFO(MacOSConsole);

IMPLEMENT_CONSTRUCTOR(MacOSConsole)
{

}

void	MacOSConsole::ProtectedInit()
{
	// Base modules have been created at this point
	// lets say that the update will sleep 1ms
	SetUpdateSleepTime(1);
    
    FilePathManager *pathManager=(FilePathManager*)KigsCore::GetSingleton("FilePathManager");
    
    u64 fsize;
    CoreRawBuffer* tst=ModuleFileManager::LoadFile("tst.txt",fsize);
    
    printf("tst size %d",tst->size());
}

void	MacOSConsole::ProtectedUpdate()
{
    printf("Hello World");
}

void	MacOSConsole::ProtectedClose()
{
}
