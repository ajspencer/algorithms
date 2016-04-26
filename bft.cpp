//
// Created by Andrew's computer on 8/27/15.
//

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

//Prototypes
class Node; 
class Queue; 
Node* doBFT(vector< vector<int> > &graph, int startingNode);
void doDFT(Node *n);

/**
 * Yeah in retrospect I probably didn't have to make my own wrapper around a standard class, but it's good practice.
 */

class Node {
    public:
        Node();
        int graphIndex;
        int distance;
        std::vector<Node *> *children;
        Node *parent;
};

Node::Node() {
    Node *parent = NULL;
    int distance = -1;
    vector<Node *> *children(0);
};

class Queue {
    public:
        void enqueue(Node *i) {deque.push_front(i);      }
        bool isEmpty()        {return deque.size() == 0; }
        int  getSize()        {return deque.size();      }
        Node* dequeue() {
            Node *toReturn =  deque.at(deque.size() -1);
            deque.pop_back();
            return toReturn;
        }
    private:
        std::deque<Node *> deque;
};

/*
 * As lone as the queue is not empty:
 * dequeue a vertex
 * For each neighrbor that has not been visited, set the distance, predeccesor and enque it
 */
Node* doBFT(vector< vector<int> > &graph, int startingNode) {
    //Make a list to represent the nodes of the graphs 
    std::vector<Node *> graphNodes(graph.size());
    //Make all of the nodes in the list 0
    for(int i = 0; i < graph.size(); i++) {
        Node *n = new Node();
        //why tf do i have to set these
        n->graphIndex = i; 
        n->distance = -1; 
        vector<Node *> *children = new vector<Node *>;
        n->children = children;  
        graphNodes.at(i) = n;
    }
    //Add the first element to the queue
    Queue *nodeQueue = new Queue();
    graphNodes.at(startingNode)->distance = 0; 
    nodeQueue->enqueue(graphNodes.at(startingNode));

    //Loop through the queue until it is empty (all veticies have been visited)
    while(!nodeQueue->isEmpty()) {
        Node *currentNode = nodeQueue->dequeue();
        vector<int> currentList = graph.at(currentNode->graphIndex);
        Node *parent = graphNodes.at(currentNode->graphIndex);

        for(int i = 0; i < currentList.size(); i++) {
            int currentChildIndex = currentList.at(i);
            Node *currentChild = graphNodes.at(currentChildIndex);
            if(currentChild->distance == -1) {
                currentChild->distance = currentNode->distance + 1;  
                currentChild->parent = currentNode;  
                currentNode->children->push_back(currentChild);
                nodeQueue->enqueue(currentChild);
            }
        }
    }
    return graphNodes.at(startingNode);
}

void doDFT(Node *n) {
    cout << "the node is: " << n->graphIndex << " the distance is: " << n->distance << "\n";
    for(int i = 0; i < n->children->size(); i++) {
        doDFT(n->children->at(i)); 
    }
    //if(N->children.size() == 0)
    //  return;
}

int main() {
    //Make an adjancy list and padd the ending with -1 (since this is never a legal node)
    int placeholderList[8][3] = {
        {1, -1, -1},
        {0, 4, 5},
        {3, 4, 5},
        {2, 6, -1},
        {1, 2, -1},
        {1, 2, 6},
        {3, 5, -1},
        {3, 5 -1},
    };
    std::vector< vector<int> > adjencyList(sizeof(placeholderList)/sizeof(placeholderList[0]), vector<int>(0));

     for(int i = 0; i < sizeof(placeholderList)/sizeof(placeholderList[0]); i++) {
         for(int j = 0; j < sizeof(placeholderList[i])/sizeof(placeholderList[i][0]); j++) {
             if(placeholderList[i][j] != -1) { 
                 adjencyList.at(i).push_back(placeholderList[i][j]);
             }
         }
     }

     for(auto vect : adjencyList) {
         for (std::vector<int>::iterator i = vect.begin(); i != vect.end(); ++i)
             std::cout << *i << ' ';
         cout << "\n";
     }
     Node *n = doBFT(adjencyList, 0);
     doDFT(n);

     return 0;
}
