from random import choice

map_ = []

apple_percentage = 12
empty_percentage = 80
rock_percentage = 5
bomb_percentage = 3

possible_cells = ['A']*apple_percentage + \
                 ['.']*empty_percentage + \
                 ['#']*rock_percentage + \
                 ['B']*bomb_percentage

for i in range(100):
    row = []
    for j in range(100):
        row.append(choice(possible_cells))
    map_.append(row)

with open('map_test.txt', 'w') as map_file:
    for row in map_:
        map_file.write(''.join(row) + '\n')

        
