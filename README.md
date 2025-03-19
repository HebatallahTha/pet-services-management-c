# Pet Services Management in C 🐶🐱

## 📌 Description

This **C program** is designed for managing pet services. It allows users to enter pet details, select services for their pets, and process payments. It also supports pet records, with the ability to check if a pet is already in the system or create a new pet record.

The program performs the following tasks:
- Add or find pet records.
- Select services available for pets.
- Record payment information and generate receipts.
- Display a summary of the total number of pets served and total payment collected.

## ✨ Features
- **Pet Record Management**: Users can search for a pet or create a new pet record if the pet is not already in the system.
- **Service Selection**: Users can choose services from a list and add them to the pet's invoice.
- **Payment Processing**: Payment details, including credit card information, are processed and stored for each transaction.
- **Receipt Generation**: After payment, the program prints a receipt with the services provided, total cost, and payment details.

## 🛠️ How to Run

1. **Clone the repository:**
    ```bash
    git clone <repository_url>
    ```

2. **Navigate into the project directory:**
    ```bash
    cd pet-services-management-c
    ```

3. **Compile the C program:**
    ```bash
    gcc pet_services.c -o pet_services
    ```

4. **Run the program:**
    ```bash
    ./pet_services
    ```

## 📂 File Structure

- `pet_services.c`: The C source file that contains the program logic for managing pets, services, payments, and receipts.
- `allServices.csv`: A CSV file containing available services for pets.
- `allPets.csv`: A CSV file storing pet records.
- `README.md`: This file, containing details about the project.

## 🔧 Dependencies

- **C Standard Library**: The program uses standard input/output, string handling, and file operations from the C Standard Library.
- **CSV files**: The program reads data from CSV files (`allServices.csv` and `allPets.csv`) to populate the service and pet records.

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details. 📝
