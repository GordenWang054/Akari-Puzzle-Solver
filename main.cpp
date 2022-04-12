#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <ctime>
#include <string>
#include <algorithm>

using namespace std;
struct location{
    int row;
    int col;
    int IntAround;
    location(int r = 0,int c = 0){
        row = r;
        col = c;
    }
    void set(int r,int c){
        row = r;
        col = c;
    }
    void operator = (location a){
        row = a.row;
        col = a.col;
    }
    bool operator > (location a){
        if(this->IntAround > a.IntAround) return true;
        else return false;
    }
    bool operator < (location a){
        if(this->IntAround < a.IntAround) return true;
        else return false;
    }
    bool operator == (location a){
        if(this->IntAround == a.IntAround) return true;
        else return false;
    }
    bool operator <= (location a){
        if(this->IntAround <= a.IntAround) return true;
        else return false;
    }
    bool operator >= (location a){
        if(this->IntAround >= a.IntAround) return true;
        else return false;
    }
};
bool comparsion(location a,location b){
    return a.IntAround>b.IntAround;
}
template<class T>
void swap(T* a, T* b)
{
    T t = *a;
    *a = *b;
    *b = t;
}
template<class T>
int partition (vector<T> & arr, int low, int high)
{
    T pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j] <= pivot) {i++;swap(&arr[i], &arr[j]);}
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
template<class T>
void quickSort(vector<T> & arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
struct grid{
    int type;
    char data;
    int row;
    int col;
    int avalibleNum;
    bool ifavalible;
    int lightUp;
    grid(int row0 = 0 ,int col0 = 0,int type0 = -1){
        row = row0;
        col = col0;
        type = type0;
        if(type != -1)
            avalibleNum = type0;
        else
            avalibleNum = 5;
        ifavalible = false;
        lightUp = 0;
    }
    void setGrid(int row0,int col0,int type0,char data0){
        row = row0;
        col = col0;
        type = type0;
        data = data0;
        lightUp = 0;
        ifavalible = false;
        if(type != -1)
            avalibleNum = type;
        else{
            avalibleNum = 999;
        }
        if(type == 5)
            ifavalible = true;
        if(type < 5)
            lightUp = 1;
    }
    void operator = (grid g){
        type = g.type;
        data = g.data;
        row = g.row;
        col = g.col;
        avalibleNum = g.avalibleNum;
        ifavalible = g.ifavalible;
        lightUp = g.lightUp;
    }
};
//type -1:Block, 0:number 0 block and so on, 5:void grid 6:light 7:lighted up grid
//avalibleNum: how many light can be place around this grid
//lightUp: judge if a grid is lighted up , false: does't light up, true:light up
//ifavalible: judge if a grid can be placed a light,true: can ,false: can't
class Puzzle{
private:
    
public:
    int rows;
    int cols;
    vector<vector<grid> > board;
    Puzzle(int row0 = 0,int col0 = 0,string s = "ABC"){//initialize of the puzzle
        rows = row0;
        cols = col0;
        vector<grid> tmpVec;
        grid tmp;
        for(int i=0;i<rows;i++){
            tmpVec.clear();
            for(int j=0;j<cols;j++){
                if(s[i*cols+j] == 'X'){tmp.setGrid(i, j, -1,s[i*cols+j]);tmpVec.push_back(tmp);continue;}
                if(s[i*cols+j] == '.'){tmp.setGrid(i, j, 5,s[i*cols+j]);tmpVec.push_back(tmp);continue;}
                tmp.setGrid(i, j, s[i*cols+j]-'0',s[i*cols+j]);
                tmpVec.push_back(tmp);
            }
            board.push_back(tmpVec);
        }
        
        cout << "construct succeed" << endl;
    }//initialization
    Puzzle(const Puzzle & p){
        rows = p.rows;
        cols = p.cols;
        for(int i=0;i<rows;i++)
            board.push_back(p.board[i]);
    }
    Puzzle(const Puzzle * p){
        rows = p->rows;
        cols = p->cols;
        for(int i=0;i<rows;i++)
            board.push_back(p->board[i]);
    }
    void printPuzzle(){//print the whole puzzle
        cout << "  " << " ";
        for(int i=0;i<cols;i++) cout << setw(3) << i << " ";
        cout << endl << endl << endl;
        for(int i=0;i<rows;i++){
            cout << setw(2) << i << " ";
            for(int j=0;j<cols;j++){
                cout << setw(3) << board[i][j].data << " ";
            }
            cout << endl << endl << endl;
        }
        cout<<endl;
    }
    void operator = (Puzzle p){
        rows = p.rows;
        cols = p.cols;
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                board[i][j] = p.board[i][j];
            }
        }
    }
    bool setLight(int row,int col){
        set0();
        if(board[row][col].type != 5) return false;
        if(board[row][col].lightUp > 0) return false;
        if(!board[row][col].ifavalible) return false;
        board[row][col].lightUp++;
        board[row][col].ifavalible = false;
        board[row][col].type = 6;
        board[row][col].data = '&';
        if(row+1 < rows)
            board[row+1][col].avalibleNum--;
        if(row-1 >= 0)
            board[row-1][col].avalibleNum--;
        if(col+1 < cols)
            board[row][col+1].avalibleNum--;
        if(col-1 >= 0)
            board[row][col-1].avalibleNum--;
        int count = 1;
        if(row+count < rows){
            while(board[row+count][col].type == 5 || board[row+count][col].type == 7){
                board[row+count][col].lightUp++;
                board[row+count][col].data = '*';
                board[row+count][col].type = 7;
                board[row+count][col].ifavalible = false;
                count++;
                if(row+count >= rows) break;
            }
        }
        count = 1;
        if(row-count >= 0){
            while(board[row-count][col].type == 5 || board[row-count][col].type == 7){
                board[row-count][col].lightUp++;
                board[row-count][col].data = '*';
                board[row-count][col].type = 7;
                board[row-count][col].ifavalible = false;
                count++;
                if(row-count < 0) break;
            }
        }
        count = 1;
        if(col+count < cols){
            while(board[row][col+count].type == 5 || board[row][col+count].type == 7){
                board[row][col+count].lightUp++;
                board[row][col+count].data = '*';
                board[row][col+count].type = 7;
                board[row][col+count].ifavalible = false;
                count++;
                if(col+count >= cols) break;
            }
        }
        count = 1;
        if(col-count >= 0){
            while(board[row][col-count].type == 5 || board[row][col-count].type == 7){
                board[row][col-count].lightUp++;
                board[row][col-count].data = '*';
                board[row][col-count].type = 7;
                board[row][col-count].ifavalible = false;
                count++;
                if(col-count < 0) break;
            }
        }
        set0();
        //cout << "set a light at " << row << "," << col << endl << endl ;
        //printPuzzle();
        return true;
    }
    
    int spareGrid(int row,int col){
        int i = row;
        int j = col;
        int spareGrid = 0;
        if(i+1 < rows){
            if(board[i+1][j].ifavalible)
                spareGrid++;
        }
        
        if(i-1 >= 0){
            if(board[i-1][j].ifavalible)
                spareGrid++;
        }
        
        if(j+1 < cols){
            if(board[i][j+1].ifavalible)
                spareGrid++;
        }
        
        if(j-1 >= 0){
            if(board[i][j-1].ifavalible)
                spareGrid++;
        }
        return spareGrid;
    }
    void set0(){
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                
                if(board[i][j].type == 2){
                    if(i+1 < rows && j-1 >=0 && i-1 >=0 && j+1 < cols){
                        if(board[i+1][j-1].type == 1 && board[i-1][j+1].type == 5)
                            board[i-1][j+1].ifavalible = false;
                        if(board[i+1][j-1].type == 5 && board[i-1][j+1].type == 1)
                            board[i+1][j-1].ifavalible = false;
                    }
                    if(i+1 < rows && j+1 < cols && i-1 >=0 && j-1 >= 0){
                        if(board[i+1][j+1].type == 1 && board[i-1][j-1].type == 5)
                            board[i+1][j+1].ifavalible = false;
                        if(board[i-1][j-1].type == 5 && board[i+1][j+1].type == 1)
                            board[i+1][j+1].ifavalible = false;
                    }
                }
                 
                
                if(board[i][j].type == 3){
                    if(i+1 < rows && j-1 >=0){
                        if(board[i+1][j-1].type == 5)
                            board[i+1][j-1].ifavalible = false;
                    }
                    if(i-1 >=0 && j+1 < cols){
                        if(board[i-1][j+1].type == 5)
                            board[i-1][j+1].ifavalible = false;
                    }
                    if(i-1 >=0 && j-1 >= 0){
                        if(board[i-1][j-1].type == 5)
                            board[i-1][j-1].ifavalible = false;
                    }
                    if(i+1 < rows && j+1 < cols){
                        if(board[i+1][j+1].type == 5)
                            board[i+1][j+1].ifavalible = false;
                    }
                }
                
                if(board[i][j].avalibleNum == 0){
                    if(i+1 < rows) board[i+1][j].ifavalible = false;
                    if(i-1 >= 0) board[i-1][j].ifavalible = false;
                    if(j+1 < cols) board[i][j+1].ifavalible = false;
                    if(j-1 >= 0) board[i][j-1].ifavalible = false;
                }
            }
        }
    }
    vector<location> sequenceForFill(){
        vector<location> sequence;
        location tmp;
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                if(board[i][j].type == 2){
                    if(i+1 < rows){
                        if(board[i+1][j].ifavalible){
                            tmp.set(i+1, j);
                            sequence.push_back(tmp);
                        }
                    }
                    if(i-1 >= 0){
                        if(board[i-1][j].ifavalible){
                            tmp.set(i-1, j);
                            sequence.push_back(tmp);
                        }
                    }
                    if(j+1 < cols){
                        if(board[i][j+1].ifavalible){
                            tmp.set(i, j+1);
                            sequence.push_back(tmp);
                        }
                    }
                    if(j-1 >= 0){
                        if(board[i][j-1].ifavalible){
                            tmp.set(i, j-1);
                            sequence.push_back(tmp);
                        }
                    }
                }
            }
        }
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                if(board[i][j].type == 4){
                    if(i+1 < rows){
                        if(board[i+1][j].ifavalible){
                            tmp.set(i+1, j);
                            sequence.push_back(tmp);
                        }
                    }
                    if(i-1 >= 0){
                        if(board[i-1][j].ifavalible){
                            tmp.set(i-1, j);
                            sequence.push_back(tmp);
                        }
                    }
                    if(j+1 < cols){
                        if(board[i][j+1].ifavalible){
                            tmp.set(i, j+1);
                            sequence.push_back(tmp);
                        }
                    }
                    if(j-1 >= 0){
                        if(board[i][j-1].ifavalible){
                            tmp.set(i, j-1);
                            sequence.push_back(tmp);
                        }
                    }
                }
            }
        }
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                if(board[i][j].type == 3){
                    if(i+1 < rows){
                        if(board[i+1][j].ifavalible){
                            tmp.set(i+1, j);
                            sequence.push_back(tmp);
                        }
                    }
                    if(i-1 >= 0){
                        if(board[i-1][j].ifavalible){
                            tmp.set(i-1, j);
                            sequence.push_back(tmp);
                        }
                    }
                    if(j+1 < cols){
                        if(board[i][j+1].ifavalible){
                            tmp.set(i, j+1);
                            sequence.push_back(tmp);
                        }
                    }
                    if(j-1 >= 0){
                        if(board[i][j-1].ifavalible){
                            tmp.set(i, j-1);
                            sequence.push_back(tmp);
                        }
                    }
                }
            }
        }
        
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                if(board[i][j].type == 1){
                    if(i+1 < rows){
                        if(board[i+1][j].ifavalible){
                            tmp.set(i+1, j);
                            sequence.push_back(tmp);
                        }
                    }
                    if(i-1 >= 0){
                        if(board[i-1][j].ifavalible){
                            tmp.set(i-1, j);
                            sequence.push_back(tmp);
                        }
                    }
                    if(j+1 < cols){
                        if(board[i][j+1].ifavalible){
                            tmp.set(i, j+1);
                            sequence.push_back(tmp);
                        }
                    }
                    if(j-1 >= 0){
                        if(board[i][j-1].ifavalible){
                            tmp.set(i, j-1);
                            sequence.push_back(tmp);
                        }
                    }
                }
            }
        }
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                if(board[i][j].type == 5){
                    tmp.set(i, j);
                    sequence.push_back(tmp);
                }
            }
        }
        return sequence;
    }
    int minPossiblity(int row,int col){
        //int min = 999;
        int min = 0;
        if(row+1 < rows){
            if(board[row+1][col].type > 0 && board[row+1][col].type <=4)
                min = (min < board[row+1][col].avalibleNum) ? min : board[row+1][col].avalibleNum;
        }
        if(row-1 >= 0){
            if(board[row-1][col].type > 0 && board[row-1][col].type <=4)
                min = (min < board[row-1][col].avalibleNum) ? min : board[row-1][col].avalibleNum;
        }
        if(col+1 < cols){
            if(board[row][col+1].type > 0 && board[row][col+1].type <=4)
                min = (min < board[row][col+1].avalibleNum) ? min : board[row][col+1].avalibleNum;
        }
        if(col-1 >= 0){
            if(board[row][col-1].type > 0 && board[row][col-1].type <=4)
                min = (min < board[row][col-1].avalibleNum) ? min : board[row][col-1].avalibleNum;
        }
        //if(min == 999) min = 0;
        return min;
    }//
    vector<location> orderToFill(){
        vector<location> vec;
        location tmp;
        tmp.row = 0;
        tmp.col = 0;
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                if(!board[i][j].ifavalible) continue;
                tmp.row = i;
                tmp.col = j;
                tmp.IntAround = minPossiblity(i, j);
                vec.push_back(tmp);
            }
        }
        quickSort(vec, 0,(int) vec.size()-1);
        return vec;
    }
    
    int certainGridNum(){
        set0();
        int numOFLight = 0;
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                if(board[i][j].avalibleNum == spareGrid(i, j) && board[i][j].avalibleNum != 0){
                    if(i+1 < rows && board[i+1][j].ifavalible){
                        setLight(i+1, j);numOFLight++;
                    }
                    if(i-1 >= 0 && board[i-1][j].ifavalible){
                        setLight(i-1, j);numOFLight++;
                    }
                    if(j+1 < cols && board[i][j+1].ifavalible){
                        setLight(i, j+1);numOFLight++;
                    }
                    if(j-1 >= 0 && board[i][j-1].ifavalible){
                        setLight(i, j-1);numOFLight++;
                    }
                }
            }
        }
        return numOFLight;
    }
    int certainGridFree(){
        set0();
        int numOfLight = 0;
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                if(!board[i][j].ifavalible && board[i][j].lightUp == 0 && board[i][j].type == 5){
                    //up and down was block search left and right
                    
                    int k = 0;
                    vector<int> storgePosL;
                    while(board[i][j+k].type == 5 || board[i][j+k].type == 7){
                        if(board[i][j+k].ifavalible) storgePosL.push_back(j+k);
                        k++;
                        if(j+k >= cols) break;
                    }
                    k = 0;
                    while(board[i][j-k].type == 5 || board[i][j-k].type == 7){
                        if(board[i][j-k].ifavalible) storgePosL.push_back(j-k);
                        k++;
                        if(j-k < 0) break;
                    }
                    //if(storgePosL.size() == 1){setLight(i, storgePosL[0]);numOfLight++;}
                    //left and right
                    k = 0;
                    vector<int> storgePosV;
                    while(board[i+k][j].type == 5 || board[i+k][j].type == 7){
                        if(board[i+k][j].ifavalible) storgePosV.push_back(i+k);k++;
                        if(i+k >= rows) break;
                    }
                    k = 0;
                    while(board[i-k][j].type == 5 || board[i-k][j].type == 7){
                        if(board[i-k][j].ifavalible) storgePosV.push_back(i-k);k++;
                        if(i-k < 0) break;
                    }
                    
                    if(storgePosV.size() == 0 && storgePosL.size() == 1){
                        if(setLight(i, storgePosL[0]))
                            numOfLight++;
                        //cout << "2 in the place of " << i << " " << j << endl;
                        continue;
                    }
                    if(storgePosV.size() == 1 && storgePosL.size() == 0){
                        if(setLight(storgePosV[0], j))
                            numOfLight++;
                        //cout << "1 in the place of " << i << " " << j << endl;
                        continue;
                    }
                        
                }
                
                if(board[i][j].ifavalible && board[i][j].lightUp == 0){
                    //above
                    int k = 0;
                    vector<int> storgePosV;
                    while(board[i+k][j].type == 5 || board[i+k][j].type == 7){
                        if(board[i+k][j].ifavalible) storgePosV.push_back(i+k);k++;
                        if(i+k >= rows) break;
                    }
                    k = 0;
                    while(board[i-k][j].type == 5 || board[i-k][j].type == 7){
                        if(board[i-k][j].ifavalible) storgePosV.push_back(i-k);k++;
                        if(i-k < 0) break;
                    }
                    
                    vector<int> storgePosL;
                    k = 0;
                    while(board[i][j+k].type == 5 || board[i][j+k].type == 7){
                        if(board[i][j+k].ifavalible) storgePosL.push_back(j+k);k++;
                        if(j+k >= cols) break;
                    }
                    k = 0;
                    while(board[i][j-k].type == 5 || board[i][j-k].type == 7){
                        if(board[i][j-k].ifavalible) storgePosL.push_back(j-k);k++;
                        if(j-k < 0) break;
                    }
                    if(storgePosV.size() == 2 && storgePosL.size() == 2){
                        if(setLight(i, j))
                            numOfLight++;
                       // cout << "in the place of " << i << " " << j << endl;
                    }
                }
            }
        }
        return numOfLight;
    }
    

    bool checkWhole(){
        
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                if(board[i][j].type == 5) return false;
            }
        }
        return true;
    }
    void preSolve(){//set0Plus() will be used here only
        int NUM = certainGridNum();
        int FREE = certainGridFree();
        int count1 = 0;
        int count2 = 0;
        int count3 = 0;
        while(!checkWhole()){
            NUM = 1;
            FREE = 1;
            while(NUM != 0){
                NUM = certainGridNum();
                count2++;
            }
            while(FREE != 0){
                FREE = certainGridFree();
                count3++;
            }
            if(count3 == 1 && count2 == 1) break;
            count2 = 0;
            count3 = 0;
            count1++;
        }
    }
    bool solver(Puzzle & p,int height = 0){//main part of the puzzle solver
        if(!p.checkContradiction1() || !p.checkContradiction2()){
            //cout << 1232 << endl;
            return false;
        }
        if(p.checkWhole()){
            cout << "Solved :" << endl;
            p.printPuzzle();
            return true;
        }
        vector<location> sequence = p.orderToFill();//failed
        int count = 0;
        for(int i=0;i<sequence.size();i++){
            if(p.board[sequence[i].row][sequence[i].col].ifavalible){
                Puzzle tmpPuzzle(p);
                count++;
                tmpPuzzle.setLight(sequence[i].row, sequence[i].col);
                tmpPuzzle.preSolve();
                //tmpPuzzle.printPuzzle();
                if(solver(tmpPuzzle,height+1)){
                    p = tmpPuzzle;
                    return true;
                }
                else{
                    p.board[sequence[i].row][sequence[i].col].ifavalible = false;
                    if(!p.checkContradiction1() || !p.checkContradiction2()) return false;
                }
            }
        }
        /*
        for(auto place : sequence){
            if(p.board[place.row][place.col].ifavalible){
                Puzzle tmpPuzzle(p);
                count++;
                tmpPuzzle.setLight(place.row, place.col);
                tmpPuzzle.preSolve();
                if(solver(tmpPuzzle,height+1)){
                    p = tmpPuzzle;
                    return true;
                }
                else{
                    p.board[place.row][place.col].ifavalible = false;
                    if(!p.checkContradiction1() || !p.checkContradiction2()) return false;
                }
            }
        }
        */
        return false;
        
    }
    bool checkContradiction1(){
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                if(!board[i][j].ifavalible && board[i][j].type == 5){
                    int num=0;
                    int count=1;
                    if(i+count < rows){
                        while((!board[i+count][j].ifavalible)){
                            num++;
                            count++;
                            if(i+count >= rows) break;
                        }
                    }
                    count = 1;
                    if(i-count >= 0){
                        while((!board[i-count][j].ifavalible)){
                            num++;
                            count++;
                            if(i-count < 0) break;
                        }
                    }
                    count = 1;
                    if(j+count < cols){
                        while((!board[i][j+count].ifavalible)){
                            num++;
                            count++;
                            if(j+count >= cols) break;
                        }
                    }
                    count = 1;
                    if(j-count >= 0){
                        while((!board[i][j-count].ifavalible)){
                            num++;
                            count++;
                            if(j-count < 0) break;
                        }
                    }
                    if(num==rows+cols-2)
                        return false;
                }
            }
        }
        return true;
    }
   
    bool checkContradiction2(){
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                if(board[i][j].type>=1 && board[i][j].type<=4){
                    //cout << i << " " << j << ":" << endl;
                    //cout << spareGrid(i, j) << " " << board[i][j].avalibleNum << endl;
                    if(spareGrid(i,j)<board[i][j].avalibleNum)
                        return false;
                }
            }
        }
        return true;
    }
    void printAvailble(){
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                cout << board[i][j].ifavalible << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    void outerPlug(Puzzle & p){
        p.printPuzzle();
        vector<location> tmp = p.orderToFill();
        /*
        for(int i=0;i<tmp.size();i++){
            cout << "(" << setw(2) << left << tmp[i].row << "," << setw(2) << left << tmp[i].col << ")  ";
            if(i%10 == 9) cout << endl;
        }
        cout << endl;
        */
        clock_t t1,t2;
        t1 = t2 = clock();
        set0();
        preSolve();
        solver(p);
        //printPuzzle();
        t2 = clock();
        cout << "Time consumed : " << (double)(t2 - t1) / CLOCKS_PER_SEC * 1000 << " ms.\n";
    }
};
//presolve exist problem
int main(){
    string s ;
    int row,col;
    //cin >> row >> col >> s;
    string s1 = "...1...X...2.1......0...X...X......0..1...1...4...XX.0..X....X..X..X......X...X....1.....2..1...2..0.....X....2..X...X....X.1...1......X.....2....1.X.X0....X........X......X.2.1.121X.X.X.X......X........1....01.3.X....X.....X......X...1.X....X...2..X....X.....3..X...1..1.....1....2...1......X..2..1....1..X.11...X...X...X..X......X...1...X......X.0...1...1...";//490 18 20
    string s2 = "..1...1...1....X...2......3....1...1...2..1....1..1..1...3.....2...1...X......X.....X....1..1...X......1.1......1..X.X.......0...X..1...X..1...1....1.X..X....X...........2.........1.1....3...1..2..1...2...1..2...X..2....X....1..2....1..1.......4.....1........X...X....1..X.....X.....3..X.....1......1.X..X...2..X.......1......2......0......1.......1..1...2..X.X......X.....X..1.....1.....X..1....X...1........0.....3.......1..X....X..X....X....2..X...X..1...3...X..1..X...2....X.X.........2...........X....X..X.X....X...X..X...X..1...X.......X.X..1......1.1......1...2..3....1.....2......1...1...2.....X...1..1..3....1..2...1...X....X......1...X....1...1...0..";//700 22 30
    string s3 = "....1.........2...1.1.X...2....X..X........2...X...X..1..X...1.....1........X.2...1.X...X1.3..1..2..1.....1....X......X..1.X...1......X..X.....X.1....1..1....1.2.....X..1......1...1.X..X......X....2.....X..X..0..2.11...2.1...1.X........1.....X...1..2..X...1...X........1..1....1...1.1.X...X.........1....";//483 16 19
    string s4 = "..X1..X....1............0....2..1X..";//6 6
    string s5 = "....3........1......X....0.X.....X...X...XX..X.X1...0.....1........1....2..X..X..X....X..X...0.X..1..X..1....X.....X....1...0..2...4....X.....X....X..2..X..4.X...X..1....1..2..X..3....2........1.....2...X0.X..2X...1...X.....0.2....1......0........1....";//660 14 18******
    string s6 = "...................1XX3..X..XXX0....2.X...X...0.X..X....2X...XX....1........2................0.........1....0...1....X..1X...X...X...21.1....1.....1....1.X1...1...1...1X..1....X...0....2.........1................1........1....XX...X2....1..X.X...X...1.0....1X10..0..2XX0...................";//400 17 17 ???
    string s7 = "X.....1..........X.....X..3.X...X.X..X.X...1.2...2...X.2...X1...X.1...2....X.....X....2.....1....1...X.X...1X...1.1...0...X.1...0.1..X.X...2.X..X.....1.......1..1.....XX.....1..3.......X.....X..0.0...X.2..X.X...1.2...1...X.1...X2...X.0...X....2.....X....X.....0....3...X.1...10...3.X...2...3.1...2.1..X.3...X.2..X.....1..........1.....0";//718 14 24;
    string s8 = "..1..X.....X..1..........1........X..20...1...2X..0..................1...1X...1X...X....X....X....X....2.1.X.....0.0.2........2.X.......X.0.X...1...1.X.X.......X.X........1.1.1.....X.X.1....1....X....1....X...XX...11...1..................X..10...X...21..1........1..........0..1.....1..X..";//768 17 17 fuking serious???
    string s9 = "......0..2..2.......X..3.....1.....2..X.....X...X...X.....1..0...0.X......X.....X...1...X.1..X..1..1...4..1...1.X..1....X.......X......X..1...X....1...X...2..1.1...X..X......1...X....2...2..X.....1.0...X..0....0....3...X..X....1......X..1..X.....X.......X....X..X..X...1..X..X..1....X......3...X..1..1......1..X..1.1...2..2...2..2..X...1..1.....X.....X..X.........1...1........X...1........X...X.........2..1.....X.....X..1...X..X..2...1..1...2.1..1..1......X..2..2...1......X....1..X..0..X...X..X..X....X.......X.....X..1..2......X....2..X...X....1....X..X...3.X.....X..2...1....X...1......1..X...1.2..2...X...X....1...1..X......1.......X....X..2.1...1..1...1..X..2..0.X...2...2.....1......1.2...4..X.....2...3...X.....X..1.....X.....1..1.......X..1..2......";//740 23 33
    string s10 = ".......X.........1.........2...3....2.X....2...1...2........X...1........2....X....X.......X....X........2....2...X....3.........3....2.....2....X.....2.....XX..X.X..XX.....3.1.....X...........X.....1...X..X.1.X...X.1.1..X........2.............2.......X.X...1.1...1.X...2.1...2....X....X.X....X....X...........................X....X....X.X....X....2...1.X...X.1...1.X...X.2.......2.............3........2..X.1.0...X.1.X..1...2.....X...........X.....2.1.....02..X.X..XX.....1.....X....3.....2....1.........1....X...2....2........1....X.......2....X....X........1...2........X...3...1....X.1....X...0.........1.........X.......";//25 25
    Puzzle akari2(23,33,s9);
    akari2.outerPlug(akari2);
    cout << "Contradiction1 satisfied :" << akari2.checkContradiction1() << endl;
    cout << "Contradiction2 satisfied :" << akari2.checkContradiction2() << endl;
    cout << "Puzzle finished :" << akari2.checkWhole() << endl;
    
    return 0;
}
