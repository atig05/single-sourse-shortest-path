#include<bits/stdc++.h>
#define vertex pair<char,int> 
using namespace std;

int find(vector<char> s,char a){
	for(int i=0;i<s.size();i++){
		if(s[i]==a)
			return i;
	}
	return -1;
}


class graph{
	int **G;
	public:
	vector<char> vset;
	int v;
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

	void in(int **a){
		int k=0;
		for(int i=0;i<v;i++){
			int *f=(int *)malloc(v*sizeof(int));
			for(int j=0;j<v;j++){
				f[j]=a[i][j];

					
			}
				*(G+i)=f;
		}
	}	
	void show_vertex(){
		for(int i=0;i<vset.size();i++)
			cout<<vset[i]<<" ";
		cout<<endl;
	}
	vector<vertex> dijkstra(char a){
		int dis[v];
		vector<vertex> spt;
		
		bool track[v];
		for(int i=0;i<v;i++){
			dis[i]=INT_MAX;
			track[i]=false;
		}
		int ai=find(vset,a);
		dis[ai]=0;
		pair<char ,int> t;
		t.first=vset[ai];
		t.second=0;
		spt.push_back(t);
		
		track[ai]=true;		
		while(spt.size()!=v){
			
			int m=INT_MAX;
			int mi=-1;
			for(int i=0;i<v;i++){
				if(ai!=i && G[ai][i]!=0 && dis[i]>dis[ai]+G[ai][i])
					dis[i]=dis[ai]+G[ai][i];
				if(dis[i]<m && dis[i]!=0 && !track[i]){
					m=dis[i];
					mi=i;
				}
			}
			ai=mi;
			pair<char ,int> t;
			t.first=vset[ai];
			t.second=m;
			spt.push_back(t);
			track[ai]=true;
		}
		return spt;
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
	char a;
	cout<<"enter  starting point--";
	cin>>a;
	vector<vertex> v=g.dijkstra(a);
	for(int i=0;i<v.size();i++)
		cout<<v[i].first<<"-"<<v[i].second<<endl;
}
