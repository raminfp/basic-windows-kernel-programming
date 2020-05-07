#include <ntddk.h>


VOID UnloadDriver(PDRIVER_OBJECT DriverObject) {
	UNREFERENCED_PARAMETER(DriverObject);
	KdPrint(("Unload My Driver \n"));
}

extern "C" NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {

	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);

	LARGE_INTEGER system_time = { 0 };
	LARGE_INTEGER local_time = { 0 };

	TIME_FIELDS local_time_fields = { 0 };

	KeQuerySystemTime(&system_time);
	ExSystemTimeToLocalTime(&system_time, &local_time);
	RtlTimeToTimeFields(&local_time, &local_time_fields);
	DbgPrint("time is %4d-%2d-%2d   %2d-%2d-%2d, \r\n", local_time_fields.Year, local_time_fields.Month, local_time_fields.Day, 
		local_time_fields.Hour, local_time_fields.Minute, local_time_fields.Second);
	
	DriverObject->DriverUnload = (PDRIVER_UNLOAD)UnloadDriver;
	KdPrint(("Driver has been registered!\n"));
	return STATUS_SUCCESS;
}
