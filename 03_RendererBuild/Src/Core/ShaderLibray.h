#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
//#include <string>
//#include <sstream>
//#include <iomanip>
#include <chrono>
#include "Core.h"

//std::string GetTimeStr()
//{
//	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
//	time_t tt = std::chrono::system_clock::to_time_t(now);
//	struct tm ltm = { 0 };
//	localtime_s(&ltm, &tt); 
//	std::stringstream stm;
//	stm << std::setfill('0');
//	stm << std::setw(4) << (ltm.tm_year + 1900) << "-";
//	stm << std::setw(2) << (ltm.tm_mon + 1) << "-";
//	stm << std::setw(2) << (ltm.tm_mday) << " ";
//	stm << std::setw(2) << (ltm.tm_hour) << "-";
//	stm << std::setw(2) << (ltm.tm_min) << "-";
//	stm << std::setw(2) << (ltm.tm_sec);
//
//	return stm.str();
//}
// 
 
 
//double* GameTime;
double FF_time()
{
	// ��ȡ��ǰʱ�������
	auto now = std::chrono::system_clock::now();
	auto seconds = std::chrono::time_point_cast<std::chrono::seconds>(now).time_since_epoch().count();
	// ������ת��Ϊdouble����
	double seconds_double = static_cast<double>(seconds);
	// ������
	//std::cout << "Current time in seconds: " << seconds << std::endl;
	//std::cout << "Current time in seconds as double: " << seconds_double << std::endl;
	return seconds_double;

}
//����С��0�ı���
vec4 C_MAX(vec4 in,double f)
{
	vec4 out;
	for (int i=0; i<4;i++)
	{
		if (in[i] <0)
		{
			out[i] = 0;
		}
		else
		{
			out[i] = in[i];
		}
		
	}
	return out;
}
double C_MAX(double in, double f)
{
	double out;
	
		if (in < 0)
		{
			out = 0;
		}
		else
		{
			out = in;
		}
	return out;
}
//�����˷�
template<int n> vec<n> C_Mul(const vec<n>& j, const vec<n>& k)
{
	vec<n> ret = j;
	for (int i = n; i--; ret[i] *= k[i]);
	return ret;
}

//��� ������������ļн�
template<int n> double dot(const vec<n>& j, const vec<n>& k)//���� �����˷�(Dot Projected)
{
	double temp = 0;
	for (int i = n; i--; temp += j[i] * k[i]);
	return temp;
}
