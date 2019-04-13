#ifndef POS_H
#define POS_H

class Pos
{
public:
	Pos();
	Pos(int, int);
	~Pos();

	int x, y;
	bool operator<(Pos a) const;
	Pos operator=(Pos a);
	bool operator==(Pos a);
};

#endif // !NOW_H
