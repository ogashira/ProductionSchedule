#include "Control.h"
#include <crtdbg.h>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <Windows.h>

int main(void) {
    // Set console output code page to CP932 (Shift_JIS) for Japanese Windows environments.
    SetConsoleOutputCP(932);

	try {
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		//_CrtSetBreakAlloc(5082583);

		Control control = Control();
		control.start();
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Runtime Error: " << e.what() << std::endl;
	}
	catch (const char* msg) {
		std::cerr << "Error: " << msg << std::endl;
	}

	system("pause > 0");

	return 0;
}
