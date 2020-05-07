#include "KeMalloc.h"
#include <ntddk.h>

constexpr unsigned long PoolTag = 'abcd';

void* __cdecl operator new(size_t Size) {
	void* Pointer = ExAllocatePoolWithTag(NonPagedPool, Size, PoolTag);
	if (Pointer) RtlZeroMemory(Pointer, Size);
	return Pointer;
}

void* __cdecl operator new(size_t Size, POOL_TYPE PoolType) {
	void* Pointer = ExAllocatePoolWithTag(PoolType, Size, PoolTag);
	if (Pointer) RtlZeroMemory(Pointer, Size);
	return Pointer;
}

void* __cdecl operator new[](size_t Size) {
	void* Pointer = ExAllocatePoolWithTag(NonPagedPool, Size, PoolTag);
	if (Pointer) RtlZeroMemory(Pointer, Size);
	return Pointer;
}

void* __cdecl operator new[](size_t Size, POOL_TYPE PoolType) {
	void* Pointer = ExAllocatePoolWithTag(PoolType, Size, PoolTag);
	if (Pointer) RtlZeroMemory(Pointer, Size);
	return Pointer;
}

void __cdecl operator delete(void* Pointer) {
	ExFreePoolWithTag(Pointer, PoolTag);
}

void __cdecl operator delete(void* Pointer, size_t Size) {
	UNREFERENCED_PARAMETER(Size);
	ExFreePoolWithTag(Pointer, PoolTag);
}

void __cdecl operator delete[](void* Pointer) {
	ExFreePoolWithTag(Pointer, PoolTag);
}

void __cdecl operator delete[](void* Pointer, size_t Size) {
	UNREFERENCED_PARAMETER(Size);
	ExFreePoolWithTag(Pointer, PoolTag);
}
