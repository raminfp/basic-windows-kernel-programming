#include <ntddk.h>

//typedef __int64 LONGLONG;
//typedef union _LARGE_INTEGER {
//	struct {
//		ULONG LowPart;
//		LONG HighPart;
//	};
//	struct {
//		ULONG LowPart;
//		LONG HighPart;
//	} u;
//	LONGLONG QuadPart;
//} LARGE_INTEGER;


void DrvUnload(_In_ PDRIVER_OBJECT DriverObject) {
	UNREFERENCED_PARAMETER(DriverObject);
	KdPrint(("Driver Unload called\n"));
}

extern "C" NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath) {

	UNREFERENCED_PARAMETER(RegistryPath);
	LARGE_INTEGER a, b;
	a.QuadPart = 100;
	a.QuadPart *= 100;
	b.QuadPart = a.QuadPart;
	if (b.QuadPart > 1000)
	{
		KdPrint(("b.QuadPart < 1000, LowPart = %x HighPart = %x", b.LowPart, b.HighPart));
	}
	DriverObject->DriverUnload = DrvUnload;
	KdPrint(("Driver initialized successfully\n"));
	return STATUS_SUCCESS;
}