package com.company;

public class Person{
    //The name of the person
    private String name;
    //The time that takes the person to pass on the other side
    private int time;

    //Constructor
    public Person (String name, int time){
        this.name = name;
        this.time = time;
    }

    //Getter for name
    public String getName(){
        return name;
    };

    //Getter for time
    public int getTime(){
        return time;
    }

    //checking if 2 people have the same name and time
    @Override
    public boolean equals(Object obj){
        if(!name.equals(((Person)obj).getName())||time!=((Person)obj).getTime())
            return false;
        return true;
    }

    @Override
    public int hashCode()
    {
        return name.hashCode() + this.time;
    }
}