#include <iostream>
#include <string>
#include <array>

long nbonacci(unsigned int series, unsigned int n);
void computeNbonacciRatio(std::string title, unsigned int series);

int main() {
	using namespace std::string_literals;
	std::array<std::array<int, 20>, 4> results;

	for (int i = 1; i <= 20; i++) {
		for (int j = 2; j <= 5; j++) {
			results[j - 2][i - 1] = nbonacci(j, i);
		}
	}

	std::cout << "--- Fibonacci Sequence ---"s << std::endl;

	for (int i = 0; i < results[0].size(); i++) {
		std::cout << results[0][i] << " ";
	}

	std::cout << std::endl;

	std::cout << "--- Tribonacci Sequence ---"s << std::endl;

	for (int i = 0; i < results[1].size(); i++) {
		std::cout << results[1][i] << " ";
	}

	std::cout << std::endl;

	std::cout << "--- Fourbonacci Sequence ---"s << std::endl;

	for (int i = 0; i < results[2].size(); i++) {
		std::cout << results[2][i] << " ";
	}

	std::cout << std::endl;

	std::cout << "--- Fivebonacci Sequence ---"s << std::endl;

	for (int i = 0; i < results[3].size(); i++) {
		std::cout << results[3][i] << " ";
	}

	std::cout << std::endl;
	std::cout << std::endl;


	computeNbonacciRatio("Fibonacci", 2);
	std::cout << std::endl;
	computeNbonacciRatio("Tribonacci", 3);
	std::cout << std::endl;
	computeNbonacciRatio("Fourbonacci", 4);
	std::cout << std::endl;
	computeNbonacciRatio("Fivebonacci", 5);
	std::cout << std::endl;
	

}

long nbonacci(unsigned int series, unsigned int n) {
	// Note: I Don't Know How to Raise Exceptions in C++, So I Won't Add Error Handling Here
	if (n <= 0) {
		return 0;
	}
	if (n <= series) {
		return 1;
	}

	long result = 0;
	for (unsigned int i = 1; i <= series; i++) {
		result += nbonacci(series, (n - i));
	}

	return result;
	
}
void computeNbonacciRatio(std::string title, unsigned int series) {
	const float ERROR = 0.000001f;

	decltype(auto) iterations = series + 1;
	long current = 1;
	long next = nbonacci(series, iterations);
	float currentRatio = 1;
	float nextRatio = next / static_cast<float>(current);

	while (std::abs(nextRatio - currentRatio) > ERROR) {
		current = next;
		next = nbonacci(series, ++iterations);
		currentRatio = nextRatio;
		nextRatio = next / static_cast<float>(current);
	}

	std::cout << title << " Ratio Approaches " << currentRatio << " After " << iterations - 1 << " Iterations" << std::endl;
}