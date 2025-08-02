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
#include <emscripten.h>
#include <emscripten/bind.h>

// Web version of the shell - SwapShell with personality!
class MyShellWeb {
private:
    std::string currentDirectory;
    bool running;
    std::vector<std::string> outputBuffer;
    std::map<std::string, std::function<std::string()>> customCommands;
    std::mt19937 rng;
    
public:
    MyShellWeb() : running(true), currentDirectory("/home/user"), rng(static_cast<unsigned>(std::time(nullptr))) {
        outputBuffer.push_back("===========================================");
        outputBuffer.push_back("Welcome to SwapShell v1.0 🚀 (Web Edition)");
        outputBuffer.push_back("Crafted with ❤️ by Swapnil Chhibber");
        outputBuffer.push_back("Final Year Computer Engineering Student");
        outputBuffer.push_back("Thapar Institute of Engineering & Technology");
        outputBuffer.push_back("===========================================");
        outputBuffer.push_back("Type 'help' for available commands");
        outputBuffer.push_back("");
        
        // Initialize custom commands
        initializeCustomCommands();
    }

    std::string processCommand(const std::string& input) {
        std::vector<std::string> tokens = tokenizeCommand(input);
        
        if (tokens.empty()) {
            return "";
        }

        std::string command = tokens[0];
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);

        if (command == "help") {
            return handleHelp();
        } else if (command == "pwd") {
            return "Current directory: " + currentDirectory;
        } else if (command == "cd") {
            return handleChangeDirectory(tokens);
        } else if (command == "ls" || command == "dir") {
            return handleListDirectory();
        } else if (command == "clear" || command == "cls") {
            outputBuffer.clear();
            return "Screen cleared";
        } else if (command == "echo") {
            std::string result = "Output: ";
            for (size_t i = 1; i < tokens.size(); ++i) {
                if (i > 1) result += " ";
                result += tokens[i];
            }
            return result;
        } else if (command == "date") {
            return handleDate();
        } else if (command == "whoami") {
            return handleWhoAmI();
        } else if (customCommands.find(command) != customCommands.end()) {
            // Execute custom SwapShell command
            return customCommands[command]();
        } else if (command == "exit") {
            return "Thank you for using SwapShell Web! 🚀\\nKeep coding and stay awesome! 💪";
        } else {
            return "Error: Command '" + command + "' not found. Type 'help' for available commands.";
        }
    }

    std::string getPrompt() {
        return "Swap🐚> ";
    }

private:
    std::vector<std::string> tokenizeCommand(const std::string& command) {
        std::vector<std::string> tokens;
        std::string current_token;
        bool in_quotes = false;
        char quote_char = '\0';

        for (size_t i = 0; i < command.length(); ++i) {
            char c = command[i];

            if (!in_quotes && (c == '"' || c == '\'')) {
                in_quotes = true;
                quote_char = c;
            } else if (in_quotes && c == quote_char) {
                in_quotes = false;
                quote_char = '\0';
            } else if (!in_quotes && (c == ' ' || c == '\t')) {
                if (!current_token.empty()) {
                    tokens.push_back(current_token);
                    current_token.clear();
                }
            } else {
                current_token += c;
            }
        }

        if (!current_token.empty()) {
            tokens.push_back(current_token);
        }

        return tokens;
    }

    std::string handleHelp() {
        return R"(=== SwapShell Web Help ===
Built-in commands:
  help            - Show this help message
  pwd             - Print working directory
  cd <directory>  - Change directory (simulated)
  ls/dir          - List directory contents
  clear/cls       - Clear the screen
  echo <text>     - Echo text to output
  date            - Quirky date display
  whoami          - About Swapnil
  exit            - Exit message

SwapShell Special Commands:
  coffee          - Get coffee recommendations ☕
  jaggi           - ASCII coffee art from Jaggi
  quote           - Random inspirational quote
  mood            - Random mood message
  chai            - Chai vs coffee debate
  hi/hello        - Friendly greeting
  sneaker         - Sneaker drop check
  swapgpt         - Fake AI assistant
  thanks          - Acknowledgment
  bug             - Random bug names
  devtip          - Coding wisdom
  sudo            - Power check
  sing            - Musical interlude
  swapify         - Music player simulation

This is SwapShell Web Edition - C++ shell with personality! 🚀
The desktop version runs natively on Windows with full OS integration.)";
    }

    std::string handleChangeDirectory(const std::vector<std::string>& tokens) {
        if (tokens.size() < 2) {
            return "Error: Usage: cd <directory>";
        }

        std::string newPath = tokens[1];
        if (newPath == "..") {
            size_t lastSlash = currentDirectory.find_last_of("/");
            if (lastSlash != std::string::npos && lastSlash > 0) {
                currentDirectory = currentDirectory.substr(0, lastSlash);
            }
        } else if (newPath == "~" || newPath == "/home") {
            currentDirectory = "/home/user";
        } else {
            if (newPath[0] != '/') {
                currentDirectory += "/" + newPath;
            } else {
                currentDirectory = newPath;
            }
        }
        return "Changed directory to: " + currentDirectory;
    }

    std::string handleListDirectory() {
        return R"([DIR]  documents
[DIR]  downloads
[DIR]  projects
[FILE] myshell.cpp
[FILE] readme.txt
[FILE] demo.html

Note: This is a simulated directory listing for demonstration.)";
    }

    void initializeCustomCommands() {
        customCommands["coffee"] = [this]() { return handleCoffee(); };
        customCommands["jaggi"] = [this]() { return handleJaggi(); };
        customCommands["quote"] = [this]() { return handleQuote(); };
        customCommands["mood"] = [this]() { return handleMood(); };
        customCommands["chai"] = [this]() { return handleChai(); };
        customCommands["hi"] = [this]() { return handleGreeting(); };
        customCommands["hello"] = [this]() { return handleGreeting(); };
        customCommands["sneaker"] = [this]() { return handleSneaker(); };
        customCommands["swapgpt"] = [this]() { return handleSwapGPT(); };
        customCommands["thanks"] = [this]() { return handleThanks(); };
        customCommands["bug"] = [this]() { return handleBug(); };
        customCommands["devtip"] = [this]() { return handleDevTip(); };
        customCommands["ls"] = [this]() { return handleLinuxLS(); };
        customCommands["sudo"] = [this]() { return handleSudo(); };
        customCommands["sing"] = [this]() { return handleSing(); };
        customCommands["swapify"] = [this]() { return handleSwapify(); };
    }

    std::string handleCoffee() {
        return "☕ Jaggi serves the best cold coffee. Swap recommends it!";
    }

    std::string handleJaggi() {
        return R"(    (
     )
  +---------+
  |  JAGGI  |
  |  COFFEE |
  +---------+
      ___
     /   \
    /_____\

"Find this joy at Jaggi, Patiala's legendary sip stop.")";
    }

    std::string handleQuote() {
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
        return "💬 " + quotes[index];
    }

    std::string handleWhoAmI() {
        return "🔥 Swapnil Chhibber, Future SDE, Sneakerhead & Problem-Solving Ninja\\nCurrently crafting code at Thapar Institute 🎓";
    }

    std::string handleMood() {
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
        return "Current Mood: " + moods[index];
    }

    std::string handleChai() {
        return "🍵 Masala chai > caffeine pills. Fight me.\\nThe perfect blend of spices and caffeine for coding sessions! 💪";
    }

    std::string handleGreeting() {
        return "Hey! You're talking to SwapShell Web Edition. Let's get stuff done 💪\\nReady to tackle some code? 🚀";
    }

    std::string handleDate() {
        return "📅 Today is August 2, 2025 (Web Edition)\\nHope you're killing it today! 🔥";
    }

    std::string handleSneaker() {
        return "👟 Sneaker drop today? Swap's checking Hypebeast...\\nCurrent rotation: Air Jordans, Yeezys, and coding socks 🧦";
    }

    std::string handleSwapGPT() {
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
        return "🤖 " + responses[index];
    }

    std::string handleThanks() {
        return "✨ Gratitude is acknowledged. Now go build something cool!\\nRemember: Every expert was once a beginner 🌱";
    }

    std::string handleBug() {
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
        return "🐛 Bug Alert: " + bugNames[index] + "\\nTime to debug! Remember: It's not a bug, it's a feature 😉";
    }

    std::string handleDevTip() {
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
        return "💡 Dev Tip: " + tips[index];
    }

    std::string handleLinuxLS() {
        return "😎 Wrong OS buddy. Try 'dir' instead!\\nOr maybe it's time to dual boot? 🐧";
    }

    std::string handleSudo() {
        return "🧙 You have no power here!\\nThis is a web browser, not your Linux playground 😄";
    }

    std::string handleSing() {
        return "🎵 Baby Shark doo doo doo doo doo doo\\n🎵 Baby Shark doo doo doo doo doo doo\\n🎵 Baby Shark doo doo doo doo doo doo\\n🎵 Baby Shark! 🦈\\n(Sorry, not sorry for the earworm 😈)";
    }

    std::string handleSwapify() {
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
        return "🎧 SwapSpotify Web: Now playing: " + songs[index] + "\\n🔀 Shuffle: ON | 🔁 Repeat: OFF | 🔊 Volume: Perfect for coding";
    }
};

// Bind the class to JavaScript
EMSCRIPTEN_BINDINGS(myshell_module) {
    emscripten::class_<MyShellWeb>("MyShellWeb")
        .constructor<>()
        .function("processCommand", &MyShellWeb::processCommand)
        .function("getPrompt", &MyShellWeb::getPrompt);
}
