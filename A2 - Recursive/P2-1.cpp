#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct HeightInfo {
	int height;
	int tallest_height_in_front;
};

int find_tallest_heights_in_front(const vector<HeightInfo *>& height_infos, int start_index) {

	if (start_index == height_infos.size()-1)
		return 0;//all done (exit the function)

	int height=height_infos[start_index+1]->height;//an integer to find a tallest
	//find the tallest
	for (int i = start_index + 1;i < height_infos.size();i++)
		if (height < height_infos[i]->height)
			height = height_infos[i]->height;

	height_infos[start_index]->tallest_height_in_front = height;//add changes
	find_tallest_heights_in_front(height_infos, start_index + 1);//call this function again
}

void set_tallest_heights_in_front(const vector<HeightInfo *>& height_infos) {
	find_tallest_heights_in_front(height_infos, 0);
}

vector<HeightInfo* > get_height_infos() {

	vector<HeightInfo* > height_infos;
	
	//to get input in an integer vector
	vector<int> infos;
	int number;
	string line;
	getline(cin, line);
	istringstream stream(line);
	while (stream >> number)
		infos.push_back(number);

	for (int i = 0;i < infos.size(); i++)
	{
		HeightInfo* height_infos_temp = new (HeightInfo); //create new temp
		//add changes
		height_infos_temp->height = infos[i];
		height_infos_temp->tallest_height_in_front = -1;

		height_infos.push_back(height_infos_temp);//pushback
	}

	return height_infos;//return the result
}

void print_heights(const vector<HeightInfo *>& height_infos) {
	//printing except the last one
	for (int i = 0;i < height_infos.size()-1;i++)
		cout << height_infos[i]->tallest_height_in_front << ' ';
	//print the last one and after printing, go to new line
	cout << height_infos[height_infos.size()-1]->tallest_height_in_front<<endl;
}

int main() {
	vector<HeightInfo *> height_infos = get_height_infos();
	set_tallest_heights_in_front(height_infos);	
	print_heights(height_infos);
	return 0;
}
