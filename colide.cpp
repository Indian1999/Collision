#include <vector>
#include <ctime>
#include <fstream>
#include "object.h"
#define G 6.673*pow(10,-11)

/* 
Tasklist/Ideas:
	-If it's on a collision course, then collide no matter the velocity
		-> The two vectors meet
		-> The two objects are at the meeting point at the same time
		-> object's radius added to the two vector's distance
	-Implement relative distance, if the object is further from a really large objects, but closer to a smaller one, then it should still crash into the larger one
	-The user could choshe amount of bodies, the average properties of the objects etc.
        -Object örököltetáse:
		->Csillagok                       -> csillag típusok
		->Bolygók (+ Hold és Törpebolygó) -> bolygó típusok
		->Kisbolygók 
	-Random object generálás szépítése
	-Bemenet txt?
	-Txt be mentsük el a generált objektumokat
	-Txt be csináljunk kimenetet
	-Távoli cél: grafikus felület
*/

int findClosest(int &ind, vector<vector<int>> &mtx)
{
	int mini;
	if (ind == 0)
	{
		mini = 1;
	}
	else
	{
		mini = 0;
	}
	
	for	(int i = 1; i < mtx.size(); i++)
	{
		if (mtx[ind][i] < mtx[ind][mini] && mtx[ind][i] != 0) mini = i;	
	}
	if(mtx[ind][mini] == 0 ) return -1;
	return mini;
}

int main()
{
	cout << "How many objects would you like to generate?\n";
	int objectCount;
	cin >> objectCount;
	vector<Object> objects;
	ofstream f;
	f.open("Generalt_objektumok.txt");
	// "random" objektumok generálása
	for (int i = 0; i < objectCount; i++)
	{
		srand((int) time(0) * i % 5243);
		long long int sugar = (rand() % 50000 + 1000) * 1000;
		double velocityAlap = rand() % 9 + 1;
		int velocityKitevo = rand() % 8 + 2;
		double velocity = velocityAlap*pow(10,velocityKitevo);
		int alap = rand() % 9 + 1;
		int kitevo = rand() % 25 + 5;
		double tomeg = alap*pow(10,kitevo);
		double vx = rand() % 100 + 0;
		double vy = rand() % 100 + 0;
		double vz = rand() % 100 + 0;
		double x = (rand() % 100 + 0) * pow(10,11);
		double y = (rand() % 100 + 0) * pow(10,11);
		double z = (rand() % 100 + 0) * pow(10,11);
		Coordinate ve {vx,vy,vz};
		Coordinate pos {x,y,z};
		string name = "object no. " + to_string(i+1);
		Object objektum(tomeg,sugar,ve,pos,velocity,name);
		objects.push_back(objektum);
		f << objektum;
		//cout << objektum << endl;
	}
	f.close();
	// Kiszámoljuk az objektumok távolságát egymástól
	vector<vector<int>> distances;
	for(int i = 0; i < objects.size(); i++)
	{
		vector<int> vec;
		for(int j = 0; j < objects.size(); j++)
		{
			vec.push_back(objects[i].getPosition().distance(objects[j].getPosition()));
		}
		distances.push_back(vec);
	}
	f.open("Collisions.txt");
	// Velocity-escape velocity összehasonlítása
	for (int i = 0; i < objects.size(); i++)
	{
		bool found = false;
		int closest = findClosest(i,distances);
		while(!found && closest != -1) // ha closest = -1, akkor egy objectum escape velocitije sem elég nagy -> kilépünk
		{
			if(objects[closest].returnEscapeVelocity() < objects[i].getVelocity())
			{
				distances[i][closest] = 0;
			}
			else
			{
				objects[closest] = objects[closest] + objects[i];
				cout << objects[i].getName() << " crashed into " << objects[closest].getName() << endl;
				f << objects[i].getName() << " crashed into " << objects[closest].getName() << endl;
				objects.erase(objects.begin()+i);
				i--;
				found = true;
			}
			closest = findClosest(i,distances);
		}
	}
	f.close();
	f.open("Remaining_objects.txt");
	// A fennmaradó objektumok:
	cout << "The remaining objects: (" << objects.size() << "/" << objectCount << ")\n";
	for(int i = 0; i < objects.size(); i++)
	{
		cout << objects[i].getName() << endl;
		f << objects[i].getName() << endl;

	}
    return 0;
}
