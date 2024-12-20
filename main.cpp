#include "Car_service.hpp" // Подключаем заголовочный файл, который содержит определения классов и функций автосервиса

#include <limits>          // Для работы с пределами чисел (например, очищение ввода)

#include <cassert>         // Для использования макроса assert для проверки условий

#include <memory>          // Для работы с умными указателями (shared_ptr)

#include <iostream>        // Для работы с потоками ввода/вывода

using namespace std; // Используем пространство имен std для удобства

int main() {

    // Создаем вектор умных указателей на объекты класса Car

    vector<shared_ptr<Car>> cars;

    // Создаем вектор умных указателей на объекты класса Client

    vector<shared_ptr<Client>> clients;

    // Создаем объект автосервиса с именем "My Auto Service"

    AutoService service("My Auto Service");

    bool running = true; // Флаг для работы цикла меню

    int choice;          // Переменная для хранения выбора пользователя

    // Основной цикл программы

    while (running) {

        // Вывод меню действий для пользователя

        cout << "1. Добавить клиента\n";

        cout << "2. Показать клиентов\n";

        cout << "3. Добавить автомобиль\n";

        cout << "4. Показать автомобили\n";

        cout << "5. Добавить сотрудника\n";

        cout << "6. Показать сотрудников\n";

        cout << "7. Добавить услугу\n";

        cout << "8. Показать услуги\n";

        cout << "9. Оформить заказ\n";

        cout << "10. Показать заказы\n";

        cout << "11. Удалить заказ\n";

        cout << "12. Выход\n";

        // Запрашиваем у пользователя выбор действия

        cout << "Выберите действие: ";

        cin >> choice;

        // Реализация действий в зависимости от выбора пользователя

        switch (choice) {

            case 1: { // Добавление клиента

                string name, phoneNumber;

                // Запрашиваем имя клиента

                cout << "Введите имя клиента: ";

                cin.ignore(); // Игнорируем символ новой строки

                getline(cin, name); // Считываем строку

                // Запрашиваем номер телефона клиента

                cout << "Введите номер телефона клиента: ";

                getline(cin, phoneNumber);

                // Создаем объект клиента и добавляем его в вектор клиентов

                auto client = make_shared<Client>(name, phoneNumber);

                clients.push_back(client);

                // Уведомляем пользователя об успешном добавлении

                cout << "Клиент успешно добавлен!" << endl;

                break;

            }

            case 2: { // Вывод списка клиентов

                cout << "<- Список клиентов ->" << endl;

                // Перебираем всех клиентов и выводим их данные

                for (const auto& client : clients) {

                    cout << "Имя: " << client->getName() << ", Телефон: " << client->getPhoneNumber() << endl;

                }

                break;

            }

            case 3: { // Добавление автомобиля

                string make, model, licensePlate, clientName;

                // Запрашиваем данные автомобиля

                cout << "Введите марку автомобиля: ";

                cin.ignore();

                getline(cin, make);

                cout << "Введите модель автомобиля: ";

                getline(cin, model);

                cout << "Введите номерной знак автомобиля: ";

                getline(cin, licensePlate);

                cout << "Введите имя клиента: ";

                getline(cin, clientName);

                // Ищем клиента с указанным именем

                auto it = find_if(clients.begin(), clients.end(), [&clientName](const shared_ptr<Client>& client) {

                    return client->getName() == clientName;

                });

                if (it != clients.end()) {

                    // Если клиент найден, создаем автомобиль и привязываем его к клиенту

                    auto car = make_shared<Car>(make, model, licensePlate);

                    (*it)->addCar(*car);

                    cars.push_back(car);

                    cout << "Автомобиль успешно добавлен!" << endl;

                } else {

                    // Если клиент не найден, выводим сообщение

                    cout << "Клиент не найден." << endl;

                }

                break;

            }

            case 4: { // Вывод списка автомобилей

                cout << "<- Список автомобилей ->" << endl;

                // Перебираем все автомобили

                for (const auto& car : cars) {

                    string ownerName = "Неизвестно"; // По умолчанию владелец неизвестен

                    // Ищем владельца автомобиля

                    for (const auto& client : clients) {

                        auto& clientCars = client->getCars();

                        auto it = find_if(clientCars.begin(), clientCars.end(), [&car](const Car& clientCar) {

                            return clientCar.getLicensePlate() == car->getLicensePlate();

                        });

                        if (it != clientCars.end()) {

                            ownerName = client->getName(); // Привязываем имя клиента как владельца

                            break;

                        }

                    }

                    // Выводим данные автомобиля и его владельца

                    cout << car->getDetails() << ", Владелец: " << ownerName << endl;

                }

                break;

            }

            case 5: { // Добавление сотрудника

                string name, position;

                // Запрашиваем данные сотрудника

                cout << "Введите имя сотрудника: ";

                cin.ignore();

                getline(cin, name);

                cout << "Введите должность сотрудника: ";

                getline(cin, position);

                // Добавляем сотрудника в автосервис

                service.addEmployee(Employee(name, position));

                cout << "Сотрудник успешно добавлен!" << endl;

                break;

            }

            case 6: { // Вывод списка сотрудников

                service.listEmployees(); // Вызываем метод для вывода сотрудников

                break;

            }

            case 7: { // Добавление услуги

                string description;

                double price;

                // Запрашиваем данные услуги

                cout << "Введите описание услуги: ";

                cin.ignore();

                getline(cin, description);

                cout << "Введите стоимость услуги: ";

                cin >> price;

                // Добавляем услугу в автосервис

                service.addService(Service(description, price));

                cout << "Услуга успешно добавлена!" << endl;

                break;

            }

            case 8: { // Вывод списка услуг

                service.listServices(); // Вызываем метод для вывода услуг

                break;

            }

            case 9: {

                string licensePlate, serviceName, employeeName;

                cout << "<- Список автомобилей ->" << endl;

                for (const auto& car : cars) {

                    string ownerName = "Неизвестно";  

                    for (const auto& client : clients) {

                        auto& clientCars = client->getCars();

                        auto it = find_if(clientCars.begin(), clientCars.end(), [&car](const Car& clientCar) {

                            return clientCar.getLicensePlate() == car->getLicensePlate();

                        });

                        if (it != clientCars.end()) {

                            ownerName = client->getName();  // Привязываем имя клиента как владельца

                            break;

                        }

                    }

                    cout << car->getDetails() << ", Владелец: " << ownerName << endl;

                }

                cout << "Введите номерной знак автомобиля: ";

                cin.ignore();

                getline(cin, licensePlate);

                auto carIt = find_if(cars.begin(), cars.end(), [&licensePlate](const shared_ptr<Car>& car) {

                    return car->getLicensePlate() == licensePlate;

                });

                if (carIt == cars.end()) {

                    cout << "Автомобиль не найден. Заказ отменен." << endl;

                    break;

                }

                string clientName = "Неизвестно";

                for (const auto& client : clients) {

                    auto& clientCars = client->getCars();

                    auto it = find_if(clientCars.begin(), clientCars.end(), [&carIt](const Car& clientCar) {

                        return clientCar.getLicensePlate() == (*carIt)->getLicensePlate();

                    });

                    if (it != clientCars.end()) {

                        clientName = client->getName();

                        break;

                    }

                }

                if (clientName == "Неизвестно") {

                    cout << "Клиент для этого автомобиля не найден. Заказ отменен." << endl;

                    break;

                }

                cout << "<- Список услуг ->" << endl;

                service.listServices();

                cout << "Введите название услуги: ";

                getline(cin, serviceName);

                auto serviceIt = find_if(service.getServices().begin(), service.getServices().end(), [&serviceName](const Service& srv) {

                    return srv.getDescription() == serviceName;

                });

                if (serviceIt == service.getServices().end()) {

                    cout << "Услуга не найдена. Заказ отменен." << endl;

                    break;

                }

                cout << "<- Список сотрудников ->" << endl;

                service.listEmployees();

                cout << "Введите имя сотрудника: ";

                getline(cin, employeeName);

                if (none_of(service.getEmployees().begin(), service.getEmployees().end(), [&employeeName](const Employee& emp) {

                    return emp.getName() == employeeName;

                })) {

                    cout << "Сотрудник не найден. Заказ отменен." << endl;

                    break;

                }

                string date;

                cout << "Введите дату заказа (в формате ДД-ММ-ГГГГ): ";

                getline(cin, date);

                double totalCost = serviceIt->getPrice();

                service.createOrder(clientName, licensePlate, serviceName, employeeName, totalCost, date);

                cout << "Заказ успешно оформлен!" << endl;

                break;

            }

            case 10: { // Вывод списка заказов

                service.listOrders(); // Вызываем метод для вывода заказов

                break;

            }

            case 11: { // Удаление заказа

                size_t orderIndex;

                cout << "Введите номер заказа для удаления: ";

                cin >> orderIndex;

                // Удаляем заказ по индексу

                service.deleteOrder(orderIndex - 1);

                break;

            }

            case 12: { // Выход из программы

                running = false;

                break;

            }

            default: { // Обработка некорректного ввода

                cout << "Неверный выбор, попробуйте снова." << endl;

                break;

            }

        }

        // Обработка ошибок ввода

        if (cin.fail()) {

            cin.clear(); // Сбрасываем флаг ошибки

            while (getchar() != '\n'); // Очищаем буфер

        }

        cout << endl; // Пустая строка для удобства

    }

    return 0; // Завершаем программу

}

