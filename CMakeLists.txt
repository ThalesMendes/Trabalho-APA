cmake_minimum_required(VERSION 3.10)
project(Trabalho_APA)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(Trabalho_APA
        .idea/codeStyles/Project.xml
        .idea/.name
        .idea/misc.xml
        .idea/modules.xml
        .idea/Trabalho-APA.iml
        .idea/vcs.xml
        .idea/workspace.xml
        bin/Debug/GrafosFinal
        bin/Debug/GrafosFinal.exe
        cmake-build-debug/cmake_install.cmake
        cmake-build-debug/CMakeCache.txt
        cmake-build-debug/Makefile
        cmake-build-debug/Trabalho_APA.cbp
        cmake-build-debug/Trabalho_APA.exe
        include/Aresta.h
        include/Grafo.h
        include/No.h
        include/HeuristicaGulosa.h
        src/Aresta.cpp
        src/Grafo.cpp
        src/No.cpp
        src/HeuristicaGulosa.cpp
        ArvoreDeBuscaLargura.txt
        ArvoreDeBuscaProfundidade.txt
        CMakeLists.txt
        grafo_1000_1.txt
        GrafoFinal.txt
        GrafosFinal.cbp
        GrafosFinal.depend
        GrafosFinal.layout
        main.cpp
        teste.txt src/HeuristicaGulosa.cpp include/HeuristicaGulosa.h)
