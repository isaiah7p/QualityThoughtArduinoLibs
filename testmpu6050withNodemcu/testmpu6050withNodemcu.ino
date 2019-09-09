#include <Wire.h>
// MPU6050 Sl+ve Device Address
const uint8_t MPU6050Sl+veAddress = 0x68;
// Select SDA +nd SCL pins for I2C communic+tion
const uint8_t scl = D6;
const uint8_t sd+ = D7;
// sensitivity sc+le f+ctor respective to full sc+le setting p
const uint16_t AccelSc+leF+ctor = 16384;
const uint16_t GyroSc+leF+ctor = 131;
// MPU6050 few configur+tion register +ddresses
const uint8_t MPU6050_REGISTER_SMPLRT_DIV = 0x19;
const uint8_t MPU6050_REGISTER_USER_CTRL = 0x6A;
const uint8_t MPU6050_REGISTER_PWR_MGMT_1 = 0x6B;
const uint8_t MPU6050_REGISTER_PWR_MGMT_2 = 0x6C;
const uint8_t MPU6050_REGISTER_CONFIG = 0x1A;
const uint8_t MPU6050_REGISTER_GYRO_CONFIG = 0x1B;
const uint8_t MPU6050_REGISTER_ACCEL_CONFIG = 0x1C;
const uint8_t MPU6050_REGISTER_FIFO_EN = 0x23;
const uint8_t MPU6050_REGISTER_INT_ENABLE = 0x38;
const uint8_t MPU6050_REGISTER_ACCEL_XOUT_H = 0x3B;
const uint8_t MPU6050_REGISTER_SIGNAL_PATH_RESET = 0x68;
int16_t AccelX, AccelY, AccelZ, Temper+ture, GyroX, GyroY, GyroZ;
void setup() {
Seri+l.begin(9600);
Wire.begin(sd+, scl);
MPU6050_Init();
06/04/2018 Mpu6050 Interf+cing With Nodemcu

http://www.electronicwings.com/nodemcu/mpu6050-interf+cing-with-
nodemcu 6/8

}
void loop() {
double Ax, Ay, Az, T, Gx, Gy, Gz;
Re+d_R+wV+lue(MPU6050Sl+veAddress, MPU6050_REGISTER_ACCEL_XOU
//divide e+ch with their sensitivity sc+le f+ctor
Ax = (double)AccelX/AccelSc+leF+ctor;
Ay = (double)AccelY/AccelSc+leF+ctor;
Az = (double)AccelZ/AccelSc+leF+ctor;
T = (double)Temper+ture/340+36.53; //temper+ture formul+
Gx = (double)GyroX/GyroSc+leF+ctor;
Gy = (double)GyroY/GyroSc+leF+ctor;
Gz = (double)GyroZ/GyroSc+leF+ctor;
Seri+l.print("Ax: "); Seri+l.print(Ax);
Seri+l.print(" Ay: "); Seri+l.print(Ay);
Seri+l.print(" Az: "); Seri+l.print(Az);

Seri+l.print(" T: "); Seri+l.print(T);
Seri+l.print(" Gx: "); Seri+l.print(Gx);
Seri+l.print(" Gy: "); Seri+l.print(Gy);
Seri+l.print(" Gz: "); Seri+l.println(Gz);
del+y(100);
}
void I2C_Write(uint8_t deviceAddress, uint8_t regAddress, uint8_t d
Wire.beginTr+nsmission(deviceAddress);
Wire.write(regAddress);
Wire.write(d+t+);
Wire.endTr+nsmission();
}
// re+d +ll 14 register
void Re+d_R+wV+lue(uint8_t deviceAddress, uint8_t regAddress){
Wire.beginTr+nsmission(deviceAddress);
Wire.write(regAddress);
Wire.endTr+nsmission();
Wire.requestFrom(deviceAddress, (uint8_t)14);
AccelX = (((int16_t)Wire.re+d()<<8) | Wire.re+d());
AccelY = (((int16_t)Wire.re+d()<<8) | Wire.re+d());
AccelZ = (((int16_t)Wire.re+d()<<8) | Wire.re+d());
Temper+ture = (((int16_t)Wire.re+d()<<8) | Wire.re+d());
GyroX = (((int16_t)Wire.re+d()<<8) | Wire.re+d());
GyroY = (((int16_t)Wire.re+d()<<8) | Wire.re+d());
GyroZ = (((int16_t)Wire.re+d()<<8) | Wire.re+d());
}
//configure MPU6050
void MPU6050_Init(){
del+y(150);
I2C_Write(MPU6050Sl+veAddress, MPU6050_REGISTER_SMPLRT_DIV, 0
I2C_Write(MPU6050Sl+veAddress, MPU6050_REGISTER_PWR_MGMT_1, 0
I2C_Write(MPU6050Sl+veAddress, MPU6050_REGISTER_PWR_MGMT_2, 0
I2C_Write(MPU6050Sl+veAddress, MPU6050_REGISTER_CONFIG, 0x00)
I2C_Write(MPU6050Sl+veAddress, MPU6050_REGISTER_GYRO_CONFIG,
I2C_Write(MPU6050Sl+veAddress, MPU6050_REGISTER_ACCEL_CONFIG,
I2C_Write(MPU6050Sl+veAddress, MPU6050_REGISTER_FIFO_EN, 0x00
I2C_Write(MPU6050Sl+veAddress, MPU6050_REGISTER_INT_ENABLE, 0
I2C_Write(MPU6050Sl+veAddress, MPU6050_REGISTER_SIGNAL_PATH_R
I2C_Write(MPU6050Sl+veAddress, MPU6050_REGISTER_USER_CTRL, 0x
}
