package net.codejava;

import lombok.NoArgsConstructor;

import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

@NoArgsConstructor
public class PathFinding {

    char[][] matrix;

    //TODO: modify it so where we went we mark -1 or something
    int pathExists(char[][] matrix, Pair startPos, Pair endPos) {

        this.matrix = matrix;
        Node source = new Node(startPos.x, startPos.y, 0);

        Queue<Node> queue = new LinkedList<Node>();

        queue.add(source);

        while(!queue.isEmpty()) {

            Node popped = queue.poll();

            //If we have reached the destination return the distance
            if(popped.x == endPos.x && popped.y == endPos.y ) {
//                printMatrix(matrix);
                return popped.distanceFromSource;
            }
            else {
                matrix[popped.x][popped.y]='1';

                List<Node> neighbourList = addNeighbours(popped);
                queue.addAll(neighbourList);
            }
        }
        return -1;
    }

//    private void printMatrix(char[][] matrix) {
//        int x = matrix.length;
//        int y = matrix[0].length;
//
//        for(int i=0; i<y; i++){
//            for(int j=0; j<x; j++){
//                System.out.print(matrix[j][i] + " ");
//            }
//            System.out.println("\n");
//        }
//    }

    private  List<Node> addNeighbours(Node popped) {

        List<Node> list = new LinkedList<>();

        if((popped.x-1 > 0 && popped.x-1 < matrix.length) && matrix[popped.x-1][popped.y] == '0') {
            list.add(new Node(popped.x-1, popped.y, popped.distanceFromSource+1));
        }
        if((popped.x+1 > 0 && popped.x+1 < matrix.length) && matrix[popped.x+1][popped.y] == '0') {
            list.add(new Node(popped.x+1, popped.y, popped.distanceFromSource+1));
        }
        if((popped.y-1 > 0 && popped.y-1 < matrix.length) && matrix[popped.x][popped.y-1] == '0') {
            list.add(new Node(popped.x, popped.y-1, popped.distanceFromSource+1));
        }
        if((popped.y+1 > 0 && popped.y+1 < matrix.length) && matrix[popped.x][popped.y+1] == '0') {
            list.add(new Node(popped.x, popped.y+1, popped.distanceFromSource+1));
        }

        if(list.size()>0){
//            System.out.println("over here");
            Node n = list.get(0);
            this.matrix[n.x][n.y] = '#';
        }
        return list;
    }
}
