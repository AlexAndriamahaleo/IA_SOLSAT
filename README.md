# Projet IA


## Usage (CMakeLists.txt):

`project(SOLSAT_C)
add_compile_options(-std=c++11)
add_executable(SOLSAT_C
        SOLSAT_C/ConstantBuild.cpp
        SOLSAT_C/ConstantBuild.h
        SOLSAT_C/tools.cpp
        SOLSAT_C/tools.h
        SOLSAT_C/PigeonsFactory.cpp
        SOLSAT_C/PigeonsFactory.h
        SOLSAT_C/QueensFactory.cpp
        SOLSAT_C/QueensFactory.h
        SOLSAT_C/FormulasReader.cpp
        SOLSAT_C/FormulasReader.h
        SOLSAT_C/SolsatMain.cpp
        SOLSAT_C/SolsatMain.h
        SOLSAT_C/DynamicBuild.cpp
        SOLSAT_C/DynamicBuild.h)`