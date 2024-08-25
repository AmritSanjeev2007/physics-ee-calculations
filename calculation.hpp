#ifndef _POINTS_DEFINITION_HPP_
    #define _POINTS_DEFINITION_HPP_

    #include "common.hpp"
    
    point centroid() noexcept
    {
        size_t coordinates_length = vertices_size()>>1;
        size_t save_length = coordinates_length;

        point __centroid {0,0};

        while(coordinates_length--) 
        {
            __centroid.x += reinterpret_cast<const point*>(vertices)[coordinates_length].x;
            __centroid.y += reinterpret_cast<const point*>(vertices)[coordinates_length].y;
        }

        __centroid.x/=save_length; __centroid.y/=save_length; 

        return __centroid;
    }

    void set_origin(point origin) noexcept
    {
        size_t sz = vertices_size()>>1;
        auto arr = reinterpret_cast<point*>(vertices);

        while(sz--)
        {
            arr[sz].x -= origin.x;
            arr[sz].y -= origin.y;
        }
    }

    struct point_compare_x {
        bool operator ()(point a, point b) const {return a.x < b.x;}
    };
    struct point_compare_y {
        bool operator ()(point a, point b) const {return a.y < b.y;}
    };

    number_t area() noexcept
    {
        point a={0,0};
        
        const point* arr = reinterpret_cast<point*>(vertices);
        size_t vertices_length = (vertices_size()>>1);

        number_t above_sum=0;
        // Above
        for(int i=0; i<vertices_length; i++)
        {
            if(arr[i].y >= 0 && a.x==0 && a.y==0) { a = arr[i]; continue; }

            if(arr[i].y < 0) continue;

            point b = arr[i];

            number_t area = 0.5*(b.x-a.x)*(b.y+a.y); // Area of trapezium

            above_sum+=area;
            a=b;
        }
        a={0,0};

        number_t below_sum=0;
        // Below
        for(int i=0; i<vertices_length; i++)
        {
            if(arr[i].y <= 0 && a.x==0 && a.y==0) { a = arr[i]; continue; }

            if(arr[i].y > 0) continue;

            point b = arr[i];

            number_t area = 0.5*(b.x-a.x)*(b.y+a.y);

            below_sum+=std::fabs(area);
            a=b;
        }

        return (above_sum+below_sum);
    }

    number_t I_xx() noexcept
    {
        point a={0,0};
        
        const point* arr = reinterpret_cast<point*>(vertices);
        size_t vertices_length = (vertices_size()>>1);

        number_t above_sum=0;
        // Above
        for(int i=0; i<vertices_length; i++)
        {
            if(arr[i].y >= 0 && a.x==0 && a.y==0) { a = arr[i]; continue; }

            if(arr[i].y < 0) continue;

            point b = arr[i];

            number_t slope = (std::fabs(b.y)-std::fabs(a.y))/(b.x-a.x);
            number_t y_intercept = std::fabs(a.y)-(slope*a.x);

            number_t p=0.25*powl(slope,3), q=powl(slope,2)*y_intercept, r=1.5*slope*powl(y_intercept,2), s=powl(y_intercept,3);

            number_t final = p*powl(b.x,4)+q*powl(b.x,3)+r*powl(b.x,2)+s*b.x;
            number_t initial = p*powl(a.x,4)+q*powl(a.x,3)+r*powl(a.x,2)+s*a.x;

            above_sum+=final-initial;
            a=b;
        }
        a={0,0};

        number_t below_sum=0;
        // Below
        for(int i=0; i<vertices_length; i++)
        {
            if(arr[i].y <= 0 && a.x==0 && a.y==0) { a = arr[i]; continue; }

            if(arr[i].y > 0) continue;

            point b = arr[i];

            number_t slope = (std::fabs(b.y)-std::fabs(a.y))/(b.x-a.x);
            number_t y_intercept = std::fabs(a.y)-(slope*a.x);

            // std::fabs is used to make sure that all points are above the y-axis. Since we are comparing each region separately,
            // it doesn't matter whether it is above or below the y-axis since we sum each moment of inertia.
            // Hence transforming them all to be above the y-axis is valid, since we are just reflecting each region.

            number_t p=0.25*powl(slope,3), q=powl(slope,2)*y_intercept, r=1.5*slope*powl(y_intercept,2), s=powl(y_intercept,3);

            number_t final = p*powl(b.x,4)+q*powl(b.x,3)+r*powl(b.x,2)+s*b.x;
            number_t initial = p*powl(a.x,4)+q*powl(a.x,3)+r*powl(a.x,2)+s*a.x;

            below_sum+=final-initial;
            a=b;
        }

        return (above_sum+below_sum);

        // The for loop computes the moment of inertia for each region and sums them together.
    }
    number_t I_yy() noexcept
    {
        point a={0,0};
        
        const point* arr = reinterpret_cast<point*>(vertices);
        size_t vertices_length = (vertices_size()>>1);

        number_t above_sum=0;
        // Above
        for(int i=0; i<vertices_length; i++)
        {
            if(arr[i].y >= 0 && a.x==0 && a.y==0) { a = std::fabs(arr[i]); continue; }

            if(arr[i].y < 0) continue;

            point b = std::fabs(arr[i]);

            std::swap(a,b); // Since all the points are in first quardrant.

            number_t slope = (b.y-a.y)/(b.x-a.x);
            number_t y_intercept = a.y-(slope*a.x);

            number_t p=0.25*slope, q=(y_intercept/3);

            number_t final = p*powl(b.x,4)+q*powl(b.x,3);
            number_t initial = p*powl(a.x,4)+q*powl(a.x,3);

            above_sum+=final-initial;
            a=b;
        }
        a={0,0};

        number_t below_sum=0;
        // Below
        for(int i=0; i<vertices_length; i++)
        {
            if(arr[i].y <= 0 && a.x==0 && a.y==0) { a = std::fabs(arr[i]); continue; }

            if(arr[i].y > 0) continue;

            point b = std::fabs(arr[i]);

            std::swap(a,b); // Since all the points are in first quardrant.

            number_t slope = (b.y-a.y)/(b.x-a.x);
            number_t y_intercept = a.y-(slope*a.x);

            number_t p=0.25*slope, q=(y_intercept/3);

            number_t final = p*powl(b.x,4)+q*powl(b.x,3);
            number_t initial = p*powl(a.x,4)+q*powl(a.x,3);

            below_sum+=final-initial;
            a=b;
        }

        return (above_sum+below_sum);
    }
    number_t I_xy() noexcept
    {
        point a={0,0};
        
        const point* arr = reinterpret_cast<point*>(vertices);
        size_t vertices_length = (vertices_size()>>1);

        number_t above_sum=0;
        // Above
        for(int i=0; i<vertices_length; i++)
        {
            if(arr[i].y >= 0 && a.x==0 && a.y==0) { a = std::fabs(arr[i]); continue; }

            if(arr[i].y < 0) continue;

            point b = std::fabs(arr[i]);

            std::swap(a,b); // Since all the points are in first quardrant.

            number_t slope = (b.y-a.y)/(b.x-a.x);
            number_t y_intercept = a.y-(slope*a.x);

            number_t p=0.25*powl(slope,2), q=(2/3)*slope*y_intercept, r=0.5*powl(y_intercept,2);

            number_t final = p*powl(b.x,4)+q*powl(b.x,3)+r*powl(b.x,2);
            number_t initial = p*powl(a.x,4)+q*powl(a.x,3)+r*powl(a.x,2);

            above_sum+=final-initial;
            a=b;
        }
        a={0,0};

        number_t below_sum=0;
        // Below
        for(int i=0; i<vertices_length; i++)
        {
            if(arr[i].y <= 0 && a.x==0 && a.y==0) { a = std::fabs(arr[i]); continue; }

            if(arr[i].y > 0) continue;

            point b = std::fabs(arr[i]);

            std::swap(a,b); // Since all the points are in first quardrant.

            number_t slope = (b.y-a.y)/(b.x-a.x);
            number_t y_intercept = a.y-(slope*a.x);

            number_t p=0.25*powl(slope,2), q=(2/3)*slope*y_intercept, r=0.5*powl(y_intercept,2);

            number_t final = p*powl(b.x,4)+q*powl(b.x,3)+r*powl(b.x,2);
            number_t initial = p*powl(a.x,4)+q*powl(a.x,3)+r*powl(a.x,2);

            below_sum+=final-initial;
            a=b;
        }

        return (above_sum+below_sum);
    }

    void sort_x() noexcept
    {
        std::sort(reinterpret_cast<point*>(vertices), reinterpret_cast<point*>(vertices)+(vertices_size()>>1), point_compare_x());
    }
    void sort_y() noexcept
    {
        std::sort(reinterpret_cast<point*>(vertices), reinterpret_cast<point*>(vertices)+(vertices_size()>>1), point_compare_y());
    }


#endif