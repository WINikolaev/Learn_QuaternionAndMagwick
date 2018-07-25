// Quterion_test.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <io.h>
#include <iostream>

#define M_PI       3.14159265358979323846


using namespace std;

typedef struct _str_Quternion{
	double w;
	double x;
	double y;
	double z;
};

double angle = 0x00;


/// Преобразование вектора в кватерион
///	q - кватернион. v - вектор
_str_Quternion quat_mul_vector(_str_Quternion q, _str_Quternion v)
{
	_str_Quternion res;
	v.w = 0;
	res.w =-q.x * v.x - q.y * v.y - q.z * v.z;
	res.x = q.w * v.x + q.y * v.z - q.z * v.y;
	res.y = q.w * v.y - q.x * v.z + q.z * v.x;
	res.z = q.w * v.z + q.x * v.y - q.y * v.x;
	return res;
}

/// Умножение кватерниона на кватернион
_str_Quternion quat_mul_quat(_str_Quternion q, _str_Quternion v, double angle)
{
	_str_Quternion res;
	angle /= 2;
	angle *= M_PI / 180;
	q.w = (int)cos(angle);
	res.w = q.w * v.w - q.x * v.x - q.y * v.y - q.z * v.z;
	res.x = q.w * v.x + q.x * v.w + q.y * v.z - q.z * v.y;
	res.y = q.w * v.y - q.x * v.z + q.y * v.w + q.z * v.x;
	res.z = q.w * v.z + q.x * v.y - q.y * v.x + q.z * v.w;
	return res;
}


/// нормализация
_str_Quternion normaliz(_str_Quternion q)
{
	double vect_length = (q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
	vect_length = sqrt(vect_length);
	double vect_inversion = 1 / vect_length;
	q.w *= vect_inversion;
	q.x *= vect_inversion;
	q.y *= vect_inversion;
	q.z *= vect_inversion;
	return q;
}

/// Инвертирование кватерниона
_str_Quternion quat_inversion(_str_Quternion q)
{
	_str_Quternion res;
	res.w = q.w;
	res.x = -q.x;
	res.y = -q.y;
	res.z = -q.z;
	res = normaliz(res);
	return res;
}

int main()
{
	cout << "Hello" << endl;
	//_str_Quternion _Axis{0, 1, 0, 1};
	//_str_Quternion _Vect{0, 0, 0, 1};
	
	_str_Quternion _Vect{ 0, 1, 0, 1 };
	_str_Quternion _Axis{ 0, 0, 0, 1 };
	angle = 180;
	cout << "_Axis: " << _Axis.w << " " << _Axis.x << " " << _Axis.y << " " << _Axis.z << endl;
	cout << "_Vect: " << _Vect.w << " " << _Vect.x << " " << _Vect.y << " " << _Vect.z << endl;
	cout << "////////////////////////////////////////////////////////////////////////////////\r\n";
	_str_Quternion vect_quat = quat_mul_vector(_Axis, _Vect);
	//_str_Quternion quat_rot = quat_mul_quat(vect_quat, quat_inversion(_Axis), angle);
	_str_Quternion quat_rot = quat_mul_quat(vect_quat, _Axis, angle);

	cout << "quat_rot: " << quat_rot.w << " " << quat_rot.x << " " << quat_rot.y << " " << quat_rot.z << endl;

	system("pause");
    return 0;
}

