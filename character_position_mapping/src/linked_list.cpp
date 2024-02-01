#include "linked_list.hpp"

template<class t1>
bool linked_list<t1>::searchNode(t1 data)
{
    Node* temp = head;
    while(temp != NULL && temp->data != data)
    {
        temp = temp->next;
    }
    if(temp == NULL)
    {
        printf("Node Not Found\n");
        return false;
    }
    else 
    {
        printf("Node found\n");
        return true;
    }
}

template<class t1>
linked_list<t1>::t1* linked_list<t1>::getNode(int position)
{
    Node* temp = head;
    int i;
    for(i = 0 ; i < position  && temp != NULL ; i++)
    {
        temp = temp->next;
    }
    if(temp == NULL)
    {
        return NULL;
    }
    return temp;
}

template<class t1>
bool linked_list<t1>::deleteNode(t1 data)
{
    Node* temp = head;
    Node* prev = NULL;
    while(temp != NULL && temp->data != data)
    {
        prev = temp;
        temp = temp->next;
    }

    if(temp == NULL)
    {
        return false;
    }

    prev->next = temp->next;
    free(temp);
    temp = NULL;
}
