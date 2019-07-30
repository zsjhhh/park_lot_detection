#include <iostream>
#include <ctime>
using namespace std;

#include <Eigen/Core>
#include <Eigen/Dense>

#define MATRIX_SIZE 50

int main(int argc, char *argv[])
{
    //声明一个2x3的float矩阵，前三个参数：数据类型，行，列
    Eigen::Matrix<float, 2, 3> matrix_23;

    Eigen::Vector3d v_3d;//实质为 Eigen::Matrix<double, 3, 1>

    Eigen::Matrix3d matrix_33 =  Eigen::Matrix3d::Zero();//初始化为零 实质为 Eigen::Matrix<double, 3, 3>

    //不确定矩阵大小，用动态大小的矩阵
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> matrix_dynamic;

    Eigen::MatrixXd matrix_x;

    //输入数据
    matrix_23 << 1, 2, 3, 4, 5, 6;
    //输出
    cout << matrix_23 << endl;

    //用（）访问矩阵中的元素
    for(int i=0;i<2; i++)
        for(int j=0;j<3;j++)
        cout<<matrix_23(i,j)<<endl;

    v_3d << 3, 2, 1;
    //矩阵和向量相乘，数据类型不同需要显示转换
    Eigen::Matrix<double, 2, 1> result = matrix_23.cast<double>()*v_3d;
    cout << result << endl;

    //矩阵运算
    matrix_33 = Eigen::Matrix3d::Random();
    cout << matrix_33 << endl <<endl;

    cout << matrix_33.transpose() << endl;//转置
    cout << matrix_33.sum() << endl;//求和
    cout << matrix_33.trace() << endl;//迹
    cout << 10*matrix_33 << endl;//数乘
    cout << matrix_33.inverse() << endl;//逆
    cout << matrix_33.determinant() << endl;//行列式

    //特征值
    //实对称矩阵可以保证对角化成功
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigen_solver(matrix_33.transpose()*matrix_33);
    cout << "Eigen values = " << eigen_solver.eigenvalues() << endl;
    cout << "Eigen vectors = " << eigen_solver.eigenvectors() << endl;

    //解方程
    Eigen::Matrix<double, MATRIX_SIZE, MATRIX_SIZE> matrix_NN;
    matrix_NN = Eigen::MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);
    Eigen::Matrix<double, MATRIX_SIZE, 1> v_Nd;
    v_Nd = Eigen::MatrixXd::Random(MATRIX_SIZE, 1);

    clock_t time_stt = clock();//计时
    
    //直接求逆
    Eigen::Matrix<double, MATRIX_SIZE, 1> x = matrix_NN.inverse()*v_Nd;
    // cout << "inverse:x = " << x << endl;
    cout << "time use in normal inverse is " << 1000*(clock()-time_stt)/(double)CLOCKS_PER_SEC << "ms" <<endl;

    //矩阵分解，如QR分解
    time_stt = clock();
    x = matrix_NN.colPivHouseholderQr().solve(v_Nd);
    // cout << "Qr composition:x = " << x << endl;
    cout << "time use in Qr composition is " <<1000*(clock()-time_stt)/(double)CLOCKS_PER_SEC<<"ms"<< endl;

    return 0;
}