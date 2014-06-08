/********************************************
 * @author: Izabela Orlowska                *
 *                                          *
 * Example of an adapter design pattern     *
 ********************************************/

#include <iostream>
#include <list>

using namespace std;

class LegacyCar
{
    private:
        int x, y;
    public:
        LegacyCar(int x, int y)
        {
            this->x = x;
            this->y = y;
        }
        void drive(int x1, int y1)
        {
            this->x += x1;
            this->y += y1;
        }
        int getX()
        {
            return x;
        }
        int getY()
        {
            return y;
        }
};

class Vehicle
{
    private:
        LegacyCar* car;
        int id;
    public:
        Vehicle(int id, int x, int y)
        {
            this->car = new LegacyCar(x,y);
            this->id = id;
        }
        void moveTo(int x2, int y2)
        {
            car->drive(x2 - car->getX(), y2 - car->getY());
        }  
        int getX()
        {
            return car->getX();
        }
        int getY()
        {
            return car->getY();
        }
        int getID()
        {
            return id;
        }
};

class RaceTrack
{
    private:
        list<Vehicle*> vehicles;
        
        Vehicle* getCar(int id)
        {
            for (list<Vehicle*>::iterator it = vehicles.begin(); 
                        it != vehicles.end(); ++it)
            {
                if (id == (*it)->getID())
                {
                    return (*it);
                }
            }
            cout << "Car with ID " << id << " doesn't exist in this RaceTrack" 
                    << endl;
            return NULL;
        }
    public:
        void addCar(Vehicle* car)
        {
            vehicles.push_back(car);
        }
        void removeCar(Vehicle* car)
        {
            vehicles.remove(car);
        }
        void moveCarTo(int carID, int x, int y)
        {
            Vehicle* car = getCar(carID);
            if (car != NULL)
            {
                car->moveTo(x,y);
            }
        }
        void printCarPosition(int carID)
        {
            Vehicle* car = getCar(carID);
            if (car != NULL)
            {
                cout << "(" << car->getX() << "," << car->getY() << ")" << endl;
            }
        }
};


int main() 
{
    Vehicle* car = new Vehicle(0, 10,-10);
    Vehicle* car2 = new Vehicle(1,0,0);
    
    RaceTrack* track = new RaceTrack();
    track->addCar(car);
    track->addCar(car2);
    track->moveCarTo(0, 7,7);
    track->printCarPosition(0);
    track->moveCarTo(1, -42, 42);
    track->printCarPosition(1);
    track->printCarPosition(2);
	return 0;
}