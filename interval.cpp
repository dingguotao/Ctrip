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

//判断一个时间段是否跨了一天
bool is_diffDays(Interval interval)
{
	if (interval.end.hour < interval.start.hour)
		return true;
	else
		return false;
}

//判断同一天中mytime是否有与interval重合的部分
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

//判断mytime是否有和myinterval重合的部分，考虑了第一天和第二天的情形
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

//将每次比较的起始时间加0.1，这样可以区分出来刚好重合的时候
Time time_plus(Time mytime)
{
	return Time(mytime.hour, mytime.minute+0.1);
}

////将每次比较的结束时间减0.1，这样可以区分出来刚好重合的时候
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
			//如果begincount、endcount有比count大的，则更新count为最大值
			if ((begincount>endcount ? begincount : endcount) > count)
				count = (begincount>endcount ? begincount : endcount);
		}
		return count;
	}
}


void main()
{
	//三个测试用例
	Interval myinterval1[] = {Interval(Time(6,0), Time(8,0))};
	cout<<most_intervals_overlap_count(myinterval1,sizeof(myinterval1)/sizeof(myinterval1[0]))<<endl;
	Interval myinterval2[] = {Interval(Time(6,0), Time(8,0)), Interval(Time(7, 30), Time(9,0))};
	cout<<most_intervals_overlap_count(myinterval2,sizeof(myinterval2)/sizeof(myinterval2[0]))<<endl;
	Interval myinterval3[] = {Interval(Time(6,0), Time(8,0)), Interval(Time(8, 0), Time(9,0))};
	cout<<most_intervals_overlap_count(myinterval3,sizeof(myinterval3)/sizeof(myinterval3[0]))<<endl;
}