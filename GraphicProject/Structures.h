#pragma once

struct RGB {
	int r;
	int g;
	int b;
};

RGB operator+ (const RGB &l, const RGB &r);

RGB operator- (const RGB &l, const RGB &r);

bool operator== (const RGB &l, const RGB& r);

bool operator!= (const RGB &l, const RGB& r);
