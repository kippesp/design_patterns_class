/*
 * chainOfResp.h
 *
 *  Created on: Sep 26, 2015
 *      Author: aldgoff
 *
 * Varies: If the responders are varying, use the Chain of Responsibility
 * pattern.
 *
 * Desc:
 *
 * Category: whatever
 *
 *  URLs:
 *    http://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#ChainOfReponsibility
 *    http://www.dofactory.com/net/chain-of-responsibility-design-pattern
 *
 *    http://sourcemaking.com/design_patterns/chain_of_responsibility
 */

#ifndef PROBLEMS_CHAINOFRESP_H_
#define PROBLEMS_CHAINOFRESP_H_

/* Consider how to model decision making in a military chain of command.
 * Simple decisions get made by the junior officers,
 * harder ones by the senior officers.
 * Model the major being killed in action.
 */

namespace legacy {

class Lieutenant {
 public:
  Lieutenant() {
  }
  ~Lieutenant() {
    DTOR("  ~Lieutenant\n", Homework);
  }

 public:
  void makeDecision(int livesAtRisk) {
    cout << "  Lieutenant charges " << livesAtRisk << ".\n";
  }
};

class Captain {
 public:
  Captain() {
  }
  ~Captain() {
    DTOR("  ~Captain\n", Homework);
  }

 public:
  void makeDecision(int livesAtRisk) {
    cout << "  Captain retreats " << livesAtRisk << ".\n";
  }
};

Lieutenant lieutenant;
Captain captain;
// Seam point - insert another officer class.

void clientCode(int livesAtRisk) {
  if (livesAtRisk < 10)
    lieutenant.makeDecision(livesAtRisk);
  else if (livesAtRisk < 20)
    captain.makeDecision(livesAtRisk);
  // Seam point - insert another decision level.
  else
    cout << "  Indecision " << livesAtRisk << ".\n";
}

void demo() {
  int data[] = {5, 15, 80};
  for (size_t i = 0; i < COUNT(data); i++) {
    clientCode(data[i]);
  }

  lieutenant.~Lieutenant();
  captain.~Captain();
  cout << endl;
}

}  // legacy

namespace problem {

struct Approver {
 protected:
  Approver* successor;

 public:
  Approver() {
    cout << "  +Approver\n";
  }

  ~Approver() {
    DTOR("  ~Approver\n", Homework);
  }

  Approver* setupChain();

  static Approver* makeObject(const string& criteria);
  void setSuccessor(Approver* approver) {
    successor = approver;
  }
};

struct Lieutenant : Approver {
  Lieutenant() {
    cout << "  +Lieutenant\n";
  }
  ~Lieutenant() {
    DTOR("  ~Lieutenant\n", Homework);
  }

  void makeDecision(int livesAtRisk) {
    cout << "  Lieutenant charges " << livesAtRisk << ".\n";
  }
};

struct Captain : Approver {
  Captain() {
    cout << "  +Captain\n";
  }
  ~Captain() {
    DTOR("  ~Captain\n", Homework);
  }

  void makeDecision(int livesAtRisk) {
    cout << "  Captain retreats " << livesAtRisk << ".\n";
  }
};

struct Major : Approver {
  Major() {
    cout << "  +Major\n";
  }
  ~Major() {
    DTOR("  ~Major\n", Homework);
  }

  void makeDecision(int livesAtRisk) {
    cout << "  Major flanks " << livesAtRisk << ".\n";
  }
};

struct Colonel : Approver {
  Colonel() {
    cout << "  +Colonel\n";
  }
  ~Colonel() {
    DTOR("  ~Colonel\n", Homework);
  }

  void makeDecision(int livesAtRisk) {
    cout << "  Colonel gathers intel " << livesAtRisk << ".\n";
  }
};

struct General : Approver {
  General() {
    cout << "  +General\n";
  }
  ~General() {
    DTOR("  ~General\n", Homework);
  }

  void makeDecision(int livesAtRisk) {
    cout << "  General strategizes " << livesAtRisk << ".\n";
  }
};

struct CommanderInChief : Approver {
  CommanderInChief() {
    cout << "  +CommanderInChief\n";
  }
  ~CommanderInChief() {
    DTOR("  ~CommanderInChief\n", Homework);
  }

  void makeDecision(int livesAtRisk) {
    cout << "  Pres negotiates " << livesAtRisk << ".\n";
  }
};

Approver* Approver::setupChain() {
  string chain[] = {"lieutenant", "captain", "major",
                    "colonel",    "general", "commanderinchief"};

  Approver* responder = Approver::makeObject(chain[0]);

  Approver* current = responder;

  for (size_t i = 1; i < COUNT(chain); i++) {
    Approver* next = Approver::makeObject(chain[i]);
    current->setSuccessor(next);
    current = next;
  }

  current->setSuccessor(new Approver);

  return responder;
}

Approver* Approver::makeObject(const string& criteria) {
  if (criteria == "lieutenant")
    return new Lieutenant;
  else if (criteria == "captain")
    return new Captain;
  else if (criteria == "major")
    return new Major;
  else if (criteria == "colonel")
    return new Colonel;
  else if (criteria == "general")
    return new General;
  else if (criteria == "commanderinchief")
    return new CommanderInChief;
  else
    throw "oops";
}

// Seam point - add another officer class.

Lieutenant* lieutenant = 0;
Captain* captain = 0;
Major* major = 0;
Colonel* colonel = 0;
General* general = 0;
CommanderInChief* pres = 0;
// Seam point - insert another officer class.

void setup() {
  lieutenant = new Lieutenant;
  captain = new Captain;
  major = new Major;
  colonel = new Colonel;
  general = new General;
  pres = new CommanderInChief;
  // Seam point - insert another officer.
}
void teardown() {
  delete lieutenant;
  delete captain;
  delete major;
  delete colonel;
  delete general;
  delete pres;
  // Seam point - insert another officer.
}

void clientCode(int livesAtRisk) {
  if (livesAtRisk < 10)
    lieutenant->makeDecision(livesAtRisk);
  else if (livesAtRisk < 20)
    captain->makeDecision(livesAtRisk);
  else if (livesAtRisk < 100)          // KIA, but can't
    major->makeDecision(livesAtRisk);  // change at runtime.
  else if (livesAtRisk < 5000)
    colonel->makeDecision(livesAtRisk);
  else if (livesAtRisk < 100000)
    general->makeDecision(livesAtRisk);
  else if (livesAtRisk >= 100000)
    pres->makeDecision(livesAtRisk);
  // Seam point - insert another decision level.
  else
    throw "OOPS!";
}

void demo() {
  setup();

  int data[] = {5, 15, 80, 1155, 8144, 400000};
  for (size_t i = 0; i < COUNT(data); i++) {
    clientCode(data[i]);
  }

  teardown();

  cout << endl;
}

}  // problem

#endif /* PROBLEMS_CHAINOFRESP_H_ */
