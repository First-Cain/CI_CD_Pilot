#include <iostream>










// Тестовый класс для CI/CD пайплайна
class TestClass {
    public:
	static void display_message() {
        std::cout << "This is a test class for CI/CD pipeline.\n";
    }
};









int main()
{

    TestClass::display_message();
	return 0;
}