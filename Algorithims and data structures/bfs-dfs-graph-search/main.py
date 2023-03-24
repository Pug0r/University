from graph import Graph


with open('graf.txt', 'r') as file:
    num_of_lines = int(file.readline())
    graph = Graph(num_of_lines)
    for line in range(num_of_lines):
        v1, v2 = file.readline().split()
        graph.add_edge(int(v1), int(v2))

graph.show()
print(graph.bfs_search(2))
print(graph.dfs_search(2))

