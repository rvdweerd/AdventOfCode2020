// STL headers
#include <algorithm>
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
#include <iterator>
#include <queue>
#include <stack>
// Own headers
#include "Utils.h"
#include "Assembler.h"

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
namespace Day7 {
	std::map<std::string, std::vector<std::pair<std::string,int>>> GetDependencyMap() {
		std::map<std::string, std::vector<std::pair<std::string, int>>> map;
		std::ifstream in("Day7_input.txt");
		std::string str;
		while (std::getline(in, str)) {
			auto vec = Utils::split(str, ' ');
			std::string master;
			std::string runner;
			for (auto& word : vec) {
				if (word == "contain") {
					master = runner.substr(0,runner.size()-2);
					runner = "";
				}
				else if (*word.rbegin() == '.' or *word.rbegin() == ',') {
					
					runner += word.substr(0, word.size() - 1);
					auto i = runner.find_first_of(' ');
					std::string prefix = runner.substr(0, i);
					runner = runner.substr(i+1);
					if (runner.back() == 's') runner.pop_back();
					if (prefix == "no") {
						map[master] = {};
					}
					else {
						int n = std::stoi(prefix); // not used for now
						map[master].push_back({ runner , n});
					}
					runner = "";
				}
				else {
					runner += word+" ";
				}
			}
		}
		return std::move(map);
	}
	bool BagHoldsGoldBag(std::string topbag, std::map<std::string, std::vector<std::pair<std::string, int>>>& map) {
		std::set<std::string> set;
		std::queue<std::string> queue;
		for (auto bagpair : map[topbag]) {
			queue.push(bagpair.first);
		}
		while (!queue.empty()) {
			std::string bag = queue.front(); queue.pop();
			if (bag == "shiny gold bag") {
				return true;
			}
			if (set.find(bag) == set.end()) {
				set.insert(bag);
				for (auto childbagpair : map[bag]) queue.push(childbagpair.first);
			}
		}
		return false;
	}
	int nGoldBagCarriers(std::map<std::string, std::vector<std::pair<std::string, int>>>& map) {
		int n = 0;
		for (auto it = map.begin(); it != map.end(); ++it) {
			if (it->second.size() == 0) continue;
			if (BagHoldsGoldBag(it->first, map)) {
				n++;
			}
		}
		return n;
	}
	int nBagsInside(std::string topbag, std::map<std::string, std::vector<std::pair<std::string, int>>>& map) {
		//if (map[topbag].size() == 0) return 1;
		int sum = 0;
		for (auto bagpair : map[topbag]) {
			if (map[bagpair.first].size() == 0) {
				sum += bagpair.second;
			}
			else {
				sum += bagpair.second + bagpair.second * nBagsInside(bagpair.first, map);
			}
		}
		//std::cout << sum<<',';
		return sum;
	}
	void Solution()
	{
		auto map=GetDependencyMap();
		int n = nGoldBagCarriers(map);
		std::cout << "Part 1. Number of bags that can hold a gold bag: " << n<<'\n';
		int m = nBagsInside("shiny gold bag", map);
		std::cout << "Part 2. Number of bags inside the gold bag: " << m;
		std::cin.get();
	}
}
namespace Day8 {
	void Solution() {
		Assembler assembler("Day8_input.txt");
		auto ans = assembler.run();
		std::cout << "Part 1:" << ans.first;
		std::cin.get();
		int ans2 = assembler.fix();
		std::cout << "Part 2:" << ans2;
		std::cin.get();
	}
}
namespace Day9 {
	class Solution {
	public:
		Solution(std::string filename) {
			LoadData(filename);
		}
		void Solve() {
			// PART 1
			int seqLen = 25;
			std::vector<long long> runnerVec;
			std::copy(input.begin(), input.begin() + seqLen, std::back_inserter(runnerVec));
			int i = seqLen;
			while (i < input.size()) {
				validSums.clear();
				GetValidSums(runnerVec, 0, 0, seqLen, 2);
				if (validSums.find(input[i]) == validSums.end()) {
					break;
				}
				else {
					runnerVec.erase(runnerVec.begin());
					runnerVec.push_back(input[i]);
					i++;
				}
			}
			std::cout << "PART 1: ";
			if (i == input.size()) {
				std::cout << "All entries comply. No errors.\n";
			}
			else {
				std::cout << "First number that fails: " << input[i]<<'\n';
			}
			// PART 2
			long long target = input[i];
			std::pair<int, int> range = GetSumRange(target);
			auto smallest = std::min_element(input.begin()+range.first, input.begin() + range.second);
			auto largest = std::max_element(input.begin() + range.first, input.begin() + range.second);
			std::cout << "PART 2: Answer = " << *smallest + *largest;
		}
	private:
		void LoadData(std::string filename) {
			std::ifstream in("Day9_input.txt");
			std::string str;
			while (std::getline(in, str)) {
				input.push_back(std::stoll(str));
			}
		}
		void GetValidSums(std::vector<long long> vec, long long sum, int i, int n, int k)
		{
			// invalid input
			if (k > n)
				return;

			// base case: combination size is k
			if (k == 0) {
				//std::cout << sum << std::endl;
				validSums.insert(sum);
				return;
			}

			// start from next index till last index
			for (int j = i; j < n; j++)
			{
				// add current element arr[j] to solution & recur for next index
				// (j+1) with one less element (k-1)
				GetValidSums(vec, sum + vec[j], j + 1, n, k - 1);

				// uncomment below code to handle duplicates
				// while (j < n - 1 && arr[j] == arr[j + 1])
				//    j++;
			}
		}
		std::pair<int, int> GetSumRange(long long target) {
			int left = 0; int right = 0;
			int sum = 0;
			while (left <= right && right < input.size()) {
				while (sum < target && right < input.size()) {
					sum += input[right];
					right++;
				}
				while (sum > target && left <= right) {
					sum -= input[left];
					left++;
				}
				if (sum == target) return { left,right };
			}
			return { -1,-1 };
		}
	private:
		std::vector<long long> input;
		std::set<long long> validSums;
	};
}
namespace Day10 {
	class Solution {
	public:
		Solution(std::string filename) {
			LoadData(filename);
		}
		void LoadData(std::string filename) {
			std::ifstream in(filename);
			std::string str;
			while (std::getline(in, str)) {
				input.push_back(std::stoi(str));
			}
			std::sort(input.begin(), input.end());
		}
		void Solve() {
			// PART 1
			std::map<int, int> distribution;
			distribution[input[0]] = 1;
			distribution[3] = 1;
			for (size_t i = 1; i < input.size(); i++) {
				int diff = input[i] - input[i - 1];
				distribution[diff]++;
			}
			int ans = distribution[1] * distribution[3];
			std::cout << "Part 1: Ans = " << ans << '\n';

			// PART 2 (DP, will use recursion with memoization here)
			this->input.insert(input.begin(), 0);
			long long nRoutes = RecurseRoutes(0);
			std::cout<<"Part 2 (recursion): Number of routes = "<<nRoutes<<'\n';
			
			// PART 2 (DP Table)
			std::vector<long long> DP(input.size(), 0); DP.back() = 1;
			for (int i = input.size() - 2; i >= 0; i--) {
				auto options = GetOptions(i);
				for (auto o : options) {
					DP[i] += DP[o];
				}
			}
			std::cout << "Part 2 (DP table) : Number of routes = " << DP[0];
		}
		long long RecurseRoutes(int index) {
			auto it = cache.find(index);
			if (it != cache.end()) {
				return it->second;
			}
			std::vector<int> options = GetOptions(index);
			if (options.size() == 0) {
				//std::cout << '\n';
				return 1;
			}
			long long sum = 0;
			for (int v : options) {
				//std::cout << input[v] << ',';
				sum += RecurseRoutes(v);
			}
			cache[index] = sum;
			return sum;
		}
		std::vector<int> GetOptions(int index) {
			std::vector<int> out;
			for (size_t runner = index + 1; runner <= index + 3 && runner < input.size(); runner++) {
				if (input[runner] - input[index] <= 3) {
					out.push_back(runner);
				}
			}
			return out;
		}
	private:
		std::vector<int> input;
		std::unordered_map<int, long long> cache;
	};
}
int main(){
	Day10::Solution("Day10_input.txt").Solve();
	return 0;
}