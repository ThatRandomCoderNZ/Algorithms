#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>
#include <stack>

//
// Created by ethan on 23/07/2021.
//


class Man{
    public:
        Man(int _id, std::vector<int> _preferences){
            id = _id;
            preferences = std::move(_preferences);
        }

        int id{};
        std::vector<int> preferences;
        int currentIndex = 0;
        int currentPartner = 0;



        void incIndex(){
            currentIndex++;
        }

        void setPartner(int partner){
            currentPartner = partner;
        }


        int getcurrentPreference(){
            return preferences[currentIndex];
        }

        int getId(){
            return id;
        }




};


class Woman{
    public:

        Woman(int _id, std::vector<int> _prefs){
            id = _id;
            preferences = _prefs;
            for(int i = 0; i < _prefs.size(); i++){
                rank[_prefs[i]] = i;
            }
        };

        std::unordered_map<int, int> rank;
        int id{};
        int currentPartner = 0;
        std::vector<int> preferences;

        int considerOffer(int manId){
            if(currentPartner == 0){
                currentPartner = manId;
                return 0;
            }
            if(rank[currentPartner] > rank[manId]){
                int oldPartner = currentPartner;
                currentPartner = manId;
                return oldPartner;
            }
            return -1;
        }

        void setPartner(int partner){
            currentPartner = partner;
        }
};

int main(){
    // Create all people
    //Add all men to a queue
    // Loop until queue is empty
    //      match man with someone
    //      If woman jilts man then add that man to the queue
    int numPairs;
    std::cin >> numPairs;

    std::vector<Man> men;
    std::vector<Woman> women;
    std::vector<int> temp;
    std::stack<int> bachelors;

    for(int i = 0; i < numPairs * 2; i++){
        std::vector<int> preferences;
        std::string inputId;
        std::cin >> inputId;
        inputId.pop_back();

        int id = std::stoi(inputId);

        for(int j = 0; j < numPairs; j++){
            std::string num;
            std::cin >> num;
            preferences.push_back(std::stoi(num));
        }

        if( i % 2 == 0){
            Man man = Man(id, preferences);
            men.push_back(man);
            temp.push_back(id);
        }else {
            Woman woman = Woman(id, preferences);
            women.push_back(woman);
        }
    }

    for(int i = temp.size() - 1; i >= 0; i--){
        bachelors.push(temp[i]);
    }

    while(!bachelors.empty()){
        Man currentMan = men[(bachelors.top() - 1) / 2];
        bachelors.pop();
        bool single = true;
        while(single){
            int offer = women[(currentMan.getcurrentPreference() / 2) - 1].considerOffer(currentMan.id);
            if(offer >= 0){
                single = false;
                men[(currentMan.id - 1) / 2].currentPartner = currentMan.getcurrentPreference();
                if(offer > 0){
                    bachelors.push(offer);
                }
            }
            currentMan.incIndex();
        }

    }

    for(auto man: men){
        std::cout << man.getId() << " : ";
        std::cout << man.currentPartner << "\n";
    }



}
