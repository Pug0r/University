import networkx as nx
import sys

# Getting data from file
file_name = sys.argv[1]
data = []
with open(file_name, 'r') as f:
    for line in f:
        data.append(int(line))

# Inserting data into directed graph
data.pop(0)  # first line is just info about number of lines
DG = nx.DiGraph()
for index, item in enumerate(data):
    DG.add_edge(item, index+1)

# Adding to the result only those vertices with no incoming edge
result = set()
for vertice, in_degree in DG.in_degree:
    if in_degree == 0:
        result.add(vertice)


def is_isolated_cycle(cycle: list, no_in_vertices: set) -> bool:
    """ Checks if a cycle is reachable from node with no incoming edge"""
    for vertice in no_in_vertices:
        for element in cycle:
            if element in nx.descendants(DG, vertice):
                return False
    return True


for cycle in list(nx.simple_cycles(DG)):
    if is_isolated_cycle(cycle, result):
        result.add(cycle[0])

print(f'Minimalnie trzeba stluc {len(result)} skarbonek/ki, np: {result}')





