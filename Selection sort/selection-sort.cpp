#include <iostream>
#include <fstream>
using namespace std;

int selection(int *array, int n){
    int sum = 0;
    int min;
    for(int i=0; i<n; i++){
        min = i;
        for(int j=i+1; j<n; j++){
            if(array[j]<array[min])
                min = j;
        }
        sum += min-i;
        swap(array[i], array[min]);
    }
    return sum;
}

int main(){
    ofstream out("output.txt");
    ifstream in("input.txt");
    for(int i=0; i<100; i++){
        int n;
            in >> n;
        int *array = new int[n];
        for(int j=0; j<n; j++){
            in >> array[j]; 
        }

        out << selection(array, n) << endl;
    }
    return 0;
}