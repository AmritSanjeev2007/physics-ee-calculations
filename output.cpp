#include "common.hpp"
#include "calculation.hpp"

int main()
{
    convert_units(); // Convert units to cm

    point __centroid = centroid();
    std::cout << "Centroid: " << __centroid << std::endl;

    set_origin(__centroid);

    sort_x();

    std::cout << "Area: " << area() << " cm^2" << std::endl;
    std::cout << "I_xx: " << I_xx() << " cm^4" << std::endl;
    std::cout << "I_yy: " << I_yy() << " cm^4" << std::endl;
    std::cout << "I_xy: " << I_xy() << " cm^4" << std::endl;

    std::cout << "\nPress Enter to exit......." << std::endl;
    getchar();
}