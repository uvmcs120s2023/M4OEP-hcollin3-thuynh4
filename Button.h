#ifndef GRAPHICS_STARTER_BUTTON_H
#define GRAPHICS_STARTER_BUTTON_H

#include "Quad.h"
#include <string>

using namespace std;

class Button : public Quad {
private:
    int index;
    color originalFill, hoverFill, pressFill, offFill;
public:
    Button(color fill, point center, unsigned int width, unsigned int height, int index);
    /* Uses OpenGL to draw the box with the label on top */
    virtual void draw() const override;

    /* Returns true if the coordinate is inside the box */
    bool isOverlapping(int x, int y) const;

    /* Change color of the Button when the user is hovering over it */
    void hover();

    /* Change color of the Button when the user is clicking on it */
    void pressDown();

    /* Change the color back when the user is not clicking/hovering */
    void release();

    void setIndex(int i);

    int getIndex();

    void setOriginalFill(color fill);
};


#endif //GRAPHICS_STARTER_BUTTON_H
