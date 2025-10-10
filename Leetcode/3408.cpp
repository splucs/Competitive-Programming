class TaskManager {
private:
    set<pair<int, int>> tasksPrioritized; // set of (priority, taskId)
    unordered_map<int, int> task2User;
    unordered_map<int, int> task2Priority;
public:
    TaskManager(vector<vector<int>>& tasks) {
        for (const vector<int>& task : tasks) {
            int userId = task[0], taskId = task[1], priority = task[2];
            add(userId, taskId, priority);
        }
    }
    
    void add(int userId, int taskId, int priority) {
        task2User[taskId] = userId;
        task2Priority[taskId] = priority;
        tasksPrioritized.insert(make_pair(priority, taskId));
    }
    
    void edit(int taskId, int newPriority) {
        int oldPriority = task2Priority[taskId];
        tasksPrioritized.erase(make_pair(oldPriority, taskId));
        task2Priority[taskId] = newPriority;
        tasksPrioritized.insert(make_pair(newPriority, taskId));
    }
    
    void rmv(int taskId) {
        int priority = task2Priority[taskId];
        tasksPrioritized.erase(make_pair(priority, taskId));
        task2User.erase(taskId);
        task2Priority.erase(taskId);
    }
    
    int execTop() {
        if (tasksPrioritized.empty()) {
            return -1;
        }
        int taskId = tasksPrioritized.rbegin()->second;
        int userId = task2User[taskId];
        rmv(taskId);
        return userId;
    }
};
