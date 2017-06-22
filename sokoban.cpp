#include"sokoban.h"
Sokoban::Sokoban(ifstream & fin){
    char ch;
    unsigned char a=0,b=0;
    start.person=0;
    for(int i=0;i<7;++i)start.boxes[i]=0;
    width=0;
    for(int i=0;i<7;++i)placeForBoxes[i]=0;
    for(int i=0;;++i){
	fin.read(&ch,1);
	if(fin.eof())break;
	if(ch=='#')not_a_wall.push_back(false);
	else if(ch!='\n')not_a_wall.push_back(true);
	switch(ch){
		case 'P': start.person=i;break;
		case 'X': placeForBoxes[b]=i;++b;break;
		case '@': start.boxes[a]=i;++a;break;
		case '\n':--i;if(width==0)width=i+1;break;
		default: break;
		}
	}
    last_states.push_back(start);
}
State::State(){
    person=0;
    for(int i=0;i<7;++i)boxes[i]=0;
}
State::State(const State& state){
    person=state.person;
    for(int i=0;i<7;++i)boxes[i]=state.boxes[i];
}
bool operator ==(State state1,State state2){
    if(state1.person!=state2.person)return 0;
    for(int i=0;i<7;++i){
	if(state1.boxes[i]!=state2.boxes[i])return 0;
	}
    return 1;
}
bool operator < (const State & st1,const State & st2) {
    for(int i=0;i<7;++i){
	if(st1.boxes[i]<st2.boxes[i])return true;
	}
    if(st1.person<st2.person)return true;
    return false;
}
State& State:: operator = (const State& state){
        if (this == &state) {
            return *this;
        }
	for(int i=0;i<7;++i)boxes[i]=state.boxes[i];	
    	person=state.person;
        return *this;
}
int Sokoban::check_cell(int course,State state){
    int temp,cell1=1,cell2=1;
    switch(course){
	case 1:temp=-width;break;
	case 2:temp=width;break;
	case 3:temp=-1;break;
	case 4:temp=1;break;
	}
    if(!not_a_wall[state.person+temp])cell1=0;
    else{
	for(int i=0;i<7;++i){
	    if((state.person+temp)==state.boxes[i])cell1=2;
	    }
	}
    if(cell1!=0){
        if(!not_a_wall[state.person+2*temp])cell2=0;
	else{
	    cell2=1;
	    for(int i=0;i<7;++i){
	    	if((state.person+2*temp)==state.boxes[i])cell2=2;
	    	}
	    }
	}
    if(cell1==1)return 1;
    if(cell1==2 && cell2==1)return 2;
    if(cell1==0 || (cell1==2 && cell2==2))return 0;
}
bool Sokoban::check_finish(State win){
    for(int i=0;i<7;++i){
	if(win.boxes[i]!=placeForBoxes[i])return 0;
	}
    return 1;   
}
bool Sokoban::push_box(int course,State & state){
    int temp;
    unsigned char a;
    bool flag=true;
    switch(course){
	case 1:temp=-width;break;
	case 2:temp=width;break;
	case 3:temp=-1;break;
	case 4:temp=1;break;
	}
    state.person+=temp;
    for(int i=0;i<7;++i){
	if(state.person==state.boxes[i]){
	    state.boxes[i]+=temp;
	    break;
	    }
	}
    while(flag){
	flag=false;
    	for(int i=0;i<6;++i){
	    if((state.boxes[i]>state.boxes[i+1]) && state.boxes[i+1]!=0){
		a=state.boxes[i+1];
	 	state.boxes[i+1]=state.boxes[i];
		state.boxes[i]=a;
		flag=true;
		}
	    }
	}
    return check_finish(state);

}
int Sokoban::create_state(int course,State & state){
    if(check_cell(course,state)==0)return 0;
    if(check_cell(course,state)==1){
	switch(course){
	    case 1:state.person-=width;break;
	    case 2:state.person+=width;break;
	    case 3:state.person-=1;break;
	    case 4:state.person+=1;break;		
	    }
	return 1;
	}
    if(check_cell(course,state)==2){
	if(push_box(course,state))return 2;
	else return 1;
	}
}
State Sokoban::find_way(){
    State ob;
    int temp,r=0;
    while(true){
    	for(int i=0;i<last_states.size();++i){
	    for(int j=1;j<5;++j){
		ob=last_states[i];
		temp=create_state(j,ob);
		if(temp==1){
		    if(ways.find(ob)==ways.end())ways[ob]=last_states[i];
		    cur_states.push_back(ob);
		    }
		if(temp==2){
		    if(ways.find(ob)==ways.end())ways[ob]=last_states[i];
		    return ob;
		    }
		}
	    }
	last_states=cur_states;
        cur_states.clear();++r;
	}
}
void Sokoban::print(State state){
    char str[not_a_wall.size()];
    for(int i=0;i<not_a_wall.size();++i){
    	if(!not_a_wall[i])str[i]='#';
	else str[i]=' ';
    	}
    for(int i=0;i<7;++i){
	if(placeForBoxes[i]!=0)str[placeForBoxes[i]]='X';
	}
    for(int i=0;i<7;++i){
	if(state.boxes[i]!=0)str[state.boxes[i]]='@';
	}
    str[state.person]='P';
    for(int i=0;i<not_a_wall.size();++i){
	cout<<str[i];
	if((i+1)%width==0)cout<<endl;
	}
}
void Sokoban::work(){
    State temp;
    int i=0;
    temp=find_way();cout<<ways.size()<<endl;
    while(i<9){
	win_way.push(temp);
	if(temp==start)break;
	else temp=ways[temp];
	++i;
	}
    while(win_way.size()!=0){
	print(win_way.top());
	win_way.pop();
	sleep(2);
	}
}
