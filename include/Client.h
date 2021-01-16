#ifndef CLIENT_
#define CLIENT_
#include"Node.h"
#include"Queue.h"
#include"LinkedList.h"
class Client
{

    public:
        Client(int _arrival,int _expected,Queue<int> * _interrupts) {
            arrivalTime = _arrival;
            expectedDuration = _expected;
            interrupts = _interrupts;
            id = _id;
            _id+=1;
            waitingTime = 0;
        }
        void setArrival(int _arr){
            arrivalTime = _arr;
        }
        int getArrival(){
            return arrivalTime;
        }
        void setDur(int _dur){
            expectedDuration = _dur;
        }
        int getDur(){
            return expectedDuration;
        }
        void setInterrupts(Queue<int> *_interrupts){
            interrupts = _interrupts;
        }

        Queue<int>* getInterrupts(){
            return interrupts;
        }

        void displayClient(){
            cout<<"arrival Time "<<arrivalTime;
             cout<<", Expected Duration "<<expectedDuration<<endl;
             interrupts->display();

        }

        static void sortClients(Queue<Client> *clients){
            Node<Client> *curr = clients->getHead();
            bool sorted = 0;
            while(curr&&!sorted){
                sorted = 1;
                Node<Client> *curr2 = curr->next;
                while(curr2){
                    if(curr2->data->getArrival() <= curr->data->getArrival()){
                        Client* temp = curr2->data;
                        curr2->data = curr->data;
                        curr->data = temp;
                        sorted = 0;
                        }
                    curr2 = curr2->next;
                }
                curr = curr->next;
            }
        }

    char getId(){
        return id;
    }
    void setWaitingTime(int _waitingTime){
        waitingTime = _waitingTime;
    }
    int getWaitingTime(){
        return waitingTime;
    }

    private:
        int arrivalTime;
        int expectedDuration;
        int waitingTime;
        char id;
        Queue<int>* interrupts;
        static char _id;
};
char Client::_id = 65;
#endif // CLIENT_
