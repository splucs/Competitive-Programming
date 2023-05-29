class ParkingSystem {
private:
    int curType[4];
    int maxType[4];
public:
    ParkingSystem(int big, int medium, int small) {
        memset(&curType, 0, sizeof curType);
        maxType[1] = big;
        maxType[2] = medium;
        maxType[3] = small;
    }
    
    bool addCar(int carType) {
        if (curType[carType] < maxType[carType]) {
            curType[carType]++;
            return true;
        }
        return false;
    }
};

/**
 * Your ParkingSystem object will be instantiated and called as such:
 * ParkingSystem* obj = new ParkingSystem(big, medium, small);
 * bool param_1 = obj->addCar(carType);
 */
