#ifndef QUEUE_H
#define QUEUE_H
#include"Node.h"

using namespace std;
template <class T>



class Queue
{
    private:
        Node<T>* head,*tail;
        int length;

    public:
        Queue(){
            head = tail = NULL;
            length = 0;
        }
        /*Queue(const Queue &oldQ){
            head = tail = NULL;
            Node<T> *curr = oldQ.head;
            while(curr){
                enQ(curr->data);
                curr = curr->next;
            }
        }*/
    void enQ(T* _data){
        Node<T>* newNode = new Node<T>(_data);
        if(head == NULL)
            head = tail = newNode;
        else{
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        length++;
    }
    T* deQ(){
        if(head){
        length--;
        Node<T>* temp = head;
        T* _data = temp->data;
        head = head->next;
        if(head == NULL){
            tail ==NULL;
            delete temp;
            return _data;
            }
        head->prev = NULL;
        delete temp;
        return _data;
        }
        return NULL;
    }

    T* peak(){
        if(head)
            return (head->data);
        return NULL;
    }

    Node<T>* peakNode(){
        if(head)
            return (head);
        return NULL;
    }


    void display(){
        cout<<"Queue length: "<<length<<endl;
        Node<T>* curr = head;
        while(curr){
            cout<<"Queue->data "<<*curr->data<<endl;
            curr = curr->next;

        }
    }

    Node<T>* getHead(){
        return head;
    }

    int getLength(){
        return length;
    }
    int getLength2(){
            Node<T>* curr = head;
            int len = 0;
            while(curr){
                len++;
                curr = curr->next;
            }
            return len;
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


};

#endif // QUEUE_H
