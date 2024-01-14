//
// Created by Andy Ng on 11/18/23.
//

#include "Noble.h"
#include "Protector.h"

using namespace std;
namespace WarriorCraft {
//Noble Implementation Code
//
//

// Constructor for the Noble class.
// Initializes the name and strength of the Noble.
// dead is set to false
    Noble::Noble(const string &name, double strength) : name(name), strength(strength), dead(false) {}

    // Getter method for the name of the noble.
    // Returns the noble's name as a const reference string.
    const string& Noble::get_name() const { return name; }

    // Getter method for the strength of the noble.
    // Returns the noble's strength as a double.
    double Noble::get_strength() const { return strength; }

    //takes in a double
    //adds the power it takes in to its strength
    void Noble::add_strength(double power) {
        strength += power;
    }

    //takes in a double
    //subtracts the power it takes in from its strength
    void Noble::minus_strength(double power) {
        strength -= power;
    };

    //takes in a double
    //multiplies strength by ratio
    void Noble::set_strength(double ratio) {
        strength *= ratio;
    }

    //getter method for the alive status of the noble
    //returns true if noble is dead and false otherwise
    bool Noble::is_dead() const { return dead; }

    //sets noble to be dead
    void Noble::kill() { dead = true; }

    //takes in a noble
    void Noble::battle(Noble& noble) {
        cout << name << " battles " << noble.get_name() << endl;
        //if noble is alive cry out
        if (!dead) {
            battle_cry();
        }
        //if noble is alive cry out
        if (!noble.dead) {
            noble.battle_cry();
        }

        //if strength of this noble is greater than strength of the other
        if (strength > noble.get_strength()) {
            if (noble.dead) {
                cout << "He's dead, " << name << endl;
            } else {
                //reduce the strengths of both nobles after battle
                reduce_strength(noble.get_strength());
                noble.reduce_strength(noble.get_strength());
                //weaker noble is killed
                noble.kill();
                cout << name << " defeats " << noble.get_name() << endl;
            }

            //if strength of this noble is less than strength of the other
        } else if (strength < noble.get_strength()) {
            if (dead) {
                cout << "He's dead, " << noble.get_name() << endl;
            } else {
                //reduce the strengths of both nobles after battle
                noble.reduce_strength(strength);
                reduce_strength(strength);
                //weaker noble is killed
                kill();
                cout << noble.get_name() << " defeats " << name << endl;
            }

            //if strength of this noble is equal to the strength of the other
        } else if (strength == noble.get_strength()) {
            if ((dead) && (noble.dead)) {
                cout << "Oh, NO! They're both dead! Yuck!" << endl;
            } else {
                //reduce the strengths of both nobles after battle
                noble.reduce_strength(strength);
                reduce_strength(strength);
                //both nobles are killed
                kill();
                noble.kill();
                cout << "Mutual Annihilation: " << name << " and "
                     << noble.get_name() << " die at each other's hands" << endl;
            }
        }

    }


//Noble output operator
    ostream &operator<<(ostream &os, const Noble &noble) {
        noble.display();
        return os;
    }

//Lord Implementation Code
//
//
//Constructor of lord class
//takes in string
//initializes its name and sets strength to 0
    Lord::Lord(const string &name) : Noble(name, 0) {}

    //output method of Lord
    //outputs its name, size and army
    void Lord::display() const {
        cout << get_name() << " has an army of size: " << army.size() << endl;
        for (size_t i = 0; i < army.size(); ++i) {
            cout << "\t" << *(army[i]);
        }
    }

    //takes in a double
    //reduces the strength to only the ratio of the original strength
    void Lord::reduce_strength(double strength) {
        if (get_strength() == 0) {
            return;
        }
        double ratio = 1 - (strength / get_strength());
        set_strength(ratio);
        // going through the army to reduce the strength of each warrior
        for (size_t i = 0; i < army.size(); ++i) {
            army[i]->reduce_strength(ratio);
        }
    }
    //takes in a protector
    //adds a new protector to its army
    //returns true if successfully hires
    //return false if failed to hire
    bool Lord::hire(Protector& protector) {
        if ((protector.get_lord() == nullptr) && (!is_dead())) {
            army.push_back(&protector); //noble adds the address of the warrior to the army
            protector.change_lord(this);//sets warrior's pointer to noble pointing to address of this noble
            add_strength(protector.get_strength()); // adds the warrior's strength to the noble's strength
            return true;
        }
            //if warrior is hired already or noble is dead noble can't hire warrior
        else {
            cout << get_name() << " failed to hire " << protector.get_name() << endl;
            return false;
        }
    }

    //takes in a protector
    //takes out a  protector from its army
    //returns true if successfully hires
    //return false if failed to hire
    bool Lord::fire(Protector& protector) {
        //if lord is alive
        if (!is_dead()) {
            // checking to see if protector is in the lord's army
            for (size_t i = 0; i < army.size(); ++i) {
                // if protector is in lord's army
                if (army[i] == &protector) {
                    protector.change_lord(nullptr);
                    minus_strength(protector.get_strength());// reduce the lord's strength
                    for (size_t j = i + 1; j < army.size(); ++j) {
                        //shift each protector after the fired protector to the left of army vector
                        army[j - 1] = army[j];
                    }
                    army.pop_back();
                    cout << protector.get_name() << " you dont work for me anymore! -- " << get_name() << endl;
                    return true;
                }
            }
            // if protector is not in army then lord can't fire warrior
            cout << get_name() << " failed to fire " << protector.get_name() << endl;
            return false;

            // if lord is dead then lord can't fire protector
        } else {
            cout << get_name() << " failed to fire " << protector.get_name() << endl;
            return false;
        }
    }

//takes in protector
//takes out protector from army
    void Lord::take_out(Protector *protector) {
        for (size_t i = 0; i < army.size(); ++i) {
            // if protector is in noble's army
            if (army[i] == protector) {
                protector->change_lord(nullptr);//sets protector pointer to lord as a nullptr
                minus_strength(protector->get_strength());// reduce the lord's strength
                for (size_t j = i + 1; j < army.size(); ++j) {
                    //shift each warrior after the fired warrior to the left of army vector
                    army[j - 1] = army[j];
                }
                army.pop_back();
                cout << protector->get_name() << " flees in terror, abandoning his lord, " << get_name() << endl;
            }
        }
    }

    //uses the battle cry method for each protector in battle
    void Lord::battle_cry() {
        for (size_t i = 0; i < army.size(); ++i) {
            army[i]->battle_cry();
        }
    }

//PersonWithStrengthToFight
//
//
    PersonWithStrengthToFight::PersonWithStrengthToFight(const string &name, double strength) : Noble(name, strength) {}

    void PersonWithStrengthToFight::display() const {
        cout << get_name() << " has strength:  " << get_strength() << endl;
    }

    void PersonWithStrengthToFight::reduce_strength(double strength) {
        minus_strength(strength);
    }

    void PersonWithStrengthToFight::battle_cry() {
        cout << "Ugh!" << endl;
    }
}