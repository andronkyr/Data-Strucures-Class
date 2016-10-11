#include "AVL.h"
#include <algorithm>
#include <string>

int main()
{
	int choice,size=0,i=0,j=0,tries=0,pointer=0,searchID=0;
	fstream file;
	string input,temp,searchTerm;
	bool done=false,found=false;
	Trie* DTree = new Trie();
	AVLTree* ATree = new AVLTree();
	Companies* companies = new Companies();
	do{
		cout << "1. Load companies from file" << endl;
		cout << "2. Save companies to file" << endl;
		cout << "3. Add a company" << endl;
		cout << "4. Delete a company by id" << endl;
		cout << "5. Display a company by id" << endl;
		cout << "6. Display Companies " << endl;
		cout << "7. Display Companies by surname search" << endl;
		cout << "8. Exit" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Please insert the name of the file (add .csv at the end of the filename)" << endl;
			cin >> input;
			companies = loadCompanies(input);
			if (companies != NULL){
				for (int i = 0; i < companies->myVector.size(); i++)
				{
					for (int j = 0; j < companies->myVector[i]->numberOfEmployees; j++)
					{
						string temp = companies->myVector[i]->Employees[j]->lastName;
						DTree->insert(companies->myVector[i], temp);
					}
				}
				for (int i = 0; i < companies->myVector.size(); i++)
				{
					ATree->root = ATree->insert(ATree->root, companies->myVector[i]);
				}
				cout << "File sucessfully loaded!" << endl;
			}
			else
				cout << "Unable to load file! Please try again" << endl;
			break;
		case 2:
			cout << "Please insert the name of the file to be written (add .csv at the end of the filename)" << endl;
			cin >> input;
			sort(companies->myVector.begin(), companies->myVector.end(), compByID);
			writeFile(input, companies);
			cout << "File updated sucessfully!" << endl;
			break;
		case 3:
			size = companies->numberOfCompanies;
			tries = 0;
			companies->myVector.push_back(new Company());
			do{
				done = true;
				if (tries == 0)
					cout << "Please insert id " << endl;
				else
					cout << "Not available id. Please try again" << endl;
				cin >> companies->myVector[size]->id;
				for (int i = 0; i < size; i++)
				{
					if (companies->myVector[size]->id == companies->myVector[i]->id)
					{
						done = false;
						tries++;
						break;
					}
				}
			} while (done == false);
			done = false;
			cin.ignore(1000, '\n');
			cout << "Please insert title \n";
			getline(std::cin, companies->myVector[size]->title);
			cout << "Please insert summary \n";
			getline(std::cin, companies->myVector[size]->summary);
			cout << "Please insert number of employees" << endl;
			cin >> companies->myVector[size]->numberOfEmployees;
			for (int i = 0; i < companies->myVector[size]->numberOfEmployees; i++)
			{
				companies->myVector[size]->Employees.push_back(new Employee());
				cout << "Please insert firstname for Employee " << i + 1 << endl;
				cin >> companies->myVector[size]->Employees[i]->firstName;
				cout << "Please insert lastname for Employee " << i + 1 << endl;
				cin >> companies->myVector[size]->Employees[i]->lastName;
				string temp = companies->myVector[size]->Employees[i]->lastName;
				DTree->insert(companies->myVector[size], temp);
				ATree->insert(ATree->root, companies->myVector[size]);
			}
			companies->numberOfCompanies++;
			break;
		case 4:
			cout << "Please enter desired type of search" << endl;
			cout << "1.Linear search" << endl;
			cout << "2.Binary search" << endl;
			cout << "3.Binary interpolation search" << endl;
			cout << "4.AVL Tree Search" << endl;
			cin >> choice;
			pointer = 0;
			if (choice > 4 || choice < 1)
				cout << "Not available choice. Please try again!" << endl;
			else
			{
				cout << "Please enter id" << endl;
				cin >> searchID;
				if (choice < 4)
				{
					sort(companies->myVector.begin(), companies->myVector.end(), compByID);
					pointer = searchByID(companies->myVector, choice, searchID);
					if (pointer != -1)
					{
						delete(companies->myVector[pointer]);
						companies->myVector.erase(companies->myVector.begin() + pointer);
						companies->numberOfCompanies--;
						ATree->root = ATree->Delete(ATree->root, searchID);
						cout << "Company Successfully Deleted !" << endl;
					}
					else
						cout << "Company Not Found !" << endl;
				}
				else
				{
					ATree->root = ATree->Delete(ATree->root, searchID); 
					pointer = searchByID(companies->myVector, 2, searchID);
					if (pointer != -1)
					{
						delete(companies->myVector[pointer]);
						companies->myVector.erase(companies->myVector.begin() + pointer);
						companies->numberOfCompanies--;
						cout << "Company Successfully Deleted !" << endl;
					}
					else
						cout << "Company Not Found !" << endl;
				}
			}
			break;
		case 5:
			cout << "Please enter desired type of search" << endl;
			cout << "1.Linear search" << endl;
			cout << "2.Binary search" << endl;
			cout << "3.Binary interpolation search" << endl;
			cout << "4.AVL Tree Search" << endl;
			cin >> choice;
			if (choice > 4 || choice < 1)
				cout << "Not available choice. Please try again!" << endl;
			else
			{
				cout << "Please enter id" << endl;
				cin >> searchID;
				if (choice < 4)
				{
					sort(companies->myVector.begin(), companies->myVector.end(), compByID);
					pointer = searchByID(companies->myVector, choice,searchID);
					if (pointer != -1)
						companies->myVector[pointer]->printInfo();
					else
						cout << "Company Not Found !" << endl;
				}
				else
					ATree->SearchAVL(ATree->root, searchID);
			}
			break;
		case 6:
			for (int i = 0; i < companies->numberOfCompanies; i++)
				companies->myVector[i]->printInfo();
			break;
		case 7:
				found = false;				
				cout << "Please enter surname" << endl;
				cin >> searchTerm;
				cout << "Please enter type of search" << endl;
				cout << "1.Linear Search" << endl;
				cout << "2.Digital Trie Search" << endl;
				cin >> choice;
				switch (choice)
				{					
				case 1:
					for (int i = 0; i < companies->numberOfCompanies; i++)
					{
						for (int j = 0; j < companies->myVector[i]->numberOfEmployees; j++)
						{
							if (companies->myVector[i]->Employees[j]->lastName == searchTerm)
							{
								cout << searchTerm + " works for " + companies->myVector[i]->title << endl;
								found = true;
							}
						}
					}
					break;
				case 2:
					found= DTree->search(searchTerm);
					break;
				}
				if (found == false)
					cout << "This employee doesn't exist" << endl;
				break;
		case 8:
			done = true;
			delete DTree;
			delete ATree;
			sort(companies->myVector.begin(), companies->myVector.end(), compByID);
			writeFile("backup.csv", companies);
			cout << "A backup never harmed anyone ! Companies automatically saved to backup.csv" << endl;
			break;
		default:
			cout << "Not available option, please try again " << endl;
		}
	} while (done == false);
	system("pause");
}

