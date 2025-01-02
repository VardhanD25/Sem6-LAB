#include <bits/stdc++.h>
using namespace std;

class DFS{
private:
    map<int,vector<int>> adj;
    int nodes;

public:
    DFS(int nodes){
        this->nodes = nodes;
    }

    void input(){
        for(int i = 0; i < nodes; i++){
            cout << "Enter nodes adjacent to node " << i << endl;
            cout << "Press -1 to stop" << endl;
            int num;
            while(true){
                cin >> num;
                if(num == -1) break;
                adj[i].push_back(num);
                adj[num].push_back(i);
            }
        }
    }

    void print_adj(){
        cout << "Adjacency List: " << endl;
        for(auto x : this->adj){
            cout << x.first << " -> ";
            for(int i : x.second){
                cout << i << " ";
            }
            cout << endl;
        }
    }

    bool dfs_search(vector<int>& path, vector<bool>& visited, int curr, int target){
        visited[curr] = true;
        path.push_back(curr);
        if(curr == target){
            cout << "Found!" << endl;
            return true;
        }
        for(int i : adj[curr]){
            if(!visited[i]){
                bool ans = dfs_search(path, visited, i, target);
                if(ans) return true;
            }
        }
        return false;
    }

    bool bfs_search(vector<int>& path, vector<bool>& visited, int target, queue<int>& q){
        visited[q.front()] = true;
        do{
            int curr = q.front();
            q.pop();
            path.push_back(curr);
            if(curr == target) return true;
            for(int i : adj[curr]){
                if(!visited[i]){
                    visited[i] = true;
                    q.push(i);
                }
            }
        } while(!q.empty());
        return false;
    }
};

int main() {
    int nodes;
    cout << "Enter number of nodes: ";
    cin >> nodes;
    DFS d(nodes);

    int choice;
    bool graphBuilt = false;

    do {
        cout << "\nMenu: \n";
        cout << "1. Input graph\n";
        cout << "2. Print adjacency list\n";
        cout << "3. DFS search\n";
        cout << "4. BFS search\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                d.input();
                graphBuilt = true;
                break;
            case 2:
                if(graphBuilt) {
                    d.print_adj();
                } else {
                    cout << "Graph not built yet! Please input the graph first." << endl;
                }
                break;
            case 3: {
                if(!graphBuilt) {
                    cout << "Graph not built yet! Please input the graph first." << endl;
                    break;
                }
                int target;
                cout << "\nEnter element to be DFS searched: ";
                cin >> target;
                vector<bool> visited(nodes, false);
                vector<int> path;
                bool found = d.dfs_search(path, visited, 0, target);
                if(found) {
                    cout << "\nPath taken to find element: ";
                    for(int i : path) {
                        cout << i << " ";
                    }
                    cout << endl;
                } else {
                    cout << "\nNot found!" << endl;
                }
                break;
            }
            case 4: {
                if(!graphBuilt) {
                    cout << "Graph not built yet! Please input the graph first." << endl;
                    break;
                }
                int target;
                cout << "\nEnter element to be BFS searched: ";
                cin >> target;
                vector<bool> visited(nodes, false);
                vector<int> path;
                queue<int> q;
                q.push(0);
                bool found = d.bfs_search(path, visited, target, q);
                if(found) {
                    cout << "\nPath taken to find element: ";
                    for(int i : path) {
                        cout << i << " ";
                    }
                    cout << endl;
                } else {
                    cout << "\nNot found!" << endl;
                }
                break;
            }
            case 5:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while(choice != 5);

    return 0;
}
