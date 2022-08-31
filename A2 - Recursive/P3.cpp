#include <iostream>
#include <sstream>
#include <vector>
#include <limits>
#include <ios>
using namespace std;

void Print_table(vector<vector<int>>& ans_table)
{
	int n = ans_table[0].size();
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<n; j++)
		{
			cout << ans_table[i][j]<<' ';
		}
		cout << endl;
	}
}

bool Solve_help(const vector<string>& table, vector<vector<int>>& ans_table, string key_word,int& counter,int row_delta[],int col_delta[],int cur_row,int cur_col)
{
	int n = ans_table[0].size();//entered n (size)
	//at the begining ==> counter=0, counter shows number of letter maches
	if (counter == key_word.size())
	{
		return true;
	}
	for (int move = 0;move < 8;move++)
	{
		int new_row = cur_row + row_delta[move];
		int new_col = cur_col + col_delta[move];

		//out of table
		if (new_col < 0 || new_row < 0 || new_col>2 * (n-1) || new_row>n-1)
			continue;
		//token before or did not mach
		if (ans_table[new_row][new_col / 2] != 0 || table[cur_row][cur_col] != key_word[counter])
			continue;

		ans_table[cur_row][cur_col/2] = counter +1;
		counter++;
		if (Solve_help(table, ans_table, key_word, counter, row_delta, col_delta, new_row, new_col))
			return true;

		counter--;
		ans_table[cur_row][cur_col/2] = 0;
	}

	return false;//the word did not found
}

//this function search with all start points and uses Solve_help to find the asnwers
bool Solve(const vector<string>& table, vector<vector<int>>& ans_table, string key_word, int& counter, int row_delta[], int col_delta[], int cur_row, int cur_col)
{
	int n = ans_table[0].size();//entered n (size)
	//diffrent start points
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < n;j++)
		{
			if (Solve_help(table, ans_table, key_word, counter, row_delta, col_delta, i, 2 * j))
			{
				return true;//answer found
			}
		}
	}
	return false;//the word did not found with all start points
}

int main()
{
	string key_word;//to be searched
	cin >> key_word;
	vector<string> table;
	int n;//table Dimentions
	cin >> n;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');// discards the input buffer
	
	vector<vector<int>> ans_table;
	//put 0
	for (int i = 0; i<n; i++)
	{
		ans_table.push_back(vector<int>());
		for (int j = 0; j<n; j++)
		{
			ans_table[i].push_back(0);
		}
	}

	for (int i = 0;i < n;i++)
	{
		string temp;
		getline(cin, temp);
		table.push_back(temp);
	}
	//Print_table(table);

	//moves
	const int possible_moves = 8;
	int row_delta[possible_moves] = { -1,-1,0,1,1,1,0,-1 };
	int col_delta[possible_moves] = { 0,2,2,2,0,-2,-2,-2 };

	int key_word_size = key_word.size();
	int counter = 0; //counter shows number of letter maches in solve function
	if (Solve(table, ans_table, key_word, counter, row_delta, col_delta,0,0))
	{
		cout << "Yes"<<endl;
		Print_table(ans_table);
	}
	else
		cout << "No"<<endl;	
	return 0;
}
