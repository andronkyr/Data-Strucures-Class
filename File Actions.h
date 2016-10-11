#include "DigitalTries.h"

int ToInteger(const std::string& s)
{
	std::istringstream in(s);

	int returnValue;
	in >> returnValue;

	return returnValue;
}

Companies* loadCompanies(string path)
{
	fstream file;
	int size;
	string temp;
	Companies* companies = new Companies();
	file.open(path.c_str());
	if (file.is_open())
	{
		getline(file, temp);
		size = ToInteger(temp);
		if (size >= 0)
			companies->numberOfCompanies = size;
		else
			size = 0;
		for (int i = 0; i < size; i++)
		{
			companies->myVector.push_back(new Company());
			getline(file, temp, ';');
			companies->myVector[i]->id = atoi(temp.c_str());
			getline(file, companies->myVector[i]->title, ';');
			getline(file, companies->myVector[i]->summary, ';');
			getline(file, temp, ';');
			companies->myVector[i]->numberOfEmployees = atoi(temp.c_str());
			for (int j = 0; j < companies->myVector[i]->numberOfEmployees; j++)
			{
				companies->myVector[i]->Employees.push_back(new Employee());
				getline(file, companies->myVector[i]->Employees[j]->firstName, ' ');
				if (j < 6)
					getline(file, companies->myVector[i]->Employees[j]->lastName, ';');
				else
					getline(file, companies->myVector[i]->Employees[j]->lastName, '\n');
			}
			if (companies->myVector[i]->numberOfEmployees < 7)
			{
				getline(file, temp, '\n');
			}
		}
		file.close();
		return companies;
	}
	else
		return NULL;
}

void writeFile(string path,Companies* companies)
{
	ofstream file;
	file.open(path.c_str(), std::ofstream::trunc);
	file << companies->numberOfCompanies <<endl;
	for (int i = 0; i < companies->numberOfCompanies; i++)
	{
		file << to_string(companies->myVector[i]->id) + ";";
		file << companies->myVector[i]->title + ";";
		file << companies->myVector[i]->summary + ";";
		file << to_string(companies->myVector[i]->numberOfEmployees) + ";";
		for (int j = 0; j < companies->myVector[i]->numberOfEmployees; j++)
		{
			file << companies->myVector[i]->Employees[j]->firstName + " " + companies->myVector[i]->Employees[j]->lastName;
			if (j == companies->myVector[i]->numberOfEmployees - 1)
				file << endl;
			else
				file << ";";
		}
	}
	file.close();
}