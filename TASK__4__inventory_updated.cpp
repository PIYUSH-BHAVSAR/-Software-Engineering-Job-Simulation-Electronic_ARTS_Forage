#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

class Item {
private:
    std::string name;
    int quantity;
    float price;

public:
    // Constructor to initialize item attributes
    Item(std::string name, int quantity, float price)
        : name{std::move(name)}, quantity{quantity}, price{price} {}

    // Getter functions
    std::string get_name() const { return name; }
    int get_quantity() const { return quantity; }
    float get_price() const { return price; }

    // Setter function for quantity
    void set_quantity(int new_quantity) { quantity = new_quantity; }

    // Check if quantity is zero
    bool is_empty() const { return quantity == 0; }
};

class Inventory {
private:
    std::unordered_map<std::string, std::unique_ptr<Item>> items; // Using unordered_map for fast lookups
    float total_money;

    // Display item data
    static void display_data(const Item& item) {
        std::cout << "\nItem name: " << item.get_name()
                  << "\nQuantity: " << item.get_quantity()
                  << "\nPrice: " << item.get_price();
    }

public:
    Inventory() : total_money{0} {}

    // Add a new item to the inventory
    void add_item() {
        std::string name;
        int quantity;
        float price;

        std::cin.ignore();
        std::cout << "\nEnter item name: ";
        std::cin >> name;
        std::cout << "Enter quantity: ";
        std::cin >> quantity;
        std::cout << "Enter price: ";
        std::cin >> price;

        // Check if item already exists
        auto it = items.find(name);
        if (it != items.end()) {
            it->second->set_quantity(it->second->get_quantity() + quantity);
        } else {
            // Add new item to map
            items[name] = std::make_unique<Item>(name, quantity, price);
        }
    }

    // Sell an item
    void sell_item() {
        std::string item_to_check;
        std::cin.ignore();
        std::cout << "\nEnter item name to sell: ";
        std::cin >> item_to_check;

        auto it = items.find(item_to_check); // Lookup the item by name
        if (it != items.end()) {
            int quantity_to_sell;
            std::cout << "\nEnter number of items to sell: ";
            std::cin >> quantity_to_sell;

            Item* item = it->second.get();
            if (quantity_to_sell <= item->get_quantity()) {
                float money_earned = item->get_price() * quantity_to_sell;
                item->set_quantity(item->get_quantity() - quantity_to_sell);
                std::cout << "\nItems sold\nMoney received: " << money_earned;
                total_money += money_earned;

                // If quantity reaches zero, remove the item from the inventory
                if (item->is_empty()) {
                    std::cout << "\nItem out of stock, removing from inventory.";
                    items.erase(it);
                }
            } else {
                std::cout << "\nCannot sell more items than available.";
            }
        } else {
            std::cout << "\nThis item is not in your inventory.";
        }
    }

    // List all items in the inventory
    void list_items() const {
        if (items.empty()) {
            std::cout << "\nInventory is empty.";
            return;
        }

        for (const auto& pair : items) {
            display_data(*pair.second);
            std::cout << "\n";
        }
    }

    // Show total earnings
    void show_total_money() const {
        std::cout << "\nTotal earnings: " << total_money << std::endl;
    }
};

// Main function
int main() {
    int choice;
    Inventory inventory_system;

    std::cout << "Welcome to the inventory management system!";

    while (true) {
        std::cout << "\n\nMENU\n"
                  << "1. Add new item\n"
                  << "2. Sell item\n"
                  << "3. List items\n"
                  << "4. Show total earnings\n"
                  << "5. Exit\n\n"
                  << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                inventory_system.add_item();
                break;
            case 2:
                inventory_system.sell_item();
                break;
            case 3:
                inventory_system.list_items();
                break;
            case 4:
                inventory_system.show_total_money();
                break;
            case 5:
                std::cout << "\nExiting...\n";
                return 0;
            default:
                std::cout << "\nInvalid choice entered. Try again.";
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                break;
        }
    }

    return 0;
}
