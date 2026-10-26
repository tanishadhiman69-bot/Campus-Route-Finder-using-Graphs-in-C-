
#include <iostream>
#include <string>
#include <queue>
using namespace std;

const int N = 8;

string places[N] = {
    "Main Gate", "Library", "Canteen", "Admin Block",
    "Computer Lab", "Auditorium", "Hostel", "Sports Ground"
};

int graph[N][N] = {0};

// Add roads between campus locations
void road(int a, int b) {
    graph[a][b] = 1;
    graph[b][a] = 1;
}

// Show all locations
void showPlaces() {
    for (int i = 0; i < N; i++)
        cout << i << ". " << places[i] << endl;
}

// BFS finds the shortest route
void bfs(int start, int dest) {
    int visited[N] = {0}, parent[N];

    for (int i = 0; i < N; i++)
        parent[i] = -1;

    queue<int> q;
    q.push(start);
    visited[start] = 1;

    while (!q.empty()) {
        int x = q.front();
        q.pop();

        for (int i = 0; i < N; i++) {
            if (graph[x][i] == 1 && !visited[i]) {
                visited[i] = 1;
                parent[i] = x;
                q.push(i);
            }
        }
    }

    if (!visited[dest]) {
        cout << "No route found.\n";
        return;
    }

    int route[N], count = 0;

    for (int x = dest; x != -1; x = parent[x])
        route[count++] = x;

    cout << "Shortest route: ";

    for (int i = count - 1; i >= 0; i--) {
        cout << places[route[i]];
        if (i > 0) cout << " -> ";
    }

    cout << "\nNumber of roads: " << count - 1 << endl;
}

// DFS shows reachable locations
void dfs(int x, int visited[]) {
    visited[x] = 1;
    cout << places[x] << endl;

    for (int i = 0; i < N; i++) {
        if (graph[x][i] == 1 && !visited[i])
            dfs(i, visited);
    }
}

int main() {
    road(0, 1);
    road(0, 3);
    road(1, 2);
    road(1, 4);
    road(2, 5);
    road(3, 4);
    road(3, 6);
    road(4, 5);
    road(6, 7);

    int choice, start, dest;

    do {
        cout << "\n=== Campus Route Finder ===\n";
        cout << "1. Show Locations\n";
        cout << "2. Find Shortest Route (BFS)\n";
        cout << "3. Show Reachable Locations (DFS)\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Please enter a number.\n";
            return 0;
        }

        if (choice == 1) {
            showPlaces();
        }
        else if (choice == 2 || choice == 3) {
            showPlaces();

            cout << "Enter starting location number (0-7): ";
            if (!(cin >> start)) {
                cout << "Invalid input. Please enter a number.\n";
                return 0;
            }

            if (start < 0 || start >= N) {
                cout << "Invalid starting location.\n";
                continue;
            }

            if (choice == 2) {
                cout << "Enter destination number (0-7): ";

                if (!(cin >> dest)) {
                    cout << "Invalid input. Please enter a number.\n";
                    return 0;
                }

                if (dest < 0 || dest >= N)
                    cout << "Invalid destination.\n";
                else
                    bfs(start, dest);
            }
            else {
                int visited[N] = {0};
                cout << "Reachable locations:\n";
                dfs(start, visited);
            }
        }
        else if (choice == 4) {
            cout << "Thank you for using Campus Route Finder!\n";
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}

