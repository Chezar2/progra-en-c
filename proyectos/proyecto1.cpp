#include <iostream>
#include <stdlib.h>
using namespace std;

int suma(int a, int b){
 return a+b;
}
int main(){
    int x,y,c=0;
    cout<<" hello world"<<endl;
    cout<<"carge valores a sumar :";
    cin>>x; cin>>y; 
    c=suma(x,y);
    cout<<"suma: "<<c;
}
