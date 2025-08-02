# MyShell Web Demo

This directory contains a web version of MyShell that can run in browsers with 20+ commands and Swapnil's signature personality!

## ✨ Features

**🎯 Enhanced Web Version includes:**

- All core commands (help, cd, pwd, ls, clear, etc.)
- **Swapnil's Signature Commands:** coffee, jaggi, whoami, mood, chai, hi/hello, sneaker, devtip, bug, thanks
- **Fun Easter Eggs:** swapgpt, sudo (joke), sing, swapify
- **Personal Touch:** Thapar references, programming jokes, motivational quotes
- **Interactive Experience:** Same personality as the native Windows version

## Quick Setup Options

### Option 1: Static Hosting (Easiest)

1. Upload the `index.html` file to any static hosting service:
   - **GitHub Pages** (free): Push to GitHub repo, enable Pages
   - **Netlify** (free): Drag & drop the HTML file
   - **Vercel** (free): Connect GitHub repo or upload files
   - **Firebase Hosting** (free): Use Firebase CLI

### Option 2: Local Testing

1. Start a simple HTTP server:

   ```bash
   # Python 3
   python -m http.server 8000

   # Node.js (if you have http-server installed)
   npx http-server

   # VS Code Live Server extension
   Right-click index.html -> "Open with Live Server"
   ```

2. Open `http://localhost:8000`

### Option 3: WebAssembly Version (Advanced)

To compile the C++ version to WebAssembly:

1. Install Emscripten:

   ```bash
   git clone https://github.com/emscripten-core/emsdk.git
   cd emsdk
   ./emsdk install latest
   ./emsdk activate latest
   source ./emsdk_env.sh
   ```

2. Compile the C++ code:

   ```bash
   emcc myshell_web.cpp -o myshell.js -s WASM=1 -s EXPORTED_FUNCTIONS="['_main']" -s EXTRA_EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']" --bind
   ```

3. Include the generated files in your HTML.

## Current Features

The current `index.html` includes:

- ✅ Interactive terminal interface
- ✅ Command history (up/down arrows)
- ✅ Simulated filesystem operations
- ✅ Colored output
- ✅ Responsive design
- ✅ All basic shell commands
- ✅ Professional UI/UX

## Demo Commands

Try these commands in the web demo:

- `help` - Show available commands
- `pwd` - Print working directory
- `ls` or `dir` - List files
- `cd documents` - Change directory
- `cd ..` - Go to parent directory
- `echo "Hello World"` - Echo text
- `date` - Show current date
- `whoami` - Show current user
- `clear` - Clear screen

## Hosting Recommendations

### Free Options:

1. **GitHub Pages**:

   - Create repo, upload files, enable Pages
   - URL: `https://yourusername.github.io/myshell-demo`

2. **Netlify**:

   - Drag & drop deployment
   - URL: `https://random-name.netlify.app`

3. **Vercel**:
   - Connect GitHub or upload
   - URL: `https://myshell-demo.vercel.app`

### Custom Domain:

- Buy domain from Namecheap, GoDaddy, etc.
- Point DNS to your hosting service
- Example: `myshell-demo.com`

## Marketing the Demo

Share your demo with:

- Social media posts
- Developer communities (Reddit r/cpp, r/programming)
- LinkedIn tech posts
- Personal portfolio/resume
- GitHub README

The web demo showcases your C++ skills while being accessible to anyone with a browser!
