
#include <wdm.h>


void* __cdecl operator new(size_t Size);

void* __cdecl operator new(size_t Size, POOL_TYPE PoolType);

void* __cdecl operator new[](size_t Size);

void* __cdecl operator new[](size_t Size);

void* __cdecl operator new[](size_t Size, POOL_TYPE PoolType);

void __cdecl operator delete(void* Pointer);

void __cdecl operator delete(void* Pointer, size_t Size);

void __cdecl operator delete[](void* Pointer);

void __cdecl operator delete[](void* Pointer, size_t Size);