#pragma once

#include "CoreBaseApplication.h"
#include "AMRule.h"

#include <windows.h>

class FileStruct
{
public:
	std::vector<std::string>	mFolders;
	bool						mWasTreated = false;
	bool						mWasMatched = false;
	WIN32_FIND_DATAA			mFileInfos;

	bool						isInDirectory(const FileStruct&);
};

inline ULARGE_INTEGER	getLargeInteger(FILETIME* t)
{
	ULARGE_INTEGER	result;
	result.LowPart = t->dwLowDateTime;
	result.HighPart = t->dwHighDateTime;
	return result;
}

class AssetManager : public CoreBaseApplication
{
public:
	DECLARE_CLASS_INFO(AssetManager, CoreBaseApplication, Core);
	DECLARE_CONSTRUCTOR(AssetManager);

protected:

	void	ProtectedInit() override;
	void	ProtectedUpdate() override;
	void	ProtectedClose() override;

	void	doTheJob();

	void	usage();

	bool	initRules(CoreItemSP rules);
	void	runRules();

	void	recursiveSearchFiles(std::string	startDirectory, std::vector<std::string>& currentDirectoryList);


	FileStruct*		getFileStructFromName(const std::string& name);
	void			removeFileStructFromlist(const std::string& name);
	void			removeFileStructFromlistUsingPattern(const std::string& pattern);
	void			matchAllDir(FileStruct&);

	CMSP							mThread;
	std::string						mFolderIn = "";
	std::string						mFolderOut = "";
	std::string						mFolderInterm = "";
	std::string						mPlatform = "";
	std::vector<FileStruct>			mFileList;
	bool							mJobIsDone = false;
	bool							mResetAll = false;
	bool							mVerbose = false;

	std::vector<AMRule>				mRules;

	WRAP_METHODS(doTheJob);
};
