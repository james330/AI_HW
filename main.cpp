#include<iostream>
#include"gameTree.cpp"
#include<time.h> 
//#include"tree.cpp"
using namespace std; 
int main(){
	
	double time;
	int x;
	gameTree g1; 
	//g1.minmax();
	//Ai is player 1;
	/*for(int i=0 ;i<20 ;i++)
	{
		
		time=clock();
		g1.minmax();
		cout<<"time is: "<<(clock()-time)/CLOCKS_PER_SEC<<" sec\n";
		cin>>x;
		
		g1.out(2 ,x);
		g1.mov_now(2 ,x);
		g1.out(2 ,x);
		if(g1.detect_turn_alive(1) == 5 || g1.detect_turn_alive(2) == 5){
			i=20;
		}
	}*/ 
	
	//Ai is player 2;
	for(int i=0 ;i<20 ;i++)
	{
		cin>>x;
		g1.out(1 ,x);
		g1.mov_now(1 ,x);
		g1.out(1 ,x);
		g1.minmax2();
		if(g1.detect_turn_alive(1) == 5 || g1.detect_turn_alive(2) == 5){
			i=20;
		}
	}
	
}
