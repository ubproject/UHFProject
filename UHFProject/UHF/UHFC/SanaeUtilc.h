﻿/*
 ============================================================================
 Name        : UHFC-Util-C
 Author      : Sanae
 Version     : 1.0.3(Beta)
 Copyright   : CopyRight 2022 SanaeProject.
 ============================================================================
 */

#ifndef UHFC_SANAEUTILC_H_
#define UHFC_SANAEUTILC_H_


/*INCLUDE*/
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "SanaeTypes.h"


/*Define Function*/
time_t get_second (time_t _time);
time_t get_minutes(time_t _time);
time_t get_hour   (time_t _time);
time_t get_day    (time_t _time);
time_t get_year   (time_t _time);

void   StopWatch_Start       (StopWatch* _data);
time_t StopWatch_Finish      (StopWatch* _data);
time_t StopWatch_elapsed_time(StopWatch* _data);


/*Functions*/
/*現在何秒かを取得します。
 * 現在の秒数を取得したい場合、第一引数にはNOWを入れてください。
*/
time_t get_second(time_t _time){
	if(_time == NOW)
		_time = time(NULL);

	_time %= MIN;

	return _time;
}

/*現在何分かを取得します。
 * 現在の分数を取得したい場合、第一引数にはNOWを入れてください。
*/
time_t get_minutes(time_t _time){
	if(_time == NOW)
		_time = time(NULL);

	_time %= HOUR;
	_time /= MIN;

	return _time;
}

/*現在何時かを取得します。
 * 現在の時間数を取得したい場合、第一引数にはNOWを入れてください。
*/
time_t get_hour(time_t _time){
	if(_time == NOW)
		_time = time(NULL);

	_time %= DAY;
	_time /= HOUR;
	_time += GMT;

	return _time;
}

/*現在1月1日から何日目かを取得します。
 * 現在の日数を取得したい場合、第一引数にはNOWを入れてください。
*/
time_t get_day(time_t _time){
	if(_time == NOW)
		_time = time(NULL);

	_time -= DAY*12;
	_time %= YEAR;
	_time /= DAY;

	return _time;
}

/*現在何年かを取得します。
 * 現在の年数を取得したい場合、第一引数にはNOWを入れてください。
*/
time_t get_year(time_t _time){
	if(_time == NOW)
		_time = time(NULL);

	_time /= YEAR;
	_time += 1970;

	return _time;
}

/*ストップウォッチ*/
void StopWatch_Start(StopWatch* _data){
	_data->_start = time(NULL);

	return;
}

time_t StopWatch_Finish(StopWatch* _data){
	_data->_finish = time(NULL);

	if(_data->_start > _data->_finish)
		return 0;

	return _data->_finish - _data->_start;
}

time_t StopWatch_elapsed_time(StopWatch* _data){
	if(_data->_finish < _data->_start)
		_data->_finish = time(NULL);

	return _data->_finish - _data->_start;
}
#endif /* UHFC_SANAEUTILC_H_ */
