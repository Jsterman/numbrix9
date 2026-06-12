def find_num_paths(difference, dx, dy):
    in_path = set()
    in_path.add((dx,dy))
    def find_paths(distance, x, y):
        if (distance == 0 and (x == dx and y == dy)):
            return 1
        if (abs(dx-x)+abs(dy-y) > distance or (x,y) in in_path):
            return 0
        in_path.add((x,y))
        num_paths = 0
        num_paths += find_paths(distance-1, x-1, y)
        num_paths += find_paths(distance-1, x+1, y)
        num_paths += find_paths(distance-1, x, y-1)
        num_paths += find_paths(distance-1, x, y+1)
        in_path.remove((x,y))
        return num_paths

    return find_paths(difference, 0, 0)
    

for i in range(2, 11):
    maxdx = i
    dx = i
    dy = 0
    print("For a distance of {}:".format(i))
    distance_combos = []
    while (dx > 0):
        ddx = dx
        while (ddx > 0 and ddx >= dy):
            distance_combos.append((ddx,dy))
            ddx -= 2
        dx -= 1
        dy += 1
    distance_combos.sort(key=lambda combo:combo[0], reverse=True)
    for combo in distance_combos:
        num_paths = find_num_paths(i, combo[0], combo[1])
        print("({}, {}): {}".format(combo[0], combo[1], num_paths))