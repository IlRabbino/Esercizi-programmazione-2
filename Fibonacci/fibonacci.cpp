//Fibonacci by Paolo Rabbito

#include <iostream>
#include <fstream>
using namespace std;

long long int fibonacci(int n){
    long long int tmp = 0;
    long long int pre = 0;
    long long int num = 1;
    for(int i=1; i<n; i++){
        tmp = num;
        num = num + pre;
        pre = tmp;
    }
    return num;
}

int main(){
    ofstream out("output.txt");
    ifstream in("input.txt");
    for(int i=0; i<100; i++){
        int n;
        in >> n;
        out << fibonacci(n) << endl;
    }
    return 0;
}