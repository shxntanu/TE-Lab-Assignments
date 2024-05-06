class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.graph = []

    # Function to add an edge to the graph
    def add_edge(self, u, v, weight):
        self.graph.append([u, v, weight])

    # Find set of an element i
    def find(self, parent, i):
        if parent[i] == i:
            return i
        return self.find(parent, parent[i])

    # Union of two sets of x and y
    def union(self, parent, rank, x, y):
        xroot = self.find(parent, x)
        yroot = self.find(parent, y)

        if rank[xroot] < rank[yroot]:
            parent[xroot] = yroot
        elif rank[xroot] > rank[yroot]:
            parent[yroot] = xroot
        else:
            parent[yroot] = xroot
            rank[xroot] += 1

    # Function to construct MST using Kruskal's algorithm
    def kruskal_mst(self):
        result = []  # This will store the resultant MST
        i = 0  # Index variable, used for sorted edges
        e = 0  # Index variable, used for result[]

        # Step 1: Sort all the edges in non-decreasing order of their weight.
        self.graph = sorted(self.graph, key=lambda item: item[2])

        parent = []
        rank = []

        # Create V subsets with single elements
        for node in range(self.V):
            parent.append(node)
            rank.append(0)

        # Number of edges to be taken is equal to V-1
        while e < self.V - 1:
            # Step 2: Pick the smallest edge.
            u, v, weight = self.graph[i]
            i += 1
            x = self.find(parent, u)
            y = self.find(parent, v)

            # If including this edge does not cause cycle, include it in result and increment the index of result for next edge
            if x != y:
                e += 1
                result.append([u, v, weight])
                self.union(parent, rank, x, y)

        print("Edge \tWeight")
        for u, v, weight in result:
            print(u, "-", v, "\t", weight)


# Example usage:
g = Graph(4)
g.add_edge(0, 1, 10)
g.add_edge(0, 2, 6)
g.add_edge(0, 3, 5)
g.add_edge(1, 3, 15)
g.add_edge(2, 3, 4)

g.kruskal_mst()
