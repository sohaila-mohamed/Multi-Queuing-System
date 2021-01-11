#ifndef CLIENT_
#define CLIENT_
#include"Node.h"
#include"Queue.h"
#include"LinkedList.h"
class Client
{
    public:
        Client(int _arrival,int _expected,Queue<int> _interrupts) {
            arrivalTime = _arrival;
            expectedDuration = _expected;
            interrupts = _interrupts;
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
        void setInterrupts(Queue<int> _interrupts){
            interrupts = _interrupts;
        }

        Queue<int>* getInterrupts(){
            return &interrupts;
        }

        void displayClient(){
            cout<<"arrival Time "<<arrivalTime;
             cout<<", Expected Duration "<<expectedDuration<<endl;
             interrupts.display();

        }

        static void sortClients(Queue<Client> clients){
            Node<Client> *curr = clients.getHead();
            bool sorted = 0;
            while(curr&&!sorted){
                sorted = 1;
                Node<Client> *curr2 = curr->next;
                while(curr2){
                    if(curr2->data->getArrival() < curr->data->getArrival()){
                        swap(curr2->data,curr->data);
                        sorted = 0;
                        }
                    curr2 = curr2->next;
                }
                curr = curr->next;
            }
        }

    protected:

    private:
        int arrivalTime;
        int expectedDuration;
        Queue<int> interrupts;
};

#endif // CLIENT_
