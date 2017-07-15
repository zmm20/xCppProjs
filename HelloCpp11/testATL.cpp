//#define MAIN

#ifdef MAIN

#include <iostream>
#include <cstdlib>

using namespace std;

class CBase
{
public:
    CBase(){}
    ~CBase(){}
    void BaseMethod()
    {
        cout << "BaseMethod in base" << endl;
    }
};

class CMath : public CBase
{
public:
    CMath(){}
    ~CMath(){}
    void BaseMethod()
    {
        cout << "BaseMethod in CMath" << endl;
    }
};

template < class T>
class CComObject : public T
{
public:
    CComObject() {}
    ~CComObject() {}
    void CallBaseMethod()
    {
        T* pT = static_cast<T*>(this);
        pT->BaseMethod();
    }
};


int main()
{
    CBase* base = new CMath();
    base->BaseMethod();

    CComObject<CBase> baseObj;
    baseObj.CallBaseMethod();

    CComObject<CMath> mathObj;
    mathObj.CallBaseMethod();

    return EXIT_SUCCESS;
}

#endif