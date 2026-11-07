#pragma once

namespace Process {
	bool isProcessRunning();

	[[nodiscard]] bool attach();
}