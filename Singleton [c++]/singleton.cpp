/********************************************
 * @author: Izabela Orlowska                *
 *                                          *
 * Example of a singleton design pattern    *
 ********************************************/

#include <iostream>
#include <cstdio>
#include <stdio.h>

using namespace std;

class Singleton
{
    private:
        static Singleton* instance;
        static bool isCreated;
        Singleton()
        {
            cout << "Singleton instance created" << endl;
        };
        
    public:
        static Singleton* getInstance()
        {
            if (!isCreated)
            {
                instance = new Singleton();
                isCreated = true;
            }
            else
            {
                cout << "Returning already existing Singleton instance" << endl;
            }
            return instance;
        };
};

bool Singleton::isCreated = false;
Singleton* Singleton::instance = NULL;

using namespace std;

int main() {
    Singleton* first    = Singleton::getInstance();
    Singleton* second   = Singleton::getInstance();
    Singleton* third    = Singleton::getInstance();
    return 0;
}