cmake_minimum_required(VERSION 3.10)
project(Trabalho_APA)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(Trabalho_APA
        .idea/misc.xml
        .idea/modules.xml
        .idea/Trabalho-APA.iml
        .idea/workspace.xml
        bin/Debug/GrafosFinal
        bin/Debug/GrafosFinal.exe
        include/Aresta.h
        include/Grafo.h
        include/No.h
        src/Aresta.cpp
        src/Grafo.cpp
        src/No.cpp
        ArvoreDeBuscaLargura.txt
        ArvoreDeBuscaProfundidade.txt
        grafo_1000_1.txt
        GrafoFinal.txt
        GrafosFinal.cbp
        GrafosFinal.depend
        GrafosFinal.layout
        main.cpp
        teste.txt)
