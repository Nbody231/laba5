#include "BTree.h"
#include <conio.h>
#include <iostream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
using namespace std;

int main()
{
	BTree<int> tree;
	int operation;
	int tmp, tmp1;
	while (true)
	{
		cout << " Binary Search Tree Operations " << endl;
		cout << " ----------------------------- " << endl;
		cout << " 1. Add " << endl;
		cout << " 2. Search " << endl;
		cout << " 3. Remove " << endl;
		cout << " 4. Destroy " << endl;
		cout << " 5. Show " << endl;
		cout << " 6. Exit " << endl;
		cout << " Enter your choice : ";
		cin >> operation;
		switch (operation)
		{
		case 1: cout << " Enter data to be added : ";
			cin >> tmp;
			tree.Add(tmp);
			break;
		case 2: cout << " Enter data to be searched : ";
			cin >> tmp;
			tree.Search(tmp);
			break;
		case 3: cout << " Enter data to be deleted : ";
			cin.ignore(1);
			cin >> tmp1;
			tree.Remove(tmp1);
			break;
		case 4: 
			tree.MakeEmpty();
			break;
		case 5: cout << " Binary Search Tree : " << endl;
			tree.Show();
			cout <<"\n -----------------------------"<<endl;
			break;
		
		case 6: system("pause");
			return 0;
			break;
		}
	}
}