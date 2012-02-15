#ifndef SUBJECT_H
#define SUBJECT_H

#include <list>

class Observer;

class Subject
{
public:
   virtual ~Subject();

   virtual void Subscribe(Observer* observer);
   virtual void Unsubscribe(Observer* observer);

   virtual void Notify();

protected:
   Subject();

   std::list<Observer*> mObservers;
};

#endif // SUBJECT_H
