#include <ntddk.h>



#define DELAY_ONE_MICROSEC (-10) // native value -> relative time
#define DELAY_ONE_MILLISEC (DELAY_ONE_MICROSEC*1000)


KTIMER myTimer;
LARGE_INTEGER due = { 0 };
KDPC myDpc;


VOID UnloadDriver(PDRIVER_OBJECT DriverObject) {
	UNREFERENCED_PARAMETER(DriverObject);
	KeCancelTimer(&myTimer);
	KdPrint(("Unload My Driver \n"));
}

VOID myDpcFunc(IN PKDPC Dpc, IN PVOID context, IN PVOID SysArgument1, IN PVOID SysArgument2) {
	UNREFERENCED_PARAMETER(Dpc);
	UNREFERENCED_PARAMETER(context);
	UNREFERENCED_PARAMETER(SysArgument1);
	UNREFERENCED_PARAMETER(SysArgument2);

	DbgPrint("Timer Working\t\n");
	KeSetTimer(&myTimer, due, &myDpc);
}
extern "C" NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {

	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);

	LARGE_INTEGER system_time = { 0 };
	LARGE_INTEGER local_time = { 0 };
	TIME_FIELDS local_time_fields = { 0 };

	due.QuadPart = 5000 * DELAY_ONE_MILLISEC;
	KeInitializeTimer(&myTimer);
	KeInitializeDpc(&myDpc, myDpcFunc, NULL);
	KeSetTimer(&myTimer, due, &myDpc);

	DriverObject->DriverUnload = (PDRIVER_UNLOAD)UnloadDriver;
	KdPrint(("Driver has been registered!\n"));
	return STATUS_SUCCESS;
}
