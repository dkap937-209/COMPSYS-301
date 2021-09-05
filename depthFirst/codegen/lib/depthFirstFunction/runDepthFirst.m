maze = [1 1 0 1; 1 0 0 0; 1 1 0 1];

startingRow = 1;
startingCol = 3;
endRow = 2;
endCol = 2;

disp("Original maze to navigate")
disp(maze)

depthFirstFunction(maze,startingRow, startingCol, endRow, endCol);