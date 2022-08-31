#include <iostream>
#include <string>
using namespace std;

string encode(string &cmdstr, int from, int to)
{
	//At the begining ==> [ from=0   to=cmdstr.size()-1 ]
	int mid = (from + to) / 2;
	string result;
	result.push_back(cmdstr[mid]);

	if (to - from == 1) //when we got 2 chars left
		return cmdstr.substr(from, 2);
	if (mid <= from || mid >= to) //in case of one char left
		return result;

	result.append(encode(cmdstr, from, mid - 1));
	result.append(encode(cmdstr, mid + 1, to));
	return result;//return the encoded code
}
int main()
{
	string cmdstr;
	cin >> cmdstr;
	cout << encode(cmdstr, 0, cmdstr.size() - 1)<<endl;
	
	return 0;
}
