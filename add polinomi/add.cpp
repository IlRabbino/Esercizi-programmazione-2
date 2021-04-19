#include <iostream>
#include <fstream>
using namespace std;

class Monomio{
private:
    Monomio *next, *prev;
    int val, esp;
public: 
    Monomio(){
        next = prev = NULL;
    }
};

class Polinomio{
private:
    Monomio *monomio;
public:
    Polinomio(){monomio = NULL;}
    
    
};

int main(){
    ofstream out("output.txt");
    ifstream in("input.txt");

    for(int i=0; i<100; i++){
        
    }

    return 0;
}

