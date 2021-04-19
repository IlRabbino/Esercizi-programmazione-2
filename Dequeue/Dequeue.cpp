#include <iostream>
#include <fstream>

using namespace std;

template<class H>
class Nodo{
private:
    H key;
    Nodo<H> *next;
public:
    Nodo(){}
    Nodo(H key){
        this->key = key;
        next = NULL;
    }

    void setNext(Nodo<H> *next){this->next = next;}

    H getKey(){return key;}
    Nodo<H> *getNext(){return next;}
};

template<class H>
class Coda{
private:
    Nodo<H> *head;
public:
    Coda(){
        head = NULL;
    }

    void enqueue(H key){
        Nodo<H> *nuovo = new Nodo<H>(key);

        if(!head){
            head = nuovo;
        }

        else{
            Nodo<H> *tmp = head;
            while(tmp->getNext()){
                tmp = tmp->getNext();
            }
            tmp->setNext(nuovo);
        }
    }

    void dequeue(){
        if(head){
            Nodo<H> *tmp = head;
            head = head->getNext();
            delete tmp;
        }

        else{
            cout << "stack underflow!" << endl;
            exit(-1);
        }
    }

    void print(ofstream &out){
        Nodo<H> *tmp = head;
        
        while(tmp){
            out << tmp->getKey() << " ";
            cout << tmp->getKey() << " ";
            tmp = tmp->getNext();
        }

        out << endl;
        cout << endl;
    }
};

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int j=0; j<100; j++){
        string tipo;
            in >> tipo;
            cout << tipo << endl;

        int n;
            in >> n;
        
        if(tipo=="int"){
            Coda<int> *coda = new Coda<int>();
            
            for(int i=0; i<n; i++){
                string obj;
                    in >> obj;
                
                if(obj=="dequeue")
                    coda->dequeue();
                
                else{
                    obj= obj.substr(1, (obj.length()-1));
                    int x = stoi(obj);
                    coda->enqueue(x);
                }
            }

            coda->print(out);
            delete coda;
        }

        if(tipo=="double"){
            Coda<double> *coda = new Coda<double>();
            
            for(int i=0; i<n; i++){
                string obj;
                    in >> obj;
                
                if(obj=="dequeue")
                    coda->dequeue();
                
                else{
                    obj= obj.substr(1, (obj.length()-1));
                    double x = stod(obj);
                    coda->enqueue(x);
                }
            }

            coda->print(out);
            delete coda;
        }

        if(tipo=="char"){
            Coda<char> *coda = new Coda<char>();
            
            for(int i=0; i<n; i++){
                string obj;
                    in >> obj;
                
                if(obj=="dequeue")
                    coda->dequeue();
                
                else{
                    char x = obj[1];
                    coda->enqueue(x);
                }
            }

            coda->print(out);
            delete coda;
        }

        if(tipo=="bool"){
            Coda<bool> *coda = new Coda<bool>();
            
            for(int i=0; i<n; i++){
                string obj;
                    in >> obj;
                
                if(obj=="dequeue")
                    coda->dequeue();
                
                else{
                    obj= obj.substr(1, (obj.length()-1));
                    int x = stoi(obj);
                    coda->enqueue(x);
                }
            }

            coda->print(out);
            delete coda;
        }
    }

    return 0;
}
