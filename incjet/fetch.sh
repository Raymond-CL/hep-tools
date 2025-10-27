#!/usr/bin/env bash
set -euo pipefail

# ===============================
# Preparation
# ===============================
TEMP_DIR="temp"
mkdir -p "$TEMP_DIR"

# --- Function to download file using wget or curl ---
download_file() {
    local url="$1"
    local output_path="$2"

    echo "Downloading: $url"
    if command -v wget >/dev/null 2>&1; then
        wget -q --show-progress "$url" -O "$output_path"
    elif command -v curl >/dev/null 2>&1; then
        curl -L "$url" -o "$output_path"
    else
        echo "Error: Neither wget nor curl found. Please install one of them." >&2
        exit 1
    fi
}

# ===============================
# Step 1: Ask for CTEQ PDF
# ===============================
echo "----------------------------------------"
read -rp "Do you want to use CTEQ as PDF? (y/n): " use_cteq
case "$use_cteq" in
    y|Y|yes|YES)
        echo "Fetching CTEQ PDF source files..."
        ;;
    *)
        echo "CTEQ not selected. Exiting."
        exit 0
        ;;
esac

# --- Download and extract ct11pdfcpp.zip ---
CTEQ_URL="http://ct.hepforge.org/PDFs/cpp/ct11pdfcpp.zip"
CTEQ_ZIP="$TEMP_DIR/ct11pdfcpp.zip"

download_file "$CTEQ_URL" "$CTEQ_ZIP"

echo "Extracting CTEQ source files..."
unzip -q "$CTEQ_ZIP" -d "$TEMP_DIR"

# Detect actual extracted folder
CTEQ_EXTRACT_DIR=$(find "$TEMP_DIR" -maxdepth 1 -type d -name "ct11pdfcpp*" | head -n 1)
if [[ -z "$CTEQ_EXTRACT_DIR" ]]; then
    echo "Error: could not locate extracted CTEQ folder."
    exit 1
fi

# Copy files
for f in ct11pdf.h ct11pdf.cc; do
    FOUND_FILE=$(find "$CTEQ_EXTRACT_DIR" -type f -name "$f" | head -n 1 || true)
    if [[ -n "$FOUND_FILE" ]]; then
        cp -p "$FOUND_FILE" .
        echo "Copied $f to project directory."
    else
        echo "Warning: $f not found inside $CTEQ_EXTRACT_DIR."
    fi
done

# ===============================
# Modify ct11pdf.h (lines 72–75)
# ===============================
if [[ -f "ct11pdf.h" ]]; then
    echo "Applying C++ standard fix to ct11pdf.h (lines 72–75)..."
    
    # Replace only the leading 'const' on those lines with 'constexpr'
    # without affecting other const declarations elsewhere.
    sed -i '72,75s/\bconst\b/constexpr/' ct11pdf.h

    echo "Modification complete: static const → static constexpr (lines 72–75)"
fi

# ===============================
# Step 2: Ask for CT18ANLO grid
# ===============================
echo "----------------------------------------"
read -rp "Do you want to get CT18ANLO grid data? (y/n): " use_ct18
case "$use_ct18" in
    y|Y|yes|YES)
        echo "Fetching CT18ANLO grid data..."
        ;;
    *)
        echo "CT18 grid not selected. Exiting."
        exit 0
        ;;
esac

# --- Download and extract CT18ANLO-pds.zip ---
CT18_URL="http://ct.hepforge.org/PDFs/ct18/pds/CT18ANLO-pds.zip"
CT18_ZIP="$TEMP_DIR/CT18ANLO-pds.zip"

download_file "$CT18_URL" "$CT18_ZIP"

echo "Extracting CT18 grid data..."
unzip -q "$CT18_ZIP" -d "$TEMP_DIR"

# Detect actual extracted folder
CT18_EXTRACT_DIR=$(find "$TEMP_DIR" -maxdepth 1 -type d -name "CT18ANLO-pds*" | head -n 1)
if [[ -z "$CT18_EXTRACT_DIR" ]]; then
    echo "Error: could not locate extracted CT18 folder."
    exit 1
fi

# Copy grid file
GRID_FILE="i2TAn2.00.pds"
FOUND_GRID=$(find "$CT18_EXTRACT_DIR" -type f -name "$GRID_FILE" | head -n 1 || true)
if [[ -n "$FOUND_GRID" ]]; then
    cp -p "$FOUND_GRID" .
    echo "Copied $GRID_FILE to project directory."
else
    echo "Warning: $GRID_FILE not found inside $CT18_EXTRACT_DIR."
fi

# ===============================
# Completion message
# ===============================
echo "----------------------------------------"
echo "Fetch complete!"
echo "You can now compile your program with:"
echo "  g++ incjet.cpp"
echo "----------------------------------------"
