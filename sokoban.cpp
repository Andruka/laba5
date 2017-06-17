#include"sokoban.h"
Sokoban::Sokoban(ifstream & fin){
    char ch;
    int count;
    State start;
    int height=0;
    for(int i=0;;++i){
	fin.read(&ch,1);
	if(fin.eof())break;
	++count;
	if(ch=='#')not_a_wall.push_back(false);
	else not_a_wall.push_back(true);
	switch(ch){
		case 'P': start.person=i;break;
		case 'X': start.placeForBoxes.push_back(i);break;
		case '@': start.boxes.push_back(i);break;
		case '\n':--i;++height;break;
		default: break;
		}
	}
    width=count/height;
    last_states.push_back(start);cout<<2<<endl;
    cout<<last_states.size()<<'q'<<endl;
    cout<<width<<endl;
    for(int i=0;i<last_states[0].boxes.size();++i)cout<<last_states[0].boxes[i]<<"";
    cout<<3<<endl; 
    for(int i=0;i<last_states[0].placeForBoxes.size();++i)cout<<last_states[0].placeForBoxes[i]<<"";
    cout<<endl; 
    cout<<last_states[0].person<<endl; 
    for(int i=0;i<not_a_wall.size();++i)cout<<not_a_wall[i]<<"";

}
Sokoban::State::State(){
    person=0;
}
Sokoban::State::State(const State & ob){
        for(int i=0;;i<ob.boxes.size())boxes.push_back(ob.boxes[i]);
   	for(int i=0;;i<ob.placeForBoxes.size())placeForBoxes.push_back(ob.placeForBoxes[i]);
	for(int i=0;;i<ob.way.size())way.push_back(ob.way[i]);
    	person=ob.person;
}
bool Sokoban::compare(State ob1,State ob2){
    int count_boxes;
    bool flag=false;
    if(ob1.person==ob2.person)return 1;
    if(ob1.boxes.size()!=ob2.boxes.size())return 0;
    count_boxes=ob1.boxes.size();
    for(int i=0;i<count_boxes;++i){
	for(int j=0;j<count_boxes;++j){
	    if(ob1.boxes[i]==ob2.boxes[j]){
		flag=true;
		break;
		}
	    }
	if(flag)flag=false;
	else return 0;
	}
    for(int i=0;i<count_boxes;++i){
	for(int j=0;j<count_boxes;++j){
	    if(ob1.placeForBoxes[i]==ob2.placeForBoxes[j]){
		flag=true;
		break;
		}
	    }
	if(flag)flag=false;
	else return 0;
	}
    return 1;
}
/*Sokoban::int check_cell(int course,State state){
    int cell1=1,cell2=1;
    if(course==1){
	if(!not_a_wall[state.person-width])cell1=0;
	else{
	    for(int i=0;i<state.boxes.size();++i){
	    	if((state.person-width)==state.boxes[i])cell1=2;
	    	}
	    }
        if(!not_a_wall[state.person-2*width])cell2=0;
	else{
	    cell2=1;
	    for(int i=0;i<state.boxes.size();++i){
	    	if((state.person-2*width)==state.boxes[i])cell2=2;
	    	}
	    }
	if(cell1==1)return 1;
	if(cell1==2 && cell2==1)return 2;
	if(cell1==0 || (cell1==2 && cell2==2))return 0;
        }
}*/
