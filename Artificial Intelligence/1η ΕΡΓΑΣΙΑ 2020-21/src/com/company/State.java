package com.company;

import java.util.ArrayList;

public class State implements Comparable{

    public static int starting_time; //the starting time of the problem
    private ArrayList<Person> left_side = new ArrayList<>(); //an arraylist of all the people on the left side
    private ArrayList<Person> right_side = new ArrayList<>(); //an arraylist of all the people on the right side
    private State father; //the father of this state. we need this on order to follow the path from start to finish if we find a solution.
    private int score; //the score from the heuristic function
    private int total_cost; //g(s) all the costs from root to this state
    private boolean right_side_bool; //boolean that represents where is the torch
    private int time_left; //time left for the problem

    //Constructor for the root
    public State(ArrayList<Person> init,int starting_time){
        right_side.addAll(init); //add everything to the right side
        State.starting_time = starting_time; //initialise the starting time
        time_left = starting_time; //initialise time_left
        right_side_bool= true; //put the torch on the right side
    }

    //the constructor that creates a copy of the current state
    public State(State state){
        this.right_side.addAll(state.getRight_side());
        this.left_side.addAll(state.getLeft_side());
        this.time_left = state.getTime_left();
        this.right_side_bool = !state.isRight_side_bool();
        father = state;
    }

    //Getters and setters

    public ArrayList<Person> getLeft_side() {
        return left_side;
    }

    public void setLeft_side(ArrayList<Person> left_side) {
        this.left_side = left_side;
    }

    public ArrayList<Person> getRight_side() {
        return right_side;
    }

    public void setRight_side(ArrayList<Person> right_side) {
        this.right_side = right_side;
    }

    public int getTime_left() {
        return time_left;
    }

    public void setTime_left(int time_left) {
        this.time_left = time_left;
    }

    public boolean isRight_side_bool() {
        return right_side_bool;
    }

    //get the cost from root till this state
    private int getCostFromRoot() {
        return starting_time -time_left;
    }

    //return total cost of state (h(s)+g(s))
    private int getTotalCost() {
        return total_cost;
    }

    //move people from right to left.
    public void move_left(Person[] peopleToMove){
        int time_to_pass = 0;

        for(Person p: peopleToMove){
            int person_time = p.getTime();
            time_to_pass = Math.max(time_to_pass, person_time); //find the max cost between the 2
            right_side.remove(p);
            left_side.add(p);
            //if the pair has only one person then skip and move only one person
            if(peopleToMove[1].equals(p))
                break;
        }
        time_left = time_left-time_to_pass; //remove the cost of moving the person/people
    }

    //move people from left to right.
    public void move_right(Person[] peopleToMove){
        int time_to_pass = 0;
        for(Person p: peopleToMove){
            int person_time = p.getTime();
            time_to_pass = Math.max(time_to_pass, person_time); //find the max cost between the 2
            left_side.remove(p);
            right_side.add(p);
            //if the pair has only one person then skip and move only one person
            if(peopleToMove[1].equals(p))
                break;
        }
        time_left = time_left-time_to_pass; //remove the cost of moving the person/people
    }

    //checks if the right side is empty
    public boolean isTerminal()
    {
        return right_side.isEmpty();
    }

    //print the current state
    public void print(){
            for(Person p:left_side)
                System.out.print(p.getName()+" ");
            if(!right_side_bool)
                System.out.print("\uD83D\uDCA1");
            System.out.print(" -------- ");
            if(right_side_bool)
                System.out.print("\uD83D\uDCA1");
        for(Person p:right_side)
            System.out.print(p.getName()+" ");
        System.out.print("Time left : "+time_left);
        System.out.print("\n");
    }

    //get the children of the state
    public ArrayList<State> getChildren(){
        ArrayList<State> children = new ArrayList<>();
        ArrayList<Person> current_side = right_side_bool?right_side:left_side;
        ArrayList<Person[]> children_arrays =  cartesianProduct(current_side); //get all the possible combinations
        State child ;
        for(Person[] p : children_arrays){
            child = new State(this); //create a new state for every combination

            //move the people that the combination suggests in order to create the new state
            if(right_side_bool)
                child.move_left(p);
            else
                child.move_right(p);
            //calculate the score for every child that has time left
            if(child.time_left>=0) {
                child.total_cost = (heuristic()+ getCostFromRoot()); //add h(s)+g(s)
                children.add(child); //add the child to the arraylist
            }
        }
        return children;
    }


    //calculate the heuristic
    //add the max cost of everyone who is right if the torch is right
    //and if the torch is left add the min of the left side to the max form above
    private int heuristic() {
        //find max of right side
        int max = -1;
        for(Person p: right_side){
            int p_time = p.getTime();
            max = Math.max(p_time, max);
        }
        //if we are on the right side return max
        if(right_side_bool){
            score = max;
            return score;
        }
        //find min of the left side
        int min = left_side.get(0).getTime(); //we get min as the cost of the first person who is left
        for(Person p: left_side){
            int p_time = p.getTime();
            min = Math.min(p_time, min);
        }
        //if we are left we reutnr max+min
        score = max + min ;
        return score;
    }

    //generate the cartesian Product of a list of people
    public ArrayList<Person[]> cartesianProduct(ArrayList<Person> list){
        ArrayList<Person[]> results = new ArrayList<>();
        if(list.size()==1 && right_side_bool) {
            Person[] pair = {list.get(0), list.get(0)};
            results.add(pair);
            return results;
        }
        for(Person firstPerson : list){
            for(Person secondPerson : list){
                boolean exists = false; //this exists helps us identify the duplicates that have another order(because order isn't a factor for this problem)
                //let's say [b,a] is a pair we want to add , it checks if there is another pair that is [a,b] already in the arraylist
                for(Person[] pair : results){
                    if (pair[0].getName().equals(secondPerson.getName()) && pair[1].getName().equals(firstPerson.getName())) {
                        exists = true;
                        break;
                    }
                }
                //if [a,b] already exists we don't add it to the arraylist
                if(exists)
                    continue;
                Person[] pair = {firstPerson,secondPerson};

                //if we are on the right side we don't want only one person to pass but 2 so we continue
                if(right_side_bool){
                    if(pair[0].getName().equals(pair[1].getName()))
                        continue;
                }
                //if we are on the left side we want only one person to pass
                else{
                    if(!pair[0].getName().equals(pair[1].getName()))
                        continue;
                }

                results.add(pair);
            }
        }
        return results;
    }

    //return the father of the state
    public State getFather() {
        return father;
    }

    //this is used when we sort the collection of states in SpaceSearcher and we want to compare the states based on the total costs (h(s)+g(s))
    @Override
    public int compareTo(Object o) {
        return Integer.compare(this.getTotalCost(),((State)o).getTotalCost());
    }



}
