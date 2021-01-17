#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"

using namespace std;


template <class T>
class LinkedList
{
    Node<T> *head,*tail;
    public:
        LinkedList(const LinkedList<T> &oldList){
            Node<T> *curr = oldList.head;
            head = tail = NULL;
            while(curr){
                add(curr->data);
                curr = curr->next;
            }
        }
        LinkedList(){
            head = tail = NULL;
        }
        ~LinkedList(){

             Node<T>* temp=head;
             while(temp){
                    cout<<"Linked List Destructor"<<endl;
                    deleteNode(temp->data);
                    temp=head;
             }
        }
    void add(T *_data){
        Node<T> *newNode = new Node<T>(_data);
        if(head == NULL){
            head = tail = newNode;
        }
        else{
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    void deleteNode(T *_data){
        Node<T> *pDelete = searchNode(_data);
        if(!pDelete)
            return;
        if(pDelete == head){
            if(pDelete == tail)
                head = tail = NULL;
        else{
            head = head->next;
            head->prev = NULL;
            }
        }
        else if(pDelete == tail){
            tail = tail->prev;
            tail->next = NULL;
        }
        else{
            pDelete->prev->next = pDelete->next;
            pDelete->next->prev = pDelete->prev;
        }
        delete pDelete;
    }
    void display(){
        Node<T>* current = head;
        while(current){
            cout<<*(current->data)<<endl;
            current = current->next;
        }
    }
    void InsertAfter(T *afterData, T *newData){
        Node<T>*newNode = new Node<T>(newData);
        Node<T>* current = head;
        while(current){
            if(current->data == afterData){
                newNode->next = current->next;
                newNode->prev = current;
                current->next->prev = newNode;
                current->next = newNode;
            }
            current = current->next;
        }

    }
     void DeleteByIndex(int index)
    {
        if(head){
            Node<T>* pDelete = searchIndex(index);
            deleteNode(pDelete->data);
        }
    }

    void Reverse()
    {

        Node<T>* tailPrev= head->next;
        Node<T>* temp = head;
        head = tail;
        head->next = tail->prev;
        head->prev = NULL;
        tail = temp;
        tail->next = NULL;
        tail->prev = tailPrev;
        Node<T>* current = head->next;
        while (current!=tail){
                Node<T>* tempNode = current->prev;
                current->prev = current->next;
                current->next = tempNode;

                current = current->next;
        }

    }
    void bubbleSort(){
        bool sorted = 0;
        Node<T>* curr = head;
        while(curr&&!sorted){
           sorted = 1;
           Node<T>* curr2 = curr->next;
           while(curr2){
                if(*curr->data > *curr2->data){

                    swap(curr->data,curr2->data);
                    sorted = 0;
                }

            curr2 = curr2->next;
           }
           curr = curr -> next;
        }
    }

    void selectionSort(){
        if (head&&tail){
            Node<T>*curr = head;
            Node<T>* minNode;
            while(curr){
                minNode = curr;
                Node<T>* curr2 = curr->next;
                while(curr2){
                    if(*minNode->data>*curr2->data){
                        minNode = curr2;
                    }
                    curr2 = curr2->next;
                }
                swap(curr->data,minNode->data);
                curr = curr->next;
            }
        }
    }

    void insertionSort(){
        if(head&&tail){
            Node<T>*curr = head->next;
            Node<T>* index;
            while(curr){
                T* key = curr->data;
                index = curr->prev;
                while(index && *index->data > *key){
                    index->next->data = index->data;
                    index = index->prev;
                }
                if(index)
                    index->next->data = key;
                else
                    head->data = key;
                curr = curr->next;
            }

        }
    }

    int binarySearch(T _data){
        bool dir = 1;
        int len = getLength();
        int start = 0, end = len-1, mid =end/2;
        Node<T>* curr = head;
        while(start<=end){
            int def1 = mid- start;
            int def2 = end - mid;
            while(dir&&def1--)
                curr = curr->next;
            while(!dir&&def2--)
                curr = curr->prev;
            if(*curr->data == _data ){
                return mid;
            }
            else if(*curr->data > _data){
                curr = curr->prev;
                end = mid-1;
                dir = 0;
                }
            else if(*curr->data<_data){
                curr = curr->next;
                start = mid+1;
                dir = 1;
            }
            mid = (start + end)/2;
        }
        return -1;

    }

    Node<T>* searchIndex(int index){
        if(index>=0&&index<getLength()){
            Node<T> *current = head;
            while(index--){
                current = current->next;
            }
            return current;

        }
        return NULL;

        }
    int getLength(){
            Node<T>* curr = head;
            int len = 0;
            while(curr){
                len++;
                curr = curr->next;
            }
            return len;
        }

    Node<T>* getHead(){
            return head;
        }
    private:
       /* void swapWithHead(){

        }*/


        Node<T>* searchNode(T *_data){
            Node<T> *current = head;
            while(current){
                if(current->data == _data)
                    return current;
                current = current->next;
            }
            return NULL;
        }



};

#endif // LINKEDLIST_H
