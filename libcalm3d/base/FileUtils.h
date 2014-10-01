#ifndef _FILEUTILS_H_
#define _FILEUTILS_H_

#include "../CMMacro.h"
#include "../Common.h"

NS_CALM_BEGIN

class FileUtils
{ 
public:
	static FileUtils* Instance();

public:
	FileUtils();
	~FileUtils();

public:
	char* getFileData(const std::string& filename, const char* mode = "r", size_t* size = nullptr);
};

NS_CALM_END

#endif // _FILEUTILS_H_