#include "thread.H"
#include "queueNode.H"
#include "assert.H"
#include "console.H"

class queue{
    private:
        queueNode* front;
        queueNode* back;
    public:
        queue(){
            front=nullptr;
            back= nullptr;
        }
        void insert(Thread* t){
            
            queueNode* temp= new queueNode(t);
            if(front==nullptr){
                Console :: puts("Front is now NULl and we are trying to insert \n ");
                front = back = temp;
                printSize();
                return;
            }
            back->next= temp;
            back=back->next;
            return;
        }
        
        Thread* getFront(){
            return front->thread;
        }
	
	void printSize(){
            queueNode* temp= front;
            int x=0;
            while(temp){
                x++;
                temp=temp->next;
            }
            Console :: puts("Queue size is ");
            Console :: puti(x);
            Console :: puts("\n");
        }

        void pop(){
            if(front == nullptr) return;
            if(front->next == nullptr) front = back = nullptr;
            front = front->next;
            return;
        }

        void remove(Thread* _thread){
            queueNode* temp = front;
            queueNode* prev = front;
            if(temp->thread == _thread){
                temp = temp->next;
                return;
            }
            
            while(temp!=nullptr && temp->thread != _thread){
                prev = temp;
                temp = temp->next;
            }
            if(temp == nullptr){
                return;
            }
            prev->next = temp->next;
            return;
        }

};
