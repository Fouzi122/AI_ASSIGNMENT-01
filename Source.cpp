#include<iostream>
#include <string>
#include<Queue>
#include <stack>

using namespace std;

struct Node {
    int state;
    int action;
    int cost;
    Node* parent;


    Node(int state, int action, int cost, Node* parent) {
        this->state = state;
        this->action = action;
        this->cost = cost + parent->cost;
        this->parent = parent;
    }

    Node() {
        state = -1;
        action = -1;
        cost = 0;
        parent = nullptr;
    }
};

int m = 8, n = 3, t = 2;
string* arrStates;
string* arrActions;
int** TransitionMatrix;
int** arrTest;

//HardCodedVAlues
//mSizeArray
string arrStates1[8] = { "(AgentInRoom1, Room1Dusty, Roam2Dusty)","(AgentInRoom1, Room1Dusty, Roam2Clean)","(AgentInRoom1, Room1Clean, Roam2Dusty)","(AgentInRoom1, Room1Clean, Roam2Clean)","(AgentInRoom2, Room1Dusty,Roam2Dusty)","(AgentInRoom2, Room1Dusty, Roam2Clean)","(AgentInRoom2, Room1Clean, Roam2Dusty)","(AgentInRoom2, Room1Clean, Roam2Clean)" };
//nSizeArray
string arrActions1[3] = { "Clean","Move To Room1","Move To Room2" };
//MxNSizedMatrix
int TransitionMatrix1[8][3] = { {2,0,4},{3,1,5},{2,2,6},{3,3,7},{5,0,4},{5,1,5},{7,2,6},{7,3,7} };
//Tx2SizedMatrix(for test cases)
int arrTest1[2][2] = { {2,3},{0,7} };


void inputHeader() {
    cout << "Enter Number of States : ";
    cin >> m;
    cout << "Enter Number of Actions : ";
    cin >> n;
    cout << "Enter Number of Test Cases : ";
    cin >> t;
}

void inputStates() {
    for (int i = 0; i < m; i++) {
        cout << "Enter State " << i + 1 << ": ";
        cin >> arrStates[i];
    }
}

void inputActions() {
    for (int i = 0; i < n; i++) {
        cout << "Enter Action" << i + 1 << " : ";
        cin >> arrActions[i];
    }

}

void inputTestCases() {
    int lastindex;
    lastindex = m - 1;
    arrTest = new int* [t];
    for (int i = 0; i < t; i++) {
        arrTest[i] = new int[2];
    }
    for (int i = 0; i < t; i++) {

        cout << "------Enter TestCase_" << i+1 << "----------" << endl;
        cout<<"Enter InitialState (from 0 to " << lastindex << ") : ";
        cin >> arrTest[i][0];
        cout<<"Enter FinalState(from 0 to " <<lastindex << ") : ";
        cin >> arrTest[i][1];
    }
}
void inputTransitionMatrix() {
    int lastindex;
    lastindex = m - 1;
    TransitionMatrix = new int* [m];
    for (int i = 0; i < m; i++) {
        arrTest[i] = new int[n];
    }
    cout << "Enter Transition Matrix" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> TransitionMatrix[i][j];
        }
    }
}
bool goalTest(Node *start, int goal) {
    if (start->state == goal)
        return true;
    else
        return false;

}
bool child_goal = false;
bool parent_goal = false;
//function breathFirstSearch
Node *breathFirstSeach(int start, int goal) {
  
    Node* s=new Node;
    s->state = start;
    queue<Node*> frontial;
    //cout << s->state;
    Node* result = nullptr;
    Node* child = nullptr;
    bool* ArrCheck = new bool[m];
    for (int i = 0; i < m; i++) {
        ArrCheck[i] = 0;
    }

    frontial.push(s);
    ArrCheck[s->state] = 1;
    while (!frontial.empty()) {
        s = frontial.front();
        frontial.pop();
        parent_goal= goalTest(s, goal);
        if (parent_goal) {
            //parent is goal
            result = s;
            break;
        }
        else {
            for (int i = 0; i < n; i++) {
                if (ArrCheck[TransitionMatrix1[s->state][i]] == 0) {
                    child = new Node;
                    ArrCheck[s->state] = 1;
                    child->state = TransitionMatrix1[s->state][i];
                    child->action = i;
                    child->parent = s;
                    child->cost = child->parent->cost + 1;
                    child_goal= goalTest(child, goal);
                    if (child_goal) {
                        result = child;
                        break;
                    }
                    frontial.push(child);
                }
            }
        }
        if (child_goal)
            break;
    }
   
    return result;
}
void findPath(Node* result) {
    stack<int> store;

    if (child_goal) {
        while (result->parent != nullptr)
        {
            store.push(result->action);
            result = result->parent;
        }
        //store.pop();
        string final;
        while (!store.empty())
        {
            final += arrActions1[store.top()];
            final += "->";
            store.pop();
        }
        final = final.substr(0, final.length() - 2);
        cout << final << endl;
        child_goal = false;
    }
    else if (parent_goal) {
        cout << "Parent is goal\n";
        parent_goal = false;
    }
    else
        cout << "NO SOLUTION EXISTS\n";

   
   

}



int main() {
    //sample Test Case
    Node* result = new Node;
    for (int i = 0; i < t; i++) {
        int start = arrTest1[i][0];
        int goal = arrTest1[i][1];
        cout << "------TestCase_" << i + 1 << "----------" << endl;
        cout << "Initial State : " << arrStates1[start] << endl;
        cout << "Final   State : " << arrStates1[goal] << endl;
        cout << "-----PATH-----: ";
        result=breathFirstSeach(start, goal);
        findPath(result);
    }
    
    inputTestCases();
    for (int i = 0; i < t; i++) {
        int start = arrTest[i][0];
        int goal = arrTest[i][1];
        cout << "------TestCase_" << i + 1 << "----------" << endl;
        cout << "Initial State : " << arrStates1[start] << endl;
        cout << "Final   State : " << arrStates1[goal] << endl;
        cout << "-----PATH-----: ";
        result = breathFirstSeach(start, goal);
        findPath(result);
    }
	system("pause");
	return 0;
}