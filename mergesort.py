from heapq import merge

def merge_sort2(m):
    """Sort list, using two part merge sort"""
    if len(m) <= 1:
        return m

    # Determine the pivot point
    middle = len(m) // 2

    # Split the list at the pivot
    right = m[middle:]
    left = m[:middle]

    # Recursively sort both halves
    left = merge_sort2(left)
    right = merge_sort2(right)

    # Merge the sorted halves