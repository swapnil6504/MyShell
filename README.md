# MyShell - Windows C++ Shell Implementation

A comprehensive command-line shell implementation in C++ for Windows, featuring modern C++17 syntax and Windows API integration.

## Features

### Core Functionality

- **Interactive Command Prompt**: Custom prompt showing current directory
- **Command Tokenization**: Intelligent parsing with quoted argument support
- **Built-in Commands**: Essential shell commands implemented natively
- **External Command Execution**: Runs system programs and utilities
- **Error Handling**: Comprehensive error reporting and recovery

### Built-in Commands

- `cd <directory>` - Change current working directory
  - Supports `..` for parent directory
  - Supports `~` or `%USERPROFILE%` for home directory
- `exit` - Exit the shell gracefully
- `help` - Display command help and usage information
- `cls`/`clear` - Clear the console screen
- `pwd` - Print current working directory
- `dir`/`ls [path]` - List directory contents with file/folder indicators

### Advanced Features

- **Quoted Arguments**: Handle arguments with spaces using quotes
- **Pipe Detection**: Basic pipeline command detection (shows notification)
- **Redirection Detection**: Basic I/O redirection detection (shows notification)
- **Colored Output**: Enhanced UI with colored text for different elements
- **Process Management**: Proper child process handling with exit code reporting

### Technical Implementation

- **C++17 Standard**: Modern C++ features and best practices
- **Windows API Integration**: Native Windows process creation and console management
- **Memory Safety**: RAII principles and proper resource cleanup
- **Error Recovery**: Robust error handling for filesystem and process operations

## Building

### Option 1: Using the provided batch file

```cmd
build.bat
```

### Option 2: Using g++ directly (MinGW/MSYS2)

```cmd
g++ -std=c++17 -O2 -Wall -Wextra myshell.cpp -o myshell.exe -lshell32
```

### Option 3: Using Visual Studio

```cmd
cl /std:c++17 /EHsc myshell.cpp shell32.lib
```

### Option 4: Using CMake

```cmd
mkdir build
cd build
cmake ..
cmake --build .
```

## Usage

Run the compiled executable:

```cmd
myshell.exe
```

### Example Session

```
====================================
    Welcome to MyShell v1.0
    Windows C++ Shell Implementation
====================================
Type 'help' for available commands

MyShell [C:\Users\YourName\Desktop\shell]> help

=== MyShell Help ===
Built-in commands:
  cd <directory>  - Change current directory
  exit            - Exit the shell
  help            - Show this help message
  cls/clear       - Clear the screen
  pwd             - Print working directory
  dir/ls [path]   - List directory contents

Special features:
  - Quoted arguments support
  - Basic pipe detection (|)
  - Basic redirection detection (>, <)
  - External command execution
  - Colored output

MyShell [C:\Users\YourName\Desktop\shell]> cd ..
Changed directory to: C:\Users\YourName\Desktop

MyShell [C:\Users\YourName\Desktop]> dir
[DIR]  shell
[FILE] document.txt
[FILE] image.png

MyShell [C:\Users\YourName\Desktop]> notepad "my file.txt"
[Opens Notepad with the specified file]

MyShell [C:\Users\YourName\Desktop]> exit
Exiting MyShell...
Thank you for using MyShell!
```

## Architecture

The shell is implemented as a single class `MyShell` with the following key components:

- **Command Loop**: Main execution loop handling user input
- **Tokenizer**: Parses command strings into tokens with quote support
- **Built-in Handler**: Processes internal shell commands
- **Process Executor**: Creates and manages external processes
- **Console Manager**: Handles colored output and UI elements

## Requirements

- Windows 7 or later
- C++17 compatible compiler
- Windows SDK (included with Visual Studio or available separately)

## Limitations

- Pipe operations are detected but not fully implemented (requires complex process chaining)
- I/O redirection is detected but not fully implemented (requires file handle management)
- No command history or line editing (could be added with Windows Console API extensions)
- No background process management (all commands run in foreground)

## Future Enhancements

Potential improvements for a production version:

1. **Full Pipe Support**: Implement process chaining for complex pipelines
2. **I/O Redirection**: Complete file redirection implementation
3. **Command History**: Add readline-style command history and editing
4. **Tab Completion**: File and command name auto-completion
5. **Environment Variables**: Full environment variable support and expansion
6. **Scripting**: Basic shell scripting capabilities
7. **Background Jobs**: Process management for background tasks
8. **Aliases**: User-definable command aliases

## Author

Made by Swapnil Chhibber

## License

This implementation is provided as an educational example demonstrating Windows API usage and modern C++ practices.
