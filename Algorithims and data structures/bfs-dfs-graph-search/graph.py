class Graph:
    """ Undirected graph storing unique ints"""
    def __init__(self, max_vertice):
        self.graph = {x: set() for x in range(max_vertice)}

    def is_edge(self, v1: int, v2: int):
        try:
            if v2 in self.graph[v1]:
                return True
        except KeyError:
            return False
        else:
            return False

    def add_edge(self, v1: int, v2: int):
        try:
            self.graph[v1].add(v2)
            self.graph[v2].add(v1)
        except KeyError:
            return

    def del_edge(self, v1: int, v2: int):
        try:
            if not self.is_edge(v1, v2):
                return
            self.graph[v1].remove(v2)
            self.graph[v2].remove(v1)
        except KeyError:
            return

    def show(self):
        sorted_keys = list(self.graph.keys())
        sorted_keys.sort()
        for key in sorted_keys:
            print(f'{key} : {self.graph[key]}')

    def dfs_search(self, start: int, to_visit: set = None, result: list = None):
        if result is None:
            result = []
        if to_visit is None:
            to_visit = set(self.graph.keys())
        result.append(start)
        to_visit.discard(start)
        while not to_visit == {}:
            try:
                min_neighbour = min(self.graph[start].intersection(to_visit))
            except (ValueError, KeyError):
                return result
            self.dfs_search(min_neighbour, to_visit, result)
        return result

    def bfs_search(self, start: int):
        result = [start]
        to_visit = []
        while True:
            unvisited_neighbours = list(self.graph[start].difference(set(result)))
            unvisited_neighbours.sort()
            to_visit += unvisited_neighbours
            if not to_visit:
                break
            start = to_visit.pop(0)
            if start not in result:
                result.append(start)
        return result




