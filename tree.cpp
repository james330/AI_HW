#include<iostream>

using namespace std;
class tree{
	private:
		int piece[10][3];
	public:
		tree();
		//就移動棋子到新的位址，檢查是否超出邊界和是否有其他棋子，在外面做檢測 
		int set_piece(char p ,int pos ,int mov);//move piece
		//確定該新位址為合法的，並無超出範圍 (0~7);
		bool detect_boundary(int p ,int x ,int y);
		//檢測該位址無任何棋子，若有則回傳該棋子編號  ,無則回傳 10; 
		const int detect_pos(const int p ,const int x ,const int y);
		//用做檢查該棋子是否活著 ,(-1 -1)就是死了 return 0;
		int detect_live(int p);
		//用來回傳該棋子單方向可移動步數上限
		int rMov(int p); 
		void set_starting();
		void out_piece();
		void out_one_piece(int number);
		~tree();
		
		friend class gameTree;
}; 
tree::tree(){
	piece[0][0]='A';//A = 65
	
	piece[1][0]='B';//B = 66
	
	piece[2][0]='e';//e = 101
	
	piece[3][0]='f';//f = 102
	
	piece[4][0]='g';//g = 103
	
	piece[5][0]='X';//X = 88
	
	piece[6][0]='Y';//Y = 89
	
	piece[7][0]='u';//u = 117
	
	piece[8][0]='v';//v = 118
	
	piece[9][0]='w';//w = 119			
}
void tree::set_starting(){
	//set piece in starting point?
	//A (X ,Y)
	piece[0][1]=3;
	piece[0][2]=1;	
	//B
	piece[1][1]=5;
	piece[1][2]=3;
	//e
	piece[2][1]=1;
	piece[2][2]=3;	
	//f
	piece[3][1]=4;
	piece[3][2]=3;
	//g
	piece[4][1]=5;
	piece[4][2]=5;
	//X
	piece[5][1]=6;
	piece[5][2]=2;
	//Y
	piece[6][1]=4;
	piece[6][2]=6;
	//u
	piece[7][1]=2;
	piece[7][2]=2;
	//v
	piece[8][1]=3;
	piece[8][2]=4;
	//w
	piece[9][1]=6;
	piece[9][2]=6;
}
int tree::set_piece(char p ,int pos ,int mov){
	//i is the position of piece[]; 
	//x is the piece x-position
	//y is the piece y-position
	//0 up
	//1	down
	//2	left
	//3	right
	
	
	int i ,x ,y ,det ,chess;
	for(i=0 ;i<10 ;){
		//to find this piece (x ,y)
		if(p != piece[i][0]){
			i++;
		}
		else{
			break;
		}
	}
	chess=piece[i][0];
	x=piece[i][1];
	y=piece[i][2];
	
	
	switch(pos){
		case 0://up	
			det=detect_pos(i ,x ,y-mov);
			if(detect_boundary(piece[i][0] ,piece[i][1] ,y-mov) == 1){
				return 1;
			}
			else if(det != 10){
				if(det<5 && i<5){
					return 1;
				}
				else if(det<5 && i>=5){
					piece[det][1]=-1;
					piece[det][2]=-1;
					piece[i][2]=y-mov;
					return 0;
				}
				else if(det>=5 && i<5){
					piece[det][1]=-1;
					piece[det][2]=-1;
					piece[i][2]=y-mov;
					return 0;
				}
				else if(det >=5 && i>=5){
					return 1;
				}
			}
			else
				piece[i][2]=y-mov;
			break;
		case 1://down
			det=detect_pos(i ,x ,y+mov);
			if(detect_boundary(piece[i][0] ,piece[i][1] ,y+mov) == 1){
				return 1;
			}
			else if(det != 10){
				if(det<5 && i<5){
					return 1;
				}
				else if(det<5 && i>=5){
					piece[det][1]=-1;
					piece[det][2]=-1;
					piece[i][2]=y+mov;
					return 0;
				}
				else if(det>=5 && i<5){
					piece[det][1]=-1;
					piece[det][2]=-1;
					piece[i][2]=y+mov;
					return 0;
				}
				else if(det >=5 && i>=5){
					return 1;
				}
			}
			else
				piece[i][2]=y+mov;
			break;
		case 2://left
			det=detect_pos(i ,x-mov ,y);
			if(detect_boundary(piece[i][0] ,x-mov ,piece[i][2]) == 1){
				return 1;
			}
			if(det == 10){
				piece[i][1]=x-mov;	
			}
			else{
				if(det<5 && i<5){
					return 1;
				}
				else if(det<5 && i>=5){
					piece[det][1]=-1;
					piece[det][2]=-1;
					piece[i][1]=x-mov;
					return 0;
				}
				else if(det>=5 && i<5){
					piece[det][1]=-1;
					piece[det][2]=-1;
					piece[i][1]=x-mov;
					return 0;
				}
				else if(det >=5 && i>=5){
					return 1;
				}
			}	
			break;
		case 3://right
			det=detect_pos(i ,x+mov ,y);
			if(detect_boundary(piece[i][0] ,x+mov ,piece[i][2]) == 1){
				return 1;
			}
			else if(det != 10){
				if(det<5 && i<5){
					return 1;
				}
				else if(det<5 && i>=5){
					piece[det][1]=-1;
					piece[det][2]=-1;
					piece[i][1]=x+mov;
					return 0;
				}
				else if(det>=5 && i<5){
					piece[det][1]=-1;
					piece[det][2]=-1;
					piece[i][1]=x+mov;
					return 0;
				}
				else if(det >=5 && i>=5){
					return 1;
				}
			}
			else
				piece[i][1]=x+mov;
			break;
		defult:
			break;
	}	
}
const int tree::detect_pos(const int p ,const int x ,const int y){
	//find[0:p-1] ,if i(x ,y) == p(x ,y) return i;
	for(int i=0 ;i<p ;){
		if(piece[i][1]==x)
		{
			if(piece[i][2]==y){
				return i;
			}
			else{
				i++;
			} 
		}
		else i++;
	}
	//find[p+1:9] ,if i(x ,y) == p(x ,y) return i;
	//else return 10 ,means not found;
	for(int i=p+1 ;i<10 ;){
		if(piece[i][1]==x)
		{
			if(piece[i][2]==y){
				return i;
			}
			else{
				i++;
			} 
		}
		else{
			i++;
		}
		if(i==10) return i;//not found i=10
	}
}
bool tree::detect_boundary(int p ,int x ,int y){
	if(x<0 || x>7){
		return 1;
	}
	else if(y<0 || y>7){
		return 1;
	}
	else
		return 0;
}
int tree::detect_live(int p){
	if(piece[p][1] ==-1 && piece[p][2] == -1){
		return 1;
	}
	else
		return 0;
}
int tree::rMov(int p){
	switch(p){
		case 65:
			return 65;
			break;
		case 66:
			return 66;
			break;
		case 101:
			return 101;
			break;
		case 102:
			return 102;
			break;
		case 103:
			return 103;
			break;
		case 88:
			return 88;
			break;
		case 89:
			return 89;
			break;
		case 117:
			return 117;
			break;
		case 118:
			return 118;
			break;
		case 119:
			return 119;
			break;
		default:
			break;
	}
}
void tree::out_piece(){
	for(int i=0 ;i<10 ;i++){
		for(int j=0 ;j<3 ;j++){
			cout<<piece[i][j]<<" ";
		} 
		cout<<endl;
	}
	cout<<endl;
}
void tree::out_one_piece(int number){
	cout<<(char)piece[number][0]<<":";
	cout<<"("<<piece[number][1]<<","<<piece[number][2]<<")\n"; 
}
tree::~tree(){
	;
}
