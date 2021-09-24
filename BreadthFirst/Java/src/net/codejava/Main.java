
package net.codejava;

public class Main {

    public static void main(String[] args)
    {
        //x and y seem to be in the wrong directions, opposite
        char[][] matrix = {
                {'0', '0', '0', '0'},
                {'1', '1', '0', '0'},
                {'0', '1', '1', '0'},
                {'1', '0', '0', '0'}
        };

        Pair startPos = new Pair(0,0);
        Pair endPos = new Pair(3,2);

        PathFinding p = new PathFinding();
        int path = p.pathExists(matrix, startPos, endPos);

        System.out.println(path);
    }
}
