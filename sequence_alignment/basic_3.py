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


def calculate_values(s1, s2):
    """
    This method takes in the two string to align and calculates values of the 2d-array with OPT values.
    It returns that array to then be used to find the optimal alignment based on its values.
    """
    opt_values = []

    # Adding rows for each character in s2 (s2 is on y-axis)
    for i in range(0, len(s2) + 1):
        opt_values.append([])

    # Initialize the bottom row's values
    for i in range(0, len(s1) + 1):
        opt_values[0].append(i * GAP_PENALTY)

    # Initialize left column's values
    for i in range(1, len(s2) + 1):
        opt_values[i].append(i * GAP_PENALTY)

    # Work through each column
    for i in range(1, len(s1) + 1):
        for j in range(1, len(s2) + 1):
            # Calculate value if we match these characters
            val_with_match = MISMATCHES[s1[i-1]][s2[j-1]] + opt_values[j-1][i-1]

            # Calculate value if i gets a gap
            val_with_i_gap = GAP_PENALTY + opt_values[j][i-1]

            # Calculate value if j gets a gap
            val_with_j_gap = GAP_PENALTY + opt_values[j-1][i]

            # Set value to min of those options
            opt_values[j].append(min(val_with_match, val_with_j_gap, val_with_i_gap))

    return opt_values


def find_solution(opt_values, s1, s2):
    alignment1 = ""
    alignment2 = ""

    i = len(s1)
    j = len(s2)

    # Minimum cost alignment is at top right corner
    cost = opt_values[j][i]

    # Find solution by moving through the opt values array and building it up
    while i > 0 or j > 0:
        # Find value of matching the letters if possible
        if i > 0 and j > 0:
            both_matched_val = opt_values[j-1][i-1] + MISMATCHES[s1[i-1]][s2[j-1]]
            if opt_values[j][i] == both_matched_val:
                # Add both letters to alignment
                alignment1 = s1[i-1] + alignment1
                alignment2 = s2[j-1] + alignment2

                # Decrement both i and j
                i -= 1
                j -= 1
                continue

        if i > 0:
            i_not_matched_val = opt_values[j][i-1] + GAP_PENALTY
            if opt_values[j][i] == i_not_matched_val:
                # Add i to alignment 1, gap to 2
                alignment1 = s1[i-1] + alignment1
                alignment2 = "_" + alignment2

                # Decrement i
                i -= 1
                continue

        if j > 0:
            j_not_matched_val = opt_values[j-1][i] + GAP_PENALTY

            if opt_values[j][i] == j_not_matched_val:
                # Add j to alignment 2, gap to 1
                alignment1 = "_" + alignment1
                alignment2 = s2[j-1] + alignment2

                # Decrement i
                j -= 1

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

    opt_values = calculate_values(s1, s2)

    cost, alignment1, alignment2 = find_solution(opt_values, s1, s2)

    memory = process_memory()

    end_time = time.time()
    time_taken = (end_time - start_time)*1000

    if output_file:
        write_output(output_file, cost, alignment1, alignment2, time_taken, memory)
