// dllmain.h: 模块类的声明。

class CHeloWorldATL3Module : public ATL::CAtlDllModuleT< CHeloWorldATL3Module >
{
public :
	DECLARE_LIBID(LIBID_HeloWorldATL3Lib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_HELOWORLDATL3, "{F892ABF1-E065-4DC0-899C-5689107AD0E4}")
};

extern class CHeloWorldATL3Module _AtlModule;
