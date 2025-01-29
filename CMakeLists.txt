# Minimum version de CMake
cmake_minimum_required(VERSION 3.20)

# Nom du projet
project(e_tron)

# Définir le standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Flags
set(CMAKE_CXX_FLAGS_RELEASE "/MP /Ot /MD /fp:fast")
set(CMAKE_CXX_FLAGS_DEBUG "/MP /Ot /MDd /fp:fast")

# Inclure les répertoires contenant les headers
include_directories(${CMAKE_SOURCE_DIR}/src)

# Ajouter les fichiers sources principaux
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.h)

# Ajouter les fichiers pour les tests (dans src/test/)
file(GLOB_RECURSE TEST_FILES ${CMAKE_SOURCE_DIR}/src/test/*.cpp ${CMAKE_SOURCE_DIR}/src/test/*.h)

# Supprimer le main 
list(REMOVE_ITEM SRC_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp)
list(REMOVE_ITEM SRC_FILES ${CMAKE_SOURCE_DIR}/src/winMain.cpp)

# Ajouter une cible exécutable pour les tests
add_executable(MyTests ${SRC_FILES})

# Supprimer les fichiers test de la liste SRC_FILES
list(REMOVE_ITEM SRC_FILES ${TEST_FILES})

# Ajouter src/main.cpp à la liste SRC_FILES
list(APPEND SRC_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp)

# Ajouter une cible exécutable pour le projet principal
add_executable(e_tron_cmd ${SRC_FILES})

list(REMOVE_ITEM SRC_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp)

list(APPEND SRC_FILES ${CMAKE_SOURCE_DIR}/src/winMain.cpp)

add_executable(e_tron_directX ${SRC_FILES})

set_target_properties(e_tron_directX PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")

# Lier les bibliothèques principales aux tests si nécessaire (optionnel)
#target_link_libraries(MyTests PRIVATE MyProject)

# Ajouter des options supplémentaires si tu utilises DirectX (par exemple)
# target_link_libraries(MyProject d3d11 dxgi d3dcompiler)
