#include <LinkedList.h>

#ifndef _STATE_H
#define _STATE_H

/*
 * Transition is a structure that holds the address of 
 * a function that evaluates whether or not not transition
 * from the current state and the number of the state to transition to
 */
typedef struct Transition {
  
  bool            (*conditionFunction)();
  int             stateNumber;
  unsigned long   delayTime;
  unsigned long   startTime;
};

/*
 * State represents a state in the statemachine. 
 * It consists mainly of the address of the function
 * that contains the state logic and a collection of transitions 
 * to other states.
 */
class State {
  
  public:
  
    State();
    ~State();

    void addTransition(bool (*c)(), State* s);
    void addTransitionDelay(unsigned long delayTime, State* s);
    int evalTransitions(bool startDelay);
    int execute(bool startDelay);
  
    // stateLogic is the pointer to the function that represents the state logic
    void (*stateLogic)();
    LinkedList<struct Transition*> *transitions;
    int index;
};

State::State() {
  
  transitions = new LinkedList<struct Transition*>();
};

State::~State() {};

/*
 * Adds a transition structure to the list of transitions
 * for this state.
 * Params:
 * conditionFunction is the address of a function that will be evaluated
 * to determine if the transition occurs
 * state is the state to transition to
 */
void State::addTransition(bool (*conditionFunction)(), State* s) {
  
  struct Transition* t = new Transition{conditionFunction, s->index, 0, 0};
  transitions->add(t);
}

void State::addTransitionDelay(unsigned long delayTime, State* s) {

  struct Transition* t = new Transition{NULL, s->index, delayTime, 0};
  transitions->add(t);
}

/*
 * Evals all transitions sequentially until one of them is true.
 * Returns:
 * The stateNumber of the transition that evaluates to true
 * -1 if none evaluate to true ===> Returning index now instead to avoid confusion between first run and no transitions
 */
int State::evalTransitions(bool startDelay) {
  
  if(transitions->size() == 0) {
    
    return index;
  }
  
  bool result = false;
  for (int i=0; i<transitions->size(); i++) {

    if (transitions->get(i)->delayTime == 0) {
    
      result = transitions->get(i)->conditionFunction();
    }
    else {

      unsigned long currentTime =  millis();
      
      if (startDelay) {

        transitions->get(i)->startTime =  currentTime;
      }
      else {
      
        if (currentTime - transitions->get(i)->startTime > transitions->get(i)->delayTime) {

          result = true;
        }
      }
    }
    
    if(result == true) {
      
      return transitions->get(i)->stateNumber;
    }
  }
  return index;
}

/*
 * Execute runs the stateLogic and then evaluates
 * all available transitions. The transition that
 * returns true is returned.
 */
int State::execute(bool startDelay) {
  
  stateLogic();
  return evalTransitions(startDelay);
}

#endif