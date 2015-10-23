#include <iostream>
using namespace std;

class Time
{
public:
	Time(int hour = 0, float minute = 0)
	{
		this->hour = hour;
		this->minute = minute;
	}
public:
	int hour;
	float minute;
};

class Interval
{
public:
	Interval(Time start, Time end)
	{
		this->start = start;
		this->end = end;
	}

public:
	Time start;
	Time end;
};

//�ж�һ��ʱ����Ƿ����һ��
bool is_diffDays(Interval interval)
{
	if (interval.end.hour < interval.start.hour)
		return true;
	else
		return false;
}

//�ж�ͬһ����mytime�Ƿ�����interval�غϵĲ���
bool is_in_intervals_simple(Time mytime, Interval myinterval)
{
	if (mytime.hour > myinterval.start.hour && mytime.hour < myinterval.end.hour )
		return true;
	else if (mytime.hour == myinterval.start.hour && mytime.minute > myinterval.start.minute )
		return true;
	else if (mytime.hour == myinterval.start.hour && mytime.minute < myinterval.end.minute)
		return true;
	else
		return false;

}

//�ж�mytime�Ƿ��к�myinterval�غϵĲ��֣������˵�һ��͵ڶ��������
bool is_in_intervals(Time mytime, Interval myinterval)
{
	if (is_diffDays(myinterval))
	{
		if (mytime.hour == 0 && mytime.minute == 0)
			return true;
		else if (mytime.hour == 24 && mytime.minute == 0)
			return true;
		else if ((is_in_intervals_simple(mytime,Interval(myinterval.start,Time(24,0))) || (is_in_intervals_simple(mytime,Interval(Time(0,0),myinterval.end)))))
			return true;
		else
			return false;
	}
	else
		return is_in_intervals_simple(mytime, myinterval);
}

//��ÿ�αȽϵ���ʼʱ���0.1�������������ֳ����պ��غϵ�ʱ��
Time time_plus(Time mytime)
{
	return Time(mytime.hour, mytime.minute+0.1);
}

////��ÿ�αȽϵĽ���ʱ���0.1�������������ֳ����պ��غϵ�ʱ��
Time time_minus(Time mytime)
{
	if ((int)(mytime.minute) == 0)
		return Time(mytime.hour-1,59.9);
	else
		return Time(mytime.hour, mytime.minute-0.1);
}

int most_intervals_overlap_count(Interval my_interval[],int length)
{
	int i, j;
	int count = 0;
	int begincount ;
	int endcount ;
	if (length ==0 || length == 1)
		return 1;
	for (i = 0; i<length; i++)
	{
		Time newtime1 =time_plus( my_interval[i].start);
		Time newtime2 =time_minus(my_interval[i].end);
		begincount = 0;
		endcount = 0;
		for (j = 0; j< length; j++)
		{
			if (is_in_intervals(newtime1,my_interval[j]))
				begincount++;
			if (is_in_intervals(newtime2,my_interval[j]))
				endcount++;
			//���begincount��endcount�б�count��ģ������countΪ���ֵ
			if ((begincount>endcount ? begincount : endcount) > count)
				count = (begincount>endcount ? begincount : endcount);
		}
		return count;
	}
}


void main()
{
	//������������
	Interval myinterval1[] = {Interval(Time(6,0), Time(8,0))};
	cout<<most_intervals_overlap_count(myinterval1,sizeof(myinterval1)/sizeof(myinterval1[0]))<<endl;
	Interval myinterval2[] = {Interval(Time(6,0), Time(8,0)), Interval(Time(7, 30), Time(9,0))};
	cout<<most_intervals_overlap_count(myinterval2,sizeof(myinterval2)/sizeof(myinterval2[0]))<<endl;
	Interval myinterval3[] = {Interval(Time(6,0), Time(8,0)), Interval(Time(8, 0), Time(9,0))};
	cout<<most_intervals_overlap_count(myinterval3,sizeof(myinterval3)/sizeof(myinterval3[0]))<<endl;
}