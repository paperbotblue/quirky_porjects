#ifndef LINKED_LIST_HPP_
#define LINKED_LIST_HPP_

#include <stdio.h>

template<class t1>
class linked_list
{   
    private:
    struct Node
    {
        t1 data;
        Node* next;
    };
    

    public:
    linked_list();
    Node* head;
    void addNode(t1 data);
    Node* createNode(t1 data);
    void printList();
    bool searchNode(t1 data);
    t1* getNode(int position);
    bool deleteNode(t1 data);
    


};


#endif