// dllmain.h: 模块类的声明。

class CHeloWorldATL2Module : public ATL::CAtlDllModuleT< CHeloWorldATL2Module >
{
public :
	DECLARE_LIBID(LIBID_HeloWorldATL2Lib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_HELOWORLDATL2, "{E1272A2C-A896-4AEB-966C-827C6397CE96}")
};

extern class CHeloWorldATL2Module _AtlModule;
