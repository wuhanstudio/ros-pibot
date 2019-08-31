class MotorControl {
  public:
    //Var
    int maxSpd = 255;
    float moveFactor = 1.0;
    float turnFactor = 3.0;

    MotorControl(int fl_for, int fl_back,
                           int fr_for, int fr_back,
                           int bl_for, int bl_back,
                           int br_for, int br_back);
    void initMotors();
    void rotateBot(bool dir, float spd);
    void moveBot(float spd, float bias);
    void stopMotors();
  private:
    //The pins
    int fl_for;
    int fl_back;
    int fr_for;
    int fr_back;
    int bl_for;
    int bl_back;
    int br_for;
    int br_back;
};
