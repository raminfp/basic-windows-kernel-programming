#include <ntddk.h>
#include "jsmn.h"



static const char *JSON_STRING =
"{\"user\": \"johndoe\", \"admin\": false, \"uid\": 1000,\n  "
"\"groups\": [\"users\", \"wheel\", \"audio\", \"video\"]}";

void DrvUnload(_In_ PDRIVER_OBJECT DriverObject) {
	UNREFERENCED_PARAMETER(DriverObject);
	KdPrint(("Driver Unload called\n"));
}


int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
	if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
		strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	}
	return -1;
}

extern "C" NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath) {

	UNREFERENCED_PARAMETER(RegistryPath);
	int i;
	int r = false;
	jsmn_parser p;
	jsmntok_t t[128];

	
	jsmn_init(&p);
	r = jsmn_parse(&p, JSON_STRING, strlen(JSON_STRING), t, sizeof(t) / sizeof(t[0]));
	if (r < 0) {
		KdPrint(("Failed to parse JSON: %d\n", r));
		return 1;
	}
	/* Assume the top-level element is an object */
	if (r < 1 || t[0].type != JSMN_OBJECT) {
		KdPrint(("Object expected\n"));
		return 1;
	}
	for (i = 1; i < r; i++) {
		if (jsoneq(JSON_STRING, &t[i], "user") == 0) {
			/* We may use strndup() to fetch string value */
			KdPrint(("- User: %.*s\n", t[i + 1].end - t[i + 1].start, JSON_STRING + t[i + 1].start));
			i++;
		}
	}
	DriverObject->DriverUnload = DrvUnload;
	KdPrint(("Driver initialized successfully\n"));
	return STATUS_SUCCESS;
}
