#ifndef NODE_H
#define NODE_H

template<class T>
class Node
{
    public:
        T* data;
        Node* next,*prev;
        Node(T* _data){
            data = _data;
            prev = next = NULL;
        }



};

#endif // NODE_H
