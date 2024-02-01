#include <stdio.h>
#include "/sharedDrive/Project/Snakev2/inc/linked_list.hpp"

struct Coord
{
    int x,y;

    Coord(int x,int y)
    {
        this->x = x;
        this->y = y;
    }
    Coord()
    {}


bool operator==(Coord c2)
{
    if(this->x == c2.x && this->y == c2.y)
    {
        return true;
    }
    return false;
}
void operator=(Coord c2)
{
    this->x = c2.x;
    this->y = c2.y;
}

    void print()
    {
        printf("(%d ,%d)",this->x,this->y);
    }


};




int main()
{
linked_list<Coord> CharacterPosition;
int input;
int a = 0,b = 0;
bool run = true;
while (run == true)
{
    printf("You have the following options:\n");
    printf("\t1. Enter current pos\n");
    printf("\t2. print all previous positions\n");
    printf("\t3. print index\n");
    printf("\t4. quit\n");
    scanf("%d",&input);
    if(input == 4)
    {
        run = false;
    }
    else if(input == 3)
    {

    }
    else if(input == 2)
    {
        CharacterPosition.printList();
    }
    else
    {
        scanf("%d %d",&a,&b);
        Coord p(a,b);
        CharacterPosition.addNode(p);
    }
}


}

template<class t1>
linked_list<t1>::linked_list()
{
    head = NULL;
}

template<class t1>
void linked_list<t1>::addNode(t1 data)
{
    if(head == NULL)
    {
        head = createNode(data);
    }
    else
    {
        Node* temp = head;
        head = createNode(data);
        head->next = temp;
    }
}

template<class t1>
linked_list<t1>::Node* linked_list<t1>::createNode(t1 data)
{
    Node* temp = new Node;
    temp->data = data;
    temp->next = NULL;
    return temp;
}

template<class t1>
void linked_list<t1>::printList()
{
    Node* temp = head;
    while(temp != NULL)
    {
        temp->data.print();
        temp = temp->next;
    }
}


