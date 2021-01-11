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

    out << endl;

    return out;
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
    Queue<Client> clients;
    int addFlag = 0;
    cout<<"1 to add new client 0 submit clients"<<endl;
    cin>>addFlag;
    while(addFlag){
        int arrive, dur;
        cout<<"enter arrival time "<<endl;
        cin>>arrive;
        cout<<"enter expected duration"<<endl;
        cin>>dur;

        int interruptsFlag=0;
        cout<<"1 if he has interrupts 0 if he hasn't"<<endl;
        cin>>interruptsFlag;
        Queue<int> *interrupts=new Queue<int>();
        while(interruptsFlag){
            //memory free
            int* interrupt=new int();
            cin>>*interrupt;
            interrupts->enQ(interrupt);
            cout<<"1 to add one more interrupt 0 to procceed"<<endl;
            cin>>interruptsFlag;
        }
        interrupts->bubbleSort();
        clients.enQ(new Client(arrive,dur,interrupts));
        cout<<"1 to add new client 0 submit clients"<<endl;
        cin>>addFlag;
    }

    clients.display();

    Client::sortClients(clients);
    clients.display();
    //Client deleted = clients.deQ();
    //cout<<deleted<<endl;
//   LinkedList<int>* ll=new LinkedList<int>();
//   int x=1;
//   ll->add(&x);
//   x++;
//   ll->add(&x);
//   x++;
//   ll->add(&x);
//   x++;
//   ll->add(&x);
//   x++;
//   ll->add(&x);
//   x++;
//   ll->add(&x);
//   x++;
//   ll->add(&x);
//   cout<<"ll.length"<<ll->getLength()<<endl;

    Bank _bank(3);
   _bank.processBank(clients);
   _bank.displayAll();

    return 0;
}
