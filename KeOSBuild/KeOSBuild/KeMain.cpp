#include <ntddk.h>

void DrvUnload(_In_ PDRIVER_OBJECT DriverObject) {
	UNREFERENCED_PARAMETER(DriverObject);

	KdPrint(("driver Unload called\n"));
}

extern "C" NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath) {
	
	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);

	DriverObject->DriverUnload = DrvUnload;

	RTL_OSVERSIONINFOW info = { sizeof(info) };
	RtlGetVersion(&info);
	KdPrint(("Windows Version: %d.%d.%d\n", info.dwMajorVersion, info.dwMinorVersion, info.dwBuildNumber));

	KdPrint(("driver initialized successfully\n"));

	return STATUS_SUCCESS;
}
