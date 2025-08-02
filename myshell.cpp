#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <memory>
#include <map>
#include <functional>
#include <random>
#include <ctime>

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
    std::map<std::string, std::function<void()>> customCommands;
    std::mt19937 rng;

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
    MyShell() : running(true), rng(static_cast<unsigned>(std::time(nullptr)))
    {
        // Get console handle for colored output
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        // Get current working directory
        updateCurrentDirectory();

        // Set console to handle UTF-8 properly
        SetConsoleOutputCP(CP_UTF8);

        // Initialize custom commands
        initializeCustomCommands();
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
        std::cout << "===========================================\n";
        std::cout << "Welcome to SwapShell v1.0 🚀\n";
        setConsoleColor(Color::MAGENTA);
        std::cout << "Crafted with ❤️  by Swapnil Chhibber\n";
        setConsoleColor(Color::YELLOW);
        std::cout << "Final Year Computer Engineering Student\n";
        std::cout << "Thapar Institute of Engineering & Technology\n";
        setConsoleColor(Color::CYAN);
        std::cout << "===========================================\n";
        setConsoleColor(Color::YELLOW);
        std::cout << "Type 'help' for available commands\n\n";
        setConsoleColor(Color::WHITE);
    }

    void printExitMessage()
    {
        setConsoleColor(Color::CYAN);
        std::cout << "\nThank you for using SwapShell! 🚀\n";
        std::cout << "Keep coding and stay awesome! 💪\n";
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
        setConsoleColor(Color::CYAN);
        std::cout << "Swap🐚> ";
        setConsoleColor(Color::WHITE);
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
        else if (command == "dir")
        {
            handleListDirectory(tokens);
        }
        else if (customCommands.find(command) != customCommands.end())
        {
            // Execute custom SwapShell command
            customCommands[command]();
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
        std::cout << "\n=== SwapShell Help ===\n";
        setConsoleColor(Color::WHITE);
        std::cout << "Built-in commands:\n";
        std::cout << "  cd <directory>  - Change current directory\n";
        std::cout << "  exit            - Exit the shell\n";
        std::cout << "  help            - Show this help message\n";
        std::cout << "  cls/clear       - Clear the screen\n";
        std::cout << "  pwd             - Print working directory\n";
        std::cout << "  dir/ls [path]   - List directory contents\n";
        
        setConsoleColor(Color::YELLOW);
        std::cout << "\nSwapShell Special Commands:\n";
        setConsoleColor(Color::WHITE);
        std::cout << "  coffee          - Get coffee recommendations ☕\n";
        std::cout << "  jaggi           - ASCII coffee art from Jaggi\n";
        std::cout << "  quote           - Random inspirational quote\n";
        std::cout << "  whoami          - About Swapnil\n";
        std::cout << "  mood            - Random mood message\n";
        std::cout << "  chai            - Chai vs coffee debate\n";
        std::cout << "  hi/hello        - Friendly greeting\n";
        std::cout << "  date            - Quirky date display\n";
        std::cout << "  sneaker         - Sneaker drop check\n";
        std::cout << "  swapgpt         - Fake AI assistant\n";
        std::cout << "  thanks          - Acknowledgment\n";
        std::cout << "  bug             - Random bug names\n";
        std::cout << "  devtip          - Coding wisdom\n";
        std::cout << "  sudo            - Power check\n";
        std::cout << "  sing            - Musical interlude\n";
        std::cout << "  swapify         - Music player simulation\n";
        
        setConsoleColor(Color::GREEN);
        std::cout << "\nSpecial features:\n";
        std::cout << "  - Quoted arguments support\n";
        std::cout << "  - Basic pipe detection (|)\n";
        std::cout << "  - Basic redirection detection (>, <)\n";
        std::cout << "  - External command execution\n";
        std::cout << "  - Colored output with personality 🎨\n\n";
        setConsoleColor(Color::WHITE);
    }

    void handleClear()
    {
        system("cls");
        setConsoleColor(Color::CYAN);
        std::cout << "Let's start fresh ✨\n\n";
        setConsoleColor(Color::WHITE);
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

    void initializeCustomCommands()
    {
        customCommands["coffee"] = [this]() { handleCoffee(); };
        customCommands["jaggi"] = [this]() { handleJaggi(); };
        customCommands["quote"] = [this]() { handleQuote(); };
        customCommands["whoami"] = [this]() { handleWhoAmI(); };
        customCommands["mood"] = [this]() { handleMood(); };
        customCommands["chai"] = [this]() { handleChai(); };
        customCommands["hi"] = [this]() { handleGreeting(); };
        customCommands["hello"] = [this]() { handleGreeting(); };
        customCommands["date"] = [this]() { handleDate(); };
        customCommands["sneaker"] = [this]() { handleSneaker(); };
        customCommands["swapgpt"] = [this]() { handleSwapGPT(); };
        customCommands["thanks"] = [this]() { handleThanks(); };
        customCommands["bug"] = [this]() { handleBug(); };
        customCommands["devtip"] = [this]() { handleDevTip(); };
        customCommands["ls"] = [this]() { handleLinuxLS(); };
        customCommands["sudo"] = [this]() { handleSudo(); };
        customCommands["sing"] = [this]() { handleSing(); };
        customCommands["swapify"] = [this]() { handleSwapify(); };
    }

    void handleCoffee()
    {
        setConsoleColor(Color::YELLOW);
        std::cout << "☕ Jaggi serves the best cold coffee. Swap recommends it!\n";
        setConsoleColor(Color::WHITE);
    }

    void handleJaggi()
    {
        setConsoleColor(Color::YELLOW);
        std::cout << "    (\n";
        std::cout << "     )\n";
        std::cout << "  +---------+\n";
        std::cout << "  |  JAGGI  |\n";
        std::cout << "  |  COFFEE |\n";
        std::cout << "  +---------+\n";
        std::cout << "      ___\n";
        std::cout << "     /   \\\n";
        std::cout << "    /_____\\\n\n";
        setConsoleColor(Color::CYAN);
        std::cout << "\"Find this joy at Jaggi, Patiala's legendary sip stop.\"\n";
        setConsoleColor(Color::WHITE);
    }

    void handleQuote()
    {
        std::vector<std::string> quotes = {
            "\"Programs must be written for people to read, and only incidentally for machines to execute.\" – Harold Abelson",
            "\"The best error message is the one that never shows up.\" – Thomas Fuchs",
            "\"Code is like humor. When you have to explain it, it's bad.\" – Cory House",
            "\"First, solve the problem. Then, write the code.\" – John Johnson",
            "\"Experience is the name everyone gives to their mistakes.\" – Oscar Wilde",
            "\"In order to be irreplaceable, one must always be different.\" – Coco Chanel",
            "\"Java is to JavaScript what car is to Carpet.\" – Chris Heilmann",
            "\"Walking on water and developing software from a specification are easy if both are frozen.\" – Edward V. Berard",
            "\"The computer was born to solve problems that did not exist before.\" – Bill Gates",
            "\"Talk is cheap. Show me the code.\" – Linus Torvalds"
        };

        std::uniform_int_distribution<> dist(0, quotes.size() - 1);
        int index = dist(rng);

        setConsoleColor(Color::MAGENTA);
        std::cout << "💬 " << quotes[index] << "\n";
        setConsoleColor(Color::WHITE);
    }

    void handleWhoAmI()
    {
        setConsoleColor(Color::CYAN);
        std::cout << "🔥 Swapnil Chhibber, Future SDE, Sneakerhead & Problem-Solving Ninja\n";
        setConsoleColor(Color::YELLOW);
        std::cout << "Currently crafting code at Thapar Institute 🎓\n";
        setConsoleColor(Color::WHITE);
    }

    void handleMood()
    {
        std::vector<std::string> moods = {
            "Running on Coffee ☕",
            "Feeling Debuggy 🐞",
            "Zen Mode Activated ✨",
            "Compiling Thoughts 🤔",
            "Error 418: I'm a teapot 🫖",
            "Optimizing Life.exe 🔧",
            "Stack Overflow Survivor 📚",
            "Syntax Error in Reality 🌀",
            "Powered by Caffeine & Dreams ⚡",
            "404: Sleep Not Found 😴"
        };

        std::uniform_int_distribution<> dist(0, moods.size() - 1);
        int index = dist(rng);

        setConsoleColor(Color::GREEN);
        std::cout << "Current Mood: " << moods[index] << "\n";
        setConsoleColor(Color::WHITE);
    }

    void handleChai()
    {
        setConsoleColor(Color::YELLOW);
        std::cout << "🍵 Masala chai > caffeine pills. Fight me.\n";
        setConsoleColor(Color::CYAN);
        std::cout << "The perfect blend of spices and caffeine for coding sessions! 💪\n";
        setConsoleColor(Color::WHITE);
    }

    void handleGreeting()
    {
        setConsoleColor(Color::GREEN);
        std::cout << "Hey! You're talking to SwapShell. Let's get stuff done 💪\n";
        setConsoleColor(Color::YELLOW);
        std::cout << "Ready to tackle some code? 🚀\n";
        setConsoleColor(Color::WHITE);
    }

    void handleDate()
    {
        SYSTEMTIME st;
        GetLocalTime(&st);
        
        setConsoleColor(Color::CYAN);
        std::cout << "📅 Today is " << st.wDay << "/" << st.wMonth << "/" << st.wYear << "\n";
        setConsoleColor(Color::YELLOW);
        std::cout << "Hope you're killing it today! 🔥\n";
        setConsoleColor(Color::WHITE);
    }

    void handleSneaker()
    {
        setConsoleColor(Color::MAGENTA);
        std::cout << "👟 Sneaker drop today? Swap's checking Hypebeast...\n";
        setConsoleColor(Color::YELLOW);
        std::cout << "Current rotation: Air Jordans, Yeezys, and coding socks 🧦\n";
        setConsoleColor(Color::WHITE);
    }

    void handleSwapGPT()
    {
        std::vector<std::string> responses = {
            "SwapGPT: You should get some rest 😴",
            "SwapGPT: Have you tried turning it off and on again? 🔄",
            "SwapGPT: The answer is 42, but what was the question? 🤖",
            "SwapGPT: More coffee = better code. Science! ☕",
            "SwapGPT: Error 404: Motivation not found. Try coffee.exe 🚀",
            "SwapGPT: Remember: Real programmers count from 0 📊",
            "SwapGPT: Stack Overflow is your friend, not your enemy 📚"
        };

        std::uniform_int_distribution<> dist(0, responses.size() - 1);
        int index = dist(rng);

        setConsoleColor(Color::BLUE);
        std::cout << "🤖 " << responses[index] << "\n";
        setConsoleColor(Color::WHITE);
    }

    void handleThanks()
    {
        setConsoleColor(Color::GREEN);
        std::cout << "✨ Gratitude is acknowledged. Now go build something cool!\n";
        setConsoleColor(Color::CYAN);
        std::cout << "Remember: Every expert was once a beginner 🌱\n";
        setConsoleColor(Color::WHITE);
    }

    void handleBug()
    {
        std::vector<std::string> bugNames = {
            "SegFaultzilla spotted 🦖",
            "404: Sanity Not Found 🔍",
            "NullPointerException-osaurus 🦕",
            "The Infinite Loop Monster 🌀",
            "Captain Memory Leak 💧",
            "Buffer Overflow Beast 📊",
            "The Syntax Error Goblin 👹",
            "Race Condition Racer 🏎️",
            "Deadlock Dragon 🐉",
            "Stack Overflow Kraken 🐙"
        };

        std::uniform_int_distribution<> dist(0, bugNames.size() - 1);
        int index = dist(rng);

        setConsoleColor(Color::RED);
        std::cout << "🐛 Bug Alert: " << bugNames[index] << "\n";
        setConsoleColor(Color::YELLOW);
        std::cout << "Time to debug! Remember: It's not a bug, it's a feature 😉\n";
        setConsoleColor(Color::WHITE);
    }

    void handleDevTip()
    {
        std::vector<std::string> tips = {
            "Always write code like the person maintaining it is a psychopath.",
            "Comment your code like you're explaining it to your past self.",
            "If debugging is the process of removing bugs, then programming must be the process of putting them in.",
            "The best code is no code at all. The second best is code you don't have to maintain.",
            "Premature optimization is the root of all evil (or at least most of it) in programming.",
            "Code never lies, comments sometimes do.",
            "The only way to learn a new programming language is by writing programs in it.",
            "Simplicity is the ultimate sophistication in code.",
            "Make it work, make it right, make it fast – in that order.",
            "Good code is its own best documentation."
        };

        std::uniform_int_distribution<> dist(0, tips.size() - 1);
        int index = dist(rng);

        setConsoleColor(Color::CYAN);
        std::cout << "💡 Dev Tip: " << tips[index] << "\n";
        setConsoleColor(Color::WHITE);
    }

    void handleLinuxLS()
    {
        setConsoleColor(Color::YELLOW);
        std::cout << "😎 Wrong OS buddy. Try 'dir' instead!\n";
        setConsoleColor(Color::CYAN);
        std::cout << "Or maybe it's time to dual boot? 🐧\n";
        setConsoleColor(Color::WHITE);
    }

    void handleSudo()
    {
        setConsoleColor(Color::RED);
        std::cout << "🧙 You have no power here!\n";
        setConsoleColor(Color::YELLOW);
        std::cout << "This is Windows, not your Linux playground 😄\n";
        setConsoleColor(Color::WHITE);
    }

    void handleSing()
    {
        setConsoleColor(Color::MAGENTA);
        std::cout << "🎵 Baby Shark doo doo doo doo doo doo\n";
        std::cout << "🎵 Baby Shark doo doo doo doo doo doo\n";
        std::cout << "🎵 Baby Shark doo doo doo doo doo doo\n";
        std::cout << "🎵 Baby Shark! 🦈\n";
        setConsoleColor(Color::YELLOW);
        std::cout << "(Sorry, not sorry for the earworm 😈)\n";
        setConsoleColor(Color::WHITE);
    }

    void handleSwapify()
    {
        std::vector<std::string> songs = {
            "Lo-fi for Coding - 1:23/2:47",
            "Synthwave Programming Mix - 45:32/1:23:45",
            "Coffee Shop Jazz - 12:34/35:20",
            "Focus Flow State - 2:15/4:30",
            "Midnight Coding Session - 8:42/15:33",
            "Retro Gaming Beats - 3:21/6:45",
            "Productive Vibes Only - 5:55/12:10"
        };

        std::uniform_int_distribution<> dist(0, songs.size() - 1);
        int index = dist(rng);

        setConsoleColor(Color::GREEN);
        std::cout << "🎧 SwapSpotify: Now playing: " << songs[index] << "\n";
        setConsoleColor(Color::CYAN);
        std::cout << "🔀 Shuffle: ON | 🔁 Repeat: OFF | 🔊 Volume: Perfect for coding\n";
        setConsoleColor(Color::WHITE);
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
