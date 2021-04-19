/* 
Corso di Programmazione II (A-L), Prof. Dario Catalano 
Esame del 17 dicembre 2014 (senza templates)  
*/
#include<iostream>

using namespace std;

class MultiStack	{
public: 
	virtual int* pop()=0;
	virtual void push(int x)=0;
	virtual void newPush(int x)=0; 
	virtual void print()=0;
};

class Nodo	{
private: 
	int valore; 
	Nodo* succ;
public: 
	Nodo(int x)	{
		valore=x; 
		succ=NULL;  }
	~Nodo() {}
	void Assegna(int x) {valore=x;}
	Nodo* Successivo()	{return succ;}
	void AssegnaSuccessivo(Nodo* p)	{succ=p;}
	int getValore()	{return valore;}
};

class Pila{
private: 
	Nodo *p;
	Pila* succ; 
public: 	
	Pila() {p=NULL;}
	void SvuotaPila() {p=NULL;}
	bool PilaVuota() {return !p;}
	int PrimoElemento() { if (p!=NULL) return p->getValore(); 
						else return 0;}
	void Push(int x); 
	int Pop();
	Nodo* getP() {return p;}
	Pila* getSucc() {return succ;}
	void setSucc(Pila* pp) {succ=pp;}
	void CancellaNodo(); 
	void StampaPila();   
	~Pila();
};

class MyMultiStack : public MultiStack {
private:
	Pila* testa; 
public:
	MyMultiStack() {testa=NULL;}
	int* pop();
	void push(int x);
	void Rearrange(Pila* t); 
	void newPush(int x);
	void print();
};

void Pila::StampaPila()	{
	Nodo* pnodo=p; 
	
	while(pnodo!=NULL) {
		cout << pnodo->getValore(); 
		if (pnodo->Successivo()!=NULL)	cout << ", "; 
		pnodo=pnodo->Successivo(); 
		}
}

void Pila::Push(int x)	{
	Nodo* aux=new Nodo(x); 
	
	if (p) aux->AssegnaSuccessivo(p); 
	p=aux; 
}

int Pila::Pop()	{
	int e; 
	
	e=PrimoElemento(); 
	CancellaNodo(); 
	return e; 
}

void Pila::CancellaNodo()	{
	Nodo* pnodo; 
	
	if (p) 	{
		pnodo=p; 
		p=p->Successivo(); 
		delete pnodo; 
	}
}

Pila::~Pila()	{
	Nodo* pnodo; 
	
	while(p!=0) 	{
		pnodo=p; 
		p=p->Successivo(); 
		delete pnodo; 
	}
}

int* MyMultiStack:: pop()	{
	Pila* temp=testa;
	
	int out=testa->Pop(); 
	if (testa->PilaVuota()) {
		testa=testa->getSucc(); 
		delete temp; }
	else {
		testa=testa->getSucc();
		Rearrange(temp); 		
		}
	return &out;
}

void MyMultiStack::Rearrange(Pila* temp)	{
	Pila* x=testa, *y=NULL; 
	
	if (temp!=NULL) {
		int valore=temp->PrimoElemento(); 
		while ((x!=NULL) && (valore < x->PrimoElemento()))	{
			y=x; 
			x=x->getSucc(); 
		}
		if (y!=NULL) 	{
			temp->setSucc(x); 
			y->setSucc(temp); 
		}
		else 	{
			temp->setSucc(testa); 
			testa=temp;
		}
	} 
}

void MyMultiStack::push(int x)	{
	testa->Push(x);
	Pila* temp=testa; 
	testa=testa->getSucc(); 
	Rearrange(temp); 
}

void MyMultiStack::newPush(int x)	{
	Pila* nuovo=new Pila; 
	
	nuovo->Push(x); 
	if (testa==NULL) {
		testa=nuovo; 
		testa->setSucc(NULL);
		}
	else Rearrange(nuovo); 
}

void MyMultiStack::print()	{
	Pila* x=testa; 
	
	while (x!=NULL) {
		cout << "["; 
		x->StampaPila(); 
		x=x->getSucc(); 
		if (x==NULL)
			cout << "] " << endl; 
		else cout << "], "; 
	}
}

int main()	{
	MyMultiStack p; 
	p.newPush(3);p.newPush(7);p.newPush(1);p.newPush(8);
	p.print(); 
	p.push(5);p.push(2);p.push(6);p.push(1);p.push(8);p.push(5);
	p.push(6);p.push(1);p.push(4);
	p.print(); 
	p.pop();p.pop();p.pop();p.pop();p.pop();
	p.print(); 
	return 0;
}


