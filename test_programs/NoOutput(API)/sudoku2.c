/*The following program is an implementation of a Sudoku Solver in C.
Sudoku is a 9*9 grid in which each row,each column and each 3*3 grid contains all numbers from 1 to 9 only once.
The program uses backtracking approach to solve the sudoku. There is a recursive function to solve the sudoku.
*/
#include<stdio.h>
int sudoku[9][9];//The array which stores entries for the sudoku
void solvesudoku(int,int);
int checkrow(int row,int num)
{//This function checks whether we can put the number(num) in the row(row) of the Sudoku or not
int column;
for(column=0;column<9;column++)
    if(sudoku[row][column]==num)
        return 0 ;//If the number is found already present at certain location we return zero
return 1;//If the number is not found anywhere we return 1
}
int checkcolumn(int column,int num)
{//This function checks whether we can put the number(num) in the column(column) of the Sudoku or not
int row;
for(row=0;row<9;row++)
    if(sudoku[row][column]==num)
        return 0;//If the number is found already present at certain location we return zero
return 1;//If the number is not found anywhere we return 1
}
int checkgrid(int row,int column,int num)
{//This function checks whether we can put the number(num) in the 3*3 grid or not
//We get the starting row and column for the 3*3 grid
row=(row/3)*3 ;
column=(column/3)*3;
int r,c;
for(r=0;r<3;r++)
    for(c=0;c<3;c++)
         if(sudoku[row+r][column+c]==num)
            return 0;//If the number is found already present at certain location we return zero
return 1;//If the number is not found anywhere we return 1
}
void navigate(int row,int column)
{//Function to move to the next cell in case we have filled one cell
if(column<8)
        solvesudoku(row,column+1);
    else
       solvesudoku(row+1,0);
}
void display()
{//The function to display the solved Sudoku
int row,column;

for(row=0;row<9;row++)
{
for(column=0;column<9;column++)
printf("%d ",sudoku[row][column]);
}
}
void solvesudoku(int row,int column)
{
    if(row>8)//If the row number is greater than 8 than we have filled all cells hence we have solved the sudoku
    display();
    if(sudoku[row][column]!=0)
    navigate(row,column);//If the value filled at a cell is not zero than it is filled with some value from 0 to 9 hence we move further
    else
    {
        int ctr;//This is a counter to check numbers from 1 to 9 whether the number can be filled in the cell or not
        for(ctr=1;ctr<=9;ctr++)
        {//We check row,column and the grid
        if((checkrow(row,ctr)==1)&&(checkcolumn(column,ctr)==1)&&(checkgrid(row,column,ctr)==1))
        {
            sudoku[row][column]=ctr;
             navigate(row,column);
        }
        }
        sudoku[row][column]=0;//No valid number was found so we clean up and return to the caller.
    }
    
}
int main()
{
int row,column;

sudoku[0][0] = 1;
sudoku[0][1] = 0;
sudoku[0][2] = 3;
sudoku[0][3] = 4;
sudoku[0][4] = 0;
sudoku[0][5] = 0;
sudoku[0][6] = 7;
sudoku[0][7] = 0;
sudoku[0][8] = 9;
sudoku[1][0] = 0;
sudoku[1][1] = 5;
sudoku[1][2] = 6;
sudoku[1][3] = 0;
sudoku[1][4] = 8;
sudoku[1][5] = 9;
sudoku[1][6] = 0;
sudoku[1][7] = 2;
sudoku[1][8] = 3;
sudoku[2][0] = 0;
sudoku[2][1] = 8;
sudoku[2][2] = 9;
sudoku[2][3] = 1;
sudoku[2][4] = 0;
sudoku[2][5] = 3;
sudoku[2][6] = 4;
sudoku[2][7] = 0;
sudoku[2][8] = 6;
sudoku[3][0] = 2;
sudoku[3][1] = 1;
sudoku[3][2] = 4;
sudoku[3][3] = 0;
sudoku[3][4] = 6;
sudoku[3][5] = 5;
sudoku[3][6] = 0;
sudoku[3][7] = 9;
sudoku[3][8] = 7;
sudoku[4][0] = 3;
sudoku[4][1] = 0;
sudoku[4][2] = 0;
sudoku[4][3] = 8;
sudoku[4][4] = 0;
sudoku[4][5] = 7;
sudoku[4][6] = 0;
sudoku[4][7] = 1;
sudoku[4][8] = 4;
sudoku[5][0] = 8;
sudoku[5][1] = 0;
sudoku[5][2] = 7;
sudoku[5][3] = 0;
sudoku[5][4] = 1;
sudoku[5][5] = 4;
sudoku[5][6] = 0;
sudoku[5][7] = 6;
sudoku[5][8] = 5;
sudoku[6][0] = 0;
sudoku[6][1] = 3;
sudoku[6][2] = 1;
sudoku[6][3] = 0;
sudoku[6][4] = 4;
sudoku[6][5] = 0;
sudoku[6][6] = 9;
sudoku[6][7] = 7;
sudoku[6][8] = 8;
sudoku[7][0] = 6;
sudoku[7][1] = 4;
sudoku[7][2] = 0;
sudoku[7][3] = 9;
sudoku[7][4] = 7;
sudoku[7][5] = 0;
sudoku[7][6] = 5;
sudoku[7][7] = 3;
sudoku[7][8] = 1;
sudoku[8][0] = 0;
sudoku[8][1] = 7;
sudoku[8][2] = 8;
sudoku[8][3] = 0;
sudoku[8][4] = 0;
sudoku[8][5] = 1;
sudoku[8][6] = 0;
sudoku[8][7] = 4;
sudoku[8][8] = 2;
solvesudoku(0,0);//We start solving the sudoku.
}
