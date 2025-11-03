cmake_minimum_required(VERSION 3.15)
project(MyProject VERSION 1.0.0 LANGUAGES CXX)

# Автоматическая загрузка зависимостей через vcpkg
set(CMAKE_TOOLCHAIN_FILE "/home/dmitry-paderin/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Включи манифест (автоматическую установку зависимостей)
set(VCPKG_MANIFEST_MODE ON)

find_package(GTest CONFIG REQUIRED)

add_executable(my_app main.cpp list.cpp)

# Линковка - vcpkg автоматически найдет зависимости
target_link_libraries(my_app PRIVATE 
    GTest::gtest 
    GTest::gtest_main
)

target_compile_features(my_app PRIVATE cxx_std_17)