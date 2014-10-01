#include "FileUtils.h"
#include "Log.h"

NS_CALM_BEGIN

FileUtils* FileUtils::Instance()
{
	static FileUtils sThis;
	return &sThis;
}

FileUtils::FileUtils()
{

}

FileUtils::~FileUtils()
{

}

char* FileUtils::getFileData(const std::string& filename, const char* mode /*= "r"*/, size_t* size /*= nullptr*/)
{
	char* buffer = nullptr;
	if (size) {
		*size = 0;
	}

	FILE* fp = fopen(filename.c_str(), "rb");
	if (fp) {
		fseek(fp, 0, SEEK_END);
		size_t filesize = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		buffer = (char*)malloc(filesize);
		filesize = fread(buffer, sizeof(char), filesize, fp);
		fclose(fp);

		if (size) {
			*size = filesize;
		}
	}

	if (!buffer) {
		std::string msg = "Get data from file(";
		msg.append(filename).append(") failed!");

		log("%s", msg.c_str());
	}

	return buffer;
}


NS_CALM_END
