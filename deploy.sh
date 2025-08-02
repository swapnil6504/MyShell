#!/bin/bash

echo "🚀 MyShell Web Demo Deployment Script"
echo "======================================"

# Check if we're in the right directory
if [ ! -f "web/index.html" ]; then
    echo "❌ Error: web/index.html not found. Run this script from the project root."
    exit 1
fi

echo "✅ Found web demo files"

# Option 1: Deploy to GitHub Pages
echo ""
echo "📡 Deployment Options:"
echo "1. GitHub Pages (recommended)"
echo "2. Netlify"
echo "3. Vercel"
echo "4. Local testing server"

read -p "Choose an option (1-4): " choice

case $choice in
    1)
        echo "🔧 Setting up GitHub Pages deployment..."
        echo "Instructions:"
        echo "1. Create a new GitHub repository"
        echo "2. Push this code to the repository"
        echo "3. Go to Settings > Pages"
        echo "4. Select 'Deploy from a branch'"
        echo "5. Choose 'main' branch and '/ (root)' folder"
        echo "6. Your demo will be available at: https://yourusername.github.io/repository-name"
        ;;
    2)
        echo "🔧 Netlify deployment..."
        echo "1. Go to https://netlify.com"
        echo "2. Drag and drop the 'web' folder"
        echo "3. Your site will be deployed instantly"
        ;;
    3)
        echo "🔧 Vercel deployment..."
        echo "1. Go to https://vercel.com"
        echo "2. Connect your GitHub repository"
        echo "3. Set build settings to serve from 'web' directory"
        ;;
    4)
        echo "🔧 Starting local server..."
        cd web
        if command -v python3 &> /dev/null; then
            echo "Starting Python HTTP server on http://localhost:8000"
            python3 -m http.server 8000
        elif command -v python &> /dev/null; then
            echo "Starting Python HTTP server on http://localhost:8000"
            python -m http.server 8000
        elif command -v npx &> /dev/null; then
            echo "Starting Node.js HTTP server on http://localhost:8080"
            npx http-server -p 8080
        else
            echo "❌ No suitable HTTP server found. Install Python or Node.js"
            exit 1
        fi
        ;;
    *)
        echo "❌ Invalid option"
        exit 1
        ;;
esac

echo ""
echo "🎉 Deployment setup complete!"
echo "Your MyShell demo showcases:"
echo "- C++ programming skills"
echo "- Systems programming knowledge"
echo "- Web technology integration"
echo "- Professional project presentation"
