#!/usr/bin/env python

class Time(object):
    def __init__(self, hour, minute):
        '''Simple time wrapper.

        :param hour: Integer, from 0 to 24.
        :param minute: Integer, from 0 to 59.
        '''

        self.hour = hour
        self.minute = minute

class Interval(object):
    def __init__(self, start, end):
        '''Interval represents a task on schedule. 

        :param start: Time, when the task starts.
        :param end: Time, when the task ends.

        TODO: add support for passing timestap strings.For example,
              Interval('00:00', '02:39').
        TODO: make Interval objects more readable in a python shell.e.g.,

            #  >>> Interval(Time(0,0), Time(2,30))
              Interval(00:00 -> 02:30)
        '''
        self.start = start
        self.end = end 
def is_diffDays(interval):
    if interval.end.hour < interval.start.hour :
        return True
    else:
        return False
		
def is_in_intervals_simple(time,interval):
    if time.hour>interval.start.hour and time.hour<interval.end.hour :
        return True
    if time.hour == interval.start.hour and time.minute > interval.start.minute:
        return True
    if time.hour == interval.end.hour and time.minute < interval.end.minute:
        return True
    return False
	
def is_in_intervals(time,interval):
    if is_diffDays(interval):
        if time.hour == 0 and time.minute== 0:
            return True
        if time.hour == 24 and time.minute== 0:
            return True
        if is_in_intervals_simple(time, Interval(Time(interval.start.hour, interval.start.minute), Time(24,0))) or is_in_intervals_simple(time,Interval(Time(0,0),Time(interval.end.hour, interval.end.minute))):
            return True
    else:
        return is_in_intervals_simple(time,interval)
    return False;


def time_plus(time):
    return Time(time.hour,time.minute+0.1)

def time_minus(time):
    if time.minute == 0 :
        return Time(time.hour-1,59.9)
    return Time(time.hour,time.minute-0.1)   
   
def most_intervals_overlap_count(intervals):
    '''count the maximum overlappes in a schedule.

    tasks on the schedule may overlaps.For example, task A was scheduled
    from 06:00 to 08:00, and task B was scheduled from 07:30 to 09:00, then
    A and B overlap in 07:30-08:00.

    mutiple tasks may overlap on the same time interval, you job is to find
    out the number of tasks when maximum overlap happens.

    :param intervals: list of Interval

    >>> most_intervals_overlap_count([Interval(Time(6,0), Time(8,0))])
    1
    >>> most_intervals_overlap_count([Interval(Time(6,0), Time(8,0)), Interval(Time(7, 30), Time(9,0))])
    2
    >>> most_intervals_overlap_count([Interval(Time(6,0), Time(8,0)), Interval(Time(8, 0), Time(9,0))])
    1
    '''
    # TODO: implement this function
    count = 0
    length = len(intervals)
    if length==0 or length==1:
        return 1
    for i in range(length):
        newtime1=time_plus(intervals[i].start)
        newtime2=time_minus(intervals[i].end)
        currentcount1=0
        currentcount2=0
        for j in range(length):
            if is_in_intervals(newtime1,intervals[j]):
                currentcount1=currentcount1+1
            if is_in_intervals(newtime2,intervals[j]):
                currentcount2=currentcount2+1
        if max(currentcount1,currentcount2)>count:
            count = max(currentcount1,currentcount2)
    return count

	
print most_intervals_overlap_count([Interval(Time(6,0), Time(8,0))])
print most_intervals_overlap_count([Interval(Time(6,0), Time(8,0)), Interval(Time(7, 30), Time(9,0))])
print most_intervals_overlap_count([Interval(Time(6,0), Time(8,0)), Interval(Time(8, 0), Time(9,0))])
