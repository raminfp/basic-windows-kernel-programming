
#include <ntddk.h>
#include "kstring.h"

#define DRIVER_TAG 'ABCD'

VOID UnloadDriver(PDRIVER_OBJECT DriverObject) {
	UNREFERENCED_PARAMETER(DriverObject);
	KdPrint(("Unload My Driver \n"));
}

extern "C" NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {

	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);

	kstring<DRIVER_TAG> regPath(RegistryPath);
	regPath.ToLower();
	regPath += L"hello";
	
	KdPrint(("Path : %*.*ws\n", regPath.Length()));
	KdPrint(("\n\n"));

	DriverObject->DriverUnload = (PDRIVER_UNLOAD)UnloadDriver;
	KdPrint(("Driver has been registered!\n"));


	return STATUS_SUCCESS;
}
