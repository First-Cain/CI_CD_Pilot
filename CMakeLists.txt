cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("CI_CD_Pilot")

# Устанавливаем стандарт C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)			

# Включаем поддержку C++ modules (для import std; в C++23).
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API ON)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP ON)

# Общие опции компиляции для всех компиляторов
if(MSVC)
    add_compile_options(/W4 /permissive- /Zc:__cplusplus) 
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror=return-type)   
endif()

# Кроссплатформенный код: пример, если нужны разные libs.
if(WIN32)
    # Windows-специфично, напр. add_definitions(-D_WINDOWS)
    message(STATUS "Building for Windows")
elseif(UNIX)
    # Linux/Mac, напр. find_package(Threads REQUIRED)
    message(STATUS "Building for Unix-like (Linux)")
endif()

# Подключаем vcpkg (уже в presets, но для универсальности)
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "D:/Hard_Code/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

# Найди GTest (без CONFIG для vcpkg)
find_package(GTest REQUIRED)

# Executable
add_executable (CI_CD_Pilot 
    "CI_CD_Pilot.cpp" 
    "TestFile.cpp" 
    "tests/test_main.cpp"
)

# Includes
target_include_directories(CI_CD_Pilot PRIVATE 
    "${PROJECT_SOURCE_DIR}"
)

# Link gtest
target_link_libraries(CI_CD_Pilot PRIVATE 
    GTest::gtest 
    GTest::gtest_main 
    GTest::gmock
)

# Кроссплатформенные опции для C++23
set_target_properties(CI_CD_Pilot PROPERTIES
  CXX_STANDARD 23
  CXX_STANDARD_REQUIRED YES
)






# Скачиваем GTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0  # Стабильная версия
)
FetchContent_MakeAvailable(googletest)

# Тестовый executable
add_executable(tests "tests/test_main.cpp")
target_link_libraries(tests PRIVATE GTest::gtest_main)

# Кроссплатформенные опции для тестов (C++23)
set_target_properties(tests PROPERTIES
  CXX_STANDARD 23
  CXX_STANDARD_REQUIRED YES
)

# Добавляем источники из основного кода (чтобы тесты видели классы)
target_sources(tests PRIVATE "TestFile.cpp")  # .cpp с реализацией класса

# Includes для тестов
target_include_directories(tests PRIVATE "${PROJECT_SOURCE_DIR}")

# Добавляем тест в ctest (для CI/CD)


# Тесты
enable_testing()
add_test(NAME UnitTests COMMAND tests)
add_test(NAME BasicTest COMMAND CI_CD_Pilot)
