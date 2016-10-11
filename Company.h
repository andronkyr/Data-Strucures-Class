#include "Employee.h"
#include <vector>

class Company
{
public:
	int id=0;
	string title="";
	string summary="";
	int numberOfEmployees=0;
	vector<Employee*> Employees;


	~Company(){}

	void printInfo()
	{
		cout << "ID : " << this->id << endl;
		cout << "Title : " << this->title << endl;
		cout << "Summary : " << this->summary << endl;
		cout << "Employees :" << endl;
		for (int j = 0; j < this->numberOfEmployees; j++)
		{
			cout << "Name : " << Employees[j]->firstName << endl;
			cout << "Last Name : " << Employees[j]->lastName << endl;
		}
		cout << "\n";
	}	
};

bool compByID (Company* c1,Company* c2) 
{
	return (c1->id < c2->id);
}