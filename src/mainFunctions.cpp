#include "mainFunctions.h"
#include <windows.h>
#include <iostream>

bool MainFunctions::writeToPipe(const std::string& message) {
    DWORD written;
    return WriteFile(this->getWritePipe(), message.c_str(), message.size(), &written, NULL);
}

void MainFunctions::setWritePipe(HANDLE wp) {
    this->hWritePipe = wp;
}

HANDLE MainFunctions::getWritePipe() {
    return this->hWritePipe;
}

void MainFunctions::LaunchGUIWithContext(GameManager* context) {
    //Created a named pipe
    const char* pipeName = "\\\\.\\pipe\\ContextPipe";
    HANDLE hPipe = CreateNamedPipe(pipeName, PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE | PIPE_WAIT, 1,1024,1024, 0, NULL);

    if (hPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to create named pipe. Error: " << GetLastError() << std::endl;
        return;
    }

    // Launch the GUI with the named pipe in args
    STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi;
    std::string command = "e_tron_directX.exe " + std::string(pipeName);
    if (!CreateProcess(NULL, (LPSTR)command.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cerr << "Failed to launch GUI application. Error: " << GetLastError() << std::endl;
        CloseHandle(hPipe);
        return;
    }

	// Write the context to the pipe
    DWORD bytesWritten;
    if (!WriteFile(hPipe, &context, sizeof(context), &bytesWritten, NULL)) {
        std::cerr << "Failed to write to pipe. Error: " << GetLastError() << std::endl;
    }

    CloseHandle(hPipe);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

	context->setStopCmd(true);
}
