#include <ntddk.h>
#include "OSVersion.h"

VOID UnloadDriver(PDRIVER_OBJECT DriverObject) {
	UNREFERENCED_PARAMETER(DriverObject);
	KdPrint(("Unload My Driver \n"));
}

extern "C" NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {

	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);

	bool BlStatusWin10 = false;
	bool BLStatusWin7 = false;

	BlStatusWin10 = OSVersion::IsWindows10OrGreater();
	BLStatusWin7 = OSVersion::IsWindows7OrGreater();

	if (BlStatusWin10 == true) {
		KdPrint(("Your OS Is a Windows 10\n"));
	}
	if (BLStatusWin7 == true) {
		KdPrint(("Your OS Is a Windows 7\n"));
	}
	UNREFERENCED_PARAMETER(RegistryPath);
	DriverObject->DriverUnload = (PDRIVER_UNLOAD)UnloadDriver;
	KdPrint(("Driver has been registered!\n"));


	return STATUS_SUCCESS;
}