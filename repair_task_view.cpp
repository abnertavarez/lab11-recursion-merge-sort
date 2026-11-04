/*
 * Course: COEN 2220 - Programming 2
 * Name: [Your Name]
 * Lab: Lab 11 - Recursion and Merge Sort
 * Description: Practice - sort a temporary view without changing original tasks
 * Due date: [Date]
 */

#include <iostream>
#include <string>
using namespace std;

struct RepairTask
{
    string taskId;      // Preserve the identity of the original task.
    int daysUntilDue;   // Smaller values must appear first in the report.
    int minutesNeeded; // Break equal-deadline ties with smaller durations first.
};

bool comesBeforeOrEqual(const RepairTask *left, const RepairTask *right);
void mergeTaskView(RepairTask *view[], RepairTask *temporary[],
                   int first, int middle, int last);
void mergeSortView(RepairTask *view[], RepairTask *temporary[], int first, int last);
void displayOriginal(const RepairTask tasks[], int count);
void displayView(RepairTask *view[], int count);

int main()
{
    const int TASK_COUNT = 8;
    RepairTask tasks[TASK_COUNT] =
    {
        {"RT-101", 3, 30}, {"RT-102", 1, 20},
        {"RT-103", 2, 15}, {"RT-104", 1, 10},
        {"RT-105", 2, 15}, {"RT-106", 3, 10},
        {"RT-107", 1, 20}, {"RT-108", 2, 5}
    };
    RepairTask *view[TASK_COUNT];      // Borrow addresses of existing tasks.
    RepairTask *temporary[TASK_COUNT]; // Hold addresses while merging the view.
    for (int index = 0; index < TASK_COUNT; index++)
    {
        view[index] = &tasks[index]; // Preserve arrival order in the initial view.
    }

    cout << boolalpha;
    cout << "Original arrival order:" << endl;
    displayOriginal(tasks, TASK_COUNT);
    cout << endl;

    // ===== Resolve these TODOs now (Part C) =====
    cout << "Earlier deadline first: "
         << comesBeforeOrEqual(&tasks[1], &tasks[0]) << endl;
    cout << "Shorter duration within same deadline: "
         << comesBeforeOrEqual(&tasks[3], &tasks[1]) << endl;
    cout << "Exact tie keeps left: "
         << comesBeforeOrEqual(&tasks[2], &tasks[4]) << endl;
    cout << "Later deadline first: "
         << comesBeforeOrEqual(&tasks[0], &tasks[1]) << endl;
    cout << endl;

    // ===== Resolve these TODOs later (Part D) =====
    // TODO (Part D): Call mergeSortView for the complete logical range.
    mergeSortView(view, temporary, 0, TASK_COUNT - 1);

    // TODO (Part D): Display the sorted view with a descriptive heading.
    cout << "Sorted view (earlier deadline first, shorter duration within same deadline):" << endl;
    displayView(view, TASK_COUNT);
    cout << endl;

    // TODO (Part D): Display tasks again to prove that arrival order did not change.
    cout << "Original arrival order after sorting view:" << endl;
    displayOriginal(tasks, TASK_COUNT);

    return 0;
}

bool comesBeforeOrEqual(const RepairTask *left, const RepairTask *right)
{
    // ===== Resolve this TODO now (Part C) =====
    if (left->daysUntilDue < right->daysUntilDue)
    {
        return true; // Left has an earlier deadline.
    }
    else if (left->daysUntilDue > right->daysUntilDue)
    {
        return false; // Right has an earlier deadline.
    }
    else
    {
        // Deadlines are equal; compare minutesNeeded.
        if (left->minutesNeeded < right->minutesNeeded)
        {
            return true; // Left has a shorter duration.
        }
        else if (left->minutesNeeded > right->minutesNeeded)
        {
            return false; // Right has a shorter duration.
        }
        else
        {
            return true; // Exact tie; preserve left's arrival order.
        }
    }
}

// ===== Resolve these TODOs later (Part D) =====
void mergeSortView(RepairTask *view[], RepairTask *temporary[], int first, int last)
{
    // TODO (Part D): Implement recursive merge sort using inclusive indices.
    if (first < last)
    {
        int middle = first + (last - first) / 2; // Avoid overflow for large indices.
        mergeSortView(view, temporary, first, middle); // Sort the left half.
        mergeSortView(view, temporary, middle + 1, last); // Sort the right half.
        mergeTaskView(view, temporary, first, middle, last); // Merge the two halves.
    }
}

void mergeTaskView(RepairTask *view[], RepairTask *temporary[],
                   int first, int middle, int last)
{
    // TODO (Part D): Merge two sorted segments using comesBeforeOrEqual.
    int leftIndex = first;       // Start of the left segment.
    int rightIndex = middle + 1; // Start of the right segment.
    int tempIndex = first;       // Start of the temporary array.

    while (leftIndex <= middle && rightIndex <= last)
    {
        if (comesBeforeOrEqual(view[leftIndex], view[rightIndex]))
        {
            temporary[tempIndex++] = view[leftIndex++]; // Take from left.
        }
        else
        {
            temporary[tempIndex++] = view[rightIndex++]; // Take from right.
        }
    }
    while (leftIndex <= middle)
    {
        temporary[tempIndex++] = view[leftIndex++]; // Copy remaining left elements.
    }
    while (rightIndex <= last)
    {
        temporary[tempIndex++] = view[rightIndex++]; // Copy remaining right elements.
    }
   
    // TODO (Part D): Preserve pending pointers and copy the merged segment back.
    for (int index = first; index <= last; index++)
    {
        view[index] = temporary[index]; // Copy back to the original view.
    }
}

void displayOriginal(const RepairTask tasks[], int count)
{
    for (int index = 0; index < count; index++)
    {
        cout << "Task: " << tasks[index].taskId
             << " | Days until due: " << tasks[index].daysUntilDue
             << " | Minutes: " << tasks[index].minutesNeeded << endl;
    }
}

void displayView(RepairTask *view[], int count)
{
    for (int index = 0; index < count; index++)
    {
        cout << "Task: " << view[index]->taskId
             << " | Days until due: " << view[index]->daysUntilDue
             << " | Minutes: " << view[index]->minutesNeeded << endl;
    }
}

/*
 * Analysis Answers
 *
 * C5 - Two-field decision
 * Explain the result for RT-103 compared with RT-108. Which field decides it?
 * Answer:
 * RT-103 has a later deadline (2 days) than RT-108 (2 days), so the first field (daysUntilDue) is equal. 
 * The second field (minutesNeeded) decides the order, with RT-103 needing 15 minutes and RT-108 needing 5 minutes. 
 * Therefore, RT-108 comes before RT-103 in the sorted view.
 * 
 * D1 - Recursive ranges
 * Show first, last, middle, and the base-case evaluations along the first branch
 * starting at 0..7. Identify where execution resumes after the call for 0..0.
 * Answer:
 * START: first=0, last=7, middle=3
 * next branch: first=0, last=3, middle=1
 * next branch: first=0, last=1, middle=0
 * base case: first=0, last=0 (returns)
 * resume: execution resumes at first=0, last=1, middle=0 to merge 0..0 and 1..1.
 * 
 *
 * D2 - Stable ties
 * Identify both pairs of tasks that tie in the two sort fields. Explain how the
 * comparator and the merge preserve their arrival order.
 * Answer:
 * The two pairs of tasks that tie in the sort fields are: RT-102 and RT-107 (both have 1 day until due and 20 minutes needed), and RT-103 and RT-105 (both have 2 days until due and 15 minutes needed).
 *
 * D3 - Time, space, and original data
 * Give the sorting time and auxiliary-space order of this pointer-array version.
 * Compare with the linked-list sort in Part B and explain why the original task
 * storage order is preserved here but the node order changes in Part B.
 * Answer:
 * Time: The sorting time for the pointer-array version is O(n log n), where n is the number of tasks. 
 * This is because merge sort divides the array into halves recursively and merges them back together, resulting in logarithmic depth and linear work at each level.
 * space: The auxiliary space for the pointer-array version is O(n) due to the temporary array used for merging.
 * In contrast, the linked-list sort in Part B also has a time complexity of O(n log n) and an auxiliary space complexity of O(n) due to the recursive call stack.
 *  However, the original task storage order is preserved in the pointer-array version because we are sorting pointers to existing tasks without modifying the tasks themselves. 
 * In Part B, the linked-list sort changes the order of nodes in the list, which alters the original order of tasks in memory.
 */