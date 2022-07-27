class Node{
    constructor(visited=false, distanceToStartNode=Infinity, distanceToNeighbour, neighbours, predecessors){
        this.visited = visited;
        this.distance = distanceToStartNode;
        this.distanceToNeighbour = distanceToNeighbour;
        this.neighbours = neighbours;
        this.predecessors = predecessors;
    }
}