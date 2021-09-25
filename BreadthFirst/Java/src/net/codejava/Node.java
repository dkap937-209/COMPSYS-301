package net.codejava;

import lombok.AllArgsConstructor;
import lombok.ToString;

@AllArgsConstructor
@ToString
class Node {
    int x;
    int y;
    int distanceFromSource;
    Node parentNode;

    public Node(int x, int y, int distanceFromSource, Node parentNode) {
        this.x = x;
        this.y = y;
        this.distanceFromSource = distanceFromSource;
        this.parentNode = parentNode;
    }

}
