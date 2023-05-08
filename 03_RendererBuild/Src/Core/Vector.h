#pragma once
#include <iostream>
#include <cassert>
#include <cmath>

//VECTOR ������
//��������ģ��
template<int n > struct vec {
	double data[n] = { 0 }; //��ʼ��data���� ��������
	double& operator[](const int i) { assert(i >= 0 && i < n); return data[i]; }	  //������ֵ
	double operator[](const int i) const { assert(i >= 0 && i < n); return data[i]; } //��ȡ��ֵ
	double norm2() const { return *this * *this; }//������ƽ��
	double norm()  const { return std::sqrt(norm2()); }//ģ�L  ������ƽ���_��
};

//�����ļӼ��˳�
template<int n> double operator*(const vec<n>& j, const vec<n>& k)//���� �����˷�(Dot Projected)
{
	double temp = 0;
	for (int i = n; i--; temp += j[i] * k[i]);
	return temp;
}

template<int n> vec<n> operator+(const vec<n>& j, const vec<n>& k)//���� �����ӷ�
{
	vec<n> temp = j;
	for (int i = n; i--; temp[i] += k[i]);
	return temp;
}

template<int n> vec<n> operator-(const vec<n>& j, const vec<n>& k)//���� �����p��
{
	vec<n> temp = j;
	for (int i = n; i--; temp[i] -= k[i]);
	return temp;
}

template<int n> vec<n> operator*(const vec<n>& lhs, const double& rhs) //���� ��λ�˷�
{
	vec<n> ret = lhs;
	for (int i = n; i--; ret[i] *= rhs);
	return ret;
}

template<int n> vec<n> operator/(const vec<n>& j, const double& k)//���� ��λ����
{
	vec<n> temp = j;
	for (int i = n; i--; temp[i] /= k);
	return temp;
}

template<int n1, int n2> vec<n1> proj(const vec<n2>& v) {
	vec<n1> ret;
	for (int i = n1; i--; ret[i] = v[i]);
	return ret;
}


template<>struct vec<2>//�ػ��ṹ�� ��ά����
{
	double x = 0, y = 0;//������ά�������� x y 
	double& operator[](const int i) { assert(i >= 0 && i < 2); return i ? y : x; };
	double  operator[](const int i)  const { assert(i >= 0 && i < 2); return i ? y : x; };
	double norm2() const { return *this * *this; }//������ƽ��
	double norm()  const { return std::sqrt(norm2()); }//ģ�L  ������ƽ���_��
	vec<2> normalized() { return (*this) / norm(); }//�˜ʻ����� ����/ģ�L
};

template<>struct vec<3>//�ػ��ṹ�� ��ά����
{
	double x = 0, y = 0, z = 0;//������ά�������� x y z
	double& operator[](const int i) { assert(i >= 0 && i < 3); return i ? (1 == i ? y : z) : x; };
	double  operator[](const int i)  const { assert(i >= 0 && i < 3); return i ? (1 == i ? y : z) : x; };
	double norm2() const { return *this * *this; }//������ƽ��
	double norm()  const { return std::sqrt(norm2()); }//ģ�L  ������ƽ���_��
	vec<3> normalized() { return (*this) / norm(); }//�˜ʻ����� ����/ģ�L
};

template<>struct vec<4>//�ػ��ṹ�� ��ά����
{
	double x = 0, y = 0, z = 0, w = 0;//������ά�������� x y z
	double& operator[](const int i) { assert(i >= 0 && i < 4); return i == 0 ? x : (i == 1 ? y : (i == 2 ? z : w)); };
	double  operator[](const int i)  const { assert(i >= 0 && i < 4); return i == 0 ? x : (i == 1 ? y : (i == 2 ? z : w)); };
	double norm2() const { return *this * *this; }//������ƽ��
	double norm()  const { return std::sqrt(norm2()); }//ģ�L  ������ƽ���_��
	vec<4> normalized() { return (*this) / norm(); }//�˜ʻ����� ����/ģ�L
};

//���� ������ʽ
typedef vec<1> vec1;
typedef vec<2> vec2;
typedef vec<3> vec3;
typedef vec<4> vec4;

//��ά������� cpp ʵ��
double cross_2(const vec2& A, const vec2& B);
//��ά������� cpp ʵ��
vec3 cross(const vec3& A, const vec3& B);