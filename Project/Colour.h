#ifndef PROJECT_COLOUR_H
#define PROJECT_COLOUR_H


class Colour {

public:
    Colour(const char *colour, const int h_min, const int s_min, const int v_min, const int h_max, const int s_max, const int v_max) :
    name(colour), h_min(h_min), s_min(s_min), v_min(v_min), h_max(h_max), s_max(s_max), v_max(v_max){};

private:
    const char *name;
    const int h_min;
    const int h_max;
    const int s_min;
    const int s_max;
    const int v_min;
    const int v_max;
};


#endif //PROJECT_COLOUR_H
