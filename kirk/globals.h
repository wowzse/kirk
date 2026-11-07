#pragma once

#include <windows.h>
#include <string>
#include <atomic>

namespace Globals {

	constexpr auto procName{ L"RobloxPlayerBeta.exe" };

	inline DWORD procId{ 0 };
	inline HANDLE procHandle{ 0 };
	inline uintptr_t procAddress{ 0 };
	inline std::wstring procVersion{ L"" };
	
	inline std::atomic<bool> attached{ false };
	inline std::atomic<bool> updateConfig{ false };

	inline uintptr_t dataModel{ 0 };

}