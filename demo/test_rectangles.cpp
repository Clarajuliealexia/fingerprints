/**
 * \file test_rectangles.cpp
 * \brief Test for the pixel color transformation : rectangle
 * \author Clara.B
 * \version 0.1
 * \date 01/12/20
 */


#include "image.h"

/**
 * \fn int main()
 * \brief Test of the rectangle function
 */
int main()
{
    cv::String s1( "../img/clean_finger.png" );
    Image finger(s1);

    finger.display("Clean finger");

    Image res = finger.Rectangle(180,150,70,30,0);
    res = res.Rectangle(50, 100, 60, 100, 1);
    res.display("Black and white rectangles");

    res.save("rectangles");

    return 0;
}
