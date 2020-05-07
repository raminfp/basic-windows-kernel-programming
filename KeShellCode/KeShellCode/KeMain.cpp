#include <ntddk.h>

#if _WIN64 
typedef ULONG64(__fastcall *asmShell)(ULONG64, ULONG64);
#else
typedef ULONG32(__fastcall *asmShell)(ULONG32, ULONG32);
#endif

VOID UnloadDriver(PDRIVER_OBJECT DriverObject) {
	UNREFERENCED_PARAMETER(DriverObject);
	KdPrint(("Unload My Driver \n"));
}

extern "C" NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {

	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);

	DriverObject->DriverUnload = (PDRIVER_UNLOAD)UnloadDriver;
	asmShell shellcode = NULL;
	/*
	    // b - a
		0x0000000000000000:  48       dec eax
		0x0000000000000001:  29 D1    sub ecx, edx
		0x0000000000000003:  48       dec eax
		0x0000000000000004:  89 C8    mov eax, ecx
		0x0000000000000006:  C3       ret
		// b + a
		0x0000000000000000:  48       dec eax
		0x0000000000000001:  01 D1    add ecx, edx
		0x0000000000000003:  48       dec eax
		0x0000000000000004:  89 C8    mov eax, ecx
		0x0000000000000006:  C3       ret
	*/
	//UCHAR machinecode[8] = "\x48\x29\xd1\x48\x89\xc8\xc3";
#if _WIN64 
	UCHAR machinecode[10] = "\xff\xc8\x29\xd1\xff\xc8\x89\xc8\xc3";
#else
	UCHAR machinecode[8] = "\x48\x01\xd1\x48\x89\xc8\xc3";
#endif
	shellcode = (asmShell)ExAllocatePool(NonPagedPool, 8);
	if (shellcode == NULL)
		goto Exit;
	RtlCopyMemory(shellcode, machinecode, 8);
	KdPrint(("Driver has been registered!\n"));
	KdPrint(("Result is %d \r\n", shellcode(5, 2)));

Exit:
	if (shellcode == NULL)
		ExFreePool(shellcode);
	return STATUS_SUCCESS;


	//
	//return STATUS_SUCCESS;
}
