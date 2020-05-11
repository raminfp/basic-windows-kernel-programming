#include <ntddk.h>
#include <ntstrsafe.h>

#define BUFFER_SIZE 20

void DrvUnload(_In_ PDRIVER_OBJECT DriverObject) {
	UNREFERENCED_PARAMETER(DriverObject);
	KdPrint(("Driver Unload called\n"));
}

#define BUFFER_SIZE 20
CHAR buffer[BUFFER_SIZE];


extern "C" NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath) {

	UNREFERENCED_PARAMETER(RegistryPath);

	HANDLE file_handle;
	NTSTATUS status;
	NTSTATUS ntstatus;
	LARGE_INTEGER byteOffset;

	IO_STATUS_BLOCK iosb;
	OBJECT_ATTRIBUTES object_attributes;
	// Create text file : C:\\ProgramData\\test.txt // read :  Helloword
	UNICODE_STRING ufile_name = RTL_CONSTANT_STRING(L"\\??\\C:\\ProgramData\\test.txt");

	InitializeObjectAttributes(
		&object_attributes,
		&ufile_name,
		OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
		NULL,
		NULL);

	status = ZwCreateFile(
		&file_handle,
		GENERIC_READ | GENERIC_WRITE,
		&object_attributes,
		&iosb,
		NULL,
		FILE_ATTRIBUTE_NORMAL,
		FILE_SHARE_READ,
		FILE_OPEN_IF,
		FILE_NON_DIRECTORY_FILE |
		FILE_RANDOM_ACCESS |
		FILE_SYNCHRONOUS_IO_NONALERT,
		NULL,
		0);
	if (status == STATUS_SUCCESS) {

		byteOffset.LowPart = byteOffset.HighPart = 0;
		ntstatus = ZwReadFile(file_handle, NULL, NULL, NULL, &iosb, buffer, BUFFER_SIZE, &byteOffset, NULL);
		if (NT_SUCCESS(ntstatus)) {
			buffer[BUFFER_SIZE - 1] = '\0'; 
			DbgPrint("%s\n", buffer);
		} 
	}
	ZwClose(file_handle);
	DriverObject->DriverUnload = DrvUnload;
	KdPrint(("Driver initialized successfully\n"));
	return STATUS_SUCCESS;
}

