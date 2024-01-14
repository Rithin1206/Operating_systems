#include "thread.H"

class queueNode{
    public:
        Thread* thread;
        queueNode* next;
        queueNode(Thread* t){
            thread=t;
            next= nullptr;
        }
};
