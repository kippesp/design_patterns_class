/*
 * Problems/Observer.h
 *
 *  Created on: Sep 15, 2015
 *      Author: aldgoff
 *
 * Varies: If the listeners are varying, use the Observer pattern.
 *
 * Desc: Notify observers automatically.
 *
 * Category: Behavioral
 *
 *  URLs:
 *    http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Observer
 *    http://www.dofactory.com/net/observer-design-pattern
 *    http://www.netobjectives.com/resources/books/design-patterns-explained/review-questions#Chapter18
 *    http://sourcemaking.com/design_patterns/observer
 */

#ifndef PROBLEMS_OBSERVER_H_
#define PROBLEMS_OBSERVER_H_

/* Consider the Dr. Seuss children's story, "The Cat in the Hat." When
 * the cat in the hat says something, things & children should respond.
 * In the approach below, the Perpetrator class has to know about all the
 * other classes. When they get changed Perpetrator has to be recompiled.
 * In addition, Perpetrator manages multiple objects, of multiple classes,
 * with multiple interfaces, which leads to long, hard to follow code.
 * Adding in the Mom and the Fish requires multiple changes in multiple
 * places, reveals multiple seam points; violates open/closed principle.
 * Use the Observer pattern to decouple the Perpetrator class.
 */

namespace legacy {

class Thing {
  string name;

 public:
  Thing(string name) : name(name) {
  }
  ~Thing() {
    string inst = string("  ~Thing ") + name + "\n";
    DTOR(inst, Homework);
  }

 public:
  void obeys() {
    cout << "    Thing " << name << " makes mischief.\n";
  }
};

class Child {
  string name;

 public:
  Child(string name) : name(name) {
  }
  ~Child() {
    string inst = string("  ~Child ") + name + "\n";
    DTOR(inst, Homework);
  }

 public:
  void giggles() {
    cout << "    " << name << " laughs.\n";
  }
};

// Seam point - add another listener.

class Perpetrator {
  const string name;

 public:
  Thing* thing1;
  Thing* thing2;
  Child* boy;
  Child* girl;
  // Seam point - insert another listener.
 public:
  Perpetrator(const string& name)
      : name(name),
        thing1(0),
        thing2(0),
        boy(0),
        girl(0)
  // Seam point - insert another listener.
  {
  }
  ~Perpetrator() {
    DTOR("~Perpetrator\n", Homework);
  }

 public:
  void says(const string& phrase) {
    cout << "  " << name << " says " << phrase << ".\n";
    if (thing1) thing1->obeys();
    if (thing2) thing2->obeys();
    if (boy) boy->giggles();
    if (girl) girl->giggles();
    // Seam point - insert another listener.
  }
};

void demo(int seqNo) {
  cout << seqNo << ") << observer::homework::legacy::demo() >>\n";
  {
    Perpetrator perp("Cat in the Hat");

    Thing* thing1 = new Thing("1");
    Thing* thing2 = new Thing("2");
    Child* boy = new Child("Boy");
    Child* girl = new Child("Girl");

    perp.thing1 = thing1;
    perp.thing2 = thing2;
    perp.says("Hello");

    perp.boy = boy;
    perp.girl = girl;
    perp.says("Let's play");

    perp.thing2 = 0;  // Thing 2 leaves.
    perp.says("Rock n Roll");

    perp.thing1 = 0;  // Thing 1 leaves.
    perp.boy = 0;     // Children go mum.
    perp.girl = 0;
    perp.says("Bye");

    delete thing1;
    delete thing2;
    delete boy;
    delete girl;
  }
  cout << endl;
}

}  // legacy

namespace problem {

struct Listener;

struct Perpetrator {
 private:
  const string name;
  list<Listener*> listeners;

 public:
  Perpetrator(const string& name) : name(name) {
  }

  ~Perpetrator() {
    DTOR("~Perpetrator\n", Problem);
    DTOR("  Listeners left should be zero = ", Problem);
    char size[10];
    sprintf(size, "%lu", listeners.size());
    DTOR(string(size) + ".\n", Problem);
  }

  void attach(Listener* observer) {
    listeners.push_back(observer);
  }

  void detach(Listener* observer) {
    listeners.remove(observer);
  }

  void says(const string& phrase);
};

struct Listener {
 protected:
  const string name;

 public:
  Listener(string name) : name(name) {
  }

  virtual ~Listener() {
    string inst = name + " ~Listener\n";
    DTOR(inst, Problem);
  }

  virtual void update(Perpetrator*) {
  }
};

void Perpetrator::says(const string& phrase) {
  cout << "  " << name << " says " << phrase << ".\n";
  list<Listener*>::iterator it = listeners.begin();
  for (; it != listeners.end(); ++it) {
    (*it)->update(this);
  }
}

struct Thing : public Listener {
  Thing(const string& name) : Listener(name) {
  }

  ~Thing() {
    string inst = string("  ~Thing ") + name + "\n";
    DTOR(inst, Problem);
  }

  void update(Perpetrator*) {
    cout << "    Thing " << name << " makes mischief.\n";
  }
};

struct Child : public Listener {
  Child(const string& name) : Listener(name) {
  }
  ~Child() {
    string inst = string("  ~Child ") + name + "\n";
    DTOR(inst, Problem);
  }

  void update(Perpetrator*) {
    cout << "    " << name << " laughs.\n";
  }
};

struct Fish : public Listener {
  Fish(const string& name) : Listener(name) {
  }

  ~Fish() {
    DTOR("  ~Fish\n", Problem);
  }

  void update(Perpetrator*) {
    cout << "    " << name << " complains.\n";
  }
};

struct Mom : public Listener {
  Mom(const string& name) : Listener(name) {
  }

  ~Mom() {
    DTOR("  ~Mom\n", Problem);
  }

  void update(Perpetrator*) {
    cout << "    " << name << " asks \"How was your day?\"\n";
  }
};

// Seam point - add another listener.

void demo(int seqNo) {
  cout << seqNo << ") << observer::homework::problem::demo() >>\n";
  {
    Perpetrator perpetrator("Cat in the Hat");

    Thing* thing1 = new Thing("1");
    Thing* thing2 = new Thing("2");
    Child* boy = new Child("Boy");
    Child* girl = new Child("Girl");
    Fish* fish = new Fish("Fish");
    Mom* mom = new Mom("Mom");

    perpetrator.attach(thing1);
    perpetrator.attach(thing2);

    perpetrator.says("Hello");

    perpetrator.attach(boy);
    perpetrator.attach(girl);

    perpetrator.says("Let's play");

    perpetrator.detach(thing2);
    perpetrator.attach(fish);

    perpetrator.says("Rock 'n Roll");

    perpetrator.detach(thing1);
    perpetrator.detach(boy);
    perpetrator.detach(girl);
    perpetrator.attach(mom);

    perpetrator.says("Bye");

    perpetrator.detach(fish);
    perpetrator.detach(mom);

    perpetrator.detach(fish);
    perpetrator.detach(mom);

    delete thing1;
    delete thing2;
    delete boy;
    delete girl;
    delete fish;
    delete mom;
  }
  cout << endl;
}

}  // problem

#endif /* PROBLEMS_OBSERVER_H_ */
