#include <iostream>
#include <vector>
using namespace std;

// SelectionSort function to sort suggestions
void SelectionSort(vector<int>& v) {
    for (int i = 0; i < v.size() - 1; i++) {
        int min = i;
        for (int j = i + 1; j < v.size(); j++) {
            if (v[j] < v[min])
                min = j;
        }
        int t = v[i];
        v[i] = v[min];
        v[min] = t;
    }
}

// FriendSuggestion class to manage friendships and suggestions
class FriendSuggestion {
private:
    int numUsers;
    vector<vector<int>> adjacencyMatrix;

public:
    FriendSuggestion(int n) : numUsers(n) {
        // Initialize adjacency matrix with zeros
        adjacencyMatrix.resize(numUsers, vector<int>(numUsers, 0));
    }

    // Add a friendship between two users
    void addFriendship(int user1, int user2) {
        adjacencyMatrix[user1][user2] = 1;
        adjacencyMatrix[user2][user1] = 1;
    }

    // Get friend suggestions for a given user
    vector<int> getFriendSuggestions(int user) {
        vector<int> suggestions;

        // Iterate through potential friends
        for (int i = 0; i < numUsers; ++i) {
            if (i != user && adjacencyMatrix[user][i] == 0) {
                int mutualFriends = 0;

                // Count mutual friends
                for (int j = 0; j < numUsers; ++j) {
                    if (adjacencyMatrix[user][j] == 1 && adjacencyMatrix[i][j] == 1) {
                        mutualFriends++;
                    }
                }

                // Encode mutual friends count and user ID
                suggestions.push_back(mutualFriends * 1000 + i);
            }
        }

        // Sort suggestions based on mutual friends count
        SelectionSort(suggestions);

        // Extract user IDs from sorted suggestions
        vector<int> result;
        for (int suggestion : suggestions) {
            result.push_back(suggestion % 1000);
        }

        return result;
    }
};

int main() {
    // Create a FriendSuggestion graph for 5 users
    FriendSuggestion graph(5);

    // Add friendships
    graph.addFriendship(0, 1);
    graph.addFriendship(0, 2);
    graph.addFriendship(1, 3);
    graph.addFriendship(2, 4);

    // Get and display friend suggestions for each user
    for (int i = 0; i < 5; i++) {
        vector<int> suggestions = graph.getFriendSuggestions(i);
        cout << "Friend suggestions for user " << i << " : ";
        for (int suggestion : suggestions) {
            cout << suggestion << " ";
        }
        cout << endl;
    }

    return 0;
}
