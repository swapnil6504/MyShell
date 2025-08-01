#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <memory>

// Windows-specific headers
#include <windows.h>
#include <shellapi.h>
#include <io.h>
#include <fcntl.h>
#include <direct.h>

class MyShell
{
private:
    std::string currentDirectory;
    bool running;
    HANDLE hConsole;

    // Console colors for enhanced UI
    enum class Color
    {
        RED = FOREGROUND_RED,
        GREEN = FOREGROUND_GREEN,
        BLUE = FOREGROUND_BLUE,
        YELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
        CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE,
        MAGENTA = FOREGROUND_RED | FOREGROUND_BLUE,
        WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
        BRIGHT_WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
    };

public:
    MyShell() : running(true)
    {
        // Get console handle for colored output
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        // Get current working directory
        updateCurrentDirectory();

        // Set console to handle UTF-8 properly
        SetConsoleOutputCP(CP_UTF8);
    }

    ~MyShell()
    {
        // Reset console color
        setConsoleColor(Color::WHITE);
    }

    void run()
    {
        printWelcomeMessage();

        while (running)
        {
            displayPrompt();
            std::string input = getUserInput();

            if (!input.empty())
            {
                processCommand(input);
            }
        }

        printExitMessage();
    }

private:
    void printWelcomeMessage()
    {
        setConsoleColor(Color::CYAN);
        std::cout << "====================================\n";
        std::cout << "    Welcome to MyShell v1.0\n";
        std::cout << "    Windows C++ Shell Implementation\n";
        std::cout << "====================================\n";
        setConsoleColor(Color::YELLOW);
        std::cout << "Type 'help' for available commands\n\n";
        setConsoleColor(Color::WHITE);
    }

    void printExitMessage()
    {
        setConsoleColor(Color::CYAN);
        std::cout << "\nThank you for using MyShell!\n";
        setConsoleColor(Color::WHITE);
    }

    void setConsoleColor(Color color)
    {
        SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
    }

    void updateCurrentDirectory()
    {
        char buffer[MAX_PATH];
        if (GetCurrentDirectoryA(MAX_PATH, buffer))
        {
            currentDirectory = std::string(buffer);
        }
        else
        {
            currentDirectory = "Unknown";
        }
    }

    void displayPrompt()
    {
        setConsoleColor(Color::GREEN);
        std::cout << "MyShell";
        setConsoleColor(Color::BLUE);
        std::cout << " [" << currentDirectory << "]";
        setConsoleColor(Color::WHITE);
        std::cout << "> ";
    }

    std::string getUserInput()
    {
        std::string input;
        std::getline(std::cin, input);
        return input;
    }

    std::vector<std::string> tokenizeCommand(const std::string &command)
    {
        std::vector<std::string> tokens;
        std::string current_token;
        bool in_quotes = false;
        char quote_char = '\0';

        for (size_t i = 0; i < command.length(); ++i)
        {
            char c = command[i];

            if (!in_quotes && (c == '"' || c == '\''))
            {
                // Start of quoted string
                in_quotes = true;
                quote_char = c;
            }
            else if (in_quotes && c == quote_char)
            {
                // End of quoted string
                in_quotes = false;
                quote_char = '\0';
            }
            else if (!in_quotes && (c == ' ' || c == '\t'))
            {
                // Whitespace outside quotes - end current token
                if (!current_token.empty())
                {
                    tokens.push_back(current_token);
                    current_token.clear();
                }
            }
            else
            {
                // Regular character or whitespace inside quotes
                current_token += c;
            }
        }

        // Add the last token if it exists
        if (!current_token.empty())
        {
            tokens.push_back(current_token);
        }

        return tokens;
    }

    void processCommand(const std::string &input)
    {
        // Check for pipe operations
        if (input.find('|') != std::string::npos)
        {
            processPipeCommand(input);
            return;
        }

        // Check for redirection
        if (input.find('>') != std::string::npos || input.find('<') != std::string::npos)
        {
            processRedirectionCommand(input);
            return;
        }

        // Regular command processing
        std::vector<std::string> tokens = tokenizeCommand(input);

        if (tokens.empty())
        {
            return;
        }

        std::string command = tokens[0];
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);

        // Handle built-in commands
        if (command == "exit")
        {
            handleExit();
        }
        else if (command == "cd")
        {
            handleChangeDirectory(tokens);
        }
        else if (command == "help")
        {
            handleHelp();
        }
        else if (command == "cls" || command == "clear")
        {
            handleClear();
        }
        else if (command == "pwd")
        {
            handlePrintWorkingDirectory();
        }
        else if (command == "dir" || command == "ls")
        {
            handleListDirectory(tokens);
        }
        else
        {
            // Execute external command
            executeExternalCommand(tokens);
        }
    }

    void processPipeCommand(const std::string &input)
    {
        std::vector<std::string> commands;
        std::stringstream ss(input);
        std::string command;

        // Split by pipe character
        while (std::getline(ss, command, '|'))
        {
            // Trim whitespace
            command.erase(0, command.find_first_not_of(" \t"));
            command.erase(command.find_last_not_of(" \t") + 1);
            if (!command.empty())
            {
                commands.push_back(command);
            }
        }

        if (commands.size() < 2)
        {
            printError("Invalid pipe command");
            return;
        }

        // For simplicity, we'll just execute the first command and show a message
        // A full implementation would require complex process chaining
        setConsoleColor(Color::YELLOW);
        std::cout << "Pipe operations detected. Executing first command only.\n";
        std::cout << "Full pipe support requires advanced process management.\n";
        setConsoleColor(Color::WHITE);

        processCommand(commands[0]);
    }

    void processRedirectionCommand(const std::string &input)
    {
        setConsoleColor(Color::YELLOW);
        std::cout << "Redirection operations detected.\n";
        std::cout << "Full redirection support requires advanced file handle management.\n";
        std::cout << "Executing command without redirection.\n";
        setConsoleColor(Color::WHITE);

        // Extract the command part (before redirection operators)
        std::string command = input;
        size_t redirect_pos = command.find_first_of("<>");
        if (redirect_pos != std::string::npos)
        {
            command = command.substr(0, redirect_pos);
            // Trim whitespace
            command.erase(command.find_last_not_of(" \t") + 1);
        }

        processCommand(command);
    }

    void handleExit()
    {
        setConsoleColor(Color::YELLOW);
        std::cout << "Exiting MyShell...\n";
        running = false;
    }

    void handleChangeDirectory(const std::vector<std::string> &tokens)
    {
        if (tokens.size() < 2)
        {
            printError("Usage: cd <directory>");
            return;
        }

        std::string newPath = tokens[1];

        // Handle special cases
        if (newPath == "~" || newPath == "%USERPROFILE%")
        {
            char userProfile[MAX_PATH];
            DWORD size = GetEnvironmentVariableA("USERPROFILE", userProfile, MAX_PATH);
            if (size > 0 && size < MAX_PATH)
            {
                newPath = std::string(userProfile);
            }
        }
        else if (newPath == "..")
        {
            // Go to parent directory
            size_t lastSlash = currentDirectory.find_last_of("\\/");
            if (lastSlash != std::string::npos && lastSlash > 0)
            {
                newPath = currentDirectory.substr(0, lastSlash);
            }
            else
            {
                newPath = currentDirectory; // Stay in current if can't go up
            }
        }

        if (SetCurrentDirectoryA(newPath.c_str()))
        {
            updateCurrentDirectory();
            setConsoleColor(Color::GREEN);
            std::cout << "Changed directory to: " << currentDirectory << "\n";
            setConsoleColor(Color::WHITE);
        }
        else
        {
            printError("Directory not found: " + newPath);
        }
    }

    void handleHelp()
    {
        setConsoleColor(Color::CYAN);
        std::cout << "\n=== MyShell Help ===\n";
        setConsoleColor(Color::WHITE);
        std::cout << "Built-in commands:\n";
        std::cout << "  cd <directory>  - Change current directory\n";
        std::cout << "  exit            - Exit the shell\n";
        std::cout << "  help            - Show this help message\n";
        std::cout << "  cls/clear       - Clear the screen\n";
        std::cout << "  pwd             - Print working directory\n";
        std::cout << "  dir/ls [path]   - List directory contents\n";
        std::cout << "\nSpecial features:\n";
        std::cout << "  - Quoted arguments support\n";
        std::cout << "  - Basic pipe detection (|)\n";
        std::cout << "  - Basic redirection detection (>, <)\n";
        std::cout << "  - External command execution\n";
        std::cout << "  - Colored output\n\n";
    }

    void handleClear()
    {
        system("cls");
    }

    void handlePrintWorkingDirectory()
    {
        setConsoleColor(Color::GREEN);
        std::cout << currentDirectory << "\n";
        setConsoleColor(Color::WHITE);
    }

    void handleListDirectory(const std::vector<std::string> &tokens)
    {
        std::string path = (tokens.size() > 1) ? tokens[1] : ".";

        // Ensure path ends with \* for FindFirstFile
        std::string searchPath = path;
        if (searchPath.back() != '\\' && searchPath.back() != '/')
        {
            searchPath += "\\";
        }
        searchPath += "*";

        WIN32_FIND_DATAA findData;
        HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findData);

        if (hFind == INVALID_HANDLE_VALUE)
        {
            printError("Cannot access directory: " + path);
            return;
        }

        do
        {
            // Skip . and .. entries
            if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0)
                continue;

            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                setConsoleColor(Color::BLUE);
                std::cout << "[DIR]  ";
            }
            else
            {
                setConsoleColor(Color::WHITE);
                std::cout << "[FILE] ";
            }
            std::cout << findData.cFileName << "\n";
        } while (FindNextFileA(hFind, &findData));

        FindClose(hFind);
        setConsoleColor(Color::WHITE);
    }

    void executeExternalCommand(const std::vector<std::string> &tokens)
    {
        if (tokens.empty())
        {
            return;
        }

        // Build command line
        std::string commandLine;
        for (size_t i = 0; i < tokens.size(); ++i)
        {
            if (i > 0)
                commandLine += " ";

            // Add quotes if the token contains spaces
            if (tokens[i].find(' ') != std::string::npos)
            {
                commandLine += "\"" + tokens[i] + "\"";
            }
            else
            {
                commandLine += tokens[i];
            }
        }

        // Convert to wide string for CreateProcess
        std::wstring wCommandLine(commandLine.begin(), commandLine.end());

        STARTUPINFOW si = {};
        PROCESS_INFORMATION pi = {};
        si.cb = sizeof(si);

        // Create the process
        if (CreateProcessW(
                nullptr,          // lpApplicationName
                &wCommandLine[0], // lpCommandLine
                nullptr,          // lpProcessAttributes
                nullptr,          // lpThreadAttributes
                FALSE,            // bInheritHandles
                0,                // dwCreationFlags
                nullptr,          // lpEnvironment
                nullptr,          // lpCurrentDirectory
                &si,              // lpStartupInfo
                &pi               // lpProcessInformation
                ))
        {
            // Wait for the process to complete
            WaitForSingleObject(pi.hProcess, INFINITE);

            // Get exit code
            DWORD exitCode;
            GetExitCodeProcess(pi.hProcess, &exitCode);

            if (exitCode != 0)
            {
                setConsoleColor(Color::YELLOW);
                std::cout << "Process exited with code: " << exitCode << "\n";
                setConsoleColor(Color::WHITE);
            }

            // Clean up
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }
        else
        {
            // If CreateProcess fails, try ShellExecute
            std::wstring wCommand(tokens[0].begin(), tokens[0].end());
            std::wstring wParams;

            // Build parameters string
            for (size_t i = 1; i < tokens.size(); ++i)
            {
                if (i > 1)
                    wParams += L" ";
                std::wstring wToken(tokens[i].begin(), tokens[i].end());
                if (tokens[i].find(' ') != std::string::npos)
                {
                    wParams += L"\"" + wToken + L"\"";
                }
                else
                {
                    wParams += wToken;
                }
            }

            HINSTANCE result = ShellExecuteW(
                nullptr,                                     // hwnd
                L"open",                                     // lpOperation
                wCommand.c_str(),                            // lpFile
                wParams.empty() ? nullptr : wParams.c_str(), // lpParameters
                nullptr,                                     // lpDirectory
                SW_SHOW                                      // nShowCmd
            );

            if (reinterpret_cast<intptr_t>(result) <= 32)
            {
                printError("Command not found or failed to execute: " + tokens[0]);
                setConsoleColor(Color::YELLOW);
                std::cout << "Try using the full path to the executable.\n";
                setConsoleColor(Color::WHITE);
            }
        }
    }

    void printError(const std::string &message)
    {
        setConsoleColor(Color::RED);
        std::cout << "Error: " << message << "\n";
        setConsoleColor(Color::WHITE);
    }
};

int main()
{
    try
    {
        MyShell shell;
        shell.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
