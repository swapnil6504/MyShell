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
        std::cout << "===========================================\n";
        std::cout << "Welcome to MyShell v1.0 🚀\n";
        std::cout << "Crafted with ❤️ by Swapnil Chhibber\n";
        std::cout << "Final Year Computer Engineering Student\n";
        std::cout << "Thapar Institute of Engineering & Technology\n";
        std::cout << "===========================================\n";
        setConsoleColor(Color::YELLOW);
        std::cout << "Ready to code, debug, and conquer! 💪\n";
        std::cout << "Type 'help' for commands or try 'coffee' for wisdom ☕\n\n";
        setConsoleColor(Color::WHITE);
    }

    void printExitMessage()
    {
        setConsoleColor(Color::CYAN);
        std::cout << "\nThanks for using SwapShell! 🚀\n";
        std::cout << "Built with ❤️ by Swapnil Chhibber\n";
        std::cout << "Keep coding and stay awesome! ✨\n";
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
        std::cout << "MyShell> ";
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
        else if (command == "about" || command == "author")
        {
            handleAbout();
        }
        else if (command == "coffee")
        {
            handleCoffee();
        }
        else if (command == "jaggi")
        {
            handleJaggi();
        }
        else if (command == "quote")
        {
            handleQuote();
        }
        else if (command == "whoami")
        {
            handleWhoami();
        }
        else if (command == "mood")
        {
            handleMood();
        }
        else if (command == "chai")
        {
            handleChai();
        }
        else if (command == "hi" || command == "hello")
        {
            handleGreeting();
        }
        else if (command == "date")
        {
            handleDate();
        }
        else if (command == "sneaker")
        {
            handleSneaker();
        }
        else if (command == "swapgpt")
        {
            handleSwapGPT();
        }
        else if (command == "thanks")
        {
            handleThanks();
        }
        else if (command == "bug")
        {
            handleBug();
        }
        else if (command == "devtip")
        {
            handleDevTip();
        }
        else if (command == "ls")
        {
            handleLsJoke();
        }
        else if (command == "sudo")
        {
            handleSudoJoke();
        }
        else if (command == "sing")
        {
            handleSing();
        }
        else if (command == "swapify")
        {
            handleSwapify();
        }
        else if (command == "joke")
        {
            handleJoke();
        }
        else if (command == "thapar")
        {
            handleThapar();
        }
        else if (command == "motivate" || command == "quote")
        {
            handleMotivate();
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

    void handleJaggi()
    {
        setConsoleColor(Color::CYAN);
        std::cout << "🏆 Tribute to Jaggi Uncle (The Coffee Legend):\n";
        setConsoleColor(Color::WHITE);
        std::cout << R"(
      ╔══════════════════════╗
      ║     ☕ JAGGI ☕      ║
      ║   Cold Coffee King   ║
      ║  Making dreams come  ║
      ║   true, one cup at   ║
      ║      a time! 👑      ║
      ╚══════════════════════╝
)" << std::endl;
        std::cout << "The man, the myth, the coffee legend! 🙌\n\n";
    }

    void handleQuote()
    {
        setConsoleColor(Color::GREEN);
        std::cout << "💡 Daily Inspiration:\n";
        setConsoleColor(Color::WHITE);

        std::vector<std::string> quotes = {
            "\"Code is poetry written in logic.\" - Swapnil",
            "\"Every bug is just an undiscovered feature waiting to happen.\"",
            "\"Coffee first, code second, debug third.\"",
            "\"The best error message is the one that never shows up.\"",
            "\"Programming is the art of telling a computer what to do.\"",
            "\"In code we trust, in comments we verify.\"",
            "\"A day without learning is a day wasted.\"",
            "\"Think twice, code once, debug never.\"",
            "\"Great software is built by great teams, fueled by great coffee.\""};

        int index = rand() % quotes.size();
        std::cout << quotes[index] << "\n\n";
    }

    void handleWhoami()
    {
        setConsoleColor(Color::MAGENTA);
        std::cout << "🚀 Meet the Developer:\n";
        setConsoleColor(Color::WHITE);
        std::cout << "Name: Swapnil\n";
        std::cout << "Role: Code Magician & Coffee Enthusiast ☕\n";
        std::cout << "Motto: 'Building software that matters, one line at a time'\n";
        std::cout << "Specialty: C++, Creative Solutions, and Cold Coffee Advocacy\n";
        std::cout << "Current Status: Bringing personality to terminals everywhere! 🎭\n\n";
    }

    void handleMood()
    {
        setConsoleColor(Color::YELLOW);
        std::cout << "🎭 Swapnil's Current Coding Mood:\n";
        setConsoleColor(Color::WHITE);

        std::vector<std::string> moods = {
            "🔥 On fire! Code is flowing like water!",
            "☕ Caffeinated and ready to debug the world!",
            "🎯 Laser-focused on solving complex problems",
            "🎨 In creative mode - architecting something beautiful",
            "🧘 Zen coding state - one with the algorithm",
            "🚀 Rocket mode engaged - productivity at maximum!",
            "🎵 Vibing with the code rhythm",
            "⚡ Electric! Every keystroke is pure energy!"};

        int index = rand() % moods.size();
        std::cout << moods[index] << "\n\n";
    }

    void handleChai()
    {
        setConsoleColor(Color::RED);
        std::cout << "🫖 Hot Take on Chai:\n";
        setConsoleColor(Color::WHITE);
        std::cout << "Look, I respect chai culture, but...\n";
        std::cout << "Cold coffee >>> Chai (fight me! ☕)\n";
        std::cout << "Though I admit, masala chai has its moments... 🤷‍♂️\n";
        std::cout << "But for coding marathons? Cold coffee all the way! 💪\n\n";
    }

    void handleGreeting()
    {
        setConsoleColor(Color::GREEN);
        std::cout << "👋 Hey there, awesome human!\n";
        setConsoleColor(Color::WHITE);
        std::cout << "Welcome to SwapShell - where commands meet personality!\n";
        std::cout << "Ready to explore some quirky features? Type 'help' to get started! 🚀\n\n";
    }

    void handleDate()
    {
        setConsoleColor(Color::YELLOW);
        std::cout << "📅 Today's Date & Time:\n";
        setConsoleColor(Color::WHITE);

        SYSTEMTIME st;
        GetLocalTime(&st);

        std::cout << "Date: " << st.wDay << "/" << st.wMonth << "/" << st.wYear << "\n";
        std::cout << "Time: " << st.wHour << ":" << (st.wMinute < 10 ? "0" : "") << st.wMinute << ":" << (st.wSecond < 10 ? "0" : "") << st.wSecond << "\n";
        setConsoleColor(Color::GREEN);
        std::cout << "Hope you're killing it today! 💪\n\n";
        setConsoleColor(Color::WHITE);
    }

    void handleSneaker()
    {
        setConsoleColor(Color::MAGENTA);
        std::cout << "👟 Sneaker Drop Alert:\n";
        setConsoleColor(Color::WHITE);

        std::vector<std::string> sneakerFacts = {
            "Latest drop: Air Max 97 'Silver Bullet' - Classic never dies! 🔥",
            "Jordan 1 High OG 'Chicago' - The GOAT of sneakers! 🐐",
            "Yeezy 350 V2 'Static' - Comfort meets style! ⚡",
            "Off-White x Nike - Virgil's legacy lives on! 👑",
            "New Balance 990v3 'Grey' - The dad shoe that's actually fire! 😎"};

        int index = rand() % sneakerFacts.size();
        std::cout << sneakerFacts[index] << "\n";
        std::cout << "Remember: Sneakers are code for your feet! 👟💻\n\n";
    }

    void handleSwapGPT()
    {
        setConsoleColor(Color::CYAN);
        std::cout << "🤖 SwapGPT v1.0 Initializing...\n";
        setConsoleColor(Color::WHITE);
        std::cout << "[████████████████████] 100%\n";
        std::cout << "SwapGPT: Hello! I'm the shell's AI assistant!\n";
        std::cout << "SwapGPT: I can help with... uh... making coffee recommendations?\n";
        std::cout << "SwapGPT: And telling you that cold coffee > hot coffee! ☕\n";
        std::cout << "SwapGPT: (Disclaimer: I'm just a function in disguise 😉)\n\n";
    }

    void handleDevTip()
    {
        setConsoleColor(Color::YELLOW);
        std::cout << "💡 Swapnil's Dev Tip of the Day:\n";
        setConsoleColor(Color::WHITE);

        std::vector<std::string> tips = {
            "Always comment your code - your future self will thank you!",
            "const > let > var - Choose your JavaScript variables wisely!",
            "Test early, test often, test with coffee! ☕",
            "Git commit messages should tell a story, not just say 'fix'",
            "Rubber duck debugging works - talk to your coffee mug if needed!",
            "Take breaks! Your best solutions come when you step away.",
            "Learn one new thing every day - consistency beats intensity!",
            "Code reviews are love letters to your teammates."};

        int index = rand() % tips.size();
        std::cout << tips[index] << "\n\n";
    }

    void handleBug()
    {
        setConsoleColor(Color::RED);
        std::cout << "🐛 Today's Bug Name Generator:\n";
        setConsoleColor(Color::WHITE);

        std::vector<std::string> adjectives = {"Sneaky", "Invisible", "Quantum", "Ninja", "Phantom", "Mysterious", "Dancing", "Laughing"};
        std::vector<std::string> nouns = {"SegFault", "NullPointer", "MemoryLeak", "BufferOverflow", "RaceCondition", "DeadLock", "StackOverflow", "HeapCorruption"};

        int adjIndex = rand() % adjectives.size();
        int nounIndex = rand() % nouns.size();

        std::cout << "Meet: " << adjectives[adjIndex] << " " << nouns[nounIndex] << "! 🎭\n";
        std::cout << "Approach with caution and plenty of coffee! ☕\n\n";
    }

    void handleThanks()
    {
        setConsoleColor(Color::GREEN);
        std::cout << "🙏 You're very welcome!\n";
        setConsoleColor(Color::WHITE);
        std::cout << "Thanks for using SwapShell - you make all this coding worthwhile!\n";
        std::cout << "Remember: You're awesome, and your code is too! 🌟\n";
        std::cout << "Now go forth and create something amazing! 🚀\n\n";
    }

    void handleSudoJoke()
    {
        setConsoleColor(Color::RED);
        std::cout << "🚫 sudo: Permission denied!\n";
        setConsoleColor(Color::WHITE);
        std::cout << "Nice try, but this is Windows territory! 🪟\n";
        std::cout << "Here we use 'Run as Administrator' like civilized people! 😄\n";
        std::cout << "sudo make me a sandwich? How about 'coffee first'! ☕\n\n";
    }

    void handleLsJoke()
    {
        setConsoleColor(Color::YELLOW);
        std::cout << "🐧 ls: command not found!\n";
        setConsoleColor(Color::WHITE);
        std::cout << "Wrong penguin house, buddy! 🐧\n";
        std::cout << "You're in Windows land - try 'dir' instead! 🪟\n";
        std::cout << "But I appreciate the Linux spirit! 💚\n\n";
    }

    void handleSing()
    {
        setConsoleColor(Color::MAGENTA);
        std::cout << "🎵 SwapShell Serenade:\n";
        setConsoleColor(Color::WHITE);
        std::cout << "♪ Code, code, code your app ♪\n";
        std::cout << "♪ Gently down the stream ♪\n";
        std::cout << "♪ Merrily, merrily, merrily, merrily ♪\n";
        std::cout << "♪ Life is but a dream... of clean code! ♪\n";
        std::cout << "*Takes a bow* 🎭 Thank you, thank you! ☕\n\n";
    }

    void handleSwapify()
    {
        setConsoleColor(Color::GREEN);
        std::cout << "🎧 Welcome to Swapify - Premium Music Experience!\n";
        setConsoleColor(Color::WHITE);
        std::cout << "🎵 Now playing: 'The Algorithm Blues' by Code Monks\n";
        std::cout << "⏮️  ⏸️  ⏭️  🔄  📶\n";
        std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ 3:42 / 4:20\n";
        std::cout << "Up next: 'Segmentation Fault Samba' 🎶\n";
        std::cout << "Premium feature: No ads, just pure coding vibes! ☕\n\n";
    }

    void handleHelp()
    {
        setConsoleColor(Color::CYAN);
        std::cout << "\n=== SwapShell Command Center ===\n";
        setConsoleColor(Color::WHITE);
        std::cout << "Standard commands:\n";
        std::cout << "  cd <directory>  - Change current directory\n";
        std::cout << "  exit            - Exit the shell\n";
        std::cout << "  help            - Show this help message\n";
        std::cout << "  about/author    - Show author information\n";
        std::cout << "  cls/clear       - Clear the screen\n";
        std::cout << "  pwd             - Print working directory\n";
        std::cout << "  dir             - List directory contents\n";

        setConsoleColor(Color::YELLOW);
        std::cout << "\n☕ Swapnil's Signature Commands:\n";
        setConsoleColor(Color::WHITE);
        std::cout << "  coffee          - Best cold coffee wisdom\n";
        std::cout << "  jaggi           - ASCII coffee art & Jaggi tribute\n";
        std::cout << "  chai            - Hot take on masala chai\n";
        std::cout << "  quote           - Random inspirational quotes\n";
        std::cout << "  whoami          - Swapnil's introduction\n";
        std::cout << "  mood            - Current coding mood\n";
        std::cout << "  hi/hello        - Friendly greeting\n";
        std::cout << "  date            - Quirky formatted system date\n";
        std::cout << "  sneaker         - Sneaker drop check\n";
        std::cout << "  devtip          - Random coding wisdom\n";
        std::cout << "  bug             - Funny bug names\n";
        std::cout << "  thanks          - Gratitude acknowledgment\n";
        std::cout << "  joke            - Programming jokes\n";
        std::cout << "  thapar          - About Thapar Institute\n";
        std::cout << "  motivate        - Motivational quotes\n";

        setConsoleColor(Color::MAGENTA);
        std::cout << "\n🎭 Easter Eggs & Fun:\n";
        setConsoleColor(Color::WHITE);
        std::cout << "  swapgpt         - AI simulation\n";
        std::cout << "  sudo            - No power here!\n";
        std::cout << "  ls              - Wrong OS buddy\n";
        std::cout << "  sing            - Musical interlude\n";
        std::cout << "  swapify         - Music player simulation\n";

        setConsoleColor(Color::GREEN);
        std::cout << "\nBuilt with C++17, Windows API, and endless ☕\n";
        std::cout << "Each command crafted with Swapnil's personality! 🚀\n\n";
        setConsoleColor(Color::WHITE);
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

    void handleAbout()
    {
        setConsoleColor(Color::CYAN);
        std::cout << "\n=== About SwapShell ===\n";
        setConsoleColor(Color::MAGENTA);
        std::cout << "Author: Swapnil Chhibber\n";
        std::cout << "Student: Final Year Computer Engineering\n";
        std::cout << "University: Thapar Institute of Engineering & Technology\n";
        setConsoleColor(Color::YELLOW);
        std::cout << "Location: Patiala, Punjab, India\n";
        setConsoleColor(Color::GREEN);
        std::cout << "\n\"Building the future, one line of code at a time! 💻✨\"\n";
        setConsoleColor(Color::WHITE);
        std::cout << "\nThis shell was built with C++17, Windows API, and lots of ☕\n\n";
    }

    void handleCoffee()
    {
        setConsoleColor(Color::YELLOW);
        std::cout << "☕ Jaggi serves the best cold coffee! ☕\n";
        setConsoleColor(Color::GREEN);
        std::cout << "Trust me, I'm a computer engineering student.\n";
        std::cout << "Cold coffee is basically liquid motivation! 💪\n";
        setConsoleColor(Color::CYAN);
        std::cout << "Fun fact: This shell was coded with 73% cold coffee in my system! 😄\n\n";
        setConsoleColor(Color::WHITE);
    }

    void handleJoke()
    {
        static int jokeIndex = 0;
        const std::vector<std::string> jokes = {
            "Why do programmers prefer dark mode? Because light attracts bugs! 🐛",
            "How many programmers does it take to change a light bulb? None, that's a hardware problem! 💡",
            "Why do Java developers wear glasses? Because they don't C# ! 👓",
            "A SQL query walks into a bar, walks up to two tables and asks: 'Can I join you?' 🍺",
            "There are only 10 types of people: those who understand binary and those who don't! 1010",
            "Why did the programmer quit his job? He didn't get arrays! 📊",
            "What's a computer's favorite beat? An algo-rhythm! 🎵"};

        setConsoleColor(Color::YELLOW);
        std::cout << "😂 Swapnil's Programming Joke #" << (jokeIndex + 1) << ":\n";
        setConsoleColor(Color::GREEN);
        std::cout << jokes[jokeIndex] << "\n\n";
        setConsoleColor(Color::WHITE);

        jokeIndex = (jokeIndex + 1) % jokes.size();
    }

    void handleThapar()
    {
        setConsoleColor(Color::BLUE);
        std::cout << "\n🏛️  Thapar Institute of Engineering & Technology 🏛️\n";
        setConsoleColor(Color::YELLOW);
        std::cout << "📍 Location: Patiala, Punjab, India\n";
        std::cout << "📅 Established: 1956\n";
        std::cout << "🎓 My Program: Computer Engineering (Final Year)\n";
        setConsoleColor(Color::GREEN);
        std::cout << "\n💡 Known for:\n";
        std::cout << "   • Excellent engineering programs\n";
        std::cout << "   • Strong industry connections\n";
        std::cout << "   • Beautiful campus in Punjab\n";
        std::cout << "   • Producing awesome engineers like me! 😎\n";
        setConsoleColor(Color::CYAN);
        std::cout << "\nProud to be a Thapar student! 🚀\n\n";
        setConsoleColor(Color::WHITE);
    }

    void handleMotivate()
    {
        static int quoteIndex = 0;
        const std::vector<std::string> quotes = {
            "\"Code is like humor. When you have to explain it, it's bad.\" - Cory House 💻",
            "\"The best error message is the one that never shows up.\" - Thomas Fuchs ✨",
            "\"Programming isn't about what you know; it's about what you can figure out.\" - Chris Pine 🧠",
            "\"Experience is the name everyone gives to their mistakes.\" - Oscar Wilde 📚",
            "\"The only way to learn a new programming language is by writing programs in it.\" - Dennis Ritchie 🔥",
            "\"Keep coding, keep learning, keep growing!\" - Swapnil Chhibber 🌱",
            "\"Coffee + Code = Magic. That's the Thapar way!\" - Swapnil's Life Philosophy ☕"};

        setConsoleColor(Color::MAGENTA);
        std::cout << "✨ Motivation from Swapnil ✨\n";
        setConsoleColor(Color::CYAN);
        std::cout << quotes[quoteIndex] << "\n";
        setConsoleColor(Color::YELLOW);
        std::cout << "\nYou've got this! Keep pushing forward! 💪🚀\n\n";
        setConsoleColor(Color::WHITE);

        quoteIndex = (quoteIndex + 1) % quotes.size();
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
