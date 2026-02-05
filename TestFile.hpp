#pragma once
#include <cmath>
#include <iostream>
#include <vector>




// Тестовый класс для CI/CD пайплайна
class TestClass {

	int a_{ 15 };

public:
	static void display_message();

	void new_test_foo() const;


	// Тестовый метод сложного математического вычисления (теорема Эйлера)
	int euler_totient( int n ) const;

	// Расчёт интеграла плотности вероятности нормального распределения
	double normal_distribution_pdf( double x, double mean, double stddev ) const;

	// Расчёт координат точек Лагранжа L1, L2, L3, L4 для двух тел (аргументы: масса a,b, угловая скорость a,b,эксцентриситет общей арбиты b. считаем что объект a статичен )
	std::vector<std::pair<int64_t, int64_t>> lagrange_points(
		const double mass_a,
		const double mass_b,
		const double angular_velocity_a,
		const double angular_velocity_b,
		const double eccentricity_b,
		const double& x1,
		const double& y1,
		const double& x2,
		const double& y2 
	) const;






};
