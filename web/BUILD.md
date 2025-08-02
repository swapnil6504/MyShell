# Building MyShell Web Version

## Prerequisites

Install Emscripten SDK for compiling C++ to WebAssembly:

```bash
# Download and install Emscripten
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
```

## Build Commands

```bash
# Basic build
emcc myshell_web.cpp -o myshell.js -s WASM=1 -s "EXPORT_ES6=1" -s "MODULARIZE=1" --bind

# Optimized build for production
emcc myshell_web.cpp -o myshell.js -O3 -s WASM=1 -s "EXPORT_ES6=1" -s "MODULARIZE=1" --bind -s ALLOW_MEMORY_GROWTH=1

# Development build with debugging
emcc myshell_web.cpp -o myshell.js -g -s WASM=1 -s "EXPORT_ES6=1" -s "MODULARIZE=1" --bind -s ASSERTIONS=1
```

## Files Generated

After building, you'll get:

- `myshell.js` - JavaScript loader
- `myshell.wasm` - WebAssembly binary

## Usage

Update your HTML to load the compiled version:

```html
<script type="module">
  import Module from "./myshell.js";

  Module().then(function (Module) {
    const shell = new Module.MyShellWeb();
    // Use shell.processCommand() and shell.getPrompt()
  });
</script>
```

## Current Status

✅ **REBUILT AND ENHANCED!** The HTML file now has a complete JavaScript implementation with 20+ commands!

**Features implemented:**

- All Swapnil's signature commands (coffee, jaggi, whoami, mood, chai, etc.)
- Easter egg commands (swapgpt, sudo, sing, swapify)
- Dynamic content with rotating jokes, tips, and moods
- Consistent branding with "MyShell> " prompt
- Enhanced welcome message matching the native version

**Ready to use:** Simply open `index.html` in any modern web browser!

**Optional:** For even better performance, you can still compile to WebAssembly using the commands above.
