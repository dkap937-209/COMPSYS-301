% maze = [1 1 0 1; 1 0 0 0; 1 1 0 1;1 0 0 1];
tic 
maze = map_convert('map.txt');

startingRow = 8;
startingCol = 10;
endRow = 6;
endCol = 3;

% disp("Original maze to navigate")
% disp(maze)

% plotmap(maze, endRow, endCol)

if((maze(startingRow, startingCol) ~= 0)|| maze(endRow, endCol) ~= 0)
    disp("Starting or end position is invalid")
else
    depthFirstFunction(maze,startingRow, startingCol, endRow, endCol);
end

toc 

