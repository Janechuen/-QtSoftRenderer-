#pragma once
#include <iostream>
#include <cassert>
#include <cmath>

//VECTOR 向量类
//定义向量模板
template<int n > struct vec {
	double data[n] = { 0 }; //初始化data数组 数据清零
	double& operator[](const int i) { assert(i >= 0 && i < n); return data[i]; }	  //设置数值
	double operator[](const int i) const { assert(i >= 0 && i < n); return data[i]; } //获取数值
	double norm2() const { return *this * *this; }//向量的平方
	double norm()  const { return std::sqrt(norm2()); }//模長  向量的平方開方
};

//向量的加减乘除
template<int n> double operator*(const vec<n>& j, const vec<n>& k)//向量 向量乘法(Dot Projected)
{
	double temp = 0;
	for (int i = n; i--; temp += j[i] * k[i]);
	return temp;
}

template<int n> vec<n> operator+(const vec<n>& j, const vec<n>& k)//向量 向量加法
{
	vec<n> temp = j;
	for (int i = n; i--; temp[i] += k[i]);
	return temp;
}

template<int n> vec<n> operator-(const vec<n>& j, const vec<n>& k)//向量 向量減法
{
	vec<n> temp = j;
	for (int i = n; i--; temp[i] -= k[i]);
	return temp;
}

template<int n> vec<n> operator*(const vec<n>& lhs, const double& rhs) //向量 單位乘法
{
	vec<n> ret = lhs;
	for (int i = n; i--; ret[i] *= rhs);
	return ret;
}

template<int n> vec<n> operator/(const vec<n>& j, const double& k)//向量 單位除法
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


template<>struct vec<2>//特化结构体 二维向量
{
	double x = 0, y = 0;//设置三维向量分量 x y 
	double& operator[](const int i) { assert(i >= 0 && i < 2); return i ? y : x; };
	double  operator[](const int i)  const { assert(i >= 0 && i < 2); return i ? y : x; };
	double norm2() const { return *this * *this; }//向量的平方
	double norm()  const { return std::sqrt(norm2()); }//模長  向量的平方開方
	vec<2> normalized() { return (*this) / norm(); }//標準化向量 向量/模長
};

template<>struct vec<3>//特化结构体 三维向量
{
	double x = 0, y = 0, z = 0;//设置三维向量分量 x y z
	double& operator[](const int i) { assert(i >= 0 && i < 3); return i ? (1 == i ? y : z) : x; };
	double  operator[](const int i)  const { assert(i >= 0 && i < 3); return i ? (1 == i ? y : z) : x; };
	double norm2() const { return *this * *this; }//向量的平方
	double norm()  const { return std::sqrt(norm2()); }//模長  向量的平方開方
	vec<3> normalized() { return (*this) / norm(); }//標準化向量 向量/模長
};

template<>struct vec<4>//特化结构体 三维向量
{
	double x = 0, y = 0, z = 0, w = 0;//设置三维向量分量 x y z
	double& operator[](const int i) { assert(i >= 0 && i < 4); return i == 0 ? x : (i == 1 ? y : (i == 2 ? z : w)); };
	double  operator[](const int i)  const { assert(i >= 0 && i < 4); return i == 0 ? x : (i == 1 ? y : (i == 2 ? z : w)); };
	double norm2() const { return *this * *this; }//向量的平方
	double norm()  const { return std::sqrt(norm2()); }//模長  向量的平方開方
	vec<4> normalized() { return (*this) / norm(); }//標準化向量 向量/模長
};

//定义 向量格式
typedef vec<1> vec1;
typedef vec<2> vec2;
typedef vec<3> vec3;
typedef vec<4> vec4;

//二维向量叉积 cpp 实现
double cross_2(const vec2& A, const vec2& B);
//三维向量叉积 cpp 实现
vec3 cross(const vec3& A, const vec3& B);