#include <iostream>
#include <vector>
#include <functional>
#include <math.h>
#include <algorithm>
#include <queue>
#include <set>
#include <iterator>


using namespace std;

class Node {

public:

  int hCost;
  int cCost;
  vector<int> state;
  string movement;

  Node() = default;

  Node(int h, int c, vector<int> _state, string s){
        hCost = h;
        cCost = c;
        state = _state;
        movement = s;
    }

    int getfCost(){
    return hCost + cCost;
    }


    string makeKey() {
		string keystr = "";
		for (int i = 0; i < 9; i++) {
				keystr += to_string(state.at(i));
        }
		return keystr;
	}


};

struct compareCost {
	bool operator()(Node &n1, Node &n2) {

		return n1.getfCost() > n2.getfCost();
	}
};

int getZeroPosition(vector<int> state){

    //find which pos the 0 is in
    for(unsigned int i=0; i < 9 ;i++){
        if(state.at(i) == 0){
            return i;
        }
    }

    return 0;

}

vector<pair<int, string>> findPossibleMoves(Node currentNode){

    int pos;
    vector<pair<int, string>> moves;

    pos = getZeroPosition(currentNode.state);

    switch (pos) {

        case 0:
             moves.push_back(make_pair(1,"r"));
             moves.push_back(make_pair(3, "d"));
            break;
        case 1:
             moves.push_back(make_pair(0,"l"));
             moves.push_back(make_pair(2, "r"));
            moves.push_back(make_pair(4, "d"));
            break;
        case 2:
             moves.push_back(make_pair(1,"l"));
             moves.push_back(make_pair(5, "d"));
            break;
        case 3:
            moves.push_back(make_pair(0,"u"));
            moves.push_back(make_pair(4, "r"));
            moves.push_back(make_pair(6, "d"));
            break;
        case 4:
            moves.push_back(make_pair(1,"u"));
            moves.push_back(make_pair(3, "l"));
            moves.push_back(make_pair(5, "r"));
            moves.push_back(make_pair(7, "d"));

            break;
        case 5:
            moves.push_back(make_pair(2, "u"));
            moves.push_back(make_pair(4, "l"));
            moves.push_back(make_pair(8, "d"));
            break;
        case 6:
            moves.push_back(make_pair(3, "u"));
            moves.push_back(make_pair(7, "r"));
            break;
        case 7:
            moves.push_back(make_pair(4, "u"));
            moves.push_back(make_pair(6, "l"));
            moves.push_back(make_pair(8, "r"));
            break;
        case 8:
            moves.push_back(make_pair(5, "u"));
            moves.push_back(make_pair(7, "l"));
            break;

        default:
            break;
    }

    return moves;

}

int getH1(vector<int> state, vector<int> goalState){

int misplacedTiles = 0;

    for (unsigned int i = 0; i < 9; i++){
        if(state.at(i) != goalState.at(i) &&  state.at(i) != 0){
            misplacedTiles++;
        }
    }

    cout << "misplaced: " << misplacedTiles << endl;


    return misplacedTiles;

}


int getManhattan(vector<int> state, vector<int> goalState){

int xPos, yPos, xGoalPos, yGoalPos;
int dist = 0;

//calculate manhattan distance
    for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
            if(state.at(i) == goalState.at(j)){
                xPos = i%3;
                yPos = floor(i/3);

                xGoalPos = j%3;
                yGoalPos = floor(j/3);

                if(state.at(i) != 0)
                dist += abs(xPos - xGoalPos) + abs(yPos - yGoalPos);
            }

        }

	}

    return dist;

}




 string FindPath(vector<int> startState, vector<int> goalState) {


    Node startNode(0, 0, startState, "");

    priority_queue<Node, vector<Node>, compareCost> openSet;
    openSet.push(startNode);
    vector<pair<int, string>> possibleMoves;
    set<string> closedSet;

    int numbMoves = 0;
    Node currentNode;

    while(!openSet.empty()){

        numbMoves++;
        currentNode = openSet.top();
        openSet.pop();
        closedSet.emplace(currentNode.makeKey());


        if(currentNode.state == goalState)
        {
            cout << endl << ":D Solution found!" << endl;
            cout << "Nodes checked: " << numbMoves << endl;
            return currentNode.movement;
        }


        //returns a vector of positions for the 0 to move in
       possibleMoves = findPossibleMoves(currentNode);

        //auto
        for( const auto &i : possibleMoves){

            vector<int> newState = currentNode.state;
            swap(newState.at(i.first), newState.at(getZeroPosition(currentNode.state)));

            Node newNode(getManhattan(newState, goalState),currentNode.cCost+1, newState, currentNode.movement+i.second);

            if (closedSet.find(newNode.makeKey()) != closedSet.end()) {
                continue;
            }
            openSet.push(newNode);


        }


    }

    cout << "No solution found!" << endl;

    return currentNode.movement;



 }



int main(int argc, char *argv[])
{


    //hardest case
    vector<int> startState{6, 4, 7, 8, 5, 0, 3, 2 , 1};

   //easy case
   //vector<int> startState {1, 2, 3, 4, 5, 6, 0, 7, 8};

    //some case
    //vector<int> startState {6, 4, 7, 8, 5, 0, 3, 2, 1};


    vector<int> goalState {1, 2, 3, 4, 5, 6, 7, 8, 0};

    string moves = FindPath(startState, goalState);

    cout << "Movement steps: " + moves << endl;


    return 0;
}





