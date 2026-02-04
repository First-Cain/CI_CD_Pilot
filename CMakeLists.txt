cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("CI_CD_Pilot")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (CI_CD_Pilot 
"CI_CD_Pilot.cpp" 
)

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


# Includes (директории заголовков)
target_include_directories(CI_CD_Pilot PRIVATE 
  "${PROJECT_SOURCE_DIR}"  # Текущая папка
  # Если есть libs: /path/to/includes
)

# Libs (если нужны, e.g. pthread для multi-thread)
target_link_libraries(CI_CD_Pilot PRIVATE 
  # pthread  # Если нужно; для Windows/Linux auto
)


# Тесты (если нужны)
enable_testing()
add_test(NAME BasicTest COMMAND CI_CD_Pilot)  # Пример простого теста

# add_test(NAME AnotherTest COMMAND CI_CD_Pilot arg1 arg2)  # Другие тесты с аргументами
# Можно добавить больше тестов по мере необходимости
# Конец CMakeLists.txt