/*****************************************************************************************************************
* RA: 145103 	Nome Alan Ricardo Gomes
* Exercicio de programacao 3
* Descricao da solucao:
* Seja um vertice virtual 0 que possui arestas que se liga a todos com o peso igual ao custo de seus 
* reservatorios. A partir do algoritmo de Prim, encontra-se a MST referente ao grafo dado. Na "pratica", um 
* distrito somente vai se ligar a um outro se o preco do encanamento for menor que o preco do reservatorio. 
* Como todos os vertices alcancam zero, eh garantido que todos terao acesso a agua com o menor custo (por ser MST).
*
******************************************************************************************************************/

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#include <functional>
# define INF 0x3f3f3f3f
using namespace std;

//http://www.geeksforgeeks.org/prims-algorithm-using-priority_queue-stl/
//[0] Reference to the Pair structure 
typedef pair<int, int> iPair;

typedef struct District{
	int key;
	int PI;
	bool isInMST;
	vector< iPair > adj;
} District;

int solve(vector<District> &districts);

int main(){
	int n, m, cost;
	int temp_i, temp_j, temp_c;
	int i;

	District zero_dist;
	vector<District> districts;

	//read
	scanf("%d %d", &n, &m);
	districts.resize(n+1); //virtual vertex added to the graph
	districts[0].key = 0;
	districts[0].PI = -1;
	districts[0].isInMST = true;
	for ( i = 0; i < n; i ++) {
		scanf("%d\n", &temp_c); //reservoir
		districts[0].adj.push_back(make_pair(i+1, temp_c));
		districts[i+1].PI = 0;
		districts[i+1].key = INF;
		districts[i+1].isInMST = false;
	}
	for ( i = 0 ; i < m; i ++ ){
		scanf("%d %d %d\n", &temp_i, &temp_j, &temp_c);
		districts[temp_i].adj.push_back(make_pair(temp_j, temp_c));
		districts[temp_j].adj.push_back(make_pair(temp_i, temp_c));
	}
	//solve
	cost = solve(districts);
	printf("%d\n", cost);
}

int solve(vector<District> &districts){
	int cost = 0;
	int i;
	priority_queue< iPair, vector <iPair> , greater<iPair> > Q;
	District u, zero;
	int v, v_w, ix;
	Q.push(make_pair(0, 0));
	while(!Q.empty()){
		u = districts[Q.top().second];
		ix = Q.top().second; 
		districts[Q.top().second].isInMST = true;
		Q.pop();
		for ( i = 0; (unsigned)i < u.adj.size(); i ++){
			v = u.adj[i].first;
			v_w = u.adj[i].second;
			if( !(districts[v].isInMST) && (v_w < districts[v].key)){
				districts[v].PI = ix;//index of u
				districts[v].key = v_w;
				Q.push(make_pair(districts[v].key, v));
			}
		}
	}
	// Sum the costs of all districts
    for (int i = 0; (unsigned)i < districts.size(); ++i){
    	cost = cost +  districts[i].key;
    }
	return cost;
}
