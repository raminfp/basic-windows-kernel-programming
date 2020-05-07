#include <ntddk.h>
#include "kvector.h"

#define DRIVER_TAG 'abcd'

template<typename T>
using vector = kvector<T, DRIVER_TAG>;

VOID UnloadDriver(PDRIVER_OBJECT DriverObject) {
	UNREFERENCED_PARAMETER(DriverObject);
	KdPrint(("Unload My Driver \n"));
}


extern "C" NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {

	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);
	
	vector<int> v;
	v.Add(5);
	v.Add(12);
	v.Add(8);
	v.Add(4);
	v.Add(2);

	KdPrint(("Vector number is : %d\n", v.GetAt(0)));
	KdPrint(("Vector number is : %d\n", v.GetAt(1)));
	KdPrint(("Vector number is : %d\n", v.GetAt(2)));

	DriverObject->DriverUnload = (PDRIVER_UNLOAD)UnloadDriver;
	KdPrint(("Driver has been registered!\n"));
	return STATUS_SUCCESS;
}
