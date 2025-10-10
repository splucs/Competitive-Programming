class FoodRatings {
private:
    unordered_map<string, string> food2Cuisine;
    unordered_map<string, int> food2Rating;
    unordered_map<string, set<pair<int, string>>> highestRatings; // map of cuisine -> set of (-rating, food)
public:
    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        int n = foods.size();
        for (int i = 0; i < n; i++) {
            food2Cuisine[foods[i]] = cuisines[i];
            food2Rating[foods[i]] = ratings[i];
            highestRatings[cuisines[i]].insert(make_pair(-ratings[i], foods[i]));
        }
    }
    
    void changeRating(string food, int newRating) {
        string cuisine = food2Cuisine[food];
        int oldRating = food2Rating[food];
        highestRatings[cuisine].erase(make_pair(-oldRating, food));
        food2Rating[food] = newRating;
        highestRatings[cuisine].insert(make_pair(-newRating, food));
    }
    
    string highestRated(string cuisine) {
        return highestRatings[cuisine].begin()->second;
    }
};
