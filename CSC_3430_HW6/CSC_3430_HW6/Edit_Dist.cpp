/************************************************
	Name: Monica Guevara
	Class: CSC 3430
	Assignment: HW #6
	Date: 3/15/17
************************************************/

//Used geeksforgeeks.org and algorithmist.com as reference

//#include<bits>
#include<iostream>
#include <algorithm>
#include <stdio.h>
#include<stdlib.h>
#include <string>
#include <iomanip>
#include "EditDistHeader.h"

using namespace std;

int v[50][50];	//Stores the matrix or table
char copyStr[100];	//Stores a copy of the first string
char copyStr2[100];	//Stores a copy of the second string
char edits[100];		//Stores the characters that represent the edits
int sizeEdits = 0;	//Stores the size of the edits array


int countd = 0;	//Counts the number of times a letter is deleted from the second string
int counter = 0;	//Counts the number of compairisons

// Finds the minimum of three values
int min(int x, int y, int z)
{
	return min(min(x, y), z);
}

int editDist(string str1, string str2, int m, int n)
{
	// If first string is empty, the only option is to
	// insert all characters of second string into first
	if (m == 0)
	{
		return n;
	}

	// If second string is empty, the only option is to
	// remove all characters of first string
	if (n == 0)
	{
		return m;
	}

	// If last characters of two strings are same.
	// Ignore last characters and get count for
	// remaining strings.
	if (str1[m - 1] == str2[n - 1])
	{
		counter++;
		return editDist(str1, str2, m - 1, n - 1);
	}

	// If last characters are not same, consider all three
	// operations on last character of first string, recursively
	// compute minimum cost for all three operations and take
	// minimum of three values.
	
		counter++;

		return 1 + min(editDist(str1, str2, m, n - 1),// Insert
			editDist(str1, str2, m - 1, n),   // Remove
			editDist(str1, str2, m - 1, n - 1) // Replace
		);
}

//Adds a space in the first string
void addSpace(string str, int index)
{
	for (int i = str.length(); i >= index; i--)
	{
		copyStr[i + 1] = copyStr[i];
	}

	copyStr[index] =' ';
}

//Adds a space in the second string
void delLetter(string str, int index)
{
	countd++;

	for (int i = str.length(); i >= index; i--)
	{
		copyStr2[i + 1] = copyStr2[i];
	}

	copyStr2[index] = ' ';
}

//Adds the characters that represent the edits in the edits array
void addEdits(int index, char c)
{
	if (sizeEdits == 0)
		sizeEdits = index;

	// If the character is 'i' then it moves everything in the array over
	if (c == 'i')
	{
		if (sizeEdits < 100)
		{
			for (int i = sizeEdits; i >= index; i--)
			{
				edits[i + 1] = edits[i];
			}
			edits[index] = c;
			sizeEdits++;
		}
	}

	//else it just stores the character in the array
	else
	{
		edits[index] = c;
	}
		
}

//Displays the strings with the applied formats
void displayFormats(string str2, string str1)
{
	cout << "\nFrom:\t";
	cout << copyStr << "\n";

	cout << "map:\t";
	if (str2.length() != 0)
	{
		for (int i = 0; i <= sizeEdits; i++)
		{
			if (edits[i] != NULL)
				cout << edits[i];
			else
				cout << " ";
		}

		cout << "\t  :i)nsertions, d)eletions, r)eplacements";
		cout << "\nTo:\t" << copyStr2 << "\n\n";
	}

	else
	{
		
		for (int i = 0; i < str1.length() + 1; i++)
		{
			if (edits[i] != NULL)
				cout << edits[i];
			else
				cout << " ";
		}

		cout << "\t: i)nsertions, d)eletions, r)eplacements";
		cout << "\nTo:\t" << copyStr2 << "\n\n";

	}
}

//Displays the table or matrix
void displayTable(int v[50][50], string s1, string s2)
{
	int m = s1.length() + 1;
	int n = s2.length() + 1;

	cout << "     ";
	for (int i = 0; i < n; i++)
	{
		cout << right << setw(2) << i <<" ";
	}

	cout << "\n";
	cout << "     ";
	for (int i = 0; i < s2.length(); i++)
	{
		cout <<right << setw(2) << s2[i] << " ";
	}

	cout << "\n";

	for (int i = 0; i < m; i++)
	{
		cout <<right << setw(2) << i << " " << s1[i] << " ";
		for (int j = 0; j < n; j++)
		{
			cout<<right<< setw(2) << v[i][j] << " ";
		}

		cout << "\n";
	}

}

//Finds the edits to convert s1 to s2
void findEdits(string s1, string s2)
{
	string newstr = s1;
	int m = s1.length() + 1;
	int n = s2.length() + 1;

	int del = 0;
	int ins = 0;
	int rep = 0;

	int i = m - 1;
	int j = n - 1;

	countd = s2.length();

	//If the first string is empty then it just needs
	//to insert everything from the second string
	if (i <= 0)
	{
		while (j >= 1)
		{
			ins = v[i][j - 1];
			addSpace(newstr, j);

			if (sizeEdits == 0)
				sizeEdits = j - 1;

			edits[j - 1] = 'i';

			j = j - 1;
		}
	}

	//Else if the the second is empty then it needs to delete everything
	//from string one
	else if (j <= 0)
	{
		while (i >= 1)
		{
			del = v[i - 1][j];

			if (sizeEdits == 0)
				sizeEdits = i - 1;

			edits[i - 1] = 'd';

			i = i - 1;
		}
	}

	//Else it checks what edits took place
	else
	{
		while (i >= 1)
		{
			while (j >= 1)
			{
				del = v[i - 1][j];
				ins = v[i][j - 1];
				rep = v[i - 1][j - 1];

				//If delete is the minimum
				if (del < ins && del < rep)
				{
					if (del != v[i][j])
					{
						addEdits(i - 1, 'd'); 
						delLetter(copyStr2, j);
					}

					i = i - 1;
				}

				//If insert is the minimum
				else if (ins < del && ins < rep)
				{
					if (ins != v[i][j])
					{
						addSpace(newstr, i);
						addEdits(i, 'i'); 
					}
					j = j - 1;
				}

				//If replace is the minimum
				else if (rep < del && rep < ins)
				{
					if (rep != v[i][j])
					{
						addEdits(i - 1, 'r'); 
					}
					i = i - 1;
					j = j - 1;
				}

				//Checks if rep is equal to insert or replace is equal to delete
				// and it goes diagonally
				else if (ins == rep || del == rep)
				{
					if (rep != v[i][j])
					{
						addEdits(i - 1, 'r');
					}
					i = i - 1;
					j = j - 1;
				}

				//If insert is equal to delete then it goes up
				else if (ins == del)
				{
					if (del != v[i][j])
					{
						addEdits(i - 1, 'd'); 
						delLetter(copyStr2, j);
					}

					i = i - 1;
				}

			}

			//If somehow j is equal to zero but is not then it just moves up or deletes
			if (i >= 1)
			{
				del = v[i - 1][j];

				if (del != v[i][j])
				{
					addEdits(i - 1, 'd'); 
					delLetter(copyStr2, j);
				}

				i = i - 1;
			}
		}
	}
}

// Finds the number of edits
int count(string s1, string s2)
{
	int m = s1.length() + 1;
	int n = s2.length() + 1;

	//Sets counter
	counter = s1.length() * s2.length();

	for (int i = 0; i <= m; i++) 
	{
		v[i][0] = i;
	}

	for (int j = 0; j <= n; j++) 
	{
		v[0][j] = j;
	}

	for (int i = 1; i <= m; i++) 
	{
		for (int j = 1; j <= n; j++) 
		{
			if (s1[i - 1] == s2[j - 1])
				v[i][j] = v[i - 1][j - 1];
			else
				v[i][j] = 1 + min(min(v[i][j - 1], v[i - 1][j]), v[i - 1][j - 1]);
		}
	}

	//Copies s1 to copyStr
	for (int i = 0; i < s1.length(); i++)
	{
		copyStr[i] = s1[i];
	}

	//Copies s2 to copyStr2
	for (int i = 0; i < s2.length(); i++)
	{
		copyStr2[i] = s2[i];
	}

	//Calls the displayTable function
	cout << "\n\nDisplay Table: \n\n";
	displayTable(v, s1, s2);
	cout << "\n\n";
	
	//Calls the findEdits function
	findEdits(s1, s2);

	//Calls the displayFormats function
	displayFormats(s2, s1);

	return v[m][n];
}

// Main
int main()
{
	string str1;
	string str2;

	cout << "Edit Distance: Monica Guevara\n";

	cout << "\nEnter First String: ";
	getline(cin, str1);

	cout << "\nEnter Second String: ";
	getline(cin, str2);

	cout << "\n\nUsing DP Minimum Edits Required to convert: " << str1 << " into " << str2 << "\nis "
		<< count(str1, str2);
	
	cout<<"\nwith " << counter << " character conversions";

	counter = 0;

	if (str1.length() <= 9 && str2.length() <= 9)
	{
		cout << "\n\nUsing Recursion Minimum Edits Required to convert " << str1 << " into " << str2 << "\nis "
			<< editDist(str1, str2, str1.length(), str2.length());
		cout << "\nwith " << counter << " character conversions\n\n";
	}

	else
	{
		cout << "\n\nStrings are too large to process recursively\n\n";
	}

	cout << "\n\nDone\n\n";
	system("pause");
	return 0;
}