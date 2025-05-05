from array import array  # Importing array module to create fixed-size hash tables

size = 10  # Define the size of the hash table

# Create two hash tables initialized with -1 (indicating empty slots)
hash_table_linear = array('i', [-1] * size)         # For linear probing
hash_table_quadratic = array('i', [-1] * size)      # For quadratic probing

# Hash function: simple modulo function
def hash_function(key):
    return key % size  # Returns index within range [0, size-1]

# Linear Probing collision resolution
def linear_probe(key, value, table):
    index = hash_function(key)  # Compute initial index
    comparisons = 1  # Start with 1 comparison
    while table[index] != -1:  # Loop until an empty slot is found
        index = (index + 1) % size  # Move to next index linearly
        comparisons += 1  # Count each probe as a comparison
    table[index] = value  # Insert the value once a free spot is found
    return comparisons  # Return number of comparisons made

# Quadratic Probing collision resolution
def quadratic_probe(key, value, table):
    index = hash_function(key)  # Compute initial index
    i = 1  # Step variable for quadratic calculation
    comparisons = 1  # Initial comparison
    while table[index] != -1:  # While the slot is not empty
        index = (hash_function(key) + i * i) % size  # Apply quadratic formula
        i += 1  # Increment i to change the step
        comparisons += 1  # Count comparisons
    table[index] = value  # Insert the value at computed position
    return comparisons  # Return number of comparisons

# Start of main program
print("---- Telephone Book: Hash Table Collision Handling ----")
n = int(input("Enter number of telephone numbers to insert (max 10): "))  # Input record count

# Validation: prevent exceeding table size
if n > size:
    print("Error: Number of inputs cannot exceed hash table size.")  # Error message
    exit()  # Exit program

data = []  # List to hold input values
for i in range(n):
    val = int(input(f"Enter telephone number {i+1}: "))  # Take input from user
    data.append(val)  # Store in list

# Insertion using Linear Probing
print("\n--- Insertion using Linear Probing ---")
linear_comparisons = 0  # Initialize total comparison counter
for num in data:
    c = linear_probe(num, num, hash_table_linear)  # Insert number
    linear_comparisons += c  # Add comparisons for current insertion
    print(f"{num} inserted with {c} comparisons.")  # Show details

# Insertion using Quadratic Probing
print("\n--- Insertion using Quadratic Probing ---")
quadratic_comparisons = 0  # Initialize comparison counter
for num in data:
    c = quadratic_probe(num, num, hash_table_quadratic)  # Insert number
    quadratic_comparisons += c  # Add to total
    print(f"{num} inserted with {c} comparisons.")  # Show details

# Show final hash tables
print("\nFinal Hash Table (Linear Probing):     ", list(hash_table_linear))  # Display linear table
print("Final Hash Table (Quadratic Probing): ", list(hash_table_quadratic))  # Display quadratic table

# Show total comparisons
print("\n--- Comparison Summary ---")
print(f"Total Comparisons (Linear Probing):     {linear_comparisons}")  # Total for linear
print(f"Total Comparisons (Quadratic Probing):  {quadratic_comparisons}")  # Total for quadratic


#how to run:
#copy the file address and open terminal, type cd ctrl+v press enter.
#in directory, type python file_name.py and enter

#concepts used:

# Hash Table: Array-based structure used to store key-value pairs.
# Used to simulate a telephone directory.

# Hash Function: Converts a key to a valid index in the table (key % size).
# Ensures even distribution and valid indexing.

# Collision: Occurs when two keys hash to the same index.
# Must be handled to avoid data loss or overwriting.

# Linear Probing: Resolves collision by checking the next index linearly (index + 1, +2...).
# Easy to implement but can cause clustering.

# Quadratic Probing: Resolves collision by checking indices with quadratic steps (index + i^2).
# Reduces clustering and spreads entries more evenly.

# Probing: Each attempt to find an empty slot is called a probe.
# Used to count and compare efficiency between strategies.

# Comparisons: The number of probes made during insertion.
# Lower comparisons indicate better collision handling performance.
