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
#include "Expressions.h"

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
namespace Day11 {
	struct Field {
		std::vector<std::vector<std::vector<char>>> copies;
		int occupied = 0;
		//bool side = 1;
	};
	class Solution {
	public:
		Solution(std::string filename) {
			LoadData(filename);
		}
		void LoadData(std::string filename) {
			std::ifstream in(filename);
			std::string str;
			while (std::getline(in, str)) {
				std::vector<char> line;
				for (char c : str) {
					line.push_back(c);
					if (c == '#') field.occupied++;
				}
				field_original.push_back(line);
			}
			field.copies.push_back(field_original);
			field.copies.push_back(field_original);
			height = field_original.size();
			width = field_original[0].size();
		}
		void Print(int side) {
			for (auto vec : field.copies[side]) {
				for (auto p : vec) {
					std::cout << p;
				}
				std::cout << '\n';
			}
		}
		int OccupiedNeighbors(int y, int x, bool side) {
			int xmin = std::max(0, x - 1);
			int xmax = std::min(width-1, x + 1);
			int ymin = std::max(0, y - 1);
			int ymax = std::min(height-1, y + 1);
			int count = 0;
			for (int row = ymin; row <= ymax; row++) {
				for (int col = xmin; col <= xmax; col++) {
					if (row == y && col == x) continue;
					if (field.copies[side][row][col] == '#') {
						count++;
					}
				}
			}
			return count;
		}
		char Look(int y, int x,int yDir, int xDir) {
			y += yDir; x += xDir;
			while (y >= 0 && y < height && x >= 0 && x < width) {
				if (field.copies[1][y][x] != '.') return field.copies[1][y][x];
				y += yDir; x += xDir;
			}
			return '.';
		}
		int OccupiedVisibleNeighbors(int y, int x, bool side) {
			int count = 0;
			count += Look(y, x, 1, 0) == '#';
			count += Look(y, x, -1, 0) == '#';
			count += Look(y, x, 0, 1) == '#';
			count += Look(y, x, 0, -1) == '#';
			count += Look(y, x, 1, 1) == '#';
			count += Look(y, x, 1, -1) == '#';
			count += Look(y, x, -1, 1) == '#';
			count += Look(y, x, -1, -1) == '#';
			return count;
		}
		int Step() {
			// field 1 fixed for evaluation, field 0 gets new seating assigned
			int flips = 0;
			for (int row = 0; row < height; row++) {
				for (int col = 0; col < width; col++) {
					char current = field.copies[1][row][col];
					if (current == '.') continue;
					int occupiedNeighbors = OccupiedNeighbors(row, col, 1);
					if (current == 'L' && occupiedNeighbors == 0) {
						field.copies[0][row][col] = '#';
						field.occupied++;
						flips++;
					}
					else if (current == '#' && occupiedNeighbors >= 4) {
						field.copies[0][row][col] = 'L';
						field.occupied--;
						flips++;
					}
				}
			}
			field.copies[1].assign(field.copies[0].begin(), field.copies[0].end());
			std::cout << "Flips:" << flips << ", Occupied: "<<field.occupied<<'\n';
			return flips;
		}
		int Step2() {
			// field 1 fixed for evaluation, field 0 gets new seating assigned
			int flips = 0;
			for (int row = 0; row < height; row++) {
				for (int col = 0; col < width; col++) {
					char current = field.copies[1][row][col];
					if (current == '.') continue;
					int occupiedNeighbors = OccupiedVisibleNeighbors(row, col, 1);
					if (current == 'L' && occupiedNeighbors == 0) {
						field.copies[0][row][col] = '#';
						field.occupied++;
						flips++;
					}
					else if (current == '#' && occupiedNeighbors >= 5) {
						field.copies[0][row][col] = 'L';
						field.occupied--;
						flips++;
					}
				}
			}
			field.copies[1].assign(field.copies[0].begin(), field.copies[0].end());
			std::cout << "Flips:" << flips << ", Occupied: " << field.occupied << '\n';
			return flips;
		}

		void Solve() {
			// PART 1
			int nSteps = 0;
			while (Step()) {
				nSteps++;
				std::cout << "STEP " << nSteps<<'\n';
				system("CLS");
				//Print(1);
				//std::cin.get();
			}
			Print(1);
			std::cout << "Part 1.\nStability after " << nSteps << " steps. Seats occupied in equilibrium: " << field.occupied<<'\n';
			std::cin.get();
			// PART 2
			field.copies.clear();
			field_original.clear();
			field.occupied = 0;
			LoadData("Day11_input.txt");
			Print(1);
			nSteps = 0;
			while (Step2()) {
				nSteps++;
				std::cout << "STEP " << nSteps << '\n';
				system("CLS");
				//Print(1);
				//std::cin.get();
			}
			Print(1);
			std::cout << "Part 2.\nStability after " << nSteps << " steps. Seats occupied in equilibrium: " << field.occupied << '\n';
			std::cin.get();
		}
	private:
		std::vector<std::vector<char>> field_original;
		Field field;
		int width;
		int height;
	};
}
namespace Day12{
	class DIR {
		enum bDIR {
			N,E,S,W
		};
	public:
		bDIR d = E;
		void increment(int n) {
			d = bDIR((d + n) % 4);
			if (d < 0) {
				d = bDIR(d+4);
			}
		}
		char Char() {
			switch (d) {
			case 0: return 'N';
			case 1: return 'E';
			case 2: return 'S';
			case 3: return 'W';
			}
		}
	};
	class Solution {
	public:
		Solution(std::string filename) {
			LoadData(filename);
		}
		void LoadData(std::string filename) {
			std::ifstream in(filename);
			std::string str;
			while (std::getline(in, str)) {
				instructions.push_back({ str[0],std::stoi(str.substr(1)) });
			}
		}
		void Move(std::pair<char,int> i) {
			switch (i.first) {
			case 'N': 
				pos.y += i.second;
				break;
			case 'S': 
				pos.y -= i.second;
				break;
			case 'E': 
				pos.x += i.second;
				break;
			case 'W': 
				pos.x -= i.second;
				break;
			case 'L': 
				dir.increment(-i.second/90);
				break;
			case 'R':
				dir.increment(i.second/90);
				break;
			case 'F': 
				Move({ dir.Char(),i.second });
			default: 
				break;
			}
		}
		void MoveUsingWP(std::pair<char, int> i) {
			switch (i.first) {
			case 'N':
				WP.y += i.second;
				break;
			case 'S':
				WP.y -= i.second;
				break;
			case 'E':
				WP.x += i.second;
				break;
			case 'W':
				WP.x -= i.second;
				break;
			case 'L':
				WP.Rotate(-i.second);
				break;
			case 'R':
				WP.Rotate(i.second);
				break;
			case 'F':
				pos.x = pos.x + WP.x * i.second;
				pos.y = pos.y + WP.y * i.second;
			default:
				break;
			}
		}
		void Solve() {
			// PART 1
			std::cout << "Part 1:\n";
			for (auto instr : instructions) {
				Move(instr);
				//std::cout << "Instruction: " << instr.first << instr.second<<", new position: ("<<pos.x<<','<<pos.y<<"), Direction: "<<dir.Char()<<"\n";
				//std::cin.get();
			}
			std::cout << "End position: (" << pos.x << ',' << pos.y << "), Manhattan distance from origin: "<<(std::abs(pos.x)+std::abs(pos.y))<<'\n';

			// PART 2
			std::cout << "Part 2:\n";
			pos = { 0,0 };
			for (auto instr : instructions) {
				MoveUsingWP(instr);
				//std::cout << "Instruction: " << instr.first << instr.second<<", new position: ("<<pos.x<<','<<pos.y<<"), WP: (" << WP.x << ',' << WP.y << ")"<<"\n";
				//td::cin.get();
			}
			std::cout << "End position: (" << pos.x << ',' << pos.y << "), Manhattan distance from origin: " << (std::abs(pos.x) + std::abs(pos.y)) << '\n';

		}
	private:
		struct Pos {
			int x=0;
			int y=0;
			void Rotate(int degrees) {
				degrees = degrees % 360;
				if (degrees < 0) degrees += 360;
				int x_tmp = x;
				switch (degrees) {
				case 90:
					x = y;
					y = -x_tmp;
					break;
				case 180:
					x = -x;
					y = -y;
					break;
				case 270:
					x = -y;
					y = x_tmp;
					break;
				default:
					break;
				}
			}
		};
		std::vector<std::pair<char, int>> instructions;
		//DIR dir = DIR::E;
		Pos pos;
		DIR dir;
		Pos WP{ 10,1 };
	};
}
namespace Day13 {
	class Solution {
	public:
		Solution(std::string filename) {
			LoadData(filename);
		}
		void LoadData(std::string filename) {
			std::ifstream in(filename);
			std::string str;
			std::getline(in, str);
			eTS = std::stoi(str);
			std::getline(in, str);
			std::vector<std::string> tokens = Utils::split(str, ',');
			int offset = 0;
			for (auto t : tokens) {
				if (t != "x") {
					int v = std::stoi(t);
					busLines.push_back(v);
					busLines_offsets.push_back({ v,offset });
					N *= v;
				}
				offset++;
			}
		}
		void Solve() {
			// PART 1
			int busIdx = 0;
			int minWait = 2e9;
			for (int i = 0; i < busLines.size();i++) {
				int wait = - eTS % busLines[i] + busLines[i];
				if (wait < minWait) {
					minWait = wait;
					busIdx = i;
				}
			}
			std::cout << "Part 1:\nans = " << minWait*busLines[busIdx]<<'\n';

			// PART 2
			long long t = 0;
			//N /= busLines[0];
			for (int i = 0; i < busLines_offsets.size(); i++) {
				int offset = busLines_offsets[i].second;
				int n_i = busLines_offsets[i].first;
				int b_i = -offset;
				do {
					b_i += n_i;
				} while (b_i < 0);
				b_i = b_i % n_i;
				if (b_i == 0) continue;
				long long N_i = N / n_i;
				long long x_i = Utils::modInverse_Fermat(N_i, n_i);
				long long t_i = ((b_i * N_i) * x_i) % N;
				t += t_i;
				//std::cout << "t_i:" << t_i<<"\n--------------\n";
				//std::cout << "t  :" << t << '\n';
			}
			t = t % N;
			std::cout << "Part 2:\nans = " << t << '\n';
		}
	private:
		int eTS;
		std::vector<int> busLines;
		std::vector<std::pair<int,int>> busLines_offsets;
		long long N=1; // product of modulars
	};
}
namespace Day14 {
	struct Instruction
	{
		int address;
		long long value;
	};
	struct InstructionBlock {
		std::string mask_str;
		unsigned long long mask=0;
		unsigned long long mash=0-1;
		std::vector<Instruction> instructions;
	};
	struct FilterBank {
		FilterBank() {
			unsigned long long base = 1;
			unsigned long long maskZeros = 0;
			unsigned long long mashOnes = 0 - 1;
			for (size_t i = 0; i < 36; i++) {
				unimask[i]= maskZeros | (base << i);
				unimash[i]= mashOnes ^ (base << i);
			}
			//for (auto v : unimask) {
			//	std::cout << Utils::ToBin(v.second,64) << '\n';
			//}
			//for (auto v : unimash) {
			//	std::cout << Utils::ToBin(v.second, 64) << '\n';
			//}
		}
		std::map<int, unsigned long long> unimask;
		std::map<int, unsigned long long> unimash;
	};
	class Solution {
	public:
		Solution(std::string filename) {
			LoadData(filename);
		}
		void Solve() {
			// PART 1.
			{
				long long sum = 0;
				for (const auto& m : memory) {
					sum += m.second;
				}
				std::cout << "Part 1.\nSum = " << sum << '\n';
			}
			// PART 2.
			memory.clear();
			for (const auto& block : instructionBlocks) {
				for (const auto& instr : block.instructions) {
					unsigned long long address = block.mask | (instr.address);// &block.mash);
					//std::cout << "org adr : " << Utils::ToBin(instr.address, 64) << '\n';
					//std::cout << "mask_str: " << std::string(64 - 36, '.') << block.mask_str << '\n';
					//std::cout << "mask    : " << Utils::ToBin(block.mask, 64) << '\n';
					//std::cout << "mash    : " << Utils::ToBin(block.mash, 64) << '\n';
					//std::cout << "new adr : " << Utils::ToBin(address, 64) << " ("<<address<<")"<< '\n';
					std::vector<unsigned long long> addressVariations = {address};
					for (size_t i = 0; i < block.mask_str.size(); i++) {
						if (block.mask_str[block.mask_str.size() - i-1] == 'X') { // process starting from least significant bit on the right
							int K = addressVariations.size();
							for (size_t k = 0; k < K; k++) {
								addressVariations.push_back(addressVariations[k] ^ filterBank.unimask[i]);
								//std::cout << "variant : "<<Utils::ToBin(addressVariations.back(),64) << " ("<<addressVariations.back() <<")"<<'\n';
							} //std::cout << '\n';
						}
					}
					// Apply instructions for this set of address variations
					for (auto adr : addressVariations) { 
						memory[adr] = instr.value;
					}
				}
			}
			long long sum = 0;
			for (const auto& m : memory) {
				sum += m.second;
			}
			std::cout << "Part 2.\nSum = " << sum << '\n';
		}
	private:
		void LoadData(std::string filename) {
			unsigned long long mask = 0;
			unsigned long long mash = 0 - 1; // all 1 binary
			std::ifstream in(filename);
			std::string str;
			InstructionBlock block;
			while (std::getline(in, str)) {
				if (str.substr(0, 3) == "mas")
				{
					mask = 0;
					mash = 0 - 1; // all 1 binary
					std::string mask_str = str.substr(7);
					if (block.instructions.size() != 0) {
						instructionBlocks.push_back(block);
					}
					for (size_t i = 0; i < mask_str.size(); i++) {
						if (mask_str[i] == '1') {
							mask = mask | (base << (34 - i +1 ));
							//std::cout << Utils::ToBin(mask, 64) << '\n';
						}
						else if (mask_str[i] == '0') {
							mash = mash ^ (base << (34 - i + 1));
							//std::cout << Utils::ToBin(mash,64)<<'\n';
						}
					}
					block.mask_str = mask_str;
					block.mask = mask;
					block.mash = mash;
					block.instructions.clear();
				}
				else {
					str = str.substr(4);
					size_t i = str.find(']');
					int address = std::stoi(str.substr(0, i));
					long long val = std::stoll(str.substr(i + 4));
					block.instructions.push_back(Instruction({ address,val }));
					memory[address] = ( mask | ( val & mash ));
				}
			}
			instructionBlocks.push_back(block);			
		}
	private:
		FilterBank filterBank;
		long long base = 1;
		std::unordered_map<long long, long long> memory;
		std::vector<InstructionBlock> instructionBlocks;
	};
}
namespace Day15 {
	class Solution {
		struct Mem2 {
			void Insert(int n) {
				penult = ult;
				ult = n;
				diff = ult - penult;
			}
			int ult=-1;
			int penult=-1;
			int diff = 0;
		};
	public:
		Solution(std::string filename) {
			LoadData(filename);
		}
		void LoadData(std::string filename) {
			for (std::size_t i = 0; i < sequence.size(); i++) {
				map[sequence[i]].Insert(i);
			}
		}
		void Solve() {
			int T = 30000000; // end number
			sequence.reserve(T);
			for (size_t i = sequence.size()-1; i < T-1; i++) {
				auto it = map.find(sequence[i]);
				if (it->second.penult == -1) { // only spoken once
					sequence.push_back(0);
					map[0].Insert(i+1);
				}
				else{
					sequence.push_back(it->second.diff);
					map[it->second.diff].Insert(i+1);
				}
			}
			std::cout << T<<"th number spoken = "<<sequence.back()<<'\n';
		}
	private:
		std::unordered_map<int, Mem2> map;
		std::vector<int> sequence = { 11,18,0,20,1,7,16 };
	};
}
namespace Day16 {
	struct Entry {
		Entry(int p)
			:
			pos(p)
		{}
		int pos;
		std::map<std::string, int> count;
		std::set<std::string> candidateFields;
	};
	class Solution {
	public:
		Solution(std::string filename) {
			LoadData(filename);
			BuildDataStructs();
		}
		void LoadData(std::string filename) {
			int fileSeg = 0; // switch to different loading routinges for different parts of the input file
			std::ifstream in(filename);
			std::string str;
			while (std::getline(in, str)) {
				if (str == "your ticket:") {
					fileSeg = 1; continue;
				}
				if (str == "nearby tickets:") {
					fileSeg = 2; continue;
				}
				if (str == "") {
					continue;
				}
				switch (fileSeg) {
				case 0:
				{	
					size_t i = str.find(":");
					std::string field = str.substr(0, i);
					str = str.substr(i + 2);
					auto tokens = Utils::split(str, ' ');
					auto range1_vec = Utils::split(tokens[0], '-');
					auto range2_vec = Utils::split(tokens[2], '-');
					fieldRanges[field] = { std::stoi(range1_vec[0]),std::stoi(range1_vec[1]),std::stoi(range2_vec[0]),std::stoi(range2_vec[1]) };
					for (auto& v : fieldRanges[field]) {
						if (v > fieldRange_max_value) fieldRange_max_value = v;
					}
				}
					break;
				case 1:
				{
					const auto tokens = Utils::split(str,',');
					for (const auto& t : tokens) {
						myTicket.push_back(std::stoi(t));
					}
				}
					break;
				case 2:
				{
					const auto tokens = Utils::split(str, ',');
					std::vector<int> vec;
					for (const auto& t : tokens) {
						vec.push_back(std::stoi(t));
					}
					nearbyTickets.push_back(vec);
				}
					break;
				}
			}

		}
		void BuildDataStructs() {
			// Build the nearbyTicketsMatrix & valueToFieldsMap
			nearbyTicketsMatrix.resize(fieldRanges.size(),std::vector<bool>(fieldRange_max_value+1));
			size_t entry = 0;
			for (auto& mapEntry : fieldRanges) {
				for (size_t i = mapEntry.second[0]; i <= mapEntry.second[1]; i++) {
					nearbyTicketsMatrix[entry][i] = 1;
					valueToFieldsMap[i].push_back(mapEntry.first);
				}
				for (size_t i = mapEntry.second[2]; i <= mapEntry.second[3]; i++) {
					nearbyTicketsMatrix[entry][i] = 1;
					valueToFieldsMap[i].push_back(mapEntry.first);
				}
				entry++;
			}
		}
		void Solve() {
			// PART 1
			{
				int errorRate = 0;
				for (auto& ticket : nearbyTickets) {
					bool valid = true;
					for (int v : ticket) {
						if (valueToFieldsMap.find(v) == valueToFieldsMap.end()) {
							errorRate += v;
							valid = false;
						}
					}
					if (valid) {
						validNearbyTickets.push_back(ticket);
					}
				}
				std::cout << "Part 1.\nerrorRate = " << errorRate << '\n';
			}
			// PART 2
			{
				std::cout << "\nPart 2.\n";
				// Create vector of entry objects for each entry on a ticket, that contains all candidate information fields for that entry
				// (based on checking all valid tickets)
				auto allValidTickets = validNearbyTickets;
				allValidTickets.push_back(myTicket);
				for (int e = 0; e < fieldRanges.size(); e++) {
					Entry* entry = new Entry(e);
					for (std::vector<int>& ticketVec : allValidTickets) {
						std::vector<std::string> candidates = valueToFieldsMap[ticketVec[e]];
						for (std::string c : candidates) {
							entry->count[c]++;
						}
					}
					for (auto e : entry->count) {
						if (e.second == allValidTickets.size()) // this field appears on all tickets for this entry and is a valid candidate
						{
							entry->candidateFields.insert(e.first);
						}
					}
					entries.push_back(entry);
				}
				// Deduce fields of ticket entries by inference 
				std::vector<Entry*> decided;
				std::queue<Entry*> undecided;
				for (Entry* entry : entries) {
					if (entry->candidateFields.size() == 1) {
						decided.push_back(entry);
					}
					else {
						undecided.push(entry);
					}
				}
				while (!undecided.empty()) {
					Entry* entry = undecided.front(); undecided.pop();
					for (Entry* decidedEntry : decided) {
						entry->candidateFields.erase(*decidedEntry->candidateFields.begin());
						if (entry->candidateFields.size() == 1) break;
					}
					if (entry->candidateFields.size() == 1) {
						decided.push_back(entry);
					}
					else {
						undecided.push(entry);
					}
				}
				// Retrieve entry positions that contain "departure"
				std::map<std::string, int> myTicketDecoded;
				for (size_t i = 0; i < entries.size(); i++) {
					myTicketDecoded[*entries[i]->candidateFields.begin()] = myTicket[i];
					std::cout << "   >" << *entries[i]->candidateFields.begin() << ": " << myTicket[i] << '\n';
				}
				long long mult = 1;
				for (auto e : myTicketDecoded) {
					if (e.first.substr(0, 9) == "departure") {
						mult *= long long(e.second);
					}
				}
				std::cout << "\nDeparture related entries multiplied: " << mult;
			}
		}
	private:
		// Datastructs for holding input data
		std::map<std::string, std::vector<int>> fieldRanges;
		std::vector<int> myTicket;
		std::vector<std::vector<int>> nearbyTickets;
		std::vector<std::vector<int>> validNearbyTickets;
		int fieldRange_max_value = 0;
		// Datastructs for solving 
		std::vector<std::vector<bool>> nearbyTicketsMatrix;
		std::map<int, std::vector<std::string>> valueToFieldsMap;
		std::vector<Entry*> entries;
	};
}
namespace Day17_clean {
	std::string Hash(const std::vector<int>& vec) {
		std::string str = "(";
		for (int v : vec) {
			str += std::to_string(v) + ',';
		}
		str.pop_back(); str += ')';
		return str;
	}
	class Solution {
	public:
		Solution(std::string filename_)
			:
			filename(filename_)
		{}
		void Solve() {
			std::cout << "Part 1.\n";
			ProcessSteps(6, 3); 
			std::cout << "\nPart 2.\n";
			ProcessSteps(6, 4);
		}
	private:
		void ProcessSteps(const int STEPS=6, const int NDIMS=3) {
			LoadData(NDIMS);
			std::cout << "Starting field actives: " << actives.size() << ". Dimension of vector space: " << NDIMS << '\n';
			for (size_t step = 0; step < STEPS; step++) {
				std::unordered_set<std::string> visited;
				std::vector<std::string> retire;
				std::vector<std::string> activate;
				for (const auto& c: actives) {
					for (const auto& cc : coordCube[c]) {
						if (visited.find(cc) != visited.end()) {
							continue; // skip if already checked
						}
						int n = CountActiveNeighbors(cc);
						if (actives.find(cc) == actives.end()) { // inactive cell
							if (n == 3) activate.push_back(cc);
						}
						else { // active cell
							if (n != 2 && n != 3) retire.push_back(cc);
						}
						visited.insert(cc);
					}
				}
				for (const auto& c : activate) actives.insert(c);
				for (const auto& c : retire) actives.erase(c);
			std::cout << "Step " << step + 1 << " completed. Actives left: " << actives.size() << '\n';
			}
		}
		void LoadData(int NDIMS) {
			actives.clear(); coord.clear(); coordCube.clear(); startingField.clear();
			int x = 0;
			int y = 0;
			std::vector<int> remainingZeroVector = std::vector<int>(std::max(0,NDIMS - 2));
			std::ifstream in(filename);
			std::string str;
			while (getline(in, str)) {
				std::vector<bool> vec1;
				for (char ch : str) {
					if (ch == '.') vec1.push_back(false);
					else if (ch == '#') {
						// Fill base data vector
						vec1.push_back(true);
						// Fill coordinate containers
						std::vector<int> c = { x,y };
						c.insert(c.end(), remainingZeroVector.begin(), remainingZeroVector.end());
						std::string c_str = Hash(c);
						coord[c_str] = c;
						actives.insert(c_str);
						// Fill neighbor coordinates map
						coordCube[c_str] = GetNeighboringCoords(c);
					}
					x += 1;
				}
				startingField.push_back(vec1);
				y += 1;
				x = 0;
			}
		}
		int CountActiveNeighbors(const std::string& c_str) {
			int count = 0;
			if (coordCube.find(c_str) == coordCube.end()) {
				coordCube[c_str] = GetNeighboringCoords(coord[c_str]);
			}
			for (auto n_str : coordCube[c_str]) {
				if (n_str == c_str) continue; // exclude own position when counting active neighbors
				else {
					if (actives.find(n_str) != actives.end()) {
						count++;
					}
				}
			}
			return count;
		}
		void Recurse(size_t i, std::vector<int> c, std::vector<std::string>& vecHash) {//, const std::string& home) {
			if (i == c.size()) {
				std::string c_str = Hash(c);
				//if (c_str == home) return; 
				coord[c_str] = c;
				vecHash.push_back(c_str);
			}
			else
			{
				for (int k = -1; k <= 1; k++) {
					c[i] += k;
					Recurse(i + 1, c, vecHash);//, home);
					c[i] -= k;
				}
			}
			return;
		}
		std::vector<std::string> GetNeighboringCoords(std::vector<int> c) {
			std::vector<std::string> vecH;
			Recurse(0, c, vecH);
			return vecH;
		}
	private:
		std::string filename;
		std::unordered_set<std::string> actives;
		std::unordered_map<std::string,std::vector<int>> coord;
		std::unordered_map<std::string, std::vector<std::string>> coordCube; // coord with all its cubic neighbors (+1/0/-1 coord in all dimensions)
		std::vector<std::vector<bool>> startingField;
	};
}
namespace Day17a_visualized {
	constexpr const int STEPS = 6;
	class Solution {
	public:
		Solution(std::string filename) {
			LoadData(filename);
			BuildWorld();
		}
		void Print(int z=0) {
			for (int i = -x0; i <= x0; i++) {
				for (int j = -y0; j <= y0; j++) {
					if (cube[x0 + i][y0 + j][z0+z-1]) std::cout << '#';
					else std::cout << '.';
				}
				std::cout << "     ";
				for (int j = -y0; j <= y0; j++) {
					if (cube[x0 + i][y0 + j][z0 + z]) std::cout << '#';
					else std::cout << '.';
				}
				std::cout << "     ";
				for (int j = -y0; j <= y0; j++) {
					if (cube[x0 + i][y0 + j][z0 + z+1]) std::cout << '#';
					else std::cout << '.';
				}
				std::cout << '\n';
			}
			std::cout << '\n';
			std::cout << "x_min=" << xMin << ", x_max=" << xMax << '\n';
			std::cout << "y_min=" << yMin << ", y_max=" << yMax << '\n';
			std::cout << "z_min=" << zMin << ", z_max=" << zMax << '\n';
			std::cout << "nActive=" << nActive << '\n';

		}
		void LoadData(std::string filename) {
			std::ifstream in(filename);
			std::string str;
			while (getline(in, str)) {
				std::vector<bool> vec1;
				for (char c : str) {
					if (c == '.') vec1.push_back(false);
					else if (c == '#') vec1.push_back(true);
				}
				if (str.size() % 2 == 0) vec1.push_back(0);
				startingField.push_back(vec1);
			}
			if (str.size() % 2 == 0) startingField.push_back(std::vector<bool>(str.size() + 1));
			w0 = startingField[0].size();
			h0 = startingField.size();
			x0 = w0 / 2 + STEPS; W = 2 * x0 + 1;
			y0 = h0 / 2 + STEPS; H = 2 * y0 + 1;
			z0 = STEPS; D = 2 * z0 + 1;
			cube.resize(W, std::vector<std::vector<bool>>(H, std::vector<bool>(D)));
		}
		void BuildWorld() {
			for (int x = -w0/2; x <= w0/2; x++) {
				for (int y = -h0/2; y <= h0/2; y++) {
					if (startingField[w0 / 2 + x][h0 / 2 + y] == true)
					{
						cube[x0 + x][y0 + y][z0] = true;
						nActive++;
						if (x - 1 < xMin) xMin = x - 1;
						if (x + 1 > xMax) xMax = x + 1;
						if (y - 1 < yMin) yMin = y - 1;
						if (y + 1 > yMax) yMax = y + 1;
					}
				}
			}
			//for (int i = -STEPS; i < STEPS; i++)
			std::cout << "Starting layer at z=-1,0,1\n";
			Print(); 
			std::cin.get();
		}
		int countActiveNeighbors(int x_query, int y_query, int z_query) {
			int count = 0;
			for (int x = std::max(x_query-1, xMin); x <= std::min(x_query+1, xMax); x++) {
				for (int y = std::max(y_query - 1, yMin); y <= std::min(y_query + 1, yMax); y++) {
					for (int z = std::max(z_query - 1, zMin); z <= std::min(z_query + 1, zMax); z++) {
						if (x == x_query && y == y_query && z == z_query) continue;
						if (cube[x+x0][y+y0][z+z0] == true) {
							count++;
						}
					}
				}
			}
			return count;
		}
		int ProcessStep() {
			int nFlips = 0;
			std::vector<std::vector<std::vector<bool>>> cube_new = cube;
			for (int x = xMin; x <= xMax; x++) {
				for (int y = yMin; y <= yMax; y++) {
					for (int z = zMin; z <= zMax; z++) {
						int n = countActiveNeighbors(x, y, z);
						if ( (cube[x + x0][y + y0][z + z0]) && (n!=2 && n!=3) ) {
							cube_new[x + x0][y + y0][z + z0] = false;
							nFlips++;
							nActive--;
						}
						else if ( (!cube[x + x0][y + y0][z + z0]) && (n == 3) ) {
							cube_new[x + x0][y + y0][z + z0] = true;
							if (x - 1 < xMin) xMin = x-1;
							if (x + 1 > xMax) xMax = x+1;
							if (y - 1 < yMin) yMin = y-1;
							if (y + 1 > yMax) yMax = y+1;
							if (z - 1 < zMin) zMin = z-1;
							if (z + 1 > zMax) zMax = z+1;
							nFlips++;
							nActive++;
						}
					}
				}
			}
			cube = cube_new;
			return nFlips;
		}
		void Solve() {			
			for (int step = 0; step < STEPS-1; step++) {
				system("CLS");
				std::cout << "Step " << step + 1 << ", flips: " << ProcessStep() << '\n';
				Print(0);
				std::cin.get();
			}
			std::cout << '\n';
		}
	private:
		std::vector<std::vector<bool>> startingField;
		std::vector<std::vector<std::vector<bool>>> cube;
		int w0; // starting field width
		int h0; // starting field height
		int W; int x0; // max envelope: W = max field width, x0 = max abs(x-coordinate), also x-index of origin
		int H; int y0; // same for y
		int D; int z0; // same for z
		int xMin =-1; // current envelope
		int xMax = 1;
		int yMin =-1;
		int yMax = 1;
		int zMin =-1;
		int zMax = 1;
		int nActive = 0;
	};
}

namespace Day18 {
	class Solution {
		std::string filename;
	public:
		Solution(std::string filename) 
			:
			filename(filename)
		{
			LoadData();
		}
		void LoadData() {
			tokenVecContainer.clear();
			tokenStackContainer.clear();
			std::ifstream in(filename);
			std::string str;
			while (getline(in, str)) {
				std::vector<std::string> tvec = Utils::split(str, ' ');
				std::vector<std::string> tokens;
				std::stack<std::string> stack;
				for (size_t t = 0; t < tvec.size(); t++) {
					int begin = 0;
					int end = tvec[t].size();
					for (char ch : tvec[t]) {
						if (ch == '(') {
							tokens.push_back("(");
							begin++;
						}
						if (ch == ')') {
							end--;
						}
					}
					tokens.push_back(tvec[t].substr(begin, end-begin));
					for (int i = 0; i < tvec[t].size() - end; i++) {
						tokens.push_back(")");
					}
				}
				for (auto it = tokens.rbegin(); it != tokens.rend(); ++it) {
					stack.push(*it);
				}
				tokenVecContainer.push_back(tokens);
				tokenStackContainer.push_back(stack);
			}
			
		}
		enum class Operation {
			ADD,MULTIPLY
		};
		long long evaluate1(std::stack<std::string>& tokenStack) {
			long long accum = 0;
			Operation op = Operation::ADD;
			while (!tokenStack.empty()) {
				std::string token = tokenStack.top(); tokenStack.pop();
				if (token == "(") {
					if (op == Operation::ADD) accum += evaluate1(tokenStack);
					else accum *= evaluate1(tokenStack);
				}
				if (token == ")") return accum;
				if (token == "*") op = Operation::MULTIPLY;
				else if (token == "+") op = Operation::ADD;
				else if (isdigit(token[0])) {
					if (op == Operation::ADD) accum += std::stoi(token);
					else accum *= std::stoi(token);
				}
			}
			return accum;
		}
		long long evaluate2(std::stack<std::string>& tokenStack) {
			long long mult = 1;
			long long accum = 0;
			Operation op = Operation::ADD;
			while (!tokenStack.empty()) {
				std::string token = tokenStack.top(); tokenStack.pop();
				if (token == "(") {
					accum += evaluate2(tokenStack) * mult;
				}
				if (token == ")") return accum;
				if (token == "*") {//op = Operation::MULTIPLY;
					mult = accum;
					accum = 0;
				}
				//else if (token == "+") op = Operation::ADD;
				else if (isdigit(token[0])) {
					//if (op == Operation::ADD) accum += std::stoi(token);
					//else accum *= std::stoi(token);
					accum += mult * std::stoi(token);
				}
			}
			return accum;
		}
		long long Evaluate1() {
			long long Accum = 0;
			for (auto tokenStack : tokenStackContainer) {
				Accum += evaluate1(tokenStack);
			}
			return Accum;
		}
		long long Evaluate2() {
			long long Accum = 0;
			for (auto tokenStack : tokenStackContainer) {
				Accum += evaluate2(tokenStack);
			}
			return Accum;
		}
		void Solve() {
			long long ans1 = Evaluate1();
			LoadData();
			long long ans2 = Evaluate2();
			std::cout << '\n';
		}
	private:
		std::vector<std::vector<std::string>> tokenVecContainer;
		std::vector<std::stack<std::string>> tokenStackContainer;

	};
}

namespace DayYY {
	class Solution {
	public:
		Solution(std::string filename) {
			LoadData(filename);
		}
		void LoadData(std::string filename) {
			std::ifstream in(filename);
			std::string str;
			std::getline(in, str);

		}
		void Solve() {

			std::cout << '\n';
		}
	private:

	};
}

int main(){
	Day18::Solution("Input_files/Day18_input.txt").Solve();
	return 0;
}