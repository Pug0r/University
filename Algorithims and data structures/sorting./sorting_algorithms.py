import random
from math import floor
import helper_functions
import matplotlib.pyplot as plt


def python_sort(array):
    return array.sort()


def merge_sort(array):

    def merge(array_a, array_b):
        merged_list = []
        while len(array_a) > 0 and len(array_b) > 0:
            if array_a[0] > array_b[0]:
                merged_list.append(array_b.pop(0))
            elif array_a[0] < array_b[0]:
                merged_list.append(array_a.pop(0))
            else:
                merged_list.append(array_b.pop(0))
                merged_list.append(array_a.pop(0))
        return merged_list + array_a + array_b

    number_of_elements = len(array)
    if number_of_elements == 1:
        return array
    left = []
    for _ in array[:number_of_elements//2]:
        left.append(array.pop(0))
    right = array
    left = merge_sort(left)
    right = merge_sort(right)
    return merge(left, right)


def quick_sort(array):
    if len(array) <= 1:
        return array
    pivot = array[-1]
    smaller = []
    greater = []
    equal = []
    for element in array:
        if element > pivot:
            greater.append(element)
        elif element == pivot:
            equal.append(element)
        else:
            smaller.append(element)
    return quick_sort(smaller) + equal + quick_sort(greater)


# todo: Tu by sie przydalo napisac klase bo jest syf, jak zdazysz to zmien!
def heap_sort(array):

    def build_max_heap(array):
        for parent_index in range((floor(len(array)//2)), -1, -1):
            promote_child(array, parent_index, len(array))
        return array

    def promote_child(array, parent_index, array_last_index):
        left_child_index = 2*parent_index+1
        right_child_index = 2*parent_index+2
        if right_child_index < array_last_index:
            if array[right_child_index] > array[left_child_index]:
                greater_child_index = right_child_index
            else:
                greater_child_index = left_child_index
        elif left_child_index < array_last_index:
            greater_child_index = left_child_index
        else:
            return array
        if array[greater_child_index] > array[parent_index]:
            array[parent_index], array[greater_child_index] = array[greater_child_index], array[parent_index]
            promote_child(array, greater_child_index, array_last_index)
        return array

    array = build_max_heap(array)
    for i in range(len(array)-1, 0, -1):
        array[i], array[0] = array[0], array[i]
        promote_child(array, 0, i)
    return array


def bubble_sort(array):
    sorted_starting_index = len(array) - 1
    while sorted_starting_index > 0:
        for index in range(0, sorted_starting_index):
            if array[index] > array[index+1]:
                array[index], array[index+1] = array[index+1], array[index]
        sorted_starting_index -= 1
    return array


def selection_sort(array):
    number_of_elements = len(array)
    for starting_index in range(number_of_elements):
        min_item_index = starting_index
        for current_iterating_index in range(starting_index+1, number_of_elements):
            if array[current_iterating_index] < array[min_item_index]:
                min_item_index = current_iterating_index
        array[starting_index], array[min_item_index] = array[min_item_index], array[starting_index]
    return array


def insertion_sort(array):
    for index in range(1, len(array)):
        to_be_inserted = array[index]
        already_sorted = index - 1
        while already_sorted >= 0 and array[already_sorted] > to_be_inserted:
            array[already_sorted+1] = array[already_sorted]
            already_sorted -= 1
        array[already_sorted+1] = to_be_inserted
    return array


def bogo_sort(array):
    """ BE CAREFUL WITH THAT!"""
    while not sorted(array) == array:
        random.shuffle(array)
    return array


if __name__ == '__main__':
    # ATTENTION, using at Your own risk
    # the author is not responsible for any damages to cpu
    # https://www.youtube.com/watch?v=DaPJkYo2quc
    # print('Bogo Sort: ', time_sorting_function(bogo_sort))

    print("Sorting functions times, array of 10**4 elements", end='\n\n')
    print("Python's sort: ", helper_functions.time_sorting_function(python_sort))
    print('Bubble Sort: ', helper_functions.time_sorting_function(bubble_sort))
    print('Selection Sort: ', helper_functions.time_sorting_function(selection_sort))
    print("Insertion Sort: ", helper_functions.time_sorting_function(insertion_sort))
    print("Quick Sort: ", helper_functions.time_sorting_function(quick_sort))
    print("Merge Sort: ", helper_functions.time_sorting_function(merge_sort))
    print("Heap Sort: ", helper_functions.time_sorting_function(heap_sort))

    # arrays_number = (5**1, 10**1, 5**2, 10**2, 5**3, 10**3, 5**4, 10**4)
    # functions = (python_sort, bubble_sort, selection_sort, insertion_sort, quick_sort, merge_sort, heap_sort)
    # data = {function.__name__: function for function in functions}
    # all_data = []
    # all_data.append([helper_functions.time_sorting_function(python_sort, elements_in_array=x) for x in arrays_number])
    # all_data.append([helper_functions.time_sorting_function(bubble_sort, elements_in_array=x) for x in arrays_number])
    # all_data.append([helper_functions.time_sorting_function(selection_sort, elements_in_array=x) for x in arrays_number])
    # all_data.append([helper_functions.time_sorting_function(insertion_sort, elements_in_array=x) for x in arrays_number])
    # all_data.append([helper_functions.time_sorting_function(quick_sort, elements_in_array=x) for x in arrays_number])
    # all_data.append([helper_functions.time_sorting_function(merge_sort, elements_in_array=x) for x in arrays_number])
    # all_data.append([helper_functions.time_sorting_function(heap_sort, elements_in_array=x) for x in arrays_number])
    #
    # fig, ax = plt.subplots()
    # ax.set_ylabel('Time in seconds')
    # ax.set_xlabel('Number of elements in array')
    # plt.xscale('log')
    # plt.legend(loc="upper right")
    # x = arrays_number
    # y_python = all_data[0]
    # y_bubble = all_data[1]
    # y_selection = all_data[2]
    # y_insertion = all_data[3]
    # y_quick = all_data[4]
    # y_merge = all_data[5]
    # y_heap = all_data[6]
    # plt.plot(x, y_python, label="Python's Sort (Tim sort)")
    # plt.plot(x, y_bubble, label="Bubble Sort")
    # plt.plot(x, y_selection, label="Selection Sort")
    # plt.plot(x, y_insertion, label="Insertion Sort")
    # plt.plot(x, y_quick, label="Quick Sort")
    # plt.plot(x, y_merge, label="Merge Sort")
    # plt.plot(x, y_heap, label="Heap Sort")
    # plt.legend(loc="upper right")
    # plt.show()










