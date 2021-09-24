package net.codejava;

import lombok.AllArgsConstructor;
import lombok.ToString;

@AllArgsConstructor
@ToString
class Node {
    int x;
    int y;
    int distanceFromSource;
}