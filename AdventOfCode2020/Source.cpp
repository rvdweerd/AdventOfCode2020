#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <sstream>

namespace Day1
{
	int Get2Product(std::vector<int>& in)
	{
		std::unordered_set<int> set;
		for (auto& v : in)
		{
			const int target = 2020-v;
			auto it = set.find(v);
			if (it != set.end())
			{
				return target*v;
			}
			else
			{
				set.insert(target);
			}
		}
	}
	int Get3Product(std::vector<int>& in,int target)
	{
		//int target = 2020;
		std::unordered_map<int,int> map2;
		std::unordered_map<int, int> map1;
		for (auto& v : in)
		{
			auto it = map1.find(v);
			if (it != map1.end())
			{
				return v * it->second;
			}
			for (auto& v_2 : map2)
			{
				map1[v_2.first - v] = v_2.second * v;
			}
			map2[target - v] = v;
		}
	}

	std::vector<int> LoadInput(std::string filepath)
	{
		std::ifstream in(filepath);
		std::vector<int> input;
		while (!in.eof())
		{
			std::string str;
			for (char ch = in.get(); ch != '\n' && !in.eof(); ch = in.get())
			{
				str += ch;
			}
			input.push_back(std::stoi(str));
		}
		return input;
	}
	void Solution()
	{
		std::vector<int> data = Day1::LoadInput("Day1_input.txt");
		int ans1 = Day1::Get2Product(data);
		int ans2 = Day1::Get3Product(data, 2020);
		std::cout << "Answer1:" << ans1 << '\n';
		std::cout << "Answer2:" << ans2;
		std::cin.get();
	}
}

namespace Day2
{
	int CountValid1()
	{
		//Day1::Solution();
		int valid = 0;
		std::ifstream in("Day2_input.txt");
		std::vector<int> input;
		std::string line;
		while (!in.eof())
		{
			std::getline(in, line, '\n');
			auto iss = std::istringstream(line);
			auto str = std::string{};
			// Extract first substring
			iss >> str;
			auto i = str.find('-');
			int min = std::stoi(str.substr(0, i));
			int max = std::stoi(str.substr(i + 1));
			// Extract second substring
			iss >> str;
			char ch = str[0];
			// Extract third substring
			iss >> str;
			int count = 0;
			for (char c : str)
			{
				if (c == ch)
				{
					count++;
				}
			}
			if ((count >= min) && (count <= max))
			{
				valid += 1;
			}
			//while (iss >> str)
			//{
			//}
		}
		return valid;
	}
	int CountValid2()
	{
		//Day1::Solution();
		int valid = 0;
		std::ifstream in("Day2_input.txt");
		std::vector<int> input;
		std::string line;
		while (!in.eof())
		{
			std::getline(in, line, '\n');
			auto iss = std::istringstream(line);
			auto str = std::string{};
			// Extract first substring
			iss >> str;
			auto i = str.find('-');
			int min = std::stoi(str.substr(0, i));
			int max = std::stoi(str.substr(i + 1));
			// Extract second substring
			iss >> str;
			char ch = str[0];
			// Extract third substring
			iss >> str;
			valid += ((str[min-1]==ch) != (str[max-1] == ch));
			//while (iss >> str)
			//{
			//}
		}
		return valid;
	}

	void Solution()
	{
		int ans1 = CountValid1();
		std::cout << "valid:" << ans1;
		int ans2 = CountValid2();
		std::cout << "valid:" << ans2;
		std::cin.get();
		//int ans2 = CountValid2();
	}
}

int main()
{
	Day2::Solution();
	return 0;
}