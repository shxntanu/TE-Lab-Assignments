class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.graph = [[0 for _ in range(vertices)] for _ in range(vertices)]

    # Function to add an edge to the graph
    def add_edge(self, u, v, weight):
        self.graph[u][v] = weight
        self.graph[v][u] = weight

    # Function to find the vertex with the minimum key value
    def min_key(self, key, mst_set):
        min_val = float('inf')
        min_index = None

        for v in range(self.V):
            if key[v] < min_val and not mst_set[v]:
                min_val = key[v]
                min_index = v

        return min_index

    # Function to construct and print MST
    def prim_mst(self):
        # Key values used to pick minimum weight edge in cut
        key = [float('inf')] * self.V
        parent = [None] * self.V  # Array to store constructed MST
        key[0] = 0  # Make key 0 so that this vertex is picked as first vertex
        mst_set = [False] * self.V

        parent[0] = -1  # First node is always the root of MST

        for _ in range(self.V):
            u = self.min_key(key, mst_set)  # Pick the minimum key vertex from the set of vertices not yet included in MST

            mst_set[u] = True  # Add the picked vertex to the MST set

            # Update key value and parent index of the adjacent vertices of the picked vertex
            for v in range(self.V):
                if self.graph[u][v] > 0 and not mst_set[v] and key[v] > self.graph[u][v]:
                    key[v] = self.graph[u][v]
                    parent[v] = u

        print("Edge \tWeight")
        for i in range(1, self.V):
            print(parent[i], "-", i, "\t", self.graph[i][parent[i]])


# Example usage:
g = Graph(5)
g.add_edge(0, 1, 2)
g.add_edge(0, 3, 6)
g.add_edge(1, 2, 3)
g.add_edge(1, 3, 8)
g.add_edge(1, 4, 5)
g.add_edge(2, 4, 7)
g.add_edge(3, 4, 9)

g.prim_mst()
