#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP
#include <cstdlib>
#include <stdio.h>

template<class t1>
class Node
  {
    public:
    t1 data;
    Node* next;
  };

template<class t1>
class linkedList
  {
    public:
    Node<t1>* head;
    int size;
    void addNode(t1 data);
    Node<t1>* createNode(t1 data);
    void deleteNode(t1 data);
    void printList();
    Node<t1>* getNode(int position);
    void pushBack(t1 data);
    linkedList();
  };

template<class t1>
linkedList<t1>::linkedList()
{
  this->head = NULL;
}

template<class t1>
void linkedList<t1>::addNode(t1 data)
{
  if(head == NULL)
  {
    head = createNode(data);
    size++;
  }
  else 
  {
    Node<t1>* temp = head;
    head = createNode(data);
    head->next = temp;    
    size++;
  }
}

template<class t1>
Node<t1>* linkedList<t1>::createNode(t1 data)
{
  Node<t1>* temp = new Node<t1>;
  temp->data = data;
  temp->next = NULL;
  return temp;
}
 
template<class t1>
void linkedList<t1>::deleteNode(t1 data)
{
  if(head != NULL && head->data == data)
  {
    free(head);
    head = NULL;
    this->size--;
    return;
  } 
  Node<t1>* temp = head;
  Node<t1>* prev = NULL;
  while(temp != NULL && temp->data != data)
  {
    prev = temp;
    temp = temp->next;
  }
  if(temp != NULL)
  {
    prev->next = temp->next;
    free(temp);
    temp = NULL;
    this->size--;
  }
  else 
  { 
    printf("deleteNode error unable to find the given Node ");
    data.print();
  }

}

template<class t1>
void linkedList<t1>::printList()
{
  Node<t1>* temp = head;
  while (temp != NULL) 
  {
    temp->data.print();
    temp = temp->next;
  }
}

template<class t1>
void linkedList<t1>::pushBack(t1 data)
{
  if(head == NULL)
  {
    printf("Error attempting to pushBack() an empty list");
    return;
  }
  addNode(data);
  size--;
  if(head->next == NULL)
  {
    return;
  }
  Node<t1>* temp = head;
  Node<t1>* prev;

  while(temp->next != NULL)
  {
    prev = temp;
    temp = temp->next;
  }
  prev->next = NULL;
  free(temp);
  temp = NULL;

}

template<class t1>
Node<t1>* linkedList<t1>::getNode(int position)
{
  Node<t1>* temp = head;
  for(int i = 0 ; i < position && temp != NULL; i ++)
  {
    temp = temp->next;
  }
  if(temp != NULL)
  {
    return temp;
  }
  return NULL;
};

#endif
