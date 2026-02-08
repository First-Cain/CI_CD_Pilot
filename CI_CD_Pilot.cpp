#include <iostream>
#include <version>
#include "TestFile.hpp"





int main()
{
	TestClass::display_message();
	TestClass obj;

	obj.new_test_foo();


	constexpr int a{ 2 };





	std::cout << "	[" << a << "]	WTF BRED\n";
	std::cout << "	[" << a << "]	Hello CMake.\n";




	// Выводим тип активной платформы
#ifdef WIN32
	std::cout << "	[" << a << "]	Windows\n";
#elif defined(__linux__)
	std::cout << "	[" << a << "]	Linux\n";
#elif defined(__APPLE__) && defined(__MACH__)
	std::cout << "	[" << a << "]	macOS\n";
#else
	std::cout << "	[" << a << "]	Unknown platform\n";
#endif



	// Выводим версию и имя компилятора и стандарт языка
#ifdef __clang__
	std::cout << "	[" << a << "]	Clang " << __clang_major__ << "." << __clang_minor__ << "." << __clang_patchlevel__ << "\n";
#elif defined(__GNUC__)
	std::cout << "	[" << a << "]	GCC " << __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__ << "\n";
#elif defined(_MSC_VER)
	std::cout << "	[" << a << "]	MSVC " << _MSC_VER << "\n";
#else
	std::cout << "	[" << a << "]	Unknown compiler\n";
#endif



	return 0;
}
