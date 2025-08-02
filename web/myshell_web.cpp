#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <memory>
#include <emscripten.h>
#include <emscripten/bind.h>

// Web version of the shell - simplified without Windows API
class MyShellWeb
{
private:
    std::string currentDirectory;
    bool running;
    std::vector<std::string> outputBuffer;

public:
    MyShellWeb() : running(true), currentDirectory("/home/user")
    {
        outputBuffer.push_back("===========================================");
        outputBuffer.push_back("Welcome to MyShell v1.0 🚀");
        outputBuffer.push_back("Crafted with ❤️ by Swapnil Chhibber");
        outputBuffer.push_back("Final Year Computer Engineering Student");
        outputBuffer.push_back("Thapar Institute of Engineering & Technology");
        outputBuffer.push_back("===========================================");
        outputBuffer.push_back("Ready to code, debug, and conquer! 💪");
        outputBuffer.push_back("Type 'help' for commands or try 'coffee' for wisdom ☕");
        outputBuffer.push_back("");
    }

    std::string processCommand(const std::string &input)
    {
        std::vector<std::string> tokens = tokenizeCommand(input);

        if (tokens.empty())
        {
            return "";
        }

        std::string command = tokens[0];
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);

        if (command == "help")
        {
            return handleHelp();
        }
        else if (command == "about" || command == "author")
        {
            return handleAbout();
        }
        else if (command == "coffee")
        {
            return handleCoffee();
        }
        else if (command == "joke")
        {
            return handleJoke();
        }
        else if (command == "thapar")
        {
            return handleThapar();
        }
        else if (command == "motivate" || command == "quote")
        {
            return handleMotivate();
        }
        else if (command == "jaggi")
        {
            return handleJaggi();
        }
        else if (command == "whoami")
        {
            return handleWhoami();
        }
        else if (command == "mood")
        {
            return handleMood();
        }
        else if (command == "chai")
        {
            return handleChai();
        }
        else if (command == "hi" || command == "hello")
        {
            return handleGreeting();
        }
        else if (command == "sneaker")
        {
            return handleSneaker();
        }
        else if (command == "devtip")
        {
            return handleDevTip();
        }
        else if (command == "bug")
        {
            return handleBug();
        }
        else if (command == "thanks")
        {
            return handleThanks();
        }
        else if (command == "swapgpt")
        {
            return handleSwapGPT();
        }
        else if (command == "sudo")
        {
            return handleSudoJoke();
        }
        else if (command == "sing")
        {
            return handleSing();
        }
        else if (command == "swapify")
        {
            return handleSwapify();
        }
        else if (command == "version" || command == "ver")
        {
            return handleVersion();
        }
        else if (command == "pwd")
        {
            return "Current directory: " + currentDirectory;
        }
        else if (command == "cd")
        {
            return handleChangeDirectory(tokens);
        }
        else if (command == "ls" || command == "dir")
        {
            return handleListDirectory();
        }
        else if (command == "clear" || command == "cls")
        {
            outputBuffer.clear();
            return "Screen cleared";
        }
        else if (command == "echo")
        {
            std::string result = "Output: ";
            for (size_t i = 1; i < tokens.size(); ++i)
            {
                if (i > 1)
                    result += " ";
                result += tokens[i];
            }
            return result;
        }
        else if (command == "date")
        {
            return "Current date: August 2, 2025 (simulated)\nHope you're killing it today! 💪";
        }
        else if (command == "whoami")
        {
            return handleWhoami();
        }
        else if (command == "exit")
        {
            return R"(Thanks for using MyShell Web! 🚀
Built with ❤️ by Swapnil Chhibber
Keep coding and stay awesome! ✨)";
        }
        else
        {
            return "Error: Command '" + command + "' not found. Type 'help' for available commands.";
        }
    }

    std::string getPrompt()
    {
        return "MyShell> ";
    }

private:
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
                in_quotes = true;
                quote_char = c;
            }
            else if (in_quotes && c == quote_char)
            {
                in_quotes = false;
                quote_char = '\0';
            }
            else if (!in_quotes && (c == ' ' || c == '\t'))
            {
                if (!current_token.empty())
                {
                    tokens.push_back(current_token);
                    current_token.clear();
                }
            }
            else
            {
                current_token += c;
            }
        }

        if (!current_token.empty())
        {
            tokens.push_back(current_token);
        }

        return tokens;
    }

    std::string handleHelp()
    {
        return R"(=== MyShell Web Help ===
Built-in commands:
  help            - Show this help message
  about/author    - Show author information
  pwd             - Print working directory
  cd <directory>  - Change directory (simulated)
  ls/dir          - List directory contents
  clear/cls       - Clear the screen
  echo <text>     - Echo text to output
  date            - Show current date
  whoami          - Show current user
  exit            - Exit message
  version/ver     - Show version info

☕ Swapnil's Signature Commands:
  coffee          - Best cold coffee wisdom
  jaggi           - ASCII coffee art & Jaggi tribute
  chai            - Hot take on masala chai
  quote/motivate  - Random inspirational quotes
  whoami          - Swapnil's introduction
  mood            - Current coding mood
  hi/hello        - Friendly greeting
  sneaker         - Sneaker drop check
  devtip          - Random coding wisdom
  bug             - Funny bug names
  thanks          - Gratitude acknowledgment
  joke            - Programming jokes
  thapar          - About Thapar Institute

🎭 Easter Eggs & Fun:
  swapgpt         - AI simulation
  sudo            - No power here!
  sing            - Musical interlude
  swapify         - Music player simulation

This is a web demonstration of the C++ shell.
The original version runs natively on Windows with full OS integration.
Built with ❤️ by Swapnil Chhibber)";
    }

    std::string handleChangeDirectory(const std::vector<std::string> &tokens)
    {
        if (tokens.size() < 2)
        {
            return "Error: Usage: cd <directory>";
        }

        std::string newPath = tokens[1];
        if (newPath == "..")
        {
            size_t lastSlash = currentDirectory.find_last_of("/");
            if (lastSlash != std::string::npos && lastSlash > 0)
            {
                currentDirectory = currentDirectory.substr(0, lastSlash);
            }
        }
        else if (newPath == "~" || newPath == "/home")
        {
            currentDirectory = "/home/user";
        }
        else
        {
            if (newPath[0] != '/')
            {
                currentDirectory += "/" + newPath;
            }
            else
            {
                currentDirectory = newPath;
            }
        }
        return "Changed directory to: " + currentDirectory;
    }

    std::string handleListDirectory()
    {
        return R"([DIR]  documents
[DIR]  downloads
[DIR]  projects
[FILE] myshell.cpp
[FILE] readme.txt
[FILE] demo.html

Note: This is a simulated directory listing for demonstration.)";
    }

    std::string handleAbout()
    {
        return R"(=== About SwapShell ===
Author: Swapnil Chhibber
Student: Final Year Computer Engineering
University: Thapar Institute of Engineering & Technology
Location: Patiala, Punjab, India

"Building the future, one line of code at a time! 💻✨"

This shell was built with C++17, Windows API, and lots of ☕
Web version powered by modern JavaScript and creativity!)";
    }

    std::string handleJaggi()
    {
        return R"(🏆 Tribute to Jaggi Uncle (The Coffee Legend):

      ╔══════════════════════╗
      ║     ☕ JAGGI ☕      ║
      ║   Cold Coffee King   ║
      ║  Making dreams come  ║
      ║   true, one cup at   ║
      ║      a time! 👑      ║
      ╚══════════════════════╝

The man, the myth, the coffee legend! 🙌)";
    }

    std::string handleWhoami()
    {
        return R"(🚀 Meet the Developer:
Name: Swapnil Chhibber
Role: Code Magician & Coffee Enthusiast ☕
Motto: 'Building software that matters, one line at a time'
Specialty: C++, Creative Solutions, and Cold Coffee Advocacy
Current Status: Bringing personality to terminals everywhere! 🎭)";
    }

    std::string handleMood()
    {
        static int moodIndex = 0;
        const std::vector<std::string> moods = {
            "🔥 On fire! Code is flowing like water!",
            "☕ Caffeinated and ready to debug the world!",
            "🎯 Laser-focused on solving complex problems",
            "🎨 In creative mode - architecting something beautiful",
            "🧘 Zen coding state - one with the algorithm",
            "🚀 Rocket mode engaged - productivity at maximum!",
            "🎵 Vibing with the code rhythm",
            "⚡ Electric! Every keystroke is pure energy!"};

        std::string result = "🎭 Swapnil's Current Coding Mood:\n";
        result += moods[moodIndex];

        moodIndex = (moodIndex + 1) % moods.size();
        return result;
    }

    std::string handleChai()
    {
        return R"(🫖 Hot Take on Chai:
Look, I respect chai culture, but...
Cold coffee >>> Chai (fight me! ☕)
Though I admit, masala chai has its moments... 🤷‍♂️
But for coding marathons? Cold coffee all the way! 💪)";
    }

    std::string handleGreeting()
    {
        return R"(👋 Hey there, awesome human!
Welcome to SwapShell - where commands meet personality!
Ready to explore some quirky features? Type 'help' to get started! 🚀)";
    }

    std::string handleSneaker()
    {
        static int sneakerIndex = 0;
        const std::vector<std::string> sneakerFacts = {
            "Latest drop: Air Max 97 'Silver Bullet' - Classic never dies! 🔥",
            "Jordan 1 High OG 'Chicago' - The GOAT of sneakers! 🐐",
            "Yeezy 350 V2 'Static' - Comfort meets style! ⚡",
            "Off-White x Nike - Virgil's legacy lives on! 👑",
            "New Balance 990v3 'Grey' - The dad shoe that's actually fire! 😎"};

        std::string result = "👟 Sneaker Drop Alert:\n";
        result += sneakerFacts[sneakerIndex] + "\n";
        result += "Remember: Sneakers are code for your feet! 👟💻";

        sneakerIndex = (sneakerIndex + 1) % sneakerFacts.size();
        return result;
    }

    std::string handleDevTip()
    {
        static int tipIndex = 0;
        const std::vector<std::string> tips = {
            "Always comment your code - your future self will thank you!",
            "const > let > var - Choose your JavaScript variables wisely!",
            "Test early, test often, test with coffee! ☕",
            "Git commit messages should tell a story, not just say 'fix'",
            "Rubber duck debugging works - talk to your coffee mug if needed!",
            "Take breaks! Your best solutions come when you step away.",
            "Learn one new thing every day - consistency beats intensity!",
            "Code reviews are love letters to your teammates."};

        std::string result = "💡 Swapnil's Dev Tip of the Day:\n";
        result += tips[tipIndex];

        tipIndex = (tipIndex + 1) % tips.size();
        return result;
    }

    std::string handleBug()
    {
        static int bugIndex = 0;
        const std::vector<std::string> adjectives = {"Sneaky", "Invisible", "Quantum", "Ninja", "Phantom", "Mysterious", "Dancing", "Laughing"};
        const std::vector<std::string> nouns = {"SegFault", "NullPointer", "MemoryLeak", "BufferOverflow", "RaceCondition", "DeadLock", "StackOverflow", "HeapCorruption"};

        int adjIndex = bugIndex % adjectives.size();
        int nounIndex = bugIndex % nouns.size();

        std::string result = "🐛 Today's Bug Name Generator:\n";
        result += "Meet: " + adjectives[adjIndex] + " " + nouns[nounIndex] + "! 🎭\n";
        result += "Approach with caution and plenty of coffee! ☕";

        bugIndex = (bugIndex + 1) % (adjectives.size() * nouns.size());
        return result;
    }

    std::string handleThanks()
    {
        return R"(🙏 You're very welcome!
Thanks for using SwapShell - you make all this coding worthwhile!
Remember: You're awesome, and your code is too! 🌟
Now go forth and create something amazing! 🚀)";
    }

    std::string handleSwapGPT()
    {
        return R"(🤖 SwapGPT v1.0 Initializing...
[████████████████████] 100%
SwapGPT: Hello! I'm the shell's AI assistant!
SwapGPT: I can help with... uh... making coffee recommendations?
SwapGPT: And telling you that cold coffee > hot coffee! ☕
SwapGPT: (Disclaimer: I'm just a function in disguise 😉))";
    }

    std::string handleSudoJoke()
    {
        return R"(🚫 sudo: Permission denied!
Nice try, but this is web territory! 🌐
Here we use 'localStorage' like civilized people! 😄
sudo make me a sandwich? How about 'coffee first'! ☕)";
    }

    std::string handleSing()
    {
        return R"(🎵 SwapShell Serenade:
♪ Code, code, code your app ♪
♪ Gently down the stream ♪
♪ Merrily, merrily, merrily, merrily ♪
♪ Life is but a dream... of clean code! ♪
*Takes a bow* 🎭 Thank you, thank you! ☕)";
    }

    std::string handleSwapify()
    {
        return R"(🎧 Welcome to Swapify - Premium Music Experience!
🎵 Now playing: 'The Algorithm Blues' by Code Monks
⏮️  ⏸️  ⏭️  🔄  📶
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ 3:42 / 4:20
Up next: 'Segmentation Fault Samba' 🎶
Premium feature: No ads, just pure coding vibes! ☕)";
    }

    std::string handleVersion()
    {
        return R"(🌐 MyShell Web v1.0
Platform: Browser (WebAssembly)
Author: Swapnil Chhibber
Build: August 2025

📊 Feature Comparison:
✅ Web Version: 20+ commands, cross-platform, instant access
✅ Native Version: 26+ commands, full Windows integration, file system access

🚀 Both versions include Swapnil's signature personality and quirky commands!
Built with the same love for coffee and clean code! ☕)";
    }

    std::string handleCoffee()
    {
        return R"(☕ Jaggi serves the best cold coffee! ☕
Trust me, I'm a computer engineering student.
Cold coffee is basically liquid motivation! 💪
Fun fact: This shell was coded with 73% cold coffee in my system! 😄)";
    }

    std::string handleJoke()
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

        std::string result = "😂 Swapnil's Programming Joke #" + std::to_string(jokeIndex + 1) + ":\n";
        result += jokes[jokeIndex];

        jokeIndex = (jokeIndex + 1) % jokes.size();
        return result;
    }

    std::string handleThapar()
    {
        return R"(🏛️  Thapar Institute of Engineering & Technology 🏛️
📍 Location: Patiala, Punjab, India
📅 Established: 1956
🎓 My Program: Computer Engineering (Final Year)

💡 Known for:
   • Excellent engineering programs
   • Strong industry connections
   • Beautiful campus in Punjab
   • Producing awesome engineers like me! 😎

Proud to be a Thapar student! 🚀)";
    }

    std::string handleMotivate()
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

        std::string result = "✨ Motivation from Swapnil ✨\n";
        result += quotes[quoteIndex] + "\n\n";
        result += "You've got this! Keep pushing forward! 💪🚀";

        quoteIndex = (quoteIndex + 1) % quotes.size();
        return result;
    }
};

// Bind the class to JavaScript
EMSCRIPTEN_BINDINGS(myshell_module)
{
    emscripten::class_<MyShellWeb>("MyShellWeb")
        .constructor<>()
        .function("processCommand", &MyShellWeb::processCommand)
        .function("getPrompt", &MyShellWeb::getPrompt);
}
