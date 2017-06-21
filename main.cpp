#include"sokoban.h"
int main(){
    ifstream fin("1.txt");
    Sokoban sok(fin);
    sok.work();
}
