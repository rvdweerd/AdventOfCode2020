#pragma once
#include <vector>
#include <string>
#include <iterator>

namespace Utils {
	template <typename Out>
	void split(const std::string& s, char delim, Out result) {
		std::istringstream iss(s);
		std::string item;
		while (std::getline(iss, item, delim)) {
			*result++ = item;
		}
	}
	std::vector<std::string> split(const std::string& s, char delim) {
		std::vector<std::string> elems;
		split(s, delim, std::back_inserter(elems));
		return elems;
	}
	long long gcd(long long a, long long b)
	{
		if (a == 0)
			return b;
		return gcd(b % a, a);
	}
	// To compute x^y under modulo m 
	long long power(long long x, unsigned long long y, unsigned long long m)
	{
		if (y == 0)
			return 1;
		int p = power(x, y / 2, m) % m;
		p = (p * p) % m;

		return (y % 2 == 0) ? p : (x * p) % m;
	}
	// Function to find modular inverse of a under modulo m 
	// Assumption: m is prime 
	long long modInverse_Fermat(long long a, long long m){
		int g = gcd(a, m);
		if (g != 1)
			std::cout << "Inverse doesn't exist";
		else
		{
			// If a and m are relatively prime, then modulo 
			// inverse is a^(m-2) mode m 
			//cout << "Modular multiplicative inverse is "
			//	<< power(a, m - 2, m);
			return power(a, m - 2, m);
		}
	}
	std::string ToBin(unsigned long long n, int min_digits = 0)
	{
		std::string bin_str;
		for (int count = 0; n != 0 || count < min_digits; n >>= 1, count++)
		{
			bin_str.push_back(bool(n & 0b1) ? '1' : '0');
		}
		std::reverse(bin_str.begin(), bin_str.end());
		return bin_str;
	}
}