#!/bin/bash

# ������� ������
clear

# ����� �����������
echo "��������� ��������� Geo Program..."
echo "----------------------------------"

# �������� ������� GCC
if ! command -v g++ &> /dev/null; then
    echo "GCC �� ����������. ��������� GCC..."
    pkg install gcc -y || { echo "�� ������� ���������� GCC."; exit 1; }
fi

# �������� ���������� ��� ���������
PROGRAM_DIR="$HOME/.local/bin"
mkdir -p "$PROGRAM_DIR"

# ���������� ��������� ����
SOURCE_URL="https://raw.githubusercontent.com/muxter90/geo-E1M/refs/heads/main/geo_e1m.cpp" # ���� ������
echo "���������� ��������� ����..."
curl -o "$PROGRAM_DIR/geo_e1m.cpp" "$SOURCE_URL" || { echo "������ ��� ���������� �����."; exit 1; }

# ������� � ����������
cd "$PROGRAM_DIR" || { echo "�� ������� ������� � ����������."; exit 1; }

# ���������� ���������
echo "���������� ���������..."
g++ geo_e1m.cpp -o geo_program || { echo "������ ��� ����������."; exit 1; }

# ���������� ����� �� ����������
chmod +x geo_program

# �������� � ���������� ~/.local/bin � PATH
if [[ ":$PATH:" != *":$HOME/.local/bin:"* ]]; then
    echo "���������� ~/.local/bin � PATH..."
    echo 'export PATH=$PATH:$HOME/.local/bin' >> ~/.bashrc
    source ~/.bashrc
fi

# ����� ������������ ���������
echo "��������� ������� �����������!"
echo "��������� � ��������: geo_program"