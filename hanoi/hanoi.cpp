#include <iostream>
#include <fstream>
using namespace std;

int hanoi(int disk, int start, int end, int free, int passi, int m, ofstream &out){
	
	if(disk == 1 ){
		if(passi==m)
		out <<  start << "  "  <<  end << endl;
		passi++;
	}
	else{
		passi = hanoi(disk-1, start, free, end, passi, m, out);
		if(passi==m)
			out <<  start << "  "  <<  end << endl;
		passi++;
		passi = hanoi(disk-1, free, end, start, passi, m, out);
	}
	return passi;
}

int main(){
    ofstream out("output.txt");
    ifstream in("input.txt");
	int passi = 1;
    for(int i=0; i<100; i++){
        int n;
            in >> n;
        int m;
            in >> m;
		cout << m << endl;
		
        hanoi(n, 1, 3, 2, passi, m, out);
		passi = 1;
    }

    return 0;
}

