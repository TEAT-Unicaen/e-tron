#include "graphics/app.h"

void* GetContextFromPipe(const std::string& pipeName) {
	HANDLE hPipe = CreateFile(pipeName.c_str(),GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);

	if (hPipe == INVALID_HANDLE_VALUE) {
		throw ETRON_EXCEPT("GUI Failed to get pipe handle");
	}

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
		std::string pipeName(lpCmdLine);
		if (pipeName != "") {
			void* context = GetContextFromPipe(pipeName);
			if (context == nullptr) {
				throw ETRON_EXCEPT("GUI Failed to get context from pipe.");
			} 
			MessageBox(nullptr, "Everything is fine", "Context retreived", MB_OK | MB_ICONEXCLAMATION);
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