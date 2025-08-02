# 🖥️ MyShell - Swapnil's Interactive C++ Shell

> A comprehensive command-line shell implementation in C++ for Windows, featuring modern C++17 syntax, Windows API integration, and Swapnil's signature personality! ☕

Created by **Swapnil Chhibber** - Final Year Computer Engineering Student  
Thapar Institute of Engineering & Technology, Patiala, Punjab

---

## 🚀 Quick Start

### Native Windows Version

```cmd
# Clone and build
git clone <repository-url>
cd shell
build.bat

# Run the shell
myshell.exe
```

### 🌐 Web Demo (Try Now!)

Open `web/index.html` in any modern browser for an instant demo with 20+ commands!

**Live Demo:** Simply double-click `web/index.html` or host it anywhere online.

---

## ✨ Features Overview

### 🎯 **Native Windows Version (26+ Commands)**

- Full Windows API integration
- Real filesystem operations
- Process management with exit codes
- Console color management
- Pipe and redirection detection
- All of Swapnil's quirky personality commands

### 🌐 **Web Version (20+ Commands)**

- Cross-platform browser compatibility
- Instant access - no compilation needed
- Same personality as the native version
- Dynamic content and rotating jokes
- Perfect for demos and showcasing

---

## 🎭 Command Categories

### 📦 **Core Shell Commands**

- `help` - Complete command listing
- `cd <directory>` - Change directory (supports `..`, `~`)
- `pwd` - Print working directory
- `ls/dir [path]` - List directory contents
- `clear/cls` - Clear screen
- `echo <text>` - Echo text output
- `date` - Current date with motivation
- `exit` - Exit with farewell message

### ☕ **Swapnil's Signature Commands**

- `coffee` - Jaggi's cold coffee wisdom
- `jaggi` - ASCII coffee art tribute
- `whoami` - Full developer introduction
- `mood` - Dynamic coding mood (8 variations)
- `chai` - Hot take on masala chai
- `hi/hello` - Friendly greeting
- `sneaker` - Rotating sneaker drops (5 facts)
- `devtip` - Programming wisdom (8 tips)
- `bug` - Funny bug name generator
- `thanks` - Gratitude acknowledgment
- `joke` - Programming jokes (7 jokes)
- `quote/motivate` - Inspirational quotes (7 quotes)
- `thapar` - University information

### 🎭 **Easter Eggs & Fun**

- `swapgpt` - AI simulation parody
- `sudo` - Permission denied joke
- `sing` - Musical serenade
- `swapify` - Music player simulation
- `version/ver` - Platform comparison

---

## 🔧 Building & Running

### **Option 1: Windows Batch Build (Recommended)**

```cmd
build.bat
```

### **Option 2: Manual Build (MinGW/MSYS2)**

```cmd
g++ -std=c++17 -O2 -Wall -Wextra myshell.cpp -o myshell.exe
```

### **Option 3: Visual Studio**

```cmd
cl /EHsc /std:c++17 myshell.cpp
```

### **Option 4: CMake Build**

```cmd
mkdir build && cd build
cmake ..
cmake --build .
```

---

## 🌐 Web Version Setup

### **Instant Demo (No Setup)**

1. Open `web/index.html` in any browser
2. Enjoy 20+ commands with full personality!

### **Host Online (5 minutes)**

#### **GitHub Pages (FREE)**

```bash
git init
git add .
git commit -m "Add MyShell demo"
git remote add origin https://github.com/yourusername/myshell.git
git push -u origin main
# Enable Pages in GitHub repo settings
# Live at: https://yourusername.github.io/myshell
```

#### **Netlify (Instant)**

1. Go to [netlify.com](https://netlify.com)
2. Drag & drop your `web` folder
3. Get instant URL like: `https://amazing-shell-123.netlify.app`

#### **Vercel/Firebase**

- Connect GitHub repo for auto-deployment
- Perfect for continuous integration

### **WebAssembly Build (Advanced)**

```bash
# Install Emscripten
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk && ./emsdk install latest && ./emsdk activate latest

# Compile to WASM
emcc web/myshell_web.cpp -o web/myshell.js -O3 -s WASM=1 -s "EXPORT_ES6=1" -s "MODULARIZE=1" --bind
```

---

## 🏗️ Technical Implementation

### **Core Architecture**

- **Language**: C++17 with modern features
- **Platform**: Windows API integration
- **Design**: Modular command handlers
- **Memory**: RAII principles and proper cleanup
- **Error Handling**: Comprehensive error recovery

### **Key Features**

- **Quoted Arguments**: Handle spaces in arguments
- **Process Management**: Child process creation and monitoring
- **Colored Output**: Enhanced UI with Windows console colors
- **Command History**: Arrow key navigation (web version)
- **Dynamic Content**: Rotating jokes, moods, and tips

### **Files Structure**

```
shell/
├── myshell.cpp          # Main C++ shell implementation
├── build.bat           # Windows build script
├── CMakeLists.txt      # CMake configuration
├── README.md           # This comprehensive guide
├── demo.bat           # Demo script
└── web/
    ├── index.html      # Web version (JavaScript)
    ├── myshell_web.cpp # C++ for WebAssembly
    └── test.html       # Command verification
```

---

## 🎨 Personality & Branding

MyShell isn't just a shell - it's **Swapnil's coding personality** in terminal form:

- **Coffee Obsession**: Jaggi's cold coffee > everything else ☕
- **Thapar Pride**: Representing the university with honor 🏛️
- **Programming Humor**: Jokes, puns, and coding wisdom 😄
- **Dynamic Content**: Never the same experience twice 🎲
- **Motivation**: Always encouraging and positive 💪

---

## 🧪 Testing & Demo

### **Test Commands**

```bash
# Try these fun commands:
coffee
jaggi
mood
joke
devtip
swapgpt
sudo make me a sandwich
```

### **Demo Script**

```cmd
demo.bat
```

### **Advanced Testing**

```bash
# File operations
cd ..
pwd
ls
cd projects

# Fun stuff
whoami
thapar
motivate
sneaker
```

---

## 🚀 Deployment & Hosting

### **Local Development**

```bash
# Python server
python -m http.server 8000

# Node.js server
npx http-server

# VS Code Live Server
# Right-click index.html -> "Open with Live Server"
```

### **Production Hosting**

- **GitHub Pages**: Free, reliable, perfect for demos
- **Netlify/Vercel**: Instant deployment from git
- **Firebase**: Google's hosting with custom domains
- **Any Static Host**: Works anywhere HTML can be served

---

## 📊 Version Comparison

| Feature           | Native Windows   | Web Version           |
| ----------------- | ---------------- | --------------------- |
| Commands          | 26+              | 20+                   |
| File Operations   | Real filesystem  | Simulated             |
| Process Execution | Full Windows API | JavaScript simulation |
| Personality       | ✅ Full          | ✅ Full               |
| Dynamic Content   | ✅               | ✅                    |
| Platform Support  | Windows only     | Cross-platform        |
| Deployment        | Compile required | Instant               |

---

## 🎓 About the Developer

**Swapnil Chhibber**  
🎓 Final Year Computer Engineering Student  
🏛️ Thapar Institute of Engineering & Technology  
📍 Patiala, Punjab, India  
☕ Cold Coffee Enthusiast & Code Architect

> "Building the future, one line of code at a time! 💻✨"

---

## 🎯 Project Goals Achieved

✅ **Feature-Complete Shell**: All essential commands implemented  
✅ **Cross-Platform Demo**: Web version for instant access  
✅ **Personality Integration**: Unique character and humor  
✅ **Technical Excellence**: Modern C++17 and clean architecture  
✅ **Easy Deployment**: Multiple hosting options available  
✅ **Documentation**: Comprehensive guides and examples

---

## 🤝 Contributing & Contact

This project showcases modern C++ development, creative problem-solving, and personality-driven software design.

**Perfect for:**

- Portfolio demonstrations
- Technical interviews
- Learning C++ and shell development
- Understanding Windows API integration
- Exploring WebAssembly compilation

---

## 📜 License

This project is part of Swapnil's academic portfolio and demonstrates advanced C++ programming skills, creative software design, and full-stack development capabilities.

**Built with ❤️, ☕, and lots of late-night coding sessions!**

---

_Ready to explore? Start with `myshell.exe` on Windows or open `web/index.html` in your browser!_ 🚀
