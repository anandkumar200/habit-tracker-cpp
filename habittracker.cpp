#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Habit{
    public:
    string name;
    vector<int> progress;

    Habit(){
        name = "";
        progress.resize(30, 0);
    }

    Habit(string n, int days = 30){
        name = n;
        progress.resize(days, 0);
    }
};

void showHabit();
void outoffile(vector<Habit> &habit);
void intofile(vector<Habit> &habit);
int maxStreak(Habit &h, int days);
int currentStreak(Habit &h, int days);
void weeklySummary(vector<Habit> &habit);
void monthlySummary(vector<Habit> &habit);

void showHabit(){
        cout << "\n    Habit Tracker     \n" << endl;
        cout <<"1. Add Habit \n" << endl;
        cout << "2. Mark Habit as done \n" << endl;
        cout << "3. Show Progress \n" << endl;
        cout << "4. Exit \n" << endl;
        cout << "5. Delete a Habit \n" << endl;
        cout << "6. Edit a Habit \n" << endl;
        cout << "7. Weekly Summary \n" << endl;
        cout << "8. Monthly Summary \n" << endl;
    }

void outoffile(vector<Habit> &habit){
    ofstream fout("C:/Users/Anand Kumar/Desktop/projectcpp/habitss.txt");
    if(!fout){
        cout << "Error in opening file\n" << endl;
        return;
    }

    else{
        for(auto &h : habit){
            fout << h.name;
            for(int i = 0; i < 30; i++){
                fout << " " << h.progress[i];
            }
            fout << "\n";
        }
    }
    fout.close();
}

void intofile(vector<Habit> &habit){
    ifstream fin("C:/Users/Anand Kumar/Desktop/projectcpp/habitss.txt");
    if(!fin){
        cout << "File not found \n" << endl;
        return;
    }
    else{
        habit.clear();
        Habit h;
        while(fin >> h.name){
            for(int i = 0; i < 30; i++){
                fin >> h.progress[i];
            }
            habit.push_back(h);
        }
    }
    fin.close();
}

int maxStreak(Habit &h, int days){
    int currentStreak = 0;
    int maxStreak = 0;
    for(int i = 0; i < days; i++){
        if(h.progress[i] == 1){
            currentStreak++;
            maxStreak = max(maxStreak, currentStreak);
        }
        else{
            currentStreak = 0;
        }
    }
    return maxStreak;
}

int currentStreak(Habit &h, int days){
    int streak1 = 0;
    for(int i = days - 1; i >= 0; i--){
        if(h.progress[i] == 1){
            streak1++;
        }
        else{
            streak1 = 0;
        }
    }
    return streak1;
}

void weeklySummary(vector<Habit> &habit){
    for(int i = 0; i < habit.size(); i++){
        int completed = 0;
        for(int j = 0; j < 7; j++){
            if(habit[i].progress[j] == 1){
                completed++;
            }
        }
        float successRate = (completed * 100.0f)/7;
        cout << "The Completed Days of " << habit[i].name << " is " << completed << endl;
        cout << "The Success Rate of " << habit[i].name << " is " << successRate << endl;
        cout << "The Current Streak of " << habit[i].name << " is " << currentStreak(habit[i], 7) << endl;
        cout << "The Maximum Streak of " << habit[i].name << " is " << maxStreak(habit[i], 7) << endl;
    }
}

void monthlySummary(vector<Habit> &habit){
    for(int i = 0; i < habit.size(); i++){
        int completed = 0;
        for(int j = 0; j < 30; j++){
            if(habit[i].progress[j] == 1){
                completed++;
            }
        }
        float successRate = (completed * 100.0f)/30;
        cout << "The Completed Days of " << habit[i].name << " is " << completed << endl;
        cout << "The Success Rate of " << habit[i].name << " is " << successRate << endl;
        cout << "The Current Streak of " << habit[i].name << " is " << currentStreak(habit[i], 30) << endl;
        cout << "The Maximum Streak of " << habit[i].name << " is " << maxStreak(habit[i], 30) << endl;
    }
    
}    

int main(){

    vector<Habit>habit;

    intofile(habit);

    int i;
    int day;
    int markedhabit;
    int selectedoption = 0;
    string editname;
    int progressChoice;

    cout << "Choose one option \n" << endl;


    while(selectedoption != 4){
        showHabit();
        cin >> selectedoption;
        if(selectedoption == 1){
            string name;
            cout << "\nSelected option is Add Habit \n" << endl;
            cout << "Add Habit \n" << endl;
            Habit temp;
            cin >> temp.name;
            
            habit.push_back(temp);
        }

        if(selectedoption == 2){
            cout << "Selected option is Mark Habit is done \n" << endl;
            cout << "Select the day of which you want to mark progress (1 - 7) \n" << endl;
            cin >> day;
            for(i = 0; i < habit.size(); i++){
                cout << i+1 << "." << habit[i].name << endl;
            }
            cout << "\nSelect the habit you want to mark done \n" << endl;
            cin >> markedhabit;
            habit[markedhabit - 1].progress[day - 1] = 1;
            cout << "\nHabit is marked \n" << endl;
        }

        if(selectedoption == 3){
            cout << "Selected option is Show Progress \n" << endl;
            for(i = 0; i < habit.size(); i++){
                cout << i+1 << "." << habit[i].name << endl;
            }
            cout << "Select the habit that you wanna check the progress of \n" << endl;
            cin >> progressChoice;
            cout << "\nHabit : " << habit[progressChoice - 1].name << "\n" << endl;
            for(i = 0; i < 7; i++){
                cout << "Day " << i+1 << ": " << (habit[progressChoice - 1].progress[i] == 1 ? "Done" : "Not Done") << endl;
            }
            int streakNum = maxStreak(habit[progressChoice - 1], 7);
            cout << "Maximum Streak of this week till now is \n" << streakNum << endl;
            int curStreak = currentStreak(habit[progressChoice - 1], 7);
            cout << "Current streak of this week till now is \n" << curStreak << endl;
            int streakNum1 = maxStreak(habit[progressChoice - 1], 30);
            cout << "Maximum Streak of this month till now is \n" << streakNum1 << endl;
            int curStreak1 = currentStreak(habit[progressChoice - 1], 30);
            cout << "Current streak of this month till now is \n" << curStreak1 << endl;
            
        }
 
        if(selectedoption == 5){
            cout << "Selected option is Delete a Habit \n" << endl;
            for(i = 0; i < habit.size(); i++){
                cout << i+1 << habit[i].name << endl;
            }
            cout << "Select a Habit that you wanna delete \n" << endl;
            cin >> selectedoption;
            habit.erase(habit.begin() + selectedoption - 1);
            cout << "Habit " << selectedoption << "is deleted succesfully \n" << endl;
        }

        if(selectedoption == 6){
            cout << "Selected option is Edit a Habit \n" << endl;
            for(i = 0; i < habit.size(); i++){
                cout << i+1 << habit[i].name << endl;
            }
            cout << "Select the Habit that you wanna edit \n" << endl;
            cin >> selectedoption;
            cout << "Enter the new name \n" << endl;
            cin.ignore();
            getline(cin, editname);
            habit[selectedoption - 1].name = editname;
            cout << "Name is edited succesfully \n" << endl;
        }

        if(selectedoption == 7){
            cout << "Selected option is Weekly Summary \n" << endl;
            weeklySummary(habit);
        }

        if(selectedoption == 8){
            cout << "Selected option is Monthly Summary \n" << endl;
            monthlySummary(habit);
        }

    }

    if(selectedoption == 4){
        cout << "Thank you, visit again \n" << endl;
    }

    outoffile(habit);

    return 0;
}