cmake_minimum_required(VERSION 3.10...3.31)  # Диапазон для фикса deprecation

# vcpkg integration (твои поля — для local и CI)
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND EXISTS "D:/Hard_Code/vcpkg/scripts/buildsystems/vcpkg.cmake")
  set(CMAKE_TOOLCHAIN_FILE "D:/Hard_Code/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "vcpkg toolchain")
endif()

# Включение горячей перезагрузки для MSVC
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("CI_CD_Pilot")

# Основной executable
add_executable(CI_CD_Pilot 
  "CI_CD_Pilot.cpp" 
  "TestFile.cpp")

# Устанавливаем C++23 для main
set_target_properties(CI_CD_Pilot PROPERTIES
  CXX_STANDARD 23
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
)

# Общие опции компиляции
if(MSVC)
  add_compile_options(/W4 /permissive- /Zc:__cplusplus) 
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror=return-type)   
endif()

# Кроссплатформенный код
if(WIN32)
  message(STATUS "Building for Windows")
elseif(UNIX)
  message(STATUS "Building for Unix-like (Linux)")
endif()

# Includes для main (твои поля + другие libs через vcpkg)
target_include_directories(CI_CD_Pilot PRIVATE "${PROJECT_SOURCE_DIR}")

# Libs для main (через vcpkg, e.g. find_package(YourLib REQUIRED); target_link_libraries(... YourLib::YourLib))
target_link_libraries(CI_CD_Pilot PRIVATE)  # Добавляй здесь твои libs, e.g. uWebSockets::uWebSockets

# GTest: Conditional — если vcpkg, find_package; else FetchContent
if(VCPKG_TOOLCHAIN)
  find_package(GTest CONFIG REQUIRED)  # vcpkg mode
else()
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
  )
  FetchContent_MakeAvailable(googletest)
endif()

# Тестовый executable (отдельный от main)
add_executable(unit_tests "tests/test_main.cpp")
target_sources(unit_tests PRIVATE "TestFile.cpp")  # Реализация класса для тестов
target_link_libraries(unit_tests PRIVATE GTest::gtest_main)  # GTest link только здесь

# C++23 для тестов
set_target_properties(unit_tests PROPERTIES
  CXX_STANDARD 23
  CXX_STANDARD_REQUIRED ON
)

# Output dir for exe (bin/ to avoid root conflicts)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Includes для тестов
target_include_directories(unit_tests PRIVATE "${PROJECT_SOURCE_DIR}")

# Тесты для ctest (в CI/CD)
enable_testing()
add_test(NAME UnitTests COMMAND tests)
add_test(NAME BasicTest COMMAND CI_CD_Pilot)  # Опционально для main