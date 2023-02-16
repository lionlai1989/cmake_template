class SemicircleRuler {
private:
    double length;
    double radius;

public:
    SemicircleRuler(double length, double radius);
    virtual void measure_length();
    virtual void measure_angle();
};
