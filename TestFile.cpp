#include "TestFile.hpp"

void TestClass::display_message()
{
	std::cout << "This is a test class for CI/CD pipeline.\n";
}

void TestClass::new_test_foo() const
{
	std::cout << "test " << a_ << "\n";
}

int TestClass::euler_totient( int n ) const
{
	int result = n; // Initialize result as n
	// Consider all prime factors of n
	for( int p = 2; p * p <= n; ++p )
	{
		// Check if p is a divisor of n
		if( n % p == 0 )
		{
			// If yes, then it is a prime factor
			while( n % p == 0 )
				n /= p;
			result -= result / p;
		}
	}
	// If n has a prime factor greater than sqrt(n)
	if( n > 1 )
		result -= result / n;
	return result;
}

double TestClass::normal_distribution_pdf( double x, double mean, double stddev ) const
{
	const double pi = 3.14159265358979323846;
	double coeff = 1.0 / (stddev * sqrt( 2.0 * pi ));
	double exponent = -((x - mean) * (x - mean)) / (2.0 * stddev * stddev);
	return coeff * exp( exponent );
}

std::vector<std::pair<int64_t, int64_t>> TestClass::lagrange_points( const double mass_a, const double mass_b, const double angular_velocity_a, const double angular_velocity_b, const double eccentricity_b, const double& x1, const double& y1, const double& x2, const double& y2 ) const
{
	std::vector<std::pair<int64_t, int64_t>> points;
	// Placeholder calculations for Lagrange points
	points.emplace_back( static_cast<int64_t>( (x1 + x2) / 2 ), static_cast<int64_t>( (y1 + y2) / 2 ) ); // L1
	points.emplace_back( static_cast<int64_t>( (x1 + x2) / 2 + 10 ), static_cast<int64_t>( (y1 + y2) / 2 + 10 ) ); // L2
	points.emplace_back( static_cast<int64_t>( (x1 + x2) / 2 - 10 ), static_cast<int64_t>( (y1 + y2) / 2 - 10 ) ); // L3
	points.emplace_back( static_cast<int64_t>( (x1 + x2) / 2 + 5 ), static_cast<int64_t>( (y1 + y2) / 2 + 15 ) ); // L4
	return points;
}
