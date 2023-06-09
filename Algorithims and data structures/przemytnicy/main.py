import networkx as nx
import sys

graph = nx.DiGraph()

# reading data
file_name = sys.argv[1]
metal_price = []

with open(file_name, 'r') as f:
    num_of_metals = int(f.readline())
    for _ in range(num_of_metals):
        metal_price.append(int(f.readline()))

    graph.add_nodes_from([x for x in range(1, num_of_metals+1)])

    num_of_transforms = int(f.readline())
    for _ in range(num_of_transforms):
        from_metal, to_metal, cost = f.readline().split()
        graph.add_edge(from_metal, to_metal, weight=int(cost))

# Finding all cycles
cycles = list(nx.simple_cycles(graph))
# Filtering cycles that contain gold
cycles_with_gold = [x for x in cycles if '1' in x]
# Finding cost for each cycle
cycles_cost = []
for cycle in cycles_with_gold:
    cost = 0
    metal_duty = []
    for node_index in range(len(cycle)):
        try:
            cost += graph.get_edge_data(cycle[node_index], cycle[node_index+1])['weight']
        except IndexError:  # To finish the cycle (last element on the list to first edge)
            cost += graph.get_edge_data(cycle[node_index], cycle[0])['weight']
        # adding duty cost
        metal_duty.append(metal_price[int(cycle[node_index]) - 1]*0.5)
    cost += min(metal_duty)
    cycles_cost.append(cost)

print(f"Poprawnym wynikiem jest: {min(cycles_cost)}")
