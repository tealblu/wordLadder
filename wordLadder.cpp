#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

vector<string> V; //words from wordlist05.txt
//Global variables for bfs distance, bfs predecessor, and neighboring nodes
//Should be unordered_map type
// GENERIC -- these shouldn't need to be changed...
unordered_map<string, bool> visited;         // have we queued up this state for visitation?
unordered_map<string, string> pred;           // predecessor state we came from
unordered_map<string, int> dist;             // distance (# of hops) from source node
unordered_map<string, vector<string>> nbrs;   // vector of neighboring states

//Implement breadth-first search, refer to Lab 10
// GENERIC (breadth-first search, outward from curnode)
void search(string source_node)
{
  queue<string> to_visit;
  to_visit.push(source_node);
  visited[source_node] = true;
  dist[source_node] = 0;
  
  while (!to_visit.empty()) {
    string curnode = to_visit.front();
    to_visit.pop();
    for (string n : nbrs[curnode])
      if (!visited[n]) {
	pred[n] = curnode;
	dist[n] = 1 + dist[curnode];
	visited[n] = true;
	to_visit.push(n);
      }
  }
}

// function to save path
vector<string> save_path(string s, string t) {
  vector<string> path;

  // pretty much copied from print_path from WolfGoatCabbage assignment
  if(s != t && pred[t] != "\0") {
    path = save_path(s, pred[t]);
    path.push_back(pred[t]);
  }

  return path;
}

void wordLadder(string s, string t, int &steps, vector<string> &p)
{
  // load words into V, check to see if s and t exist
  bool sFound = false;
  bool tFound = false;
  ifstream infile("wordlist05.txt");
  for(string line; getline(infile, line); ) {
    V.push_back(line);
    if(line == s) {
      sFound = true;
    }
    if(line == t) {
      tFound = true;
    }
  }

  // warn user if s and t are not found
  if(sFound == false) {
    cout << "Warning: Source word not found in word list! Exiting..." << endl;
    exit(EXIT_FAILURE);
  }
  if(tFound == false) {
    cout << "Warning: Target word not found in word list! Exiting..." << endl;
    exit(EXIT_FAILURE);
  }

  // At this point, words should be loaded and s and t are present in V

  // Build nbrs:

  // Loop through V to pick first word
  for(unsigned i = 0; i < V.size(); i++) {
    // Loop through V again to pick second word
    for(unsigned j = 0; j < V.size(); j++) {
      int differs = 0;

      // Loop through characters and compare
      for(unsigned k = 0; k < V[i].size(); k++) {
        if(V[i][k] != V[j][k]) {
          differs++;
        }
      }

      // If the strings differ by one character, they are neighbors
      if(differs == 1) {
        nbrs[V[i]].push_back(V[j]);
      }
    }
  }

  // nbrs is now built, perform search
  search(s);

  // save number of steps
  steps = dist[t];

  // save path
  p = save_path(s, t);
  p.push_back(t);

  /* the end! this is the last assignment in this class, so I'd like to thank Dr. Widman and all the TA's
  for being awesome!! Yall are the best :) */
}

int main(void)
{
  int steps = 0;
  string s, t;
  vector<string> path;
  
  cout << "Source: ";
  cin >> s;

  cout << "Target: ";
  cin >> t;

  wordLadder(s, t, steps, path);

  if (steps == 0)
  {
      cout << "No path!\n";
  }
  else
  {
      cout << "Steps: " << steps << "\n\n";
      for (unsigned i=0; i<path.size(); i++)
      {
          cout << path[i] << endl;
      }
  }
  return 0;
}
