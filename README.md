# StateMachine
This library implements a basic State Machine. The state logic and its transition's conditions are implemented as functions in your sketch for flexibility. The machine is intended to be deterministic, meaning that you can only be in one state at the time and transitions should occur only when your transition condition functions return true. Please note that if multiple transitions are defined for a state the first one to evaluate to true is the one that modifies the current state. The 

This implementation relies on LinkedList (https://github.com/ivanseidel/LinkedList) to implement the collection of states and the collection of transitions for a state.

Modified and extended By Neville Kripp (GrumpyOldTech)
Original works by jrullan <jerullan@yahoo.com>


## STATES
There are two ways of declaring a state logic:
1. Through a lambda function (an anonymous function) declared in the addState() method.
2. Defining the function normally and passing the address to the addState() method.
 
States contain the machine logic of the program. The machine only evaluates the current state until a transition occurs that points to another state.

To evaluate a piece of code only once while the machine is in a particular state, you can use the machine.evaluateOnce attribute. It is true each time the machine enters a new state until the first transition is evaluated.

## TRANSITIONS
Each state has transitions defined in setup(). Transitions require two parameters, 
1. The transition test function that returns a boolean value indicating whether or not the transition occured, 
2. The state pointer.
3. There is the option of specifing a delay transition as well, in this case the first parameter is the delay period in milliseconds

Transitions are evaluated by the state machine after the state logic has executed. If none of the transitions evaluate to true, then the machine stays in the current state. 
