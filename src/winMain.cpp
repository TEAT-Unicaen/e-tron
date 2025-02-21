#include <windows.h>
#include <string>
#include "graphics/app.h"

void* GetContextFromPipe() {
	HANDLE hPipe;
	const int maxRetries = 10;
	const int delayMs = 100; 
	//Handle the pipe connection safely with retries
	for (int i = 0; i < maxRetries; ++i) {
		hPipe = CreateFile("\\\\.\\pipe\\ContextPipe", GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
		if (hPipe != INVALID_HANDLE_VALUE) {
			break;
		}

		if (i == maxRetries - 1) {throw ETRON_EXCEPT("GUI Failed to get pipe handle");}
		Sleep(delayMs);
	}

	//Read the context from the pipe
	void* context;
	DWORD bytesRead;
	if (!ReadFile(hPipe, &context, sizeof(context), &bytesRead, NULL)) {
		CloseHandle(hPipe);
		throw ETRON_EXCEPT("GUI Failed to read from connected pipe. Error: " + GetLastError());
	}

	CloseHandle(hPipe);
	return context;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine,_In_ int nCmdShow) {
	try {

		//Execution from the cmdline
		std::string useContext(lpCmdLine);
		if (useContext == "context") {
			void* context = GetContextFromPipe();
			if (context == nullptr) {
				throw ETRON_EXCEPT("GUI Failed to get context from pipe.");
			} 
			MessageBox(nullptr, "Everything is fine", "Context retrieved", MB_OK | MB_ICONEXCLAMATION);
			return App{}.run();
			// return App{}.run(context); TODO : Implement context in App
		}

		//Standard execution
		return App{}.run();

	} catch (const ETronException& e) {
		MessageBox(nullptr, e.what(), e.getType(), MB_OK | MB_ICONEXCLAMATION);
		return -1;
	} catch (const std::exception& e) {
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
		return -2;
	}
	catch (...) {
		MessageBox(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
		return -3;
	}
	return -555;
}