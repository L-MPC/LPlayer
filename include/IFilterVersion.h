
#pragma once

interface __declspec(uuid("A0DD28E1-61C0-4539-A7E6-14544AFF092E"))
IFilterVersion :
public IUnknown {
    STDMETHOD_(DWORD, GetFilterVersion)() = 0;
};
