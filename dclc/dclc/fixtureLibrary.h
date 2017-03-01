#pragma once

enum parameterTypes { intensity, pan, tilt, red, green, blue, cyan, magenta, yellow, smooth, piecewiseSmooth, piecewiseFixed, white, amber, goboRotation, goboIndex, shutter, strobe, control, macro};

struct fixtureParameter {
	char name[255];

};

struct fixtureTemplate {
	char name[255];
	char manufacturer[255];

};

struct fixtureLibrary {
	fixtureTemplate *fixtureTemplate;
	fixtureLibrary *next;
};


void initLibrary(); //Mostly load it from disk


