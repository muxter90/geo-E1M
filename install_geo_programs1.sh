#!/bin/bash

# Очистка экрана
clear

# Вывод приветствия
echo "Установка программы Geo Program..."
echo "----------------------------------"

# Проверка наличия GCC
if ! command -v g++ &> /dev/null; then
    echo "GCC не установлен. Установка GCC..."
    pkg install gcc -y || { echo "Не удалось установить GCC."; exit 1; }
fi

# Создание директории для программы
PROGRAM_DIR="$HOME/.local/bin"
mkdir -p "$PROGRAM_DIR"

# Скачивание исходного кода
SOURCE_URL="https://raw.githubusercontent.com/muxter90/geo-E1M/refs/heads/main/geo_e1m.cpp" # Ваша ссылка
echo "Скачивание исходного кода..."
curl -o "$PROGRAM_DIR/geo_e1m.cpp" "$SOURCE_URL" || { echo "Ошибка при скачивании файла."; exit 1; }

# Переход в директорию
cd "$PROGRAM_DIR" || { echo "Не удалось перейти в директорию."; exit 1; }

# Компиляция программы
echo "Компиляция программы..."
g++ geo_e1m.cpp -o geo_program || { echo "Ошибка при компиляции."; exit 1; }

# Добавление права на выполнение
chmod +x geo_program

# Проверка и добавление ~/.local/bin в PATH
if [[ ":$PATH:" != *":$HOME/.local/bin:"* ]]; then
    echo "Добавление ~/.local/bin в PATH..."
    echo 'export PATH=$PATH:$HOME/.local/bin' >> ~/.bashrc
    source ~/.bashrc
fi

# Вывод завершающего сообщения
echo "Программа успешно установлена!"
echo "Запустите её командой: geo_program"