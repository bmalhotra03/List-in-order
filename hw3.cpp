// Brij Malhotra
// hw3.cpp
// Purpose: Create a program that reads in data from a file and displays it in the original order according to the number

#include <iostream>
#include <string>
#include <sstream> 
#include <fstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

class Line
{
    private:
        
        struct Node {
            int order;
            Node * next;
            string name;
        };
        Node * head;

    public: 
        
        Line(){
            head = nullptr;
        }

        ~Line(){
            Node * curr;
            Node * next;

            curr = head;

            while (curr!=nullptr){
                next = curr->next;
                delete curr;
                curr = next;
            }
            head = nullptr;
        }

        void Insert(int num, string name){

            Node * newNode = nullptr;
            Node * curr = nullptr;
            Node * prev = nullptr;

            newNode = new Node();
            newNode->order = num;
            newNode->name = name;
            newNode->next = nullptr;

            if (!head){
                head = newNode;
            } else{
                curr = head;
                prev = nullptr;
                
                while (curr!= nullptr && curr->order < num){
                    prev = curr;
                    curr = curr->next;
                }

                if (prev == nullptr){
                    head = newNode;
                    newNode->next = curr;
                } else{
                    prev->next = newNode;
                    newNode->next = curr;
                }
            }
        }

        void display(){
            Node * nodePtr;
            nodePtr = head;
            
            while (nodePtr){
                cout << nodePtr->name << " " << nodePtr->order << " " << endl;

                nodePtr = nodePtr->next;
            }
        }
};

int main(){

    // Line org;
    string filename;
    ifstream infile;
    int num;
    
    cout << endl;
    while(true){
        Line org;
        
        cout << "Enter a filename to view (select CTRL C to exit the program): ";
        getline(cin, filename);

        infile.open(filename);
        while (!infile){
            cout << endl;
            cout << "Please enter a valid filename: ";
            getline(cin, filename);
            infile.close();
            infile.open(filename);
        }

        cout << endl;
        cout << "The file contents are: " << endl << endl;

        while (!infile.eof()){
            string string1, string2;
        
            getline(infile, string1, ' ');
            getline(infile, string2, '\n');

            num = stoi(string2);
            cout << string1 << " " <<  string2 << endl;
            org.Insert(num, string1);
        }

        cout << endl;
        cout << "The original order of the line is: " << endl << endl;
        org.display();
        cout << endl;
        org.~Line();
        infile.close();
    }
    cout << endl << endl;
   
    return 0;
}