#include <iostream>
#include <cmath>

using namespace std;

#include <Eigen/Core>
#include <Eigen/Geometry>

int main( int argc, char** argv){

    //Eigen/Geometry 模块提供了各种旋转和平移的表示

    //3D旋转矩阵直接使用Matrix3d或Matrix3f
    Eigen::Matrix3d rotation_matrix = Eigen::Matrix3d::Identity();
    //旋转向量使用AngleAxis，底层不直接是Matrix，运算可当做矩阵（重载了运算符）
    Eigen::AngleAxisd rotation_vector(M_PI/4, Eigen::Vector3d(0, 0, 1));//绕z轴旋转45度
    cout.precision(3);
    cout << "rotation matrix = \n" << rotation_vector.matrix() << endl;//用matrix()转换成矩阵
    rotation_matrix = rotation_vector.toRotationMatrix();//直接赋值
    
    Eigen::Vector3d v(1, 0, 0);
    //用AngleAxis进行坐标变换
    Eigen::Vector3d v_rotated = rotation_vector*v;
    cout << "(1,0,0) after rotation ="<< v_rotated.transpose() << endl;
    //或用旋转矩阵
    v_rotated = rotation_matrix*v;
    cout << "(1,0,0) after rotation ="<< v_rotated.transpose() << endl;

    //欧拉角
    Eigen::Vector3d euler_angles = rotation_matrix.eulerAngles(2,1,0);//ZYX顺序 yaw,pitch,roll
    cout << "yaw pitch roll = " << euler_angles.transpose() <<endl;

    //欧式变换矩阵
    Eigen::Isometry3d T = Eigen::Isometry3d::Identity();//4x4矩阵
    T.rotate(rotation_vector); //按照rotation_vector旋转
    T.pretranslate(Eigen::Vector3d(1,3,4));//把平移向量设成（1,3,4）
    cout << "Transform matrix = \n" << T.matrix() << endl;

    //用变换矩阵进行坐标 变换
    Eigen::Vector3d v_transformed = T*v;//相当于R*v+t
    cout << "v transformed = " << v_transformed.transpose() << endl;

    //四元数
    Eigen::Quaterniond q = Eigen::Quaterniond(rotation_vector);
    cout << "quaternion = \n" << q.coeffs() << endl;//coeff顺序(x,y,z,w),w为实部
    
    q = Eigen::Quaterniond(rotation_matrix);
    cout << "quaternion = \n" << q.coeffs() << endl;

    //使用四元数旋转一个向量，使用重载的乘法
    v_rotated = q*v;
    cout << "(1,0,0) after rotation =" << v_rotated.transpose() << endl;

    return 0;
}