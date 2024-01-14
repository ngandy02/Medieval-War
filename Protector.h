//
// Created by Andy Ng on 11/18/23.
//

#ifndef CS2124_PROTECTOR_H
#define CS2124_PROTECTOR_H


#include <iostream>
#include <string>
#include <vector>

namespace WarriorCraft {

    class Noble;

    class Lord;

    class Protector {
        //Protector output operator prototype
        //Friend keyword is used to allow access to private data members
        friend std::ostream &operator<<(std::ostream &os, const Protector &protector);
    public:
        //Protector constructor prototype
        Protector(const std::string &name, double strength);

        //Protector virtual battle_cry method
        virtual void battle_cry() = 0;

        //Protector strength getter method prototype
        double get_strength() const;

        //Protector name getter method prototype
        const std::string& get_name() const;

        //Protector reduce_strength prototype
        void reduce_strength(double ratio);

        //Protector runaway prototype
        void runaway();

        //Protector change_lord prototype
        void change_lord(Lord *boss);

        //Protector Lord getter method prototype
        Noble* get_lord() const;

        //Protector Lord name getter method prototype
        const std::string& get_lord_name() const;


    private:
        std::string name;
        double strength;
        Lord* lord;

    };

    class Wizard : public Protector {
    public:
        //Wizard constructor prototype
        Wizard(const std::string &name, int strength);

        //Wizard battle_cry() prototype
        void battle_cry();
    };

    class Warrior : public Protector {
    public:
        //Warrior constructor prototype
        Warrior(const std::string &name, int strength);
        void battle_cry();
    };

    class Archer : public Warrior {
    public:
        //Archer constructor prototype
        Archer(const std::string &name, int strength);

        //Archer battle_cry() prototype
        void battle_cry();
    };

    class Swordsman : public Warrior {
    public:
        //Swordsman constructor prototype
        Swordsman(const std::string &name, int strength);

        //Swordsman battle_cry() prototype
        void battle_cry();
    };

}
#endif //CS2124_PROTECTOR_H
