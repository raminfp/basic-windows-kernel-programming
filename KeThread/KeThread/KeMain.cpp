#include <ntddk.h>


VOID UnloadDriver(PDRIVER_OBJECT DriverObject) {
	UNREFERENCED_PARAMETER(DriverObject);
	KdPrint(("Unload My Driver \n"));
}


VOID MyProc(IN PVOID Context) {
	UNREFERENCED_PARAMETER(Context);
	DbgPrint("my new thread \r\n");
	PsTerminateSystemThread(STATUS_SUCCESS);
}

extern "C" NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {

	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);

	HANDLE ThreadHandel = NULL;
	NTSTATUS status;
	status = PsCreateSystemThread(&ThreadHandel, 0, NULL, NULL, NULL, MyProc, NULL);

	if (!NT_SUCCESS(status)) {
		DbgPrint("Create Thread failed \r\n");
		return status;
	}

	DriverObject->DriverUnload = (PDRIVER_UNLOAD)UnloadDriver;
	KdPrint(("Driver has been registered!\n"));
	return STATUS_SUCCESS;
}
