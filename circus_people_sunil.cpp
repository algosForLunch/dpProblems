struct Person {
    int ID;
    int height;
    int weight;
}



int findLargestPossiblePeopleCount(vector<Person> people) {
    vector<int> peopleSortedByHeight = people;
    std::sort(peopleSortedByHeight.begin(), peopleSortedByHeight.end(), [](const Person& a, const Person& b) {return a.height>b.height});
    
    Person personWithMaxHeightAndWeight;
    personWithMaxHeightAndWeight.weight = INT_MAX;
    personWithMaxHeightAndWeight.height = INT_MAX;
    findLargestPossiblePeopleCount(personWithMaxHeightAndWeight, people, results);
    
    
    int maxHeight = 0;
    int resultCount = 0;
    for(auto it = results.begin(); it != results.end(); it++) {
        if(it->second.second>maxHeight) {
            maxHeight = it->second.second;
            resultCount = it->second.first;
        }
    }
    return resultCount;
}

// Returns <numberOfPeople,MaxHeight> for Person p
pair<int, int> findLargestPossiblePeopleCount(const Person p, vector<Person> peopleSortedByHeight, unordered_map<Person, pair<int, int>& result) {
    if(result.find(p)!=result.end()) {
        return result[p];
    }
    if(peopleSortedByHeight.size()==1) {
        return make_pair(1,peopleSortedByHeight[0].height);
    }
    pair<int, int> resultForP= make_pair(0,0);
    for(int i = 0; i < peopleSortedByHeight.size(); i++) {
        vector<Person> subset;
        for(int j = i; j<peopleSortedByHeight.size(); j++) {
            if(peopleSortedByHeight[j].weight < peopleSortedByHeight[i].weight) {
                subset.push_back(peopleSortedByHeight[j]);
            }
        }
        pair<int, int> res = findLargestPossiblePeopleCount(peopleSortedByHeight[i], subset, result);
        if(res.second+p.height>resultForP.second) {
            resultForP.first = res.first+1;
            resultForP.second = res.second + p.height;
        }
    }
    result[p] = resultForP;
    return resultForP;
}
