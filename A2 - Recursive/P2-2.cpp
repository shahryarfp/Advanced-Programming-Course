#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

vector<int> get_tallest_heights_in_front(const vector<int>& heights, int start_index) {
	
	vector<int> tallest_heights_in_front;
	if (start_index == heights.size() - 1)
	{
		tallest_heights_in_front.push_back(-1);
		return tallest_heights_in_front;//all done
	}

	int h = heights[start_index + 1];//an integer to find a tallest
	//find the tallest
	for (int i = start_index + 1;i < heights.size();i++)
		if (h < heights[i])
			h = heights[i];
	
	tallest_heights_in_front.push_back(h);//add changes
	vector<int> temp= get_tallest_heights_in_front(heights, start_index + 1);
	tallest_heights_in_front.insert(tallest_heights_in_front.end(), temp.begin(), temp.end());//concat vectors
	return tallest_heights_in_front;//return result
}

vector<int> get_tallest_heights_in_front(const vector<int>& heights) {
	return get_tallest_heights_in_front(heights, 0);
}

vector<int> get_heights() {

	//to get input in an integer vector
	vector<int> infos;
	int number;
	string line;
	getline(cin, line);
	istringstream stream(line);
	while (stream >> number)
		infos.push_back(number);//pushback

	return infos;//return the result
}

void print_heights(const vector<int>& heights) {
	//printing
	for (int i = 0;i < heights.size();i++)
		cout << heights[i] << ' ';

	cout << endl;//after printing, go to new line
}

int main() {
	vector<int> heights = get_heights();
	vector<int> tallest_heights_in_front = get_tallest_heights_in_front(heights);
	print_heights(tallest_heights_in_front);
	return 0;
}