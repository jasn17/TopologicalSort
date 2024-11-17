#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <string>

using namespace std;

void dfs(const string& course, unordered_map<string, vector<string>>& graph, 
         unordered_map<string, bool>& visited, stack<string>& topoStack) {
    visited[course] = true;
    
    for (const string& neighbor : graph[course]) {
        if (!visited[neighbor]) {
            dfs(neighbor, graph, visited, topoStack);
        }
    }
    
    topoStack.push(course);
}

vector<string> topologicalSort(unordered_map<string, vector<string>>& graph, vector<string>& courses) {
    unordered_map<string, bool> visited;
    stack<string> topoStack;

    for (const string& course : courses) {
        visited[course] = false;
    }

    for (const string& course : courses) {
        if (!visited[course]) {
            dfs(course, graph, visited, topoStack);
        }
    }

    vector<string> topoOrder;
    while (!topoStack.empty()) {
        topoOrder.push_back(topoStack.top());
        topoStack.pop();
    }

    reverse(topoOrder.begin(), topoOrder.end());

    return topoOrder;
}

int main() {

    vector<string> courses = {"LA15", "LA16", "LA22", "LA31", "LA32", "LA126", "LA127", "LA141", "LA169"};
    
    unordered_map<string, vector<string>> graph = {
        {"LA15", {}},
        {"LA16", {"LA15"}},
        {"LA22", {}},
        {"LA31", {"LA15"}},
        {"LA32", {"LA16", "LA31"}},
        {"LA126", {"LA22", "LA32"}},
        {"LA127", {"LA16"}},
        {"LA141", {"LA22", "LA16"}},
        {"LA169", {"LA32"}}
    };

    vector<string> order = topologicalSort(graph, courses);

    cout << "A valid course sequence is:\n";
    for (const string& course : order) {
        cout << course << " ";
    }
    cout << endl;

    return 0;
}