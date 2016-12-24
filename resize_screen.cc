// From a coding test: rescale image dimensions to fit a screen while
// keeping the aspect ratio.
// I think my tested specified double pixels, which is odd in
// retrospect, but made the math trivial.  I've tried to make it a bit
// more realistic, with integral input and output, and making sure each
// dimension has at least one pixel.

#include <cstdio>
#include <cmath>

typedef int pixel;

pixel makepixel(double v) {
    pixel p(trunc(v));
    if (p<1) p=1;
    return p;
}

struct rect {
    pixel w;
    pixel h;
    rect(double _w, double _h) : w(makepixel(_w)), h(makepixel(_h)) {}
};

rect resize (const rect& image, const rect& screen) {
    double wr = 1.0* screen.w / image.w;
    double hr = 1.0* screen.h / image.h;
    if (wr < hr)
        return rect{ image.w * wr, image.h * wr};
    else
        return rect{ image.w * hr, image.h * hr};
}

void pr_rect (const rect &r) {
    printf("%d by %d\n",r.w, r.h);
}

int main() {
    rect screen{600,400};
    pr_rect(screen);
    pr_rect( resize(rect{300,200}, screen) );
    pr_rect( resize(rect{300,600}, screen) );
    pr_rect( resize(rect{800,200}, screen) );
    pr_rect( resize(rect{800,800}, screen) );
    pr_rect( resize(rect{100,200}, screen) );
    pr_rect( resize(rect{300,100}, screen) );
    pr_rect( resize(rect{1200,100}, screen) );
    pr_rect( resize(rect{601,401}, screen) );
    pr_rect( resize(rect{610,401}, screen) );
    pr_rect( resize(rect{1300,2}, screen) );
}
