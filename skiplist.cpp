#include<iostream>
#include<vector>
#include<limits.h>
#include<stdlib.h>
#include<time.h>

/**
 * Node class to hold the datum in a skip list
 */
class Node {
    public:
        Node(int value, Node *next, Node *below);
        int datum;
        Node *next, *below;
};

/**
 * Skip list class
 */
class SkipList {
    public: 
        SkipList();
        void printMe();
        void add(int key);
        void remove(int key);
        int search(int key);
        Node *head, *tail;
    private:
        std::vector<Node *> getPath(int key, int height);
};

/**
 * Constructor for the node class
 */
Node::Node(int value, Node *next, Node *below) {
    this->datum = value;
    this->next = next;
    this->below = below;
}

/**
 * Constructor for the skip list
 */
SkipList::SkipList() {
    Node *newHead = new Node(INT_MAX, NULL, NULL);
    Node *newTail = new Node(INT_MIN, newHead, NULL);
    this->head = newHead;
    this->tail = newTail;
    //Initalize the random seed
    srand(time(0));
};

/**
 * Searches for an item in the skip list by narrowsing down the interval the item must be in. Returns the key that was found, or -1 if it was not found. 
 * key | the key being searhed for in the skip list
 */
int SkipList::search(int key) {
    Node *currentNode = this->tail; 
    while(currentNode->datum != key) {
        if(currentNode->next->datum <= key) currentNode = currentNode->next;
        else currentNode = currentNode->below;
        if(currentNode == NULL) return -1;
    }
    return currentNode->datum;
}

/**
 * Adds a key to the linked list and randomly determines how many levels of nodes will be created for the linked list. 
 * key | the key being added to the linked list
 */
void SkipList::add(int key) {
    //Generate a random number between zero and one
    int random = rand() % 2;
    int totalLevels = 1; 
    //Generate the needed number of levels based on the random int
    while(random == 1) {
        totalLevels++;
        random = rand() % 2;
    }
    std::cout << "The levels for this insert is: " << totalLevels << "\n";
    std::cout.flush();
    std::vector<Node *> insertPath = getPath(key, totalLevels);
    Node *oldTop = NULL;
    for(std::vector<Node *>::iterator it = insertPath.begin(); it != insertPath.end(); it++) {
        //Get the current node that we are adjusting the pointers of
        Node *currentNode = *it;
        //Make the new node point to what the old node used to be pointing to
        Node *insertMe = new Node(key, currentNode->next, NULL);
        //Change what the node we are adjusting is pointing to
        currentNode->next = insertMe;
        //Change the top node of the previous level
        if(oldTop != NULL) oldTop->below = currentNode;
        oldTop = insertMe;
    }
 }

/**
 * Removes a node form the skip list based on the key. 
 * key | the key of the node to be removed
 * If you give this duplicate keys, it will only remove one occurance
 */

void SkipList::remove(int key) {
    //Get the path to the key to delete, -1 means we want the entire path
    std::vector<Node *> deletePath = getPath(key, -1);
    //Iterate through the path and delete as need be
    for(std::vector<Node *>::iterator it = deletePath.begin(); it != deletePath.end(); it++) {
        Node *currentNode = *it;
        if(currentNode->next->datum == key) {
            Node *oldNode = currentNode->next;
            currentNode->next = currentNode->next->next;
            delete oldNode;
        }
        //Check if the pervious modification changed the head and tail and adjust if need be
        if(currentNode->datum == this->tail->datum && currentNode->next->datum == this->head->datum) {
            Node *oldHead = this->head;
            Node *oldTail = this->tail;
            this->head = this->head->below;
            this->tail = this->tail->below;
            delete oldHead;
            delete oldTail;
        }
    }
}

/**
 * Helper function to get the paths for insertion and removal. Returns a vector of the nodes whose pointers need to be adjusted in the insertion or deletion process. 
 * Give -1 if you want the entire path
 * key | the key being inserted
 * height | the height the key should be inserted
 */
std::vector<Node *> SkipList::getPath(int key, int height) {
    Node *currentNode = this->tail;
    std::vector<Node *> nodes;
    //Iterate until we get to the bottom level
    while(currentNode != NULL) {
        //Find the right interval to move down in
        if(currentNode->next->datum < key) currentNode = currentNode->next;
        //Each time we move down a level, add the key we were just at to the list of returning nodes
        else {
            nodes.push_back(currentNode);
            currentNode = currentNode->below;
        }
    }
    //-1 is the key that I want the entire path
    if(height == -1) return nodes;
    //Add a new level to the nodes if it's not tall enough
    while(nodes.size() < height) {
        Node *newHead = new Node(INT_MAX, NULL, this->head);
        Node *newTail = new Node(INT_MIN, newHead, this->tail);
        this->tail = newTail;
        this->head = newHead;
        nodes.insert(nodes.begin(), newTail);
    }
    //Get the sub vector of the number of ones we need for the insertion or deletion based on the height
    std::vector<Node *>::const_iterator first = nodes.begin() + (nodes.size() - height);
    std::vector<Node *>::const_iterator last = nodes.end();
    //Return this subvector
    std::vector<Node *> returnVect(first, last); 
    return returnVect;
}

//Internal helper function to print the list
void SkipList::printMe() {
    Node *tail = this->tail;
    while(tail != NULL) {
        Node *currentNode = tail;
        while(currentNode != NULL) {
            printf("%d ", currentNode->datum);
            currentNode = currentNode->next;
        }
        printf("\n");
        tail = tail->below;
    }
}

int main() {
    SkipList *lawl = new SkipList();
    lawl->add(7);
    lawl->add(5);
    lawl->add(2);
    lawl->add(10);
    lawl->printMe();
    printf("okay, now I am going to delete 7!\n");
    lawl->remove(7);
    printf("search correct? %d\n" , lawl->search(5));
    lawl->printMe();
    return 0;
}
