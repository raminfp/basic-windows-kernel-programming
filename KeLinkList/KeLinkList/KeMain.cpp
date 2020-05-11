#include <ntddk.h>
#include "LinkedList.h"
//#include <ntimage.h>
//#include <fltKernel.h>
//#include <Ntifs.h>

#define DRIVER_TAG 'hell'


struct MyData {
	int Data;
	LIST_ENTRY Entry;
	int MoreData;
};


PVOID NTAPI GetKernelProcAddress(LPCWSTR SystemRoutineName) {
	UNICODE_STRING Name;
	RtlInitUnicodeString(&Name, SystemRoutineName);
	return MmGetSystemRoutineAddress(&Name);
}


void DrvUnload(_In_ PDRIVER_OBJECT DriverObject) {
	UNREFERENCED_PARAMETER(DriverObject);
	KdPrint(("Driver Unload called\n"));
}

LinkedList<MyData> MyList;


extern "C" NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath) {

	UNREFERENCED_PARAMETER(RegistryPath);

	MyList.Init();
	auto item = static_cast<MyData*>(ExAllocatePoolWithTag(NonPagedPool, sizeof(MyData), DRIVER_TAG));
	item->Data = 8;
	item->MoreData = 19;
	MyList.PushBack(item);

	DriverObject->DriverUnload = DrvUnload;
	KdPrint(("Driver initialized successfully\n"));
	return STATUS_SUCCESS;
}
