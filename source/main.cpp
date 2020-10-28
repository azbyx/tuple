#include <iostream>
#include <cassert>
#include "../header/custom_tuple.h"


void do_it(){
    int vari = 111;
    double vard = 2.2;
    const char* varstr = "ddd";

    int vari1 = 999;
    double vard1 = 0.9999;
    const char* varstr1 = "zzz";
    auto tpl = make_custom_tuple(vari, vard, varstr);

    auto tpltie = tpl;
    (void) tpltie;
    //auto tplr = make_custom_tuple(1, 2, 3);
    std::cout << "vars: vari, vard, varstr in tpl:" << std::endl;
    std::cout << custom_get<0>(tpl) << ' ' << custom_get<1>(tpl) << ' ' << custom_get<2>(tpl) << std::endl;
    std::cout << "vars: vari1, vard1, varstr1 before assignment:" << std::endl;
    std::cout << vari1 << ' ' << vard1 << ' ' << varstr1 << std::endl;
    //
    custom_tie(vari1, vard1, varstr1) = tpl;
    //custom_get<0>(tpltie) = custom_get<0>(tpl), custom_get<1>(tpltie) = custom_get<1>(tpl), custom_get<2>(tpltie) = custom_get<2>(tpl);
    std::cout << "vars: vari1, vard1, varstr1 after assignment:" << std::endl;
    std::cout << vari1 << ' ' << vard1 << ' ' << varstr1 << std::endl;
}


auto getPerson() {
    const std::string name = "Petia";
    const std::string secondName = "Ivanoff";
    const std::size_t age = 23;
    const std::string department = "Sale";
    return make_custom_tuple(name, secondName, age, department);
}

int main(int, char**) {

    std::string name, secondName, department;
    std::size_t age;

    custom_tie(name, secondName, age, department) = getPerson();

    assert(name == "Petia");
    assert(secondName == "Ivanoff");
    assert(age == 23);
    assert(department == "Sale");

    do_it();

    return 0;
}

