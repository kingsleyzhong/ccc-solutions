/*
Idea: Just figure out each case manually and hard code it in. Easier and more straight-forward than a simulation algorithm or a mathematical formula (both very overkill)
*/

#include <iostream>

using namespace std;

int main() {
	int n;
	cin >> n;

	if(n == 1 or n == 9)
		cout << 1;
	else if (n == 2 or n == 3 or n == 7 or n == 8)
		cout << 2;
	else if (n == 5 or n == 4 or n == 6)
		cout << 3;



	return 0;
}
