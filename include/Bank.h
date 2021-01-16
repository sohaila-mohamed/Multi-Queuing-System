#ifndef BANK_H
#define BANK_H
#include "climits"
#include"Queue.h"
#include"Client.h"
class Bank
{
    public:
        Bank(int num) {
            cout<<"ctor"<<endl;
            totalWait = 0;
            bankTime = 0;
            while(num--)
                bankTellers.add(new Queue<Client>());
        }
    void processBank(Queue<Client> clients){
                int time = 50;
                int count = 0;
                while(time--){
                    //bankTellers.searchIndex(selectQueue())->data->enQ(clients.deQ());    This line works properly
                    Client * PeakClient=clients.peak();
                    if(PeakClient)
                        if(PeakClient->getArrival() <= bankTime){
                         Client * NextClient;
                         Node<Queue<Client>>* currentQueue;
                          do{
                                int sq=selectQueue();
                                //cout<<"Selected Queue= "<<sq<<endl;
                                currentQueue = bankTellers.searchIndex(selectQueue());
                                if(currentQueue){
                                    Queue<Client> *teller = currentQueue->data;
                                    Client* arrived = clients.deQ();
                                    teller->enQ(arrived);
                                    cout<<"Client "<< arrived->getId()<<" reached bank at teller number num: "<<sq <<endl;
                                    BankCamera();
                                    NextClient=clients.peak();
                                    count++;
                                }
                          }
                          while(NextClient&&PeakClient->getArrival()==NextClient->getArrival());
                        }
                        bankTime++;
                        updateWaitingTime();
                        updateExpectedDuration();
                        queueUpdate();
                }
                stuckInqueuWaitingTime();
                cout<<"average Waiting Time: "<<(double)totalWait /(double)count<<endl;
    }
    void updateWaitingTime(){
        Node<Queue<Client>> *_teller = bankTellers.getHead();
        while(_teller){
            Node<Client> *_client= _teller->data->getHead();
            while(_client){
                if(_client ->data != _teller->data->peak()){
                    int waitingTime = _client->data->getWaitingTime();
                    _client->data->setWaitingTime(++waitingTime);
                    }
                _client = _client ->next;
            }
            _teller = _teller->next;
        }
    }
    // searchIndex performance issue
    void updateExpectedDuration(){
        for (int i=0;i<bankTellers.getLength();i++){

                Client * currentClient=bankTellers.searchIndex(i)->data->peak();
                if(currentClient){
                    int duration=currentClient->getDur();
                    currentClient->setDur(--duration);
                    if(!duration){
                        bankTellers.searchIndex(i)->data->deQ();
                        totalWait+=currentClient->getWaitingTime();
                        cout<<"Client: "<< currentClient->getId()<< " at teller number "<<i<<" left with waiting time: "<<currentClient->getWaitingTime()<<endl;
                        BankCamera();
                        }
                }
        }
    }
    void queueUpdate(){
        for (int i=0;i<bankTellers.getLength();i++){
           Queue<Client> * currentTellerQueue=bankTellers.searchIndex(i)->data;
           int length=currentTellerQueue->getLength();
           Node<Client> * currentClient= currentTellerQueue->peakNode();
            int count = 0;
                while(currentClient){
                        Queue<int> *currentClientInterupts=currentClient->data->getInterrupts();
                    if(currentClientInterupts->peak()&&*currentClientInterupts->peak()==bankTime){
                       cout<<"Interrupt !!!"<<endl;
                        currentClientInterupts->deQ();
                        Client* dequed = currentClient->data;
                        currentTellerQueue->deleteNode(currentClient->data);
                        cout<<"the "<< dequed->getId()<<" Client at teller Num: "<<i<<" interrupted"<<endl;
                        BankCamera();
                        int backIndex = selectQueue();
                        bankTellers.searchIndex(backIndex)->data->enQ(dequed);
                        cout<<"the "<< currentClient->data->getId()<<" Client"<<" got back at teller Num: "<<backIndex<<endl;
                        BankCamera();
                        //delete dequed;
                    }
                    currentClient=currentClient->next;
                    count++;
                }
        }
    }



    void displayAll(){
        int length = bankTellers.getLength();
        cout<<"Length"<<length<<endl;
        while(length--){
            cout<<"Queue num:"<<length<<"  Content"<<endl;
            bankTellers.searchIndex(length)->data->display();

        }
    }

    int maxLength(){
        int Max=0;
         int currentLength;
         for (int i=0;i<bankTellers.getLength();i++){
                currentLength= bankTellers.searchIndex(i)->data->getLength();
                if(currentLength>Max) Max=currentLength;
         }
         return Max;
    }

    void BankCamera(){
        cout<<"BankClock: "<<bankTime<<"---------------------------------------"<<endl;
        int MaxLength=maxLength();
        int tellersLength=bankTellers.getLength();
        for (int i=0;i<tellersLength;i++){
            cout<<" |-| ";
        }
        cout<<endl;

        for(int j=0;j<MaxLength;j++){
                 for (int k=0;k<tellersLength;k++){
                      if( bankTellers.searchIndex(k)->data->searchIndex(j))
                              cout<<"  "<<bankTellers.searchIndex(k)->data->searchIndex(j)->data->getId()<<"  ";
                      else
                        cout<<"     ";
                 }
        cout<<endl;
        }
       cout<<"---------------------------------------------------"<<endl;

    }

    void stuckInqueuWaitingTime(){
        Node<Queue<Client>> *_teller = bankTellers.getHead();
        while(_teller){
            Node<Client> *_client = _teller->data->getHead();
            while(_client){
                totalWait += _client->data->getWaitingTime();
                _client = _client->next;
            }
            _teller = _teller->next;
        }
    }

    private:
        LinkedList<Queue<Client>> bankTellers;
        int bankTime;
        int totalWait;


        int selectQueue(){
            int queueNum;
            int clientsRemaining = INT_MAX;
            int length = bankTellers.getLength();
            for(int i = 0 ;i < length ; i++){
                if(bankTellers.searchIndex(i)->data->getLength() < clientsRemaining){
                    queueNum = i;
                    clientsRemaining = bankTellers.searchIndex(i)->data->getLength();
                }
            }
            return queueNum;
        }
};

#endif // BANK_H



 //Old processBank
              /*  int length = clients.getLength();
                int time = 50;
                while(length--){
                    //if(clients.peak().getArrival() <= bankTime){
                        Client _client = clients.deQ();
                        cout<<"ClientArrivalTime"<<_client.getArrival()<<endl;
                        bankTellers.searchIndex(selectQueue())->data->enQ(&_client);

                         //teller->enQ(&_client);
                         cout<<bankTellers.searchIndex(selectQueue())->data->getHead()<<endl;
                         //cout<<teller->getHead()<<endl;
                        int len1=bankTellers.searchIndex(selectQueue())->data->getLength2();
                        cout<<"len1: "<<len1<<endl;
                        //int len2 =teller->getLength2();
                        //cout<<"Len2: "<<len2<<endl;



                    //}
                    bankTime++;
                }*/
