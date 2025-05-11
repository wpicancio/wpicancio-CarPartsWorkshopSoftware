## Automotive Parts Inventory Management System

## Description
An inventory management system developed in C for auto parts stores, dealerships and repair stores. The software allows complete control of the stock of tabelies (parts tables) and sales records, facilitating inventory management and monitoring of commercial transactions.

## Main Features

### Stock Management (Tabelies)
- Parts Entry: Detailed parts registration with information such as car model, make, year, color, reference, price and quantity in stock.
- **Stock List**: Complete view of all available inventory
- Search**: Quick search for specific parts in stock
- **Removal**: Deletion of items from the register when necessary
- Automatic update**: Automatic adjustment of quantities after sales

### Sales Management
- Sales Register**: Documentation of transactions with stock availability validation
- Sales History**: Listing of all sales made
- **Automatic Calculation**: Determination of the total value of sales

## Technical Aspects
- Language**: Developed in C
- Storage Uses binary files for data persistence
- **Data Structures**: Implements structs to organize information
- **Portability**: Compatible with different operating systems
- **Interface**: Interactive menu via command line

## Differentials
- Intelligent stock check during sales
- Automatic lowercase conversion in searches for greater flexibility
- Temporary file system to guarantee data integrity
- Data entry validation
- Automatic removal of out-of-stock products

## How to use
1. Compile the source code with a C compiler
2. Run the generated binary file
3. Navigate through the main menu between the Stock and Sales options
4. Follow the on-screen instructions to perform the desired operations

## Data Structure
The system uses two main structures:
- `struct tablies`: Stores complete information about the parts in stock
- `struct sales`: Records the details of commercial transactions

## Future Contributions and Improvements
- Implementation of a graphical interface
- Generation of reports and statistics
- Automatic data backup
- Alert system for low stock
- Integration with barcode readers

---

Developed to facilitate stock and sales control in the automotive sector, guaranteeing efficiency and precision in daily operations.
