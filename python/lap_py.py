import time
import numpy as np

ROWS = 500
COLUMNS = 500
ITERATIONS = 10000


def perform_iterations(counter, grid1, grid2):
    counter /= 2
    while (counter) > 0:
        grid2[1:ROWS-1, 1:COLUMNS-1] = 0.25*np.add(np.add(grid1[2:ROWS, 1:COLUMNS-1], grid1[0:ROWS-2, 1:COLUMNS-1]),
                                                   np.add(grid1[1:ROWS-1, 2:COLUMNS], grid1[1:ROWS-1, 0:COLUMNS-2]))
        grid1[1:ROWS-1, 1:COLUMNS-1] = 0.25*np.add(np.add(grid2[2:ROWS, 1:COLUMNS-1], grid2[0:ROWS-2, 1:COLUMNS-1]),
                                                   np.add(grid2[1:ROWS-1, 2:COLUMNS], grid2[1:ROWS-1, 0:COLUMNS-2]))
        counter -= 1


def boundary_conditions(grid):
    for i in range(COLUMNS):
        grid[0][i] = i/(COLUMNS-1)*i/(COLUMNS-1)
        grid[ROWS-1][i] = i/(COLUMNS-1)*i/(COLUMNS-1)-1

    for j in range(ROWS):
        grid[j][0] = -j/(ROWS-1)*j/(ROWS-1)
        grid[j][ROWS-1] = 1-j/(ROWS-1)*j/(ROWS-1)


grid1 = np.zeros((ROWS, COLUMNS))
grid2 = np.zeros((ROWS, COLUMNS))

boundary_conditions(grid1)
boundary_conditions(grid2)

start_time = time.perf_counter()
perform_iterations(ITERATIONS, grid1, grid2)
stop_time = time.perf_counter()

sum1 = 0
sum2 = 0

for j in range(1, ROWS-1):
    for i in range(1, COLUMNS-1):
        sum2 = sum2+(grid2[j][i] * grid2[j][i])
        sum1 = sum1+(grid1[j][i] * grid1[j][i])

print(sum1, sum2, sum1 - sum2)
print(stop_time - start_time)
