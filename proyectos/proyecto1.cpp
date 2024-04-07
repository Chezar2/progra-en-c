#include <iostream>
#include <stdlib.h>
using namespace std;
int main(){
int n,m,a,contador=0;
bool listo=false;
cout<<" inicio:"<<endl;
cin>>n;cin>>m;cin>>a;

int area=n*m;
int cuadrados=a*a;

while(listo==false){
if(n>=a && m>=a){
    cout<<" se puede poner 1 cuadrado"<<endl;
    contador++;
    n=n-a; m=m-a;
}else{
    listo=true;
    cout<<"ya no entran mas cuadrados"<<endl;
}

}//fin de while
cout<<" en total entran "<<contador<<" cuadrados"<<endl;
//ahora agrego los cuadrados extra para los bordes



return contador;

}
