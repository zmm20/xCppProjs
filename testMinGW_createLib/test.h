#ifdef Dll_ISECOCRFORTESS
#define DllAPI __declspec(dllimport)   
#else   
#define DllAPI __declspec(dllexport) 
#endif

#include <string>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

DllAPI int add(int a, int b);
DllAPI std::string hello(std::string name); // 测试标准容器

#ifdef __cplusplus
}
#endif /* __cplusplus */

