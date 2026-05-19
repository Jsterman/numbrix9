

class Numbrix9:
    def __init__(self):
        self.grid = []
        for i in range(9):
            row = []
            for j in range(9):
                row.append(0)
            self.grid.append(row)

        self.grid[0][0] = 81
        self.grid[0][2] = 77
        self.grid[0][4] = 73
        self.grid[0][6] = 69
        self.grid[0][8] = 65
        self.grid[1][1] = 79
        self.grid[1][3] = 75
        self.grid[1][5] = 71
        self.grid[1][7] = 67
        self.grid[2][0] = 55
        self.grid[2][8] = 63
        self.grid[3][1] = 53
        self.grid[3][7] = 19
        self.grid[4][0] = 43
        self.grid[4][8] = 17
        self.grid[5][1] = 41
        self.grid[5][7] = 15
        self.grid[6][0] = 37
        self.grid[6][8] = 13
        self.grid[7][1] = 33
        self.grid[7][3] = 27
        self.grid[7][5] = 3
        self.grid[7][7] = 9
        self.grid[8][0] = 35
        self.grid[8][2] = 31
        self.grid[8][4] = 29
        self.grid[8][6] = 5
        self.grid[8][8] = 7

        self.missing_pos = []
        self.missing_neg = []

        for i in range(9):
            for j in range(9):
                num = self.grid[i][j]
                if num != 0:
                    if num != 1:
                        self.missing_neg.append((i, j))
                    if num != 81:
                        self.missing_pos.append((i, j))

    def solve(self):
        loops = 0
        while len(self.missing_pos) > 0 and len(self.missing_neg) > 0:
            made_change = False
            for i in range(len(self.missing_pos)):
                item = self.missing_pos[i]
                this_made_change = self.move(item, True)
                made_change = made_change or this_made_change

            for i in range(len(self.missing_neg)):
                item = self.missing_neg[i]
                this_made_change = self.move(item, False)
                made_change = made_change or this_made_change

            if not made_change:
                loops += 1
            else:
                loops = 0
            if loops > 2:
                print("Something went wrong, can't solve the puzzle.")
                break
    
    def move(self, item, pos):
        i, j = item
        num = self.grid[i][j]
        if pos:
            cf = num + 1
        else:
            cf = num - 1
        up = max(i-1, 0)
        down = min(i+1, 8)
        right = min(j+1, 8)
        left = max(i-1, 0)
        if (self.grid[up][j] == cf):
            if pos:
                self.missing_pos.remove(item)
            else:
                self.missing_neg.remove(item)
            return False
        elif (self.grid[down][j] == cf):
            if pos:
                self.missing_pos.remove(item)
            else:
                self.missing_neg.remove(item)
            return False
        elif (self.grid[i][left] == cf):
            if pos:
                self.missing_pos.remove(item)
            else:
                self.missing_neg.remove(item)
            return False
        elif (self.grid[i][right] == cf):
            if pos:
                self.missing_pos.remove(item)
            else:
                self.missing_neg.remove(item)
            return False
        
        num_possible_moves = 0
        possible_dirs = [False, False, False, False]
        if self.direction_valid(up, j, cf):
            num_possible_moves += 1
            possible_dirs[0] = True
        elif self.direction_valid(down, j, cf):
            num_possible_moves += 1
            possible_dirs[1] = True
        elif self.direction_valid(i, left, cf):
            num_possible_moves += 1
            possible_dirs[2] = True
        elif self.direction_valid(i, right, cf):
            num_possible_moves += 1
            possible_dirs[3] = True

        if num_possible_moves == 1:
            if possible_dirs[0]:
                self.grid[up][j] = cf
                if pos:
                    self.missing_pos.append((up, j))
                    self.missing_pos.remove(item)
                else:
                    self.missing_neg.append((up, j))
                    self.missing_neg.remove(item)
            elif possible_dirs[1]:
                self.grid[down][j] = cf
                if pos:
                    self.missing_pos.append((down, j))
                    self.missing_pos.remove(item)
                else:
                    self.missing_neg.append((down, j))
                    self.missing_neg.remove(item)
            elif possible_dirs[2]:
                self.grid[i][left] = cf
                if pos:
                    self.missing_pos.append((i, left))
                    self.missing_pos.remove(item)
                else:
                    self.missing_neg.append((i, left))
                    self.missing_neg.remove(item)
            elif possible_dirs[3]:
                self.grid[i][right] = cf
                if pos:
                    self.missing_pos.append((i, right))
                    self.missing_pos.remove(item)
                else:
                    self.missing_neg.append((i, right))
                    self.missing_neg.remove(item)
            return True
        return False

        
        

    def direction_valid(self, i, j, proposed_value):
        if (self.grid[i][j] != 0):
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
    puzzle.solve()
    print(puzzle.to_string())