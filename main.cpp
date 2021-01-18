#include <iostream>
#include"Bank.h"
#include"LinkedList.h"
#include"Client.h"
#include"Queue.h"

using namespace std;
ostream & operator << (ostream &out,  Client &c)
{
    out<<"Arrival: ";
    out << c.getArrival();
    out<<' ';
    out<<"Expected duration: ";
    out << c.getDur();
    out<<" ";
    out<<"Waiting Time: ";
    out<<c.getWaitingTime();

    out << endl;

    return out;
}

 bool validateInputs(int val){
         bool validNoT = true;
        if(val<=0){
           validNoT = false;
        }
        return validNoT;

    }

int main()
{

    /*Queue<int> obj;
    int x = 5,y = 6, z = 7,a = 100,b = 8,c = 10;
    obj.enQ(&x);obj.enQ(&y);obj.enQ(&z);obj.enQ(&a);obj.enQ(&b);obj.enQ(&c);
    cout<<"deque : "<<obj.deQ()<<endl;
    cout<<"deque: "<<obj.deQ()<<endl;
    cout<<"deque: "<<obj.deQ()<<endl;
    cout<<"deque: "<<obj.deQ()<<endl;
    cout<<"deque: "<<obj.deQ()<<endl;
    cout<<"deque: "<<obj.deQ()<<endl;
    int de = obj.deQ();
    de?cout<<"deque: "<<de<<endl:cout<<"queue is empty"<<endl;
    cout<<"peak: "<<obj.peak()<<endl;
    obj.display();*/
     int NoT=0;
    int BankCloseTime=0;

    do{

        cout<<"Enter number of Tellers *Note(Should be positive): ";
        cin>>NoT;
    }
    while(!validateInputs(NoT));
    do{
        cout<<"Enter Bank Closing Time *Note(Should be positive): ";
        cin>>BankCloseTime;
    }
     while(!validateInputs(BankCloseTime));



    Queue<Client> clients;
    int addFlag = 0;
    cout<<"enter 1 to add new client 0 submit clients"<<endl;
    cin>>addFlag;
    while(addFlag){
        int arrive, dur;
        bool nonNegArr = false,nonNegDur = false;

        while(!nonNegArr){
            nonNegArr = true;
            cout<<"enter arrival time "<<endl;
            cin>>arrive;
            if(arrive<0){
                nonNegArr = false;
                cout<<"arrive should be positive value"<<endl;
            }
        }
        while(!nonNegDur){
            nonNegDur = true;
            cout<<"enter expected duration"<<endl;
            cin>>dur;
            if(dur<=0){
                nonNegDur = false;
                cout<<"Duration should be positive"<<endl;
            }
        }
        int interruptsFlag=0;
        cout<<"enter 1 if he has interrupts 0 if he hasn't"<<endl;
        cin>>interruptsFlag;
        Queue<int> *interrupts=new Queue<int>();
        while(interruptsFlag){
            //memory free
            int* interrupt=new int();
            bool properInterrupt = false;
            while(!properInterrupt){
                cout<<"enter interrupt time: ";
                cin>>*interrupt;
                properInterrupt = true;
                if(*interrupt < arrive){
                    properInterrupt = false;
                    cout<<"enterrupts can't happen before client arrives"<<endl;
                }
            }
            interrupts->enQ(interrupt);
            cout<<"enter 1 to add one more interrupt 0 to procceed"<<endl;
            cin>>interruptsFlag;
        }
        interrupts->bubbleSort();
        clients.enQ(new Client(arrive,dur,interrupts));
        cout<<"1 to add new client 0 submit clients"<<endl;
        cin>>addFlag;
    }

   clients.display();

    Client::sortClients(&clients);
   clients.display();
    //Client deleted = clients.deQ();
    //cout<<deleted<<endl;


    Bank _bank(NoT);
    _bank.processBank(clients,BankCloseTime);
    _bank.displayAll();

    return 0;
}
