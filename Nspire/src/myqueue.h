template<class T>
struct QueueNode
{	
	T data;
	QueueNode* next;
};
	
	
template<class T>
class queue
{
	public:
		queue()
		{
			phead=ptail=0;	
		}
		
		~queue()
		{
			while(empty()==false)
			{
				pop();
			}
		}
		
		T front()
		{
			return phead->data;
		}
		
		void push(const T &data)
		{
			if(ptail==0)
			{
				phead=ptail=new QueueNode<T>;
				ptail->data=data;
				ptail->next=0;
			} else 
			{
				QueueNode<T> *pt;
				pt=new QueueNode<T>;
				pt->data=data;
				pt->next=0;
				ptail->next=pt;
				ptail=pt;
			}
		}
		
		void pop()
		{
			if(phead==0 && ptail==0)
			{
				return;
			}
				
			
			if(phead==ptail)
			{
				delete phead;
				phead=ptail=0;
				return;
			}
			
			QueueNode<T> *pt=phead->next;
			delete phead;
			phead=pt;
		}
		
		bool empty()
		{
			return (phead==0&&ptail==0)?true:false;
		}
		
	private:
		QueueNode<T> *phead;
		QueueNode<T> *ptail;
		
};
