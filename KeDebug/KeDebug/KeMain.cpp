
#include <ntddk.h>

//typedef struct _UNICODE_STRING {
//	USHORT Length;
//	USHORT MaximumLength;
//	PWSTR  Buffer;
//} UNICODE_STRING;
//typedef UNICODE_STRING *PUNICODE_STRING;
//
//typedef struct _STRING {
//	USHORT Length;
//	USHORT MaximumLength;
//	PCHAR Buffer;
//} STRING;
//typedef STRING *PSTRING;
//typedef STRING ANSI_STRING;
//typedef PSTRING PANSI_STRING;

VOID UnloadDriver(PDRIVER_OBJECT DriverObject) {
	UNREFERENCED_PARAMETER(DriverObject);
	KdPrint(("Unload My Driver \n"));
}

UNICODE_STRING pUStr;
//PUNICODE_STRING pUStr;
PANSI_STRING    pAStr = (PANSI_STRING)"Hello Ansi";

// Refs : https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/wdm/nf-wdm-dbgprint
// Unicode format codes (%C, %S, %lc, %ls, %wc, %ws, and %wZ)

extern "C" NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {

	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);
	RtlInitUnicodeString(&pUStr, L"Hello Unicode!");

	DbgPrint("Unicode string (wZ): %wZ\n", pUStr.Length / sizeof(WCHAR), pUStr.Length / sizeof(WCHAR), &pUStr);
	KdPrint(("Unicode string (S): %S\n", &pUStr));
	DbgPrint("Char (C): %C\n", 'A');
	KdPrint(("Char (C): %C\n", 'A'));
	KdPrint(("Unicode string (ls): %ls\n", pUStr));
	DbgPrint("Unicode string With DbgPrint() (ws): %wZ\n", &pUStr);
	KdPrint(("Unicode string With KdPrint() (ws): %wZ\n", &pUStr));
	KdPrint(("ANSI string: %.*s\n", pAStr->Length / sizeof(CHAR), pAStr));

	DriverObject->DriverUnload = (PDRIVER_UNLOAD)UnloadDriver;
	KdPrint(("Driver has been registered!\n"));
	return STATUS_SUCCESS;
}
