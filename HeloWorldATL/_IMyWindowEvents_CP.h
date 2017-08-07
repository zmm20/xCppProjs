#pragma once

using namespace ATL;

template <class T>
class CProxy_IMyWindowEvents : public IConnectionPointImpl<T, &__uuidof(_IMyWindowEvents), CComDynamicUnkArray>
{
	// 警告:  此类可以由向导重新生成
public:
};
