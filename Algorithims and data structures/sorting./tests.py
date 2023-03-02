import random
import unittest
import sorting_algorithms
import helper_functions


class MyTestCase(unittest.TestCase):
    def test_merge(self):
        random.seed()
        array1 = helper_functions.generate_random_ints_array(10**3)
        array2 = array1.copy()
        self.assertListEqual(sorting_algorithms.merge_sort(array1), sorted(array2))

    def test_bubble(self):
        random.seed()
        array1 = helper_functions.generate_random_ints_array(10**3)
        array2 = array1.copy()
        self.assertListEqual(sorting_algorithms.bubble_sort(array1), sorted(array2))

    def test_insertion(self):
        random.seed()
        array1 = helper_functions.generate_random_ints_array(10**3)
        array2 = array1.copy()
        self.assertListEqual(sorting_algorithms.insertion_sort(array1), sorted(array2))

    def test_selection(self):
        random.seed()
        array1 = helper_functions.generate_random_ints_array(10**3)
        array2 = array1.copy()
        self.assertListEqual(sorting_algorithms.selection_sort(array1), sorted(array2))

    def test_quick(self):
        random.seed()
        array1 = helper_functions.generate_random_ints_array(10**3)
        array2 = array1.copy()
        self.assertListEqual(sorting_algorithms.quick_sort(array1), sorted(array2))

    def test_heap(self):
        random.seed()
        array1 = helper_functions.generate_random_ints_array(10**3)
        array2 = array1.copy()
        self.assertListEqual(sorting_algorithms.heap_sort(array1), sorted(array2))


if __name__ == '__main__':
    unittest.main()
