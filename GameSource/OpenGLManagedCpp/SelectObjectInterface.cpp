#include "SelectObjectInterface.h"


/*
void void System::ComponentModel::INotifyPropertyChanged::PropertyChanged::add(PropertyChangedEventHandler^ p) {
	pE = static_cast<PropertyChangedEventHandler^> (Delegate::Combine(pE, p)); 
	// cannot refer directly to the event
	// E = static_cast<MyDel^> (Delegate::Combine(pE, p));   // error
}

void void System::ComponentModel::INotifyPropertyChanged::PropertyChanged::remove(PropertyChangedEventHandler^ p) {
	pE = static_cast<PropertyChangedEventHandler^> (Delegate::Remove(pE, p));
}
*/