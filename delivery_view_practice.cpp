/*
 * Course: COEN 2220 - Programming 2
 * Name: [Your Name]
 * Lab: Lab 11 - Recursion and Merge Sort (Part E - Project Application)
 * Description: Practice building a filtered pointer view of delivery orders without altering the original collection.
 * Due date: [Date]
 */

#include <iostream>
#include <string>
using namespace std;

struct OrderPreview
{
    int orderId;
    string orderType;
    string status;
    string building;
    int priority;
};

void displayOrders(const OrderPreview orders[], int count);
void displayView(OrderPreview *view[], int count);

int main()
{
    const int CAPACITY = 4;
    OrderPreview orders[CAPACITY] = {
        {101, "DELIVERY", "PENDING", "Bldg-A", 2},
        {102, "DELIVERY", "COMPLETED", "Bldg-B", 1},
        {103, "DINE_IN", "PENDING", "Bldg-C", 3},
        {104, "DELIVERY", "IN_PROGRESS", "Bldg-A", 1}
    };

    OrderPreview *view[CAPACITY];
    int viewCount = 0;

    cout << "=== Part E: Delivery View Practice ===" << endl << endl;
    cout << "Original orders before building view:" << endl;
    displayOrders(orders, CAPACITY);
    cout << endl;

    // Filter active DELIVERY orders into the view
    for (int i = 0; i < CAPACITY; i++)
    {
        if (orders[i].orderType == "DELIVERY" && 
            (orders[i].status == "PENDING" || orders[i].status == "IN_PROGRESS"))
        {
            view[viewCount++] = &orders[i];
        }
    }

    cout << "Filtered delivery view (active delivery orders only):" << endl;
    displayView(view, viewCount);
    cout << endl;

    cout << "Original orders after building view (proving no changes):" << endl;
    displayOrders(orders, CAPACITY);

    return 0;
}

void displayOrders(const OrderPreview orders[], int count)
{
    for (int i = 0; i < count; i++)
    {
        cout << "ID: " << orders[i].orderId 
             << " | Type: " << orders[i].orderType 
             << " | Status: " << orders[i].status 
             << " | Bldg: " << orders[i].building 
             << " | Priority: " << orders[i].priority << endl;
    }
}

void displayView(OrderPreview *view[], int count)
{
    for (int i = 0; i < count; i++)
    {
        cout << "View Item -> ID: " << view[i]->orderId 
             << " | Type: " << view[i]->orderType 
             << " | Status: " << view[i]->status 
             << " | Bldg: " << view[i]->building 
             << " | Priority: " << view[i]->priority << endl;
    }
}