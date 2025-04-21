#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct resultadoStruct{
    int pIzq, pDer; // peso de los equipos
    int nIzq, nDer; // numero de participantes por equipo
};

typedef resultadoStruct * resultado;

void generar(int nivel, vector<int>& s){
    s[nivel-1]++;
}

void asignar(resultado s, int nivel, const vector<int>& pesos, int equipo) {
    if (equipo == 0) {
        s->nIzq++;
        s->pIzq += pesos[nivel - 1];
    } else {
        s->nDer++;
        s->pDer += pesos[nivel - 1];
    }
}

bool solucion(int nivel, int n, resultado s){
    return (nivel == n + 1) && abs(s->nDer - s->nIzq) <= 1;
}

bool criterio(int nivel, int n){
    return nivel < n;
}

bool masHermanos(int nivel, vector<int>& s) {
    return s[nivel - 1] <1;
}

void retroceder(resultado s, int nivel, const vector<int>& pesos, int equipo) {
    if (equipo == 0) {
        s->nIzq--;
        s->pIzq -= pesos[nivel - 1];
    } else {
        s->nDer--;
        s->pDer -= pesos[nivel - 1];
    }
}

resultado backtracking(vector<int> pesos){
    int n = pesos.size();
    int nivel = 1;
    vector<int> s(n,-1);
    int voa = __INT_MAX__;
    resultado soa = new resultadoStruct;
    resultado estado = new resultadoStruct{0, 0, 0, 0};

    while (nivel!=0){

        // generar un hermano
        generar(nivel, s);

        
        if (s[nivel - 1] <= 1) {asignar(estado, nivel, pesos, s[nivel - 1]);}
            

        // si he encontrado una mejor solucion actualizo el voa y soa
        if(solucion(nivel,n,estado) && abs(estado->pIzq - estado->pDer)<voa){
            voa=abs(estado->pIzq - estado->pDer);
            if(soa!=nullptr){
                delete soa;
            }
            soa = new resultadoStruct(*estado);
        }

        // si puedo llegar a una solicion final sigo
        if(criterio(nivel,n)){
            nivel++;
        }else {
            while ((nivel > 0) && !masHermanos(nivel,s)){
                retroceder(estado,nivel,pesos,s[nivel-1]);
                s[nivel - 1] = -1;
                nivel--;
            }
        }
    }
    printf("%d %d %d %d\n",soa->nDer, soa->nIzq, soa->pDer,soa->pIzq);
    delete estado;

    return soa;

}



int main(){
    int C;          // numero de casos
    cin >> C;
    string linea;   // linea para leer blancos;

    getline(cin,linea); // lectura de la primera linea en blanco

    for(int i=0;i<C;i++){
        if (i>0){
            getline(cin,linea); // lecutra de la linea en blanco entre casos
        }
        int n;
        cin >> n;           // numero de participantes
        vector<int> pesos;  // vector con los pesos de los participantes
        for(int j=0;j<n;j++){
            int p;
            cin >> p;
            pesos.push_back(p);
        }

        resultado r = backtracking(pesos);

        int a = r->pIzq;
        int b = r->pDer;
        if (a > b) swap(a, b);
        cout << a << " " << b << endl;

        delete r;
    }



    return 0;
}