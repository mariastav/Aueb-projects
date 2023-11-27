package com.company;

import java.util.ArrayList;
import java.util.Collections;

public class SpaceSearcher {
    private ArrayList<State> states;
    //Constructor
    public SpaceSearcher(){
        states = new ArrayList<>();
    }

    //Astar Algorithm Implementation
    public State Astar(State initialState)
    {
        this.states = new ArrayList<State>();
        this.states.add(initialState); //we add the root to the arraylist of states we want to check
        while(this.states.size() > 0) //while there are stetes to check
        {
            State currentState = this.states.remove(0); //we get the first one who is the root or who has the lowest total cost
            //if the state is terminal we return the state
            if(currentState.isTerminal())
            {
                return currentState;
            }
            //We generate the children and calculate the heuristic values and the cost of the state for every child
            this.states.addAll(currentState.getChildren());
            //We sort all the children according to their heuristic scores and cost from root till the child
            Collections.sort(this.states);
        }
        return null;
    }

}
