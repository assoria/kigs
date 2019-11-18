#ifndef _CORE_PLATFORM_DEFINES_H
#define _CORE_PLATFORM_DEFINES_H

//#define DOPROFILE

// **********************************************************************
//
// ERROR MANAGEMENT
//
// **********************************************************************


// level error 0 is for all error / warning / messages
// level error 1 is for error / warning 
// level error 2 is for error only
// level error 3 is for nothing
#ifdef _DEBUG
#define KIGS_ERROR_LEVEL		0
#else //_DEBUG
#define KIGS_ERROR_LEVEL		2
#endif //_DEBUG

#define	STOP_ON_ERROR

#define	KIGS_ERROR_BUFFER_SIZE	4096 

// **********************************************************************
//
// STL MANAGEMENT
//
// **********************************************************************

#define _NO_KSTL_OVERLOADING_
#ifndef _NO_KSTL_OVERLOADING_
#define _DO_KSTL_OVERLOADING_
#endif

// **********************************************************************
//
// MEMORY MANAGEMENT
//
// **********************************************************************

#define _NO_MEMORY_MANAGER_

#define MEMORYMANAGEMENT_START 
#define MEMORYMANAGEMENT_END 

#define NO_MEMORYMANAGEMENT_START 
#define NO_MEMORYMANAGEMENT_END	 

#ifndef _NO_MEMORY_MANAGER_

#define MM_USE_CUSTOM_CALLBACK
#define	MM_IS_INIT_BY_CORE

#endif


// **********************************************************************
//
// THREAD MANAGEMENT
//
// **********************************************************************

#define SYSTEM_THREAD_RETURN_A_VALUE

#ifdef SYSTEM_THREAD_RETURN_A_VALUE
typedef	int ThreadReturnType;
#else
typedef	void ThreadReturnType;
#endif

// **********************************************************************
//
// RTTI (dynamic cast) MANAGEMENT
//
// **********************************************************************

//#define RTTI_IS_AVAILABLE

// **********************************************************************
//
// FILE MANAGEMENT
//
// **********************************************************************

#define PLATFORM_FILE					FILE
#define Platform_Hiddenfopen			MacOSfopen
#define Platform_Hiddenfread			MacOSfread
#define Platform_Hiddenfwrite			MacOSfwrite
#define Platform_Hiddenftell			MacOSftell
#define Platform_Hiddenfseek			MacOSfseek
#define Platform_Hiddenfflush			MacOSfflush
#define Platform_Hiddenfclose			MacOSfclose
#define Platform_CheckState				MacOSCheckState
#define Platform_FindFullName			MacOSFindFullName
#define	Platform_CreateFolderTree		MacOSCreateFolderTree

// **********************************************************************
//
// RANDOM MANAGEMENT
//
// **********************************************************************

#define Platform_rand		rand
#define Platform_srand		srand

// **********************************************************************
//
// MISC
//
// **********************************************************************

#define USE_LIB_PNG
#define USE_LIB_JPG

#define SUPPORT_S3TC_TEXTURE
#define SUPPORT_ETC_TEXTURE

#define kigsprintf(...) printf(__VA_ARGS__)

//#ifdef KIGS_TOOLS
//#define NO_DELAYED_INIT
//#endif

# endif //_CORE_PLATFORM_DEFINES_H