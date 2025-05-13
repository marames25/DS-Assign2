#include <bits/stdc++.h>
using namespace std;

#define size 1000
string backStack[size] ;
string forwardStack[size] ;
int top1 = -1 , top2 = -1 ;

void visit(string url)
{
    top1=-1;
    if (top2 == size-1)
    {
        cout<<"Stack Overflow."<<endl;
    }
    else
    {
        if (backStack[top2]==url)
        {
            cout<<"You are already visiting URL: " << url<<endl;
        }
        else {
            top2++;
            backStack[top2] = url;
            cout << "Visited: " << url << endl;
        }
    }
}
string go_Back()
{
    if (top2 <= 0)
    {
        cout<<"Going back is not possible.";
        return "";
    }
    else {
        top1++;
        forwardStack[top1] = backStack[top2];
        top2--;
        cout << "Current URL: " << backStack[top2] << endl;
        return backStack[top2];
    }
}
string go_Forward()
{
    if (top1 == -1)
    {
        cout<<"Going forward is not possible.";
        return "";
    }
    else {
        top2++;
        backStack[top2] = forwardStack[top1];
        top1--;
        cout << "Current URL: " << backStack[top2] << endl;
        return backStack[top2];
    }
}
string current_URL()
{
    if (top2 >= 0)
    {
        cout << "Current URL is: " << backStack[top2] << endl;
    }
    else   cout << "No URL visited yet." << endl;
}
int main() {

	  ifstream file("../input1.txt");

    if (!file.is_open()) {
        cout << "Error: Could not open the file\n";
        return 1;
    }

    string line, url;
    while (getline(file, line)) {
        stringstream ss(line);
        string operation;
        ss >> operation;

        if (operation == "visit") {
            ss >> url;
            visit(url);
        } else if (operation == "go_Back") {
            go_Back();
        } else if (operation == "go_Forward") {
            go_Forward();
        } else if (operation == "current_URL") {
            current_URL();
        } else {
            cout << "Unknown operation: " << operation << endl;
        }
    }

    file.close();

    return 0;
}