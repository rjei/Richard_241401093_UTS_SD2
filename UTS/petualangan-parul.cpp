#include <iostream>
#include <vector>
#include <string>
#include <queue>  
#include <stack>  

using namespace std;

// Pake class Graph yg dari latian dfs/bfs 
class Graph {
private:
    int numVertices;
    vector<vector<int>> adjMatrix; 
    vector<string> nama_kafe;      

    // Helper A,B,C biar gampang bacanya
    char getCharName(int i) {
        return (char)('A' + i);
    }

public:
    Graph(int V) {
        numVertices = V;
        adjMatrix.resize(numVertices, vector<int>(numVertices, 0));
    }

    void addCafeName(string name) {
        nama_kafe.push_back(name);
    }

    void addEdge(int u, int v, int w) {
        //A=0, B=1 (0-based index bestie)
        if (u >= 0 && u < numVertices && v >= 0 && v < numVertices) {
            adjMatrix[u][v] = w;
            adjMatrix[v][u] = w; // Bolak-balik sama aja 
        }
    }

    //PART 1: PARUL KELUYURAN (DFS) 
    // Function rekursif DFS dari latian dfs.cpp
    void dfsUtil(int u, vector<bool>& visited) {
        visited[u] = true;
        cout << getCharName(u);

        // Cek tetangga
        for (int v = numVertices - 1; v >= 0; v--) {
            // Cek ada jalan (bobot > 0) & belum di-visit? 
            if (adjMatrix[u][v] > 0 && !visited[v]) {
                cout << " -> ";
                dfsUtil(v, visited);
            }
        }
    }
    // Fungsi starter DFS-nya
    void runDFS(int startVertex) {
        cout << "PENJELAJAHAN PARUL (DFS dari A):\n";
        vector<bool> visited(numVertices, false);
        dfsUtil(startVertex, visited);
        cout << "\n\n"; 
    }

    //PART 2: PARUL CARI JALUR SATSET (BFS) 
    // buat ngambil bobot/jarak
    int getWeight(int u, int v) {
        return adjMatrix[u][v];
    }
    // BFS buat nyari jalan dari start ke end
    void runBFS(int start, int end) {
        cout << "JALUR TERCEPAT PARUL (BFS):\n"; 
        vector<bool> visited(numVertices, false);
        vector<int> parent(numVertices, -1); //buat nyimpen dateng dari mana
        queue<int> q; 

        q.push(start);
        visited[start] = true;
        bool found = false;

        // 1. BFS (pake queue)
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            if (u == end) {
                found = true;
                break; //KETEMU! Break!
            }

            for (int v = numVertices - 1; v >= 0; v--) {
                // Ada jalan (bobot > 0)? Belum di-visit?
                if (adjMatrix[u][v] > 0 && !visited[v]) {
                    visited[v] = true;
                    q.push(v);
                    parent[v] = u; // Catet parent-nya
                }
            }
        }

        if (!found) {
            cout << "Jalur dari " << getCharName(start) << " ke " 
                 << getCharName(end) << " gaada :(\n";
            return;
        }

        // 2. Spill jalurnya 
        stack<int> path;
        int current = end;
        while (current != -1) {
            path.push(current);
            current = parent[current]; // Mundur terus pake parent
        }

        // 3. Waktunya nge-print hasil + ngitung total
        vector<int> final_path;
        while (!path.empty()) {
            final_path.push_back(path.top());
            path.pop();
        }

        long long total_jarak = 0;
        int total_langkah = 0;

        // Loop ini nge-print yg ada nama kafe + jarak meteran
        for (int i = 0; i < final_path.size(); i++) {
            int u = final_path[i];
            cout << nama_kafe[u] << " (" << getCharName(u) << ")\n"; 
            
            if (i < final_path.size() - 1) {
                int v = final_path[i+1];
                int weight = getWeight(u, v);
                
                cout << weight << "m\n";
                
                total_jarak += weight;
                total_langkah++;
            }
        }

      
        cout << "\nJalur terpendek: ";
        for (int i = 0; i < final_path.size(); i++) {
            cout << getCharName(final_path[i]);
            if (i < final_path.size() - 1) {
                cout << " -> ";
            }
        }
        
        cout << "\nTotal langkah: " << total_langkah << " edge\n";  
        cout << "Total jarak: " << total_jarak << " meter\n"; 
    }
};

int main() {
    // A=0, B=1, C=2, D=3, E=4
    int V = 5;
    Graph g(V);

    g.addCafeName("Warung Kopi Pak Harry"); // A=0
    g.addCafeName("Kedai Coding IKLC");      // B=1
    g.addCafeName("Catfe Alya");            // C=2
    g.addCafeName("Studio Fasilkom-TI");    // D=3
    g.addCafeName("Wi-Fi Gratis Sejagat");  // E=4

   
    g.addEdge(0, 1, 4); // A-B (4)
    g.addEdge(0, 2, 2); // A-C (2)
    g.addEdge(1, 3, 3); // B-D (3)
    g.addEdge(2, 3, 1); // C-D (1)
    g.addEdge(3, 4, 5); // D-E (5)


    g.runDFS(0); // Start dari A (index 0)

    g.runBFS(0, 4); // Start A (0), fin E (4)

    return 0;
}