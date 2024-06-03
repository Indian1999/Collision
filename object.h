#ifndef OBJECT_H
#define OBJECT_H
#include "coordinate.h"
#define G 6.673*pow(10,-11)

class Object
{
private:
	double mass;
	long long int radius;
	long double velocity;
	long double g;
	long double escapeVelocity;
	Coordinate v;
	Coordinate position;
	long double density;
	double volume;
	string name;
	long double getEscapeVelocity (double m, int r) { return sqrt(2*G*m/r); }
	long double getGAcceleration  (double m, int r) 
	{ 
		long long int r2 = radius*radius;
		return (G*m/r2); 
	}
	long double calculateDensity(double m, int r) 
	{
		double rad = r;
       	double volume(((rad*rad*rad)*M_PI*4)/3);
		return m/volume;
	}
	double calculateVolume(int r)
	{
		double rad = r;
		double ki(((rad*rad*rad)*M_PI*4/3));
		return ki;
	}
public:
	Object()
	{
		mass = 0;
		volume = 0;
		radius = 0;
		velocity = 0;
		g = 0;
		escapeVelocity = 0;
		v = {0,0,0};
		position = {0,0,0};
		density = 0;
		name = "default";
	}
	Object(double m, int r, Coordinate vect, Coordinate pos, long double vel = 0, string nev = "default")
	{
		mass = m;
		radius = r;
		velocity = vel;
		g = getGAcceleration(m,r);
		escapeVelocity = getEscapeVelocity(m,r);
		density = calculateDensity(m,r);
		v = vect;
		position = pos;
		volume = calculateVolume(r);
		name = nev;
	}	
	friend ostream& operator << (ostream& os, const Object& o)
	{
		os << "The properties of the object " << o.name << ":" << "\n" << "Mass: " << o.mass << "\nRadius: " << o.radius << "\nVelocity: " << o.velocity << "\nGravitational force: " << o.g << "\nEscape velocity: " << o.escapeVelocity <<  "\nIt's way of movement: " << o.v << "\nDensity: " << o.density << "\nPosition: " << o.position << "\nVolume: " << o.volume;
		return os;
	}
	long double getVelocity() const { return velocity; }
	long double returnEscapeVelocity() const { return escapeVelocity; } 
	double getMass() const { return mass; }
	long long int getRadius() const {return radius;}
	long double getDensity() const {return density;}
	double getVolume() const {return volume;}
	Coordinate getDirection() const {return v;}
	Coordinate getPosition() const {return position;}
	string getName() const {return name;}
	Object operator + (Object other)
	{
	  /*Új tömeg: az együttes tömegük
		A sűrűség nem változik
		Az új térfogat: Új tömeg/sűrűség
		Új sugár: az új térfogatból számolva */
		double newMass = other.getMass() + mass;
		double newVolume = newMass/density;
		int newRadius = cbrt((3*newVolume)/(4*M_PI));
		Object ki(newMass,newRadius,this->getDirection(),position,velocity,name);
		return ki;
	}
};


#endif
