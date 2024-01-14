//
// Created by Andy Ng on 11/18/23.
//

#ifndef CS2124_NOBLE_H
#define CS2124_NOBLE_H

#include <iostream>
#include <string>
#include <vector>

namespace WarriorCraft {
    class Protector;

    class Noble {
        //Noble output operator prototype
        //Friend keyword is used to allow access to private data members
        friend std::ostream &operator<<(std::ostream &os, const Noble &noble);

    public:
        //Noble constructor prototype
        Noble(const std::string &name, double strength);


        virtual void reduce_strength(double strength) = 0;

        virtual void battle_cry() = 0;

        virtual void display() const = 0;

        const std::string& get_name() const;

        double get_strength() const;

        void set_strength(double ratio);

        bool is_dead() const;

        void kill();

        void battle(Noble &noble);

        void add_strength(double power);

        void minus_strength(double power);


    private:
        std::string name;
        double strength;
        bool dead;
    };

    class Lord : public Noble {
    public:
        Lord(const std::string &name);

        void display() const;

        void reduce_strength(double strength);


        bool hire(Protector &protector);

        bool fire(Protector &protector);

        void take_out(Protector *protector);

        void battle_cry();

    private:
        std::vector<Protector*> army;
    };

    class PersonWithStrengthToFight : public Noble {
    public:
        PersonWithStrengthToFight(const std::string& name, double strength);

        void display() const;

        void reduce_strength(double strength);

        void battle_cry();
    };

}

#endif //CS2124_NOBLE_H
