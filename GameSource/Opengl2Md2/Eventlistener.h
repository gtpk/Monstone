#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif    
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif    
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#endif

template <typename PARAM>
class EventHandler
{
public:
	EventHandler()
	{}
	~EventHandler()
	{SAFE_DELETE( EventListener);}

	void * CalleeThis;
	void * EventListener;
	void (*fptr)(EventHandler*,PARAM*);

	template <typename Callee>
	bool Registcallback( Callee* callee, void (Callee::*func)(PARAM*))
	{
		EventListener = (void*)malloc( sizeof(func) );
		memcpy(EventListener, &func, sizeof(func));
		CalleeThis = (void*)callee;
		fptr = StateMemberDispatcher<Callee,PARAM>;
	}
	void CallEvent(PARAM* param)
	{
		StateMemberDispatcher(this,param);
	}
};

template <typename Callee,typename PARAM>
inline void StateMemberDispatcher(EventHandler<PARAM>* _eventHandler, PARAM* _param)
{
    typedef void (Callee::*Functor)(PARAM*);    // Helper typedef.
	Callee& callee = *(Callee*)_eventHandler->CalleeThis;
	Functor& f = *(Functor*)_eventHandler->EventListener;
	(callee.*f)(_param);
}