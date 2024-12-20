#include <iostream>  // Подключение библиотеки для ввода/вывода

#include <vector>    // Подключение библиотеки для работы с контейнером vector

#include <string>    // Подключение библиотеки для работы со строками

#include <algorithm> // Подключение библиотеки для использования алгоритмов (например, sort)

using namespace std; // Использование стандартного пространства имен

// Класс Car представляет автомобиль

class Car {

private:

    string make;          // Марка автомобиля (например, Toyota, BMW)

    string model;         // Модель автомобиля (например, Corolla, X5)

    string licensePlate;  // Номерной знак автомобиля

public:

    // Конструктор для инициализации автомобиля с указанными значениями

    Car(string make, string model, string licensePlate)

        : make(make), model(model), licensePlate(licensePlate) {}

    // Метод для получения информации об автомобиле в виде строки

    string getDetails() const {

        return "Make: " + make + ", Model: " + model + ", License Plate: " + licensePlate;

    }

    // Метод для получения номерного знака автомобиля

    string getLicensePlate() const {

        return licensePlate;

    }

};

// Базовый класс Person для представления человека

class Person {

protected:

    string name; // Имя человека

public:

    // Конструктор для инициализации имени

    Person(string name) : name(name) {}

    // Метод для получения имени человека

    string getName() const {

        return name;

    }

};

// Класс Client представляет клиента автосервиса и наследует класс Person

class Client : public Person {

private:

    string phoneNumber;       // Номер телефона клиента

    vector<Car> cars;         // Список автомобилей, принадлежащих клиенту

public:

    // Конструктор для инициализации клиента с именем и номером телефона

    Client(string name, string phoneNumber) : Person(name), phoneNumber(phoneNumber) {}

    // Метод для добавления автомобиля в список клиента

    void addCar(const Car& car) {

        cars.push_back(car);

    }

    // Метод для получения списка автомобилей клиента

    vector<Car>& getCars() {

        return cars;

    }

    // Метод для получения номера телефона клиента

    string getPhoneNumber() const {

        return phoneNumber;

    }

};

// Класс Service представляет услугу автосервиса

class Service {

private:

    string description; // Описание услуги (например, "Замена масла")

    double price;       // Стоимость услуги

public:

    // Конструктор для инициализации услуги с описанием и ценой

    Service(string description, double price) : description(description), price(price) {}

    // Метод для получения описания услуги

    string getDescription() const {

        return description;

    }

    // Метод для получения стоимости услуги

    double getPrice() const {

        return price;

    }

};

// Класс Employee представляет сотрудника автосервиса и наследует класс Person

class Employee : public Person {

private:

    string position; // Должность сотрудника (например, "Механик")

public:

    // Конструктор для инициализации сотрудника с именем и должностью

    Employee(string name, string position) : Person(name), position(position) {}

    // Метод для получения должности сотрудника

    string getPosition() const {

        return position;

    }

};

// Класс Order представляет заказ автосервиса

class Order {

private:

    string clientName;       // Имя клиента, связанного с заказом

    string carDetails;       // Детали автомобиля (например, "Toyota Corolla")

    string serviceDetails;   // Детали услуги (например, "Замена масла")

    string employeeName;     // Имя сотрудника, выполняющего заказ

    double totalCost;        // Общая стоимость заказа

    string orderDate;        // Дата заказа

public:

    // Конструктор для создания заказа с указанными параметрами

    Order(string clientName, string carDetails, string serviceDetails, string employeeName, double totalCost, const string& orderDate)

        : clientName(clientName), carDetails(carDetails), serviceDetails(serviceDetails),

          employeeName(employeeName), totalCost(totalCost), orderDate(orderDate) {}

    // Метод для получения информации о заказе в виде строки

    string getDetails() const {

        return "Client: " + clientName + ", Car: " + carDetails + ", Service: " + serviceDetails + 

               ", Employee: " + employeeName + ", Total: $" + to_string(totalCost) + ", Date: " + orderDate;

    }

};

// Класс AutoService представляет автосервис и его функциональность

class AutoService {

private:

    string name;                   // Название автосервиса

    vector<Service> services;      // Список услуг, предоставляемых автосервисом

    vector<Employee> employees;    // Список сотрудников автосервиса

    vector<Order> orders;          // Список заказов, выполненных автосервисом

public:

    // Конструктор для инициализации автосервиса с названием

    AutoService(string name) : name(name) {}

    // Метод для добавления новой услуги в список

    void addService(const Service& service) {

        services.push_back(service);

    }

    // Метод для добавления нового сотрудника в список

    void addEmployee(const Employee& employee) {

        employees.push_back(employee);

    }

    // Метод для создания нового заказа и добавления его в список

    void createOrder(const string& clientName, const string& carDetails, const string& serviceDetails, const string& employeeName, double totalCost, const string& orderDate) {

        orders.emplace_back(clientName, carDetails, serviceDetails, employeeName, totalCost, orderDate);

    }

    // Метод для вывода списка услуг на экран

    void listServices() const {

        for (const auto& service : services) {

            cout << service.getDescription() << " - $" << service.getPrice() << endl;

        }

    }

    // Метод для вывода списка сотрудников на экран

    void listEmployees() const {

        for (const auto& employee : employees) {

            cout << employee.getName() << " - " << employee.getPosition() << endl;

        }

    }

    // Метод для вывода списка заказов на экран

    void listOrders() const {

        for (size_t i = 0; i < orders.size(); ++i) {

            cout << i + 1 << ") " << orders[i].getDetails() << endl; // Индексация начинается с 1

        }

    }

    // Метод для удаления заказа по индексу

    void deleteOrder(size_t index) {

        if (index < orders.size()) {

            orders.erase(orders.begin() + index); // Удаление заказа по индексу

            cout << "Order removed successfully!" << endl;

        } else {

            cout << "Invalid order index." << endl; // Сообщение об ошибке, если индекс некорректный

        }

    }

    // Метод для получения списка услуг (доступ для других частей программы)

    vector<Service>& getServices() {

        return services;

    }

    // Метод для получения списка сотрудников (доступ для других частей программы)

    vector<Employee>& getEmployees() {

        return employees;

    }

};

