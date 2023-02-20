#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

pair<int, int> decision_func(const int programmer, int (&departments)[5][5], const int (&programmers)[5][5], vector<int> &open_departments) {
    
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
            break;
        }
    }

    if(possibilites.size() > 1) {
        for(int i = 0; i < 5; ++i) {
            if (count(possibilites.begin(), possibilites.end(), programmers[programmer-1][i])) {
                decision.first = programmers[programmer-1][i];
                decision.second = programmer;
                open_departments.erase(remove(open_departments.begin(), open_departments.end(), decision.first), open_departments.end());
                
                for(auto &possibility : possibilites) {
                    int index_to_remove;

                    if( possibility != decision.first) {
                        index_to_remove = distance(departments[possibility-1], find(departments[possibility-1], departments[possibility-1] + 5, programmer));

                        for(int j = index_to_remove; j < 4; ++j) {
                        departments[possibility-1][j] = departments[possibility-1][j+1]; 
                        } 
                    }  
                }
                return decision;
            }
        }
    } else {
        decision.first = possibilites[0];
        decision.second = programmer;
        open_departments.erase(remove(open_departments.begin(), open_departments.end(), decision.first), open_departments.end());
        return decision;
    }
    return decision;
}

vector<pair<int, int>> department_selection(int (&departments)[5][5],const int (&programmers)[5][5]) {

        static vector<pair<int, int>> selections;
        vector<int> open_departments {1, 2, 3, 4, 5};
        
        selections.push_back(decision_func(1, departments, programmers, open_departments));
        selections.push_back(decision_func(2, departments, programmers, open_departments));
        selections.push_back(decision_func(3, departments, programmers, open_departments));
        selections.push_back(decision_func(4, departments, programmers, open_departments));
        selections.push_back(decision_func(5, departments, programmers, open_departments));
        
        return selections;
    }

bool comp_func(const pair<int, int> &p1, const pair<int, int> &p2) {
    return p1.first < p2.first;
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

    vector<pair<int, int>> solution = department_selection(departments, programmers);
    sort(solution.begin(), solution.end(), comp_func);
     
    cout << "\n";
    for(int i = 0; i < 5; ++i) {
        cout << "Department #" << solution[i].first << " " << "will get Programmer #" << solution[i].second << endl;
    }
    cout << "\n";

    return 0;
}
