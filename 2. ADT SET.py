class SetADT:
    def __init__(self):
        self.set_data = set()  # Initializes an empty set using Python's built-in set to ensure uniqueness of elements

    # Add a new element to the set
    def add(self, element):
        self.set_data.add(element)  # Adds an element to the set; duplicates are automatically avoided

    # Remove an element from the set
    def remove(self, element):
        self.set_data.discard(element)  # Removes the element if present; discard does not raise error if not found

    # Check if an element is present in the set
    def contains(self, element):
        return element in self.set_data  # Returns True if the element exists in the set, otherwise False

    # Return the number of values in the set
    def size(self):
        return len(self.set_data)  # Returns the number of unique elements currently in the set

    # Return an iterator used to loop over the collection
    def iterator(self):
        return iter(self.set_data)  # Returns an iterator to loop over the set elements

    # Return the intersection of two sets
    def intersection(self, other_set):
        return self.set_data.intersection(other_set.set_data)  # Returns elements common to both sets using built-in function

    # Return the union of two sets
    def union(self, other_set):
        return self.set_data.union(other_set.set_data)  # Returns all unique elements from both sets combined

    # Return the difference between two sets
    def difference(self, other_set):
        return self.set_data.difference(other_set.set_data)  # Returns elements present in this set but not in the other

    # Check if this set is a subset of another set
    def is_subset(self, other_set):
        return self.set_data.issubset(other_set.set_data)  # Returns True if this set is a subset of the other

# --- Main Functionality ---
def main():
    print("\nSet ADT Operations")
    set1 = SetADT()
    set2 = SetADT()

    while True:
        print("\nMenu:")
        print("1. Add to Set 1")
        print("2. Add to Set 2")
        print("3. Remove from Set 1")
        print("4. Check if element in Set 1")
        print("5. Size of Set 1")
        print("6. Iterate over Set 1")
        print("7. Union")
        print("8. Intersection")
        print("9. Difference (Set1 - Set2)")
        print("10. Subset Check (Set1 ⊆ Set2)")
        print("11. Exit")

        choice = input("Enter your choice: ")

        if choice == '1':
            ele = input("Enter element to add to Set 1: ")
            set1.add(ele)
        elif choice == '2':
            ele = input("Enter element to add to Set 2: ")
            set2.add(ele)
        elif choice == '3':
            ele = input("Enter element to remove from Set 1: ")
            set1.remove(ele)
        elif choice == '4':
            ele = input("Enter element to search in Set 1: ")
            print("Found" if set1.contains(ele) else "Not Found")
        elif choice == '5':
            print("Size of Set 1:", set1.size())
        elif choice == '6':
            print("Elements in Set 1:")
            for item in set1.iterator():
                print(item)
        elif choice == '7':
            print("Union:", set1.union(set2))
        elif choice == '8':
            print("Intersection:", set1.intersection(set2))
        elif choice == '9':
            print("Difference (Set1 - Set2):", set1.difference(set2))
        elif choice == '10':
            print("Set1 is subset of Set2:" if set1.is_subset(set2) else "Set1 is NOT a subset of Set2")
        elif choice == '11':
            print("Exiting.")
            break
        else:
            print("Invalid choice. Try again.")

if __name__ == '__main__':
    main()

#how to run:
#copy the file address and open terminal, type cd ctrl+v press enter.
#in directory, type python file_name.py and enter

# --- Explanation of Concepts Used ---
# 1. SetADT class models the abstract behavior of a mathematical set using Python's built-in set type.
# 2. Each operation (add, remove, contains, size, etc.) is defined to match typical ADT function behavior.
# 3. The use of Python's set guarantees all values are unique, matching set theory requirements.
# 4. The methods for intersection, union, difference, and subset are implemented directly with efficient built-in operations.
# 5. This modular design makes the code reusable and clear for testing multiple set operations with minimal changes.
# 6. The main() function provides a menu-driven interface, allowing dynamic interaction with SetADT for practical learning.
