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
            bankTime = 0;
            while(num--)
                bankTellers.add(new Queue<Client>());
        }
    void processBank(Queue<Client> clients){
              //new processBank
                //int length = clients.getLength();
                int time = 50;
                //int closingTime = clients.getTail()->data->getArrival()+clients.getTail()->data->getDur();
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
                                }

                          }
                          while(NextClient&&PeakClient->getArrival()==NextClient->getArrival());
                        }
                        bankTime++;
                        updateExpectedDuration();
                        queueUpdate();

                        //BankCamera();

                }

    }

    void updateExpectedDuration(){
        for (int i=0;i<bankTellers.getLength();i++){

                Client * currentClient=bankTellers.searchIndex(i)->data->peak();

                if(currentClient){

                    int duration=currentClient->getDur();
                    currentClient->setDur(--duration);

                    if(!duration) {
                        //currentClient->displayClient();
                       // cout<<"abo 7amada left  "<<"Bank Clock is: "<<bankTime<<endl;

                        bankTellers.searchIndex(i)->data->deQ();
                        cout<<"Client"<< currentClient->getId()<< " at teller number "<<i<<" left"<<endl;
                        BankCamera();
                        //displayAll();
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
                        cout<<"the "<< currentClient->data->getId()<<" Client at teller Num: "<<i<<" interrupted"<<endl;
                        BankCamera();
                        int backIndex = selectQueue();
                        bankTellers.searchIndex(backIndex)->data->enQ(dequed);
                        cout<<"the "<< currentClient->data->getId()<<" Client"<<" got back at teller Num: "<<backIndex<<endl;
                        BankCamera();
                    }
                    currentClient=currentClient->next;
                    count++;
                }
        }
    }
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
        cout<<bankTime<<"---------------------------------------"<<endl;
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
