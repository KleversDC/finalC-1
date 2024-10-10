#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Appliance {
    string name;
    string manufacturer;
    int year;
    double price;
};
void ShowAppliance(const Appliance& appliance) {
    cout << "------------------------------------" << endl;
    cout << "Name : " << appliance.name << endl;
    cout << "Manufacturer : " << appliance.manufacturer << endl;
    cout << "Year : " << appliance.year << endl;
    cout << "Price : " << appliance.price << " USD" << endl;
}
void FillAppliance(Appliance& appliance) {
    cout << "Enter appliance name: ";
    getline(cin, appliance.name);
    cout << "Enter manufacturer: ";
    getline(cin, appliance.manufacturer);
    cout << "Enter year of production: ";
    cin >> appliance.year;
    cout << "Enter price: ";
    cin >> appliance.price;
    cin.ignore();
}
void saveToFile(const vector<Appliance>& appliances, const string& path) {
    ofstream file(path, ios::app);
    if (file.is_open()) {
        for (const auto& appliance : appliances) {
            file << appliance.name << "," << appliance.manufacturer << ","
                << appliance.year << "," << appliance.price << endl;
        }
        file.close();
        cout << "Data saved to file" << endl;
    }
    else {
        cout << "Error opening file" << endl;
    }
}
void loadFromFile(vector<Appliance>& appliances, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        appliances.clear();
        string line;
        while (getline(file, line)) {
            Appliance appliance;
            size_t pos = 0;

            pos = line.find(",");
            appliance.name = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find(",");
            appliance.manufacturer = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find(",");
            appliance.year = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);

            appliance.price = stod(line);

            appliances.push_back(appliance);
        }
        file.close();
        cout << "Data loaded from file" << endl;
    }
    else {
        cout << "Error opening file" << endl;
    }
}
void ShowAppliances(const vector<Appliance>& appliances) {
    cout << "Appliances : " << endl;
    for (const auto& appliance : appliances) {
        ShowAppliance(appliance);
    }
    cout << " ************************** \n";
}
void searchByName(const vector<Appliance>& appliances, const string& name) {
    for (const auto& appliance : appliances) {
        if (appliance.name == name) {
            ShowAppliance(appliance);
        }
    }
}
void searchByManufacturer(const vector<Appliance>& appliances, const string& manufacturer) {
    for (const auto& appliance : appliances) {
        if (appliance.manufacturer == manufacturer) {
            ShowAppliance(appliance);
        }
    }
}

int main() {
    vector<Appliance> appliances;
    string filename = "appliances.txt";
    int choice;

    do {
        cout << "\n===== Appliance Management Menu =====" << endl;
        cout << "1. Add new appliance" << endl;
        cout << "2. Show all appliances" << endl;
        cout << "3. Search by name" << endl;
        cout << "4. Search by manufacturer" << endl;
        cout << "5. Save to file" << endl;
        cout << "6. Load from file" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            Appliance newAppliance;
            FillAppliance(newAppliance);
            appliances.push_back(newAppliance);
            break;
        }
        case 2:
            ShowAppliances(appliances);
            break;
        case 3: {
            string name;
            cout << "Enter appliance name to search: ";
            getline(cin, name);
            searchByName(appliances, name);
            break;
        }
        case 4: {
            string manufacturer;
            cout << "Enter manufacturer to search: ";
            getline(cin, manufacturer);
            searchByManufacturer(appliances, manufacturer);
            break;
        }
        case 5:
            saveToFile(appliances, filename);
            break;
        case 6:
            loadFromFile(appliances, filename);
            break;
        case 0:
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 0);
}
