/**
 * \file test_symmetries.cpp
 * \brief Test of the symmetries
 * \author Thomas.B Carole.B
 * \version 0.1
 * \date 01/12/20
 */


#include "image.h"


/**
 * \fn int main()
 * \brief Test of the symmetries functions
 * The function tests the 3 different symmetries
 */
int main()
{
    cv::String s1( "../img/clean_finger.png" );
    Image img(s1);
    img.display("Finger");

    Image img2 = img.sym_y();
    img2.display("Symmetry along y");
    img2.save("symmetry_y");

    Image img3 = img.sym_x();
    img3.display("Symmetry along x");
    img3.save("symmetry_x");

    Image img4 = img.sym_xy();
    img4.display("Symmetry along the diagonal");
    img4.save("symmetry_xy");

    return 0;
}
