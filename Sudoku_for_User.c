#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>

char GetCh();
void setDifficulty(int, int);
char *citoa(int num, char *str, int, int, int, int);
bool generate(int, int);
bool isSafe(int, int, int);

int selected_row, selected_col, for_user, flag;
int for_each_subgrid[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
int grid[9][9] = {0}, user_grid[9][9] = {0};
char box_value_final[] = " ";
bool not_removed[9][9] = {false}, skip[9][9] = {false};
char list[9][9] = {"         ", // Array consisting of actual numbers to show in grid
                   "         ",
                   "         ",
                   "         ",
                   "         ",
                   "         ",
                   "         ",
                   "         ",
                   "         "};
char list_right[9][9] = {"         ", // Used to show the required symbol to the right of numbers whenever required
                         "         ",
                         "         ",
                         "         ",
                         "         ",
                         "         ",
                         "         ",
                         "         ",
                         "         "};
char list_left[9][9] = {"         ", // Used to show the required symbol to the left of numbers whenever required
                        "         ",
                        "         ",
                        "         ",
                        "         ",
                        "         ",
                        "         ",
                        "         ",
                        "         "};
void box() // Actual grid structure which will be shown on console
{
    printf("\n\n");
    for (int row = 0; row < 9; row++)
    {
        printf(" %c%c%c | %c%c%c | %c%c%c || %c%c%c | %c%c%c | %c%c%c || %c%c%c | %c%c%c | %c%c%c ", list_left[row][0], list[row][0], list_right[row][0], list_left[row][1], list[row][1], list_right[row][1], list_left[row][2], list[row][2], list_right[row][2], list_left[row][3], list[row][3], list_right[row][3], list_left[row][4], list[row][4], list_right[row][4], list_left[row][5], list[row][5], list_right[row][5], list_left[row][6], list[row][6], list_right[row][6], list_left[row][7], list[row][7], list_right[row][7], list_left[row][8], list[row][8], list_right[row][8]);
        if (row == 2 || row == 5)
        {
            printf("\n-------------------------------------------------------\n-------------------------------------------------------\n");
        }
        else
            printf("\n-------------------------------------------------------\n");
    }
}
void random_list(int numbers[]) // Randomize the array of number frim 1 to 9 ti make a unique puzzle
{
    for (int i = 8; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }
}
bool isSafe(int row, int col, int allocated) // Checks if the alloted number follows the condition of suduko
{
    // checking for row and column
    for (int i = 0; i < 9; i++)
    {
        if (grid[row][i] == allocated || grid[i][col] == allocated)
        {
            return false;
        }
    }
    // checking for 3x3 subgrid
    int startRow = row - (row % 3);
    int startCol = col - (col % 3);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid[startRow + i][startCol + j] == allocated)
            {
                return false;
            }
        }
    }
    return true;
}
void setDifficulty(int upper, int lower) // Sets the difficulty of problem by removing values in cells randomly on the basis of upper and lower limit
{
    int number_of_cell_to_keep = (rand() % (upper - lower)) + lower;
    int row, col;
    for (int i = 0; i < number_of_cell_to_keep; i++)
    {
        do
        {
            row = rand() % 9;
            col = rand() % 9;
        } while (not_removed[row][col]);

        not_removed[row][col] = true;
        char *ptr = citoa(grid[row][col], box_value_final, 0, 0, 0, 1);
        user_grid[row][col] = grid[row][col];
        list_left[selected_row][selected_col] = *ptr;
        list[row][col] = *(ptr + 1);
    }
}
bool generate(int row, int col) // Generates a complete filled grid
{
    if (row == 8 && col == 9)
    {
        return true;
    }

    if (col == 9)
    {
        col = 0;
        row++;
    }

    random_list(for_each_subgrid);

    for (int i = 0; i < 9; i++)
    {
        int num = for_each_subgrid[i];
        if (isSafe(row, col, num))
        {
            grid[row][col] = num;
            if (generate(row, col + 1))
            {
                return true;
            }
            grid[row][col] = 0;
        }
    }
    return false;
}
void move_left_or_up(int *var) // Used to shift the user control to left cell or cell above
{
    if (*var > 0)
        (*var)--;
    else
        *var = 8;
}
void move_right_or_down(int *var) // Used to shift the user control to right cell or cell below
{
    if (*var < 8)
        (*var)++;
    else
        *var = 0;
}
int main()
{
    int row, col, flag, user_input, difficulty;
    char *ptr, ch, choice;
    srand(time(NULL));
    random_list(for_each_subgrid);

    if (generate(0, 0))
    {
        /*Difficulty Levels:1. Easy: Around 36 to 46 given cells .
                            2. Medium: Around 32 to 35 given cells.
                            3. Hard: Around 28 to 31 given cells.
                            4. Expert: Around 22 to 27 given cells.
                            5. Diabolical: Fewer than 22 given cells.*/
        setDifficulty(46, 36);
    }
    else
    {
        printf("Failed to generate relevent sudoku. Please try again");
        exit(0);
    }
    while (1)
    {
        box();
        while (1)
        {
            printf("\nUse arrow key to navigate and number to insert ('Backspace' to remove): ");
            {
                ch = GetCh(); // Take Input from user
            }
            if (ch == '<')
            {
                move_left_or_up(&selected_col);
            }
            else if (ch == '>')
            {
                move_right_or_down(&selected_col);
            }
            else if (ch == 'v')
            {
                move_right_or_down(&selected_row);
            }
            else if (ch == '^')
            {
                move_left_or_up(&selected_row);
            }
            else if (ch == 'f') // If user wants to remove a value for a cell
            {
                if (!not_removed[selected_row][selected_col])
                {
                    char *ptr = citoa(0, box_value_final, 1, 0, 0, 1);
                    user_grid[selected_row][selected_col] = 0;
                    list[selected_row][selected_col] = *(ptr + 1);
                    list_right[selected_row][selected_col] = *(ptr + 2);
                    skip[selected_row][selected_col] = false;
                }
                else
                {
                    system("cls");
                    box();
                    printf("Permanent Numbers can not be removed\n\n");
                    continue;
                }
            }
            else
            {
                if (!not_removed[selected_row][selected_col])
                {
                    break;
                }
                else
                {
                    system("cls");
                    box();
                    printf("There is already a permanent number in this cell\n\n");
                    continue;
                }
            }
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    if (list_right[i][j] == '*')
                        list_right[i][j] = ' ';
                }
            }
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    char *ptr = citoa(grid[i][j], box_value_final, 0, 0, 0, 0);
                    list_left[i][j] = *ptr;
                }
            }
            system("cls");
            char *ptr = citoa(grid[selected_row][selected_col], box_value_final, 0, 0, 0, 1);
            list_left[selected_row][selected_col] = *ptr;
            box();
        }

        row = selected_row;
        col = selected_col;

        user_input = ch - '0';

        system("cls");
        if (not_removed[row][col])
        {
            printf("\nThere is already a permanent number in this cell\n\n");
            continue;
        }

        char *ptr = citoa(user_input, box_value_final, 1, user_input, 0, 1);
        user_grid[row][col] = user_input;
        list[row][col] = *(ptr + 1);

        for (int i = 0; i < 9; i++) // Part of code to add required '*' and '^' on the basis of user input and situation
        {
            for (int j = 0; j < 9; j++)
            {

                if (user_input != grid[row][col])
                {
                    if (i == (row) && j == (col))
                    {
                        char *ptr = citoa(user_grid[i][j], box_value_final, 1, user_input, 1, 1);
                        skip[i][j] = true;
                        list_right[i][j] = *(ptr + 2);
                    }
                    else
                    {
                        char *ptr = citoa(user_grid[i][j], box_value_final, 0, user_input, 1, 0);
                    }
                }
                else
                {
                    if (i == (row) && j == (col))
                    {
                        char *ptr = citoa(user_grid[i][j], box_value_final, 1, user_input, 0, 1);
                        skip[i][j] = false;
                    }
                    else
                    {
                        char *ptr = citoa(user_grid[i][j], box_value_final, 0, user_input, 1, 0);
                    }
                }
                list[i][j] = *(ptr + 1);
                if (!skip[i][j])
                {
                    list_right[i][j] = *(ptr + 2);
                }
            }
        }
        system("cls");

        for (int i = 0; i < 9; i++) // Checks on winning condition
        {
            for (int j = 0; j < 9; j++)
            {
                if (grid[i][j] != user_grid[i][j])
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 1)
            {
                break;
            }
        }
        if (flag != 1)
        {
            break;
        }
        else
            flag = 0;
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            list_right[i][j] = ' ';
            list_left[i][j] = ' ';
        }
    }
    box();
    printf("\n Congratulations !! You have solved this Sudoku Problem\n");
}
char GetCh() // Function which takes input from user using arrow key, without having to press enter
{
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); // recognises standard input device- usually keyboard
    INPUT_RECORD irInputRecord;                     // stores information about the input event - ASCII, key press etc.
    DWORD dwEventsRead;                             // stores number of input event
    CHAR cChar, fChar;
    while (1)
    {
        if (ReadConsoleInputA(hStdin, &irInputRecord, 1, &dwEventsRead)) // Read the whole input event
        {
            if (irInputRecord.EventType == KEY_EVENT && irInputRecord.Event.KeyEvent.bKeyDown) // checks if the input event is a key event (i.e., a key was pressed or released) and if it corresponds to a key press (not a key release).
            {
                cChar = irInputRecord.Event.KeyEvent.wVirtualKeyCode; // stores the virtual key codes of the input
                fChar = irInputRecord.Event.KeyEvent.uChar.AsciiChar; // stores the ASCII values of key pressed

                if (cChar == VK_LEFT) // left arrow key was pressed
                {
                    return '<';
                }
                else if (cChar == VK_UP) // Up arrow key was pressed
                {
                    return '^';
                }
                else if (cChar == VK_RIGHT) // Right arrow key was pressed
                {
                    return '>';
                }
                else if (cChar == VK_DOWN) // Down arrow key was pressed
                {
                    return 'v';
                }
                else if (cChar == VK_BACK) //  Backspace key was pressed
                {
                    return 'f';
                }
                else if (fChar >= 49 && fChar <= 57) // A numebr ranging from 1 to 9 is pressed
                {
                    return fChar;
                }
            }
        }
    }
}
char *citoa(int num, char *str, int flag, int user_input, int flag1, int selected)
{
    /* Handle 0 explicitly, otherwise empty string is
     * printed for 0 */
    if (selected == 1)
    {
        str[0] = '>';
    }
    else
        str[0] = ' ';

    if (num == 0)
    {
        str[1] = ' ';
        str[2] = ' ';
        str[3] = '\0';
        return str;
    }
    // Process individual digits

    int rem = num % 10;
    str[1] = rem + '0';

    if ((num == user_input) && (flag1 == 1))
    {
        if (flag == 1)
        {
            str[2] = '^';
        }
        else
            str[2] = '*';
    }
    else
    {
        str[2] = ' ';
    }
    str[3] = '\0';
    // Reverse the string
    return str;
}
