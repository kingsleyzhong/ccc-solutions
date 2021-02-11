/*
Nothing special or fancy, just follow the instructions given
*/

#include <iostream>

using namespace std;

int main() {
	int i, a = 0, b = 0;
	while(true){
		cin >> i;
		if(i == 1){
			char c;
			int n;
			cin >> c >> n;
			if(c == 'A')
				a = n;
			else
				b = n;
		}
		else if(i == 2){
			char c;
			cin >> c;
			if(c == 'A')
				cout << a << endl;
			else
				cout << b << endl;
		}
		else if(i == 3){
			char x, y;
			cin >> x >> y;
			if(x == 'A' and y == 'A')
				a += a;
			else if(x == 'A' and y == 'B')
				a += b;
			else if(x == 'B' and y == 'A')
				b += a;
			else if(x == 'B' and y == 'B')
				b += b;
		}
		else if(i == 4){
			char x, y;
			cin >> x >> y;
			if(x == 'A' and y == 'A')
				a *= a;
			else if(x == 'A' and y == 'B')
				a *= b;
			else if(x == 'B' and y == 'A')
				b *= a;
			else if(x == 'B' and y == 'B')
				b *= b;
		}
		else if(i == 5){
			char x, y;
			cin >> x >> y;
			if(x == 'A' and y == 'A')
				a -= a;
			else if(x == 'A' and y == 'B')
				a -= b;
			else if(x == 'B' and y == 'A')
				b -= a;
			else if(x == 'B' and y == 'B')
				b -= b;
		}
		else if(i ==6){
			char x, y;
			cin >> x >> y;
			if(x == 'A' and y == 'A')
				a /= a;
			else if(x == 'A' and y == 'B')
				a /= b;
			else if(x == 'B' and y == 'A')
				b /= a;
			else if(x == 'B' and y == 'B')
				b /= b;
		}
		else
			break;
	}



	return 0;
}
