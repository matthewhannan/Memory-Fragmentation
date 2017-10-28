//
//  pa2.cpp
//  pa_2
//
//  Created by Matt Hannan on 10/22/17.
//  Copyright © 2017 Matt Hannan. All rights reserved.
//

#include <iostream>
#include "pa2.h"
#include <string>
#include <limits>

using namespace std;

//allocating memory dedicated to this program

LinkedList memory;

//kilobyte of program to pages conversion
int kilobyteConversion(int kilobytes){
    if(kilobytes % 4 == 0){
        return kilobytes/4;
    }
    return (kilobytes/4) + 1;
}

void kill(){
    
    cout<<"Program name - ";
    string nameOfProgram;
    cin>>nameOfProgram;
    
    //empties and essentially deleted program, which frees up space
    int successful = memory.empty(nameOfProgram);
    cout<<endl;
    
    //checks for error in removal
    if(successful > 0){
        cout<<"Program "<<nameOfProgram<< " successfully killed, "<<successful<<" page(s) reclaimed.";
    }
    else{
        cout<<"The program named "<<nameOfProgram<<" doesn't exist!";
    }
    
}

void add(bool worst){
    cout<<"Program title - ";
    string title;
    cin>>title;
    int sizeOfKilobytes;
    cout<<"Program size (KB) - ";
    cin>>sizeOfKilobytes;
    int sizePG = kilobyteConversion(sizeOfKilobytes);
    bool exception = false;  //exception to check if title was already used
    bool successful = false;  //checks if the program ran fine
    
    //smakes sure the program title isn't already taken
    if(memory.search(title)){
        cout<<endl;
        cout<<"That title is already taken! "<<title;
        exception = true;
    }
    
    //inserts program depending on algorithmic fit style
    else{
        if(worst){
            successful = memory.worstAlgorithm(title, sizePG);
        }
        else{
            successful = memory.bestAlgorithm(title, sizePG);
        }
    }
    
    
    //double checks for errors/exceptions
    if(!exception){
        cout<<endl;
        if(successful){
            cout<<"Program "<<title<< " added successfulfully: "<<sizePG<<" page(s) used.";
        }
        else {
            cout<<"Program is too large - Unable to add! "<<title<<".";
        }
    }
}

//erases all memory allocated in order to abort program
void exit(){
    memory.erase();
}

//counts fragments
void fragment(){
    int fragments = memory.fragmentation();
    cout<<endl<<"There are "<<fragments<<" fragment(s).";
}


int main(int argc, char *argv[]){
    
    //takes in a user input via command line argument to specify worst/best fit preference
    string algorithm = argv[1];
    bool worst = false;
    cout<<"Welcome to Project Two - Memory Allocation!!"<<endl;
    while(true){
        
        if(algorithm.compare("worst") == 0){
            worst = true;
            cout<<"Worst fit algorithm chosen!"<<endl;
            break;
        }
        else if(algorithm.compare("best") == 0){
            worst = false;
            cout<<"Best fit algorithm chosen!"<<endl;
            break;
        }
        else cout<<"Try Again - Type either \"worst\" or \"best\""<<endl;
    }
    
    //setting values to the linked list nodes
    for(int x = 0; x < 32; x++){
        memory.place();
    }
    
    //coordinates user intention to command the program
    int decide = 0;
    do{
        cout<<endl;
        cout<<"1. Add program"<<endl;
        cout<<"2. Kill program"<<endl;
        cout<<"3. Fragmentation"<<endl;
        cout<<"4. Print memory"<<endl;
        cout<<"5. Exit"<<endl<<endl;
        //regulates user input
        int userIn;
        cout<<"userIn - ";
        while(!(cin >> userIn)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"That's not an option - Please try again"<<endl;
            cout<<"Selection - ";
        }
        
        decide = userIn;
        //makes sure the user chose an option that was possible
        if(userIn != 1 && userIn != 2 && userIn != 3 && userIn != 4 && userIn != 5){
            cout<<"That's not an option - Please try again";
            continue;
        }
        //calls corresponding methods
        switch(userIn){
            case 1: add(worst); break;
            case 2: kill(); break;
            case 3: fragment(); break;
            case 4: memory.printList(); break;
            case 5: exit(); break;
        }
        
        cout<<endl;
        
    } while(decide != 5);
    
    return 0;
}
