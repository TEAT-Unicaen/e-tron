#include <iostream>
#include <windows.h>

int main() {
    HANDLE hReadPipe;
    char buffer[128];
    DWORD bytesRead;

    // Init an read named pipe to retreive first process infos
    hReadPipe = CreateNamedPipe("\\\\.\\pipe\\GamePipe", PIPE_ACCESS_INBOUND, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,1,128,128,0,NULL);

    if (hReadPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to create named pipe.\n";
        return 1;
    }

    std::cout << "Created a pipe ... Waiting for connection." << std::endl;

    // Waiting for a client pipe connect
    if (!ConnectNamedPipe(hReadPipe, NULL)) {
        std::cerr << "Failed to connect to named pipe.\n";
        CloseHandle(hReadPipe);
        return 1;
    }

    // Pipe message handling
    while (true) {
        if (ReadFile(hReadPipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
            buffer[bytesRead] = '\0';
            std::cout << buffer << std::endl;
        } else {
            std::cerr << "Failed to read from pipe. Closing ...\n";
            break;
        }
    }

    CloseHandle(hReadPipe);
    return 0;
}
