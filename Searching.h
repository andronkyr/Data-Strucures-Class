#include "File Actions.h"

#include <math.h> 

int BinarySearch(vector<Company*> myVector, int searchTerm, int left, int right)
{
	if (left > right)
		return -1;
	else
	{
		int mid = (left + right) / 2;
		if (myVector[mid]->id > searchTerm)
			return BinarySearch(myVector, searchTerm, left, mid - 1);
		else if (myVector[mid]->id < searchTerm)
			return BinarySearch(myVector, searchTerm, mid + 1, right);
		else
			return mid;
	}
}

int searchByID(vector<Company*> myVector, int choice,int searchTerm)
{
	int left, right, size, next;
	bool found = false;
	switch (choice)
	{
	case 1:		//Linear search	
		for (int i = 0; i < myVector.size(); i++)
		{
			if (myVector[i]->id == searchTerm)
			{				
				found = true;
				return i;
			}
		}	
		if (found == false)
		{
			return -1;
		}
		break;
	case 2:		//Binary search
		return  BinarySearch(myVector, searchTerm,0, myVector.size()-1);
	case 3:		//Binary Interpolation Search
		if ((searchTerm > myVector[myVector.size() - 1]->id) || (searchTerm < myVector[0]->id))		//checks for an id that is out of the available id's
			return -1;
		else
		{
			left = 0;
			right = myVector.size() - 1;
			size = right - left + 1;
			next = (int)(size*(searchTerm - myVector[left]->id) / (myVector[right]->id - myVector[left]->id)) + 1;
			//if searchTerm is the last or the one before that company (the fraction will be equal to 1 and the vector will be non legally indexed		
			if (next == size + 1)
			{
				if (searchTerm == myVector[myVector.size() - 1]->id)
					return myVector.size() - 1;
				else
					break;
			}
			else if (next == size)
			{
				if (searchTerm == myVector[myVector.size() - 2]->id)
					return myVector.size() - 2;
				else
					break;
			}
			while ((searchTerm != myVector[next]->id)&&(next>=0))
			{
				int i = 0;
				size = right - left + 1;
				if (size < 5)
				{
					for (int j = left; j <= right; j++)
					{
						if (myVector[j]->id == searchTerm)
							return j;
					}
					return -1;
				}
				if (searchTerm >= myVector[next]->id)
				{
					if (next == 0)
						break;
					while (searchTerm > myVector[next + (int)i*sqrt(size) - 1]->id)
					{
						i++;
						if ((next + (int)i*sqrt(size) - 1) > (myVector.size() - 1))
						{
							i--;
							break;
						}
					}
					
					right = next + i*(int)sqrt(size);
					left = next + (i - 1)*(int)sqrt(size);
				}
				else if (searchTerm < myVector[next]->id)
				{
					if (next == myVector.size() - 1)
					{
						if (searchTerm == myVector[myVector.size() - 3]->id)
							return myVector.size() - 3;
						else
							break;
					}
					while (searchTerm < myVector[next - (int)i*sqrt(size) + 1]->id)
					{
						i++;
						if ((next - (int)i*sqrt(size) + 1) < 0)
						{
							i--;
							break;
						}
					}
					right = next - (i-1)*(int)sqrt(size);
					left = next - i *(int)sqrt(size);
				}
				next = left + (int)((right - left + 1)*(searchTerm - myVector[left]->id) / (myVector[right]->id - myVector[left]->id)) - 1;
				
			}
			if (searchTerm == myVector[next]->id)
				return next;
			else
				return -1;
		}	
	}	
}