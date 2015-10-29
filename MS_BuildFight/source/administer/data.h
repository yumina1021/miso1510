#pragma once


#define DATA_EVENT_TYPE_START		1
#define DATA_EVENT_TYPE_NONE		0
#define DATA_EVENT_TYPE_PAUSE		2
#define DATA_EVENT_TYPE_END			3


struct DATA_EVENT
{
	int Type;
	int Frame;
};

struct DATA_POSITION
{
	float x, y, z;
};

struct DATA_ROTATION
{
	float x, y, z;
};

struct DATA_MOTION
{
	int motion;
};

struct DATA_SHOT
{
	int Type;
};

struct DATA_OVERLOAD
{
	int Type;
};

struct DATA_TIME
{
	int Time;
};

struct DATA_LIFE
{
	int Gauge;
	int Life;
};

#define DATA_TYPE_EVENT			(1)
#define DATA_TYPE_POSITION		(2)
#define DATA_TYPE_ROTATION		(3)
#define DATA_TYPE_MOTION		(4)
#define DATA_TYPE_SHOT			(5)
#define DATA_TYPE_OVERLOAD		(6)
#define DATA_TYPE_TIME			(7)
#define DATA_TYPE_LIFE			(8)


struct DATA
{
	int		ID;
	int		Type;

	union
	{
		DATA_EVENT		Event;
		DATA_POSITION	Position;
		DATA_ROTATION	Rotation;
		DATA_MOTION		Motion;
		DATA_SHOT		Shot;
		DATA_OVERLOAD	OverLoad;
		DATA_TIME		Time;
		DATA_LIFE		Life;
	};
};
