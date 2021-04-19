#include<iostream>
#include<fstream>
using namespace std;

/*void Merge(int* vett, int sx, int c, int dx){
    int i = sx;
    int j = c+1;
    int k = 0;
    int tmp[dx-sx+1];

    while(i <= c && j <= dx){
        if(vett[i] < vett[j]){
            tmp[k] = vett[i];
            i++;
        }
        else{
            tmp[k] = vett[j];
            j++;
        }
        k++;
    }

    while(i <= c){
        tmp[k] = vett[i];
        i++; k++;
    }

    while(j <= dx){
        tmp[k] = vett[j];
        j++; k++;
    }

    for(int i =  sx; i <= dx; i++)
        vett[i] = tmp[i - sx];
}*/

void Merge(int *vett, int sx, int c, int dx){
    int tmp[dx-sx+1];
    int k = 0;
    int i = sx;
    int j = c+1;

    while(i<=c && j<=dx){
        if(vett[i]<vett[j]){
            tmp[k] = vett[i];
            i++;
        }
        else{
            tmp[k] = vett[j];
            j++;
        }
        k++;
    }

    while(i<=c){
        tmp[k] = vett[i];
        k++;
        i++;
    }
    while(j<=dx){
        tmp[k] = vett[j];
        k++;
        j++;
    }

    for(int i=sx; i<dx; i++)
        vett[i] = tmp[i];
}

void mergeSort(int *vett, int sx, int dx, int &counter){
    if(sx<dx){
        int c = (dx+sx)/2;
        counter+=vett[sx];
        mergeSort(vett, sx, c, counter);
        mergeSort(vett, c+1, dx, counter);
        Merge(vett, sx, c, dx);
    }
}

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");
    int *vett;
    
    for(int i=0; i<100; i++){
        int n;
            in >> n;
        vett = new int[n];
        int counter = 0;
        for(int j=0; j<n;j++)
            in >> vett[j];
        mergeSort(vett, 0, n-1, counter);
        out << counter << endl;
    }
    return 0;
}