#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
using namespace std;
int const vids=4; //modificar para tener más vidas
typedef struct nodo *pnodo;
typedef struct nodo{
                     string palabra;
                     pnodo siguiente;
                     pnodo anterior;
                     };
typedef struct tlista{
        pnodo ini;
        pnodo finale;
        int cont;};
void inicia_lista(tlista &lista);
void crear_nodo(tlista &lista);
bool buscar_nodo(tlista lista, string valor);
void agregar_final(tlista &lista,pnodo nuevo);
void mostrar(tlista lista);
bool buscar_nodo(tlista lista, int valor);
//jugadores
typedef struct nodoj *jnodo;
typedef struct nodoj{
                     string nombre;
                     string alias;
                     int puntacion;
                     int partidas;
                     jnodo sig;
                     };

typedef struct jlista{
					 jnodo i;
};

void inicia_lista(jlista &jugadores);
void crear_nodo(jnodo &nuevo);
void agregar_final(jlista &jugadores, jnodo nuevo);
void mostrar(jlista jugadores);
void buscar_jugador(jlista jugadores);
void cambiar_puntaje_perdedor(jlista &jugadores,string valor1,string valor2);
void cambiar_puntaje_ganador(jlista &jugadores,string valor1,string valor2);
//arbol
typedef struct anodo *arb;
typedef struct anodo{
                     char dato;
                     arb izq;
                     arb der;
                     };

void inicia_arbol(arb &r);
void crear_nodo(arb &r, char dato);
void insercion(arb &r,arb nuevo);
bool busqueda(arb r,char buscado);
void probar_letras(jlista &jugadores,tlista lista,arb r, string misteriosa, string valor1, string valor2, int &vidas,string &voladora, bool &seleccionada);

////////////////////---------MENU-----///////////////////////////////////
int menu(tlista &lista, jlista &jugadores, arb &r);
void opcion_1(tlista &lista);
void opcion_2( jlista &jugadores);
void opcion_3(jlista &jugadores);
void opcion_4(jlista &jugadores,tlista &lista, arb &r);

///////////////////////////////////////////////////////////////////////
int numero_aleatorio();
void seleccionar_palabra(tlista lista,arb &r, string &misteriosa);
///////////////////////////////////////////////////////////////////

bool validacion(tlista lista, jlista jugadores);
bool jugador_registrado(jlista jugadores, string valor1, string valor2);


//////////////////////INICIO DEL PROGRAMA///////////////////////
int main()
{   tlista lista; // diccionario
    jlista jugadores; // registro de jugadores
        arb r;        // arbol de verificación

    inicia_lista(jugadores);
    inicia_lista(lista);
    inicia_arbol(r);

    menu(lista,jugadores,r);

//liberación de estructuras dinámicas
    inicia_lista(jugadores);
    inicia_lista(lista);
    inicia_arbol(r);

  return 0;
}
//diccionario
void inicia_lista(tlista &lista)
{
   lista.finale=NULL;
     lista.ini=NULL;
     lista.cont=0;
}

bool verificar_minuscula(string palabra)
{
    int i,m=0;

    for(i=0;i<palabra.length();i++)
    {
        if(palabra[i]>='a' && palabra[i]<='z')
        {
            m++;
        }
    }
    if(m==palabra.length())
        return true;
    else
    return false;
}
bool verificar_tamanio(string palabra)
{
    if(palabra.length()<=25)
        return true;
    else
        return false;
}
void crear_nodo(tlista &lista)
{ string valor;
  pnodo nuevo;
   cin>>valor;
  int contador=0,i;
         if(verificar_minuscula(valor))
            {
                if (verificar_tamanio(valor)){
                  if(buscar_nodo(lista,valor))
                    {
               cout<<" Esta palabra ya esta en el diccionario"<<endl;
                    }
                else
                {
                    nuevo=new nodo;
                     if (nuevo!=NULL)
                    {
                nuevo->palabra=valor;
                nuevo->siguiente=NULL;
                nuevo->anterior=NULL;
                        agregar_final(lista,nuevo);
                 }
                   else
                    cout << "MEMORIA INSUFICIENTE" << endl;

                }}
                else
                cout<<" NO se permiten palabras con MAS de 25 CARACTERES"<<endl;
          }
          else
               cout<<" SOLO SE ACEPTAN PALABRAS EN MINUCULA"<<endl;
}
//
void agregar_final(tlista &lista,pnodo nuevo)
{ pnodo i;
      if (lista.cont==0)
        {
         lista.ini=nuevo;
        lista.finale=nuevo;
        }

      else
        {
         lista.finale->siguiente=nuevo;
        nuevo->anterior=lista.finale;
        lista.finale=nuevo;
        }
     lista.finale->siguiente=lista.ini;
     lista.ini->anterior=lista.finale;
     lista.cont++;
}
//
void mostrar(tlista lista)
{
    pnodo i;
    if(lista.cont==0)
    {cout<<" Diccionario vacio"<<endl; }
    else
    {    i=lista.ini;
        while(i->siguiente!=lista.ini)
        {
            cout<<" ."<<i->palabra<<" "<<endl;
            i=i->siguiente;
        }
        cout<<" ."<<i->palabra<<" "<<endl;
    }
}

bool buscar_nodo(tlista lista, string valor)
{ pnodo i;
  bool encontrado=false;
  if (lista.cont!=0)
  {

    i=lista.ini;
    while(i->siguiente!=lista.ini && encontrado==false)
    {
      if (i->palabra==valor)
        encontrado=true;
        i=i->siguiente;
    }
     if (i->palabra==valor)
        encontrado=true;
  }
  return encontrado;
}
//jugadores

void inicia_lista(jlista &jugadores)
{
    jugadores.i = NULL;
}

void crear_nodo(jnodo &nuevo)
{
  nuevo=new nodoj;
  if (nuevo!=NULL)
     { cout<<"    Ingrese su Nombre: ";
      cin>>nuevo->nombre;
       cout<<"    Ingrese su Alias: ";
       cin>>nuevo->alias;
       nuevo->puntacion=0;
       nuevo->partidas=0;
       nuevo->sig=NULL;
     }
  else
     cout << "MEMORIA INSUFICIENTE" << endl;
}

void agregar_final(jlista &jugadores,jnodo nuevo)
{ jnodo p;

	  if (jugadores.i == NULL)
         jugadores.i = nuevo;
      else
        {
          p=jugadores.i;
          while (p->sig!=NULL)
            {   p=p->sig; }

       p->sig=nuevo;
        }
}

void mostrar(jlista jugadores)
{ jnodo p;
  if (jugadores.i != NULL)
  {
        p=jugadores.i;
        while(p!=NULL)
        {
                      cout <<"------  Jugador: ---------" <<endl;
                      cout<<"| NOMBRE:    "<<p->nombre<<endl;
                      cout<<"| ALIAS:     "<<p->alias<<endl;
                      cout<<"| PUNTUACION: "<<p->puntacion<<endl;
                      cout<<"| PARTIDAS JUGADAS: "<<p->partidas<<endl;
                      cout<<"_ _ _ _ _ _ _ _ _ _ _ _ _ _"<<endl;
                      p=p->sig;
        }
  }
  else
    cout << "LISTA VACIA";
  cout << endl;
}
void buscar_jugador(jlista jugadores)
{
    jnodo p;
    int i,cont=0;
    bool encontrado=false;
    string valor1,valor2;


    if (jugadores.i!=NULL)
     {  p=jugadores.i;
    cout<<" Ingrese NOMBRE del jugador: ";
    cin>>valor2;
    cout<<" Ingrese ALIAS del jugador: ";
    cin>>valor1;

    while(p!=NULL && encontrado==false)
    {
     if(p->alias==valor1 && p->nombre==valor2)
     {
         encontrado=true;
        cout<<endl;
        cout<<" ___JUGADOR ENCONTRADO___ "<<endl<<endl;
        cout<<" NOMBRE: "<<p->nombre<<endl;
        cout<<" ALIAS: "<<p->alias<<endl;
        cout<<" PARTIDAS JUGADAS: "<<p->partidas<<endl;
        cout<<" PUNTUACION: "<<p->puntacion<<endl;
         }
           p=p->sig;

    }
    if(encontrado==false)
        cout<<"No se encuentra registrado el jugador"<<endl;
  }
  else
    cout<< "No hay jugadores registrados"<<endl;


}
//
void cambiar_puntaje_ganador(jlista &jugadores,string valor1,string valor2)
{
     jnodo p;
    int i,cont=0;
    bool encontrado=false;
    if (jugadores.i!=NULL)
     {  p=jugadores.i;

    while(p!=NULL && encontrado==false)
    {
     if(p->alias==valor1 && p->nombre==valor2)
    {
         encontrado=true;
        p->puntacion=p->puntacion+10;
        p->partidas++;
    }
           p=p->sig;
    }
  }
  else
    cout<< "No hay jugadores registrados"<<endl;
}
void cambiar_puntaje_perdedor(jlista &jugadores,string valor1,string valor2)
{
     jnodo p;
    int i,cont=0;
    bool encontrado=false;
    if (jugadores.i!=NULL)
     {  p=jugadores.i;

    while(p!=NULL && encontrado==false)
    {
     if(p->alias==valor1 && p->nombre==valor2)
    {
         encontrado=true;
        p->puntacion=p->puntacion-5;
         p->partidas++;
    }
           p=p->sig;
    }
  }
  else
    cout<< "No hay jugadores registrados"<<endl;
}
//
int numero_aleatorio()
{ srand(time(NULL));
   int x;
   x=1+rand()%(151-1);
   return x;
}

bool validacion(tlista lista, jlista jugadores)
{
  if(lista.cont==0 || jugadores.i==NULL)
    return true;

    return false;
}
bool jugador_registrado(jlista jugadores, string valor1, string valor2)
{
    jnodo p;
    int i;
    bool encontrado=false;

    if (jugadores.i!=NULL)
     {
        p=jugadores.i;
    while(p!=NULL && encontrado==false)
    {
     if(p->alias==valor1 && p->nombre==valor2)
      return true;
           p=p->sig;

    }
  }
  return encontrado;

}
/////////////////////----- ARBOL -----////////////////////

void inicia_arbol(arb &r)
{
    r=NULL;
}
void crear_nodo(arb &r, char dato)
{arb nuevo;
bool b;
    if( busqueda(r,dato)==false)
        {   nuevo=new anodo;
         if (nuevo!=NULL)
     { nuevo->dato=dato;
       nuevo->izq=NULL;
       nuevo->der=NULL;
       insercion(r,nuevo);
       }
       else
     cout << "MEMORIA INSUFICIENTE" << endl;



}}

bool busqueda(arb r,char buscado)
{
bool encontrado=false;
     if (r!=NULL)
     {
        if (r->dato == buscado)
           encontrado=true;
        else
            if (buscado < r->dato)
               encontrado=busqueda(r->izq,buscado);
            else
                encontrado=busqueda(r->der,buscado);
     }
return encontrado;
}
void insercion(arb &r,arb nuevo)
{
   if (r==NULL)
      r=nuevo;
   else
   {
      if (nuevo->dato < r->dato)
         insercion(r->izq, nuevo);
      else
         insercion(r->der, nuevo);
   }
}

//////////ZONA MENU//////
int menu(tlista &lista, jlista &jugadores, arb &r)
{
int opcion;
pnodo nuevo;
opcion= -1;
    do
    {
     cout<<" ************ PRINCIPAL  *********"<<endl;
     cout<<" 1- Anadir palabras al diccionario"<<endl;
     cout<<" 2- Registrar Jugador"<<endl;
     cout<<" 3- Consultar Jugador"<<endl;
     cout<<" 4- Jugar"<<endl;
     cout<<" 5- Salir"<<endl;
     cout<<"**********************************"<<endl;
     cout<<" Elija una opcion: ";
        cin>>opcion;
        cout<<"\n";
        switch (opcion)
        {    case 1: opcion_1(lista);              break;
             case 2: opcion_2(jugadores);          break;
             case 3: opcion_3(jugadores);          break;
             case 4: opcion_4(jugadores,lista,r);    break;
             case 5: cout<<" FIN DEL PROGRAMA"<<endl; break;
             default: cout<<"OPCION INCORRECTA, intente de nuevo";
        }
        cout<<endl;
        system("pause");
        system("cls");
    }while(opcion!=5);
}

void opcion_1(tlista &lista)
{ int opcion=-1;
    system("cls");
                   do{
                    cout<<"\n.............DICCIONARIO.................."<<endl;
                    cout<<"\n1: Cargar Palabra nueva";
                    cout<<"\n2: Mostrar Diccionario";
                    cout<<"\n3: Salir"<<endl;
                    cin>>opcion;
                    switch(opcion){
                       case 1: cout<<"\nIngrese la palabra que desee cargar al diccionario: ";
                                   crear_nodo(lista);
                                   break;
                      case 2: mostrar(lista); break;
                      case 3: cout<<" Saliendo del diccionario"<<endl; break;
                      default: cout<<"OPCION INCORRECTA, intente de nuevo";
                    }
                    system("pause");
                   system("cls");
                   }while(opcion!=3);
}

void opcion_2( jlista &jugadores)
{   system("cls");
    int opcion=-1;
    jnodo nuevo;
                 do{
        cout<<"\n........REGISTRAR JUGADOR........"<<endl;
        cout<<"\n1: Cargar Jugador";
        cout<<"\n2: Mostrar Jugadores";
        cout<<"\n3: Salir";
        cout<<"\nElija una opcion: ";
        cout<<"\n";
        cin>>opcion;
        cout<<"\n";
          switch (opcion)
            {
               case 1:
                       cout<<"   JUGADOR   "<<endl;
                       crear_nodo(nuevo);
                        agregar_final(jugadores,nuevo);

                       cout<<"\n";
                       break;

               case 2: mostrar(jugadores);
                       cout<<"\n";
                       break;
                case 3: cout<<" SALIENDO..."<<endl; break;
                default: cout<<"OPCION INCORRECTA, intente de nuevo";
           }
           system("pause");
           system("cls");
               }while(opcion!=3);
}

void opcion_3(jlista &jugadores)
{
     system("cls");
    buscar_jugador(jugadores);
}
//

void opcion_4(jlista &jugadores,tlista &lista,arb &r)
{
bool seleccionada=false;
 char respuesta;
    string valor,valor1,valor2,p,misteriosa,voladora;
    int opcion=-1,i,vidas;
     if(validacion(lista,jugadores)==false){

           system("cls");
             cout<<" Iniciar SESION"<<endl;
             cout<<" Ingrese NOMBRE del jugador:";
             cin>>valor2;
             cout<<" Ingrese ALIAS del jugador: ";
             cin>>valor1;
        if(jugador_registrado(jugadores,valor1,valor2)){

          do{ system("cls");
            if(seleccionada==false)
            vidas=-1000;
          cout<<"*****ADIVINA LA PALABRA*****"<<endl;
          cout<<" 1- Seleccionar Palabra"<<endl;
          cout<<" 2- Probar Letras"<<endl;
          cout<<" 3- Arriesgar Solucion"<<endl;
          cout<<" 4- Salir"<<endl;
          cout<<"****************************"<<endl;
          cout<<" Elija una opcion: ";
          cin>>opcion;
          switch(opcion)
          {
              case 1:
                  if (vidas>0)
              {system("cls");
                  cout<<"SEGURO DE SELECCIONAR OTRA PALABRA?"<<endl;
                  cout<<" PIERDE AUTOMATICAMENTE"<<endl;
                  cout<<"s/n"<<endl;

                  cin>>respuesta;
                  if(respuesta=='s')
                  {
                    cambiar_puntaje_perdedor(jugadores,valor1,valor2);
              cout<<endl<<" SELECCIONANDO PALABRA..."<<endl;
              seleccionada=true;
              vidas=-100000;
              inicia_arbol(r);
              seleccionar_palabra(lista,r,misteriosa);
                  }
                  cout<<" Continue"<<endl;
                  system("pause");
                  system("cls");

              }
              else{
                   cout<<endl<<" SELECCIONANDO PALABRA..."<<endl;
              seleccionada=true;
              vidas=-100000;
              inicia_arbol(r);
              seleccionar_palabra(lista,r,misteriosa);
              system("pause");}

              break;

              case 2: if(seleccionada)
              { system("cls");
              if(vidas<0){
              vidas=vids;}
                  probar_letras(jugadores,lista,r,misteriosa,valor1,valor2,vidas,voladora,seleccionada);

              }
                  else
                    cout<<" SELECCIONE una palabra"<<endl;
                    system("pause");
                    break;
            case 3:
                if(seleccionada && vidas>=0)
                  {
                    vidas=-10000;
         cout<<endl<<" Ingrese la palabra"<<endl;
       cin>>valor;
           if(misteriosa==valor){
             cambiar_puntaje_ganador(jugadores,valor1,valor2);
             cout<<"GANADOR"<<endl;}
           else{
             cambiar_puntaje_perdedor(jugadores,valor1,valor2);
             cout<<"HA PERDIDO"<<endl;
             cout<<" La palabra era: "<<misteriosa<<endl;
             }
             seleccionada=false;
                  }
                  else
                    cout<<" Seleccione una palabra"<<endl;
                  system("pause");
                    break;


            case 4:

            if(vidas>=0 && seleccionada==true)
            {
                    cout<<" SEGURO DESEA SALIR?"<<endl;
                    cout<<" PERDERIA LA PARTIDA!!"<<endl;
                    cout<<" s/n"<<endl;
                    cin>>respuesta;
                    if(respuesta=='s'){
                          cout<<" Saliendo ..."<<endl;
            cambiar_puntaje_perdedor(jugadores,valor1,valor2);
                    }else
                opcion=-1;
            }
            else
                cout<<" Saliendo..."<<endl;

             break;


             default: cout<<"OPCION INCORRECTA, intente de nuevo";

          }
              }while(opcion!=4);}
               else{
            cout<<" INICIO DE SESION FALLIDO"<<endl;
            cout<<" Asegurese de haberse REGISTRADO o de escribir correctamente su NOMBRE y ALIAS"<<endl;}}
            else
                cout<<" REVISE QUE EL DICICONARIO CONTENGA PALABRAS, Y QUE TENGA JUGADORES REGISTRADOS"<<endl;
}



void seleccionar_palabra(tlista lista,arb &r, string &misteriosa)
{ pnodo i;
 int x,c=0;
 x=numero_aleatorio();
    if(lista.cont==0)
    {
        cout<<" No hay palabras en el DICCIONARIO "<<endl;
    }
    else
    {
        i=lista.ini;
        while(c<x)
        {   c++;
            i=i->siguiente;
        }
        misteriosa=i->palabra;
        for(x=0;x <i->palabra.length();x++)
        {
            crear_nodo(r,i->palabra[x]);
        }
    }
}
//
void probar_letras(jlista &jugadores,tlista lista, arb r,string misteriosa, string valor1, string valor2, int &vidas,string &voladora,bool &seleccionada)
{
   bool ganador=false;
    char desconocido[misteriosa.length()], pal, resp='s';
    string valor;
    int i,cont=0,x,d;
     x=misteriosa.length();

     if(vidas!=4){
 for(i=0;i<misteriosa.length();i++)
      {
       desconocido[i]= voladora[i];
      }
     }

    while(vidas>0 && ganador==false && resp!='n'){system("cls");
     cout<<" INTENTOS RESTANTES: "<<vidas<<endl;
            d=0;

     for(i=0;i<misteriosa.length();i++)
      {
          if(desconocido[i]==misteriosa[i])
            cout<<" "<<misteriosa[i]<<" ";
          else
            cout<<" _ ";
      }
        cout<<endl;

    cout<<endl<<" Prueba una LETRA"<<endl;
    cin>>pal;

   if(busqueda(r,pal))
    {
      for(i=0;i<misteriosa.length();i++)
    {
        if(misteriosa[i]==pal)
          desconocido[i]=misteriosa[i];
    }
    cout<<" Letra CORRECTA"<<endl;
    system("pause");
    system("cls");
       cout<<" INTENTOS RESTANTES: "<<vidas<<endl;
     for(i=0;i<misteriosa.length();i++)
      {
          if(desconocido[i]==misteriosa[i])
            cout<<" "<<misteriosa[i]<<" ";
          else
            cout<<" _ ";
      }
        cout<<endl;

    }
   else{
    cout<<" Intente de nuevo"<<endl;
   }
   //

   for(i=0;i<misteriosa.length();i++)
   {
       if(desconocido[i]==misteriosa[i])
       d++;
   }
     if(d==x)
   {
       cout<<" GANADOR "<<endl;
        cambiar_puntaje_ganador(jugadores,valor1,valor2);
        seleccionada=false;
       ganador=true;
   }
   else
   {
       cout<<endl<<" Desea continuar probando LETRAS? s/n"<<endl;
       cin>>resp;

       }
   vidas--;
system("pause");
}

      if (vidas==0 && ganador==false)
       {      system("cls");
    for(i=0;i<misteriosa.length();i++)
      {
          if(desconocido[i]==misteriosa[i])
            cout<<" "<<misteriosa[i]<<" ";
          else
            cout<<" _ ";
      }
cout<<" DEBE ARRIESGAR, no le quedan intentos"<<endl;
}
if(resp=='n')
{system("cls");
     for(i=0;i<misteriosa.length();i++)
      {
          if(desconocido[i]==misteriosa[i])
            cout<<" "<<misteriosa[i]<<" ";
          else
            cout<<" _ ";
      }
}
 for(i=0;i<misteriosa.length();i++)
      {
        voladora[i]=desconocido[i];
      }
      cout<<endl;

}
