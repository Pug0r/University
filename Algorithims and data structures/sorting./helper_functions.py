import random
import time


def generate_random_ints_array(number_of_elements):
    random.seed()
    return [random.randint(0, 100) for _ in range(number_of_elements)]


def time_sorting_function(function, array=None, elements_in_array=10**4, repetitions=10**0):
    if array is None:
        array = generate_random_ints_array(elements_in_array)
    start = time.time()
    for _ in range(repetitions):
        function(array)
    end = time.time()
    return end-start


def does_my_function_work_please_do(function, array=None, elements_in_array=10**4):
    if array is None:
        array = generate_random_ints_array(elements_in_array)
    print('Unsorted array: ', array)
    print('Python sorted: ', sorted(array))
    print('Your function sorted: ', function(array))



