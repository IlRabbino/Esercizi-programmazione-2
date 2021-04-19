//pop-stack by Paolo Rabbito

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

template<class H>
class Nodo{
private:
    Nodo<H> *prev;
    Nodo<H> *next;
    H key; 
public:
    Nodo(){}
    Nodo(H key){
        this->key = key;
    }
    
    void setNext(Nodo<H> *next){this->next=next;}
    void setPrev(Nodo<H> *prev){this->prev=prev;}

    Nodo<H> *getNext(){return next;}
    Nodo<H> *getPrev(){return prev;}
    H getKey(){return key;}
};

template<class H>
class Pila{
private:
    Nodo<H> *head;
    Nodo<H> *tail;
public:
    Pila(){
        head = new Nodo<H>();
        tail = new Nodo<H>();
        head->setNext(tail);
        tail->setPrev(head);
    }

    void push(H key){
        Nodo<H> *nuovo = new Nodo<H>(key);

        if(head->getNext()!=tail){
            Nodo<H> *tmp = head->getNext();
            while(tmp->getNext()!=tail){
                tmp = tmp->getNext();
            }
            tmp->setNext(nuovo);
            nuovo->setPrev(tmp);
            tail->setPrev(nuovo);
            nuovo->setNext(tail);
        }

        else{
            head->setNext(nuovo);
            nuovo->setPrev(head);
            tail->setPrev(nuovo);
            nuovo->setNext(tail);
        }
    }

    void pop(){
        Nodo<H> *tmp = tail->getPrev();
        tmp->getPrev()->setNext(tail);
        tail->setPrev(tmp->getPrev());
        delete tmp;
    }

    void print(ofstream &out){
        Nodo<H> *tmp = tail->getPrev();
        while(tmp!=head){
            out << tmp->getKey() << " ";
            tmp = tmp->getPrev();
        }
        out << endl;
    }
};

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    
    for(int i=0; i<100; i++){
        string tipo;
        in >> tipo;

        int n;
        in >> n;

        if(tipo=="int"){
            Pila<int> *pila = new Pila<int>();

            string obj;
                
            for(int j=0; j<n; j++){
                in >> obj;
                if(obj!="pop"){
                    int len = obj.length()-1;
                    int x = stoi(obj.substr(1, len));
                    pila->push(x);
                }

                else{
                    pila->pop();
                }
            } 

            pila->print(out);
            delete pila;   
        }
        if(tipo=="double"){
            Pila<double> *pila = new Pila<double>();

            string obj;
                
            for(int j=0; j<n; j++){
                in >> obj;
                if(obj!="pop"){
                    int len = obj.length()-1;
                    double x = stod(obj.substr(1, len));
                    pila->push(x);
                }

                else{
                    pila->pop();
                }
            } 

            pila->print(out);
            delete pila;   
        }
        if(tipo=="char"){
            Pila<char> *pila = new Pila<char>();

            string obj;
            
            for(int j=0; j<n; j++){
                in >> obj;
                if(obj!="pop"){
                    char x = obj[1];
                    pila->push(x);
                }

                else{
                    pila->pop();
                }
            } 

            pila->print(out);
            delete pila;   
        }
        if(tipo=="bool"){
            Pila<bool> *pila = new Pila<bool>();

            string obj;

            for(int j=0; j<n; j++){
                in >> obj;
                if(obj!="pop"){
                    int len = obj.length()-1;
                    bool x = stoi(obj.substr(1, len));
                    pila->push(x);
                }

                else{
                    pila->pop();
                }
            } 

            pila->print(out);
            delete pila;   
        }
    }

    return 0;
}