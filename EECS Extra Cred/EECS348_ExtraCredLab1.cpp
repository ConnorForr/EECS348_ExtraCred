#include <bits/stdc++.h>
#include<fstream>
using namespace std;

pair<int, int> decision_func(int programmer, const int (&departments)[][5], const int (&programmers)[][5], vector<int> &open_departments) {
    
    pair<int, int> decision;
    vector<int> possibilites;

    for(int i = 0; i < 5; ++i) {
        for(int j = 0; j < 5; ++j) {
            if(programmer == departments[j][i]) {
                if(count(open_departments.begin(), open_departments.end(), (j+1))) {
                    possibilites.push_back((j+1));
                }
            }
        }
        if(!possibilites.empty()) {
            cout << "break hit" << endl;
            break;
        }
    }
    cout << "possibilites ";
    for(auto &x : possibilites) {
        cout << x << " ";
    }
    cout << endl;

    if(possibilites.size() > 1) {
        for(int i = 0; i < 5; ++i) {
            if (count(possibilites.begin(), possibilites.end(), programmers[programmer-1][i])) {
                decision.first = programmers[programmer-1][i];
                decision.second = programmer;
                open_departments.erase(open_departments.begin()+programmers[programmer-1][i]-1);
                return decision;
            }
        }
    } else {
        decision.first = possibilites[0];
        decision.second = programmer;
        open_departments.erase(open_departments.begin()+possibilites[0]-1);
        return decision;
    }
}

pair<int, int>* department_selection(const int (&departments)[][5], const int (&programmers)[][5]) {

        pair<int, int> selections[5];
        vector<int> open_departments {1, 2, 3, 4, 5};
        
        selections[0] = decision_func(1, departments, programmers, open_departments);

        cout << "open_deps ";
        for(auto &x : open_departments) {
            cout << x << " ";
        }
        cout << endl;

        selections[1] = decision_func(2, departments, programmers, open_departments);

        cout << "open_deps ";
        for(auto &x : open_departments) {
            cout << x << " ";
        }
        cout << endl;

        selections[2] = decision_func(3, departments, programmers, open_departments);

        cout << "open_deps ";
        for(auto &x : open_departments) {
            cout << x << " ";
        }
        cout << endl;

        selections[3] = decision_func(4, departments, programmers, open_departments);

        cout << "open_deps ";
        for(auto &x : open_departments) {
            cout << x << " ";
        }
        cout << endl;

        selections[4] = decision_func(5, departments, programmers, open_departments);
        
        return selections;
    }

int main() {
    
    ifstream input_file("matching-data.txt");
    int programmers[5][5];
    int departments[5][5];
    int num;
 
    if (input_file.is_open()) {
        for(int i = 0; i < 10; ++i) { 
            for(int j = 0; j < 5; ++j) {
                input_file >> num;
                if (i < 5) {
                    departments[j][i] = num;
                } else {
                    programmers[j][i-5] = num;
                }
            }
        }
        input_file.close();
    }

    pair<int, int> * arr = department_selection(departments, programmers);
    
    for(int i = 0; i < 5; ++i) {
        cout << arr[i].first << " " << arr[i].second << endl;
    }
    return 0;
}
