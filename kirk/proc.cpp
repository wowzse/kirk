#include "proc.h"
#include "globals.h"

#include <windows.h>
#include <TlHelp32.h>

static bool getProcId() {
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snapshot == INVALID_HANDLE_VALUE) return false;

	PROCESSENTRY32W processEntry{};
	processEntry.dwSize = sizeof(processEntry);

	if (Process32FirstW(snapshot, &processEntry)) {
		do {
			if (_wcsicmp(Globals::procName, processEntry.szExeFile) == 0) {
				CloseHandle(snapshot);
				Globals::procId = processEntry.th32ProcessID;
				return true;
			}
		} while (Process32NextW(snapshot, &processEntry));
	}

	CloseHandle(snapshot);
	return false;
}

static bool getProcAddress() {
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, Globals::procId);
	if (snapshot == INVALID_HANDLE_VALUE) return false;

	MODULEENTRY32W moduleEntry{};
	moduleEntry.dwSize = sizeof(moduleEntry);

	if (Module32FirstW(snapshot, &moduleEntry)) {
		do {
			if (_wcsicmp(Globals::procName, moduleEntry.szModule) == 0) {
				CloseHandle(snapshot);
				Globals::procAddress = reinterpret_cast<uintptr_t>(moduleEntry.modBaseAddr);
				return true;
			}
		} while (Module32NextW(snapshot, &moduleEntry));
	}

	CloseHandle(snapshot);
	return false;
}

static bool getProcHandle() {
	Globals::procHandle = OpenProcess(PROCESS_ALL_ACCESS, false, Globals::procId);
	return Globals::procHandle;
}

static bool getVersion() {
	wchar_t path[MAX_PATH];
	DWORD size = MAX_PATH;

	if (QueryFullProcessImageNameW(Globals::procHandle, 0, path, &size)) {
		wchar_t* end = std::wcsrchr(path, L'\\');
		if (!end) return false;

		*end = L'\0';

		wchar_t* start = std::wcsrchr(path, L'\\');
		if (!start) return false;

		Globals::procVersion.assign(start + 1);
		return true;
	}
	return false;
}

bool Process::isProcessRunning() {
	return Globals::procHandle && WaitForSingleObject(Globals::procHandle, 0) == WAIT_TIMEOUT;
}

bool Process::attach() {
	return getProcId() && getProcAddress() && getProcHandle() && getVersion();
}