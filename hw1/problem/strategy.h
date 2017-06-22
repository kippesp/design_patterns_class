/*
 * strat.h
 *
 *  Created on: Jun 13, 2017
 *      Author: aldgoff
 */

#ifndef SRC_PROBLEMS_STRAT_H_
#define SRC_PROBLEMS_STRAT_H_

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
  Easy
  // Seam point #1 - add another way.
};

void hard() { cout << "The hard way.\n"; }
void easy() { cout << "The easy way.\n"; }
// Seam point #2 - add another way.

void clientCode1(Way way) {
  cout << "  clientCode1 - ";
  switch (way) {
    case Hard:
      hard();
      break;
    case Easy:
      easy();
      break;
      // Seam point #3 - add another way.
  }
}
void clientCode2(Way way) {
  cout << "  clientCode2 - ";
  switch (way) {
    case Hard:
      hard();
      break;
    case Easy:
      easy();
      break;
      // Seam point #4 - add another way.
  }
}
void clientCode3(Way way) {
  cout << "  clientCode3 - ";
  switch (way) {
    case Hard:
      hard();
      break;
    case Easy:
      easy();
      break;
      // Seam point #5 - add another way.
  }
}
//...
void clientCode8(Way way) {
  cout << "  clientCode8 - ";
  switch (way) {
    case Hard:
      hard();
      break;
    case Easy:
      easy();
      break;
      // Seam point #10 - add another way.
  }
}

void demo(int seqNo) {  // Test all daughter classes & clients.
  cout << seqNo << ") << strategy::homework::problem::demo() >>\n";
  Way criteria[] = {Hard, Easy};
  for (size_t i = 0; i < COUNT(criteria); i++) {
    clientCode1(criteria[i]);
    clientCode2(criteria[i]);
    clientCode3(criteria[i]);
    //...
    clientCode8(criteria[i]);
    cout << endl;
  }
  cout << endl;
}

}  // legacy

namespace problem {

enum Way {
  Hard,
  Easy,
  Quick,
  Clear
  // Seam point #1 - add another way.
};

void hard() { cout << "The hard way.\n"; }
void easy() { cout << "The easy way.\n"; }
void quick() { cout << "The quick way.\n"; }
void clear() { cout << "The clear way.\n"; }
// Seam point #2 - add another way.

void clientCode1(Way way) {
  cout << "  clientCode1 - ";
  switch (way) {
    case Hard:
      hard();
      break;
    case Easy:
      easy();
      break;
    case Quick:
      quick();
      break;
    case Clear:
      clear();
      break;
      // Seam point #3 - add another way.
  }
}
void clientCode2(Way way) {
  cout << "  clientCode2 - ";
  switch (way) {
    case Hard:
      hard();
      break;
    case Easy:
      easy();
      break;
    case Quick:
      quick();
      break;
    case Clear:
      clear();
      break;
      // Seam point #4 - add another way.
  }
}
void clientCode3(Way way) {
  cout << "  clientCode3 - ";
  switch (way) {
    case Hard:
      hard();
      break;
    case Easy:
      easy();
      break;
    case Quick:
      quick();
      break;
    case Clear:
      clear();
      break;
      // Seam point #5 - add another way.
  }
}
//...
void clientCode18(Way way) {
  cout << "  clientCode18 - ";
  switch (way) {
    case Hard:
      hard();
      break;
    case Easy:
      easy();
      break;
    case Quick:
      quick();
      break;
    case Clear:
      clear();
      break;
      // Seam point #20 - add another way.
  }
}

void demo(int seqNo) {  // Test all daughter classes & clients.
  cout << seqNo << ") << strategy::homework::problem::demo() >>\n";
  Way criteria[] = {Hard, Easy, Quick, Clear};
  for (size_t i = 0; i < COUNT(criteria); i++) {
    clientCode1(criteria[i]);
    clientCode2(criteria[i]);
    clientCode3(criteria[i]);
    //...
    clientCode18(criteria[i]);
    cout << endl;
  }
  cout << endl;
}

}  // problem

#endif /* SRC_PROBLEMS_STRAT_H_ */
