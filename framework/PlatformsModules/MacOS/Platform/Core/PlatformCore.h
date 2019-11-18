#ifndef _MACOS_CORE_H_
#define _MACOS_CORE_H_

#include <stdio.h>

class FileHandle;

template<typename smartPointOn>
class SmartPointer ;

extern bool MacOSfopen(FileHandle* handle, const char * mode);
//extern SmartPointer<FileHandle> MacOSfopen(const char* name, const char * mode);
extern long int MacOSfread(void * ptr, long size, long count, FileHandle* handle);
extern long int MacOSfwrite(const void * ptr, long size, long count, FileHandle* handle);
extern long int MacOSftell(FileHandle* handle);
extern int MacOSfseek( FileHandle* handle, long int offset, int origin);
extern int MacOSfflush( FileHandle* handle);
extern int MacOSfclose( FileHandle* handle);

extern SmartPointer<FileHandle> MacOSFindFullName(const std::string&	filename);
extern void MacOSCheckState(FileHandle* handle);
extern bool MacOSCreateFolderTree(FileHandle* hndl);

std::string to_utf8(const wchar_t* buffer, int len);
std::string to_utf8(const std::wstring& str);
std::wstring to_wchar(const char* buffer, int len);
std::wstring to_wchar(const std::string& str);


#endif //_MACOS_CORE_H_
