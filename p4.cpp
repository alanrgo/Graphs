/******************************************************************************************************
Nome: Alan Ricardo Gomes 	RA: 145103
Dado os intervalos e seus respectivos valores, podemos reduzir o problema de agendamento de intervalos
em um problema de encontrar o maior caminho num grafo de compatibilidade de horarios. Seja G um grafo, 
um vertice representa um intervalo. (u,v) pertence a G se e somente se forem compativeis (ou seja, nao
conflitarem), e w(u,v) eh o valor negativo do intervalo. Alem disso, cria-se dois vertices virtuais, um 
source e um sink. O source se liga a todos com peso 0. E um vertice se conecta ao sink, se nao houver 
compatibilidade com qualquer intervalo j tal que j < v, sendo a ordem dos intervalos ordenadas de acordo 
com o tempo de inicio. O maior caminho eh obtido rodando o algoritmo de menor caminho numa DAG com 
os pesos negativos.
********************************************************************************************************/

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>

#include "minpathcpp.h"

#define INFINITO 1000000001

using namespace std;

struct Vertex {
	int index;
	int start;
	int end;
	int value;
};

struct less_than_key
{
    inline bool operator() (const Vertex& u, const Vertex& v)
    {
        return (u.start < v.start);
    }
};

bool thereIsIntersection(Vertex u, Vertex v){	
	// interval u in v
	if( u.start <= v.start && u.end > v.start ){ // case 1
		return true;
	}
	else if ( v.start <= u.start && v.end > u.start ){
		return true;
	}
	return false;
}

int main(){
	int n, temp_s, temp_f, temp_v;
	int i, j;
	bool compatible = false;

	
	vector< Vertex > V;
	vector<Grafo::Edge> P;
	scanf("%d",&n);
	Grafo G = Grafo(n+2);
	V.resize(n+2);

	//the source
	V[0].start = -1;
	V[0].end = -1;
	V[0].value = 0;
	V[0].index = 0;
	V[n+1].start = INFINITO;
	V[n+1].end = -1;
	V[n+1].value = 0;
	V[n+1].index = n+1;

	for ( i = 1; i <= n; i++ ){
		scanf("%d %d %d\n", &temp_s, &temp_f, &temp_v);
		V[i].start = temp_s;
		V[i].end = temp_f;
		V[i].value = temp_v;
		V[i].index = i;
	}

	//sort by starting times
	sort( V.begin(), V.end(), less_than_key());
	
	for ( i = 1; i <= n; i++ ){
		compatible = false;
		G.adicionaAresta(n+1, V[i].index, 0);
		for ( j = i-1; j > 0; j-- ){ //create compatible edges
			if(!thereIsIntersection(V[i], V[j])){
				G.adicionaAresta(V[i].index, V[j].index, -V[i].value);
				compatible = true;
			}
		}
		if(!compatible){
			G.adicionaAresta(V[i].index, 0, -V[i].value);
		}
	}

	int dist = 0;
	dist = G.min_path(n+1, 0, P);
	cout << -dist << endl;

	for (vector<Grafo::Edge>::iterator it = P.end()-2; it >= P.begin(); it--)
		cout << it->y << " ";
	cout << endl;

}