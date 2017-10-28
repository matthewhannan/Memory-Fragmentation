//
//  pa2.h
//  pa_2
//
//  Created by Matt Hannan on 10/22/17.
//  Copyright © 2017 Matt Hannan. All rights reserved.
//

#ifndef pa2_h
#define pa2_h
#include <cstdlib>
#include <string>
#include <iostream>
#include <limits>
using namespace std;

//creating class Node
class Node {
//encapsulation

private:
    Node *consecutive; //the next node after a node
    bool unused; //whether a node is used or not
    string title; //title of the node

public:
    //deliberate constructor
    Node(){
        unused = true;
        title = "";
        consecutive = NULL;
    }
    //method makes a node null
    void nullifyNode(){
        consecutive = NULL;
    }
    //accessors (getters) and mutators (setters) for private Node variable, due to object oriented ettiquitte
    bool getUnused(){
        return this->unused;
    }
    string getTitle(){
        return this->title;
    }
    Node *getConsecutive(){
        return this->consecutive;
    }
    void setUnused(bool unused){
        this->unused = unused;
    }
    void setTitle(string title){
        this->title = title;
    }
    void setConsecutive(Node *consecutive){
        this->consecutive = consecutive;
    }
    
};
//class that creates the LinkedList
class LinkedList {
//encapsulation
private:
    
    Node *initial;//keeps a pointer on the first node
    
public:
    //LinkedList methods
    void linkedList(){
        this->initial = NULL;
    }
    void unusedList(){
        void unused();
    }
    void linkedList(Node *initial){
        this->initial = initial;
    }
    //setters and getters for initial node on linked list
    Node *getInitial(){
        return this->initial;
    }
    void setInitial(Node *initial){
        this->initial = initial;
    }
    //prints the full list in real time to aid with debugging
    void printList(){
        if(initial == NULL){
            cout << "List is empty!" << endl;
        }
        else {
            int counter = 0;
            Node *node = initial;
            while(node != NULL && counter != 32){
                if(node->getUnused() == false){
                    cout<< node->getTitle() << "\t";
                    node = node->getConsecutive();
                    counter++;
                }
                else {
                    cout << "Free\t" ;
                    node = node->getConsecutive();
                    counter++;
                }
                if(counter % 8 == 0){
                    cout << endl;
                }
            }
        }
    }
    
    //searches through the list for a specific name program
    bool search(string title){
        Node *temporary = initial;
        for(int i = 0; i < 32; i++){
            if(temporary != NULL){
                if(temporary->getTitle().compare(title)== 0){
                    return true;
                }
                temporary = temporary->getConsecutive();
            }
        }
        return false;
    }
    
    //places the new program in the list
    void place(){
        Node *node = new Node();
        if(initial == NULL) {
            initial = node;
            return;
        }
        Node *temporary = initial;
        for(int i = 0; i < 32; i++){
            if(temporary->getConsecutive() != NULL){
                temporary = temporary->getConsecutive();
            }
        }
        temporary->setConsecutive(node);
    }
    
    //empties a node of its states
    int empty(string title){
        Node *temporary = initial;
        int counter = 0;
        for(int y = 0; y < 32; y++){
            if(temporary != NULL){
                if(temporary->getTitle().compare(title)== 0){
                    temporary->setTitle("");
                    temporary->setUnused(true);
                    temporary = temporary->getConsecutive();
                    counter++;
                }
                else{
                    temporary = temporary->getConsecutive();
                }
            }
        }
        return counter;
    }
    //counts the possible fragments of empty spaces on the list
    
    //deletes memory/data
    void erase(){
        Node *temporary = initial;
        Node *next = NULL;
        for(int x = 0; x < 32; x++){
            if(temporary != NULL){
                next = temporary->getConsecutive();
                delete temporary;
                temporary = next;
            }
        }
    }
    
    int fragmentation(){
        Node *temporary = initial;
        int counter = 0;
        Node *end = temporary;
        for( int i = 0; i < 32; i++){
            if(temporary != NULL){
                bool unused = temporary->getUnused();
                if(unused){
                    Node *next = temporary->getConsecutive();
                    if(next != NULL){
                        if(!next->getUnused()){
                            counter++;
                        }
                    }
                }
                end = temporary;
                temporary = temporary->getConsecutive();
            }
        }
        bool tempUnused = true;
        tempUnused = end->getUnused();
        if(!tempUnused){
            return counter;
        }
        else{
            return (counter + 1);
        }
    }
    
    //algorithm that user defines on how to add programs to the list (best fit)
    bool bestAlgorithm(string title, int size){
        Node *temp = getInitial();
        Node *biggest = temp;
        int minimum = 33;
        int counter = 0;
        Node *initialNode = temp;
        bool successful = false;
        
        
        while (temp != NULL){
            
            bool untaken = temp->getUnused();
            Node *consecutive = temp->getConsecutive();
            //asks if a space is free or not
            if(untaken){
                counter++;
                if(consecutive == NULL && counter < minimum && counter >= size){
                    counter++;
                    minimum = counter;
                    biggest = initialNode;
                    break;
                }
                
                temp = temp->getConsecutive();
                
            }
            
            else{
                counter++;
                if(counter < minimum && counter > size){
                    
                    minimum = counter;
                    biggest = initialNode;
                    counter = 0;
                    temp = temp->getConsecutive();
                    initialNode = temp;
                }
                else{
                    counter = 0;
                    temp = temp->getConsecutive();
                    initialNode = temp;
                }
            }
        }
        Node *first = biggest;
        //asks how specific the available space is relative to the program's size
        if(minimum <= size){
            successful = false;
        }
        else{
            for(int q = 0; q < size; q++){
                
                first->setUnused(false);
                first->setTitle(title);
                successful = true;
                first = first->getConsecutive();
            }
        }
        return successful;
    }
    //algorithm that user defines on how to add programs to the list (worst fit)
    bool worstAlgorithm(string title, int size){
        Node *temp = initial;
        Node *biggest = temp;
        int maximum = 0;
        int counter = 0;
        Node *initialNode = temp;
        bool successful = false;
        
        while (temp != NULL){
            
            bool used = temp->getUnused();
            Node *consecutive = temp->getConsecutive();
            //checks if a node is free or not
            if(used){
                counter++;
                
                if(consecutive == NULL && counter > maximum && counter >= size){
                    counter++;
                    maximum = counter;
                    biggest = initialNode;
                    break;
                }
                
                temp = temp->getConsecutive();
                
                
            }
            
            else{
                counter++;
                if((counter > maximum) && (counter > size)){
                    
                    maximum = counter;
                    biggest = initialNode;
                    counter = 0;
                    temp = temp->getConsecutive();
                    initialNode = temp;
                }
                else{
                    counter = 0;
                    temp = temp->getConsecutive();
                    initialNode = temp;
                }
            }
        }
        Node *first = biggest;
        //asks how specific the available space is relative to the program's size
        if(maximum <= size){
            successful = false;
        }
        else{
            for(int i = 0; i < size; i++){
                
                first->setUnused(false);
                first->setTitle(title);
                successful = true;
                first = first->getConsecutive();
            }
        }
        return successful;
    }
    
};

#endif /* pa_2_h */
