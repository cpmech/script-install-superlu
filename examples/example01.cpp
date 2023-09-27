#include <iostream>

using namespace std;

int main(int argc, char **argv) try {

    cout << " >>>>> ~+~+~+~+~+~+~+~+~+~+~+~+ <<<<< " << endl;
    cout << " . . . Hello SuperLU Example 01 . . . " << endl;
    cout << " >>>>> ~+~+~+~+~+~+~+~+~+~+~+~+ <<<<< " << endl;

    return 0;

} catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    return 1;
} catch (std::string &msg) {
    std::cout << msg.c_str() << std::endl;
    return 1;
} catch (const char *msg) {
    std::cout << msg << std::endl;
    return 1;
} catch (...) {
    std::cout << "some unknown exception happened" << std::endl;
    return 1;
}
