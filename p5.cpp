/*******************************************************************************************
* Exercicio de programacao P5
* NOME: Alan Ricardo Gomes 					RA: 145103
* Para resolver este problema, podemos resolver o problema de de matching em Grafo bipartido 
* Neste caso, criamos uma coluna de vertices representando as linhas i, e uma coluna de vertices
* representando a coluna j. Havera uma aresta conectando os dois vertices se a(i,j) for igual a 1
* Adiciona-se tambem o vertice source (aqui sendo o vertice 0) e o vertice target (aqui sendo 2*n+1).
* Para resolver o problema de matching, foi utilizado o algoritmo de Edmonds-Karp. 
* Caso o valor do flow maximo seja igual a n, retorna SIM. Retorna-se NAO, caso contrario
*******************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>

#define INFINITY 1000000001
#define WHITE 0
#define GRAY 1

using namespace std;

int min(int a, int b){
	if ( a < b )
		return a;
	return b;
}

//[1] class retrieved from handout code of MC558 - UNICAMP (with modifications)
struct Graph {

	public:
	struct Edge{
		int x;
		int y;
		int c;
		int index;
		int reverse_index;
	};

	// creates empty graph
	Graph(){}

	// creates new graph with n vertices
	Graph(int n){
		for (int i = 0; i < n; i++){
			adj.push_back(vector<Edge>());
		}
	}

	// add vertex to the graph
	// returns the index
	int addVertex() {
		adj.push_back(vector<Edge>());
		return adj.size()-1;
	}

	int size(void) {
		return adj.size();
	}

	// adiciona uma aresta de x a y com peso w
	// 0 <= x,y <= n-1
	void addEdge(int x, int y, int c) {
		Edge e, e_back;
		e.x = x;
		e.y = y;
		e.c = c;

		e_back.x = y;
		e_back.y = x;

		if( c == INFINITY )
			e_back.c = INFINITY;
		else 
			e_back.c = 0;

		e.index = adj[x].size();
		e_back.reverse_index = adj[x].size();

		e_back.index = adj[y].size();
		e.reverse_index = adj[y].size();

		adj[x].push_back(e);
		adj[y].push_back(e_back);
		
	}

	bool bfs(int source, int t, int &max_flow){
		Edge **PI = (Edge **) malloc(adj.size()*sizeof(Edge*));
		vector<int> d;
		vector<int> color;
		queue<int> Q;

		d.resize(adj.size());
		color.resize(adj.size());

		for (unsigned int i = 0; i < adj.size(); i ++ ){
			PI[i] = NULL;
			d[i] = INFINITY;
			color[i] = WHITE;
		}
		d[source] = 0;
		color[0] = GRAY;
		Q.push(source);
		while (!Q.empty()){
			int u = Q.front();
			Q.pop();
			for (vector<Edge>::iterator it = adj[u].begin(); it != adj[u].end(); it++) {
				int v = it->y;
				// cout << "("<< u << ", "<< v << ")" <<endl;
				if(color[v] == WHITE && it->c != 0 ){
					Q.push(v);
					PI[v] = &*it;
					color[v] = GRAY;
					d[v] = d[u] + 1;
				}
			}
		}

		int min_flow = INFINITY;
	    for (Edge *e = PI[t]; e != NULL; e = PI[e->x]){
	    	int u, index;
	    	u = (*e).x;
	    	index = (*e).index;
	    	min_flow = min (min_flow, adj[u][index].c);
	    }
	    for (Edge *e = PI[t]; e != NULL; e = PI[e->x]){
	    	int u, v, index, rev_index;
	    	u = (*e).x;
	    	v = (*e).y;
	    	index = (*e).index;
	    	rev_index = (*e).reverse_index;

	    	if( adj[u][index].c != INFINITY )
	    		adj[u][index].c -= min_flow;
	    	if(adj[v][rev_index].c != INFINITY)
	    		adj[v][rev_index].c += min_flow;
	    	
	    }
	    if( min_flow != INFINITY)
	    	max_flow += min_flow;
	    free(PI);
	    return (color[t] == GRAY);
	}

	bool solve( int n){
		int source = 0;
		int target = 2*n + 1;
		int max_flow = 0;

		while(bfs(source, target, max_flow)){

		}
		// cout << max_flow <<endl;
		if ( max_flow == n )
			return true;
		return false;
	}

	private:
		vector<vector<Edge> > adj;
};

int main (){
	int n;
	bool answer = false;
	
	scanf("%d", &n);
	//source will have index 0 and target will have index 2*n+1
	Graph G = Graph(2*n+2);
	for ( unsigned int i = 1; i <= (unsigned) n; i ++ ){
		int number;
		G.addEdge(0, int (i), 1);
		for (unsigned int j = 1; j <= (unsigned) n; j ++ ){
			if( (unsigned) j!= (unsigned) n ){
				scanf("%d ", &number);
			}
			else{
				scanf("%d\n", &number);
			}
			if( number == 1 ){
				G.addEdge(i, j+n, 1);
			}
		}
	}
	for ( unsigned int i = 1 + n; i <= (unsigned) 2*n; i ++ ){
		G.addEdge(int (i), 2*n+1, 1);
	}
	answer = G.solve(n);
	if ( answer )
		cout << "SIM" <<endl;
	else 
		cout << "NAO"<<endl;
	return 0;
}