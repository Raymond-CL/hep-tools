#!/usr/bin/env bash
set -euo pipefail

# ==========================================
# Dependency check before compilation
# ==========================================
REQUIRED_FILES=("ct11pdf.h" "ct11pdf.cc" "i2TAn2.00.pds")

missing_files=()
for f in "${REQUIRED_FILES[@]}"; do
    if [[ ! -f "$f" ]]; then
        missing_files+=("$f")
    fi
done

if (( ${#missing_files[@]} > 0 )); then
    echo "----------------------------------------"
    echo "Missing required files:"
    for f in "${missing_files[@]}"; do
        echo "  - $f"
    done
    echo "----------------------------------------"
    echo "Attempting to fetch missing files..."
    
    if [[ -x "./fetch.sh" ]]; then
        ./fetch.sh
    else
        echo "Error: fetch.sh not found or not executable."
        exit 1
    fi

    echo "----------------------------------------"
    echo "Rechecking files after fetch..."
    for f in "${REQUIRED_FILES[@]}"; do
        if [[ ! -f "$f" ]]; then
            echo "Error: $f still missing after fetch. Aborting compilation."
            exit 1
        fi
    done
    echo "All required files present. Proceeding to compile..."
fi

# ==========================================
# Compilation commands
# ==========================================
echo "Cleaning previous build..."
rm -f incjet.exe *.o results.txt

echo "Compiling ct11pdf.cc..."
g++ -c ct11pdf.cc

echo "Compiling incjet.cpp..."
g++ -Wall -Wextra -Wpedantic -O3 -c incjet.cpp

echo "Linking executable..."
g++ -o incjet.exe ct11pdf.o incjet.o -lgsl

echo "----------------------------------------"
echo "Build complete: incjet.exe"
echo "You can now run it with ./incjet.exe"
echo "----------------------------------------"
