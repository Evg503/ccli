#!/bin/bash

# Настройки по умолчанию
CONFIG="Debug"
CLEAN_BUILD=false

# Цвета для вывода
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0;0m' # Без цвета

# Справка
show_help() {
    echo "Использование: $0 [опции] [Конфигурация]"
    echo "Конфигурации: Debug (по умолчанию), Release, RelWithDebInfo, MinSizeRel"
    echo "Опции:"
    echo "  -c, --clean    Удалить старую сборку перед компиляцией"
    echo "  -h, --help     Показать это сообщение"
}

# Обработка флагов
while [[ "$1" =~ ^- ]]; do
    case "$1" in
        -h|--help)
            show_help
            exit 0
            ;;
        -c|--clean)
            CLEAN_BUILD=true
            shift
            ;;
        *)
            echo -e "${RED}Ошибка: Неизвестный флаг $1${NC}"
            show_help
            exit 1
            ;;
    esac
done

# Определение конфигурации (если передана аргументом)
if [ -n "$1" ]; then
    CONFIG="$1"
fi

# Очистка сборки при необходимости
if [ "$CLEAN_BUILD" = true ]; then
    echo -e "${BLUE}Очистка директории сборки...${NC}"
    rm -rf build
fi

# Создание директории и генерация файлов сборки
if [ ! -d "build" ]; then
    echo -e "${BLUE}Генерация файлов сборки (${CONFIG})...${NC}"
    cmake -B build -DCMAKE_BUILD_TYPE="$CONFIG" || { echo -e "${RED}Ошибка генерации CMake!${NC}"; exit 1; }
fi

# Запуск сборки
echo -e "${BLUE}Запуск сборки проекта в режиме ${CONFIG}...${NC}"
cmake --build build --config "$CONFIG"

# Проверка результата сборки
if [ $? -eq 0 ]; then
    echo -e "${GREEN}Сборка успешно завершена!${NC}"
else
    echo -e "${RED}Ошибка во время сборки!${NC}"
    exit 1
fi
