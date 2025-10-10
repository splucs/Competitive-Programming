struct Cell{
    int row, col;
    Cell(int _row, int _col) : row(_row), col(_col) {}
};

class Spreadsheet {
private:
    vector<vector<int>> spreadsheet;

    Cell parse(string cell) {
        int col = cell[0]-'A';
        int row = atoi(cell.substr(1).c_str())-1;
        return Cell(row, col);
    }
    int getCellValue(Cell cell) {
        if (cell.row < 0 || cell.row >= spreadsheet.size()) {
            return 0;
        }
        if (cell.col < 0 || cell.col >= 26) {
            return 0;
        }
        return spreadsheet[cell.row][cell.col];
    }
    void setCellValue(Cell cell, int value) {
        if (cell.row < 0 || cell.row >= spreadsheet.size()) {
            return;
        }
        if (cell.col < 0 || cell.col >= 26) {
            return;
        }
        spreadsheet[cell.row][cell.col] = value;
    }
    int getTermValue(string term) {
        if ('A' <= term[0] && term[0] <= 'Z') {
            return getCellValue(parse(term));
        }
        return atoi(term.c_str());
    }
public:
    Spreadsheet(int rows) {
        spreadsheet.assign(rows, vector<int>(26, 0));
    }
    
    void setCell(string cell, int value) {
        Cell parsedCell = parse(cell);
        setCellValue(parsedCell, value);
    }
    
    void resetCell(string cell) {
        setCell(cell, 0);
    }
    
    int getValue(string formula) {
        int plusIdx = formula.find("+");
        string firstTerm = formula.substr(1, plusIdx);
        string secondTerm = formula.substr(plusIdx+1);
        return getTermValue(firstTerm) + getTermValue(secondTerm);
    }
};
