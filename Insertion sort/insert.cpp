#include<iostream>
#include<fstream>
using namespace std;

int insertion(int *vett, int n){
    int contatore = 0;
    int j;
    for(int i=1; i<n; i++){
        for(int j=i; j>0; j--){
            if(vett[j]<vett[j-1]){
                swap(vett[j], vett[j-1]);
                contatore++;
            }
        }
    }
    return contatore;
}

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");
    int *vett;
    for(int i=0; i<100; i++){
        int n;
            in >> n;
        vett = new int[n];
        for(int j=0; j<n; j++)
            in >> vett[j];
        out << insertion(vett, n) << endl;
    }
    return 0;
}