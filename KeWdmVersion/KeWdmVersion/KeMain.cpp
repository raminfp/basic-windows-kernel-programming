#include <ntddk.h>

// https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/wdm/nf-wdm-ioiswdmversionavailable#requirements

void DrvUnload(_In_ PDRIVER_OBJECT DriverObject) {
	UNREFERENCED_PARAMETER(DriverObject);
	KdPrint(("Driver Unload called\n"));
}

extern "C" NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath) {

	UNREFERENCED_PARAMETER(RegistryPath);
	if (IoIsWdmVersionAvailable(1, 0x10)) {
		KdPrint(("WDM 1.10 is supported, this is Windows 2000, or better.\n"));
	}
	else if (IoIsWdmVersionAvailable(1, 5)) {
		KdPrint(("WDM 1.05 is supported,\n"));
	}
	else {
		KdPrint(("WDM 1.0 is always supported.\n"));
	}
	DriverObject->DriverUnload = DrvUnload;
	KdPrint(("Driver initialized successfully\n"));
	return STATUS_SUCCESS;
}
