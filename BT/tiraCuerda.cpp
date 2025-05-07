#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
using namespace std;



void generar(int nvl, int sol[], int pesos[], int& equipo1, int& equipo2, int& count1, int& count2){
    if(sol[nvl]!= 1){
        sol[nvl]++;               //nivel no es 1, aumentamos el valor
        if(sol[nvl]==0){          //si es 0, genera en equipo1
            equipo1+=pesos[nvl];
            count1++;
        }
        else{                       //si es 1, genera en equipo2, resta en equipo1
            equipo2+=pesos[nvl];
            count2++;
            equipo1-=pesos[nvl];
            count1--;
        }
    }
}
int solucion(int nvl, int participantes, int count1, int count2){   //criterio para solucion, n nodos visitados, equipos parejos
    return (nvl == participantes -1) && (abs(count1-count2)<=1);
}

bool criterio(int nvl, int nparticipantes, int count1, int count2){  //criterio para avanzar, cualquier nodo no solución se estudia si se cumple la restriccion
    if ((nvl >= nparticipantes-1) || (count1>nparticipantes/2+1) || (count2>nparticipantes/2+1)){
        return false;
    }
    else{
        return true;
    }
}


bool mas_hermanos(int nvl, int sol[]){         //si no se ha avanzado a nivel = 1, hay más hermanos de ese nodo
    return sol[nvl] < 1;
}

void retroceder(int& nvl, int sol[], int pesos[], int& equipo1, int& equipo2, int& count1, int& count2){
    if(sol[nvl]==1){
        equipo2 -= pesos[nvl];                //retrocede y elimina los cambios en ese nivel, retrocede de 1 en 1
        count2--;                             //si nivel = 1, eliminamos cambios del equipo2, restamos peso y decrementamos
    }
    else{
        equipo1 -= pesos[nvl];                //si es 0, restamos peso y decrementamos del equipo1
        count1--;
    }
    sol[nvl] = -1;                            //establecemos el nivel a no explorado y retrocedemos el nivel en 1
    nvl--;
}

void backtracking(int pesos[], int nparticipantes){
    int nvl = 0;                    //nivel inicial
    int sol[nparticipantes];        //vector solucion
    int equipo1 = 0;
    int count1 = 0;
    int equipo2 = 0;
    int count2 = 0;
    int equipo1_fin = 0;
    int equipo2_fin = 0;
    for (int i = 0; i<nparticipantes; i++){
        sol[i] = -1;                //valor no escogido, inicialización del vector de eleccion de miembros
    }
    int voa = 450*31;               //valor optimo actual (peso máximo de 450 por 31 miembros imposibles de asignar según restricciones del problema (infinito))
    while(nvl!=-1 && sol[0]!=1){    //si quitamos sol[0]=1 trabajamos sin poda extra, no eliminamos la mitad del vector solución
        generar(nvl, sol, pesos, equipo1, equipo2, count1, count2);                         //generamos el nivel
        if (solucion(nvl,nparticipantes,count1, count2) && (abs(equipo1-equipo2)<voa)){     //si es solución y es mejor que voa anterior, se sobreescribe
            voa = abs(equipo1-equipo2);
            equipo1_fin = equipo1;               //guardamos en equipo1_fin y equipo2_fin los valores por si no volvemos a encontrar otra solućión mejor
            equipo2_fin = equipo2;
        }
        else if (criterio(nvl,nparticipantes,count1,count2)){            //si se cumple el criterio sseguimos avanzando
            nvl++;
        }
        else while(!mas_hermanos(nvl,sol) && nvl > -1){          //si no tiene más hermanos, retrocedemos y eliminamos lo calculado
            retroceder(nvl,sol,pesos,equipo1,equipo2,count1,count2);
        }
    }

    if(equipo2_fin < equipo1_fin){
        cout << equipo2_fin << " " << equipo1_fin << endl;
    }
    else{
        cout << equipo1_fin << " " << equipo2_fin << endl;
    }

}



int main(){
    int casos, nparticipantes;
    cin >> casos;                              //leo casos de realización de backtracking
    for (int i = 0; i < casos; i++){           //bucle en función de casos
        cin >> nparticipantes;                   //leo participantes (mñaximo 30)
        int pesos[nparticipantes];               //creo array en pila (es posible debido al bajo tamaño (máximo 30)
        for (int j= 0; j<nparticipantes; j++){
            cin >> pesos[j];                      //inserto datos de entrada (pesos) en array creado
        }
        backtracking(pesos,nparticipantes);         //inicio de backtracking
    }
}
