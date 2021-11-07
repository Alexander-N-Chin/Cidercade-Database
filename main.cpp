/****************************************************************************************************************

Alexander N. Chin | NetID: ANC200008
CS 2337.002 Jason Smith
Project 3 ""Cidercade database" Final Submission
11/6/2021

*****************************************************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

#include "BinTree.h"
#include "Game.h"
#include "Node.h"
using namespace std;
//prints the statistics of the given node and formats it according to the project description
void printStats(Node<Game>* node) {
    int highscore = stoi(node->getData().getHigh_score());
    cout << "High Score: " << highscore << endl;
    cout << "Initials: " << node->getData().getInitials() << endl;
    cout << "Plays: " << node->getData().getPlays() << endl;
    cout << "Revenue: $" << node->getData().getPlays() * 0.25 << endl;

    //print 2 empty lines
    cout << endl << endl;
}

//updates the value of a record dictated by the inputed field number an
void updateRecord(BinTree<Game>& tree, int field, string value, Game& game, Node<Game>* node) {
    int plays;
    node = tree.searchNode(game);
    //case: node not found
    if (!node) {
        cout << game.getName() << " NOT FOUND" << endl;
        return;
    }
    cout << game.getName() << " UPDATED" << endl;
    //uses given field as switch case expression
    switch (field) {
        case 1:
            //high score
            cout << "UPDATE TO high score - VALUE " << value << endl;
            node->getData().setHigh_score(value);
            break;
        case 2:
            //initials
            cout << "UPDATE TO initials - VALUE " << value << endl;
            node->getData().setInitials(value);
            break;
        case 3:
            //plays
            cout << "UPDATE TO plays - VALUE " << value << endl;
            plays = stoi(value);
            node->getData().setPlays(plays);
            break;
    }
    printStats(node);
}

//reads the initial database and creates a binary tree with nodes from each line.
void readInputFile(ifstream& in, BinTree<Game>& tree) {
    string temp, name, highscore, initials;
    int plays;
    while (getline(in, temp)) {
        if (!temp.empty()) {
            //takes each line and makes a string stream with it to parse into a new node and inserts it into the tree
            stringstream ss(temp);
            getline(ss, name, ',');
            getline(ss, highscore, ',');
            getline(ss, initials, ',');
            getline(ss, temp, ',');
            plays = stoi(temp);
            Game game(name, highscore, initials, plays);
            Node<Game>* node = new Node<Game>(game);
            tree.insertNode(node);
        }
    }
}

//reads the batch commands file and uses a switch case to decipher which command to execute.
void readCommandsFile(ifstream& in, BinTree<Game>& tree) {
    string temp, temp2, name, highscore, initials, value;
    int field, field2, plays;
    bool found = false;
    vector<Node<Game>*> a;
    Node<Game>* node;
    Game game;
    while (getline(in, temp)) {
        //adds line to string stream to assist parsing
        stringstream ss(temp);
        ss >> field;
        //uses the first character as a switch case expression
        switch (field) {
            case 1:
                //Add a record given
                //1 "name" high-score initials plays $revenue
                getline(ss, name, '\"');
                getline(ss, name, '\"');
                ss >> highscore >> initials >> temp;
                plays = stoi(temp);
                game.setName(name);
                game.setHigh_score(highscore);
                game.setInitials(initials);
                game.setPlays(plays);
                node = new Node<Game>(game);
                tree.insertNode(node);
                cout << "RECORD ADDED" << endl;
                cout << "Name: " << node->getData().getName() << endl;
                printStats(node);
                break;
            case 2:
                //search for a name
                //2 name
                getline(ss, temp);
                temp.erase(0,1);
                game.setName(temp);
                a = tree.vectorizeInOrder();
                for (int i = 0; i < (int)a.size(); i++) {
                    if (game == a[i]->getData()) {
                        found = true;
                        cout << a[i]->getData().getName()<< " FOUND" << endl;
                        printStats(a[i]);
                    }
                }
                if (!found) {
                    cout << temp << " NOT FOUND" << endl;

                    //display 2 empty lines after each command
                    cout << endl << endl;
                }
                found = false;
                break;
            case 3:
                //update a field with a new value
                //3 "name" field value
                getline(ss, name, '\"');
                getline(ss, name, '\"');
                game.setName(name);
                ss >> field2 >> value;
                updateRecord(tree, field2, value, game, node);
                break;
            case 4:
                //delete a record
                //4 name
                getline(ss, name);
                name.erase(0,1);
                game.setName(name);
                node = tree.removeNode(game);
                if (!node) {
                    //case: node not found
                    cout << name << " NOT FOUND" << endl;

                    //display 2 empty lines after each command
                    cout << endl << endl;
                    break;
                }
                cout << "RECORD DELETED" << endl;
                cout << "Name: " << node->getData().getName() << endl;
                printStats(node);
                break;
            case 5:
                //display sorted record in alphabetical order
                //5 <asc/des>
                getline(ss, temp);
                temp.erase(0,1);
                if (temp == "asc") {
                    cout << "RECORDS SORTED ASCENDING" << endl;
                    tree.displayInOrder(cout, false);
                } else {
                    cout << "RECORDS SORTED DESCENDING" << endl;
                    tree.displayInOrder(cout, true);
                }
                //display 2 empty lines after each command
                cout << endl << endl;
                break;
        }
    }
}

int main() {
    ifstream in;
    ofstream out;
    string dataName, commandsName;
    BinTree<Game> tree;

    cout << fixed << setprecision(2);               //formatting at the beginning
    cout << "Enter initial database filename: ";    //prompt user for filenames
    cin >> dataName;
    cout << "Enter batch command filename: ";
    cin >> commandsName;
    cout << endl;

    //open and read each file
    in.open(dataName);
    if (in.is_open()) {
        readInputFile(in, tree);
    } else {
        cout << "ERROR: could not open input database file" << endl;
    }
    in.close();

    in.open(commandsName);
    if (in.is_open()) {
        readCommandsFile(in, tree);
    } else {
        cout << "ERROR: could not open commands file" << endl;
    }
    in.close();

    //open output file and write breadth first traversal to the file
    out.open("cidercade.dat");
    if (out.is_open()) {
        tree.displayBreadthFirst(out);
    } else {
        cout << "ERROR: could not open output database file" << endl;
    }
    out.close();

    return 0;
}
