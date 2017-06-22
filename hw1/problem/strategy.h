/*
 * strat.h
 *
 *  Created on: Jun 13, 2017
 *      Author: aldgoff
 */

#ifndef SRC_PROBLEMS_STRAT_H_
#define SRC_PROBLEMS_STRAT_H_

#include <cassert>

#include "macros.h"

/* Consider a case where there is a growing number of ways to perform a task
 * and a growing number of use cases that have to choose one of those ways.
 *
 * Below is legacy code that might result from the first few stories.
 * Initially there are two ways to perform the task and a handful of use
 * cases. At first, things don't look so bad, but we've set ourselves up
 * for quadratic scaling in the lines of code. As each new user story
 * is implemented the quadratic scaling law of change in two dimensions
 * steadily erodes programmer velocity.
 *
 * Why? Because we have not separated decision from doing.
 * We go from 10 seam points in the legacy code to 20 seam points in the
 * problem code, and that number will continue to go up.
 * The decision act (switch statement) is heavily duplicated.
 *
 * Refactor using the Strategy design pattern to return to a linear
 * scaling law; separate deciding from doing. Regardless of whether the
 * next story adds a new way to perform the task or a new use case
 * only a linear amount of code needs to be added. You will know when
 * your design is a success once the number of seam points remains constant.
 */

namespace legacy {

enum Way {
  Hard,
  Easy,
  Trivial
  // Seam point #1 - add another way.
};

// Seam point #2 - add another way.

struct Strategy {
  virtual ~Strategy() {
    DTOR("~Strategy", Homework);
  }

  virtual void compute() = 0;
};

struct CriteriaHard : public Strategy {
  ~CriteriaHard() {
    DTOR("~CriteriaHard", Homework);
  }

  void compute() {
    cout << "The hard way.\n";
  }
};

struct CriteriaEasy : public Strategy {
  ~CriteriaEasy() {
    DTOR("~CriteriaEasy", Homework);
  }

  void compute() {
    cout << "The easy way.\n";
  }
};

struct CriteriaTrivial : public Strategy {
  ~CriteriaTrivial() {
    DTOR("~CriteriaTrivial", Homework);
  }

  void compute() {
    cout << "The trivial way.\n";
  }
};

void clientCode1(Strategy* criteria) {
  cout << "  clientCode1 - ";
  criteria->compute();
}

void clientCode2(Strategy* criteria) {
  cout << "  clientCode2 - ";
  criteria->compute();
}

void clientCode3(Strategy* criteria) {
  cout << "  clientCode3 - ";
  criteria->compute();
}

//...
void clientCode8(Strategy* criteria) {
  cout << "  clientCode8 - ";
  criteria->compute();
}

void demo(int seqNo) {  // Test all daughter classes & clients.
  cout << seqNo << ") << strategy::homework::problem::demo() >>\n";
  Way criteria[] = {Hard, Easy, Trivial};
  Strategy* scheme[COUNT(criteria)] = {0};

  for (size_t i = 0; i < COUNT(criteria); i++) {
    switch (criteria[i]) {
      case Hard:
        scheme[i] = new CriteriaHard;
        break;
      case Easy:
        scheme[i] = new CriteriaEasy;
        break;
      case Trivial:
        scheme[i] = new CriteriaTrivial;
        break;
      default:
        assert(false);
    }

    clientCode1(scheme[i]);
    clientCode2(scheme[i]);
    clientCode3(scheme[i]);
    //...
    clientCode8(scheme[i]);
    cout << endl;
  }
  cout << endl;

  for (size_t i = 0; i < COUNT(criteria); i++) {
    delete scheme[i];
  }
}

}  // legacy

namespace problem {

enum Way {
  Hard,
  Easy,
  Quick,
  Clear,
  Given,
  // Seam point #1 - add another way.
};

// Seam point #2 - add another way.

struct Strategy {
  virtual ~Strategy() {
    DTOR("~Strategy", Homework);
  }

  virtual void compute() = 0;
};

struct CriteriaHard : Strategy {
  ~CriteriaHard() {
    DTOR("~CriteriaHard", Problem);
  }

  void compute() {
    cout << "The hard way.\n";
  }
};

struct CriteriaEasy : Strategy {
  ~CriteriaEasy() {
    DTOR("~CriteriaEasy", Problem);
  }

  void compute() {
    cout << "The easy way.\n";
  }
};

struct CriteriaQuick : Strategy {
  ~CriteriaQuick() {
    DTOR("~CriteriaQuick", Problem);
  }

  void compute() {
    cout << "The quick way.\n";
  }
};

struct CriteriaClear : Strategy {
  ~CriteriaClear() {
    DTOR("~CriteriaClear", Problem);
  }

  void compute() {
    cout << "The clear way.\n";
  }
};

struct CriteriaGiven : Strategy {
  ~CriteriaGiven() {
    DTOR("~CriteriaGiven", Problem);
  }

  void compute() {
    cout << "The given way.\n";
  }
};

void clientCode1(Strategy* criteria) {
  cout << "  clientCode1 - ";
  criteria->compute();
}

void clientCode2(Strategy* criteria) {
  cout << "  clientCode2 - ";
  criteria->compute();
}

void clientCode3(Strategy* criteria) {
  cout << "  clientCode3 - ";
  criteria->compute();
}

//...

void clientCode18(Strategy* criteria) {
  cout << "  clientCode18 - ";
  criteria->compute();
}

void demo(int seqNo) {  // Test all daughter classes & clients.
  cout << seqNo << ") << strategy::homework::problem::demo() >>\n";
  Way criteria[] = {Hard, Easy, Quick, Clear, Given};
  Strategy* scheme[COUNT(criteria)] = {0};

  for (size_t i = 0; i < COUNT(criteria); i++) {
    switch (criteria[i]) {
      case Hard:
        scheme[i] = new CriteriaHard;
        break;
      case Easy:
        scheme[i] = new CriteriaEasy;
        break;
      case Quick:
        scheme[i] = new CriteriaQuick;
        break;
      case Clear:
        scheme[i] = new CriteriaClear;
        break;
      case Given:
        scheme[i] = new CriteriaGiven;
        break;
      default:
        assert(false);
    }
  }

  for (size_t i = 0; i < COUNT(criteria); i++) {
    clientCode1(scheme[i]);
    clientCode2(scheme[i]);
    clientCode3(scheme[i]);
    //...
    clientCode18(scheme[i]);
    cout << endl;
  }
  cout << endl;

  for (size_t i = 0; i < COUNT(criteria); i++) {
    delete scheme[i];
  }
}

}  // problem

#endif /* SRC_PROBLEMS_STRAT_H_ */
