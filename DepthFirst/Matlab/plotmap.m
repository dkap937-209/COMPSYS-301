function plotmap(map, endRow, endCol)
%Plots the map. See map_convert

[X,Y]=meshgrid(1:20,1:20);
plot(X,Y,'k'); hold on
plot(Y,X,'k');
axis([0, 20, 0, 16]);
axis off
[maprows,mapcols]=size(map);

for i=1:maprows
    for j=1:mapcols
       if (map(i,j) == 1)
           placeblock([16-i,j]);
       end
       if(map(i,j) == -1)
           position=[j, 16-i];
           rectangle('Position',[position,1,1],'FaceColor','y');
       end  
    end
end

position = [endCol, 16-endRow];
rectangle('Position',[position,1,1],'FaceColor','g');

%plot row indices
for i = 1:maprows,
   c=sprintf('%d',i); 
   text(0.5,maprows-i+1+0.5,c,'FontSize',8); 
   text(mapcols+1+0.5,maprows-i+1+0.5,c,'FontSize',8); 
end
%plot col indices
for i = 1:mapcols,
   c=sprintf('%d',i); 
   text(0.5+i,maprows+1+0.5,c,'FontSize',8);
   text(0.5+i,0.5,c,'FontSize',8);
end

hold off

end

function placeblock(position)
position=[position(2) position(1)];
rectangle('Position',[position,1,1],'FaceColor','r');
end


