#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <memory>
#include <emscripten.h>
#include <emscripten/bind.h>

// Web version of the shell - simplified without Windows API
class MyShellWeb {
private:
    std::string currentDirectory;
    bool running;
    std::vector<std::string> outputBuffer;
    
public:
    MyShellWeb() : running(true), currentDirectory("/home/user") {
        outputBuffer.push_back("====================================");
        outputBuffer.push_back("    Welcome to MyShell v1.0 (Web)");
        outputBuffer.push_back("    C++ Shell in Your Browser!");
        outputBuffer.push_back("====================================");
        outputBuffer.push_back("Type 'help' for available commands");
        outputBuffer.push_back("");
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
            return "Current date: August 2, 2025 (simulated)";
        } else if (command == "whoami") {
            return "web-user";
        } else if (command == "exit") {
            return "Thank you for using MyShell Web!";
        } else {
            return "Error: Command '" + command + "' not found. Type 'help' for available commands.";
        }
    }

    std::string getPrompt() {
        return "MyShell [" + currentDirectory + "]> ";
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
        return R"(=== MyShell Web Help ===
Built-in commands:
  help            - Show this help message
  pwd             - Print working directory
  cd <directory>  - Change directory (simulated)
  ls/dir          - List directory contents
  clear/cls       - Clear the screen
  echo <text>     - Echo text to output
  date            - Show current date
  whoami          - Show current user
  exit            - Exit message

This is a web demonstration of the C++ shell.
The original version runs natively on Windows with full OS integration.)";
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
};

// Bind the class to JavaScript
EMSCRIPTEN_BINDINGS(myshell_module) {
    emscripten::class_<MyShellWeb>("MyShellWeb")
        .constructor<>()
        .function("processCommand", &MyShellWeb::processCommand)
        .function("getPrompt", &MyShellWeb::getPrompt);
}
