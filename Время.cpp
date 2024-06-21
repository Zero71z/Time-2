#include <iostream>

class Time {
private:
    int hours;
    int minutes;
    int seconds;

public:
    Time(int h = 0, int m = 0, int s = 0) : hours(h), minutes(m), seconds(s) {}

    // Операторы сравнения
    bool operator>(const Time& other) const {
        if (hours > other.hours) return true;
        if (hours == other.hours && minutes > other.minutes) return true;
        return (hours == other.hours && minutes == other.minutes && seconds > other.seconds);
    }

    bool operator<(const Time& other) const {
        return !(*this > other || *this == other);
    }

    bool operator==(const Time& other) const {
        return hours == other.hours && minutes == other.minutes && seconds == other.seconds;
    }

    bool operator!=(const Time& other) const {
        return !(*this == other);
    }

    // Арифметические операторы
    Time operator+(const Time& other) const {
        int total_seconds = hours * 3600 + minutes * 60 + seconds + other.hours * 3600 + other.minutes * 60 + other.seconds;
        return Time(total_seconds / 3600, (total_seconds % 3600) / 60, total_seconds % 60);
    }

    Time& operator+=(const Time& other) {
        *this = *this + other;
        return *this;
    }

    Time operator-(const Time& other) const {
        int total_seconds = hours * 3600 + minutes * 60 + seconds - (other.hours * 3600 + other.minutes * 60 + other.seconds);
        if (total_seconds < 0) {
            total_seconds += 86400; // 24 часа в секундах
        }
        return Time(total_seconds / 3600, (total_seconds % 3600) / 60, total_seconds % 60);
    }

    Time& operator-=(const Time& other) {
        *this = *this - other;
        return *this;
    }

    // Преобразовываем в 12-часовой формат 
    void convertTo12HourFormat() {
        int temp_hours = hours % 12;
        std::string period = (hours < 12) ? "AM" : "PM";
        std::cout << "Время в 12-часовом формате: " << temp_hours << ':' << minutes << ':' << seconds << ' ' << period << std::endl;
    }

    friend std::istream& operator>>(std::istream& is, Time& time) {
        is >> time.hours >> time.minutes >> time.seconds;
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Time& time) {
        os << time.hours << ':' << time.minutes << ':' << time.seconds;
        return os;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    Time t1, t2;
    std::cout << "Введите первое время (часы минуты секунды): ";
    std::cin >> t1;

    std::cout << "Введите второе время (часы минуты секунды): ";
    std::cin >> t2;

    // Операторы сравнения
    if (t1 > t2) std::cout << "Первое время больше, чем второе." << std::endl;
    if (t1 == t2) std::cout << "Времена равны." << std::endl;
    if (t1 != t2) std::cout << "Времена не равны." << std::endl;

    // Арифметические операторы
    Time sum = t1 + t2;
    std::cout << "Сумма: " << sum << std::endl;

    Time diff = t1 - t2;
    std::cout << "Разница во времени: " << diff << std::endl;

    // Преобразовываем в 12-часовой формат
    t1.convertTo12HourFormat();
    t2.convertTo12HourFormat();

    return 0;
}
