#include <iostream>
#include <vector>
#include <cstdlib>
#include <queue>
#include <cmath>


const int row = 3; //row size of Matrix
const int column = 3; //columnumn size of Matrix

int defaultMatrix[row][column] = {{1,0,2},{7,5,4},{8,6,3}}; // default Matrix

int goal[row][column] = {{1,2,3},{4,5,6},{7,8,0}}; 

class Matrix
{

private:
    int Matrix[row][column];
    int level;
    int cost;
public:
    //Matrix constructor
    Matrix() {
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                Matrix[i][j] = defaultMatrix[i][j];
            }
        }
        level = 0;
        cost = 0;
    }
    
    //print out current board
    void displayMatrix()
    {
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < column; ++j)
            {
                std::cout << Matrix[i][j] << " ";
            }

            std::cout << std::endl;
        }
    }
    
    // change board value if users wanted to
    void changeVal(int arr[][column]) {
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                Matrix[i][j] = arr[i][j];
            }
        }
    }
    
    // check if two Matrixs are equal
    bool isEqual(int arr[][column]) {
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {

               if (Matrix[i][j] != arr[i][j]) {
                  return false;
               }
            }
        }

        return true;
    }
    
    //moving blank space up
    void moveUp() {

        int temp = 0;
        //starts from 1 because 0 row can never go up
        for (int i = 1; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                if (Matrix[i][j] == 0) {
                    temp = Matrix[i-1][j];
                    Matrix[i-1][j] = Matrix[i][j];
                    Matrix[i][j] = temp;
                    return;
                }
            }
        }
    }

    // moving blank space down
    void moveDown() { 
        int temp = 0;
        //ends at row - 1 because the last row can never go down
        for (int i = 0; i < row - 1; ++i) {
            for (int j = 0; j < column; ++j) {
                if (Matrix[i][j] == 0) {
                    temp = Matrix[i+1][j];
                    Matrix[i+1][j] = Matrix[i][j];
                    Matrix[i][j] = temp;
                    return;
                }
            }
        }
    }

    // moving blank space left
    void moveLeft() {
        int temp = 0;
        for (int i = 0; i < row; ++i) {
            //starts at second columnumn because first columnumn can never move left
            for (int j = 1; j < column; ++j) {
               if (Matrix[i][j] == 0) {
                  temp = Matrix[i][j-1];
                  Matrix[i][j-1] = Matrix[i][j];
                  Matrix[i][j] = temp;
                  return;
               }
            }
        }
    }
    // move blank space right
    void moveRight() {
        int temp = 0;
        for (int i = 0; i < row; ++i) {
            // ends at column - 1 because the last columnumn can never move right
            for (int j = 0; j < column - 1; ++j) {
                if (Matrix[i][j] == 0) {
                    temp = Matrix[i][j+1];
                    Matrix[i][j+1] = Matrix[i][j];
                    Matrix[i][j] = temp;
                    return;
                }
            }
        }
    }
    
    //evaluation function f(n) = g(n) + h(n) for misplaced tiles
    //increment whenever theres a value not matching the goal state
    int getMisplacedTilesCost()
    {
        int misplacedCnt = 0;
        
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j)
            {   
                //does not count blank space
                if (Matrix[i][j] != 0)
                {
                    if (Matrix[i][j] != goal[i][j])
                        misplacedCnt++;
                }
            }
        }
        
        cost = level + misplacedCnt;
        return cost;
    }
    

    int getManhattanCost() {
        int distanceCnt = 0;
        int val = 0;
        int xFinal = 0;
        int yFinal = 0;
        
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                val = Matrix[i][j];
                
                if (val != 0) {
                    xFinal = (val - 1) / row;
                    yFinal = (val - 1) % column;
                    distanceCnt = distanceCnt + abs(xFinal - i) + abs(yFinal - j);
                }
            }
        }
        
        cost = level + distanceCnt;
        return cost;
    }
    
   
   int getlevel() {
    return level;
   }
   
   void setlevel(int d) {
      level = d;
   }
   
   int getElement(int i, int j) {
      return Matrix[i][j];
   }
   
   Matrix& operator=(const Matrix& rhs)
   {
      level = rhs.level;
      
      for (int i = 0; i < row; ++i)
      {
         for (int j = 0; j < column; ++j)
         {
               Matrix[i][j] = rhs.Matrix[i][j];
         }
      }
      return *this;
   }
    
};

// check if two objects contain the same Matrix
bool sameMatrix(Matrix &p1, Matrix &p2)
{
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < column; ++j)
        {
            if (p1.getElement(i,j) != p2.getElement(i,j))
                return false;
        }
    }
    return true;
}

//check if successor state is repeated from any state that has been visited before
bool stateRepeated(vector<Matrix> &v, Matrix &p)
{
    for (int i = 0; i < v.size(); ++i)
    {
        if (sameMatrix(v.at(i),p))
            return true;
    }
    return false;
}

// sort based on misplaced tiles heuristic
void selectionSortMT(vector<Matrix> &v)
{
    Matrix temp;
    int min = 0;
    
    for (int i = 0; i < v.size(); ++i)
    {
        min = i;
        for (int j = i+1; j < v.size(); ++j)
        {
            if (v.at(j).getMisplacedTilesCost() < v.at(min).getMisplacedTilesCost())
            {
                min = j;
            }
        }
        temp = v.at(min);
        v.at(min) = v.at(i);
        v.at(i) = temp;
    }
}

// sort based on manhattan distance heuristic
void selectionSortMD(vector<Matrix> &v)
{
    Matrix temp;
    int min = 0;
    
    for (int i = 0; i < v.size(); ++i)
    {
        min = i;
        for (int j = i+1; j < v.size(); ++j)
        {
            if (v.at(j).getManhattanCost() < v.at(min).getManhattanCost())
            {
                min = j;
            }
        }
        temp = v.at(min);
        v.at(min) = v.at(i);
        v.at(i) = temp;
    }
}

//queueing function for uniform cost search
//does not matter the order it queues into since all the cost is the same
queue<Matrix> uniformCostSearch(queue<Matrix>& n, Matrix& curr, vector<Matrix> &v, int &level)
{
    //first successor
    Matrix up = curr;
    up.moveUp();
    up.setlevel(level);
    if (!stateRepeated(v,up))
    {
        //up.drawMatrix();
        n.push(up);
    }
    
    //second successor
    Matrix down = curr;
    down.moveDown();
    down.setlevel(level);
    if (!stateRepeated(v,down))
    {
        //down.drawMatrix();
        n.push(down);
    }
    
    //third successor
    Matrix left = curr;
    left.moveLeft();
    left.setlevel(level);
    if (!stateRepeated(v,left))
    {
        //left.drawMatrix();
        n.push(left);
    }
    
    //forth successor
    Matrix right = curr;
    right.moveRight();
    right.setlevel(level);
    if (!stateRepeated(v,right))
    {
        //right.drawMatrix();
        n.push(right);
    }
    
    return n;
}

//queueing function for misplaced tiles
//always queue the state with lowest cost in front
queue<Matrix> misplacedTiles(queue<Matrix>& n, Matrix& curr, vector<Matrix> &v, int &level)
{
    vector<Matrix> toSort;
    
    //add nodes in queue into toSort, so it always check the lowest cost node 
    while(!n.empty())
    {
        toSort.push_back(n.front());
        n.pop();
    }
    
    //first successor
    Matrix up = curr;
    up.moveUp();
    up.setlevel(level);

    if (!stateRepeated(v,up))
        toSort.push_back(up);

    //second successors
    Matrix down = curr;
    down.moveDown();
    down.setlevel(level);

    if (!stateRepeated(v,down))
        toSort.push_back(down);


    //third successor
    Matrix left = curr;
    left.moveLeft();
    left.setlevel(level);

    if (!stateRepeated(v,left))
        toSort.push_back(left);

    //forth successor
    Matrix right = curr;
    right.moveRight();
    right.setlevel(level);
    
    if (!stateRepeated(v,right))
        toSort.push_back(right);

    selectionSortMT(toSort);

    for (int i = 0; i < toSort.size(); ++i)
    {
        n.push(toSort.at(i));
    }
    
    return n;
}

//queueing fucntion for manhattan distance
//always queue the state with lowest cost in front
queue<Matrix> manhattanDistance(queue<Matrix>& n, Matrix& curr, vector<Matrix> &v, int &level)
{
    vector<Matrix> toSort;
    
    //add nodes in queue into toSort, so it always check the lowest cost node 
    while(!n.empty())
    {
        toSort.push_back(n.front());
        n.pop();
    }
    
    //first successor
    Matrix up = curr;
    up.moveUp();
    up.setlevel(level);

    if (!stateRepeated(v,up))
        toSort.push_back(up);

    //second successors
    Matrix down = curr;
    down.moveDown();
    down.setlevel(level);

    if (!stateRepeated(v,down))
        toSort.push_back(down);


    //third successor
    Matrix left = curr;
    left.moveLeft();
    left.setlevel(level);

    if (!stateRepeated(v,left))
        toSort.push_back(left);

    //forth successor
    Matrix right = curr;
    right.moveRight();
    right.setlevel(level);
    
    if (!stateRepeated(v,right))
        toSort.push_back(right);

    selectionSortMD(toSort);

    for (int i = 0; i < toSort.size(); ++i)
    {
        n.push(toSort.at(i));
    }
    
    return n;
}

// this is the A* algorithm
void general_search(Matrix init, const int& queueing_function)
{
    //a list that stores nodes that have been generated but not yet visited
    queue<Matrix> node;
    //store nodes that have been visited 
    vector<Matrix> visited;
    // level counter
    int levelCnt = 0;
    int maxNode = node.size();
    node.push(init);
    
    std::cout << "Expanding state" << std::endl;
    while (1)
    {
        if (node.empty())
        {
            std::cout << "Search failure!" << std::endl;
            return;
        }
        
        Matrix current = node.front();
        
        current.drawMatrix();
        std::cout << std::endl;
        
        //if the current state is goal state
        if (current.isEqual(goal))
        {
            std::cout << "Goal!!" << std::endl;
            std::cout << "To solve this problem the search algorithm expanded a total of " << visited.size() << " nodes." << std::endl;
            std::cout << "The maximum number of nodes in the queue at one time was " << maxNode << std::endl;
            std::cout << "The level of goal node was " << current.getlevel() << std::endl;
            return;
        }
        
        visited.push_back(node.front());
        node.pop();
    
        if (queueing_function == 1)
        {
            // when queueing function is called, level is incremented
            levelCnt = current.getlevel() + 1;
            uniformCostSearch(node, current, visited, levelCnt);
        }
        else if (queueing_function == 2)
        {
            levelCnt = current.getlevel() + 1;
            misplacedTiles(node, current, visited, levelCnt);
        }
        else if (queueing_function == 3)
        {
            levelCnt = current.getlevel() + 1;
            manhattanDistance(node, current, visited, levelCnt);
        }

        if (node.size() > maxNode)
            maxNode = node.size();
    }
}


int main()
{
    int chooseMatrix = 0; //type 1 or 2 to choose Matrix
    int userNum = 0;
    int userArr[row][column];
    
    Matrix p = Matrix();
    
    std::cout << "Welcome to Adrians 8-Matrix solver." << std::endl;
    std::cout << "Type \"1\" to use a default Matrix, or \"2\" to enter your own Matrix." << std::endl;
    cin >> chooseMatrix;
    
    //default Matrix
    if (chooseMatrix == 1)
    {
        p.drawMatrix();
    }
    
    //custom Matrix
    else if (chooseMatrix == 2)
    {
        std::cout << "Enter your Matrix, use a zero to represent the blank" << std::endl;
        std::cout << "Enter first row, use space or tabs between numbers" << std::endl;
        for (int i = 0; i < column; ++i)
        {
            cin >> userNum;
            userArr[0][i] = userNum;
        }
        std::cout << "Enter second row, use space or tabs between numbers" << std::endl;
        for (int i = 0; i < column; ++i)
        {
            cin >> userNum;
            userArr[1][i] = userNum;
        }
        std::cout << "Enter third row, use space or tabs between numbers" << std::endl;
        for (int i = 0; i < column; ++i)
        {
            cin >> userNum;
            userArr[2][i] = userNum;
        }
        
        /*
        std::cout << "Enter forth row, use space or tabs between numbers" << std::endl;
        for (int i = 0; i < column; ++i)
        {
            cin >> userNum;
            userArr[3][i] = userNum;
        }
        */
        std::cout << std::endl;
        
        p.changeVal(userArr);
        p.drawMatrix();
    }
    else
        exit(1);
    
    std::cout << "Enter your choice of algorithm" << std::endl;
    std::cout << "\t 1. Uniform Cost Search" << std::endl;
    std::cout << "\t 2. A* with the Misplaced Tile Heuristic" << std::endl;
    std::cout << "\t 3. A* with the Manhattan distance Heuristic" << std::endl;
    cin >> userNum;
    std::cout << std::endl;
    
    
    general_search(p,userNum);
    return 0;
}