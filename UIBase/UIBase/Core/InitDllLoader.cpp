#include "../Header/MainDependency.h"
#ifdef __WIN32

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4073)
#endif

#pragma init_seg(lib)

static class InitDllLoader {
public:
	InitDllLoader() 
	{
		module = LoadLibraryA(DEFAULT_HGEDLLPATH);
	}

	~InitDllLoader() 
	{
		FreeLibrary(module);
	}

private:

	HMODULE module;

} _initDllLoader;

#endif