import math
import sys
from resource import *
import time
import psutil


# Hardcoded mismatch values based on the table in the assignment description
MISMATCHES = {
    "A": {
        "A": 0,
        "C": 110,
        "G": 48,
        "T": 94
    },
    "C": {
        "A": 110,
        "C": 0,
        "G": 118,
        "T": 48
    },
    "G": {
        "A": 48,
        "C": 118,
        "G": 0,
        "T": 110
    },
    "T": {
        "A": 94,
        "C": 48,
        "G": 110,
        "T": 0
    }
}

# This is the standard gap penalty as specified by the assignment description
GAP_PENALTY = 30


def efficiently_calculate_values(s1, s2):
    """
    This method takes in the two strings to align and calculates OPT-Values for the last column.
    values of the 2d-array with OPT values.
    It returns that array to then be used to find the optimal alignment based on its values.
    """
    base_column = []
    new_column = []

    # Initialize first column
    for i in range(0, len(s2) + 1):
        base_column.append(i * GAP_PENALTY)

    # Loop through doing column by column
    for i in range(1, len(s1) + 1):

        # Loop through rows in this column, calculating the new column
        for j in range(0, len(s2) + 1):
            if j == 0:
                # First item in column just uses gap penalty
                new_column.append(i * GAP_PENALTY)
            else:
                # Calculate next item
                matched_both_cost = base_column[j-1] + MISMATCHES[s1[i-1]][s2[j-1]]

                s1_gap_cost = base_column[j] + GAP_PENALTY

                s2_gap_cost = new_column[j-1] + GAP_PENALTY

                new_column.append(min(matched_both_cost, s1_gap_cost, s2_gap_cost))

        # Update base and new column
        base_column = new_column
        new_column = []

    # Return values calculated in last column
    return base_column


def handle_base_case(s1, s2):
    """
    Handling base case at bottom of memory efficient solution's recursion.
    At this point, we've split s1 all the way down to 1 character and need to find it's best alignment with s2.
    This is by trying to match s1 with itself in s2 and doing gaps elsewhere, or just making everything a gap.
    We return the cost, and alignments associated with these two strings.
    """
    # At best, we just do a gap for everything
    current_min_cost = GAP_PENALTY * (len(s2) + 1)
    s1_index = None

    for i in range(0, len(s2)):
        if GAP_PENALTY * (len(s2) - 1) + MISMATCHES[s1][s2[i]] < current_min_cost:
            # Matching at this index is cheaper
            current_min_cost = GAP_PENALTY * (len(s2) - 1) + MISMATCHES[s1][s2[i]]
            s1_index = i

    if s1_index is not None:
        # s1 goes somewhere, build alignment 1
        alignment1 = ""
        for i in range(0, len(s2)):
            if i == s1_index:
                alignment1 += s1
            else:
                alignment1 += "_"
        return current_min_cost, alignment1, s2
    else:
        # Build alignments and return
        alignment1 = s1
        for i in range(0, len(s2)):
            alignment1 += "_"
        return current_min_cost, alignment1, "_" + s2


def efficiently_find_solution(s1, s2):
    """
    This divide and conquer method uses the efficient solution to sequence alignment.
    It will return the cost and overall alignments at the top level.
    """
    # TODO: Handle base case
    # Handle base cases
    if len(s1) == 1:
        return handle_base_case(s1, s2)
    elif len(s2) == 0:
        alignment2 = "_" * len(s1)
        return GAP_PENALTY * len(s1), s1, alignment2,

    # Split s1 in half
    split_point = int(len(s1) / 2)
    s1l = s1[0:split_point]
    s1r = s1[split_point:]

    # Array to store expected alignment cost of each split point in y
    split_value_costs = []

    # Find alignment cost for each split point in y
    left_alignment_costs = efficiently_calculate_values(s1l, s2)
    # Reverse s1r before calculating values as discussed in lecture
    right_alignment_costs = efficiently_calculate_values(s1r[::-1], s2[::-1])

    for i in range(0, len(s2) + 1):
        # Calculate left and right cost of each split point
        left_cost = left_alignment_costs[i]
        right_cost = right_alignment_costs[len(s2) - i]

        split_value_costs.append(left_cost + right_cost)

    # Choose the split point
    split_point = split_value_costs.index(min(split_value_costs))

    # Make official split of s2
    s2l = s2[0:split_point]
    s2r = s2[split_point:]

    # Calculate solution/alignment for each half after split (divide/conquer)
    recursive_left_cost, alignment1_left, alignment2_left = efficiently_find_solution(s1l, s2l)
    recursive_right_cost, alignment1_right, alignment2_right = efficiently_find_solution(s1r, s2r)

    # Combine step occurs here (concatenate)
    cost = recursive_left_cost + recursive_right_cost
    alignment1 = alignment1_left + alignment1_right
    alignment2 = alignment2_left + alignment2_right

    return cost, alignment1, alignment2


def generate_string(base, indices):
    """
    This method takes in a base string and the indices, as given by an input file.
    It returns a generated string to use in our sequence alignment problem.
    """
    curr_string = base

    for index in indices:
        curr_string = f"{curr_string[0:index+1]}{curr_string}{curr_string[index+1:]}"

    return curr_string


def read_input(filename):
    """
    This method reads in an input file and outputs the two strings to find a minimum cost alignment for.
    """
    base1 = None
    base1_numbers = []
    base2 = None
    base2_numbers = []

    with open(filename, 'r') as input_file:
        lines = input_file.readlines()
        for line in lines:
            # Skip empty lines
            if not line.strip():
                continue

            try:
                # Try and make line into an int
                value = int(line)
                if not base2:
                    # This is a number for base 1
                    base1_numbers.append(value)
                else:
                    # This is a number for base 2
                    base2_numbers.append(value)
            except Exception:
                # This is one of the bases
                if base1 is None:
                    base1 = line.strip()
                else:
                    base2 = line.strip()

    s1 = generate_string(base1, base1_numbers)
    s2 = generate_string(base2, base2_numbers)
    return s1, s2


def write_output(filename, cost, alignment1, alignment2, time_taken, memory):
    with open(filename, "w") as output_file:
        output_file.write(f"{cost}\n")
        output_file.write(f"{alignment1}\n")
        output_file.write(f"{alignment2}\n")
        output_file.write(f"{time_taken}\n")
        output_file.write(f"{memory}")


def process_memory():
    process = psutil.Process()
    memory_info = process.memory_info()
    memory_consumed = int(memory_info.rss/1024)
    return memory_consumed


def get_alignment_cost(alignment1, alignment2):
    """
    Utility method used in testing to verify that outputted alignments actually match my outputted cost.
    """
    cost = 0
    for i in range(0, len(alignment1)):
        if alignment1[i] != "_" and alignment2[i] != "_":
            cost += MISMATCHES[alignment1[i]][alignment2[i]]
        else:
            cost += GAP_PENALTY

    return cost


if __name__ == "__main__":
    start_time = time.time()

    # Get input and output files (first and second args)
    args = sys.argv
    input_file = args[1]

    output_file = None
    if len(args) >= 3:
        output_file = args[2]

    # Read input file and generate strings using information
    s1, s2 = read_input(input_file)

    cost, alignment1, alignment2 = efficiently_find_solution(s1, s2)

    memory = process_memory()

    end_time = time.time()
    time_taken = (end_time - start_time)*1000

    if output_file:
        write_output(output_file, cost, alignment1, alignment2, time_taken, memory)
