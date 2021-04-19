#include <iostream>
#include <fstream>
using namespace std;
#define STOP -1

class ArrayList {
private:
    int head, n, len;
    int *A, *N;
public:
    ArrayList(int len) {
        this->len = len;
        n = 0;
        head = STOP;
        A = new int[len];
        N = new int[len];
    }
    void add(int x) {
        A[n] = x;
        int t = head;
        int prev = -1;
        while(t!=STOP && A[t]<=x) {
            prev = t;
            t = N[t];
        }
        if(prev==-1) {
            N[n] = head;
            head = n;
        }
        else {
            N[n] = N[prev];
            N[prev] = n;
        }
        n++;
    }
    void canc(int x) {
        int t = head;
        int prev = -1;
        while(t!=STOP && A[t]<x) {
            prev = t;
            t = N[t];
        }
        if(t==STOP || A[t]>x) return;
        if(prev==-1) {
            head = N[t];
        }
        else {
            N[prev] = N[t];
        }
        A[t] = A[n-1];
        N[t] = N[n-1];
        for(int i=0; i<n; i++) if(N[i]==n-1) N[i]=t;
        n--;
    }
    void print(ofstream &out) {
        for(int i=0; i<n; i++) out << N[i] << " ";
        out << endl;
    }
};

int main(){
    ofstream out("output.txt");
    ifstream in("input.txt");
    for(int i=0; i<100; i++){
        int n;
            in >> n;
        ArrayList *a = new ArrayList(n);
        for(int j=0; j<n; j++){
            int x;
                in >> x;
            a->add(x);
        }
        a->print(out);
    }
    return 0;
}