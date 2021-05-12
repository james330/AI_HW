// 			4 
//			0 
//	6	2	A	3	7 
//			1 
//			5 



#include<iostream>
#include"tree.cpp"
using namespace std;
class gameTree{
	private:
		tree now;
		tree temp;
		int a_x;
		//不用ARRAY，改用多個英文字母就好了 = = ，反正也不需要存甚麼東西 ? 
		int arr[28][28][28];
		int value_mov;
		int alpha;
		int beta;
	public:
		gameTree();
		int det_alive(int turn ,int number);//return 1 means die; 
		int detect_turn_alive(int turn);
		int mov(int turn ,int number);
		int mov_now(int turn ,int number);
		int point(int turn ,tree a ,tree b);//a is now ,b is temp;
		int minmax();
		int minmax2();
		void out(int turn ,int number);
		~gameTree();
		
};
gameTree::gameTree(){
	
	alpha=-100;
	beta=100;
	
	now.set_starting();
	
	
	for(int i=0 ;i<28 ;i++){
		for(int j=0 ;j<28 ;j++){
			for(int k=0 ;k<28 ;k++){
				arr[i][j][k]=0;
			}
		}
	}
}

int gameTree::det_alive(int turn ,int number){
	tree temp;
	int x ,y ,p;
	int i=number/4;
	if(turn == 1){
		if(i<2){
			p=0;
		}
		else if(i<4){
			p=1;
		}
		else if(i==4){
			p=2;
		} 
		else if(i==5){
			p=3;
		}
		else if(i==6){
			p=4;
		}
	}
	else if(turn == 2){
		if(i<2){
			p=5;
		}
		else if(i<4){
			p=6;
		}
		else if(i==4){
			p=7;
		} 
		else if(i==5){
			p=8;
		}
		else if(i==6){
			p=9;
		}
	}
	else{
		cout<<"your turn is error"<<endl;
		return false;
	}
	
	return temp.detect_live(p);
		
}

int gameTree::mov(int turn ,int number){
	//at turn =1;
	//if turn =1  ,piece[0:4]
	//else ,piece[5:9]
	// A = 0~7
	// B = 8~15
	// e = 16~19
	// f = 20~23
	// g = 24~27
	int i=number/4;
	int j=number%4;
	
	if(turn == 1){
		switch(i){
			case 0:
				return temp.set_piece('A' ,j ,i+1);
				break;
			case 1:
				return temp.set_piece('A' ,j ,i+1);
				break;
			case 2:
				return temp.set_piece('B' ,j ,i-1);
				break;
			case 3:
				return temp.set_piece('B' ,j ,i-1);
				break;
			case 4:
				return temp.set_piece('e' ,j ,1);
				break;
			case 5:
				return temp.set_piece('f' ,j ,1);
				break;
			case 6:
				return temp.set_piece('g' ,j ,1);
				break; 
		}
			
	}
	else if(turn == 2){
		switch(i){
			case 0:
				return temp.set_piece('X' ,j ,i+1);
				break;
			case 1:
				return temp.set_piece('X' ,j ,i+1);
				break;
			case 2:
				return temp.set_piece('Y' ,j ,i-1);
				break;
			case 3:
				return temp.set_piece('Y' ,j ,i-1);
				break;
			case 4:
				return temp.set_piece('u' ,j ,1);
				break;
			case 5:
				return temp.set_piece('v' ,j ,1);
				break;
			case 6:
				return temp.set_piece('w' ,j ,1);
				break; 
		}
	}
	else{
		cout<<"your turn is error"<<endl;
		return 1;
	}
}

void gameTree::out(int turn ,int number){
	int i=number/4;
	if(turn == 1){
		if(i<2)
			now.out_one_piece(0);
		if(i>=2 &&i<4)
			now.out_one_piece(1);
		if(i==4)
			now.out_one_piece(2);
		if(i==5)
			now.out_one_piece(3);
		if(i==6)
			now.out_one_piece(4);
	}
	else if(turn == 2){
		if(i<2)
			now.out_one_piece(5);
		if(i>=2 &&i<4)
			now.out_one_piece(6);
		if(i==4)
			now.out_one_piece(7);
		if(i==5)
			now.out_one_piece(8);
		if(i==6)
			now.out_one_piece(9);
	}
}

int gameTree::minmax(){	
	alpha=-100;
	beta=100;	
	int b_x ,a_y ,b_y ,a_z ,b_z ,p;
	a_x=alpha;
	a_y=alpha;
	a_z=alpha;
	b_x=beta;
	b_y=beta;
	b_z=beta;
	tree temp2 ,temp3;
	temp =now;
	int i=0 ,j=0 ,k=0;
	for(int x=0 ;x<28 ;){
		i++;
		//若該棋子已死 
		if(det_alive(1 ,x) == 1){
			x++; 
		}
		else{
			//若該棋子存活，那試走看看
			//若合法再往下展開 
			if(mov(1 ,x) == 1){
				//這裡是不合法部分 
				temp = now;
				x++;
			} 
			else{
				//這裡是合法走法展開部分
				//將上層的ALPHA，BETA傳到下層
				a_y = a_x;
				b_y = b_x;
				j++;
				
				//將該層棋盤狀態記錄下來
				temp2=temp;
				
				//展開下面的走法 
				for(int y=0 ;y<28 ;){
					j++;
					//若該棋子已死
					if(det_alive(2 ,y) == 1){
						y++;
					}
					else{
						//若該棋子存活，那試走看看
						//若合法再往下展開 
						if(mov(2 ,y) == 1){
							//這裡是不合法部分 
							temp=temp2;
							y++;
						}
						else{
							//這裡是合法走法展開部分
							//將上層的ALPHA，BETA傳到下層
							a_z = a_y;
							b_z = b_y;
							
							//將該層棋盤狀態記錄下來
							temp3=temp;
							
							for(int z=0 ;z<28 ;){
								k++;
								if(det_alive(1 ,z) == 1){
									z++;
								}
								else{
									if(mov(1 ,z) == 1){
										temp=temp3;
										z++;
									}
									else{
										p=point(1 ,now ,temp);
										if(p > a_z){
											a_z = p;
											if(a_z >= b_z){
												temp=temp3;
												z++;
											}
										}
									}
								}
							}
							
							//將該層ALPHA，BETA 中最小的回傳到上層的BTEA 
							if(a_z < b_y){
								b_y = a_z;
							}
							temp=temp2;
							y++;
						}
						
					}
					
				}
				
				//將該層ALPHA，BETA 中最大的回傳到上層的ALPHA
				if(b_y > a_x){
					value_mov=x;
					a_x = b_y;
				}
				temp = now;
				x++;
			}	
		}
		
	}
	
	
	
	
	cout<<"mov step: "<<value_mov<<endl;
	
	out(1 ,value_mov);
	mov_now(1 ,value_mov);
	out(1 ,value_mov);
}

int gameTree::minmax2(){
	alpha=-100;
	beta=100;	
	int b_x ,a_y ,b_y ,a_z ,b_z ,p;
	a_x=alpha;
	a_y=alpha;
	a_z=alpha;
	b_x=beta;
	b_y=beta;
	b_z=beta;
	tree temp2 ,temp3;
	temp =now;
	int i=0 ,j=0 ,k=0;
	for(int x=0 ;x<28 ;){
		i++;
		//若該棋子已死 
		if(det_alive(2 ,x) == 1){
			x++; 
		}
		else{
			//若該棋子存活，那試走看看
			//若合法再往下展開 
			if(mov(2 ,x) == 1){
				//這裡是不合法部分 
				temp = now;
				x++;
			} 
			else{
				//這裡是合法走法展開部分
				//將上層的ALPHA，BETA傳到下層
				a_y = a_x;
				b_y = b_x;
				j++;
				
				//將該層棋盤狀態記錄下來
				temp2=temp;
				
				//展開下面的走法 
				for(int y=0 ;y<28 ;){
					j++;
					//若該棋子已死
					if(det_alive(1 ,y) == 1){
						y++;
					}
					else{
						//若該棋子存活，那試走看看
						//若合法再往下展開 
						if(mov(1 ,y) == 1){
							//這裡是不合法部分 
							temp=temp2;
							y++;
						}
						else{
							//這裡是合法走法展開部分
							//將上層的ALPHA，BETA傳到下層
							a_z = a_y;
							b_z = b_y;
							
							//將該層棋盤狀態記錄下來
							temp3=temp;
							
							for(int z=0 ;z<28 ;){
								k++;
								if(det_alive(2 ,z) == 1){
									z++;
								}
								else{
									if(mov(2 ,z) == 1){
										temp=temp3;
										z++;
									}
									else{
										p=point(2 ,now ,temp);
										if(p > a_z){
											a_z = p;
											if(a_z >= b_z){
												temp=temp3;
												z++;
											}
										}
									}
								}
							}
							
							//將該層ALPHA，BETA 中最小的回傳到上層的BTEA 
							if(a_z < b_y){
								b_y = a_z;
							}
							temp=temp2;
							y++;
						}
						
					}
					
				}
				
				//將該層ALPHA，BETA 中最大的回傳到上層的ALPHA
				if(b_y > a_x){
					value_mov=x;
					a_x = b_y;
				}
				temp = now;
				x++;
			}	
		}
		
	}
	
	
	
	
	cout<<"mov step: "<<value_mov<<endl;
	
	out(2 ,value_mov);
	mov_now(2 ,value_mov);
	out(2 ,value_mov);
}

int gameTree::point(int turn ,tree a ,tree b){
	int weight=0;
	//檢測 0~9位置的棋子
	//看誰死了? 應該會有0 ~ 10個棋子死? 
	for(int i=0 ;i<10 ;i++){
		//若該棋子本來就死的 
		if(a.detect_live(i) ==  1){;}
		else{
			//若該棋子從活的到死去? 
			if(b.detect_live(i) == 1){
				if(turn == 1){
					if(i<2)//A ,B
						weight-=12;
					if(i>=2 && i<5)//e ,f ,g
						weight-=7;
					if(i>=5 && i<7)//X ,Y
						weight+=10;
					if(i>=7 && i<10)//u ,v ,w
						weight+=5;
					else
						weight+=0;
				}
				else if(turn == 2){
					if(i<2)//A ,B
						weight+=10;
					if(i>=2 && i<5)//e ,f ,g
						weight+=5;
					if(i>=5 && i<7)//X ,Y
						weight-=12;
					if(i>=7 && i<10)//u ,v ,w
						weight-=7;
					else
						weight+=0;
				}
			}
		}	
	}
	
	return weight;
}

int gameTree::mov_now(int turn ,int number){
	int i=number/4;
	int j=number%4;
	
	if(turn == 1){
		switch(i){
			case 0:
				return now.set_piece('A' ,j ,i+1);
				break;
			case 1:
				return now.set_piece('A' ,j ,i+1);
				break;
			case 2:
				return now.set_piece('B' ,j ,i-1);
				break;
			case 3:
				return now.set_piece('B' ,j ,i-1);
				break;
			case 4:
				return now.set_piece('e' ,j ,1);
				break;
			case 5:
				return now.set_piece('f' ,j ,1);
				break;
			case 6:
				return now.set_piece('g' ,j ,1);
				break; 
		}
			
	}
	else if(turn == 2){
		switch(i){
			case 0:
				return now.set_piece('X' ,j ,i+1);
				break;
			case 1:
				return now.set_piece('X' ,j ,i+1);
				break;
			case 2:
				return now.set_piece('Y' ,j ,i-1);
				break;
			case 3:
				return now.set_piece('Y' ,j ,i-1);
				break;
			case 4:
				return now.set_piece('u' ,j ,1);
				break;
			case 5:
				return now.set_piece('v' ,j ,1);
				break;
			case 6:
				return now.set_piece('w' ,j ,1);
				break; 
		}
	}
	else{
		cout<<"your turn is error"<<endl;
		return 1;
	}
}

int gameTree::detect_turn_alive(int turn){
	int die=0;
	if(turn == 1){
		for(int i=0 ;i<5 ;i++){
			if(now.detect_live(i) == 1){
				die++;	
			}
		}
	}
	else if(turn == 2){
		for(int i=5 ;i<10 ;i++){
			if(now.detect_live(i) == 1){
				die++;	
			}
		}
	}
	
	if(die == 5){
		return 1;
	}
	else return 0;
}

gameTree::~gameTree(){
	;
}
