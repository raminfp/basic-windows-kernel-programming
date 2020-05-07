#include <ntddk.h>

#include "KeMalloc.h"



void DrvUnload(_In_ PDRIVER_OBJECT DriverObject) {
	UNREFERENCED_PARAMETER(DriverObject);
	KdPrint(("Driver Unload called\n"));
}


struct MyData2 {
	int Count;
	char *name;
};

extern "C" NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath) {

	UNREFERENCED_PARAMETER(RegistryPath);
	int i;
	int r = false;
	
	auto msize = new MyData2;
	msize->Count = 123456;
	msize->name = "test";
	KdPrint(("My Count is : %d\n", msize->Count));
	KdPrint(("My Count is : %s\n", msize->name));
	delete msize;

	DriverObject->DriverUnload = DrvUnload;
	KdPrint(("Driver initialized successfully\n"));
	return STATUS_SUCCESS;
}
