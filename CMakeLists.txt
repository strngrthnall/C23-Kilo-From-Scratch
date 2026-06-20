cmake_minimum_required(VERSION 4.2)
project(C23_Kilo_From_Scratch C)

# 1. Configuração do padrão de linguagem
set(CMAKE_C_STANDARD 23)

# Desativa as extensões GNU (Vamos usar C puro)
set(CMAKE_C_EXTENSIONS OFF)

# Garante que a compilação falhe se não suportar o C23
set(CMAKE_C_STANDARD_REQUIRED ON)

# 2. Flags para o compilador
add_compile_options(-Wall -Wextra -pedantic)

# 3. Inserindo a pasta ./include
include_directories(include)

# 4. Arquivos fonte
file(GLOB SOURCES "src/*.c")

# 5. Executável final
add_executable(kilo ${SOURCES}
        include/terminal.h
        src/terminal.c
        include/input.h
        src/input.c)