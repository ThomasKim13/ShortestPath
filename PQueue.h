#ifndef P_QUEUE_H
#define P_QUEUE_H
#include "DblList.h"
#include "position.h"

template <typename T>
class PQueue: private DblList<T>{ //inherit from the DL List but don't make an is-a
//public methods
public:
    PQueue(bool isMin); //min queue or not
    virtual ~PQueue();
    void add(T data);
    T remove();
    int size();
    bool isEmpty();
    T peek();
    T removeTop();
private:
    //private variable
    bool isMinQ;
};
//checks if the queue is empty
template <typename T>
bool PQueue<T>::isEmpty(){
    return DblList<T>::isEmpty();
}

//returns the size of the queue
template <typename T>
int PQueue<T>::size(){
    return DblList<T>::size();
}
//sets the minimum
template <typename T>
PQueue<T>::PQueue(bool isMin){
    isMinQ = isMin;
}
//default deconstructor
template <typename T>
PQueue<T>::~PQueue(){
}
//removes from the top
template <typename T>
T PQueue<T>::remove(){
    if(isMinQ){
        return DblList<T>::removeFront(); //smallest always at front
    } else{
        return DblList<T>::removeBack(); //largest always at back
    }
}
//adds to the queue
template <typename T>
void PQueue<T>::add(T d){
    if(isEmpty()){ //well, that's easy. Just add.
        DblList<T>::addFront(d);
        return;
    }
    ListNode<T>* newNode = new ListNode<T>(d);
    int currIdx = 0;
    ListNode<T>* currNode = DblList<T>::m_front;
    //this while loop here is modded to compare the weights instead of just the data
    while(currNode != NULL && currNode->m_data->getWeight() < d->getWeight()){ //from front, find the right

        ++currIdx;
        currNode = currNode->m_next;
    }
    DblList<T>::add(currIdx,d); //this is a hack because it starts over looking from

}
template <typename T>
T PQueue<T>::removeTop() {
    return DblList<T>::removeFront();
}

#endif