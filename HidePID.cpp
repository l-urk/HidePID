#include <windows.h>
#include <string>
#include <cstdio>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        // Print usage information if the number of arguments is incorrect
        printf("Usage: %s <executable_path> [arguments...]\n", argv[0]);
        return 1;
    }

    const char* executablePath = argv[1];

    // Build the command line by concatenating the executable path and arguments
    std::string commandLine = executablePath;
    for (int i = 2; i < argc; ++i) {
        commandLine += " ";
        commandLine += argv[i];
    }

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;  // Hide the console window of the new process

    // Create the process with the specified command line
    if (CreateProcessA(
        NULL,                     // Application Name (use NULL if CommandLine specifies the executable name)
        (LPSTR)commandLine.c_str(),  // Command Line
        NULL,                     // Process Attributes
        NULL,                     // Thread Attributes
        FALSE,                    // Inherit Handles
        CREATE_NO_WINDOW | DETACHED_PROCESS,  // Creation Flags
        NULL,                     // Environment
        NULL,                     // Current Directory
        &si,                      // Startup Information
        &pi                       // Process Information
    )) {
        // The process has been successfully created.

        // Close handles to the process and thread
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        // Handle error
        DWORD error = GetLastError();
        // Print or log the error code, or use FormatMessage to get a human-readable error message.
    }

    return 0;
}
