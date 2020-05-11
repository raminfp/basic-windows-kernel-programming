#include <ntddk.h>
#include <ntstrsafe.h>


#define BUFFER_SIZE 20

void DrvUnload(_In_ PDRIVER_OBJECT DriverObject) {
	UNREFERENCED_PARAMETER(DriverObject);
	KdPrint(("Driver Unload called\n"));
}

extern "C" NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath) {

	UNREFERENCED_PARAMETER(RegistryPath);


	HANDLE file_handle;
	
	NTSTATUS status;
	NTSTATUS ntstatus;

	IO_STATUS_BLOCK iosb;
	OBJECT_ATTRIBUTES object_attributes;
	UNICODE_STRING ufile_name = RTL_CONSTANT_STRING(L"\\??\\C:\\ProgramData\\a.txt");

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
		KdPrint(("File Write\n"));
		// Write to file
		NTSTATUS status;
		WCHAR *BUFFER = L"HelloWorld!";
		//ULONG strlen = RtlStringCbLengthW(BUFFER, BUFFER_SIZE, NULL);
		//ULONG strlen_ = wcslen(BUFFER);
		//ULONG stLength = sizeof(BUFFER);
		ntstatus = ZwWriteFile(file_handle, NULL, NULL, NULL, &iosb,
					BUFFER, BUFFER_SIZE, NULL, NULL);
		if (ntstatus == STATUS_SUCCESS) {
			KdPrint(("File Write is Done\n"));
		}
	}
	ZwClose(file_handle);
	DriverObject->DriverUnload = DrvUnload;
	KdPrint(("Driver initialized successfully\n"));
	return STATUS_SUCCESS;
}

