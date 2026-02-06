// Для capture output (void-методы печатают в cout)
#include <sstream>  // Для stringstream — перехват cout
#include <iostream> // Для std::cout
#include <gtest/gtest.h>  // Основной header GTest (EXPECT_*, ASSERT_*)
#include "TestFile.hpp"   // Включаем header класса для доступа к методам



// Тесты группируются в suites (TestClassTests) для организации
TEST( TestClassTests, DisplayMessage ) {
	// Перехватываем output, чтобы проверить, что метод печатает
	std::stringstream buffer;          // Фейковый stream вместо cout
	std::streambuf* old = std::cout.rdbuf( buffer.rdbuf() );  // Redirect cout

	TestClass::display_message();  // Вызываем статический метод

	std::cout.rdbuf( old );  // Восстанавливаем cout
	std::string output = buffer.str();  // Получаем, что напечаталось

	// Проверяем: EXPECT — non-fatal (тест продолжается даже если fail)
	EXPECT_EQ( output, "This is a test class for CI/CD pipeline.\n" );
}

//TEST( TestClassTests, NewTestFoo ) {
//	TestClass obj;  // Создаём объект
//
//	// Аналогично перехват output (метод печатает a_)
//	std::stringstream buffer;
//	std::streambuf* old = std::cout.rdbuf( buffer.rdbuf() );
//
//	obj.new_test_foo();  // Вызываем
//
//	std::cout.rdbuf( old );
//	std::string output = buffer.str();
//
//	EXPECT_EQ( output, "test 15\n" );  // Проверяем на значение a_ (15)
//}
//
//TEST( TestClassTests, EulerTotient ) {
//	TestClass obj;
//
//	// Простые случаи: Вызываем, проверяем return
//	EXPECT_EQ( obj.euler_totient( 1 ), 1 );    // Для 1
//	EXPECT_EQ( obj.euler_totient( 5 ), 4 );    // Простое число
//	EXPECT_EQ( obj.euler_totient( 10 ), 4 );   // 10 = 2*5
//	EXPECT_EQ( obj.euler_totient( 28 ), 12 );  // 28 = 2^2*7
//
//	// ASSERT — fatal (если fail, тест stop)
//	ASSERT_EQ( obj.euler_totient( 0 ), 0 );  // Edge case (хотя для 0 undefined, но по коду result=0)
//}
//
//TEST( TestClassTests, NormalDistributionPdf ) {
//	TestClass obj;
//
//	// Проверяем на известных значениях (mean=0, stddev=1 — standard normal)
//	double result = obj.normal_distribution_pdf( 0.0, 0.0, 1.0 );
//	EXPECT_DOUBLE_EQ( result, 0.3989422804014327 );  // Примерное значение (1/sqrt(2*pi))
//
//	// Другой случай
//	EXPECT_NEAR( obj.normal_distribution_pdf( 1.0, 0.0, 1.0 ), 0.24197072451914337, 1e-10 );  // NEAR для floating-point с tolerance
//}
//
//TEST( TestClassTests, LagrangePoints ) {
//	TestClass obj;
//
//	// Входные данные (placeholder, адаптируй под реальные)
//	double mass_a = 1.0, mass_b = 0.1;
//	double ang_vel_a = 0.0, ang_vel_b = 1.0;
//	double ecc_b = 0.0;
//	double x1 = 0.0, y1 = 0.0, x2 = 10.0, y2 = 0.0;
//
//	auto points = obj.lagrange_points( mass_a, mass_b, ang_vel_a, ang_vel_b, ecc_b, x1, y1, x2, y2 );
//
//	// Проверяем размер вектора (4 точки L1-L4)
//	ASSERT_EQ( points.size(), 4 );
//
//	// Проверяем конкретные значения (из placeholder в коде)
//	EXPECT_EQ( points[0], std::make_pair( 5LL, 0LL ) );  // L1: (5,0)
//	EXPECT_EQ( points[1], std::make_pair( 15LL, 10LL ) );  // L2
//	EXPECT_EQ( points[2], std::make_pair( -5LL, -10LL ) ); // L3
//	EXPECT_EQ( points[3], std::make_pair( 10LL, 15LL ) );  // L4
//}
//
//// Main для GTest (gtest_main auto запускает все тесты)
//int main( int argc, char** argv ) {
//	::testing::InitGoogleTest( &argc, argv );
//	return RUN_ALL_TESTS();
//}