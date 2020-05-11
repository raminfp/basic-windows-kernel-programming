#include <fltKernel.h>
#include <ntddk.h>


void DrvUnload(_In_ PDRIVER_OBJECT DriverObject) {
	UNREFERENCED_PARAMETER(DriverObject);
	KdPrint(("Driver Unload called\n"));
}

extern "C" NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath) {

	UNREFERENCED_PARAMETER(RegistryPath);

	PVOID memory = NULL;
	PVOID buffer = NULL;
	ULONG bufferSize = 42;

	// create heap in order to allocate memory later
	memory = RtlCreateHeap(
		HEAP_GROWABLE,
		NULL,
		1000,
		0, NULL, NULL
	);

	// allocate buffer of bufferSize
	buffer = RtlAllocateHeap(
		memory,
		HEAP_ZERO_MEMORY,
		bufferSize
	);
	PANSI_STRING  pAStr = (PANSI_STRING)"Hello";
	/*
		RtlCopyMemory
		RtlMoveMemory
		RtlFillMemory
		RtlZeroMemory
		RtlCompareMemory
	*/
	RtlCopyMemory(buffer, pAStr, 20);
	KdPrint(("String (S): %s\n", buffer));
	RtlFreeHeap(memory, 0, buffer);
	RtlDestroyHeap(memory);

	DriverObject->DriverUnload = DrvUnload;
	KdPrint(("Driver initialized successfully\n"));
	return STATUS_SUCCESS;
}
