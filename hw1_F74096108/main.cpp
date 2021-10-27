#include <iostream>
#include <vector>
#include <stack>
#include <fstream>

class point{ //class point is to record every point with their correspond x and y position and direction
public :
    int x ;
    int y ;
    int dir ; //direction which the next step will take
point() : x(0) , y(0) , dir(0) {} ; //constructor
point(int i , int j ) : x(i) , y(j) , dir(0) {} ; //constructor
};


using namespace std ;
void readFile(ifstream& ifs , vector<string>& maze); // load the file
void printMaze(vector<string>& maze); //print out the map loaded from the file
void solution(stack<point>& s , vector<string>& maze , point& startPoint , point& endPoint) ; // show the path
const int dir_x[4]={1,0,0,-1}; // dir_x[0] together with dir_y[0] represent the dir=0 moving direction which is moving
const int dir_y[4]={0,1,-1,0}; // right .

int main() {
    //variables
    vector<string> maze ; // store the map loaded from the file
    string filename ; // store the filename typed by the user
    int p_x , p_y ; // p_x , p_y are used to store the number to initialize the point objects

    cout << "enter filename : " ;
    cin >> filename ;
    ifstream ifs(filename , std::ios::in );
    readFile(ifs,maze); // load the file
    printMaze(maze); //print out the map loaded from the file

    while(1){
        stack<point> s; // using the stack to backtrack
        cout << "enter start position : " ;
        cin >> p_y >> p_x;
        point startPoint(p_x,p_y); //create the startPoint by constructing the point class object
        if(p_x==-1 && p_y==-1){ // end the program when the user type (-1,-1)
            cout << "end the code." ;
            break;
        }
        cout << "enter exit position : " ;
        cin >> p_y >> p_x ;
        if(p_x==-1 && p_y==-1){ // end the program when the user type (-1,-1)
            cout << "end the code." ;
            break;
        }
        point endPoint(p_x,p_y); //create the endPoint by constructing the point class object

        solution(s , maze , startPoint , endPoint) ; // find out the route the mouse has gone through
    }
    return 0;
}

void readFile(ifstream& ifs , vector<string>& maze){ //read the file
    if(!ifs.is_open()){
        cout << "The file can not open . " ; // error message
        exit(1);
    }
    else{
        string temp ; // create the string variable to store the data form the loaded file and push it back to the maze
        while(std::getline(ifs,temp))
            maze.push_back(temp);
    }
}

void printMaze(vector<string>& maze){
    for(auto x: maze){
        for(auto y : x)
            cout<<y ;
        cout<<"\n" ;
    }
}

void solution(stack<point>& s , vector<string>& maze , point& startPoint , point& endPoint){
    int mark[17][17]={0}; //initialize the mark which records the path has been traveled
    s.push(startPoint); // add the startPoint to the stack
    mark[startPoint.y][startPoint.x]=1; //mark the start point
    int count = 0; // count variable is used to record the steps

    if(startPoint.x == endPoint.x && startPoint.y == endPoint.y ){ //if the startPosition is same as endPosition
        cout << count << ":"<<startPoint.y<<","<<startPoint.x<<"\n";
        cout << "successfully escaped!!\n";
        return ;
    }

    while(!s.empty()){
        point temp=s.top();
        s.pop();
        int i=temp.x , j=temp.y , d=temp.dir ;
        cout << count << ":"<<j<<","<<i<<"\n";

        while(d<4){ // d only has four directions (right , down , up , left)
            int g=i+dir_x[d] ;//next step
            int h=j+dir_y[d] ;//next step
            if(g==endPoint.x && h==endPoint.y){//reach exit
                count++;
                cout << count << ":"<<h<<","<<g<<"\n";
                cout << "successfully escaped!!\n";
                return ;
            }
            if( maze[h][g]!='1' && mark[h][g]!=1){ //find the new point , is valid and haven't been traveled before
                mark[h][g]=1;
                temp.x=i;
                temp.y=j;
                temp.dir=d+1;
                s.push(temp); // push the current position i and j and another direction . Since there might have
                count++; // another possible way
                cout << count << ":"<<h<<","<<g<<"\n";
                i=g ; // move the current position to the next step
                j=h ;
                d=0 ; // remember to set the d to 0
            }else
                d++ ; //can't find out the new point , try another direction
        }
        count++;
    }
    cout << "Failed to escape ." << endl ;
    return;
}
