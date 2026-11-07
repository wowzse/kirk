#pragma once

#include <windows.h>
#include <string_view>

extern "C" {
	NTSTATUS Luck_ReadVirtualMemory(
		HANDLE processHandle,
		PVOID baseAddress,
		PVOID buffer,
		SIZE_T numOfBytesToRead,
		PSIZE_T numOfBytesRead
	);
	NTSTATUS Luck_WriteVirtualMemory(
		HANDLE processHandle,
		PVOID baseAddress,
		PVOID buffer,
		SIZE_T numOfBytesToWrite,
		PSIZE_T numOfBytesWritten
	);
	extern uint32_t Luck_ReadSyscall;
	extern uint32_t Luck_WriteSyscall;
}

namespace Syscall {
	inline bool isCleanStub(uint8_t* stub) {
		return stub[0] == 0x4C && stub[1] == 0x8B && stub[2] == 0xD1 && stub[3] == 0xB8;
	}

	inline bool getSyscallNum(uint32_t& var, std::string_view funcName) {
		HMODULE hNtdll = GetModuleHandleA("ntdll.dll");
		if (!hNtdll) return false;

		uint8_t* stub = reinterpret_cast<uint8_t*>(GetProcAddress(hNtdll, funcName.data()));
		if (!isCleanStub(stub)) return false;

		memcpy(&var, &stub[4], sizeof(uint32_t));
		return true;
	}

	[[nodiscard]] inline bool initSyscalls() {
		return getSyscallNum(Luck_ReadSyscall, "NtReadVirtualMemory") && getSyscallNum(Luck_WriteSyscall, "NtWriteVirtualMemory");
	}
}