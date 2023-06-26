
#ifndef SORTEDLINKEDLIST_H
#define SORTEDLINKEDLIST_H

#include <vector>

#include <iostream>
using namespace std;

class Node {
public:
    int id;
    float rate;
    Node* next;

    Node();
    Node(int, float);
};


class sortedLinkeList {

public:

    Node* head = NULL;
    Node* tail = NULL;
    int count = 0;


    /*
    Function name: insert

    Description:
        Adds a new news and sortes them according to rating using a sorted linked list.

    Parameters:

        head (Pointer News)-pass by refrence.
        item (News)-Node

    Returns:
        void
  */
    void insert(Node* item);


};

#endif // SORTEDLINKEDLIST_H
