//
// Created by Andy Ng on 11/18/23.
//

#include "Protector.h"
#include "Noble.h"

using namespace std;
namespace WarriorCraft {


//Protector Implementation Code
//
//

// Constructor for the Protector class
// Initializes the name and strength of the warrior
// Sets it pointer to Lord as nullptr

    Protector::Protector(const string &name, double strength) : name(name), strength(strength), lord(nullptr) {}

// Getter method for the strength of the protector.
// Returns the protector's strength as a double.
    double Protector::get_strength() const { return strength; }

// Getter method for the name of the protector.
// Returns the protector's name as a string.
    const string &Protector::get_name() const { return name; }

//takes in a ratio of type double of the strength that remains after battle
//multiplies the strength with the ratio to get a new strength
//doesn't return anything, void method
    void Protector::reduce_strength(double ratio) { strength *= ratio; }


//does not take in any parameters
//doesn't return anything, void method
//utilizes Lord's take_out() method to remove the lord
//utilizes Lord's take_out() method to remove protector from army
    void Protector::runaway() {
        if (lord != nullptr) { //if warrior is currently hired by a noble
            //use noble's method to remove warrior from noble's army
            //warrior is no longer hired by this noble
            lord->take_out(this);
        }
    }

//takes in a pointer to a noble
//doesn't return anything, void method
//changes protector's pointer to lord to point to the address that is passed in
    void Protector::change_lord(Lord *boss) {
        lord = boss;
    }

    //doesn't take in anything
    //getter method for the lord that the protector is hired by
    //returns a pointer to a Noble
    Noble* Protector::get_lord() const {
        return lord;
    }

    //doesn't take in anything
    //getter method for the lord's name
    //returns a const-by-reference string
    const string& Protector::get_lord_name() const {
        return lord->get_name();
    }




// Output operator for the Protector class.
// Takes an ostream object and a const Protector object.
// Outputs the protector's name and strength to the ostream
// Returns the modified ostream object.
    ostream &operator<<(ostream &os, const Protector &protector) {
        os << protector.name << " has strength " << protector.strength << endl;
        return os;
    }


//Wizard Implementation Code
//
//

// Constructor for the Wizard class.
// Initializes the name and strength of the Wizard.
    Wizard::Wizard(const string& name, int strength) : Protector(name, strength) {}

    //Wizard's battle cry method
    //Doesn't take in any parameters
    //Makes a certain sound when defending in battle
    void Wizard::battle_cry() {
        cout << "POOF!" << endl;
    }

//Warrior Implementation Code
//
//

//Constructor for Warrior class
// Initializes the name and strength of Warrior
    Warrior::Warrior(const string &name, int strength) : Protector(name, strength) {}

    void Warrior::battle_cry(){
        cout << " says: Take that in the name of my lord, " << get_lord_name() << endl;
    }
//Archer Implementation Code
//
//

//Constructor for Archer class
//Initializes the name and strength of Archer
    Archer::Archer(const string &name, int strength) : Warrior(name, strength) {}

    //Archer's battle cry method
    //Doesn't take in any parameters
    //Makes a certain sound and talks when defending in battle
    void Archer::battle_cry() {
        cout << "TWANG!" << get_name();
        Warrior::battle_cry();
    }

//Swordsman Implementation Code
//
//

//Constructor for Swordsman class
//Initializes the name and strength of Swordsman
    Swordsman::Swordsman(const string &name, int strength) : Warrior(name, strength) {}

    //Swordsman's battle cry method
    //Doesn't take in any parameters
    //Makes a certain sound and talks when defending in battle
    void Swordsman::battle_cry() {
        cout << "CLANG!" << get_name();
        Warrior::battle_cry();
    }
}