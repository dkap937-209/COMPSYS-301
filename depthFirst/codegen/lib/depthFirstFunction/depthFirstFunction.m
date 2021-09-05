function [] = depthFirstFunction(maze, startingRow, startingCol, endRow, endCol, intersectionRow, intersectionCol)


    if nargin == 5
        intersectionRow = 0;
        intersectionCol = 0;
    end
    
    mazeSize = size(maze);
    MAX_HEIGHT = mazeSize(1);
    MAX_WIDTH = mazeSize(2);
    
    %Check in each direction we can go
    northPos = startingRow - 1;
    eastPos = startingCol + 1;
    southPos = startingRow + 1;
    westPos = startingCol - 1;

    north = false;
    east = false;
    west = false;
    south = false;
    directionsToMoveIn = 0;

    %North
    if northPos < 0 
        if maze(northPos, startingCol)==0
            north = true;
            directionsToMoveIn = directionsToMoveIn +1;
        end 
    end

    %East
    if eastPos <= MAX_WIDTH 
        if maze(startingRow, eastPos)==0
            east = true;
            directionsToMoveIn = directionsToMoveIn +1;
        end 
    end

    %South
    if southPos <= MAX_HEIGHT 
        if maze(southPos, startingCol)==0
            south = true;
            directionsToMoveIn = directionsToMoveIn +1;
        end 
    end

    %West 
    if westPos > 0 
        if maze(startingRow, westPos)==0
           west = true;
           directionsToMoveIn = directionsToMoveIn +1;
        end 
    end
    
    %If we can only move in one direction
     if(startingRow == endRow && startingCol == endCol)
        maze(startingRow, startingCol) = -1;
        disp("Finished")
        disp(maze)
        
     elseif(directionsToMoveIn == 1)
        if(north == true)
            disp("move north")
            maze(startingRow, startingCol) = -1;
            disp(maze)
            depthFirstFunction(maze, northPos, startingCol, endRow, endCol);
        end
        if(east == true)
            disp("move east")
            maze(startingRow, startingCol) = -1;
            disp(maze)
            depthFirstFunction(maze, startingRow, eastPos, endRow, endCol);
        end
        if(south == true)
            disp("move south")
            maze(startingRow, startingCol) = -1;
            disp(maze)
            depthFirstFunction(maze, southPos, startingCol, endRow, endCol);
        end
        if(west == true)
            disp("move east")
            maze(startingRow, startingCol) = -1;
            disp(maze)
            depthFirstFunction(maze, startingRow, westPos, endRow, endCol);
        end
        
    %If we can move in multiple directions    
    elseif directionsToMoveIn >1
         maze(startingRow,startingCol) = -1;
         if north == true
             depthFirstFunction(maze, northPos, startingCol, endRow, endCol, intersectionRow, intersectionCol);
         end
         
         if east == true
             depthFirstFunction(maze, startingRow, eastPos, endRow, endCol, intersectionRow, intersectionCol);
         end
         
         if south == true
             depthFirstFunction(maze, southPos, startingCol, endRow, endCol, intersectionRow, intersectionCol);
         end
         
         if west == true
             depthFirstFunction(maze, startingRow, westPos, endRow, endCol, intersectionRow, intersectionCol);
         end
        
    else
        maze(startingRow, startingCol) = -1;
        disp("Can't move")
        disp(maze)
        
        if intersectionRow ~= 0 && intersectionCol ~= 0
            depthFirstFunction(maze, intersectionRow, intersectionCol, endRow, endCol);
        end

    end 



end

