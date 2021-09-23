function finished = depthFirstFunction(maze, startingRow, startingCol, endRow, endCol, intersectionRow, intersectionCol)

    if nargin == 5
        intersectionRow = 0;
        intersectionCol = 0;
    end
    
    finished = false;
    mazeSize = size(maze);
    MAX_HEIGHT = mazeSize(1);
    MAX_WIDTH = mazeSize(2);
    INF = 999999;
    
    %Used to help find which direction is closest to destination
    %Order: North, East, South, West
    heuristicVals = [INF INF INF INF];
       
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
    if northPos > 0 
        if maze(northPos, startingCol)==0
            north = true;
%             heuristicVals(1) = abs(startingCol - endCol) + abs(northPos - endRow);
            heuristicVals(1) = sqrt((startingCol - endCol)^2 + abs(northPos - endRow)^2);
            directionsToMoveIn = directionsToMoveIn +1;
        end 
    end

    %East
    if eastPos <= MAX_WIDTH 
        if maze(startingRow, eastPos)==0
            east = true;
%             heuristicVals(2) = abs(eastPos- endCol) + abs(startingRow - endRow);
            heuristicVals(2) = sqrt(abs(eastPos- endCol)^2 + abs(startingRow - endRow)^2);
            directionsToMoveIn = directionsToMoveIn +1;
        end 
    end

    %South
    if southPos <= MAX_HEIGHT 
        if maze(southPos, startingCol)==0
            south = true;
%             heuristicVals(3) = abs(startingCol - endCol) + abs(southPos - endRow);
            heuristicVals(3) = sqrt(abs(startingCol - endCol)^2 + abs(southPos - endRow)^2);  
            directionsToMoveIn = directionsToMoveIn +1;
        end 
    end

    %West 
    if westPos > 0 
        if maze(startingRow, westPos)==0
           west = true;
%            heuristicVals(4) = abs(westPos - endCol) + abs(startingRow - endRow);
           heuristicVals(4) = sqrt(abs(westPos - endCol)^2 + abs(startingRow - endRow)^2);
           directionsToMoveIn = directionsToMoveIn +1;
        end 
    end
    
    if finished == true
        return
    elseif(startingRow == endRow && startingCol == endCol)
        maze(startingRow, startingCol) = -1;
        disp("Finished")
%         disp(maze)
        plotmap(maze, endRow, endCol)
        finished = true;
        
     elseif(directionsToMoveIn == 1)    
         
        if(north == true && finished == false)
            disp("move north")
            maze(startingRow, startingCol) = -1;
%             disp(maze)
            finished = depthFirstFunction(maze, northPos, startingCol, endRow, endCol);
        end
        if(east == true && finished == false)
            disp("move east")
            maze(startingRow, startingCol) = -1;
%             disp(maze)
            finished = depthFirstFunction(maze, startingRow, eastPos, endRow, endCol);
        end
        if(south == true && finished == false)
            disp("move south")
            maze(startingRow, startingCol) = -1;
%             disp(maze)
            finished = depthFirstFunction(maze, southPos, startingCol, endRow, endCol);
        end
        if(west == true && finished == false)
            disp("move east")
            maze(startingRow, startingCol) = -1;
%             disp(maze)
            finished = depthFirstFunction(maze, startingRow, westPos, endRow, endCol);
        end
        
    %If we can move in multiple directions    
    elseif directionsToMoveIn >1
         maze(startingRow,startingCol) = -1;
         plotmap(maze, endRow, endCol)
         smallestH = min(heuristicVals);  
         disp("Heuristic vals: "+ heuristicVals)
         disp("Smallest heuristic value: "+ smallestH)
         if north == true && finished == false && smallestH == heuristicVals(1)
             finished = depthFirstFunction(maze, northPos, startingCol, endRow, endCol, intersectionRow, intersectionCol);
         end
         
         if east == true && finished == false && smallestH == heuristicVals(2)
             finished = depthFirstFunction(maze, startingRow, eastPos, endRow, endCol, intersectionRow, intersectionCol);
         end
         
         if south == true && finished == false && smallestH == heuristicVals(3)
             finished = depthFirstFunction(maze, southPos, startingCol, endRow, endCol, intersectionRow, intersectionCol);
         end
         
         if west == true && finished == false && smallestH == heuristicVals(4)
             finished = depthFirstFunction(maze, startingRow, westPos, endRow, endCol, intersectionRow, intersectionCol);
         end
        
    else
        maze(startingRow, startingCol) = -1;
        disp("Can't move")
%         disp(maze)
        
        if intersectionRow ~= 0 && intersectionCol ~= 0
            depthFirstFunction(maze, intersectionRow, intersectionCol, endRow, endCol);
        end

    end 
     
end

