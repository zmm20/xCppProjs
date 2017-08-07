// dllmain.h: 模块类的声明。

class CHeloWorldATLModule : public ATL::CAtlDllModuleT< CHeloWorldATLModule >
{
public :
	DECLARE_LIBID(LIBID_HeloWorldATLLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_HELOWORLDATL, "{0E824538-9EE9-4B4E-9696-051FF864D034}")
};

extern class CHeloWorldATLModule _AtlModule;
