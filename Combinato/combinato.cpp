#include <iostream>
#include <fstream>
using namespace std;

class List{
private:
    int *key, *index;
    int count;
public:
    List(int n){
        key = new int[n];
        index = new int[n];
        count = 0;
    }

    void add(int x){
        key[count] = x;
        if(count==0)
            index[count] = -1;
        
        else{
            //set successivo
            int succ = 10001;
            int tmp;
            for(int i=0; i<count; i++){
                if(key[i]>x && key[i]<succ){
                    succ = key[i];
                    tmp = i;
                }
            }

            if(succ!=10001)
                index[count] = tmp;
            else{
                index[count] = -1;
            }
            //trova precedente
            int pre = 0;
            for(int i=0; i<count; i++){
                if(key[i]<=x && key[i]>=pre){
                    pre = key[i];
                    tmp = i;
                }
            }

            if(pre!=0)
                index[tmp] = count;
        }
        count++;
    }

    void stampa(ofstream &out){
        for(int i=0; i<count; i++){
            out << index[i] << " ";
        }
        out << endl;
    }
};


int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i=0; i<100; i++){
        int n;
            in >> n;
        List *l = new List(n);
        for(int j=0; j<n; j++){
            int x;
                in >> x;
            l->add(x);
        }
        l->stampa(out);
        delete l;
    }
    system("PAUSE");
    return 0;
}