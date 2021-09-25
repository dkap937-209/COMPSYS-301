package net.codejava;

import lombok.NoArgsConstructor;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

@NoArgsConstructor
public class PathFinding {

    char[][] matrix;

    int pathExists(char[][] matrix, Pair startPos, Pair endPos) {

        this.matrix = matrix;
        Node source = new Node(startPos.x, startPos.y, 0, null);

        Queue<Node> queue = new LinkedList<Node>();
        ArrayList<Node> path = new ArrayList<>();

        queue.add(source);

        while(!queue.isEmpty()) {
            Node popped = queue.poll();

            //If we have reached the destination return the distance
            if(popped.x == endPos.x && popped.y == endPos.y) {
                System.out.println("Found final spot");

                while(!(popped == source)){
                    path.add(popped);
                    popped = popped.parentNode;
                }

                printMatrix(matrix, path);
                return popped.distanceFromSource;
            }
            else {
                List<Node> neighbourList = addNeighbours(popped);
                queue.addAll(neighbourList);
            }
        }
        return -1;
    }

    private void printMatrix(char[][] matrix, ArrayList<Node> path) {
        int y = matrix[0].length;
        for(Node n: path){
            this.matrix[n.x][n.y] = ' ';
        }

        for (char[] chars : matrix) {
            for (int j = 0; j < y; j++) {
                System.out.print(chars[j] + " ");
            }
            System.out.println("\r");
        }
    }

    private  List<Node> addNeighbours(Node popped) {

        List<Node> list = new LinkedList<>();

        if((popped.x-1 > 0 && popped.x-1 < matrix.length) && matrix[popped.x-1][popped.y] == '0') {
            list.add(new Node(popped.x-1, popped.y, popped.distanceFromSource+1, popped));
        }
        if((popped.x+1 > 0 && popped.x+1 < matrix.length) && matrix[popped.x+1][popped.y] == '0') {
            list.add(new Node(popped.x+1, popped.y, popped.distanceFromSource+1, popped));
        }
        if((popped.y-1 > 0 && popped.y-1 < matrix[0].length) && matrix[popped.x][popped.y-1] == '0') {
            list.add(new Node(popped.x, popped.y-1, popped.distanceFromSource+1, popped));
        }
        if((popped.y+1 > 0 && popped.y+1 < matrix[0].length) && matrix[popped.x][popped.y+1] == '0') {
            list.add(new Node(popped.x, popped.y+1, popped.distanceFromSource+1, popped));
        }

        return list;
    }
}
