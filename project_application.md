# Lab 11 - Project Application

## E1 - Original collection and borrowed pointers
The `orders` array holds the original four `OrderPreview` records in memory. The `view` array is a separate array of pointers (`OrderPreview *`) that borrows the memory addresses of specific orders from `orders`. The actual data remains strictly inside the `orders` array, meaning `view` does not own or duplicate any objects.

## E2 - Implemented view and test
- **Dummy cases tested:**
  1. ID 101: `DELIVERY`, `PENDING` (Active delivery -> Added to view)
  2. ID 102: `DELIVERY`, `COMPLETED` (Completed delivery -> Ignored)
  3. ID 103: `DINE_IN`, `PENDING` (Dine-in order -> Ignored)
  4. ID 104: `DELIVERY`, `IN_PROGRESS` (Active delivery -> Added to view)
- **Expected vs. Observed:** The view correctly selected only IDs 101 and 104.
- **Preservation verification:** Printing the `orders` array before and after constructing the view confirmed that the original order elements, their statuses, and their array positions remained completely unchanged, preserving the required FIFO operational sequence.

## E3 - Sorting criterion and next integration step
- **Comparison rules for the report:**
  1. **Building:** Ascending alphabetical order (e.g., "Bldg-A" comes before "Bldg-B").
  2. **Priority:** Descending numeric order within the same building (e.g., Priority 3 comes before Priority 1).
  3. **Order ID:** Ascending numeric order in case of an exact tie in both building and priority.
- **Example:** If comparing two orders for "Bldg-A", one with Priority 2 (ID 101) and one with Priority 1 (ID 104), ID 101 will come first.
- **Next integration step:** Adapt the recursive merge sort algorithm (`mergeSortView` and its comparator) using these three comparison rules to sort the pointer array when generating reports in the main cafeteria project.

## E4 - Lab evidence
- Source file: `delivery_view_practice.cpp`
- Test output: `delivery_view_output.txt`
- **Explanation:** This practice demonstrates how to build temporary, filtered pointer views to display custom reports without modifying the underlying operational data structure (such as a FIFO queue or main list).