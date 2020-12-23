#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <set>
#include <map>
#include <unordered_map>
#include <sstream>
#include <stdlib.h>

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
namespace Day3 {
	class Field
	{
	public:
		Field(std::string path) {
			std::ifstream in(path);
			std::string str;
			while (std::getline(in, str)){
				if (width != str.size()) std::cout << str.size() << ",";
				width = str.size();
				std::vector<char> line;
				for (size_t i = 0; i < str.size(); i++){
					char ch = str[i];
					line.push_back(ch);
				}
				field.push_back(line);
				height++;
			}
		}
		long long int Traverse(int stride, int drop) {
			long long int count = 0;
			int x=0; int y = 0;
			while (y < height){
				x = x % field[y].size();
				if (field[y][x] == '#') count++;
				x += stride;
				y += drop;
			}
			std::cout << "[(" << stride << "," << drop << "):" << count << "].";
			return count;
		}
	private:
		std::vector<std::vector<char>> field;
		int width;
		int height=0;
	};
	void Solution() {
		Field field("day3_input.txt");
		std::cout<<"Part 1. Ans="<<field.Traverse(3,1)<<'\n';
		long long int res = field.Traverse(1, 1) * field.Traverse(3, 1) * field.Traverse(5, 1) * field.Traverse(7, 1) * field.Traverse(1, 2);
		std::cout << "Part 2. Ans=" << res;
	}
}
namespace Day4{
	struct Record {
		std::map < std::string,std::string > entries;
		Record() {
			entries.insert({ "byr","" });
			entries.insert({ "iyr","" });
			entries.insert({ "eyr","" });
			entries.insert({ "hgt","" });
			entries.insert({ "hcl","" });
			entries.insert({ "ecl","" });
			entries.insert({ "pid","" });
			entries.insert({ "cid","" });
		}
		void Insert(std::string entry,std::string val) {
			auto it = entries.find(entry);
			if (it != entries.end()) {
				if (it->second == "") filled++;
				it->second = val;
			}
		}
		void Clear(){
			for (auto& e : entries) {
				e.second = "";
			}
			filled = 0;
			//valid = false;
		}
		bool IsValid() {
			if (filled < 7) return false;
			if (filled == 7 && entries["cid"] != "") return false;
			if (std::stoi(entries["byr"]) < 1920 || std::stoi(entries["byr"]) > 2002) {
				//std::cout << "BYR invalid:" << entries["byr"]<<'\n';
				return false;
			}
			if (std::stoi(entries["iyr"]) < 2010 || std::stoi(entries["iyr"]) > 2020) {
				//std::cout << "IYR invalid:" << entries["iyr"] << '\n'; 
				return false;
			}
			if (std::stoi(entries["eyr"]) < 2020 || std::stoi(entries["eyr"]) > 2030) {
				//std::cout << "EYR invalid:" << entries["eyr"] << '\n';
				return false;
			}
			auto hgt_str = entries["hgt"];
			std::string units = hgt_str.substr(hgt_str.size() - 2);
			int length = std::stoi(hgt_str.substr(0, hgt_str.size() - 1));
			if (units == "cm") {
				if (length < 150 || length >193) return false;
			}
			else if (units == "in") {
				if (length < 59 || length >76) return false;
			}
			else return false;
			if (entries["hcl"][0] != '#') {
				std::cout << "HCL invalid:" << entries["hcl"] << '\n';
				return false;
			}
			if (entries["hcl"].substr(1).size() != 6) {
				std::cout << "HCL invalid:" << entries["hcl"] << '\n';
				return false;
			}
			auto t = entries["ecl"];
			if (!(t=="amb"||t=="blu" || t == "brn" || t == "gry" || t == "grn" || t == "hzl" || t == "oth")) {
				std::cout << "ECL invalid:" << entries["ecl"] << '\n';
				return false;
			}
			if (entries["pid"].size() != 9) {
				std::cout << "PID invalid:" << entries["pid"] << '\n';
				return false;
			}
			/*if (entries["cid"].size() != 3) {
				std::cout << "cid invalid:" << entries["cid"] << '\n';
			}*/
			return true;
		}
		int filled = 0;
		int n_records = 8;
		//bool valid = false;

	};
	class Dbase
	{
	public:
		Dbase(std::string path) {
			std::ifstream in(path);
			std::string str;
			Record rec;
			std::string key = "";
			std::string val = "";
			while (std::getline(in, str)) {
				if (str == "") { //empty line
					records.push_back(rec);
					if (rec.IsValid()){
						n_valid_records++;
					}
					//PrintRecord(rec);
					rec.Clear();
				}
				for (char& ch : str) {
					if (ch == ':') {
						key = val;
						val = "";
					}
					else if (ch == ' ') {
						rec.Insert(key,val);
						key = "";
						val = "";
					}
					else {
						val += ch;
					}
				}
				rec.Insert(key, val);
				key = "";
				val = "";
			}
			rec.Insert(key, val);
			records.push_back(rec);
			if (rec.IsValid()) {
				n_valid_records++;
			}
			//PrintRecord(rec);
			rec.Clear();
		}
		void PrintRecord(Record& rec) {
			//std::cout << '\n';
			system("CLS");
			for (auto& e : rec.entries) {
				std::cout << "[" << e.first << "]:" << (e.second == "" ? "..." : e.second) << "" << '\n';
			}
			std::cout << "filled:" << rec.filled << '\n';
			std::cout << "valid:" << rec.IsValid() << '\n';
			std::cout << "total count:" << records.size() << '\n';
			std::cout << "valid      :" << n_valid_records << '\n';
			std::cin.get();

		}
		int GetNumValids() {
			return n_valid_records;
		}
		int GetNumDocs() {
			return records.size();
		}
		void test() {
			int count = 0;
			for (auto e : records) {
				if (e.n_records<8 && e.entries["cid"]=="") count++;
			}
			int k = 0;
		}
	private:
		std::vector<Record> records;
		int n_valid_records=0;

	};
	void Solution() {
		Dbase dbase("Day4_input.txt");
		std::cout << "Number of docs  :" << dbase.GetNumDocs()<<'\n';
		std::cout << "Number of valids:" << dbase.GetNumValids();
		dbase.test();
	}
}
namespace Day5 {
	int ProcessInput() {	
		std::ifstream in("Day5_input.txt");
		std::string str;
		std::set<int> filled;
		int seat_max = 0;
		while (std::getline(in, str)) {
			std::string bin_str="";
			for (char ch:str) {
				if (ch == 'B' || ch == 'R') {
					bin_str += '1';
				}
				else if (ch == 'F' || ch == 'L') {
					bin_str += '0';
				}
			}
			int seat_id = std::stoi(bin_str, 0, 2);
			filled.insert(seat_id);
		}
		for (auto it = filled.begin(); it != filled.end(); ++it){
			if ((*std::next(it) - *it) == 2) {
				std::cout << "Your seat:" << *it + 1<<'\n';
				break;
			}
		}
		return *filled.rbegin();
	}
	void Solution() {
		std::cout << "Highest seat_id:"<<ProcessInput();
	}
}
namespace Day6 {
	int CalcAns1() {
		std::ifstream in("Day6_input.txt");
		std::string str;
		std::set<char> set;
		int sum = 0;
		while (std::getline(in, str)){
			if (str == "") {
				int num = set.size();
				set.clear();
				sum += num;
				std::cout << "plus "<<num<<'\n';
			}
			for (char ch : str) {
				set.insert(ch);
			}
		}
		int num = set.size();
		sum += num;
		return sum;
	}
	int CalcAns2() {
		std::ifstream in("Day6_input.txt");
		std::string str;
		std::map<char,int> map;
		int sum = 0;
		int n = 0;
		while (std::getline(in, str)) {
			if (str == "") {
				for (auto& it : map) {
					if (it.second == n) sum++;
				}
				map.clear();
				n=0;
				continue;
			}
			for (char ch : str) {
				map[ch]++;
			}
			n++;
		}
		for (auto& it : map) {
			if (it.second == n) sum++;
		}
		return sum;
	}
	void Solution() {
		std::cout << "Part 1, sum="<<CalcAns1()<<'\n';
		std::cout << "Part 2, sum=" << CalcAns2();
	}
}
int main()
{
	Day6::Solution();
	std::cin.get();
	return 0;
}