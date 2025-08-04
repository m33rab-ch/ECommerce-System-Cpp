#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;

const int MAX_RECORDS = 100;
const int MAX_ORDERS = 100;

struct Product
{
    string name;
    float price;
    string category;
    int stock;
    string brand;
    string description;
    int purchases;
};

struct Cart
{
    Product product;
    int quantity;
};

struct OrderItem
{
    Product product;
    int quantity;
    float subTotal;
};

struct Order
{
    OrderItem orderItems[MAX_RECORDS];
    int orderItemCount;
    float total;
    string name;
    string address;
    string phone;
    string city;
    string state;
    string paymentTransactionId;
};

void displayMainMenu()
{
    cout << "------ Main Menu ------" << endl;
    cout << "1. Display all products" << endl;
    cout << "2. Search products" << endl;
    cout << "3. Display products detail by #" << endl;
    cout << "4. Add to cart" << endl;
    cout << "5. Display cart" << endl;
    cout << "6. Remove from cart" << endl;
    cout << "7. Checkout" << endl;
    cout << "8. Display My Orders" << endl;
    cout << "9. Display Order Detail by #" << endl;
    cout << "10. Exit" << endl;
    cout << "-----------------------" << endl;
}

void displayProducts(Product products[], int productCount)
{
    for (int i = 0; i < productCount; i++)
    {
        cout << "ID: " << i << endl;
        cout << "Name: " << products[i].name << endl;
        cout << "Price: " << products[i].price << endl;
        cout << "Category: " << products[i].category << endl;
        cout << "Brand: " << products[i].brand << endl;
        cout << endl;
    }
}

void displayDetails(Product products[], int productCount, int index)
{
    if (index >= 0 && index < productCount)
    {
        cout << "Name:  " << products[index].name << endl;
        cout << "Category:  " << products[index].category << endl;
        cout << "Price:  " << products[index].price << endl;
        cout << "Brand:  " << products[index].brand << endl;
        cout << "Description: " << products[index].description << endl;
        cout << "Purchases: " << products[index].purchases << endl;
        cout << "Stock: " << products[index].stock << endl;
        cout << endl;
    }
    else
    {
        cout << "Invalid product ID." << endl;
    }
}

void searchProducts(Product products[], int productCount, string input)
{
    for (int i = 0; i < productCount; i++)
    {
        if (input == products[i].category || input == products[i].name)
        {
            displayDetails(products, productCount, i);
        }
    }
}

Cart addToCart(Product products[], int productCount)
{
    int productId;
    int quantity;

    while (true)
    {
        cout << "Enter the product ID: ";
        cin >> productId;
        if (productId < 0 || productId >= productCount)
        {
            cout << "Invalid product ID. Please enter a valid product ID: ";
        }
        else
        {
            break;
        }
    }
    while (true)
    {
        cout << "Enter the quantity: ";
        cin >> quantity;
        if (quantity < 0 || quantity > products[productId].stock)
        {
            cout << "Invalid quantity. Please enter a valid quantity: ";
        }
        else
        {
            break;
        }
    }

    Cart cart;
    cart.product = products[productId];
    cart.quantity = quantity;
    return cart;
}

float getCartTotal(Cart cart[], int cartCount)
{
    float total = 0.0;
    for (int i = 0; i < cartCount; i++)
    {
        total += cart[i].product.price * cart[i].quantity;
    }
    return total;
}

void displayCart(Cart cart[], int cartCount)
{
    for (int i = 0; i < cartCount; i++)
    {
        cout << "Item #" << i + 1 << endl;
        cout << "Product: " << cart[i].product.name << endl;
        cout << "Price: " << cart[i].product.price << endl;
        cout << "Quantity: " << cart[i].quantity << endl;
        cout << "Subtotal: " << cart[i].product.price * cart[i].quantity << endl;
        cout << endl;
    }
    cout << "Total: $" << getCartTotal(cart, cartCount) << endl;
}

void removeItemFromCart(Cart *cart, int *cartCount)
{
    int index;
    cout << "Enter the item number to remove: ";
    cin >> index;
    if (index <= 0 || index > *cartCount)
    {
        cout << "Invalid item number. Please enter a valid item number." << endl;
    }
    else
    {
        for (int i = index - 1; i < *cartCount - 1; i++)
        {
            cart[i] = cart[i + 1];
        }
        (*cartCount)--;
    }
}

// Function to handle checkout
void checkout(Cart cart[], int &cartCount, Order orders[], int &orderCount)
{
    if (cartCount == 0)
    {
        cout << "Your cart is empty. Add items to the cart before checkout." << endl;
        return;
    }

    if (orderCount >= MAX_ORDERS)
    {
        cout << "Order limit reached. Cannot place more orders." << endl;
        return;
    }

    Order order;
    float total = 0.0;
    order.orderItemCount = 0;

    // Collect order items and calculate total
    for (int i = 0; i < cartCount; i++)
    {
        order.orderItems[order.orderItemCount] = {cart[i].product, cart[i].quantity, cart[i].product.price * cart[i].quantity};
        total += order.orderItems[order.orderItemCount].subTotal;
        order.orderItemCount++;
    }

    order.total = total;

    // Collect customer details
    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, order.name);
    cout << "Enter your address: ";
    getline(cin, order.address);
    cout << "Enter your phone: ";
    getline(cin, order.phone);
    cout << "Enter your city: ";
    getline(cin, order.city);
    cout << "Enter your state: ";
    getline(cin, order.state);
    cout << "Enter payment transaction ID: ";
    getline(cin, order.paymentTransactionId);

    // Save the order
    orders[orderCount] = order;
    orderCount++;

    // Clear the cart
    cartCount = 0;

    cout << "Order placed successfully! Your total is $" << total << endl;
}

// Function to display all orders
void displayMyOrders(Order orders[], int orderCount)
{
    if (orderCount == 0)
    {
        cout << "You have no orders." << endl;
        return;
    }

    for (int i = 0; i < orderCount; i++)
    {
        cout << "Order #" << i + 1 << endl;
        cout << "Total: $" << orders[i].total << endl;
        cout << "Name: " << orders[i].name << endl;
        cout << "Address: " << orders[i].address << endl;
        cout << "Phone: " << orders[i].phone << endl;
        cout << "City: " << orders[i].city << endl;
        cout << "State: " << orders[i].state << endl;
        cout << "Payment Transaction ID: " << orders[i].paymentTransactionId << endl;
        cout << endl;
    }
}

// Function to display the details of a specific order
void displayOrderDetails(Order orders[], int orderCount, int orderIndex)
{
    if (orderIndex < 0 || orderIndex >= orderCount)
    {
        cout << "Invalid order index. Please enter a valid order index." << endl;
        return;
    }

    Order &order = orders[orderIndex];
    cout << "Order #" << orderIndex + 1 << endl;
    cout << "Name: " << order.name << endl;
    cout << "Address: " << order.address << endl;
    cout << "Phone: " << order.phone << endl;
    cout << "City: " << order.city << endl;
    cout << "State: " << order.state << endl;
    cout << "Payment Transaction ID: " << order.paymentTransactionId << endl;
    cout << "Total: $" << order.total << endl;
    cout << endl;
    cout << "Items: " << endl;

    for (int i = 0; i < order.orderItemCount; i++)
    {
        cout << "Item #" << i + 1 << endl;
        cout << "Product: " << order.orderItems[i].product.name << endl;
        cout << "Price: " << order.orderItems[i].product.price << endl;
        cout << "Quantity: " << order.orderItems[i].quantity << endl;
        cout << "Subtotal: " << order.orderItems[i].subTotal << endl;
        cout << endl;
    }
}

int main()
{
    // Read CSV with these attributes

    ifstream productFileIn("Products.csv");

    Product products[MAX_RECORDS];
    int productCount = 0;

    Cart cart[MAX_RECORDS];
    int cartCount = 0;

    Order orders[MAX_ORDERS];
    int orderCount = 0;

    string line;
    istringstream ss;
    while (getline(productFileIn, line))
    {
        ss = istringstream(line);
        getline(ss, products[productCount].name, ',');
        ss >> products[productCount].price;
        ss.ignore();
        getline(ss, products[productCount].category, ',');
        ss >> products[productCount].stock;
        ss.ignore();
        getline(ss, products[productCount].brand, ',');
        getline(ss, products[productCount].description, ',');
        ss >> products[productCount].purchases;
        ss.ignore();
        productCount++;
    }

    productFileIn.close();

    bool exit = false;

    while (!exit)
    {
        displayMainMenu();
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            displayProducts(products, productCount);
            break;
        case 2:
        {
            string searchInput;
            cout << "Enter product name or category to search: ";
            cin.ignore();
            getline(cin, searchInput);
            searchProducts(products, productCount, searchInput);
            break;
        }
        case 3:
        {
            int index;
            cout << "Enter product ID to display details: ";
            cin >> index;
            displayDetails(products, productCount, index);
            break;
        }
        case 4:
            if (cartCount < MAX_RECORDS)
            {
                cart[cartCount] = addToCart(products, productCount);
                cartCount++;
            }
            else
            {
                cout << "Cart is full. Cannot add more items." << endl;
            }
            break;
        case 5:
            displayCart(cart, cartCount);
            break;
        case 6:
            removeItemFromCart(cart, &cartCount);
            break;
        case 7:
            checkout(cart, cartCount, orders, orderCount);
            break;
        case 8:
            displayMyOrders(orders, orderCount);
            break;
        case 9:
        {
            int orderIndex;
            cout << "Enter the order number to display details: ";
            cin >> orderIndex;
            displayOrderDetails(orders, orderCount, orderIndex - 1);
            break;
        }
        case 10:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}
