#include<bits/stdc++.h>

//#include "disjoint_set_rank.cpp"
using namespace std;

int find(vector<char> s,char a){
	for(int i=0;i<s.size();i++){
		if(s[i]==a)
			return i;
	}
	return -1;
}
class edge{
	public:
	char s;
	char d;
	int w;
	edge(char a,char b,int x){
		s=a;
		d=b;
		w=x;
	}
	void showe( ){
		cout<<s<<d<<"-"<<w<<endl;
	}
};

class graph{
	int **G;
	public:
	vector<char> vset;
	int v;
	vector<edge> eset;
	
	graph(int n){
		G=(int**)malloc(sizeof(int*)*n);
		//eset=(edge*)malloc(sizeof(edge)*n);
		v=n;
	}
	void insert_vset(vector<char> k,int n){
		for(int i=0;i<n;i++)
			vset.push_back(k[i]);
	}
	void show(){
		int n=vset.size();
		for(int i=0;i<vset.size();i++)
			cout<<" "<<vset[i];
		cout<<endl;
		for(int i=0;i<n;i++){
			cout<<vset[i];
			for(int j=0;j<n;j++)
				cout<<" "<<G[i][j];
			cout<<endl;
		}
	}
	void show_edge_set(){
		for(int i=0;i<eset.size();i++){
			cout<<eset[i].s<<eset[i].d<<"-"<<eset[i].w<<endl;
		}
	}

	void in(int **a){
		int k=0;
		G=a;
		for(int i=0;i<v;i++){
			for(int j=0;j<v;j++){
				if(a[i][j]!=0){
					edge e=edge(vset[i],vset[j],a[i][j]);
					eset.push_back(e);
				}
			}
		}
	}	
	void show_vertex(){
		for(int i=0;i<vset.size();i++)
			cout<<vset[i]<<" ";
		cout<<endl;
	}
	void Bellman_Ford(char a){
		int dist[v],p[v];
		for(int i=0;i<v;i++){
			dist[i]=INT_MAX;
			p[i]=0;
		}
		char path[v];
		int s=find(vset,a);
		dist[s]=0;
		p[s]=s;
	//	path[s]='0';
		for(int i=0;i<v-1;i++){
			for(int j=0;j<eset.size();j++){
				int u1=find(vset,eset[j].s);
				int v1=find(vset,eset[j].d);
				if(dist[u1]!=INT_MAX and dist[v1]>dist[u1]+eset[j].w){
					dist[v1]=dist[u1]+eset[j].w;
					p[v1]=u1;	
					
				}
			}
		}
		bool  NE=false;
		for(int j=0;j<eset.size();j++){
			int u1=find(vset,eset[j].s);
			int v1=find(vset,eset[j].d);	
			if(dist[u1]!=INT_MAX and dist[v1]>dist[u1]+eset[j].w){
				NE=true;
				break;
			}
		}
		if(NE){
			cout<<"Contains Negative edge--"<<endl;
			return;
		}
		for(int i=0;i<v;i++){
			if(p[i]==i)
				cout<<vset[i]<<" Distance- "<<dist[i]<<" it's root"<<endl;
			else
				cout<<vset[i]<<" Distance- "<<dist[i]<<" Parent-"<<vset[p[i]]<<endl;
		}		
	}
};
graph read_file(){
	int n;
	fstream g;
	g.open("GRAPH.txt",ios::in);
	g>>n;
	vector<char> k;
	for(int i=0;i<n;i++){
		char h;
		g>>h;
		k.push_back(h);
	}
		
	
	graph A=graph(n);
	A.insert_vset(k,n);
	int **a=(int **)malloc(n*sizeof(int*));
	for(int i=0;i<n;i++){
		int *f=(int *)malloc(n*sizeof(int));
		for(int j=0;j<n;j++)
			g>>f[j];
		*(a+i)=f;
	}

	A.in(a);	
	//A.show();
	return A;
	}
int main(void){
	graph g=read_file();
	g.show();
	g.show_edge_set();
//	cout<<INT_MAX<<endl;
	g.Bellman_Ford('F');

}
