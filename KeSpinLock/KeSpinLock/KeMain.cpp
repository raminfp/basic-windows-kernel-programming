#include <ntddk.h>

void DrvUnload(_In_ PDRIVER_OBJECT DriverObject) {
	UNREFERENCED_PARAMETER(DriverObject);
	KdPrint(("Driver Unload called\n"));
}

// SpinLock in the function base
void SafeFunction()
{
	KSPIN_LOCK my_spin_lock;
	KIRQL irql;
	KeInitializeSpinLock(&my_spin_lock);
	KeAcquireSpinLock(&my_spin_lock, &irql);
	//  To do something …
	KeReleaseSpinLock(&my_spin_lock, irql);
}


extern "C" NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath) {

	UNREFERENCED_PARAMETER(RegistryPath);

	KSPIN_LOCK my_spin_lock;
	KeInitializeSpinLock(&my_spin_lock);
	KIRQL irql;
	KeAcquireSpinLock(&my_spin_lock, &irql);
	// To do something …
	KdPrint(("To do something …\n"));
	KeReleaseSpinLock(&my_spin_lock, irql);
	DriverObject->DriverUnload = DrvUnload;
	KdPrint(("Driver initialized successfully\n"));
	return STATUS_SUCCESS;
}
