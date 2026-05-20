import os
import csv
from copy import deepcopy
from pathlib import Path

class Numbrix9:
    def __init__(self, filename="puzzles/easy_may_19_2026.csv"):
        base_path = Path(os.path.realpath(__file__)).parent.parent
        file = open(base_path/filename)
        csvreader = csv.reader(file)
        self.orig_grid = []
        for row in csvreader:
            grid_row = []
            for j in range(9):
                grid_row.append(int(row[j]))
            self.orig_grid.append(grid_row)


        self.grid = deepcopy(self.orig_grid)

        self.missing_pos = []
        self.missing_neg = []

        self.min_num = 82
        self.min_loc = (0,0)

        self.has_nums = set()

        for i in range(9):
            for j in range(9):
                num = self.orig_grid[i][j]
                if num != 0:
                    self.has_nums.add(num)
                    if num < self.min_num:
                        self.min_loc = (i, j)
                        self.min_num = num
                    if num != 1:
                        self.missing_neg.append((i, j))
                    if num != 81:
                        self.missing_pos.append((i, j))

    def depth_first(self):
        # give the algorithm the location of the lowest number
        
        i, j = self.min_loc
        if self.min_num != 1:
            return self.depth_first_alg_dec(i, j, self.min_num)
        else:
            return self.depth_first_alg(i, j, self.min_num)
    
    def depth_first_alg_dec(self, i, j, test_value):
        if i < 0 or i >= 9 or j < 0 or j >= 9:
            return False
        # if the grid square is occupied and it doesn't match the value we want to put in it, it is not a valid path
        if self.grid[i][j] != 0 and self.grid[i][j] != test_value:
            return False
        
        self.grid[i][j] = test_value

        if test_value == 1:
            if not self.depth_first_alg(i, j, test_value):
                if self.orig_grid[i][j] != self.grid[i][j]:
                    self.grid[i][j] = self.orig_grid[i][j]
                return False
            return True
        else:
            if self.depth_first_alg_dec(i-1, j, test_value-1) or self.depth_first_alg_dec(i+1, j, test_value-1) or self.depth_first_alg_dec(i, j-1, test_value-1) or self.depth_first_alg_dec(i, j+1, test_value):
                return True
            else:
                if self.orig_grid[i][j] != self.grid[i][j]:
                    self.grid[i][j] = self.orig_grid[i][j]
                return False
            


    def depth_first_alg(self, i, j, test_value):
        # if the indecies are out of bounds, this is an invalid path
        if i < 0 or i >= 9 or j < 0 or j >= 9:
            return False
        # if the grid square is occupied and it doesn't match the value we want to put in it, it is not a valid path
        if self.grid[i][j] != 0 and self.grid[i][j] != test_value:
            return False
        # if the number exists elsewhere on the grid, this is not a valid path
        if self.grid[i][j] == 0 and test_value in self.has_nums:
            return False
        
        # mark the grid with the proposed value
        self.grid[i][j] = test_value
        self.has_nums.add(test_value)

        # if we're looking for the last number and the cell is blank or matches, we have found a valid path
        if test_value == 81 and (self.grid[i][j] == 0 or self.grid[i][j] == test_value):
            return True

        # first we see if the cell has a neighbor of the next value up. If it does, we send the algorithm through that cell. It may not be a valid path based on previous choices, so if it isn't we need to know so we can reset our current location if needed
        has_neighbor = False
        look_for = False
        if self.look_forward(i-1, j, test_value+1):
            has_neighbor = True
            look_for = self.depth_first_alg(i-1, j, test_value+1)
        elif self.look_forward(i+1, j, test_value+1):
            has_neighbor = True
            look_for = self.depth_first_alg(i+1, j, test_value+1)
        elif self.look_forward(i, j-1, test_value+1):
            has_neighbor = True
            look_for = self.depth_first_alg(i, j-1, test_value+1)
        elif self.look_forward(i, j-1, test_value+1):
            has_neighbor = True
            look_for = self.depth_first_alg(i, j-1, test_value+1)
        
        # if there was a neighbor
        if has_neighbor:
            # if it wasn't a valid path and we need to reset the grid value, do so
            if not look_for and self.orig_grid[i][j] != self.grid[i][j]:
                self.grid[i][j] = self.orig_grid[i][j]
                self.has_nums.remove(test_value)
            return look_for
        # if there was no defined neighbor, go in the various directions. If there was a valid path, return true
        elif self.depth_first_alg(i+1, j, test_value+1) or self.depth_first_alg(i-1, j, test_value+1) or self.depth_first_alg(i, j-1, test_value+1) or self.depth_first_alg(i, j+1, test_value+1):
            return True
        else:
            # no valid path found, reset this cell value if necessary
            if self.orig_grid[i][j] != self.grid[i][j]:
                self.grid[i][j] = self.orig_grid[i][j]
                self.has_nums.remove(test_value)
            return False

        # if test_value == 1 and (self.grid[i][j] == 0 or self.grid[i][j] == test_value):
        #     return True
        
        
    def look_forward(self, i, j, test_value):
        if i < 0 or i >= 9 or j < 0 or j >= 9:
            return False
        return self.grid[i][j] == test_value
        
        

    def direction_valid(self, i, j, proposed_value):
        if (self.orig_grid[i][j] != 0):
            return False
        else:
            return True
        
    def to_string(self):
        to_return = ""

        for i in range(9):
            for j in range(9):
                num = self.grid[i][j]
                if (num < 10 and num != 0):
                    to_return += " "
                if (num == 0):
                    to_return += "__"
                else:
                    to_return += str(num)
                to_return += " "
            to_return += "\n"
        return to_return
        


if __name__ == "__main__":
    puzzle = Numbrix9()
    print(puzzle.to_string())
    if puzzle.depth_first():
        print("Found valid solution!")
    else:
        print("No valid solution found")
    print(puzzle.to_string())