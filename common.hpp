#ifndef _CALCULATIONS_COMMON_DEFINITION_CPP_
    #define _CALCULATIONS_COMMON_DEFINITION_CPP_

    #define WING_LENGTH_CENTIMETRES 11.1L

    #include <iostream>
    #include <string>
    #include <fstream>
    #include <filesystem>
    #include <algorithm>
    #include <memory>
    #include <cmath>
    
    using number_t = long double;
    struct point{number_t x,y;};

    namespace std
    {
        constexpr point fabs(point _p) noexcept
        {
            return point{fabsl(_p.x),fabsl(_p.y)};
        }
    }

    std::ostream& operator<<(std::ostream& os, const point& p) noexcept
    {
        return os << "{" << p.x << "," << p.y << "}";
    }

    number_t vertices[] {
        1.000000,-0.414472,
        1.349058,-0.369168,
        1.294366,-0.373725,
        1.198656,-0.387398,
        1.089273,-0.401071,
        1.42198,-0.360053,
        1.499459,-0.341822,
        1.567824,-0.328149,
        1.654419,-0.314476,
        1.731899,-0.296246,
        1.827608,-0.287131,
        1.909646,-0.273458,
        1.996241,-0.259785,
        2.078278,-0.246112,
        2.1512,-0.232439,
        2.219565,-0.218766,
        2.297044,-0.195978,
        2.365409,-0.186863,
        2.415543,0.063807,
        2.506695,-0.141286,
        2.579617,0.063807,
        2.643424,-0.09571,
        2.666212,-0.07748,
        2.689,0.045576,
        2.702673,-0.013673,
        2.711789,0.013673,
        2.647982,0.059249,
        2.49758,0.063807,
        2.319832,0.059249,
        2.210449,0.059249,
        2.110181,0.068364,
        2.014472,0.050134,
        1.941549,0.041019,
        1.854954,0.036461,
        1.768359,0.031903,
        1.677207,0.022788,
        1.558709,0.013673,
        1.481229,0.009115,
        1.399191,0.013673,
        1.312597,0.004558,
        1.235117,-0.004558,
        1.139407,-0.01823,
        1.061927,-0.027346,
        0.970775,-0.022788,
        0.888737,-0.031903,
        0.811258,-0.031903,
        0.72922,-0.036461,
        0.642625,-0.036461,
        0.565146,-0.041019,
        0.473993,-0.045576,
        0.396514,-0.050134,
        0.314476,-0.054692,
        0.246112,-0.054692,
        0.17319,-0.059249,
        0.086595,-0.059249,
        -0.004558,-0.054692,
        -0.091153,-0.059249,
        -0.168632,-0.063807,
        -0.278015,-0.063807,
        -0.373726,-0.07748,
        -0.478551,-0.086595,
        -0.556031,-0.07748,
        -0.624395,-0.072922,
        -0.720105,-0.068364,
        -0.783912,-0.068364,
        -0.861392,-0.07748,
        -0.947986,-0.072922,
        -1.016351,-0.082037,
        -1.130292,-0.086595,
        -1.230559,-0.07748,
        -1.321712,-0.082037,
        -1.435653,-0.063807,
        -1.522248,-0.059249,
        -1.640746,-0.054692,
        -1.754687,-0.036461,
        -1.859512,-0.031903,
        -1.955222,-0.009115,
        -2.064605,0.022788,
        -2.164873,0.031903,
        -2.260583,0.059249,
        -2.374524,0.072922,
        -2.452003,-0.360053,
        -2.552271,0.109383,
        -2.652539,0.127614,
        -2.748249,0.127614,
        -2.834844,0.113941,
        -2.86219,-0.104826,
        -2.880421,-0.050134,
        -2.889536,-0.013673,
        -2.825729,-0.145844,
        -2.784711,-0.182305,
        -2.743692,-0.214209,
        -2.693558,-0.246112,
        -2.647982,-0.273458,
        -2.57506,-0.309919,
        -2.520368,-0.337265,
        -2.392754,-0.382841,
        -2.333505,-0.405629,
        -2.256026,-0.428417,
        -2.187661,-0.44209,
        -2.119297,-0.460321,
        -2.05549,-0.469436,
        -1.97801,-0.487666,
        -1.891415,-0.496781,
        -1.823051,-0.501339,
        -1.736456,-0.510454,
        -1.645303,-0.524127,
        -1.531363,-0.528685,
        -1.444768,-0.528685,
        -1.353615,-0.5378,
        -1.276136,-0.542358,
        -1.17131,-0.546915,
        -1.048254,-0.546915,
        -0.952544,-0.551473,
        -0.865949,-0.546915,
        -0.761124,-0.546915,
        -0.688202,-0.556031,
        -0.587934,-0.546915,
        -0.483109,-0.556031,
        -0.369168,-0.546915,
        -0.250669,-0.5378,
        -0.154959,-0.528685,
        -0.031903,-0.524127,
        0.072922,-0.522665,
        0.168632,-0.510518,
        0.259785,-0.492224,
        0.382841,-0.487666,
        0.492224,-0.473993,
        0.578819,-0.464878,
        0.69276,-0.455742,
        0.799111,-0.440521,
        0.910042,-0.428396
    };

    constexpr size_t vertices_size() noexcept { return (sizeof(vertices)/sizeof(vertices[0])); } 
    
    constexpr number_t unit_scale = WING_LENGTH_CENTIMETRES/(1.51246+1.7261); // From arbitrary unit -> metres
    void convert_units() noexcept // converts the vertices from the arbitrary unit scale to the SI scale. Specifically, unit -> cm
    {
        for(int i=0; i<vertices_size(); i++)
        {
            vertices[i] *= unit_scale;
        }
    }

    void print_vertices(std::ostream& os=std::cout) noexcept
    {
        size_t sz = vertices_size()>>1;
        auto arr = reinterpret_cast<const point*>(vertices);

        while(sz--)
        {
            os << arr[sz] << '\n';
        }
        os << std::flush;
    }

#endif