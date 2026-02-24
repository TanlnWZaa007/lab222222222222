#include <iostream>
#include <cstdlib> // สำหรับการใช้ฟังก์ชัน atof() เพื่อแปลง string เป็น double

using namespace std;

int main(int argc, char* argv[]) {

    if (argc == 1) {
        cout << "Please input numbers to find average.\n";
        return 0;
    }

    double sum = 0;
    int count = argc - 1; 
    for (int i = 1; i < argc; ++i) {
        sum += atof(argv[i]); 
    }

    double average = sum / count; 

    cout << "---------------------------------\n";
    cout << "Average of " << count << " numbers = " << average << "\n";
    cout << "---------------------------------\n";

    return 0;
}
