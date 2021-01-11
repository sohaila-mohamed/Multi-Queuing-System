#ifndef BANK_H
#define BANK_H
#include "climits"
#include"Queue.h"
#include"Client.h"
class Bank
{
    public:
        Bank(int num) {
            bankTime = 10;
            while(num--)
                bankTellers.add(new Queue<Client>());
        }
    void processBank(Queue<Client> clients){
              //new processBank
                //int length = clients.getLength();
                int time = 50;
                while(time--){

                    //bankTellers.searchIndex(selectQueue())->data->enQ(clients.deQ());    This line works properly
                    Client * PeakClient=clients.peak();
                    if(PeakClient)
                        if(PeakClient->getArrival() <= bankTime){
                         Client * NextClient;
                          do{
                                Queue<Client> *teller = bankTellers.searchIndex(selectQueue())->data;
                                teller->enQ(clients.deQ());
                                NextClient=clients.peak();
                          }
                          while(NextClient&&PeakClient->getArrival()==NextClient->getArrival());
                        }
                        queueUpdate();
                        updateExpectedDuration();
                        bankTime++;
                }



    }

    void updateExpectedDuration(){
        for (int i=0;i<bankTellers.getLength();i++){

                Client * currentClient=bankTellers.searchIndex(i)->data->peak();

                if(currentClient){

                        int duration=currentClient->getDur();
                        currentClient->setDur(--duration);

                        if(!duration) {
                            currentClient->displayClient();
                            bankTellers.searchIndex(i)->data->deQ();}
                }


        }


    }
    void queueUpdate(){
        for (int i=0;i<bankTellers.getLength();i++){
           Queue<Client> * currentTellerQueue=bankTellers.searchIndex(i)->data;
           int length=currentTellerQueue->getLength();
           Node<Client> * currentClient= currentTellerQueue->peakNode();

           if(currentClient){

                while(currentClient){
                        Queue<int> *currentClientInterupts=currentClient->data->getInterrupts();
                    if(*currentClientInterupts->peak()==bankTime){
                        cout<<"Before Interrputs"<<endl;
                        displayAll();
                        currentTellerQueue->deQ();
                        currentClientInterupts->deQ();
                        bankTellers.searchIndex(selectQueue())->data->enQ(currentClient->data);
                        cout<<"After Interrputs"<<endl;
                        displayAll();
                    }

                    currentClient=currentClient->next;
                }
        }
        }


    }



    int selectQueue(){
        int queueNum;
        int clientsRemaining = INT_MAX;
        int length = bankTellers.getLength();
        while(length--){
            if(bankTellers.searchIndex(length)->data->getLength() < clientsRemaining){
                queueNum = length;
                clientsRemaining = bankTellers.searchIndex(length)->data->getLength();
            }
        }
        return queueNum;
    }


    void displayAll(){
        int length = bankTellers.getLength();
        cout<<length<<endl;
        while(length--){
            cout<<"Queue num:"<<length<<"  Content"<<endl;
            bankTellers.searchIndex(length)->data->display();

        }
    }


    private:
        LinkedList<Queue<Client>> bankTellers;
        int bankTime;
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
