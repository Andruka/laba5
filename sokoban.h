#include<cstdlib>
#include<iostream>
#include<fstream>
#include<vector>
#include<stack>
#include<map>
#include<unistd.h>
using namespace std; 
class Sokoban;
class State{
  public:
    unsigned char boxes[7];
    unsigned char person;
    State();
    State& operator = (const State& state);
    friend bool operator < (State st1,State st2);
    friend Sokoban;
};
class Sokoban{
    State start;
    unsigned char width;
    unsigned char placeForBoxes[7];
    map<State,State>ways;
    vector <bool> not_a_wall;
    vector <State> last_states,cur_states;
    stack <State> win_way;
  public:
    Sokoban(ifstream & fin);
    friend bool operator == (State state1,State state2);
    int check_cell(int course,State  state);
    bool check_finish(State win);
    bool push_box(int course,State & state);
    int create_state(int course,State & state);
    State find_way();
    void print(State state);
    void work();    
};
