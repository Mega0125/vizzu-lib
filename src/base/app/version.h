#ifndef APP_VERSION
#define APP_VERSION

#include <string>

namespace App
{

class Version
{
public:

	Version(int major, int minor, int patch) :
	    major(major),
	    minor(minor),
	    patch(patch)
	{}

	explicit operator std::string() const;

private:
	int major;
	int minor;
	int patch;

	static std::string buildTimestamp();
};

}

#endif
