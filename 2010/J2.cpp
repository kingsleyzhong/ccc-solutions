/*
Simulation Algorithm
*/

#include <iostream>

using namespace std;

int main() {

	int a, b, c, d, ni = 0, br = 0, s; //a,b,c,d and s are all the same variables as in problem statement. ni and br and the positions of nikky and bryon respectively
	cin >> a >> b >> c >> d >> s;

    // NIKKY = a fwd / b back
    // Bryon = c fwd /  d back

    for(int cr = 0;cr < s; cr++){ // cr is current step
		// Checking if nikky is going forward or backwards
		if(cr % (a + b) < a){
			ni++;
		}
		else{
			ni--;
		}
		if(cr % (c + d) < c){
			br++;
		}
		else{
			br--;
		}
    }

    if(ni > br)
    	cout << "Nikky";
    else if (br > ni)
    	cout << "Bryon";
    else
    	cout << "Tied";




	return 0;
}
