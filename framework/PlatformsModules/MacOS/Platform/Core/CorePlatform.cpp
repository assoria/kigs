#include "PrecompiledHeaders.h"
#include "../../../../Core/Headers/Core.h"
#include "../../../../FileManager/Headers/FilePathManager.h"
#include "Platform/Core/PlatformCore.h"
#include "Platform/Core/PlatformBaseApplication.h"

#include "../../../../Core/Headers/ModuleBase.h"
#include "../../../../Core/Headers/CoreBaseApplication.h"

#ifdef KIGS_HTTPREQUEST_AVAILABLE
#include "../../../../HTTPRequest/Headers/HTTPConnect.h"
#endif

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

// check if file exist and if it's a file or directory
void MacOSCheckState(FileHandle * hndl)
{
    struct stat filestat;
    
    if(stat(hndl->myFullFileName.c_str(),&filestat)<0)
    {
        // file doesn't exist
        hndl->resetStatus();
        return;
    }
    
    hndl->myStatus |= FileHandle::Exist;
    if (S_ISDIR(filestat.st_mode))
        hndl->myStatus |= FileHandle::IsDIr;

}

bool MacOSCreateFolderTree(FileHandle* hndl)
{
	
  	if ((hndl->myStatus&FileHandle::Exist) == 0)
	{
		SmartPointer<FileHandle> parent = FilePathManager::CreateFileHandle(FilePathManager::GetParentDirectory(hndl->myFullFileName));
		if (parent->myFullFileName != "")
		{
			MacOSCheckState(parent.get());
			MacOSCreateFolderTree(parent.get());
            
            if(mkdir(parent->myFullFileName.c_str(),755) != 0)
                return false;
            
		}
	}

	return true;
}

SmartPointer<FileHandle>	MacOSFindFullName(const kstl::string&	filename)
{
	//  TODO
  	if (filename[0] != '#')
	{
		return 0;
	}

	kstl::string fullFileName = "";

	FilePathManager::DeviceID	id = (FilePathManager::DeviceID)(filename[1]);

	switch (id)
	{
	case FilePathManager::CARD_STORAGE:
		return 0;
		break;
	case FilePathManager::DEVICE_STORAGE:
		return 0;
		break;
	case FilePathManager::APPLICATION_STORAGE:
	case FilePathManager::DB_STORAGE:				// Database is in application storage for us on win32
	{
/*		char resultchar[256];
		if (SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, resultchar) == S_OK)
		{
			fullFileName += resultchar;
			fullFileName += "\\";
		}*/
        // TODO
        return 0;
        break;
	}
	break;
	case FilePathManager::DOCUMENT_FOLDER:
	{
        /*
		char resultchar[256];
		if (SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, resultchar) == S_OK)
		{
			fullFileName += resultchar;
			fullFileName += "\\";
		}*/
        //TODO
        return 0;
        break;
        
    }
	break;
	case FilePathManager::DISTANT_FOLDER1:
	case FilePathManager::DISTANT_FOLDER2:
	case FilePathManager::DISTANT_FOLDER3:
	case FilePathManager::DISTANT_FOLDER4:
		break;

	default:
		if ((id >= FilePathManager::RESERVED1) && (id < FilePathManager::DRIVEA))
		{
			return 0;
		}
		else if (id >= FilePathManager::DRIVEA)
		{
			fullFileName += (char)('A' + (int)(id - FilePathManager::DRIVEA));
			fullFileName += "://";
		}
	}
	fullFileName += (const char*)(&(filename.c_str()[3]));

	SmartPointer<FileHandle> result = FilePathManager::CreateFileHandle((const char*)(&(filename.c_str()[3])));

	result->myDeviceID = id;
	result->myFullFileName = fullFileName;
	MacOSCheckState(result.get());
	return result;

}

bool MacOSfopen(FileHandle* handle, const char * mode)
{
	
  	unsigned int flagmode = FileHandle::OpeningFlags(mode);

	if (handle->myStatus&FileHandle::Open) // already opened ? return true
	{
		// check if open mode is the same
		if (flagmode == handle->getOpeningFlags())
		{
			return true;
		}
		else
		{
			fclose(handle->myFile);
		}
	}

	// create parent if in write mode
	if (flagmode & FileHandle::Write)
	{
		MacOSCreateFolderTree(handle);
	}


	handle->myFile = fopen(handle->myFullFileName.c_str(), mode);

	if (handle->myFile)
	{
		handle->myStatus |= FileHandle::Open;
		handle->myStatus |= FileHandle::Exist;
		handle->setOpeningFlags(flagmode);
		return true;
	}
	handle->resetStatus();
	return false;

}

long int MacOSfread(void * ptr, long size, long count, FileHandle* handle)
{
	return fread(ptr, size, count, handle->myFile);
}

long int MacOSfwrite(const void * ptr, long size, long count, FileHandle* handle)
{
	return fwrite(ptr, size, count, handle->myFile);
}

long int MacOSftell(FileHandle* handle)
{
	return ftell(handle->myFile);
}

int MacOSfseek(FileHandle* handle, long int offset, int origin)
{
	return fseek(handle->myFile, offset, origin);
}
int MacOSfflush(FileHandle* handle)
{
	return fflush(handle->myFile);
}
int MacOSfclose(FileHandle* handle)
{
	int result = fclose(handle->myFile);
	handle->resetStatus(); // reset 
	return result;
}

std::string to_utf8(const wchar_t* buffer, int len)
{
    
	/*int nChars = ::WideCharToMultiByte(
		CP_UTF8,
		0,
		buffer,
		len,
		NULL,
		0,
		NULL,
		NULL);
	if (nChars == 0) return "";
*/
    // TODO
	std::string newbuffer;
	//newbuffer.resize(nChars);
/*	::WideCharToMultiByte(
		CP_UTF8,
		0,
		buffer,
		len,
		const_cast<char*>(newbuffer.c_str()),
		nChars,
		NULL,
		NULL);
*/
	return newbuffer;
}

std::string to_utf8(const std::wstring& str)
{
	return to_utf8(str.c_str(), (int)str.size());
}

std::wstring to_wchar(const char* buffer, int len)
{
/*	int nChars = ::MultiByteToWideChar(
		CP_UTF8,
		0,
		buffer,
		len,
		NULL,
		0);

	if (nChars == 0) return L"";
*/
    // TODO
	std::wstring newbuffer;
/*	newbuffer.resize(nChars);
	::MultiByteToWideChar(
		CP_UTF8,
		0,
		buffer,
		len,
		const_cast<wchar_t*>(newbuffer.c_str()),
		nChars);
*/
	return newbuffer;
}

std::wstring to_wchar(const std::string& str)
{
	return to_wchar(str.c_str(), (int)str.size());
}
