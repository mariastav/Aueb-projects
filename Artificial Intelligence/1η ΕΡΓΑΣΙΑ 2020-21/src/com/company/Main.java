package com.company;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;

public class Main {
    private static ArrayList<Person> right_side = new ArrayList<>();
    private static int time;

    public static void main(String[] args) throws IOException {
        //this is for testing the program, it creates the same people as the video from the exercise
        initTest();
        //init(); //we call a function to initialise the right side of the problem
        State init = new State(right_side,time); //we create the root state of the problem
        SpaceSearcher sp = new SpaceSearcher(); //we create a new spacesearcher
        //with the function currentTimeMillis we want to calculate how much time the pc actually takes to find the solution
        long start = System.currentTimeMillis();
        State fin = sp.Astar(init); //run the algorithm with the root state
        long end = System.currentTimeMillis();
        //if the algorithm can't find a solution we need to inform the user
        if(fin == null)
        {
            System.out.println("Could not find solution");
        }
        else
        {
            //find the path from the leaf state to the root
            State temp = fin;
            ArrayList<State> path = new ArrayList<>();
            path.add(fin);
            while(temp.getFather()!=null)
            {
                path.add(temp.getFather());
                temp = temp.getFather();
            }
            //reverse the path in order for the root is first and the leaf state last
            Collections.reverse(path);
            //print the steps that the problem need in order to be solved
            System.out.println("Finished in "+path.size()+" steps!");
            for(State item : path)
            {
                item.print();
            }
        }
        System.out.println("A* search time: " + (double)(end - start) / 1000 + " sec."); //print the time that the pc need in order to run the program(the algorithm not the printing)
    }

    //get the root state information from the user using the console
    private static void init() {
        //we use a buffer reader in order to read users imput
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));) {
            //we ask for the number of people on the right side
            System.out.println("Enter the number of participants here: ");
            int num = Integer.parseInt(reader.readLine());

            System.out.println("Enter the max time you want the problem to be solved: ");
            time = Integer.parseInt(reader.readLine());

            //for the numder of people that the user gave us we ask the name and the number of the people
            for(int i=1; i<=num; i++){
                System.out.println("Enter the name of person number " + i + " here: ");
                String name = reader.readLine();
                System.out.println("Enter the time of person number " + i + " here: ");
                int time = Integer.parseInt(reader.readLine());
                Person p = new Person(name, time);
                right_side.add(p);
            }
        }
        catch (IOException ex){
            System.out.println(ex);
        }

    }

    private static void initTest() {
        Person a = new Person("A",1);
        Person b = new Person("B",3);
        Person c = new Person("C",6);
        Person d = new Person("D",8);
        Person e = new Person("E",12);
        right_side.add(a);
        right_side.add(b);
        right_side.add(c);
        right_side.add(d);
        right_side.add(e);
        time = 30;
    }

}

