# Sudoku Puzzle

This C program generates Sudoku puzzles of varying difficulty levels and provides a user-friendly interface for solving them. Sudoku is a puzzle game where the goal is to fill a 9x9 grid with digits (typically 1-9) so that each row, column, and 3x3 subgrid (referred to as "boxes") contains all digits from 1 to 9 without any repetitions.

## Functionality Overview:
1. **Grid Generation**: The program generates a fully filled 9x9 Sudoku grid adhering to Sudoku rules using the backtracking method and the `isSafe()` function to ensure validity.
2. **Difficulty Setting**: The `setDifficulty()` function converts the filled grid into a puzzle by randomly removing values within specified upper and lower limits, offering different difficulty levels.
3. **User Interface**: The program utilizes the `GetCh()` function to allow players to navigate through the grid and input numbers without needing to press enter. It prevents inserting numbers into filled cells, allows users to remove their own filled numbers, and marks incorrect user-filled cells with a '^' symbol.
4. **Winning Condition**: At the end of each iteration, the program checks if the winning condition is met and displays a congratulatory message along with the solved grid.

In summary, this code provides a user-friendly interface for solving Sudoku puzzles of different difficulty levels, ensuring adherence to rules and providing helpful feedback during the game.
