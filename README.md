# Опциональное задание б/н.

[![Build Status](https://travis-ci.com/azbyx/tuple.svg?branch=master&status=created)](https://travis-ci.com/azbyx/tuple)
[![Download](https://api.bintray.com/packages/azbyx/tuple/tuple/images/download.svg) ](https://bintray.com/azbyx/tuple/tuple/_latestVersion)

# Для закрепления материала по std::tuple выполните следующие задания.

# Задание 1.

Реализуйте свой вариант `std::tie`.
Следующий код должен быть валидным:
```
#include <string>
#include <tuple>
#include <cassert>

auto getPerson() {
 const std::string name = "Petia";
 const std::string secondName = "Ivanoff";
 const std::size_t age = 23;
 const std::string department = "Sale";
 return std::make_tuple(
 name, secondName, age, department
 );
}

int main(int argc, char * argv[]) {
 std::string name, secondName, department;
 std::size_t age;
 custom_tie(name, secondName, age, department) = getPerson();
 assert(name == "Petia");
 assert(secondName == "Ivanoff");
 assert(age == 23);
 assert(department == "Sale");
 return 0;
}
```

# Задание 2. 

Реализуйте свой вариант `std::tuple`. Предыдущий пример должен валидно работать с
`custom_tuple` и `custom_tie`.
