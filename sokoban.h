#include<cstdlib>
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
class Sokoban{
    int width;
    class State{
      public:
    	vector <int> boxes;
   	vector <int> placeForBoxes;
	vector <int> way;
    	int person;
	State();
	State(const State & ob);
    };
    vector <bool> not_a_wall;
    vector <State> last_states,cur_states;
  public:
    Sokoban(ifstream & fin);
    int check_cell(int course,State state);
    bool check_finish(State win);
    bool compare(State ob1,State ob2);
    bool push_box(int course,State state);
    void work();    
};
