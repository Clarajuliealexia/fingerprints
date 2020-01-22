#include "pressure.h"


void cartesian_to_polar(cv::Point origin, cv::Point pt, float &r, float &theta)
{
    r = sqrt(pow(pt.x, 2) + pow(pt.y, 2));
    cv::Point diff = pt - origin;

    if (diff.x > 0) {
        if (diff.y >= 0) theta = atan((float) pt.y / pt.x);
        else theta = atan((float) pt.y / pt.x) + 2 * PI;
    } else if (diff.x == 0) {
        if (diff.y > 0) theta = PI / 2;
        else theta = 3 * PI / 2;
    } else {
        theta = atan((float) pt.y / pt.x) + PI;
    }
}

 
/*
 * Réfléchir à comment inclure un angle dans la définition
 * et choisir de l'appliquer seulement aux pixels dans une direction
 * donnée, et utiliser un tirage aléatoire de points dépendant du
 * tirage précédent 
 */
float c_isotropic(float r, float param, int func)
{
    switch (func) {
        case 0:
            return 1 - exp(- 1 / (param * pow(r, 2)));
        case 1:
            return exp(- param * r);
        case 2:
            return 1 / (1 + param * r);
        default:
            return 1 - exp(- 1 / (param* pow(r, 2)));;
    }
}


float c_anisotropic(int x, int y, cv::Point center, float param_x, 
                    float param_y, float param)
{
    return 1-exp(-param/pow(param_x*pow(x-center.x, 2) + param_y*pow(y-center.y, 2), 8));
}


float c_anisotropic_polar(float r, float theta, cv::Point center,
                          float param_x, float param_y, float param)
{
    return 1-exp(-param/pow(param_x*pow(r * cos(theta), 2) + param_y*pow(r * sin(theta), 2), 8));
}


std::vector<float> coeffs(cv::Point center, std::vector<cv::Point> coords,
                          float param_x, float param_y, float param, bool iso)
{
    std::vector<float> res;
    int size = coords.size();
    float dist;

    if (iso) {
        for (int i = 0; i < size; i++) {
            dist = cv::norm(center - coords[i]);
	        res.push_back(c_isotropic(dist, param));
        }
    } else {
        // float r, theta;
        for (int i = 0; i < size; i++) {
            res.push_back(c_anisotropic(coords[i].x, coords[i].y, center, param_x, param_y, param));
            // cartesian_to_polar(center, coords[i], r, theta);
            // res.push_back(c_anisotropic_polar(r, theta, center, param_x, param_y, param));
        }
    }

    return res;
}


std::vector<float> linspace(float begin, float end, int N, bool endpoint)
{
    std::vector<float> res;
    int total_it = N;

    if (endpoint) total_it++;

    for (int i = 0; i < total_it; i++)
        res.push_back((i * (end - begin) + begin)/N);

    return res;
}


std::vector<cv::Point> points_ellipse(cv::Point center, float a, float b)
{
    std::vector<cv::Point> res;
    std::vector<float> lin = linspace(0, 2*PI, 10000);

    for (std::vector<float>::iterator i = lin.begin(); i != lin.end(); i++)
        res.push_back(cv::Point(int(center.x + a * cos(*i)), int(center.y + b * sin(*i))));

    return res;
}
