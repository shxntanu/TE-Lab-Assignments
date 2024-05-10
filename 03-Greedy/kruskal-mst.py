class Graph:
    def __init__(self):
        self.adj_list: dict[str, list[(str, int)]] = {}
        self.edges = []

    def add_edge(self, node_1: str, node_2: str, weight: int):
        if node_1 not in self.adj_list:
            self.adj_list[node_1] = []
        self.adj_list[node_1].append((node_2, weight))
        if node_2 not in self.adj_list:
            self.adj_list[node_2] = []
        self.adj_list[node_2].append((node_1, weight))
        self.edges.append((node_1, node_2, weight))

    def check_cycle(self, src: str, dst: str) -> bool:
        if src not in self.adj_list or dst not in self.adj_list:
            return False
        queue = [src]
        visited = [src]
        while len(queue) != 0:
            front = queue.pop(0)
            if front == dst:
                return True
            neighbors = self.adj_list[front]
            for neighbor in neighbors:
                if neighbor[0] not in visited:
                    visited.append(neighbor[0])
                    queue.append(neighbor[0])
        return False

    def __str__(self) -> str:
        str_repr = ""
        for key, val in self.adj_list.items():
            str_repr += f"{key} {self.adj_list[key]}\n"
        return str_repr


def min_spanning_tree(graph: Graph):
    ordered_edges = list(sorted(graph.edges, key=lambda edge: edge[2]))
    spanning_tree: Graph = Graph()
    min_cost: int = 0
    for edge in ordered_edges:
        if spanning_tree.check_cycle(edge[0], edge[1]):
            continue
        spanning_tree.add_edge(*edge)
        min_cost += edge[2]
    print(f"Min cost of spanning tree {min_cost}")


graph = Graph()

while True:
    print("Add edge to the graph: ")
    node_a = input("Enter first node: ")
    node_b = input("Enter second node: ")
    if node_a == node_b == "-":
        break
    weight = int(input("Enter weight of the edge: "))
    graph.add_edge(node_a, node_b, weight)

print("Graph adjacency list: ")
print(graph)

min_spanning_tree(graph)
